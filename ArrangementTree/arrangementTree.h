#pragma once
#include <iostream>

using namespace std;

void output(int n, int x[])
{
	for (int i = 1; i <= n; i++)
		cout << x[i];
	cout << endl;
}

void backTrack(int t, int x[], int n)
{
	if (t > n)
		output(n, x);
	else
	{
		for (int i = t; i <= n; i++)
		{
			swap(x[t], x[i]);
			backTrack(t + 1, x, n);
			swap(x[t], x[i]);
		}
	}
}