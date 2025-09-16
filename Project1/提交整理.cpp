#include<iostream>
#include<string>
#include<sstream>
using namespace std;

template<class T>
class node
{
private:
	T val;
public:
	node* prior, * next;
	node();

	node(T v);

	node(const node& a);

	template<class U>
	friend istream& operator>>(istream& in, node<U>& a);

	template<class U>
	friend ostream& operator<<(ostream& out, node<U>& a);

	T& Val();

	node<T> operator=(const node<T>& a);

	bool operator<(node<T>& a);

	bool operator==(node<T>& a);
};

template<class T>
class list
{
private:
	node<T>* head, * end;
	int len;
public:
	list();

	template<class U>
	friend istream& operator>>(istream& in, list<U>& a);

	template<class U>
	friend ostream& operator<<(ostream& out, list<U>& a);

	void set(T* s);

	void insert(int pos, T val);

	void erase(int pos);

	void erase(node<T>& pos);

	void erase(node<T>* pos);

	node<T>& operator[](int pos);

	void swap(int i, int j);

	void sort();

	void insert(list<T>& a);

	int size();
};

template<class T>
node<T>::node()
{
	prior = NULL;
	next = NULL;
}

template<class T>
node<T>::node(T v)
{
	val = v;
	prior = NULL;
	next = NULL;
}

template<class T>
node<T>::node(const node& a)
{
	val = a.val;
	prior = a.prior;
	next = a.next;
}

template<class T>
istream& operator>>(istream& in, node<T>& a)
{
	in >> a.val;
	return in;
}


template<class T>
ostream& operator<<(ostream& out, node<T>& a)
{
	out << a.val;
	return out;
}


template<class T>
T& node<T>::Val()
{
	return val;
}

template<class T>
node<T> node<T>::operator=(const node<T>& a)
{
	val = a.val;
	prior = a.prior;
	next = a.next;
	return *this;
}

template<class T>
bool node<T>::operator<(node<T>& a)
{
	return val < a.val;
}

template<class T>
bool node<T>::operator==(node<T>& a)
{
	return val == a.val;
}

template<class T>
list<T>::list()
{
	len = 0;
	head = NULL;
	end = head;
}

template<class T>
istream& operator>>(istream& in, list<T>& a)
{
	int n;
	in >> n;
	a.len = n;
	if (n == 0)
		return in;

	a.head = new node<T>;
	cin >> *(a.head);

	node<T>* p = a.head;
	for (int i = 1; i < n; i++)
	{
		node<T>* q = new node<T>;
		cin >> *q;
		p->next = q;
		q->prior = p;
		p = q;
	}

	a.end = p;

	return in;
}

template<class T>
ostream& operator<<(ostream& out, list<T>& a)
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

template<class T>
void list<T>::set(T* s)
{
	for (int i = 0; i < s.size(); i++)
	{
		insert(i + 1, s[i]);
	}
}

template<class T>
void list<T>::insert(int pos, T val)
{
	if (pos <= 0 || pos > len + 1)
	{
		throw runtime_error("");
		return;
	}

	try {
		pos--;
		node<T>* p = head;
		while (pos--)
		{
			p = p->next;
		}

		node<T>* q = new node<T>(val);
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

		len++;
	}
	catch (runtime_error& e) {
		throw e;
	}
}

template<class T>
void list<T>::erase(int pos)
{

	if (pos <= 0 || pos > len)
	{
		throw runtime_error("");
		return;
	}
	try {

		pos--;

		node<T>* p = head;
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
		else if (p == end)
		{
			end = p->prior;
			end->next = NULL;
		}

		delete p;

		len--;
	}
	catch (runtime_error& e) {
		throw e;
	}
}

