#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char **argv)
{
    ifstream in(argv[1]);
    double x,y;
    in>>x>>y;
    string fileName = string(argv[1])+"D";
    ofstream out(fileName);
    out<<x<<endl<<y<<endl;
    out<<x*y<<endl;
    out<<x+y<<endl;
    out<<x*x<<endl;
    out<<y*y<<endl;
    out.close();
    return 0;
}
