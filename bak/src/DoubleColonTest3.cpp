//:: 的作用之三：隐藏再现
#include <iostream>
using namespace std;
class A {
public:
	static int i;
	static void Add() {
		i++;
	}
	void out() {
		cout << "static i = " << i << endl;
	}
};
int A::i = 10;
class B: private A {
public:
	A ::out;
};
class C: public A {//public B
public:
	void f();
};
void C::f() {
	A::i = 50;
	A::Add();
}
int main_doublecolontest3() {
	A a;
	C c;
	a.Add();
	a.out();
	c.f();
	c.out();
	cout << "static i = " << A::i << endl;

	return 0;
}
