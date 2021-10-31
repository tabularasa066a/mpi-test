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
	

## 参考
1. メイン教材
https://kaityo256.github.io/sevendayshpc/sevendayshpc.pdf

2. こういうのも読んだほうがいいよね（低レイヤについて）
https://tanakamura.github.io/pllp/docs/
