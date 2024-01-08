#include "VM450G12Control.h"
//#include wifi class 
#define _USE_MATH_DEFINES
#include <math.h>
#include <string>
#include <iostream>
#include <iomanip>
//#include <curl/curl.h>

using namespace std;

VM450G12Control::VM450G12Control()
	:thetad(0), thetav(0), d(0), v(0), debug(true),time2_0(0),t2m1_0(0),t2m2_0(0)    //thetad is somehow strange defined and may need port
{
	R_t    = 4;                      R_r    = 9;
//  [0,10)                          [0,10)

	v1_t   = 5;                      v2_r   = 7;                        v2_t   = 6;//v2_t & v2_r due to the lack of side propellers, having v2 term may or may not help~
//  [0,10)                          [0,10)                             [0,10)    
	kr = 3000;
	time1 = 150;
	time2 = 650;
	//time3 = 550; //ms for stage period

}


VM450G12Control::~VM450G12Control()
{
}

void VM450G12Control::geterror(double& thetadd, double& thetavv, double& dd, double& vv) //geterror(const double& x, const double& y, ...)
{
	thetad = thetadd;
	thetav = thetavv;
	d      = dd;
    v      = vv;
}

void VM450G12Control::setk(const string& whichk, const double& num)
{
	if (whichk == "rt")  //1
	{
		R_t = num;
	}
	else if (whichk == "rr") //2
	{
		R_r = num;
	}
	else if (whichk == "v1t") //3
	{
		v1_t = num;
	}
	else if (whichk == "v2r") //4
	{
		v2_r = num;
	}
	else if (whichk == "v2t") //5
	{
		v2_t = num;
	}
	else if (whichk == "t1") //6
	{
		time1 = num;
	}
	else if (whichk == "t2") //7
	{
		time2 = num;
	}
	else if (whichk == "kr") //8
	{
		kr = num;
	}
    //
	else
	{
		//cout an error!
		cout << "command undefined!" << endl;
	}
}

