//:: 的作用之二：隐藏再现
#include <iostream>
using namespace std;
class A {
public:
	int X, Y;
};
class B: public A {
public:
	int Y, Z;
};
int main_doublecolontest1() {
	B b;
	b.X = 1;
	b.Y = 2;
	b.A::Y = 3;
	b.Z = 4;
	return 0;
}
