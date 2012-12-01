/*
 * perceptron.cpp
 *
 *  Created on: Nov 27, 2012
 *      Author: prashanta
 */

#include "perceptron.h"
#include "math.h"

perceptron::perceptron()
{
	input = 0.0;
}

perceptron::~perceptron()
{
}

void perceptron::setPosPerceptron(int pos)
{
    posPerceptron = pos;
}

int perceptron::getPosPerceptron()
{
    return posPerceptron;
}

void perceptron::setLayer(int lyr)
{
    layer = lyr;
}

int perceptron::getLayer()
{
    return layer;
}

void perceptron::setInput(double val)
{
	input = val;
}


/*void perceptron::setInput(double ipFeatures[])
{
	input = ipFeatures[posPerceptron-1];
}*/


void perceptron::setInput(double ipFeatures[], double w[])
{
    if(layer == 2)
    {
    	for(int i = 0; i < MAXIN+1; i++)
		{
			input += ipFeatures[i] * w[i];
		}
    }
    else if(layer == 3)
    {
        for(int i = 0; i < MAXH+1; i++)
        {
            input += ipFeatures[i] * w[i];
        }
    }
}

double perceptron::getInput()
{
    return input;
}

void perceptron::setOutput()
{
	if (layer == 1)
	{
		output =  input;
	}
	else if (layer == 2 && posPerceptron  == 0)
	{
		output = input; // -1 i.e. the bias term for hidden node
	}
	else
	{
		output = 1.0/(1+exp(-input));
	}
}

double perceptron::getOutput()
{
    return output;
}