void VM450G12Control::calculate()
{
	double bfr = 2.2; //CHANGE HERE !            //bfr should be some number[>.<] as the fraction of advancing speed on that of backing behind 
	double bfv = 11;  //CHANGE HERE !            //or more pricisely, the ratio of needed propulisons for back(255) and ahead at the same speed[~.~]!
	                                             //bfv should be the speed[~.~]cm/s.
	if (0)// some strange value to indicate the stop
	{
		
	}
	else if (v==0 && fabs(thetad)>M_PI/6)
	{
		if (thetad>0)
		{
			t1m1_0 = -70;
			t1m2_0 = 70;
		}
		else
		{
			t1m1_0 = 70;
			t1m2_0 = -70;
		}
		time1_0 = kr * fabs(thetad) / M_PI;
		//t2m1_0 = 0;
		//t2m2_0 = 0;
		//time2_0 = 0;
	}
	else
	{
		double R, v1, v2, t1, r1, t2, tv2, rv2;
		v1 = v * cos(thetav);
		v2 = v * sin(thetav);
		if (fabs(thetad) < 1E-2)
		{
			t1 = 255;
			t2 = 0;
		}
		else if (fabs(fabs(thetad) - M_PI) < 1E-2)
		{
			t1 = -255;
			t2 = 0;
		}
		else if (cos(thetad) > 1E-2)
		{
			R = d / 2 / fabs(sin(thetad));
			//double bfr = 2.2; //CHANGE HERE !            //bfr should be some number[>.<] as the fraction of advancing speed on that of backing behind 
			t1 = R_t / 10 * 255 / bfr * (1 - pow(R / 100 + 1, -1));
			//double bfv = 11;  //CHANGE HERE !            //or more pricisely, the ratio of needed propulisons for back(255) and ahead at the same speed[~.~]!
														   //bfv should be the speed[~.~]cm/s.
			if (v1 > bfr * t1 / 255 * bfv)
			{
				t2 = -bfr * (v1 - bfr * t1 / 255 * bfv)*v1_t / 10;
				//bfr should be the number[>.<]
				if (fabs(t2) > 255)
				{
					t2 = t2 * 255 / fabs(t2);
				}
			}
			else
			{
				t2 = -(v1 - bfr * t1 / 255 * bfv)*v1_t / 10;
				//bfr should be the number[>.<]
				if (fabs(t2) > 255)
				{
					t2 = t2 * 255 / fabs(t2);
				}
			}
		}
		else
		{
			R = d / 2 / fabs(sin(thetad));
			//double bfr = 2.2; //CHANGE HERE !          //bfr should be the number[>.<]
			t1 = R_t / 10 * 255 * (1 - pow(R / 100 + 1, -1));
			//double bfv = 11;  //CHANGE HERE !    
			if (v1 > t1 / 255 * bfv)                    //bfv should be the speed[~.~]cm/s.
			{
				t2 = -bfr * (v1 - t1 / 255 * bfv)*v1_t / 10;
				//bfr should be the number[>.<]
//check max
				if (fabs(t2) > 255)
				{
					t2 = t2 * 255 / fabs(t2);
				}
			}
			else
			{
				t2 = -(v1 - t1 / 255 * bfv)*v1_t / 10;
				//check max
				if (fabs(t2) > 255)
				{
					t2 = t2 * 255 / fabs(t2);
				}
			}
		}
		double cc = 2;  //CHANGE HERE!     /minimum possible radius of turn [cm]
		if ((thetad >= 0 && thetad < M_PI / 2 - 1E-2) || (thetad <= -M_PI / 2 + 1E-2 && thetad >= -M_PI))
		{
			r1 = R_r / 10 * 255 * fabs(sin(thetad)) * 2 / d * cc;//turn left
			if (fabs(r1) > 255)
			{
				r1 = r1 * 255 / fabs(r1);
			}
		}
		else
		{
			r1 = -R_r / 10 * 255 * fabs(sin(thetad)) * 2 / d * cc;//turn right
			if (fabs(r1) > 255)
			{
				r1 = r1 * 255 / fabs(r1);
			}
		}
		//when t2, r2 are got, checking whether the maximized addition larger than 255!
		//there's another interpretation that we could initially adjust the side velocity by rv2, tv2, t2 term with some impluse but vary small time
		//and then kill rv2 and tv2, but with t1 r1 and velocity adjusting of t2 for some time
		//finally kill t2, only t1 and r1 remain to work

		double sidev = 10; //CHANGE HERE!   [cm/s] maximum side velocity that you think the boat can correct without causing other huge problems~ 
		double maxd = 100; //CHANGR HERE!   [cm] the covering distance that you think is long enough to endure the path deviation by correcting the side velocity
		if (sin(thetav) >= 0 && (thetad == -M_PI / 2 || tan(thetad) >= 0))     //heading and left   !!quite short time!!
		{
			rv2 = v2_r / 10 * 255 * fabs(sin(thetad))* fabs(v2) / sidev;
			tv2 = v2_t / 10 * 255 * fabs(v2) / sidev * (1 + d / maxd);
			if (fabs(tv2) > 255)
			{
				tv2 = tv2 * 255 / fabs(tv2);
			}
		}
		else if (sin(thetav) >= 0 && (thetad == M_PI / 2 || tan(thetad) < 0)) //back and right     !!quite short time!!
		{
			rv2 = -v2_r / 10 * 255 * fabs(sin(thetad))* fabs(v2) / sidev;
			tv2 = -v2_t / 10 * 255 * fabs(v2) / sidev * (1 + d / maxd);
			if (fabs(tv2) > 255)
			{
				tv2 = tv2 * 255 / fabs(tv2);
			}
		}
		else if (sin(thetav) < 0 && (thetad == -M_PI / 2 || tan(thetad) >= 0)) //back and left      !!quite short time!!
		{
			rv2 = v2_r / 10 * 255 * fabs(sin(thetad))* fabs(v2) / sidev;
			tv2 = -v2_t / 10 * 255 * fabs(v2) / sidev * (1 + d / maxd);
			if (fabs(tv2) > 255)
			{
				tv2 = tv2 * 255 / fabs(tv2);
			}
		}
		else //(sin(thetav) < 0 && tan(thetad) < 0)   //heading and right  !!quite short time!!
		{
			rv2 = -v2_r / 10 * 255 * fabs(sin(thetad))* fabs(v2) / sidev;
			tv2 = v2_t / 10 * 255 * fabs(v2) / sidev * (1 + d / maxd);
			if (fabs(tv2) > 255)
			{
				tv2 = tv2 * 255 / fabs(tv2);
			}
		}
		cout << setiosflags(ios::left);
		if (debug)
		{
			//cout << setiosflags(ios::left);
			cout << setw(6) << "t1:  " << setw(11) << t1 << setw(6) << "r1:  " << setw(11) << r1 << setw(6) << "t2:  " << setw(11) << t2 << setw(6) << "tv2:  " << setw(11) << tv2 << setw(6) << "rv2:  " << setw(11) << rv2 << endl;

			//cout << "t1: " << t1 << endl;
			//cout << "r1: " << r1 << endl;
			//cout << "t2: " << t2 << endl;
			//cout << "tv2: " << tv2 << endl;
			//cout << "rv2: " << rv2 << endl;
		}


		//0-150 only rv2 tv2 t2
		//verify if maximum addition abs(t2+tv2)+abs(rv2) larger than 255, m1 or m2 
		//then let t2-=abs(t2+tv2)+abs(rv2)-255, and recalculate m1 m2
		//150-450 only t2 t1 r1
		//if max abs(t1+t2)+abs(r1)>255;
		//just *255/max(abs).
		//450-1000 only t1 r1
		//just *255/max(abs) if >255


		if (rv2 > 0)
		{

			if (fmax(fabs(tv2 - rv2), fabs(tv2 + rv2 / bfr)) > 255)
			{
				rv2 = rv2 * 255 / fmax(fabs(tv2 - rv2), fabs(tv2 + rv2 / bfr));
				tv2 = tv2 * 255 / fmax(fabs(tv2 - rv2), fabs(tv2 + rv2 / bfr));
			}

			double tt2 = t2;
			if (fmax(fabs(tv2 - rv2 + t2), fabs(tv2 + rv2 / bfr + t2)) > 255) //(fabs(t2 + tv2) + fabs(rv2) > 255)
			{
				tt2 = t2 / fabs(t2)*(fabs(t2) - (fmax(fabs(tv2 - rv2 + t2), fabs(tv2 + rv2 / bfr + t2)) - 255));
				//tt2 = t2 / fabs(t2)*(fabs(t2) - (fabs(t2 + tv2) + fabs(rv2) - 255));
			}

			t1m1 = tv2 - rv2 + tt2;
			t1m2 = tv2 + rv2 / bfr + tt2;

		}
		else
		{

			if (fmax(fabs(tv2 - rv2 / bfr), fabs(tv2 + rv2)) > 255)
			{
				rv2 = rv2 * 255 / fmax(fabs(tv2 - rv2 / bfr), fabs(tv2 + rv2));
				tv2 = tv2 * 255 / fmax(fabs(tv2 - rv2 / bfr), fabs(tv2 + rv2));
			}

			double tt2 = t2;
			if (fmax(fabs(tv2 - rv2 / bfr + t2), fabs(tv2 + rv2 + t2)) > 255) //(fabs(t2 + tv2) + fabs(rv2) > 255)
			{
				tt2 = t2 / fabs(t2)*(fabs(t2) - (fmax(fabs(tv2 - rv2 / bfr + t2), fabs(tv2 + rv2 + t2)) - 255));
				//tt2 = t2 / fabs(t2)*(fabs(t2) - (fabs(t2 + tv2) + fabs(rv2) - 255));
			}

			t1m1 = tv2 - rv2 / bfr + tt2;
			t1m2 = tv2 + rv2 + tt2;
		}
		/*
			if (r1 > 0)
			{

			}
			else
			{

			}
		*/
		if (r1 > 0)
		{
			if (fmax(fabs(t1 - r1), fabs(t1 + r1 / bfr)) > 255)
			{
				t1 = t1 * 255 / fmax(fabs(t1 - r1), fabs(t1 + r1 / bfr));
				r1 = r1 * 255 / fmax(fabs(t1 - r1), fabs(t1 + r1 / bfr));
			}

			if (fmax(fabs(t1 + t2 - r1), fabs(t1 + t2 + r1 / bfr)) > 255)
			{
				if (fabs(t2) > fmax(fabs(t1 - r1), fabs(t1 + r1 / bfr)))
				{
					t2 = t2 / fabs(t2)*(fabs(t2) - (fmax(fabs(t1 + t2 - r1), fabs(t1 + t2 + r1 / bfr)) - 255));
				}
				else
				{
					t1 = t1 * 255 / fmax(fabs(t1 + t2 - r1), fabs(t1 + t2 + r1 / bfr));
					r1 = r1 * 255 / fmax(fabs(t1 + t2 - r1), fabs(t1 + t2 + r1 / bfr));
					t2 = t2 * 255 / fmax(fabs(t1 + t2 - r1), fabs(t1 + t2 + r1 / bfr));
				}
			}
			t2m1 = t1 + t2 - r1;
			t2m2 = t1 + t2 + r1 / bfr;
		}
		else
		{
			if (fmax(fabs(t1 - r1 / bfr), fabs(t1 + r1)) > 255)
			{
				t1 = t1 * 255 / fmax(fabs(t1 - r1 / bfr), fabs(t1 + r1));
				r1 = r1 * 255 / fmax(fabs(t1 - r1 / bfr), fabs(t1 + r1));
			}

			if (fmax(fabs(t1 + t2 - r1 / bfr), fabs(t1 + t2 + r1)) > 255)
			{
				if (fabs(t2) > fmax(fabs(t1 - r1 / bfr), fabs(t1 + r1)))
				{
					t2 = t2 / fabs(t2)*(fabs(t2) - (fmax(fabs(t1 + t2 - r1 / bfr), fabs(t1 + t2 + r1)) - 255));
				}
				else
				{
					t1 = t1 * 255 / fmax(fabs(t1 + t2 - r1 / bfr), fabs(t1 + t2 + r1));
					r1 = r1 * 255 / fmax(fabs(t1 + t2 - r1 / bfr), fabs(t1 + t2 + r1));
					t2 = t2 * 255 / fmax(fabs(t1 + t2 - r1 / bfr), fabs(t1 + t2 + r1));
				}
			}
			t2m1 = t1 + t2 - r1 / bfr;
			t2m2 = t1 + t2 + r1;
		}

	}
	//cout << setiosflags(ios::left);
	cout <<setw(7)<< "time1  " << setw(6) << time1 << setw(6) << "t1m1  " << setw(11) << t1m1 << setw(6) << "t1m2  " << setw(11) << t1m2 << setw(7) << "time2  " << setw(6) << time2 << setw(6) << "t2m1  " << setw(11) << t2m1 << setw(6) << "t2m2  " << setw(11) << t2m2 << endl;

	/*
	cout << "t1m1  " << t1m1 << endl;
	cout << "t1m2  " << t1m2 << endl;
	cout << "time2  " << time2 << endl;
	cout << "t2m1  " << t2m1 << endl;
	cout << "t2m2  " << t2m2 << endl;
	*/
}

