#pragma comment(linker, "/STACK:2769095000")
#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<string>


using namespace std;
/// <summary>
/// ID: 12310 -> 5dig * 4val
/// #ID = 1024
/// </summary>
int gen(int mask, int dig)
{
	while (dig > 0)
	{
		dig--;
		mask = mask | ((rand() % 4) << (dig * 2));
	}
	return mask;
}

int g[1025][5][4];
string info[1025];

pair<int, int> coord(int orig, int nxt)
{
	for (int i = 4; i >= 0; i--)
	{
		if ((((orig ^ nxt) >> 2 * i) & 3) == 0)
			continue;
		int j = (nxt >> 2 * i) & 3;
		return { 4 - i, j };
	}
	return { -1, -1 };
}

string base4(int x)
{
	string s;
	for (int i = 8; i >= 0; i -= 2)
	{
		s += to_string(x >> i & 3);
	}
	return s;
}

int step;
string find(int cur, int finish, bool print = 0)
{

	if (cur == finish)
		return info[finish];
	step++;

	if (print)cout << "from " << cur << " (" << base4(cur) << "):\n";
	int i, j;
	for (int k = 8; k >= 0; k -= 2)
	{
		if ((((cur ^ finish) >> k) & 3) == 0)
			continue;
		j = (finish >> k) & 3;
		i = 4 - k / 2;
		break;
	}
	cout << "common prefix " << i << "  next digit " << j << "\n";
	cout << "next ID: " << g[cur][i][j] << " (" << base4(g[cur][i][j]) << ")\n";
	return find(g[cur][i][j], finish, print);
}

void emulation()
{
	for (int i = 0; i < 1024; i++)
	{
		for (int j = 0; j < 5; j++)
			fill(g[i][j], g[i][j] + 4, -1);
		info[i] = "info about id " + to_string(i);
	}

	for (int i = 0; i < 1024; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				if (g[i][j][k] >= 0)
					continue;
				int mask = (((i >> 2 * (5 - j)) << 2) | k) << 2 * (4 - j);
				if (j == 4 && mask == i)
				{
					g[i][j][k] = i;
					continue;
				}
				while (1)
				{
					int v = gen(mask, 4 - j);
					if (v == i)
						continue;
					g[i][j][k] = v;
					break;
				}
			}
		}
	}

	int mn = 100000, mx = -100000, sum = 0, cntt = 0;
	for (int k = 0; k < 1; k++)
	{
		for (int i = 0; i < 1024; i++)
		{
			cntt++;
			step = 0;
			int finish = rand() % 1024;
			cout << "start search from " << i << " (" << base4(i) << ") to " << finish << " (" << base4(finish)  << ")\n";
			string info = find(i, finish);
			cout << info << "  : " << finish << " " << "with " << step << " step\n\n\n";
			sum += step;
			mn = min(mn, step);
			mx = max(mx, step);
		}
	}
	cout << mn << " " << 1.0 * sum / cntt << " " << mx;
}


int main()
{
	auto _ = freopen("input.txt", "r", stdin);
	_ = freopen("output.txt", "w", stdout);

	emulation();
}
