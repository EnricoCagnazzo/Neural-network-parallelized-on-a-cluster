#include <iostream>
#include <fstream>
#include <random>

using namespace std;

double centerX[]={3, 3,0,1};
double centerY[]={3,-1,3,1.5};

double devX[]={0.5,0.5,1  ,0.5};
double devY[]={1  ,0.5,0.5,0.5};

int main()
{
    default_random_engine generator;
    normal_distribution<double> distribution0x(centerX[0],devX[0]);
    normal_distribution<double> distribution0y(centerY[0],devY[0]);
    normal_distribution<double> distribution1x(centerX[1],devX[1]);
    normal_distribution<double> distribution1y(centerY[1],devY[1]);
    normal_distribution<double> distribution2x(centerX[2],devX[2]);
    normal_distribution<double> distribution2y(centerY[2],devY[2]);
    normal_distribution<double> distribution3x(centerX[3],devX[3]);
    normal_distribution<double> distribution3y(centerY[3],devY[3]);

    int nSampleForClass=1000;
    for (int i=0;i<nSampleForClass;i++){
        char intStr[3];
        sprintf(intStr,"%d",i);
        string fileName = string(intStr);
	fileName="/mnt/raid/redNeuronalParalela/dataset/"+fileName;
        string fileName0= fileName+"_0";
        ofstream out0(fileName0);
        double x0=distribution0x(generator),y0=distribution0y(generator);
        out0<<x0<<endl<<y0<<endl<<0<<endl;
        out0.close();
        string fileName1= fileName+"_1";
        ofstream out1(fileName1);
        double x1=distribution1x(generator),y1=distribution1y(generator);
        out1<<x1<<endl<<y1<<endl<<1<<endl;
        out1.close();
        string fileName2= fileName+"_2";
        ofstream out2(fileName2);
        double x2=distribution2x(generator),y2=distribution2y(generator);
        out2<<x2<<endl<<y2<<endl<<2<<endl;
        out2.close();
        string fileName3= fileName+"_3";
        ofstream out3(fileName3);
        double x3=distribution3x(generator),y3=distribution3y(generator);
        out3<<x3<<endl<<y3<<endl<<3<<endl;
        out3.close();
    }
    return 0;
}
