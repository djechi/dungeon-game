// finalproject.cpp
// DJ Echipare, CISP 360
// 5/3/23

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <random>
#include <iomanip>

using namespace std;

struct Room{
    string room_title;
    string room_description;
    int room_id;
    int exitCodeN;
    int exitCodeS;
    int exitCodeE;
    int exitCodeW;
    bool isOccupied;
    int roomCount;
};

// Specification A1 - Add different classes for the character
struct playerClass{
    string classType[4] = {"Knight", "Tank", "Mage", "Rogue"};
    string classDescription[4] = {"A noble knight who uses his trusty sword to slay his foes", "A juggernaut who uses his brolic strength to crush his foes", "A sorcerer who uses forbidden magic to rid of foes.", "A thief who uses his craftiness to gain the upperhand on his foes."};
    string classStats[4] = {"80 HP | 16 DMG | 60 DEF | 40 DODGE | 15 HEAL | 30 CRIT", "110 HP | 14 DMG | 80 DEF | 20 DODGE | 20 HEAL | 15 CRIT", "70 HP | 20 DMG | 30 DEF | 30 DODGE | 20 HEAL | 20 CRIT", "55 HP | 13 DMG | 40 DEF | 80 DODGE | 13 HEAL | 70 CRIT"};
    string classAttack[4] = {"You thrust your sword ", "You charge head first ", "You cast a dark magic spell ", "You slice with your dagger "};
    string classHealMsg[4] = {"You drink a health potion ", "You inject yourself with chemicals", "You cast a healing spell", "You consume a herb"}; 
    int classHP[4] = {80, 110, 70, 55};
    int classDMG[4] = {16, 14, 20, 13};
    int classDefense[4] = {60, 80, 30, 40};
    int classDodgeChance[4] = {40, 20, 30, 80};
    int classHeal[4] = {15, 11, 20, 13};
    int classCrit[4] = {30, 15, 20, 80};
};

// Specification B2 - Put your monsters in a Monster() class
class Monster
{
private: 
    string monster[4] = {"Orc", "Vampire", "Minotaur", "Chimera"};
    string monsterType[4] = {"A large green ogre stands in your way.", "A blood sucking monster stands in your way.", "A being that is half-man and half-bull stands in your way.", "A fire breathing animal-like creature stands in your way."};

public:
    void SelectMonster(int);
    void Combat(int);
    int monsterHit(int);
    int Health (int);
    int monsterHP[4] = {100, 80, 120, 75};
    int monsterDMG[4] = {8, 6, 12, 13};
    int monsterDefense[4] = {55, 20, 70, 45}; 
    int monsterCrit[4] = {20, 30, 35, 25};
    string monsterAttack[4] = {"The Orc slashes you with his axe ", "The Vampire grazes you with his teeth ", "The Minotaur hits you with his club ", "The Chimera breathes fire at you "};
};

int Monster::Health(int index){
  return monsterHP[index];  
}

int Monster::monsterHit(int index){
  return monsterDMG[index];
}

void Monster::Combat(int index){
  cout << monsterAttack[index];
}

void Monster::SelectMonster(int index){
  cout << "Monster: " << monster[index] << endl;
  cout << "Monster Description: " << monsterType[index] << endl;
}

void menu();
void classMenu(const playerClass&);
void classChoice(const playerClass&, int);
void RoomCheck(int);
void Credits();
int dmgCalc(int, int, int, int, bool&);
int randomRange(int, int);
bool calcDodge (int);

