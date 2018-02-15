#include <iostream>
#include <fstream>
#include <random>

#define nInput 6
#define nHidden 6

using namespace std;

int main()
{
    double extreme=1/sqrt(nInput);
    default_random_engine generator;
    uniform_real_distribution<double> distribution(0,extreme);
    ofstream weights ("/mnt/raid/redNeuronalParalela/weights/weightsInHidd");
    double w;
    for (int i=0;i<nInput;i++){
        for (int j=0;j<nHidden;j++){
            w=distribution(generator);
            weights<<w<<endl;
        }
    }
    weights.close();
    return 0;
}
