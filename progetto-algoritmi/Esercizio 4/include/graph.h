#pragma once

typedef struct _Node Node;
typedef struct _Adj Adj;
typedef struct _Graph Graph;

/**
 * function to create a new graph and set the initial values
 */
Graph* graph_create_new(int num_n);

/**
 * function to create a new edge
 */
void graph_add_edge(Graph* g, int src, int dest, int w);

/**
 *function to precompute the graph and start the dfs
 */
void graph_precomputation(Graph* g);

/**
 * function to set up the query values and start the search
 */
int query_setup(Graph *g, int src, int dest, int w);