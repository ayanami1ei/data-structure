#include<iostream>
#include<vector>

using namespace std;

int main()
{
	int n;
	cin >> n;

	vector<int> dp(n + 1, 0);

	dp[0] = 1;
	for (int k = 1; k <= n; ++k) {
		dp[k] = 0;
		for (int i = 0; i < k; ++i)
			dp[k] += dp[i] * dp[k - 1 - i];
	}

	cout << dp[n] << endl;
}