#ifndef DARKSOULS_H_INCLUDED
#define DARKSOULS_H_INCLUDED
#include <iostream>

#define first(G) G.first
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
    bool position;
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

void createLocation(string locationName, string boss, adrVertex &v);
void initGraph(graph &G);
void addLocation(graph &G, string newLocation, string newBoss);
void buildGraph(graph &G);
bool checkVertices(graph &G);
void showLocation(graph G);
bool haveLitBonfire(graph G);
adrVertex searchLocation(graph G, string locationName);
adrVertex searchNextBoss(graph G, string bossName);
void createEdge(graph &G, string locationName, string destLocation);
void connectLocation(graph G);
adrVertex findPosition(graph G);
void showPosition(graph G);
void findShortestPath(graph G, string strLocation, string tgtLocation);
void continuePath(graph G, string strLocation, string lastBossDefeated);
void visitLocation(graph G, string tgtLocation);
void defeatTheGame(graph G);
#endif // DARKSOULS_H_INCLUDED
