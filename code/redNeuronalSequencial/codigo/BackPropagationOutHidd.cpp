#include <cstring>
#include <cstdlib>
#include <iostream>
#include <fstream>

#define nHidden 6
#define nOutput 4
#define weightsFilePos "/mnt/raid/redNeuronalSequencial/weights/weightsHiddOut"
#define deltaFilePos "/mnt/raid/redNeuronalSequencial/weights/deltaOutput"

#define ro 0.5

using namespace std;

double expectedOutput[nOutput],outputLayer[nOutput],outputLayerBeforeActivation[nOutput];
double hiddenLayer[nHidden];
double weights[nHidden][nOutput];

void calculateExpectedOutput(char fileName[]){
    int i=0;
    for (;fileName[i]!='_';i++);
    int correctedClass=fileName[i+1]-'0';
    for (i=0;i<nOutput;i++)
        expectedOutput[i]=correctedClass==i;
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
    char *identifier;
    int i=0;
    identifier=(char *)malloc(10);
    for (;outputName[i]<'0' || outputName[i]>'9';i++);
    memcpy (identifier, outputName+i, 9);
    return identifier;
}

int main(int argc, char **argv)
{
    ifstream hidden(getHiddenPath(argv[1]));
    for (int i=0;i<nHidden;i++)
        hidden>>hiddenLayer[i];
    hidden.close();

    ifstream output(argv[1]);
    for (int i=0;i<nOutput;i++)
        output>>outputLayer[i];
    output.close();

    calculateExpectedOutput(argv[1]);

    ifstream weigthsFile(weightsFilePos);
    for (int i=0;i<nHidden;i++)
        for (int j=0;j<nOutput;j++)
            weigthsFile>>weights[i][j];
    weigthsFile.close();

    //diff W(i,j)=ro*deltaO(i)*sH(j)
    //deltaO(i)=[T(i)/sO(i)]*f's(zO(i)) where:
    //  T(i) is the target
    //  sO(i) is the value inside the output neuron after the activation function
    //  f's is the derivate of the activation function of the output layer
    //  zO(i) is the value inside the output neuron before the activation function

    //  For the softmax activation function: f'(x)=f(x)(1-f(x))

    double deltaO[nOutput];

    for (int i=0;i<nOutput;i++){
        deltaO[i]=expectedOutput[i]/outputLayer[i];
        deltaO[i]*=outputLayer[i]*(1-outputLayer[i]);
        double diff;
        for (int j=0;j<nHidden;j++){
            diff=ro*deltaO[i]*hiddenLayer[j];
            weights[i][j]+=diff;
        }
    }

    ofstream newWeightsFile(weightsFilePos);
    for (int i=0;i<nHidden;i++)
        for (int j=0;j<nOutput;j++){
            newWeightsFile<<weights[i][j]<<endl;
            newWeightsFile.flush();
        }
    newWeightsFile.close();

    char deltaFileFullName[100];
    strcpy (deltaFileFullName, deltaFilePos);
    strcat (deltaFileFullName, getIdentifier(argv[1]));

    ofstream deltaFile(deltaFileFullName);
    for (int i=0;i<nOutput;i++)
        deltaFile<<deltaO[i]<<endl;
    deltaFile.close();

    return 0;
}
