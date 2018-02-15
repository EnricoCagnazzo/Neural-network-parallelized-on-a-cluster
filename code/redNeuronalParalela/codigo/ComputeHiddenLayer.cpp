#include <iostream>
#include <fstream>
#include <string.h>

#define nInput 6
#define nHidden 6
using namespace std;

double inputLayer[nInput],hiddenLayer[nHidden]={};
double weights[nInput][nHidden];

double ReLUFunction(double x){
    return x>0?x:0;
}

int main(int argc, char **argv)
{
    ifstream input(argv[1]);
    ifstream weigthsFile("/mnt/raid/redNeuronalParalela/weights/weightsInHidd");
    for (int i=0;i<nInput;i++)
        input>>inputLayer[i];
    input.close();

    for (int i=0;i<nInput;i++)
        for (int j=0;j<nHidden;j++)
            weigthsFile>>weights[i][j];
    weigthsFile.close();

    for (int i=0;i<nInput;i++)
        for (int j=0;j<nHidden;j++)
            hiddenLayer[j]+=inputLayer[i]*weights[i][j];

    FILE *hidden;
    char hiddenFile[80];
    strcpy (hiddenFile,argv[1]);
    strcat (hiddenFile,"H");
    hidden=fopen(hiddenFile,"w");
    for (int i=0;i<nHidden;i++)
        fprintf(hidden,"%E \n",ReLUFunction(hiddenLayer[i]));
    fclose(hidden);
    return 0;
}
