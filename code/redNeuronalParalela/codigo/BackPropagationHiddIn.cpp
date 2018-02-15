#include <cstring>
#include <cstdlib>
#include <iostream>
#include <fstream>

#define nInput 6
#define nHidden 6
#define nOutput 4
#define weightsInHiddFilePos "/mnt/raid/redNeuronalParalela/weights/weightsInHidd"
#define weightsHiddOutFilePos "/mnt/raid/redNeuronalParalela/weights/weights/weightsHiddOut"
#define deltaOutputFilePos "/mnt/raid/redNeuronalParalela/weights/deltaOutput"

#define ro 0.5

using namespace std;

double inputLayer[nInput], hiddenLayer[nHidden];
double weightsInHidd[nInput][nHidden];
double weightsHiddOut[nHidden][nOutput];
double deltaHidden[nHidden],deltaOutput[nOutput];

char* getInputPath(char outputName[]){
    char* inputName;
    int i=0;
    for (;outputName[i]!='\0';i++);
    inputName=(char*)malloc(i);
    memcpy(inputName,outputName,i);
    inputName[i-2]='\0';
    return inputName;
}

char* getHiddenPath(char outputName[]){
    char* hiddenName;
    int i=0;
    for (;outputName[i]!='\0';i++);
    hiddenName=(char*)malloc(i);
    memcpy(hiddenName,outputName,i);
    hiddenName[i-1]='\0';
    return hiddenName;
}

char* getIdentifier(char outputName[]){
    char* identifier;
    int i=0;
    for (;outputName[i]<'0' || outputName[i]>'9';i++);
    identifier=(char *)malloc(10);
    memcpy(identifier,outputName+i,10);
    return identifier;
}

int main(int argc, char **argv)
{
    char deltaFullFileName[100];
    strcpy(deltaFullFileName, deltaOutputFilePos);
    strcat(deltaFullFileName, getIdentifier(argv[1]));

    ifstream deltaOutputFile(deltaFullFileName);
    for (int i=0;i<nOutput;i++)
        deltaOutputFile>>deltaOutput[i];
    deltaOutputFile.close();

    ifstream weightsHiddOutFile(weightsHiddOutFilePos);
    for (int i=0;i<nHidden;i++)
        for (int j=0;j<nOutput;j++)
            weightsHiddOutFile>>weightsHiddOut[i][j];
    weightsHiddOutFile.close();

    ifstream weightsInHiddFile(weightsInHiddFilePos);
    for (int i=0;i<nInput;i++)
        for (int j=0;j<nHidden;j++)
            weightsInHiddFile>>weightsInHidd[i][j];
    weightsInHiddFile.close();

    ifstream inputLayerFile(getInputPath(argv[1]));
    for (int i=0;i<nInput;i++)
        inputLayerFile>>inputLayer[i];
    inputLayerFile.close();

    ifstream hiddenLayerFile(getHiddenPath(argv[1]));
    for (int i=0;i<nHidden;i++)
        hiddenLayerFile>>hiddenLayer[i];
    hiddenLayerFile.close();


    //diff W(i,j)=ro*deltaH(j)*xI(i)
    //deltaH(j)=f's(yJ)*sum(c=1...nOutput)wJC*deltaO(c) where:
    //  f's is the derivate of the activation function of the hidden layer
    //  yJ is the value inside the hidden neuron before the activation function
    //  wJC is the weight Hidden(j)->Output(c)
    //  deltaO(c) is the value (already calculated) in the backprepagation output->hidden
    //  xI(i) is the value inside the input neuron (no activation functions are applied on it)

    //For the activation function ReLU: f'(x)=1 if  f(x)>0; 0 otherwise


    for (int i=0;i<nHidden;i++){
        deltaHidden[i]=0;
        if (hiddenLayer[i]==0)
            continue;
        for (int j=0;j<nOutput;j++)
            deltaHidden[i]+=weightsHiddOut[i][j]*deltaOutput[j];
    }

    for (int i=0;i<nInput;i++){
        for (int j=0;j<nHidden;j++)
            weightsInHidd[i][j]+=ro*deltaHidden[j]*inputLayer[i];
    }

    ofstream newWeightsFile(weightsInHiddFilePos);
    for (int i=0;i<nInput;i++)
        for (int j=0;j<nHidden;j++){
            newWeightsFile<<weightsInHidd[i][j];
            newWeightsFile.flush();
        }
    newWeightsFile.close();

    return 0;
}
