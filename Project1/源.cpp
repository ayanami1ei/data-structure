#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
using namespace std;

class poly {
private:
	int coef;
	int expn;
public:
	poly() {}
	poly(int c, int e) :coef(c), expn(e) {}
	friend istream& operator>>(istream& in, poly& a)
	{
		in >> a.coef >> a.expn;
		return in;
	}

	friend ostream& operator<<(ostream& out, poly& a)
	{
		if (a.expn==0)
			out << a.coef;
		else if (a.expn == 1)
		{
			if (a.coef == 1)
				out << "x";
			else if (a.coef == -1)
				out << "-x";
			else
				out << a.coef << "x";
		}
		else if (a.coef == 1)
			out << "x^" << a.expn;
		else if (a.coef == -1)
			out << "-x^" << a.expn;
		else
			out << a.coef << "x^" << a.expn;
		return out;
	}

	poly operator+(const poly& b) {
		if (expn != b.expn) {
			return poly(0, 0);
		}
		return poly{ coef + b.coef, expn };
	}

	poly operator-(const poly& b) {
		if (expn != b.expn) {
			return poly(0, 0);
		}
		return poly{ coef - b.coef, expn };
	}

	bool operator<(const poly& b) const {
		return expn < b.expn;
	}

	int getCoef() const {
		return coef;
	}

	int getExpn() const {
		return expn;
	}
};

class clist {
private:
	poly n[1000];
	int maxlen;

public:
	int len;
	poly operator[](int i) {
		return n[i];
	}
	clist(){
		len = 0;
		maxlen = 1000;
	}
	friend istream& operator>>(istream& in, clist& a)
	{
		in >> a.len;
		if (a.len < 0 || a.len >= a.maxlen) {
			cout << "error\n";
			a.len = 0;
			return in;
		}
		for (int i = 0; i < a.len; i++)
			in >> a.n[i];

		return in;
	}

	friend ostream& operator<<(ostream& out, clist& a)
	{
		if (a.len < 0 || a.len >= a.maxlen) {
			out << "error\n";
			return out;
		}

		bool f = true;

		//out << a.len << " ";
		for (int i = 0; i < a.len; i++)
		{
			if (i != 0)
			{
				if (a.n[i].getCoef() > 0)
					out << "+";
			}
			out << a.n[i];
			f = false;
		}
		if (f)
			out << 0;
		return out;
	}

	int insert(int pos, poly val)
	{
		if(len+1>=maxlen){
			cout << "error\n";
			return 1;
		}
		pos--;
		if (pos < 0 || pos >= len+1) {
			cout << "error\n";
			return 1;
		}
		try {
			for (int i = len; i > pos; i--)
			{
				n[i] = n[i - 1];
			}
			n[pos] = val;
			len++;

			return 0;
		}
		catch (exception& e) {
			cout << "error\n";
			return 1;
		}
	}

	int erase(int pos)
	{
		if (len + 1 >= maxlen) {
			cout << "error\n";
			return 1;
		}
		pos--;
		if (pos<0 || pos>=len) {
			cout << "error\n";
			return 1;
		}
		try {
			len--;
			for (int i = pos; i < len; i++)
			{
				n[i] = n[i + 1];
			}

			return 0;
		}
		catch (exception& e) {
			cout << "error\n";
			return 1;
		}
	}

	void find(int pos)
	{
		if (len + 1 >= maxlen) {
			cout << "error\n";
			return;
		}
		pos--;
		if (pos < 0 || pos >= len) {
			cout << "error\n";
			return;
		}
		try {
			cout << n[pos] << endl;
		}
		catch (exception& e) {
			cout << "error\n";
			return;
		}
	}

	int multiinsert
	(int i, int n, poly item[])
	{
		for (int k=0;k<n;k++)
			if (insert(i + k, item[k])!=0)
				return 1;
		return 0;
	}

	int multidel(int i, int n)
	{
		for (int k = 0; k < n; k++)
			if (erase(i)!=0)
				return 1;
		return 0;
	}

	void move(int f, int d) {
		d = d % len;
		poly* temp = new poly[d];
		if (f == 0) {
			for (int i=0;i< d; i++)
				temp[i] = n[i];

			for (int i = 0; i < len - d; i++)
				n[i] = n[i + d];

			for (int i = 0; i < d; i++)
				n[len - d + i] = temp[i];
		}
		else {
			for (int i = 0; i < d; i++)
				temp[d-1-i] = n[len-1-i];

			for (int i = len-1; i >= d; i--)
				n[i] = n[i - d];

			for (int i = 0; i < d; i++)
				n[d-1-i] = temp[d-1-i];
		}
		delete[] temp;
	}
#if 0
	void findLongestSub() {
		vector<vector<poly>> res;

		for (int i = 0; i < len; i++) {
			res.push_back(vector<poly>{n[i]});
			for (int j = i + 1; j < len; j++) {
				if (n[j] > res.back().back()) {
					res.back().push_back(n[j]);
				}
				else
					break;
			}
		}

		sort(res.begin(), res.end(), [](const vector<int>& a, const vector<int>& b) {
			return a.size() > b.size();
			});

		for (int i = 0; i < res[0].size(); i++) {
			cout << res[0][i];
			if (i != res[0].size() - 1)
				cout << " ";
		}
	}
#endif
	void sort() {
		std::sort(n, n + len);
	}

	clist operator+(clist& b) {
		clist res;
		this->sort();
		b.sort();
		int i = 0, j = 0;
		while (i < this->len && j < b.len) {
			if (this->n[i].getExpn() == b.n[j].getExpn()) {
				poly temp = this->n[i] + b.n[j];
				if (temp.getCoef() != 0)
					res.insert(res.len + 1, temp);
				i++;
				j++;
			}
			else if (this->n[i].getExpn() < b.n[j].getExpn()) {
				res.insert(res.len + 1, this->n[i]);
				i++;
			}
			else {
				res.insert(res.len + 1, b.n[j]);
				j++;
			}
		}
		while (i < this->len) {
			res.insert(res.len + 1, this->n[i]);
			i++;
		}
		while (j < b.len) {
			res.insert(res.len + 1, b.n[j]);
			j++;
		}
		return res;
	}

	clist operator-(clist& b) {
		clist res;
		this->sort();
		b.sort();
		int i = 0, j = 0;
		while (i < this->len && j < b.len) {
			if (this->n[i].getExpn() == b.n[j].getExpn()) {
				poly temp = this->n[i] - b.n[j];
				if (temp.getCoef() != 0)
					res.insert(res.len + 1, temp);
				i++;
				j++;
			}
			else if (this->n[i].getExpn() < b.n[j].getExpn()) {
				res.insert(res.len + 1, this->n[i]);
				i++;
			}
			else {
				res.insert(res.len + 1, poly(-b.n[j].getCoef(), b.n[j].getExpn()));
				j++;
			}
		}
		while (i < this->len) {
			res.insert(res.len + 1, this->n[i]);
			i++;
		}
		while (j < b.len) {
			res.insert(res.len + 1, poly(-b.n[j].getCoef(), b.n[j].getExpn()));
			j++;
		}
		return res;
	}
};


int main()
{
	int t;
	cin >> t;

	while (t--) {
		clist a;
		cin >> a;
		cout << a << endl;

		clist b;
		cin >> b;
		cout << b << endl;

		clist c;
		c = a + b;
		cout << c << endl;

		c = a - b;
		cout << c << endl << endl;
	}
}