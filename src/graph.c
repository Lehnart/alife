#include <malloc.h>
#include "graph.h"

Graph *graph_new() {
    Graph *graph = malloc(sizeof(Graph));
    graph->heads = array_new(0);
    graph->nodes = array_new(0);
    graph->edges = array_new(0);

    return graph;
}

Node *graph_add_node(Graph *graph, void *data) {
    Node *node = malloc(sizeof(Node));
    node->data = data;
    node->inputs = array_new(0);
    node->outputs = array_new(0);

    node->id = graph->nodes->size;
    array_append(graph->nodes, node);

    return node;
}

Node *graph_add_head(Graph *graph, void *data) {
    Node *node = graph_add_node(graph, data);
    array_append(graph->heads, node);
    return node;
}

Edge *graph_add_edge(Graph* graph, Node* src, Node* dest, void* data){
    Edge *edge = malloc(sizeof(Edge));
    edge->data = data;
    edge->src = src;
    edge->dest = dest;
    edge->id = graph->edges->size;
    array_append(graph->edges, edge);

    if (dest != NULL) array_append( dest->inputs, edge );
    if (src != NULL) array_append( src->outputs, edge );
    return edge;
}

Node* graph_get_node(Graph *graph, unsigned int id) {
    void *ptr = array_get(graph->nodes, id);
    if (ptr != NULL){
        Node* node = (Node*) ptr;
        return node;
    }
    return NULL;
}


