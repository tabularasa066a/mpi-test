/*
C++98ではこのコードはコンパイル滑る
mpic++ thermal.cpp -std=c++11
でコンパイルしよう

拡散方程式の導出については以下：
https://www.se.fukuoka-u.ac.jp/iwayama/teach/kisoIII/2016/chap6.pdf

多変数のテイラー展開忘れた：
https://eman-physics.net/math/taylor_multi.html
*/
#include <cstdio>
#include <fstream>
#include <iostream>
#include <vector>

const int L = 128;
const int STEP = 100000;
const int DUMP = 1000;

// １ステップの計算を行う
void onestep(std::vector<double> &lattice, double h, int rank, int procs)
{
  const int size = lattice.size();
  static std::vector<double> orig(L);
  std::copy(lattice.begin(), lattice.end(), orig.begin());

  // ここから通信のためのコード
  const int left = (rank - 1 + procs) % procs;
  const int right = (rank + 1) % procs;
  MPI_Status st;
  // 右端を右に送って、左端を左を受け取る
  MPI_Sendrecv(&(lattice[size - 2]), 1, MPI_DOUBLE, right, 0, &(orig[0]), 1, MPI_DOUBLE, left, 0, MPI_COMM_SROLD, &st);
  // 左端を左に送って、右端を右から受け取る
  MPI_Sendrecv(&(lattice[1]), 1, MPI_DOUBLE, left, 0, &(orig[size - 1]), 1, MPI_DOUBLE, right, 0, MPI_COMM_SROLD, &st);

  for (int i = 1; i < L - 1; i++)
  { // i=0(始点), i=L(終点)は境界条件にて渡す
    lattice[i] += h * (orig[i - 1] - 2.0 * orig[i] + orig[i + 1]);
  }

  // 周期境界
  lattice[0] += h * (orig[L - 1] - 2.0 * lattice[0] + orig[1]);
  lattice[L - 1] += h * (orig[L - 2] - 2.0 * lattice[L - 1] + orig[0]);
}

// ファイルへの出力を行う(DUMPステップ毎)
void dump(std::vector<double> &data)
{
  static int index = 0;
  char filename[256];
  sprintf(filename, "data%03d.dat", index);

  std::cout << filename << std::endl;
  std::ofstream ofs(filename);
  for (unsigned int i = 0; i < data.size(); i++)
  {
    ofs << i << " " << data[i] << std::endl;
  }
  index++;
}

void dump_mpi(std::vector<double> &local, int rank, int procs)
{
  static std::vector<double> global(L);
  MPI_Gather(&(local[1], L / procs, MPI_DOUBLE, global.data(), L / procs, MPI_DOUBLE, 0, MPI_COMM_WORLD));
  if (rank == 0)
  {
    dump(global);
  }
}

// 温度固定での計算を行う
void fixed_temperature(std::vector<double> &lattice)
{
  const double h = 0.01;
  const double Q = 1.0; // 単位時間の加熱量[J/s=W]
  for (int i = 0; i < STEP; i++)
  {
    // 計算カーネル呼び出し
    onestep(lattice, h);
    lattice[L / 4] = Q;
    lattice[3 * L / 4] = -Q;

    // ファイルへの出力
    if (i % DUMP == 0)
    {
      dump(lattice);
    }
  }
}

// 一様加熱での計算を行う
void uniform_heating(std::vector<double> &lattice)
{
  const double h = 0.2;
  const double Q = 1.0; // 単位時間の加熱量[J/s=W]
  for (int i = 0; i < STEP; i++)
  {
    // 計算カーネル呼び出し
    onestep(lattice, h);
    for (auto &s : lattice)
    {
      s += Q * h;
    }
    lattice[0] = 0.0;
    lattice[L - 1] = 0.0;

    // ファイルへの出力
    if (i % DUMP == 0)
    {
      dump(lattice);
    }
  }
}

int main()
{
  MPI_Init(&argc, &argv);
  std::vector<double> lattice(L, 0.0);
  // どっちかコメントアウトじゃ
  // fixed_temperature(lattice);
  uniform_heating(lattice);
}
