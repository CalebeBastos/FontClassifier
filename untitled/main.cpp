////////////////////////////////////////////////////////////////////
//          Constants for Backprop Font Data                      //
////////////////////////////////////////////////////////////////////

#define  FV_IN       "norm.sep"
#define  NORMALIZE    false
#define  FONT_DATA    true

#define  ALPHA         0.0     // momentum factor
#define  ETA           0.1     // learning rate
#define  MAXIN         14      // number of input nodes
#define  MAXH          20      // number of nodes hidden layer
#define  MAXOUT        26      // number of nodes output layer
#define  N_ITERATIONS  10       // times to train the network
#define  NUMFV         78      // number of feature vectors total
#define  NUMUV         78      // number of test vectors
#define  LOG_MOD       10      // print results every LOG_MOD iterations

#define  RESULTS_OUT_NAME   "bp.out"
#define  WEIGHTS_IN         "bpw.in"
#define  WEIGHTS_OUT        "bpw.out"
#define  WEIGHT_FILE_NAME   "genw.txt"  // for genweights

#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>

//void GenerateWeights();

using namespace std;

//const double MAX = double(RAND_MAX);

struct myFeatures
{
    int alphabet;
    int font;
    double feature[14];  // hardcoded 14. need to change it later sometime
};

int _NUMDATA_ = 0;  // total number of data sets in the input file

int main()
{
    /*
    vector<myFeatures> myData;
    myFeatures myFeature;
    // create an ifstream object to read in from the file
    ifstream fin("norm.txt");

    int num1 = 0;
    double num2 = 0.0;
    int count = 0;
    while(fin)
    {
        count = 0;
        while(count < 16) // hardcoded 16. need to change it later sometime
        {
            if(count == 0)
            {
                fin >> num1;
                myFeature.alphabet = num1;
            }
            else if(count == 1)
            {
                fin >> num1;
                myFeature.font = num1;
            }
            else
            {
                fin >> num2;
                myFeature.feature[count-2] = num2;
            }
            count++;
        }
        myData.push_back(myFeature);
        _NUMDATA_++;
        if(fin >> num1 == NULL) break;
    }
    fin.close();*/
    /****************************************************** done reading the features from the file upto here *****************************************************/

    //random_shuffle(myData.begin(), myData.end()); // randomly shuffle elements of the vector myData

    //GenerateWeights();
    cout << "Hello";

    return 0;
}

/**
* Generates random weights and writes them onto a file
*/
/*
void GenerateWeights()
{
    float double_off;
    int i;
    int j;
    float offset;
    ofstream outfile;
    float x;

    offset = 0.1;
    double_off = offset * 2.0;

    outfile.open(WEIGHT_FILE_NAME);
    srand(time(NULL));
    outfile.setf(ios::fixed);

    for(i = 0; i < MAXH; i++)
    {
        for(j = 0; j < MAXIN + 1; j++)
        {
            x = (rand() / MAX) * double_off - offset;
            outfile << setprecision(6);
            outfile << setw(10) << x;
            if ((j+1) % 7 == 0)
                outfile << endl;
        }
        outfile << endl;
    }
    outfile << endl;

    for(i = 0; i < MAXOUT; i++)
    {
        for(j = 0; j < MAXH + 1; j++)
        {
            x = (rand() / MAX) * double_off - offset;
            outfile << setprecision(6);
            outfile << setw(10) << x;
            if ((j + 1) % 7 == 0)
                outfile << endl;
        }
        outfile << endl;
    }
    outfile.close();
}

*/














