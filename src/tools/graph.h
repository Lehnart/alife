#ifndef ALIFE_GRAPH_H
#define ALIFE_GRAPH_H

#include "array.h"

typedef struct Node {
    unsigned int id;
    void *data;

    Array *inputs;
    Array *outputs;
} Node;

typedef struct Edge {
    unsigned int id;
    void *data;

    Node *src;
    Node *dest;
} Edge;


typedef struct Graph {
    Array *heads;
    Array *nodes;
    Array *edges;
} Graph;


Graph *graph_new();

Node *graph_add_node(Graph *graph, void *data);

Node *graph_add_head(Graph *graph, void *data);

Edge *graph_add_edge(Graph *graph, Node *src, Node *dest, void *data);

Node *graph_get_node(Graph *graph, unsigned int id);


#endif //ALIFE_GRAPH_H
