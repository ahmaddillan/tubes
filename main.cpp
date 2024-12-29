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
    string bosses[11] = {"Bell Gargoyles", "Chaos Witch Quelaag", "Iron Golem",
    "Ornstein & Smough", "Great Grey Wolf Sif", "Pinwheel", "The Bed of Chaos",
    "Nito", "Four Kings", "Seath the Scaleless", "Gwyn Lord of Cinder"};
    graph G;

    initGraph(G);
    buildGraph(G);
    //connectLocation(G);
    position(first(G)) = true;

    do{
        select = menu();
        switch(select){
            case 1:
                //memberikan step menyelesaikan game

                //defeatTheGame(G);
                break;
            case 2: {
                //mencari bos berikutnya

                string strLocation;
                string lastBossDefeated;
                cout << "# Please enter your location right now: ";
                cin >> strLocation;
                cout << "# Who was the last boss you defeated? ";
                cin >> lastBossDefeated;
                bool bossFound = false;

                for (int i = 0; i < 11; i++){
                    if (bosses[i] == lastBossDefeated){
                        for (int j = 0; j <= i; j++) {
                            adrVertex v = first(G);
                            while (v != NULL) {
                                if (boss(v) == bosses[j]) {
                                    defeated(v) = true;
                                    break;
                                }
                                v = next(v);
                            }
                        }

                       // continuePath(G, strLocation, lastBossDefeated);
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
                //mencari posisi player sekarang

              //  adrVertex pos = findPosition(G);
            //    if (pos != NULL){
                 //   cout << "Your Position right now is in " << locationName(pos) << ".\n" <<endl;
              //  }else {
               //     cout << "You are nowhere to be found.\n" << endl;
               // }
                break;
            }
            case 4: {
                //mencari rute dari lokasi yang dicari

                cout << "# Which location you want to visit?" << endl;
                showLocation(G);
                string loc;
                cin >> loc;
                adrVertex v = first(G);
                bool locFound = false;

                while (v != NULL){
                    if (locationName(v) == loc){
                       // visitLocation(G, loc);
                      //  locFound = true;
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
                //mecari rute terpendek lokasi yang dicari posisi player sekarang

                string strLocation;
                string endLocation;
                cout << "# Please enter your location right now: ";
                cin >> strLocation;
                cout << "# Please enter where you're headed: ";
                cin >> endLocation;

                adrVertex v = first(G);
                bool strFound = false, endFound = false;

                while (v != NULL){
                    if (locationName(v) == strLocation){
                        strFound = true;
                        adrVertex temp = first(G);
                        while (temp != NULL){
                            if (locationName(temp) == endLocation){
                                endFound = true;
                               // findShortestPath(G, strLocation, endLocation);
                                break;
                            }
                            temp = next(temp);
                        }
                        break;
                    }
                    v = next(v);
                }

                if (!strFound || !endFound){
                     cout << "[ERROR] Location is nowhere to be found.\n" << endl;
                }
                break;
            }
            case 6:
                //menampilkan semua lokasi dan informasinya

                cout << "~~~~~~~~~~~~~~~~|List of All Location|~~~~~~~~~~~~~~~~" << endl;
                showLocation(G);
                cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;
                break;
            case 0:
                //menyelesaikan program

                cout << "Bye~" << endl;
                break;
            default:
                cout << "There is no such menu.\n" << endl;
                break;
        }
    }while (select != 0);

    return 0;
}
