#include "VM450G12Control.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
vector<double> FIRST()
{
	cout << "d  thetad  v  thetav :" << endl;
	string line1;
	vector<double> input1;
	double tool;
	int count = 0;
	//cin.ignore(1024, '\n');
	getline(cin, line1);
	istringstream ss(line1);
	while (ss >> tool)
	{
		count++;
		/*
		if (count > 4)
		{
			cin.ignore(1024, '\n');
			cout << "you are stupid!" << endl;

			input1=FIRST();
		}
		*/
		input1.push_back(tool);
	}
	if (count != 4)
	{
		//cin.ignore(1024, '\n');
		cout << "you are stupid!" << endl;

		input1 = FIRST();
	}
	return input1;
}
vector<double> SECOND()
{
	cout << "rt		rr		v1t		v2r		v2t		time1	time2	kr	:" << endl;
	string line2;
	vector<double> input2;
	double tool;
	int count = 0;
	//cin.ignore(1024, '\n');
	getline(cin, line2);
	istringstream ss(line2);
	while (ss >> tool)
	{
		count++;
		/*
		if (count > 5)
		{
			cin.ignore(1024, '\n');
			cout << "you are stupid!" << endl;

			input2=SECOND();
		}
		*/
		input2.push_back(tool);
	}
	if (count != 8)
	{
		//cin.ignore(1024, '\n');
		cout << "you are stupid!" << endl;

		input2 = SECOND();
	}
	return input2;
}


int main()
{
	//printf("hello world\n");
	//double A[2][2][2][2];
	//printf("%f\n", A[0][0][0][-1]);
	//system("pause");

	//const int a(0);
	//const int b(1);
	//const int* pa = &a;
	//const int* pb = &b;
	//const int* &r = pa;
	//r = &b;

	/*
	const int& r = 10;
	const int* p=&r;
	p = p + 4;
	*/
	//int a = -1;
	//std::cout << std::to_string(a) << std::endl;
	VM450G12Control test;

	double thetad = M_PI / 6;
	double thetav = -M_PI / 36;
	double d = 20;
	double v = 5;

	vector<double> first, second;

	cout << "Do you want to change inputs? [y/n]" << endl;

	if (getchar() != 'n')
	{
		cin.ignore(1024, '\n');
		first = FIRST();
		d = first[0];
		thetad = first[1];
		v = first[2];
		thetav = first[3];
	}
	else cin.ignore(1024, '\n');

	cout << "Do you want to change coefficients? [y/n]" << endl;
	if (getchar() != 'n')
	{
		cin.ignore(1024, '\n');
		second = SECOND();
		test.setk("rt", second[0]);
		test.setk("rr", second[1]);
		test.setk("v1t", second[2]);
		test.setk("v2r", second[3]);
		test.setk("v2t", second[4]);
		test.setk("t1", second[5]);
		test.setk("t2", second[6]);
		test.setk("kr", second[7]);
	}
	else cin.ignore(1024, '\n');

	test.geterror(thetad, thetav, d, v);
	test.calculate();
	test.wifi_it();






	return 0;
}
