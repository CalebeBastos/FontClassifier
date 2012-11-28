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

void perceptron::setInput(double *ipFeatures, double *w)
{
    if(layer == 1)
    {
        input = ipFeatures[posPerceptron];
    }
    else if(layer == 2)
    {
        for(int i = 0; i < MAXIN+1; i++)
        {
            input += ipFeatures[i] * w[i];
        }
    }
    else
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
    output = 1.0/(1+exp(-input));
}

double perceptron::getOutput()
{
    return output;
}


