//============================================================================
// Name        : neuralnet.cpp
// Author      : prashanta
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include "datatypes.h"

void GenerateWeights();

using namespace std;

const double MAX = double(RAND_MAX);

int _NUMDATA_;

int main()
{
    vector<myFeatures> myData;
    myFeatures myFeature;
    // create an ifstream object to read in from the file
    ifstream fin("norm.txt");
    if (!fin)
    {
        cout << "the file could not be opened";
        return 0;
    }

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
    fin.close();
    /****************************************************** done reading the features from the file upto here *****************************************************/

    random_shuffle(myData.begin(), myData.end()); // randomly shuffle elements of the vector myData

    GenerateWeights();


    return 0;
}

/**
* Generates random weights and writes them onto a file
*/

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
