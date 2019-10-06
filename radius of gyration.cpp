#include<iostream>
#include<fstream>
#include<string>
#include <sstream>
#include<cmath>
#include<stdio.h>
#include <vector>
#include <iomanip>
#include<cstdlib>
#include "nr.h"
using std::vector;
using std::pow;
using namespace std;
using std::string;
void read_positions(vector<double> & rx, vector<double> & ry,vector<double> & rz)
{
        string filename="np.xyz";
        ifstream read_input(filename.c_str());
        std::string line,word;
        while (std::getline(read_input, line))
        {
         	double x1,x2,x3;

                std::istringstream iss(line);

                if(iss>>word>>x1>>x2>>x3){

                rx.push_back(x1);

                ry.push_back(x2);

                rz.push_back(x3);}
}
     read_input.close();
}
void center_of_mass(vector<double> & rx, vector<double> & ry,vector<double> & rz, vector<double> & x, vector<double> & y, vector<double> & z)
{   double cmx,cmy,cmz,X,Z,Y ;
    double resultx = 0;
    double resulty = 0;
    double resultz = 0;
	for(int i=0; i<rx.size(); ++i)
	{
		resultx += rx[i];
		resulty += ry[i];
        resultz += rz[i];

}
cmx = resultx/(rx.size()); //x coordinate for center of mass
cmy = resulty/(rx.size()); //y coordinate for center of mass
cmz = resultz/(rx.size()); //z coordinate for center of mass
//cout<<"cm"<<cmx<<", "<<cmy<<", "<<cmz<<'\n' ;
for(int i=0; i<rx.size(); ++i){
                X = rx[i] - cmx;
                Y = ry[i] - cmy;
                Z = rz[i] - cmz;
		x.push_back(X);
		y.push_back(Y);
		z.push_back(Z);
cout << "X1 ="<<x[i]<<", "<<y[i]<<", "<<z[i]<<'\n'; //the computed r vector minus CM
}
}
double radius_of_gyration(vector<double> & x, vector<double> & y, vector<double> & z)
{
	double xx=0.0,xy=0.0,xz=0.0,yx=0.0,yy=0.0,yz=0.0,zx=0.0,zy=0.0,zz=0.0;
	for ( int q=0; q<x.size(); ++q)
	{
		xx += x[q]*x[q];
		yy += y[q]*y[q];
		zz += z[q]*z[q];
		xy += x[q]*y[q];
		xz += x[q]*z[q];
		yx += y[q]*x[q];
		yz += y[q]*z[q];
		zx += z[q]*x[q];
		zy += y[q]*z[q];
	}
	DP a_d[3*3]=      //computing the eigenvalues for gyration
          {xx,xy,xz,
          yx,yy,yz,
          zx,zy,zz};
        int i,j,k,l,kk,ll,nrot;
        Mat_DP a(a_d,3,3);

          Vec_DP d(3),r(3);
          Mat_DP v(3,3);
          NR::jacobi(a,d,v,nrot);
          cout << "eigenvalues: " << endl;
          for (j=0;j<3;j++) {
            cout << setw(12) << d[j];
            if ((j+1) % 5 == 0) cout << endl;}
cout<<""<<xx<<", "<<xy<<", "<<xz<<", "<<yx<<", "<<yy<<", "<<yz<<", "<<zx<<", "<<zy<<", "<<zz<<'\n';
return 0;
}
int main()
{
vector <double> rx, ry, rz,x,y,z;
read_positions(rx, ry, rz);
center_of_mass(rx, ry, rz,x,y,z);
radius_of_gyration(x,y,z);
//for(int i=0; i<rx.size(); ++i){
//cout << "X2 "<<x[i]<<", "<<y[i]<<", "<<z[i]<<'\n';}
return 0;
}
