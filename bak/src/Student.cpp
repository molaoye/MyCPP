/*
 * Student.cpp
 *
 *  Created on: 2015-11-23
 *      Author: chency
 */

#include <iostream>  // 预处理命令

using namespace std;

class Student //声明一个类,类名为Student
{
private:
	//以下为类中的私有部分
	int num; //私有变量num
	int score; //私有变量score
public:
	//以下为类中的公用部分
	void setdata() //定义公用函数setdata
	{
		cin >> num; //输入num的值
		cin >> score; //输入score的值
	}
	void display() //定义公用函数display
	{
		cout << "num=" << num << endl;//输出num
		cout << "score=" << score << endl; //输出score
	}
};

Student stud1,stud2;

int main_student(){
	stud1.setdata(); // 调用对象stud1的setdata函数
	stud2.setdata(); // 调用对象stud2的setdata函数
	stud1.display(); // 调用对象stud1的display函数
	stud2.display(); // 调用对象stud2的display函数
	return 0;
}
