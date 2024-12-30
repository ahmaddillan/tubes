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

void buildGraph(graph &G){
    addLocation(G, "Northern_Undead_Asylum", "NONE");
    addLocation(G, "Firelink_Shrine", "NONE");
    addLocation(G, "Undead_Burg", "NONE");
    addLocation(G, "Undead_Parish", "Bell_Gargoyles");
    addLocation(G, "Depths", "NONE");
    addLocation(G, "Blighttown", "NONE");
    addLocation(G, "Quelaag's_Domain", "Chaos_Witch_Quelaag");
    addLocation(G, "Sen's_Fortress", "Iron_Golem");
    addLocation(G, "Anor_Londo", "Ornstein_&_Smough");
    addLocation(G, "Darkroot_Garden", "Great_Grey_Wolf_Sif");
    addLocation(G, "Darkroot_Basin", "NONE");
    addLocation(G, "New_Londo_Ruins", "NONE");
    addLocation(G, "The_Catacombs", "Pinwheel");
    addLocation(G, "The_Duke's_Archive", "NONE");
    addLocation(G, "Lost_Izalith", "The_Bed_of_Chaos");
    addLocation(G, "Demon_Ruins", "NONE");
    addLocation(G, "Tomb_of_Giants", "Nito");
    addLocation(G, "The_Valley_of_Drakes", "NONE");
    addLocation(G, "The_Abyss", "Four Kings");
    addLocation(G, "Crystal_Cave", "Seath_the_Scaleless");
    addLocation(G, "Kiln_of_The_First_Flame", "Gwyn_Lord_of_Cinder");
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
    if (first(G) == NULL){
        cout << "empty";
        return;
    }
    adrVertex v = first(G);
    while (v != NULL){
        cout << locationName(v);
        adrEdge e = firstEdge(v);
        if (boss(v) == "NONE"){
            cout << " [Bonfire: " << (bonfire(v) ? "Lit" : "Not Lit") << (position(v) ? "] You Are Here" : "]") << endl;
        }else {
            cout << " [Boss: " << boss(v) << " (" << (defeated(v) ? "Slain" : "Alive") << "), Bonfire: " << (bonfire(v) ? "Lit" : "Not Lit") << (position(v) ? "] You Are Here" : "]") << endl;
        }
        while (e != NULL){
            cout << " ->" << destLocation(e) << endl;
            e = nextEdge(e);
        }
        cout << endl;
        v = next(v);
    }
}

bool haveLitBonfire(graph G){
    bool litBonfire = false;
    adrVertex v = first(G);
    while (v != NULL){
        if (bonfire(v) == true){
            litBonfire = true;
            break;
        }
        v = next(v);
    }
    return litBonfire;
}

adrVertex searchLocation(graph G, string locationName){
    adrVertex v = first(G);
    while (v != NULL){
        if (locationName == locationName(v)){
            return v;
        }
        v = next(v);
    }
    return NULL;
}

adrVertex searchNextBoss(graph G, string bossName){
    adrVertex v = first(G);
    adrVertex bossLocation = NULL;
    while (v != NULL){
        if (bossName == boss(v)){
            bossLocation = v;
        }

        if (bossLocation != NULL){
            v = next(v);
            if (v != NULL && boss(v) != "NONE"){
                return v;
            }
        } else {
            v = next(v);
        }
    }
    return NULL;
}

void createEdge(graph &G, string locationName, string destLocation){
    adrVertex v = searchLocation(G, locationName);
    adrVertex destV = searchLocation(G, destLocation);

    adrEdge e = new edge;
    destLocation(e) = destLocation;
    destVertex(e) = destV;
    nextEdge(e) = NULL;

    if (firstEdge(v) == NULL){
        firstEdge(v) = e;
    } else {
        adrEdge temp = firstEdge(v);
        while (nextEdge(temp) != NULL){
            temp = nextEdge(temp);
        }
        nextEdge(temp) = e;
    }

    adrEdge reversE = new edge;
    destLocation(reversE) = locationName;
    destVertex(reversE) = v;
    nextEdge(reversE) = NULL;
    if (firstEdge(destV) == NULL){
        firstEdge(destV) = reversE;
    }else {
        adrEdge temp2 = firstEdge(destV);
        while (nextEdge(temp2) != NULL){
            temp2 = nextEdge(temp2);
        }
        nextEdge(temp2) = reversE;
    }
}

