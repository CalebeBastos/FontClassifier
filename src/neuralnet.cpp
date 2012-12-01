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

    /**************************************************** trying to train the net from here onwards ***************************************************************/
    //double inW[MAXIN+1] = {1}; // weight matrix for the input layer
    double inLayerOut[MAXIN + 1] = {0}; // output of the input layer
    double w[MAXH][MAXIN+1] = {{0}}; // weight from hidden to input layer
    double hLayerOut[MAXH + 1] = {0}; // output of the hidden layer
    double v[MAXOUT][MAXH+1] = {{0}}; // weight from output to hidden layer
    double opLayerOut[MAXOUT] = {0}; // output from the ouput layer
    double desired[MAXOUT] = {0}; // desired output vector of the net, every other element is 0 except one of them. if A 0th element is 1, if B 1st element is 1 and so on.
    // read in the weights from the initial weight file(i.e the randomly generated weights using GenerateWeights function)
    readWeights(w, v);
    //cout << w[0][0] << " " << w[0][1] << " " << w[0][2] << endl;
    //cout << v[0][0] << " " << v[0][1] << " " << v[0][2] << endl;

    for(int n = 0; n < N_ITERATIONS; n++)
    {
    	//random_shuffle(myData.begin(), myData.end()); // randomly shuffle elements of the vector myData

		// looping through each of the input vectors (one epoch)
		int i = 0;
		double mse = 0;
		int numCorrect = 0;
		for(i = 0; i < NUMFV; i++)
		{
			// filling out the output vector i.e. the desired output for that particular input vector
			for (int j = 0; j < MAXOUT; j++)
			{
				if(j == myData[i].alphabet)
				{
					desired[j] = 1;
				}
				else
				{
					desired[j] = 0;
				}
			}

			/***************************************************** starting forward propagation ****************************************************/
			// looping through all the input nodes
			for(int j = 0; j < MAXIN+1; j++)
			{
				if (j == 0)
				{
					ipLayer[j].setInput(-1);
				}
				else
				{
					ipLayer[j].setInput(myData[i].feature[j-1]);  // replace 0 by i once the outer loop is opened
				}
				ipLayer[j].setOutput();
				inLayerOut[j] = ipLayer[j].getOutput();
				//cout << inLayerOut[j] << "  ";
			}

			//looping through all the hidden nodes
			for(int j = 0; j < MAXH+1; j++)
			{
				if (j == 0)
					hLayer[j].setInput(-1);
				else
					hLayer[j].setInput(inLayerOut, w[j-1]);
				//cout << hLayer[j].getInput() << "  ";
				hLayer[j].setOutput();
				hLayerOut[j] = hLayer[j].getOutput();
				//cout << hLayerOut[j] << "  ";
			}


			// looping through all the output nodes
			for(int j = 0; j < MAXOUT; j++)
			{
				opLayer[j].setInput(hLayerOut, v[j]);
				//cout << opLayer[j].getInput() << "  ";
				opLayer[j].setOutput();
				opLayerOut[j] = opLayer[j].getOutput();
				//cout << opLayerOut[j] << "  ";
			}
			//cout << endl;
			/******************************************************** starting backward propagation **********************************************/

			// correcting the weights from input nodes to output nodes
			for(int j = 0; j < MAXH+1; j++)
			{
				for(int k = 0; k < MAXIN+1; k++ )
				{
					double del = 0.0;
					for(int p = 0; p < MAXOUT; p++)
					{
						del = del +  (desired[p] - opLayerOut[p]) * derivative(opLayer[p].getInput()) * v[p][j];
					}
					w[j][k] = w[j][k] + ETA * derivative(hLayer[j].getInput()) * ipLayer[k].getInput() *  del;
					//fout << w[k][j];
				}
				//fout << "\n";
			}


			// correcting the weights from hidden nodes to output nodes
			for(int k = 0; k < MAXOUT; k++)
			{
				for(int j = 0; j < MAXH+1; j++)
				{
					v[k][j] = v[k][j] + ETA * (desired[k] - opLayerOut[k]) * derivative(opLayer[k].getInput()) * hLayer[j].getOutput();
					//fout << v[k][j];
				}
				//fout << "\n";
			}

			int max = -100;
			int index = 0;
			for (int j = 0; j < MAXOUT; j++)
			{
				if (opLayerOut[j] > max)
				{
					index = j;
				}
			}

			if(index == myData[i].alphabet)
			{
				numCorrect++;
			}

			for (int j = 0; j < MAXOUT; j++)
			{
				mse += (desired[j] - opLayerOut[j]) * (desired[j] - opLayerOut[j]);
			}

		} // end of each epoch


		// displaying mean squared error after each epoch to see if the net is training itself or not
		cout << "mse" << n << ": " << mse << "  ";
		cout << "total correctly identified" << numCorrect << endl;

		// write the weights at the end of each epoch to a file
		for (int k = 0; k < MAXOUT; k++)
		{
			for (int j = 0; j < MAXH+1; j++)
			{
				fout << v[k][j];
			}
			fout << "\n";
		}

		for (int j = 0; j < MAXH+1; j++)
		{
			for (int k = 0; k < MAXIN+1; k++)
			{
				fout << w[k][j];
			}
			fout << "\n";
		}

    } // end of all epochs

    /********************************************************************* trying to test the net from here onwards *********************************************************/
    /*int i = 0;
    for (i = 0; i < NUMFV; i++) // testing for the training data; once you are sure the net is working fine test for testing data
    {
		// looping through all the input nodes
		for(int j = 0; j < MAXIN+1; j++)
		{
			if (j == 0)
				ipLayer[j].setInput(-1);
			else
				ipLayer[j].setInput(myData[i].feature[j-1]);  // replace 0 by i once the outer loop is opened
			ipLayer[j].setOutput();
			inLayerOut[j] = ipLayer[j].getOutput();
		}

		// looping through all the hidden nodes
		for(int j = 0; j < MAXH+1; j++)
		{
			if (j == 0)
				hLayer[j].setInput(-1);
			else
				hLayer[j].setInput(inLayerOut, w[j-1]);
				hLayer[j].setOutput();
				hLayerOut[j] = hLayer[j].getOutput();
		}

		// looping through all the output nodes
		for(int j = 0; j < MAXOUT; j++)
		{
			opLayer[j].setInput(hLayerOut, v[j]);
			opLayer[j].setOutput();
			opLayerOut[j] = opLayer[j].getOutput();
		}

		cout << "displaying the output vector " << endl;
		for (int j = 0; j < MAXOUT; j++)
		{
		  	cout << opLayerOut[j];
		}
		cout << endl;
    }*/


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

void readWeights(double w[][MAXIN+1], double v[][MAXH+1])
{
	//double w[MAXH][MAXIN] = {0.00};
	//double v[MAXOUT][MAXH] = {0.00};
	ifstream infile(WEIGHT_FILE_NAME);

	for (int i = 0; i < MAXH; i++)
		for (int j = 0; j <= MAXIN; j++)
			infile >> w[i][j]; // input to hidden

	for (int i = 0; i < MAXOUT; i++)
		for (int j = 0; j <= MAXH; j++ )
			infile >> v[i][j]; // hidden to output
}

double derivative(double ip)
{
	double output;
	double var;
	//output = (exp(-ip))/pow((1+exp(-ip)),2);
	var = 1 + exp(-ip);

	output = (exp(-ip))/(var*var);
	return output;
}
