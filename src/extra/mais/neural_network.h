#ifndef ALIFE_NEURAL_NETWORK_H
#define ALIFE_NEURAL_NETWORK_H

#include "../../tools/graph.h"

typedef struct NeuronEdge{
    double weight;
} NeuronEdge;


typedef struct Neuron{
    double bias;
    double result;
    int layer;
    double (*activation_function)(const double weights[], const double inputs[], double bias, int size);
} Neuron;

typedef struct NeuralNetwork{
    int n_layers;
    Graph* graph;
} NeuralNetwork;

NeuralNetwork* neural_network_new(const int layers[], int size);
Array* neural_network_evaluate(NeuralNetwork* nn, Array* inputs);

#endif //ALIFE_NEURAL_NETWORK_H