void connectLocation(graph G){
    createEdge(G, "Northern_Undead_Asylum", "Firelink_Shrine");
    createEdge(G, "Firelink_Shrine", "Undead_Burg");
    createEdge(G, "Firelink_Shrine", "Undead_Parish");
    createEdge(G, "Firelink_Shrine", "New_Londo_Ruins");
    createEdge(G, "Firelink_Shrine", "The_Catacombs");
    createEdge(G, "Firelink_Shrine", "Kiln_of_The_First_Flame");
    createEdge(G, "Undead_Burg", "Depths");
    createEdge(G, "Undead_Burg", "The_Valley_of_Drakes");
    createEdge(G, "Undead_Burg", "Undead_Parish");
    createEdge(G, "Undead_Burg", "Darkroot_Basin");
    createEdge(G, "Undead_Parish", "Darkroot_Garden");
    createEdge(G, "Undead_Parish", "Depths");
    createEdge(G, "Undead_Parish", "Sen's_Fortress");
    createEdge(G, "Depths", "Blighttown");
    createEdge(G, "Blighttown", "The_Valley_of_Drakes");
    createEdge(G, "Blighttown", "Quelaag's_Domain");
    createEdge(G, "Quelaag's_Domain", "Demon_Ruins");
    createEdge(G, "Sen's_Fortress", "Anor_Londo");
    createEdge(G, "Anor_Londo", "The_Duke's_Archive");
    createEdge(G, "Darkroot_Garden", "Darkroot_Basin");
    createEdge(G, "Darkroot_Basin", "The_Valley_of_Drakes");
    createEdge(G, "New_Londo_Ruins", "The_Abyss");
    createEdge(G, "New_Londo_Ruins", "The_Valley_of_Drakes");
    createEdge(G, "The_Duke's_Archive", "Crystal_Cave");
    createEdge(G, "Demon_Ruins", "Lost_Izalith");
    createEdge(G, "The_Catacombs", "Tomb_of_Giants");
}

adrVertex findPosition(graph G){
    adrVertex v = first(G);
    while (v != NULL){
        if(position(v) == true){
            return v;
        }
        v = next(v);
    }
    return NULL;
}

void showPosition(graph G){
    adrVertex v = findPosition(G);
    cout << "You are in " << locationName(v) << "." << endl;
}

void findShortestPath(graph G, string strLocation, string tgtLocation){
    const int NMAX = INT_MAX;

    int countV = 0;
    adrVertex v = first(G);
    while (v != NULL){
        countV++;
        v = next(v);
    }

    string locations[countV];
    bool visited[countV];
    int distance[countV];
    int predecessors[countV];

    v = first(G);
    for (int i = 0; i < countV; ++i){
        locations[i] = locationName(v);
        visited[i] = false;
        distance[i] = NMAX;
        predecessors[i] = -1;
        v = next(v);
    }

    int startIdx = -1;
    int targetIdx = -1;
    for (int i = 0; i < countV; ++i){
        if (locations[i] == strLocation){
            startIdx = i;
        }
        if (locations[i] == tgtLocation){
            targetIdx = i;
        }
    }

    if (startIdx == -1 || targetIdx == -1){
        cout << "Location not found!" << endl;
        return;
    }

    int Q[countV];
    int front = 0, rear = 0;

    Q[rear++] = startIdx;
    visited[startIdx] = true;
    distance[startIdx] = 0;

    while (front < rear){
        int currentIdx = Q[front++];

        adrVertex currentV = first(G);
        for (int i = 0; i < currentIdx; ++i){
            currentV = next(currentV);
        }

        adrEdge e = firstEdge(currentV);
        while (e != NULL){
            string neighborLocation = destLocation(e);
            int neighborIdx = -1;

            for (int j = 0; j < countV; ++j){
                if (locations[j] == neighborLocation){
                    neighborIdx = j;
                    break;
                }
            }

            if (neighborIdx != -1 && !visited[neighborIdx]){
                visited[neighborIdx] = true;
                distance[neighborIdx] = distance[currentIdx] + 1;
                predecessors[neighborIdx] = currentIdx;
                Q[rear++] = neighborIdx;

                if (neighborIdx == targetIdx){
                    break;
                }
            }
            e = nextEdge(e);
        }
    }
    if (distance[targetIdx] == -1){
        cout << "No path from " << strLocation << " ke " << tgtLocation << "." << endl;
    }else {
        cout << "The shortest path from " << strLocation << " to " << tgtLocation << " is: " << distance[targetIdx] << endl;
        cout << "Path: ";
        string path[countV];
        int pathLength = 0;
        int step = targetIdx;
        while (step != -1){
            path[pathLength++] = locations[step];
            step = predecessors[step];
        }
        for (int i = pathLength - 1; i >= 0; --i){
            cout << path[i];
            adrVertex temp = first(G);
            while (temp != NULL){
                if (locationName(temp) == path[i] && bonfire(temp) == false){
                    bonfire(temp) = true;
                }
                temp = next(temp);
            }
            if (i > 0){
                cout << " -> ";
            }
        }
        cout << "\n" << endl;
    }
}

void continuePath(graph G, string strLocation, string lastBossDefeated){
    adrVertex v = searchNextBoss(G, lastBossDefeated);
    cout << "Your next boss is " << boss(v) << " in " << locationName(v) << ".\n" << endl;
    findShortestPath(G, strLocation, locationName(v));
}

