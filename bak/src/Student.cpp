/*
 * Student.cpp
 *
 *  Created on: 2015-11-23
 *      Author: chency
 */

#include <iostream>  // Ԥ��������

using namespace std;

class Student //����һ����,����ΪStudent
{
private:
	//����Ϊ���е�˽�в���
	int num; //˽�б���num
	int score; //˽�б���score
public:
	//����Ϊ���еĹ��ò���
	void setdata() //���幫�ú���setdata
	{
		cin >> num; //����num��ֵ
		cin >> score; //����score��ֵ
	}
	void display() //���幫�ú���display
	{
		cout << "num=" << num << endl;//���num
		cout << "score=" << score << endl; //���score
	}
};

Student stud1,stud2;

int main_student(){
	stud1.setdata(); // ���ö���stud1��setdata����
	stud2.setdata(); // ���ö���stud2��setdata����
	stud1.display(); // ���ö���stud1��display����
	stud2.display(); // ���ö���stud2��display����
	return 0;
}