void VM450G12Control::wifi_it()
{
	int wifi1, wifi2, wifi3, wifi4, wifi5, wifi6;
	if (0)
	{

	}
	else if (v == 0 && fabs(thetad) > M_PI / 6)
	{
		 wifi1 = round(time1_0);
		 wifi2 = round(time2_0);
		 wifi3 = round(t1m1_0);
		 wifi4 = round(t1m2_0);
		 wifi5 = round(t2m1_0);
		 wifi6 = round(t2m2_0);
	}
	else
	{
		 wifi1 = round(time1);
		 wifi2 = round(time2);
		 wifi3 = round(t1m1);
		 wifi4 = round(t1m2);
		 wifi5 = round(t2m1);
		 wifi6 = round(t2m2);
	}
	string tobetrans = "192.168.4.1/update?L1=" + to_string(wifi3) + "R1=" + to_string(wifi4) + "L2=" + to_string(wifi5) + "R2=" + to_string(wifi6) + "T1=" + to_string(wifi1) + "T2=" + to_string(wifi2);
	
	cout << tobetrans << endl;
	/*
	    CURL *curl;
        CURLcode res;

        curl_global_init(CURL_GLOBAL_DEFAULT);

        curl=curl_easy_init();

        if(curl)
        {
                curl_easy_setopt(curl, CURLOPT_URL,tobetrans.c_str());
                //curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION ,WriteDate); as long as receiving, WriteData woul be called, if default, just cout the
                //                                                          information to comman line; also the command line stdout could be replaced
                //                                                          to WRUTEDATA specification as below.
                //curl_easy_setopt(curl, CURLOPT_WRITEDATA, &ResString); you can declare the ResString [string] before and set it as where the receive
                //                                                       data should be stored, this can aslo be stored to a file id.
                res=curl_easy_perform(curl);
                if(res!=CURLE_OK)
                {
                        std::cerr<<"curl_easy_perform() failed: "<<curl_easy_strerror(res)<<std::endl;
                        curl_easy_cleanup(curl);
                }
                //else
                //{
                        //cout<<ResString<<endl;
                //}
        }
        curl_global_cleanup();


	*/

}

