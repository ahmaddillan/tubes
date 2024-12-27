#ifndef DARKSOULS_H_INCLUDED
#define DARKSOULS_H_INCLUDED
#include <iostream>

#define first(G) G->first
#define locationName(V) V->locationName
#define boss(V) V->boss
#define defeated(V) V->defeated
#define position(V) V->position
#define bonfire(V) V->bonfire
#define firstEdge(V) V->firstEdge
#define next(V) V->next
#define destLocation(E) E->destLocation
#define destVertex(E) E->destVertex
#define nextEdge(E) E->nextEdge
using namespace std;

typedef struct vertex *adrVertex;

typedef struct edge *adrEdge;

struct vertex{
    string locationName;
    string boss;
    bool defeated;
    bool position
    bool bonfire;
    adrEdge firstEdge;
    adrVertex next;
};

struct edge{
    string destLocation;
    adrVertex destVertex;
    adrEdge nextEdge;
};

struct graph {
    adrVertex first;
};

void createVertex(string locationName, string boss, adrVertex &v);
void initGraph(graph &G);
void addVertex(graph &G, string newLocation, string newBoss);
void buildGraph(graph &G);
bool checkVertices(graph &G);
void showVertex(graph G);
bool haveVisited(graph G);
adrVertex searchVertex(graph G, string locationName);
void createEdge(graph &G, string locationName, string destLocation);
void connectVertex(graph G);
adrVertex findPosition(graph G);
void showPosition(graph G);
void findShortestPath(graph G, string strLocation, string tgtLocation);
void visitLocation(graph G, string tgtLocation);

#endif // DARKSOULS_H_INCLUDED
