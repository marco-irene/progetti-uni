#include <stdlib.h>
#include <string.h>
#include "../inc/graph.h"

struct _Node {
    int value;
    int weight;
    Node *next;
};

struct _Adj {
    int value;
    int level;
    int prev_n;
    int prev_w;
    Node *head;
};

struct _Graph {
    int n_nodes;
    int max_weight;
    Adj *adj_list;
};

Graph *graph_create_new(int num_v) {
    Graph *res = (Graph *) malloc(sizeof(Graph));
    res->adj_list = (Adj *) malloc(sizeof(Adj) * (num_v + 1));
    res->n_nodes = num_v;

    for (int i = 0; i <= res->n_nodes; i++) {
        res->adj_list[i].value = i;
        res->adj_list[i].level = -1;
        res->adj_list[i].prev_n = -1;
        res->adj_list[i].head = NULL;
    }

    return res;
}

/**
 * function to create a new node
 * @param v: node value
 * @param w: node weight
 * @return
 */
  Node *new_node(int v, int w) {
    Node *res = (Node *) malloc(sizeof(Node));
    res->value = v;
    res->weight = w;

    return res;
}

void graph_add_edge(Graph *g, int src, int dest, int w) {
    g->max_weight = g->max_weight > w ? g->max_weight : w;
    Node *a = new_node(src, w);
    Node *b = new_node(dest, w);

    b->next = g->adj_list[a->value].head;
    g->adj_list[a->value].head = b;

    a->next = g->adj_list[b->value].head;
    g->adj_list[b->value].head = a;
}

/**
 * function to scroll through the graph (depth first) and set every node's level
 * @param g : graph
 * @param v : current node
 * @param prev_v : v's previous node
 */
void dfs(Graph *g, int v, int prev_v) {
    g->adj_list[v].level = g->adj_list[prev_v].level + 1;
    g->adj_list[v].prev_n = prev_v;
    Node *tmp = g->adj_list[v].head;

    while (tmp != NULL) {
        if (tmp->value == prev_v) {
            g->adj_list[v].prev_w = tmp->weight;
        } else {
            dfs(g, tmp->value, v);
        }
        tmp = tmp->next;
    }
}

void graph_precomputation(Graph *g) {
    dfs(g, 1, 0);
}

/**
 * function to compare the weight of the query to the weights of the path between the two nodes
 * @param g: graph
 * @param src: first node
 * @param dest: second node
 * @param w: weight of the query
 * @return: 1 if the query was successful, 0 otherwise
 */
int query(Graph *g, int src, int dest, int w) {
    if (src == dest) { return 0; }
//src is higher than dest
    if (g->adj_list[src].level == g->adj_list[dest].level)
        return (g->adj_list[src].prev_w > w || g->adj_list[dest].prev_w > w) ? 1 : query(g, g->adj_list[src].prev_n,
                                                                                         g->adj_list[dest].prev_n, w);

    return g->adj_list[dest].prev_w > w ? 1 : query(g, src, g->adj_list[dest].prev_n, w);
}

int query_setup(Graph *g, int src, int dest, int w) {
    int tmp;
    if (w > g->max_weight) { return 0; }
    if (g->adj_list[src].level > g->adj_list[dest].level) {
        tmp = src;
        src = dest;
        dest = tmp;
    }

    return query(g, src, dest, w);
}