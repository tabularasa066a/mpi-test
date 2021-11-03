# HPC
## 概要
- MPIとか導入してHPCの勉強するよ

## C++MPIソースのコンパイルと実行の流れ
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
## スパコンメモ書き
- スパコンは複数のユーザの計算要求を処理する必要がある → ジョブ管理が大事
	- 各ユーザが実行させたい計算のことをジョブという
	- 複数のユーザのジョブの実行を管理することをジョブスケジューリングという
	- ユーザ要求ノード数や実行時間を記したジョブスクリプトを書いてスケジューラに提出する
- 大容量のファイルを複数ノードで共有する必要 → 大規模なネットワークファイルシステム
- ネットワーク（ちゃんと値のパッシングが成立）と信頼性（一部のノードが落ちても大事に至らない）が大切だよ

## アルゴリズム覚書（ここじゃないよね・・・）
### モンテカルロ法：乱数で円周率を求める
1. 正方形（D={(x,y) | -1<=x<=1, -1<=y<=1})に内接する半径１の円（C）を考える。
2. Dを描画するN個の点(x,y)を乱数で生成していく
3. 乱数点(x,y)がCに入る時、その個数をカウントする（`if(x*x+y*y<=1）n++`）
4. 面積比：C/Dを考えると
```
C / D = π / 4 = n / N
∴ π = (4 * n) / N
```
が言えるので乱数から円周率が求まる。

### 拡散方程式の導出の流れ
1. 着目物理量（それは位置と時刻からなる関数）を定義
2. Δt後の物理量を期待値として求める
3. テイラー展開して式を整理する（時刻項はオーダ２で切る点注意）

- 導出：
https://www.se.fukuoka-u.ac.jp/iwayama/teach/kisoIII/2016/chap6.pdf
- 多変数関数のテイラー展開（忘れてる・・・：
https://eman-physics.net/math/taylor_multi.html



## 参考
1. メイン教材
https://kaityo256.github.io/sevendayshpc/sevendayshpc.pdf

2. こういうのも読んだほうがいいよね（低レイヤについて）
https://tanakamura.github.io/pllp/docs/
