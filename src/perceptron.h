/*
 * perceptron.h
 *
 *  Created on: Nov 27, 2012
 *      Author: prashanta
 */

#ifndef PERCEPTRON_H_
#define PERCEPTRON_H_

#include "datatypes.h"
class perceptron
{
    private:
		static int numPerceptron; // keeps track of total number of perceptrons
        int posPerceptron; // the position of the perceptron in a particular layer
        int layer; // layer to which the perceptron belongs to
        double input; // input to the perceptron
        double output; // output from the perceptron

    public:
        perceptron();
        virtual ~perceptron();

        void setPosPerceptron(int);
        int getPosPerceptron();

        void setLayer(int);
        int getLayer();

        // to calculate the input to each perceptron we must pass the input features which a part of the structure myFeatures, and also the weight array to
        // that particular perceptron which we read from the weight file
        void setInput(double *ipFeatures, double *w);
        double getInput();

        // no need of input parameters since it will use the private data input
        void setOutput();
        double getOutput();
};

#endif /* PERCEPTRON_H_ */
