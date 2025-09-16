#include<iostream>
#include"stack.hpp"

using namespace std;

int main()
{
	int n;
	cin >> n;

	int sum = 0;

	for (int i = 0; i < n; ++i)
	{
		stack<char> st;
		cin >> st;

		stack<char> tmp;

		while (!st.empty())
		{
			try {
				if (tmp.top()!=st.top())
				{
					tmp.push(st.pop());
				}
				else
				{
					st.pop();
					tmp.pop();
				}
			}
			catch(runtime_error& e)
			{
				if (e.what() == "empty")
					break;
				tmp.push(st.pop());
				continue;
			}
		}

		if (tmp.empty())
			++sum;
	}

	cout << sum;
}