template<class T>
void list<T>::erase(node<T>& pos)
{
	try {
		int in = len;
		node<T>* p = head;
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
	catch (runtime_error& e) {
		throw e;
	}
}

template<class T>
void list<T>::erase(node<T>* pos)
{
	if (pos == NULL)
		return;
	try {
		node<T>* p = pos;
		if (pos->prior)
		{
			p = pos->prior;
			p->next = pos->next;

			if (pos == end)
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
	catch (runtime_error& e) {
		throw e;
	}
}

template<class T>
node<T>& list<T>::operator[](int pos)
{
	if (pos <= 0 || pos > len)
	{
		throw runtime_error("");
	}
	try {
		pos--;
		node<T>* p = head;
		while (pos--)
		{
			p = p->next;
		}
		return *p;// ->Val();
	}
	catch (runtime_error& e) {
		throw e;
	}
}

template<class T>
void list<T>::swap(int i, int j)
{
	node<T>* p = head;
	node<T>* q = head;
	node<T>* t[4];

	if (i <= 0 || i > len || j <= 0 || j > len)
	{
		throw runtime_error("");
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

		node<T> tp = *p;
		node<T> tq = *q;

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
	}
	catch (runtime_error& e) {
		throw e;
	}
}

template<class T>
void list<T>::sort()
{
	for (int i = 1; i <= len; i++)
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

template<class T>
void list<T>::insert(list& a)
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

template<class T>
int list<T>::size()
{
	return len;
}




template<class T>
class stack {
private:
	node<T>* head; // Õ»¶¥Ö¸Õë
	node<T>* tail; // Õ»µ×Ö¸Õë
	int len;

public:
	stack();

	~stack();

	template<class U>
	friend istream& operator>>(istream& in, stack<U>& a);

	void push(T x);

	T pop();

	T top() const;

	bool empty() const;

	T size() const;

	void sort(int s, int e, T(*fp)(T, T) = [](T a, T b) {
		return a < b;
		});

	stack<T> operator=(stack<T>& a);
};

template<class T>
stack<T>::stack()
{
	head = nullptr;
	tail = head;
	len = 0;
}

template<class T>
stack<T>::~stack() {
	while (!empty())
		pop();
}

template<class T>
istream& operator>>(istream& in, stack<T>& a)
{
#if 0
	int n;
	in >> n;
	T val;
	for (int i = 0; i < n; ++i) {
		in >> val;
		a.push(val);
	}

	node<T>* p = a.head;
	while (p->next != nullptr)
		p = p->next;
	a.tail = p;

	return in;
#endif

#if 1
	string str;
	in >> str;

	for (int i = str.size() - 1; i >= 0; --i)
		a.push(str[i]);
	node<T>* p = a.head;
	while (p->next != nullptr)
		p = p->next;
	a.tail = p;

	return in;
#endif
}

template<class T>
void stack<T>::push(T x) {
	if (len == 0)
	{
		head = new node<T>(x);
		tail = head;
		++len;
		return;
	}
	node<T>* a = new node<T>(x);
	a->next = head;
	head->prior = a;
	head = a;
	++len;
}

template<class T>
T stack<T>::pop() {
	if (empty()) {
		cout << "Õ»¿Õ£¬ÎÞ·¨pop" << endl;
		throw runtime_error("empty");
	}

	if (len == 1)
	{
		T val = head->Val();
		delete head;
		head = nullptr;
		tail = head;
		len = 0;
		return val;
	}
	node<T>* tmp = head;
	head = head->next;
	head->prior = nullptr;

	T val = tmp->Val();

	delete tmp;
	--len;

	return val;
}

template<class T>
T stack<T>::top() const {
	if (empty()) {
		//cout << "Õ»¿Õ£¬Ã»ÓÐÕ»¶¥ÔªËØ" << endl;
		throw runtime_error("");
	}
	return head->Val();
}

template<class T>
bool stack<T>::empty() const {
	return head == nullptr;
}

template<class T>
T stack<T>::size() const {
	return len;
}

template<class T>
void stack<T>::sort(int s, int e, T(*fp)(T, T))
{
	if (e - s <= 1)
		return;

	int i = s, j = e;
	T mid;
	node<T>* p = head, pi = head, pj = head;
	int l = len;

	for (int k = 0; k < i; ++k)
		pi = pi->next;
	for (int k = 0; k < j; ++k)
		pj = pj->next;

	while (l >= len / 2)
	{
		p = p->next;
	}
	mid = p->Val();

	while (i <= j)
	{
		while (fp(pi->Val(), mid))
		{
			pi = pi->next;
			++i;
		}
		while (fp(mid, pj->Val()))
		{
			pj = pj->prior;
			--j;
		}

		if (i <= j)
		{
			T tmp = pi->Val();
			pi->val = pj->Val();
			pj->val = tmp;
			pi = pi->next;
			pj = pj->prior;
			++i;
			--j;
		}
	}
	sort(s, i, fp);
	sort(i, e, fp);
}

template<class T>
stack<T> stack<T>::operator=(stack<T>& a)
{
	if (this == &a)
		return *this;
	while (!empty())
		pop();
	node<T>* p = a.tail;
	while (p)
	{
		push(p->Val());
		p = p->prior;
	}
	return *this;
}


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
				if (tmp.top() != st.top())
				{
					tmp.push(st.pop());
				}
				else
				{
					st.pop();
					tmp.pop();
				}
			}
			catch (runtime_error& e)
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