#pragma once
#include <iostream>

using namespace std;

bool placeTest(int k, int x[])
{
	for (int i = 1; i <= k-1; i++)
		if (x[i] == x[k] || (abs(x[i] - x[k]) == abs(i - k)))
			return false;
	return true;
}


void print(int n, int x[])
{
	for (int i = 1; i <= n; i++)
		cout << x[i] << " ";
	cout << endl;
}

void nQueen(int k, int x[], int n)
{
	if (k > n)
		print(n, x);
	else
	{
		for (int i = 1; i <= n; i++)
		{
			x[k] = i;
			if (placeTest(k, x))
				nQueen(k + 1, x, n);
		}
	}
}


