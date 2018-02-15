#include <iostream>
#include <fstream>
#include <random>

#define nHidden 6
#define nOutput 4

using namespace std;

int main()
{
    double extreme=1/sqrt(nHidden);
    default_random_engine generator;
    uniform_real_distribution<double> distribution(0,extreme);
    ofstream weights ("/mnt/raid/redNeuronalSequencial/weights/weightsHiddOut");
    double w;
    for (int i=0;i<nHidden;i++){
        for (int j=0;j<nOutput;j++){
            w=distribution(generator);
            weights<<w<<endl;
        }
    }
    weights.close();
    return 0;
}
