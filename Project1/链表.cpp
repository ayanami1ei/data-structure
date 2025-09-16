#if 1

#include<iostream>
#include<string>
#include<sstream>
using namespace std;

class Basicnode
{
private:
	char val;
public:
	Basicnode* prior, * next;
	Basicnode()
	{
		prior = NULL;
		next = NULL;
	}

	Basicnode(char v)
	{
		val = v;
		prior = NULL;
		next = NULL;
	}

	Basicnode(const Basicnode& a)
	{
		val = a.val;
		prior = a.prior;
		next = a.next;
	}

	friend istream& operator>>(istream& in, Basicnode& a)
	{
		in >> a.val;
		return in;
	}

	friend ostream& operator<<(ostream& out, Basicnode& a)
	{
		out << a.val;
		return out;
	}

	char& Val()
	{
		return val;
	}

	Basicnode operator=(const Basicnode& a)
	{
		val = a.val;
		prior = a.prior;
		next = a.next;
		return *this;
	}

	bool operator<(Basicnode& a)
	{
		return val < a.val;
	}

	bool operator==(Basicnode& a)
	{
		return val == a.val;
	}

#if 0
	bool operator>(Basicnode& a)
	{
		return val > a.val;
	}

	bool operator==(Basicnode& a)
	{
		return val == a.val;
	}
#endif
};

class node
{
private:
	Basicnode* head, * end;
	int len;
public:
	node()
	{
		len = 0;
		head = NULL;
		end = head;
	}

	friend istream& operator>>(istream& in, node& a)
	{
		int n;
		in >> n;
		a.len = n;
		if (n == 0)
			return in;

		a.head = new Basicnode;
		cin >> *(a.head);

		Basicnode* p = a.head;
		for (int i = 1; i < n; i++)
		{
			Basicnode* q = new Basicnode;
			cin >> *q;
			p->next = q;
			q->prior = p;
			p = q;
		}

		a.end = p;

		return in;
	}

	friend ostream& operator<<(ostream& out, node& a)
	{
		if (a.len == 0)
		{
			out << "-";
			return out;
		}
		for (int i = 1; i <= a.len; i++)
		{
			out << a[i];
		}
		return out;
	}

	void set(string s)
	{
		for (int i=0;i<s.size();i++)
		{
			insert(i + 1, s[i]);
		}
	}

	void insert(int pos, char val)
	{
		if (pos <= 0 || pos > len + 1)
		{
			throw exception();
			return;
		}

		try {
			pos--;
			Basicnode* p = head;
			while (pos--)
			{
				p = p->next;
			}

			Basicnode* q = new Basicnode(val);
			if (p == head)
			{
				head = q;
				if (len != 0)
				{
					q->next = p;
					p->prior = q;
				}
				else
					end = q;
			}
			else if (p == NULL)
			{
				end->next = q;
				q->prior = end;
				end = q;
			}
			else if (p->prior)//&& p->next)
			{
				//if (p == end)
					//end = q;
				p->prior->next = q;
				q->prior = p->prior;
				p->prior = q;
				q->next = p;
			}
#if 0
			else if (p == end)
			{
				end = q;
				q->prior = p;
				p->next = q;
			}
#endif

			len++;
		}
		catch(exception& e) {
			throw e;
		}
	}

	void erase(int pos)
	{
		
		if (pos <= 0 || pos > len)
		{
			throw exception();
			return;
		}
		try {

			pos--;

			Basicnode* p = head;
			while (pos--)
			{
				p = p->next;
			}

			if (p == head)
				head = p->next;
			else if (p->next && p->prior)
			{
				p->prior->next = p->next;
				p->next->prior = p->prior;
			}
			else if (p==end)
			{
				end = p->prior;
				end->next = NULL;
			}
				
			delete p;

			len--;
		}
		catch (exception& e) {
			throw e;
		}
	}

	void erase(Basicnode& pos)
	{
		try {
			int in = len;
			Basicnode* p = head;
			while (1)
			{
				p = p->next;
				if (*p == pos)
					break;
			}

			if (p == head)
				head = p->next;
			else if (p->next && p->prior)
			{
				p->prior->next = p->next;
				p->next->prior = p->prior;
			}
			else if (p == end)
			{
				end = p->prior;
				end->next = NULL;
			}

			delete p;

			len--;
		}
		catch (exception& e) {
			throw e;
		}
	}

	void erase(Basicnode* pos)
	{
		if (pos == NULL)
			return;
		try {
			Basicnode* p = pos;
			if (pos->prior)
			{
				p = pos->prior;
				p->next = pos->next;

				if (pos== end)
					end = p;
				else
					pos->next->prior = p;

				delete pos;
			}
			else if (pos->next)
			{
				p = pos->next;
				p->prior = pos->prior;
				head = p;
				delete pos;
			}
			else
			{
				delete pos;
				head = NULL;
				end = NULL;
			}
			

			len--;
		}
		catch (exception& e) {
			throw e;
		}
	}

