#ifndef PERCEPTRON_H
#define PERCEPTRON_H

class perceptron
{
    private:
        static int numPerceptrons; // total number of perceptrons in the net
        int layer; // layer to which the perceptron belongs to
        double input; // input to the perceptron
        double output; // output from the perceptron

    public:
        perceptron();
        double calculateInput();
        double calculateOutput();
};

#endif // PERCEPTRON_H
