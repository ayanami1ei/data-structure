#include<list>
#include<iostream>

using namespace std;

class room
{
private:
	int num;
	bool state;//0:free 1:busy
	string name;
public:
	room(int s)
	{
		state = s;
	}
	friend istream& operator>>(istream& in, room& a)
	{
		if (a.state)
			in >> a.name >> a.num;
		return in;
	}
	friend ostream& operator<<(ostream& out, room& a)
	{
		if (a.state)
			out << a.name << "(" << a.num << ")";
		else
			out << a.num;
		return out;
	}

	int& Num()
	{
		return num;
	}

	string& Name()
	{
		return name;
	}

	bool operator==(const room& a) const
	{
		return num == a.num;
	}

	bool& State() 
	{
		return state;
	}
};

class node
{
private:
	list<room> used_rooms,free_rooms;
public:

	node()
	{
		room temp1(0);
		for (int i = 1; i <= 20; i++)
		{
			temp1 = room(0);
			temp1.Num() = i + 100;
			free_rooms.push_back(temp1);
		}
	}

	friend istream& operator>>(istream& in, node& a)
	{
		int n;
		in >> n;
		room temp(1);
		for (int i = 0; i < n; i++)
		{
			in >> temp;
			a.used_rooms.push_back(temp);
		}

		a.upgrade_room();

		return in;
	}

	friend ostream& operator<<(ostream& out, node& a)
	{
		a.sort();
		bool first = true;
		for (auto& i : a.used_rooms) {
			if (!first) 
				out << "-";
			out << i;
			first = false;
		}


		out << endl;
		first = true;
		for (auto& i : a.free_rooms) {
			if (!first) 
				out << "-";
			out << i;
			first = false;
		}

		out << endl;
		return out;
	}

	void upgrade_room()
	{
		for (auto it = free_rooms.begin(); it != free_rooms.end();)
		{
			if (find(used_rooms.begin(), used_rooms.end(),
				*it) != used_rooms.end())
			{
				it = free_rooms.erase(it);
			}
			else 
			{
				++it;
			}
		}

	}
	
	void assign(string name)
	{
		try {
			room x = free_rooms.front();
			free_rooms.pop_front();

			x.Name() = name;
			x.State() = 1;
			used_rooms.push_back(x);
			sort();
		}
		catch (exception& e) {
			throw e;
		}
	}

	void disassign(int n)
	{
		try {
			auto it = find_if(used_rooms.begin(), used_rooms.end(),
				[n](room r) {return r.Num() == n; });
			if (it == used_rooms.end())
				throw exception();
			room x = *it;
			used_rooms.erase(it);
			x.Name() = "";
			x.State() = 0;
			free_rooms.push_back(x);
			sort();
		}
		catch (exception& e) {
			throw e;
		}
	}

	void sort()
	{
		used_rooms.sort([](room r1, room r2) {return r1.Num() < r2.Num(); });
	}

	void display_free()
	{
		bool first = true;
		for (auto& i : free_rooms) {
			if (!first)
				cout << "-";
			cout << i;
			first = false;
		}

		cout << endl;
	}

	void display_used()
	{
		bool first = true;
		for (auto& i : used_rooms) {
			if (!first)
				cout << "-";
			cout << i;
			first = false;
		}

		cout << endl;
	}
};

int main()
{
	node a;
	cin >> a;

	int n;
	cin >> n;

	while (n--)
	{
		string op;
		string name;

		cin >> op;
		if (op=="assign")
		{
			cin >> name;
			try {
				a.assign(name);
			}
			catch (exception& e) {
				//cout << "No room available" << endl;
				continue;
			}
		}
		else if (op == "return")
		{
			int n;
			cin >> n;
			try {
				a.disassign(n);
			}
			catch (exception& e) {
				//cout << "No such person" << endl;
				continue;
			}
		}
		else if (op == "display_free")
		{
			a.display_free();
		}
		else if (op == "display_used")
		{
			a.display_used();
		}
	}
}