	Basicnode& operator[](int pos)
	{
		if (pos <= 0 || pos > len)
		{
			throw exception();
		}
		try {
			pos--;
			Basicnode* p = head;
			while (pos--)
			{
				p = p->next;
			}
			return *p;// ->Val();
		}
		catch (exception& e) {
			throw e;
		}
	}

	void swap(int i,int j)
	{
		Basicnode* p = head;
		Basicnode* q = head;
		Basicnode* t[4];

		if (i <= 0 || i > len || j <= 0 || j > len)
		{
			throw exception();
			return;
		}

		try {
			int ti = i, tj = j;
			ti--;
			tj--;
			while (ti--)
			{
				p = p->next;
			}
			while (tj--)
			{
				q = q->next;
			}

			Basicnode tp = *p;
			Basicnode tq = *q;

			if (i < j)
			{
				erase(j);
				erase(i);

				insert(i, tq.Val());
				insert(j, tp.Val());
			}
			else
			{
				erase(i);
				erase(j);
				insert(j, tp.Val());
				insert(i, tq.Val());
			}
			
#if 0
			t[0] = p->prior;
			t[1] = p->next;

			t[2] = q->prior;
			t[3] = q->next;

			p->swap(q);

			if (p==head)
				head = q;
			else if (q == head)
				head = p;

			if (p == end)
				end = q;
			else if (q == end)
				end = p;

			if (p->prior && p->prior->next)
				p->prior->next = q;
			if (p->next && p->next->prior)
				p->next->prior = q;
			if (q->prior && q->prior->next)
				q->prior->next = p;
			if (q->next && q->next->prior)
				q->next->prior = p;
#endif
		}
		catch (exception& e) {
			throw e;
		}
	}

	void sort()
	{
		for (int i=1;i <= len; i++)
		{
			for (int j = i + 1; j <= len; j++)
			{
				if ((*this)[j] < (*this)[i])
				{
					swap(i, j);
				}
			}
		}
	}

	void insert(node& a)
	{
		if (a.len == 0)
			return;
		if (len == 0)
		{
			head = a.head;
			end = a.end;
			len = a.len;
			return;
		}
		end->next = a.head;
		a.head->prior = end;
		end = a.end;
		len += a.len;
	}

	int size()
	{
		return len;
	}

#if 0
	void geo(int n, int k, int s)
	{
		if (n == 1)
		{
			cout << "1 ";
			return;
		}
		if (n == 0)
			return;
		len = n;
		if (n <= 0 || s <= 0 || s > n || k <= 0)
		{
			throw exception();
			return;
		}

		try {
			head = new Basicnode(1);
			Basicnode* p = head;
			for (int i = 2; i <= n; i++)
			{
				Basicnode* q = new Basicnode(i);
				p->next = q;
				q->prior = p;
				p = q;
			}
			end = p;
			end->next = head;
			head->prior = end;
			p = head;
			
			while(s--)
				p = p->next;

			p = p->prior;

			while (len > 2)
			{
				for (int i = 1; i < k; i++)
					p = p->next;
				cout << *p << " ";

				Basicnode* tp = p;
				p = p->next;
				tp->prior->next = tp->next;
				tp->next->prior = tp->prior;
				len--;
				delete tp;

				
				//if (len == 1)
				//{
				//	cout << *p << endl;
				//	return;
				//}
			}

			if (k%2!=1)
				cout << *(p->next) << " " << *p<<" ";
			else
				cout << *p << " " << *(p->next)<<" ";
		}
		catch (exception& e) {
			throw e;
		}
	}
#endif

	void zuma()
	{
		Basicnode* p = head;
		//p = p->next;

		while (p && p->next)
		{
			int c = 1;

			Basicnode* q = p;
			while (q->next && *q == *(q->next))
			{
				c++;
				q = q->next;
			}
			if (c>=3)
			{
				if (c==len)
				{
					len = 0;
					head = NULL;
					end = NULL;
					return;
				}
				if (p->prior)
				{
					p = p->prior;
					for (int i=0;i<c;i++)
						erase(p->next);
				}
				else if(p == head)
				{
					p = q;
					head = q;
				}
				else
				{
					head = NULL;
					end = NULL;
					len = 0;

					delete p->next->next;
					delete p->next;
					delete p;

					return;
				}

				//if (len >= 3)
				//	zuma();
				if (len < 3)
					return;

				p = head;
			}
			else if (p->next)
				p = p->next;
		}
	}
};



int main()
{
	string s;
	cin >> s;
	node a;
	a.set(s);

	int p, n;
	char c;

	cin >> n;

	while (n--) 
	{
		cin >> p >> c;
		p++;
		a.insert(p, c);
		a.zuma();
		cout << a << endl;
	}
	
}

#endif