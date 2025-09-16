#include<iostream>
#include"stack.hpp"
#include<string>

using namespace std;

int main()
{
	string s;
	cin >> s;
	s = string(s.rbegin(), s.rend());

	stack<char> orig;
	stack<int> num;
	//int an = 0;

	for (char c : s)
		orig.push(c);
	int temp = 0;
	int rhs;
	int lhs;
	while (!orig.empty())
	{
		switch (orig.top())
		{
		case '+':
			temp = num.pop();
			temp += num.pop();
			num.push(temp);
			temp = 0;
			orig.pop();
			break;
		case '-': 
			rhs = num.pop(); 
			lhs = num.pop(); 
			num.push(lhs - rhs);
			orig.pop();
			break;
		
		case '*':
			temp = num.pop();
			temp *= num.pop();
			num.push(temp);
			temp = 0;
			orig.pop();
			break;
		case '/': 
			rhs = num.pop();
			lhs = num.pop();
			num.push(lhs / rhs);
			orig.pop();
			break;

		case '.':
			num.push(temp);
			temp = 0;
		case '@':
			orig.pop();
			continue;
			break;

		default:
			temp = temp * 10 + orig.pop() - '0';
			break;
		}
	}

	cout << num.pop() << endl;
}