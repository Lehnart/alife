#include <malloc.h>
#include "neural_network.h"
#include "math.h"
#include "tools.h"

double activation(const double weights[], const double inputs[], double bias, int size) {
    double sum = 0.;
    for (int i = 0; i < size; i++) {
        sum += weights[i] * inputs[i];
    }
    sum += bias;

    return 1. / (1 + exp(sum));
}

NeuralNetwork *neural_network_new(const int layers[], int size) {

    NeuralNetwork *nn = malloc(sizeof(NeuralNetwork));

    Graph *graph = graph_new();
    for (int layer_index = 0; layer_index < size; layer_index++) {
        for (int i = 0; i < layers[layer_index]; i++) {

            Neuron *neuron = malloc(sizeof(Neuron));
            neuron->activation_function = activation;
            neuron->layer = layer_index;
            neuron->bias = rand_double();

            if (layer_index == 0) {
                Node *node = graph_add_head(graph, neuron);

                NeuronEdge *neuron_edge = malloc(sizeof(NeuronEdge));
                neuron_edge->weight = rand_double();
                graph_add_edge(graph, NULL, node, neuron_edge);
            } else {
                Node *node = graph_add_node(graph, neuron);
                int offset = 0;
                for (int j = 0; j < layer_index - 1; j++) {
                    offset += layers[j];
                }
                for (int j = offset; j < offset + layers[layer_index]; j++) {
                    NeuronEdge *neuron_edge = malloc(sizeof(NeuronEdge));
                    neuron_edge->weight = rand_double();
                    graph_add_edge(graph, graph_get_node(graph, j), node, neuron_edge);
                }
            }
        }
    }

    nn->graph = graph;
    nn->n_layers = size;
    return nn;
}

Array *neural_network_evaluate(NeuralNetwork *nn, Array *inputs) {
    Array *nodes = nn->graph->nodes;
    double node_inputs[100];
    double node_weights[100];

    for (unsigned int node_index = 0; node_index < nodes->size; node_index++) {
        Node *node = graph_get_node(nn->graph, node_index);
        Neuron *neuron = node->data;
        if (neuron->layer == 0) {
            double *input = array_get(inputs, node_index);
            double *weight = array_get(node->inputs, 0);
            double result = neuron->activation_function(weight, input, neuron->bias, 1);
            neuron->result = result;
        } else {
            for (int edge_index = 0; edge_index < node->inputs->size; edge_index++) {
                Edge *edge = array_get(node->inputs, edge_index);
                NeuronEdge *neuron_edge = edge->data;
                Neuron *input_neuron = edge->src->data;
                node_inputs[edge_index] = input_neuron->result;
                node_weights[edge_index] = neuron_edge->weight;
            }

            double result = neuron->activation_function(node_weights, node_inputs, neuron->bias,
                                                        (int) node->inputs->size);
            neuron->result = result;
        }
    }
}