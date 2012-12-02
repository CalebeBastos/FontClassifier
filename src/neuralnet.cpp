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
#include <cmath>
#include "datatypes.h"
#include "perceptron.h"

void GenerateWeights();
void readWeights(double w[][MAXIN+1], double v[][MAXH+1]);
double derivative(double );

using namespace std;

const double MAX = double(RAND_MAX);

int _NUMDATA_;

int main()
{
    vector<myFeatures> myData;
    myFeatures myFeature;
    // create an ifstream object to read in from the file
    ifstream fin("norm.txt");   //hardcoded norm.txt. need to chage it sometime later
    ofstream fout(WEIGHTS_OUT);
    ofstream fout1(RESULTS_OUT_NAME);
    if (!fin)
    {
        cout << "the file could not be opened";
        return 0;
    }

    int num0 = 0;
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
                fin >> num0;
                myFeature.alphabet = num0;
                count++;
            }
            else if(count == 1)
            {
                fin >> num1;
                myFeature.font = num1;
                count++;
            }
            else
            {
                fin >> num2;
                myFeature.feature[count-2] = num2;
                count++;
            }

        //count++;
        }
        myData.push_back(myFeature);
        _NUMDATA_++;
        //if(fin >> num1 == NULL) break;    blunder!!
        if(_NUMDATA_ == 156)
        	break;
    }
    fin.close();

    /****************************************************** done reading the features from the file upto here *****************************************************/

    //GenerateWeights();   // Uncomment this if you want to try out with a different set of weights

    perceptron* ipLayer = new perceptron[MAXIN+1];
    perceptron* hLayer = new perceptron[MAXH+1];
    perceptron* opLayer = new perceptron[MAXOUT];

    for (int i = 0; i < MAXIN+1; i++)
    {
    	// the 0th position is the bias term
    	ipLayer[i].setLayer(1);
    	ipLayer[i].setPosPerceptron(i);
    }
    for (int i = 0; i < MAXH+1; i++)
    {
    	// the 0th position is the bias term
    	hLayer[i].setLayer(2);
    	hLayer[i].setPosPerceptron(i);
    }
    for (int i = 0; i < MAXOUT; i++)
    {
    	opLayer[i].setLayer(3);
    	hLayer[i].setPosPerceptron(i);
    }

    int itIndex = 0;		// iterator for the number of iterations
    int fVectorIndex = 0;	// iterator for the feature vectors
    int ipLayerIndex = 0;	// iterator for the input layer perceptrons
    int hLayerIndex = 0;	// iterator for the hidden layer perceptrons
    int opLayerIndex = 0;	// iterator for the output layer perceptrons
    int i = 0, j = 0, k = 0, p = 0;

    double max = 0.0;
    int maxIndex = 0;
    int totalCorrect = 0;

    double ipLayerInput[MAXIN+1] = {0}; // input to input layer
    double ipLayerOutput[MAXIN+1] = {0}; // output of the input layer
    double hLayerInput[MAXH+1] = {0};	// input to hidden layer
    double hLayerOutput[MAXH+1] = {0};	// output of hidden layer
    double opLayerInput[MAXOUT] ={0};	// input to the output layer
    double opLayerOutput[MAXOUT] = {0};	// output from the hidden layer

    double desired[MAXOUT] = {0};

    double v[MAXOUT][MAXH+1] = {{0}};
    double w[MAXH][MAXIN+1] = {{0}};
    readWeights(w, v);
    double del = 0;  // blunder
    for(itIndex = 0; itIndex < N_ITERATIONS; itIndex++)   //open this loop only when you are sure that the inside stuffs is working
    {
    	totalCorrect = 0;
    		for(fVectorIndex = 0; fVectorIndex < NUMFV; fVectorIndex++) //open this loop only when you are sure that the inside stuffs is working fine
    		{
    			// finding out the desired output vector depending upon the alphabet
    			for(opLayerIndex = 0; opLayerIndex < MAXOUT; opLayerIndex++)
    			{
    				if(myData[fVectorIndex].alphabet == opLayerIndex)
    				{
    					desired[opLayerIndex] = 1;
    				}
    				else
    				{
    					desired[opLayerIndex] = 0;
    				}
    			}

    			/********************************************************* starting forward propagation ***********************************************/
    			// looping through each input perceptron and setting their input as well as calculating their output
    			for(ipLayerIndex = 0; ipLayerIndex <= MAXIN; ipLayerIndex++)
    			{
    				if(ipLayerIndex == 0)
    				{
    					ipLayer[ipLayerIndex].setInput(-1.0);
    				}
    				else
    				{
    					ipLayer[ipLayerIndex].setInput(myData[fVectorIndex].feature[ipLayerIndex - 1]);
    				}
    				ipLayer[ipLayerIndex].setOutput();
    				ipLayerOutput[ipLayerIndex] = ipLayer[ipLayerIndex].getOutput();
    				//cout << ipLayerOutput[ipLayerIndex] << "  ";
    			}
    			//cout << endl;

    			// looping through each hidden perceptron and setting their input as well as calculating their output
    			for(hLayerIndex = 0; hLayerIndex <= MAXH; hLayerIndex++)
    			{
    				if(hLayerIndex == 0)
    				{
    					hLayer[hLayerIndex].setInput(-1.0);
    				}
    				else
    				{
    					hLayer[hLayerIndex].setInput(ipLayerOutput, w[hLayerIndex-1]);
    				}
    				//cout << hLayer[hLayerIndex].getInput() << "  ";
    				hLayer[hLayerIndex].setOutput();
    				hLayerOutput[hLayerIndex] = hLayer[hLayerIndex].getOutput();
    				//cout << hLayerOutput[hLayerIndex] << "  " ;
    			}
    			//cout << endl;

    			for(opLayerIndex = 0; opLayerIndex < MAXOUT; opLayerIndex++)
    			{
    				opLayer[opLayerIndex].setInput(hLayerOutput, v[opLayerIndex]);
    				opLayer[opLayerIndex].setOutput();
    				opLayerOutput[opLayerIndex] = opLayer[opLayerIndex].getOutput();
    				if(fVectorIndex == 0)
    				{
    					cout << opLayerOutput[opLayerIndex] << "  ";
    				}

    			}
    			if(fVectorIndex == 0)
    			{
    				cout << endl;
    			}

    			/******************************************************************** starting backpropagation ***********************************************************/
    			for(j = 0; j < MAXH; j++)
    			{
    				for(k = 0; k <= MAXIN; k++)
    				{
    					del = 0.0;
    					for(p = 0; p < MAXOUT; p++)
    					{
    						del = del + (desired[p] - opLayerOutput[p]) * derivative(opLayer[p].getInput()) * v[p][j];
    					}
    					w[j][k] = w[j][k] + ETA * derivative(hLayer[j].getInput())* ipLayer[k].getInput() * del;
    				}
    			}

    			for(k = 0; k < MAXOUT; k++)
    			{
    				for(j = 0; j <= MAXH; j++)
    				{
    					v[k][j] = v[k][j] + ETA * (desired[k] - opLayerOutput[k]) * derivative(opLayer[k].getInput()) * hLayer[j].getOutput();
    				}
    			}

    			/*
    			max = -100.0;
    			maxIndex = 0;
    			for (opLayerIndex = 0; opLayerIndex < MAXOUT; opLayerIndex++)
    			{
    				if(opLayerOutput[opLayerIndex] > max)
    				{
    					max = opLayerOutput[opLayerIndex];
    					maxIndex = opLayerIndex;
    				}
    			}

    			if(maxIndex == myData[fVectorIndex].alphabet)
    			{
    				totalCorrect++;
    			}*/


    		} // end of an epoch

    		//cout << "total vectors correctly classified in iteration " << itIndex << ": " << totalCorrect << endl;

    }   //end of the total iterations(all epochs)


    return 0;
}

/**
* Generates random weights and writes them onto a file
*/
void GenerateWeights()
{
    double double_off;
    int i;
    int j;
    double offset;
    ofstream outfile;
    double x;

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

void readWeights(double w[][MAXIN+1], double v[][MAXH+1])
{
	//double w[MAXH][MAXIN] = {0.00};
	//double v[MAXOUT][MAXH] = {0.00};
	ifstream infile(WEIGHT_FILE_NAME);
	if(!infile)
	{
		cout << "cannot open the file!";
		exit(0);
	}

	for (int i = 0; i < MAXH; i++)
		for (int j = 0; j <= MAXIN; j++)
			infile >> w[i][j]; // input to hidden

	for (int i = 0; i < MAXOUT; i++)
		for (int j = 0; j <= MAXH; j++ )
			infile >> v[i][j]; // hidden to output
}

double derivative(double ip)
{
	double output;   //blunder
	double var;
	var = 1 + exp(-ip);
	output = (exp(-ip))/(var*var);
	return output;
}
