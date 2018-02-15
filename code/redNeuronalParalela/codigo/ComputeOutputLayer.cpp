#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>

#define nHidden 6
#define nOutput 4

using namespace std;

double hiddenLayer[nHidden],outputLayer[nOutput]={};
double weights[nHidden][nOutput];

double softMax(double x, double s){
    if (s==0) return 1.0/nOutput;
    return exp(x)/s;
}

bool toNormalize(){
    for (int i=0;i<nOutput;i++)
	if (outputLayer[i]>100.0){
//	    cout<<outputLayer[i]<<endl;
	    return true;
	}
    return false;
}

void normalize(){
    while (toNormalize()) {
	for (int i=0;i<nOutput;i++)
	    outputLayer[i]/=10;
//	cout<<outputLayer[0]<<'\t'<<outputLayer[1]<<'\t'<<outputLayer[2]<<'\t'<<outputLayer[3]<<endl;
    }
}

int main(int argc, char **argv)
{
    ifstream hidden(argv[1]);
    ifstream weigthsFile("/mnt/raid/redNeuronalParalela/weights/weightsHiddOut");
    for (int i=0;i<nHidden;i++)
        hidden>>hiddenLayer[i];
    hidden.close();

    for (int i=0;i<nHidden;i++)
        for (int j=0;j<nOutput;j++){
            weigthsFile>>weights[i][j];
//	    cout<<weights[i][j]<<'\t';
	}
    weigthsFile.close();

    for (int i=0;i<nHidden;i++)
        for (int j=0;j<nOutput;j++)
            outputLayer[j]+=hiddenLayer[i]*weights[i][j];

    normalize();

    double sum=0;
    for (int i=0;i<nOutput;i++)
        sum+=exp(outputLayer[i]);

    FILE *output;
    char outputName[80];
    strcpy (outputName,argv[1]);
    strcat (outputName,"O");
    output=fopen(outputName,"w");
    for (int i=0;i<nOutput;i++){
	double result=softMax(outputLayer[i],sum);
        fprintf(output,"%E \n",result);
//	cout<<outputLayer[i]<<'\t'<<result<<endl;
    }
    fclose(output);

    return 0;
}