int main() {
    playerClass classes;
    Monster m;
    int menuNum, currentRoomID = 1;
    int classIndex;
    bool quit = false;
    char move;
    char fightMove;
    string playerName;
    srand(time(0));
    const int critDmg = 3;
    const int numMonsters = 4;
    bool skipRoomDesc = false;
  
    // Specification B1 - Add more rooms
    // Specification C1 - Five Rooms
    Room rooms[9];
    rooms[1] = {"Starting Room", "Surrounding you is a room full of weapons scattered across the floor, seemingly belonging to those that have entered the room before you.\nThere is a door to the North, South, East, and West.", 1, 2, 3, 4, 5, false};
    rooms[2] = {"Concrete Room", "Surrounding you is a great room surrounded by dirty concrete walls.\nThere is a door to the South.", 2, -1, 1, -1, -1, false, 0};
    rooms[3] = {"Royal Room", "Surrounding you is a room filled with gold furniture and marble floors.\nThere is a door to the North.", 3, 1, -1, -1, -1, true, 0};
    rooms[4] = {"Torture Room", "Surrounding you is a room of pure evil, filled with various torture devices, blades, and saws.\nThere is a door to the East.", 4, -1, -1, 6, 1, true, 0};
    rooms[5] = {"Library Room", "Surrounding you is a room resembling that of an old ruined library with fallen book cases and ripped book pages all over the floor.\nThere is a door to the East.", 5, -1, -1, 1, -1, true, 0};
    rooms[6] = {"Mirror Room", "Surrounding you is a room full of mirrors.\nThere is a door to the South and West.", 6, -1, 7, -1, 3, false, 0};
    rooms[7] = {"Final Room", "Surrounding you are colored window panes shining rays of light. It seems you are near the end of the labrynth.\nThere is a door to the North and East.", 7, 6, -1, 8, -1, true, 0};
    rooms[8] = {" ", " ", 8};
  
    cout << "\t\t  Welcome to Text Adventure!\n" << string (65, '-') << endl;
    cout << "\t\t1. Play\t 2. Credits  3. Quit\n";
    cout << string (65, '-') << endl;  
    cout << "Menu Option: ";
    
    do {
        cin >> menuNum;
        if (menuNum < 1 || menuNum > 3) {
            cout << "Invalid menu option. Choose a option 1-3: ";
        }
    }
    while (menuNum < 1 || menuNum > 3);
    
    switch (menuNum){
        case 1: {
        // Specification C2 - Player Name
        cout << "\nEnter a name for your character: ";
        cin >> playerName;
        
        classMenu(classes);
        
        do {
        cin >> classIndex;
        if (classIndex < 1 || classIndex > 4){
            cout << "Invalid class option. Choose an option 1-4: ";
        }
        } while (classIndex < 1 || classIndex > 4);
        
    // Array offset
    classIndex -= 1;
    
    int HP = classes.classHP[classIndex];

    classChoice(classes, classIndex);
    cout << "\nBeginning your Adventure...\n";
    cout << "\nYou are a forgotten warrior. Punished by the king, he sends you into a labyrinth full of dangerous rooms. You step forward and the entrance door shuts behind you.\n";
    cout << "\nControls - W (UP) | S (DOWN) | A (LEFT) | D (RIGHT) | L (LOOK) | ! (HELP) | Q (QUIT)\n\n";
      
    do {  
    // Specification C4 – Abbreviated Room Description
    // Specification A3 - Once the room has been visited already, display a message Specification
    if (skipRoomDesc == false) {
        cout << "Current Room: " << rooms[currentRoomID].room_title << endl;
        if (rooms[currentRoomID].roomCount == 0){
            rooms[currentRoomID].roomCount++;
            cout << "Room Description: " << rooms[currentRoomID].room_description << endl;
          } else {
        cout << "This room seems familiar.\n";
          }
        }
    
    cout << "\nEnter a move: ";
    cin >> move;
    
 // Move the player and update the move count
      if (move == 'W' || move == 'w') {
         if (rooms[currentRoomID].exitCodeN != -1){
                cout << playerName << " begins moving North.\n";
                currentRoomID = rooms[currentRoomID].exitCodeN;
         } else {
                cout << "You can't go that way!" << endl;
         }
         skipRoomDesc = false;
      } 
      
      else if (move == 'S' || move == 's') {
         if (rooms[currentRoomID].exitCodeS != -1){
                  cout << playerName << " begins moving South.\n";
                  currentRoomID = rooms[currentRoomID].exitCodeS;    
         } else {
                    cout << "You can't go that way!" << endl;
         }
         skipRoomDesc = false;
      } 
      
        else if (move == 'A' || move == 'a') {
            if (rooms[currentRoomID].exitCodeW != -1){
                cout << playerName << " begins moving West.\n";
                currentRoomID = rooms[currentRoomID].exitCodeW;
        } else {
                cout << "You can't go that way!" << endl;
        }
         skipRoomDesc = false;
      } 
      
      else if (move == 'D' || move == 'd') {
        if (rooms[currentRoomID].exitCodeE != -1){
            cout << playerName << " begins moving East.\n";
            currentRoomID = rooms[currentRoomID].exitCodeE;
        } else {
            cout << "You can't go that way!" << endl;
         }
        skipRoomDesc = false;
      } 
        // Specification C5 - Detailed Look      
        else if (move == 'L' || move == 'l'){
            cout << "Current Room: " << rooms[currentRoomID].room_title << endl;
            cout << "Room Description: " << rooms[currentRoomID].room_description << endl;
            skipRoomDesc = true;
      } 
      
      else if (move == '!'){
        cout << "\n\nText Adventure is a game where the user moves by typing in the keys:\nW (UP), S (DOWN), A (LEFT), and D (RIGHT).\n\nUsing these keys, navigate through mysterious rooms and fight off monsters that lurk in the darkness.\n\n";
        skipRoomDesc = false;
      } 
      
      else if (move == 'Q' || move == 'q'){
      quit = true;
        
      // Specification C3 - Input Validation
      } else {
      cout << "Invalid input. Please try again." << std::endl;
      skipRoomDesc = true;
    }

    // Checks if a monster has spawned in the room and displays it
    if (rooms[currentRoomID].isOccupied == true){
        bool fightOver = false;
        bool monstAttack = true;
        int index = rand() % numMonsters;
        int monsterHP = m.Health(index);
        cout << "\nA monster appears in the room you're in looking to battle!\n\n";
        m.SelectMonster(index);  
        cout << "\nFight Controls - A (ATTACK) | D (DODGE) | H (HEAL) \n";
        while (fightOver == false) {
            cout << "Current HP: " << HP << endl << "Monster HP: " << monsterHP << endl;
            cout << "\nChoose a fighting move: ";
            cin >> fightMove;
            if (fightMove == 'A' || fightMove == 'a'){
                bool isCrit = false;
                int attackDMG = dmgCalc(classes.classDMG[classIndex], classes.classCrit[classIndex], critDmg, m.monsterDefense[index], isCrit);
                monsterHP = monsterHP - attackDMG;
                
                if (isCrit == true) {
                cout << classes.classAttack[classIndex] << "doing " << attackDMG << " critical damage!\n";
                } else {
                cout << classes.classAttack[classIndex] << "doing " << attackDMG << " damage.\n";
                }
                monstAttack = true;
            }
            
            else if (fightMove == 'D' || fightMove == 'd'){
                bool dodgeSuccess = calcDodge(classes.classDodgeChance[classIndex]);
                if (dodgeSuccess == true) {
                    monstAttack = false; 
                    cout << "Dodge Successful.\n";
                }
                
                else {
                    cout << "Dodge Unsuccessful.\n";
                    monstAttack = true;
                }
            }
            
            
            else if (fightMove == 'H' || fightMove == 'h'){
                HP += classes.classHeal[classIndex];
                if (HP > classes.classHP[classIndex]) {
                    HP = classes.classHP[classIndex];
                    cout << classes.classHealMsg[classIndex] << " healing to full hp!\n";
                }
                
                else {
                cout << classes.classHealMsg[classIndex] << " healing " << HP << " HP.\n";
                }
                monstAttack = true;
            }
            
            else {
                cout << "Invalid move input.\n";
                monstAttack = false;
            }
            
  
            if (monstAttack == true && monsterHP > 0){
                bool isCrit = false;
                int monstDMG = dmgCalc(m.monsterDMG[index], m.monsterCrit[index], critDmg, classes.classDefense[classIndex], isCrit);
                HP -= monstDMG;
                
                if (isCrit == true){
                    m.Combat(index);
                    cout << "doing " << monstDMG << " critical damage!\n";    
                } else {
                    m.Combat(index);
                    cout << "doing " << monstDMG << " damage.\n";
                }
            }

            // Specification A2 - Once a monster has been defeated, no longer display the monster in the room
            if (monsterHP <= 0){
            cout << "You've defeated the monster!\n\n";
            fightOver = true;
            rooms[currentRoomID].isOccupied = false;
            }

            if (HP <= 0){
            cout << "You've been slain by the monster!\n\n";
            fightOver = true;
          }
        }
      }
    
    // Check if player has reached the final room
    if (currentRoomID == 8) {
      cout << "\nCongratulations! You've reached the final room.\n";
      quit = true;
      }
    
    if (HP <= 0) {
      cout << playerName << "has been slain!";
        quit = true;
    }
    } while (quit == false);
        Credits();
    break;
    }
    
    case 2: {
    Credits();
    break;
    }
  
    case 3: {
    cout << "\nYou have quit the game.";
    break;
    }
    
    default: {
        cout << "Invalid menu choice.\n";
        break;
    }
  }
  
  return 0;
}

