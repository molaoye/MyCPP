//:: 的作用之一：恢复访问权
#include <iostream>
using namespace std;
class A {
public:
	A(int xx = 1, int yy = 2) {
		X = xx;
		Y = yy;
	}
	int get_XY() {
		return X * Y;
	}
	void put_XY() {
		cout << X << "*" << Y << "=" << X * Y << endl;
	}
protected:
	int X, Y;
};
class B: private A {
public:
	B(int s, int xx, int yy) :
		A(xx, yy), S(s) {
	}
	A :: put_XY;
	A :: get_XY;
	void make_S() {
		put_XY();
		cout << S << endl;
	}
private:
	int S;
};

int main_doublecolontest2() {
	B b(3, 5, 6);
	b.get_XY();
	b.put_XY();
	b.make_S();

	return 0;
}
