# HPC
## 概要
- MPIとか導入してHPCの勉強するよ

## チュートリアル
1. 以下のコードを`hello.cpp`として保存
```c++
#include <cstdio>
#include <mpi.h>
int main(int argc, char **argv)
{
  MPI_Init(&argc, &argv);
  printf("Hello MPI World!\n");
  MPI_Finalize();
  return 0;
}
```

2. `mpic++`でコンパイル
```bash
mpig++ ./hello.cpp
```

3. `mpirun`コマンドで実行
```bash
# -npオプションで並列数（ランク数）を指定
mpirun -np 2 ./a.out
```

## 参考
https://kaityo256.github.io/sevendayshpc/sevendayshpc.pdf
