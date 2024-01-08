//#pragma once
#ifndef VM450G12control_H
#define VM450G12control_H
//#include some class maybe
#include <string>

class VM450G12Control
{
	double thetad, thetav, d, v;  //rad rad cm cm/s
	double R_t, R_r;
	double v1_t, v2_r, v2_t;
	int kr;
	int time1, time2;  //time3;
	//double t, r;
	double t1m1, t1m2, t2m1, t2m2;
	double t1m1_0, t1m2_0, t2m1_0, t2m2_0;
	int time1_0, time2_0;
public:
	bool debug;
	VM450G12Control();
	~VM450G12Control();
	void geterror(double& thetadd, double& thetavv, double& dd, double& vv); //geterror(const double& x, const double& y, ...);
	void setk(const std::string& whichk, const double& num);
	void calculate();
	void wifi_it();
};

#endif 