void visitLocation(graph G, string tgtLocation){
    adrVertex startV, endV;
    startV = findPosition(G);
    endV = searchLocation(G, tgtLocation);
    position(startV) = false;
    position(endV) = true;

    if (bonfire(endV) == false){
        bonfire(endV) = true;
    }

    cout << "You moved from " << locationName(startV) << " to " << locationName(endV) << ".\n" << endl;
}

void defeatTheGame(graph G){
    adrVertex v = first(G);
    position(v) = true;
    cout << "|First Step|\n" << endl;
    cout << "Defeat Bell Gargoyles!\n" << endl;
    findShortestPath(G, "Northern_Undead_Asylum", "Undead_Parish");
    visitLocation(G, "Undead_Parish");
    while (v != NULL){
        if (boss(v) == "Bell_Gargoyles"){
            defeated(v) = true;

        }
        v = next(v);
    }
    v = first(G);

    cout << "|Second Step|\n" << endl;
    cout << "Defeat Chaos Witch Quelaag!\n" << endl;
    findShortestPath(G, "Undead_Parish", "Quelaag's_Domain");
    visitLocation(G, "Quelaag's_Domain");
    while (v != NULL){
        if (boss(v) == "Chaos_Witch_Quelaag"){
            defeated(v) = true;

        }
        v = next(v);
    }
    v = first(G);

    cout << "|Third Step|\n" << endl;
    cout << "Defeat Iron Golem!\n" << endl;
    findShortestPath(G, "Quelaag's_Domain", "Sen's_Fortress");
    visitLocation(G, "Sen's_Fortress");
    while (v != NULL){
        if (boss(v) == "Iron_Golem"){
            defeated(v) = true;

        }
        v = next(v);
    }
    v = first(G);

    cout << "|Fourth Step|\n" << endl;
    cout << "Defeat Ornstein & Smough!\n" << endl;
    findShortestPath(G, "Sen's_Fortress", "Anor_Londo");
    visitLocation(G, "Anor_Londo");
    while (v != NULL){
        if (boss(v) == "Ornstein_&_Smough"){
            defeated(v) = true;

        }
        v = next(v);
    }
    v = first(G);

    cout << "|Fifth Step|\n" << endl;
    cout << "Defeat Great Grey Wolf Sif!\n" << endl;
    findShortestPath(G, "Anor_Londo", "Darkroot_Garden");
    visitLocation(G, "Darkroot_Garden");
    while (v != NULL){
        if (boss(v) == "Great_Grey_Wolf_Sif"){
            defeated(v) = true;

        }
        v = next(v);
    }
    v = first(G);

    cout << "|Sixth Step|\n" << endl;
    cout << "Defeat Pinwheel!\n" << endl;
    findShortestPath(G, "Darkroot_Garden", "The_Catacombs");
    visitLocation(G, "The_Catacombs");
    while (v != NULL){
        if (boss(v) == "Pinwheel"){
            defeated(v) = true;

        }
        v = next(v);
    }
    v = first(G);

    cout << "|Seventh Step|\n" << endl;
    cout << "Defeat The Bed of Chaos!\n" << endl;
    findShortestPath(G, "The_Catacombs", "Lost_Izalith");
    visitLocation(G, "Lost_Izalith");
    while (v != NULL){
        if (boss(v) == "The_Bed_of_Chaos"){
            defeated(v) = true;

        }
        v = next(v);
    }
    v = first(G);

    cout << "|Eighth Step|\n" << endl;
    cout << "Defeat Nito!\n" << endl;
    findShortestPath(G, "Lost_Izalith", "Tomb_of_Giants");
    visitLocation(G, "Tomb_of_Giants");
    while (v != NULL){
        if (boss(v) == "Nito"){
            defeated(v) = true;

        }
        v = next(v);
    }
    v = first(G);

    cout << "|Ninth Step|\n" << endl;
    cout << "Defeat Four Kings!\n" << endl;
    findShortestPath(G, "Tomb of Giants", "The_Abyss");
    visitLocation(G, "The_Abyss");
    while (v != NULL){
        if (boss(v) == "Four King"){
            defeated(v) = true;

        }
        v = next(v);
    }
    v = first(G);

    cout << "|Tenth Step|\n" << endl;
    cout << "Defeat Seath the Scaleless!\n" << endl;
    findShortestPath(G, "The_Abyss", "Crystal_Cave");
    visitLocation(G, "Crystal_Cave");
    while (v != NULL){
        if (boss(v) == "Seath_the_Scaleless"){
            defeated(v) = true;
        }
        v = next(v);
    }
    v = first(G);

    cout << "|Last Step|\n" << endl;
    cout << "Defeat Gwyn Lord of Cinder!\n" << endl;
    findShortestPath(G, "Crystal_Cave", "Kiln_of_The_First_Flame");
    visitLocation(G, "Kiln_of_The_First_Flame");
    while (v != NULL){
        if (boss(v) == "Gwyn_Lord_of_Cinder"){
            defeated(v) = true;

        }
        v = next(v);
    }
    cout << "Congratulation You Beat The Game!" << endl;
}
