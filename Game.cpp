#include "Game.h"
#include "Track.h"
#include "Entity.h"
#include "Mario.h"
#include "Wario.h"
#include "Toad.h"
#include "Obstacle.h"
#include "Banana.h"
#include "Shell.h"

// Name: Game() - Default Constructor
// Description: Creates a new Game. Welcomes player to UMBC Mario Kart. Initializes laps and racers to 1
// Preconditions: None
// Postconditions: m_numLaps and m_numRacers initialized to 1
Game::Game(){
    cout << "************Welcome to UMBC Mario Kart*************" << endl;
    cout << endl;
    m_numLaps = 1;
    m_numRacers = 1;
    RaceSetup();
    StartRace();
}
// Name: ~Game
// Description: Destructor
// Preconditions: None
// Postconditions: Deallocates anything dynamically allocated in Game
Game::~Game(){

}
// Name: LoadTrack
// Description: Asks user which track to use (1-3)
//              Calls LoadTrack for use in myTrack
//              If three laps then the same track is loaded three times
// Precondition: Files must exist. m_numLaps must be populated
// Postcondition: myTrack is populated with track Pieces
void Game::LoadTrack(){
    int trackNum = 0;
    while (trackNum > 3 || trackNum < 1){
        cout << "Which track would you like to use? ";
        cin >> trackNum;
    }
    for (int i = 0; i < m_numLaps; i++){
        myTrack.LoadTrack(TRACK[trackNum - 1][1]);
    }
}
// Name: RaceSetup
// Description: Asks the user for their name and stores it in local variable
//              Allows user to choose which racer to use (Mario, Wario, or Toad) using provided name
//              Allows the user to choose how many other racers to use (no limit) - Randomly assigned (can be duplicates)
//              Allows the user to choose how many laps to race (no limit)
// Preconditions: None
// Postconditions: m_Racers populated with racers, m_numLaps populated
void Game::RaceSetup(){
    string name;
    int racerChoice = 0;
    int numLaps = 0;
    int numCompetitors = 0;
    cout << "What is your name? ";
    cin >> name;
    m_playerName = name;
    while (racerChoice > 3 || racerChoice < 1){
        cout << "Select a Racer \n1. Toad \n2. Wario \n3. Mario" << endl;
        cin.ignore();
        cin >> racerChoice;
    }
    if (racerChoice == 1){
        Entity* newToad = new Toad(m_playerName, TOAD_STATS[0], TOAD_STATS[1], TOAD_STATS[2]);
        m_Racers.push_back(newToad);
    }
    if (racerChoice == 2){
        Entity* newWario = new Wario(m_playerName, WARIO_STATS[0], WARIO_STATS[1], WARIO_STATS[2]);
        m_Racers.push_back(newWario);
    }
    if (racerChoice == 3){
        Entity* newMario = new Mario(m_playerName, MARIO_STATS[0], MARIO_STATS[1], MARIO_STATS[2]);
        m_Racers.push_back(newMario);
    }
    while (numCompetitors < 1){
        cout << "How many other competitors would you like? ";
        cin.ignore();
        cin >> numCompetitors;
    }
    m_numRacers += numCompetitors;
    for (int i = 1; i < m_numRacers; i++){
        int cpuChoice = 1 + (rand() % 3); 
        string name = "CPU";
        if (cpuChoice == 1){
            Entity* newToad = new Toad(name, TOAD_STATS[0], TOAD_STATS[1], TOAD_STATS[2]);
            m_Racers.push_back(newToad);
        }
        if (cpuChoice == 2){
            Entity* newWario = new Wario(name, WARIO_STATS[0], WARIO_STATS[1], WARIO_STATS[2]);
            m_Racers.push_back(newWario);
        }
        if (cpuChoice == 3){
            Entity* newMario = new Mario(name, MARIO_STATS[0], MARIO_STATS[1], MARIO_STATS[2]);
            m_Racers.push_back(newMario);
        }
    }
    while (numLaps < 1){
        cout << "How many laps would you like to complete for the race? ";
        cin.ignore();
        cin >> numLaps;
    }
    m_numLaps = numLaps;
    LoadTrack();  
}
// Name: StartRace()
// Description: As long as the race isn't over or the user hasn't quit repeat these:
//              Displays current position in track for user
//              Shows round number
//              Displays current piece description on track
//              Displays the next piece description on track (like what is ahead)
//              Makes computer racers randomly choose a speed for this round (100%, 75%, 50%, 25%)
//              Tick (passing max speed)
//              Reorder vector based on who has moved the most down the track (m_curLocation)
//              Display the order
// Preconditions: LoadTrack and RaceSetup must have been completed
// Postconditions: Continues until race is over. If completed, displays result (who won)
void Game::StartRace(){
    int const MAXSPEED = 1.0;
    int const PRETTYFAST = 0.75;
    int const FAST = 0.5;
    int const SLOW = 0.25;
    for (int i = 0; i < (int)m_Racers.size(); i++){
        m_Racers[i]->SetCurLocation(0.0);
        m_Racers[i]->SetCurSpeed(0.0);
    }
    int roundNum = 1;
    int choice = 0;
    bool finished = CheckFinish();
    cout << "You will be racing " << m_numLaps << " laps" << endl;
    cout << "The total length of the race is " << myTrack.GetTotalLength()*m_numLaps << " meters." << endl;
    myTrack.DisplayPiece(0);
    cout << endl;
    cout << "*********ON YOUR MARKS*********\n\n*********GET SET*********\n\n*********GO! GO! GO!*********\n" << endl;
    cout << "You currently see:" << endl;
    myTrack.DisplayPiece(0);
    while (choice != 6 && finished == false){
        while (choice < 1 || choice > 6){
            choice = Action();
        }
        if (choice != 6){
            int playerLocation = m_Racers[0]->GetCurLocation();
            int playerPiece = myTrack.GetPiece(playerLocation);
            cout << "You currently see: " << endl;
            myTrack.DisplayPiece(playerPiece);
            cout << "Ahead is:" << endl;
            myTrack.DisplayPiece(playerPiece+1);
            cout << endl;
            cout << "************************\nRound : " << roundNum << "\n************************" << endl;
            choice = Action();
            if (choice == 1){
                m_Racers[0]->CalcSpeed(MAXSPEED);
                CpuRandom();
                for (int i = 0; i < m_numRacers; i++){
                    m_Racers[i]->SetCurLocation(m_Racers[i]->GetCurSpeed());
                }
            }
            else if (choice == 2){
                m_Racers[0]->CalcSpeed(PRETTYFAST);
                CpuRandom();
                for (int i = 0; i < m_numRacers; i++){
                    m_Racers[i]->SetCurLocation(m_Racers[i]->GetCurSpeed());
                }
            }
            else if (choice == 3){
                m_Racers[0]->CalcSpeed(FAST);
                CpuRandom();
                for (int i = 0; i < m_numRacers; i++){
                    m_Racers[i]->SetCurLocation(m_Racers[i]->GetCurSpeed());
                }
            }
            else if (choice == 4){
                m_Racers[0]->CalcSpeed(SLOW);
                CpuRandom();
                for (int i = 0; i < m_numRacers; i++){
                    m_Racers[i]->SetCurLocation(m_Racers[i]->GetCurSpeed());
                }
            }
            finished = CheckFinish();
            roundNum++;
            Display();
        }
    }
    cout << "The race is over!" << endl;

}
// Name: CheckFinish
// Description: Checks to see if any racer has exceeded total length of the track
// Precondition: m_Racers has been populated and myTrack has been populated
// Postcondition: Returns true if race is over; else false
bool Game::CheckFinish(){
    bool finished = false;
    for (int i = 0; i < m_numRacers; i++){
        if (m_Racers[i]->GetCurLocation() > myTrack.GetTotalLength()){
            finished = true;
        }
    }
    return finished;
}
// Name: CpuRandom
// Description: Iterates over all computer m_Racers and uses CalcSpeed to randomly assign either (100%, 75%, 50%, 25%)
// Precondition: m_Racers has been populated
// Postcondition: Using CalcSpeed, updates racer's speeds
void Game::CpuRandom(){
    for (int i = 1; i < (int)m_Racers.size(); i++){
        if (m_Racers[i]->GetName() != m_playerName){
            int speedMod = 1+(rand() % 4);
            if (speedMod == 1){
                m_Racers[i]->CalcSpeed(0.25);
            }
            if (speedMod == 2){
                m_Racers[i]->CalcSpeed(0.50);
            }
            if (speedMod == 3){
                m_Racers[i]->CalcSpeed(0.75);
            }
            if (speedMod == 4){
                m_Racers[i]->CalcSpeed(1);
            }
        }
    }
}
// Name: Tick
// Description: Iterates over all computer m_Racers and calls Tick and passes the maxSpeed of the current piece of track that racer is on
// Precondition: m_Racers has been populated and myTrack has been populated
// Postcondition: Checks to see if the racer crashes by exceeding the max limit of that track piece
void Game::Tick(double maxSpeed){
    for (int i = 0; i < m_numRacers; i++){
        m_Racers[i]->Tick(myTrack.GetMaxSpeed(m_Racers[i]->GetCurLocation()));
    }
}
// Name: Order
// Description: Uses a simple bubble sort (nested for loops) to reorder who has traveled the farthest
// Precondition: m_Racers has been populated
// Postcondition: m_Racers is sorted from highest distance traveled to lowest distance traveled
void Game::Order(){
    for (int i = 0; i < (int)m_Racers.size(); i++){
        for (int j = i+1; j < (int)m_Racers.size(); j++){
            if (i != (int)m_Racers.size()){
                if (m_Racers[i]->GetCurLocation() > m_Racers[i+1]->GetCurLocation()){
                    Entity* temp = m_Racers[i];
                    m_Racers[i] = m_Racers[i+1];
                    m_Racers[i+1] = temp;
                }
            } 
        }
    }
}
// Name: Attack
// Description: Optional-extra credit
//              Uses obstacles to make things crash. Uses bananas to make racers crash behind the user
//              Uses shells to crash racers ahead.
//              Can only attempt after the base project is completed
//              Can add additional member functions and variables to make this functionality work
//void Game::Attack();

