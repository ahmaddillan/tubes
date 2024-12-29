#include <iostream>
#include "darkSouls.h"
using namespace std;

void createLocation(string locationName, string boss, adrVertex &v){
    v = new vertex;
    locationName(v) = locationName;
    boss(v) = boss;
    defeated(v) = false;
    position(v) = false;
    bonfire(v) = false;
    firstEdge(v) = NULL;
    next(v) = NULL;
}

void initGraph(graph &G){
    first(G) = NULL;
}

void addLocation(graph &G, string newLocation, string newBoss){
    adrVertex newV;
    createLocation(newLocation, newBoss, newV);
    if (first(G) == NULL){
        first(G) = newV;
    }else {
        adrVertex temp = first(G);
        while (next(temp) != NULL){
            temp = next(temp);
        }
        next(temp) = newV;
    }
}

void createEdge(graph &G, string from, string to){
    vertex* src = first(G);
    vertex* dest = first(G);

    // mencari asal vertex
    while (src != NULL && locationName(src) != from) {
        src = next(src);
    }

    // mencari tujuan vertex
    while (dest != NULL && locationName(dest) != to) {
        dest = next(dest);
    }

    // menambah edge pada vertex yanf ditemukan
    if (src != NULL && dest != NULL) {
        edge* newEdge = new edge;
        destVertex(newEdge) = dest;
        nextEdge(newEdge) = firstEdge(src);
        firstEdge(src) = newEdge;
    }
}
void buildGraph(graph &G){
    addLocation(G, "Northern Undead Asylum", "NONE");
    addLocation(G, "Firelink Shrine", "NONE");
    addLocation(G, "Undead Burg", "NONE");
    addLocation(G, "Undead Parish", "Bell Gargoyles");
    addLocation(G, "Depths", "NONE");
    addLocation(G, "Blighttown", "NONE");
    addLocation(G, "Quelaag's Domain", "Chaos Witch Quelaag");
    addLocation(G, "Sen's Fortress", "Iron Golem");
    addLocation(G, "Anor Londo", "Ornstein & Smough");
    addLocation(G, "Darkroot Garden", "Great Grey Wolf Sif");
    addLocation(G, "Darkroot Basin", "NONE");
    addLocation(G, "New Londo Ruins", "NONE");
    addLocation(G, "The Catacombs", "Pinwheel");
    addLocation(G, "The Duke's Archive", "NONE");
    addLocation(G, "Lost Izalith", "The Bed of Chaos");
    addLocation(G, "Demon Ruins", "NONE");
    addLocation(G, "Tomb of Giants", "Nito");
    addLocation(G, "The Valley of Drakes", "NONE");
    addLocation(G, "The Abyss", "Four Kings");
    addLocation(G, "Crystal Cave", "Seath the Scaleless");
    addLocation(G, "Kiln of The First Flame", "Gwyn Lord of Cinder");

    // menambah edge untuk bagian connection
    createEdge(G, "Firelink Shrine", "Undead Burg");
    createEdge(G, "Undead Burg", "Undead Parish");
    createEdge(G, "Undead Parish", "Sen's Fortress");
    createEdge(G, "Blighttown", "Quelaag's Domain");
    createEdge(G, "Sen's Fortress", "Anor Londo");
}

bool checkVertices(graph &G){
    int vCount = 0;
    adrVertex v = first(G);
    while (v != NULL){
        vCount++;
        v = next(v);
    }
    if (vCount <= 0){
        return false;
    }else {
        return true;
    }
}
void showLocation(graph G){
    vertex* temp = first(G);
    while(temp!=NULL){
        cout<< "Location: " << locationName(temp)<< endl;
        cout<< "Boss: " << boss(temp)<< endl;
        cout<< "BonFire Lit: " << (bonfire(temp) ? "Yes" : "No") <<endl;
        cout<< "Connected to: ";

        edge* e = firstEdge(temp);
        while(e !=NULL){
            cout << locationName(destVertex(e))<< " ";
            e = nextEdge(e);
        }
        cout << endl << endl;
        temp = next(temp);
    }
}
bool haveLitBonfire(graph G){
    vertex* temp = first(G);
    while (temp != NULL) {
        if(bonfire(temp)){
            return true;
        }
        temp = next(temp);
    }
    return false;
}
adrVertex searchLocation(graph G, string locName){
    adrVertex temp = first(G);
    while (temp != NULL){
        if (locationName(temp) == locName){
            return temp;
        }
        temp = next(temp);
    }
}
adrVertex searchNextBoss(graph G, string bossName);
void connectLocation(graph G);
adrVertex findPosition(graph G);
void showPosition(graph G);
void findShortestPath(graph G, string strLocation, string tgtLocation);
void continuePath(graph G, string strLocation, string lastBossDefeated);
void visitLocation(graph G, string tgtLocation);
void defeatTheGame(graph G);
