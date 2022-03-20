
#include <stddef.h>
#include <stdio.h>
#include "../array.h"
#include "../graph.h"
#include "../neural_network.h"

int main() {
    int layers[3] = {3, 3, 3};
    NeuralNetwork *nn = neural_network_new(layers, 3);

    Array *inputs = array_new(3);

    double input_doubles[3] = {1., 2., 3.};

    array_set(inputs, 0, &input_doubles[0]);
    array_set(inputs, 1, &input_doubles[1]);
    array_set(inputs, 2, &input_doubles[2]);

    neural_network_evaluate(nn, inputs);

    return 0;
}