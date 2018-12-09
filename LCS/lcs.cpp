#include <iostream>
#include <vector>
#include <string>
using namespace std;

int LCS_LENGTH(string x, string y, int c[][100], int b[][100])
{
	int m = 0, n = 0;
	m = x.size();
	n = y.size();

	for (int i = 0; i <= m; i++)
		c[i][0] = 0;
	for (int j = 0; j <= n; j++)
		c[0][j] = 0;

	for(int i=1;i<=m;i++)
		for (int j = 1; j <= n; j++)
		{
			if (x[i-1] == y[j-1])
			{
				c[i][j] = c[i - 1][j - 1] + 1;
				b[i][j] = 1;
			}
			else if (c[i - 1][j] >= c[i][j - 1])
			{
				c[i][j] = c[i - 1][j];
				b[i][j] = 2;
			}
			else
			{
				c[i][j] = c[i][j - 1];
				b[i][j] = 3;
			}
		}

	return c[m][n];
}

void PRINT_LCS(int b[][100], string x, int i, int j)
{

	if (i == 0 || j == 0)
		return;
	if (b[i][j] == 1)
	{
		PRINT_LCS(b, x, i-1, j-1);
		cout << x[i-1];
	}
	else if (b[i][j] == 2)
		PRINT_LCS(b, x, i - 1, j);
	else
		PRINT_LCS(b, x, i, j - 1);
}

int main()
{
	string x = "abcbdab";
	string y = "bdcaba";
	const int m = x.size();
	const int n = y.size();

	int c[100][100];
	int b[100][100];
	int length = 0;

	cout << "请输入字符串x:" << endl;
	cin >> x;
	cout << "请输入字符串y:" << endl;
	cin >> y;

	length = LCS_LENGTH(x, y, c, b);

	if (length == 0)
	{
		cout << "没有最长公共字串！" << endl;
	}
	else
	{
		cout << "最长公共字串为:" << endl;
		int i = x.size();
		int j = y.size();
		PRINT_LCS(b, x, i, j);
	}
	cout << "\n\n";
	system("pause");
	
	return 0;
}