void Credits(){
  cout << "\nThe Game is now over.f\n";
  cout << "\nGame made by DJ Echipare.\n";
}

void classMenu(const playerClass& p){
    cout << "\nChoose your class:\n";
    for (int i = 0; i < 4; i++) {
        cout << " " << (i + 1) << ". " << p.classType[i] << "\n";
    }
    
    cout << "\nEnter the class number: ";
}

void classChoice(const playerClass& p, int index){
    cout << "\nClass: " << p.classType[index] << endl;
    cout << string (80, '=') << endl;
    cout << "Description: " << p.classDescription[index] << endl;
    cout << p.classStats[index] << endl;
}

int dmgCalc(int baseDMG, int critChance, int critMult, int defenseStat, bool& isCrit){
    double dmgReduc = static_cast<double>(defenseStat) / 100;
    int roll = randomRange(1,100);
    // Crit hit
    if (roll <= critChance) {
        double critDMG = (baseDMG * critMult) * dmgReduc;
        isCrit = true;
        return static_cast<int>(round(critDMG));
    } else {
    double finalDMG = baseDMG * dmgReduc;
    // Normal hit
    return static_cast<int>(round(finalDMG));
    }
}

bool calcDodge(int dodgeStat) {
    bool success = false;
    int roll = randomRange(1,100);
    
    // Successful dodge
    if (roll <= dodgeStat) {
        return success = true;
    }
    
    // Unsuccessful dodge
    return success;
}

int randomRange(int min, int max) {
    static std::mt19937 gen(time(0));
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}