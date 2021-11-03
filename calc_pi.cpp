/* モンテカルロ法
pi = 4*n / N
x, y: 正方形内の点（-1<=x<1, -1<=y<=1; 一様分布で出す）
n: 円内の点の数（x^2 + y^2 <= 1のときn++）
N: -1<=x<=1, -1<=y<=1を満たす点(x, yの)総数
*/
#include <cstdio>
#include <random>
#include <algorithm>

const int TRIAL = 100000;

double calc_pi(const int seed)
{
	std::mt19937 mt(seed);
	std::uniform_real_distribution<double> ud(0.0, 1.0);
	int n = 0;
	for (int i = 0; i < TRIAL; i++)
	{
		double x = ud(mt);
		double y = ud(mt);
		if (x * x + y * y < 1.0)
			n++;
	}

	return 4.0 * static_cast<double>(n) / static_cast<double>(TRIAL);
}

int main(void)
{
	double pi = calc_pi(0);
	printf("%f\n", pi);
}