// Name: Display
// Description: Displays each racer in m_Racers by using overloaded << operator
// Precondition: m_Racers has been populated
// Postcondition: Usage is *m_Racers.at(i) << cout << endl;
void Game::Display(){
    cout << "************************" << endl;
    for (int i = 0; i < m_numRacers; i++){
        cout << m_Racers[i]->GetType() << " (" << m_Racers[i]->GetName() << ") has gone "\
        << m_Racers[i]->GetCurLocation() << " meters and is currently going "\
        << m_Racers[i]->GetCurSpeed() << " m/s" << endl;
    }
    cout << "************************" << endl;

}
// Name: Tick
// Description: Iterates over all racers in m_Racers to return the index of where the player's racer exists (after sort)
// Precondition: m_Racers has been populated and sort has been called
// Postcondition: Returns the index of where the player's racer exists
int Game::FindPlayer(){
    return 0;
}
// Name: Action()
// Description: Menu for game
//              Required to implement cases 1-4 and 6.
//              Choice 5 (Attack) is optional and is part of the extra credit
//              Asks the user if they want to change their speed
// Preconditions: Everything in start has been completed
// Postconditions: Game continues until someone finishes race
int Game::Action(){
    int choice = 0;
    cout << "What would you like to do? \n1. Max Speed \n2. Pretty Fast \n3. Fast \n4. Slow \n6. Quit" << endl;
    cin >> choice;
    return choice;
}