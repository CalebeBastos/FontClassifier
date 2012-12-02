/*
 * datatypes.h
 *
 *  Created on: Nov 27, 2012
 *      Author: prashanta
 */

#ifndef DATATYPES_H_
#define DATATYPES_H_

////////////////////////////////////////////////////////////////////
// Constants for Backprop Font Data //
////////////////////////////////////////////////////////////////////

#define FV_IN "norm.sep"
#define NORMALIZE false
#define FONT_DATA true

#define ALPHA 0.0 // momentum factor
#define ETA 1 // learning rate
#define MAXIN 14 // number of input nodes
#define MAXH 20 // number of nodes hidden layer
#define MAXOUT 26 // number of nodes output layer
#define N_ITERATIONS 500 // times to train the network
#define NUMFV 78 // number of feature vectors total
#define NUMUV 78 // number of test vectors
#define LOG_MOD 10 // print results every LOG_MOD iterations

#define RESULTS_OUT_NAME "bp.out"
#define WEIGHTS_IN "bpw.in"
#define WEIGHTS_OUT "bpw.out"
#define WEIGHT_FILE_NAME "genw.txt" // for genweights

struct myFeatures
{
    int alphabet;
    int font;
    double feature[14]; // hardcoded 14. need to change it later sometime
};

extern int _NUMDATA_; // total number of data sets in the input file

#endif /* DATATYPES_H_ */
