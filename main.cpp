#include <iostream>
#include "darkSouls.h"
using namespace std;

int menu(){
    int input;
    cout << "~~~~~~~~~~~~~~~~~~ MENU ~~~~~~~~~~~~~~~~~~" << endl;
    cout << "1. Steps to Defeat the Game." << endl;
    cout << "2. Find the Next Boss." << endl;
    cout << "3. Find Your Position." << endl;
    cout << "4. Visit Location." << endl;
    cout << "5. Find the Shortest Route." << endl;
    cout << "6. Show All Locations and Their Status." << endl;
    cout << "0. Exit." << endl;
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout << "# choose menu: ";
    cin >> input;
    return input;
}

int main()
{
    int select;
    string bosses[11] = {"Bell_Gargoyles", "Chaos_Witch_Quelaag", "Iron_Golem",
    "Ornstein_&_Smough", "Great_Grey_Wolf_Sif", "Pinwheel", "The_Bed_of_Chaos",
    "Nito", "Four_Kings", "Seath_the_Scaleless", "Gwyn_Lord_of_Cinder"};
    graph G;

    initGraph(G);
    buildGraph(G);
    connectLocation(G);
    position(first(G)) = true;

    do{
        select = menu();
        switch(select){
            case 1:
                defeatTheGame(G);
                break;
            case 2: {
                adrVertex pos = findPosition(G);
                if (pos == NULL){
                    cout << "[ERROR] Location is nowhere to be found.\n" << endl;
                    break;
                }

                string lastBossDefeated;
                cout << "# Who was the last boss you defeated? ";
                cin >> lastBossDefeated;
                bool bossFound = false;

                for (int i = 0; i < 11; i++){
                    if (bosses[i] == lastBossDefeated){
                        for (int j = 0; j <= i; j++) {
                            adrVertex v = first(G);
                            while (v != NULL) {
                                bonfire(v) = true;
                                if (boss(v) == bosses[j]) {
                                    defeated(v) = true;
                                    break;
                                }
                                v = next(v);
                            }
                        }

                        continuePath(G, locationName(pos), lastBossDefeated);
                        bossFound = true;
                        break;
                    }
                }
                if (!bossFound){
                    cout << "There is no boss named like that.\n" << endl;
                }
                break;
            }
            case 3: {
                adrVertex pos = findPosition(G);
                if (pos != NULL){
                    cout << "Your Position right now is in " << locationName(pos) << ".\n" <<endl;
                }else {
                    cout << "You are nowhere to be found.\n" << endl;
                }
                break;
            }
            case 4: {
                cout << "# Which location you want to visit?" << endl;
                showLocation(G);
                string loc;
                cin >> loc;
                adrVertex v = first(G);
                bool locFound = false;

                while (v != NULL){
                    if (locationName(v) == loc){
                        visitLocation(G, loc);
                        locFound = true;
                        break;
                    }
                    v = next(v);
                }
                if (!locFound){
                    cout << "[ERROR] Location is nowhere to be found.\n" << endl;
                }
                break;
            }
            case 5: {
                adrVertex pos = findPosition(G);
                if (pos == NULL){
                    cout << "[ERROR] Location is nowhere to be found.\n" << endl;
                    break;
                }
                string endLocation;
                cout << "# Please enter where you're headed: ";
                cin >> endLocation;

                adrVertex v = first(G);
                bool endFound = false;

                while (v != NULL){
                    if (locationName(v) == endLocation){
                        endFound = true;
                        findShortestPath(G, locationName(pos), endLocation);
                        break;
                    }
                    v = next(v);
                }

                if (!endFound){
                     cout << "[ERROR] Location is nowhere to be found.\n" << endl;
                }
                break;
            }
            case 6:
                cout << "~~~~~~~~~~~~~~~~|List of All Location|~~~~~~~~~~~~~~~~" << endl;
                showLocation(G);
                cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;
                break;
            case 0:
                cout << "Bye~" << endl;
                break;
            default:
                cout << "There is no such menu.\n" << endl;
                break;
        }
    }while (select != 0);

    return 0;
}
