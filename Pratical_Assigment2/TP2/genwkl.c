// A union-find algorithm to identify islands
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct subset {
    int parent;
    int rank;
} subset;

// A utility function to find set of an element i
int Find(subset subsets[], int i){
    if (subsets[i].parent == i){
        return i;
    } else {
        return Find(subsets, subsets[i].parent);
    }
}

// A function that does union of two sets of x and y
void Union(subset subsets[], int xroot, int yroot){
    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

int rndnode(int nodes){ return (int)(drand48()*nodes); }

int main(){
    int seed = 1;
    //10 7
    int transportcapacity = 7;
    int transportcost = 20;
    int transportinterval = 80;
    int retrievecost = 3;
    int nodes = 20;
    int numpackets = 500;
    int conncomp = nodes;
    long atime=1;
    long rtime=5;
    int src, dst, fsrc, fdst;

        srand48(seed);

        FILE *f = fopen("entrada.txt", "w");
        if (f == NULL) {
            printf("Erro ao abrir o arquivo!\n");
            return 1;
        }

        subset *ss = (subset*)malloc(sizeof(subset) * nodes);
        for (int i = 0; i < nodes; i++) {
            ss[i].parent = i;
            ss[i].rank = 0;
        }
        int *graph = (int*)malloc(sizeof(int) * nodes * nodes);
        for (int i = 0; i < nodes * nodes; i++) graph[i] = 0;

        // Escrita dos parâmetros no arquivo
        fprintf(f, "%d\n%d\n%d\n%d\n", transportcapacity, transportcost, transportinterval, retrievecost);

        while(conncomp > 1) {
            do {
                src = rndnode(nodes);
                dst = rndnode(nodes);
            } while (src == dst);
            fsrc = Find(ss, src);
            fdst = Find(ss, dst);
            if (fsrc != fdst) {
                Union(ss, fsrc, fdst);
                conncomp--;
                graph[src * nodes + dst] = 1;
                graph[dst * nodes + src] = 1;
            }
        }

        // Escrita da matriz no arquivo
        fprintf(f, "%d\n", nodes);
        for (int i = 0; i < nodes; i++) {
            for (int j = 0; j < nodes; j++) {
                fprintf(f, "%d", graph[i * nodes + j]);
                if (j < nodes - 1) {
                    fprintf(f, " ");
                } else {
                    fprintf(f, "\n");
                }
            }
        }

        // Escrita dos pacotes no arquivo
        fprintf(f, "%d\n", numpackets);
        for (int i = 0; i < numpackets; i++) {
            do {
                src = rndnode(nodes);
                dst = rndnode(nodes);
            } while (src == dst);
            atime += (long)(drand48() * rtime);
            fprintf(f, "%ld pac %d org %d dst %d\n", atime, 1201 + i, src, dst);
        }

        fclose(f);
        free(ss);
        free(graph);

        return numpackets;
}
