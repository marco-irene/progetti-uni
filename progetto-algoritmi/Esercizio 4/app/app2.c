#include <stdio.h>
#include "../inc/graph.h"

int main(int argc, char *argv[]) {
    int n, src, dest, w, q;
    scanf("%d", &n);
    Graph *g = graph_create_new(n);
    for(int i = 0; i < n-1; i++) {
        scanf("%d %d %d", &src, &dest, &w);
        graph_add_edge(g, src, dest, w);
    }

    graph_precomputation(g);
    scanf("%d", &q);

    for(int i = 0; i < q; i++) {
        scanf("%d %d %d", &src, &dest, &w);
        if(query_setup(g, src, dest, w)) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }

    return 0;
}