#include "Toad.h"
#include "Character.h"

// Name: Toad() - Default Constructor
// Description: Creates a new Toad
// Preconditions: None
// Postconditions: Can create a Toad
Toad::Toad():Character(){

}
// Name: Toad(string name)
// Description: Creates a new Toad
// Preconditions: None
// Postconditions: Can create a Toad
Toad::Toad(string name, double topSpeed, double handling, double acceleration):Character(name, topSpeed, handling, acceleration){
    
}
// Name: ~Toad - Virtual Destructor
// Description: Makes sure everything in child class is deallocated
// Preconditions: None
// Postconditions: Everything dynamically allocated is deallocated
Toad::~Toad(){

}

// OPTIONAL: EXTRA CREDIT
// Name: SpecialAttack
// Description: Defines the Toad's special attack (up to you what it does)
// Preconditions: None
// Postconditions: Does something (think turbo, star etc. Must do something other than just changing output!)
void Toad::SpecialMove(){

}

// Name: GetType
// Description: Returns the name of the object type (Toad in this case)
// Precondition: Must be populated
// Postcondition: Returns m_type (used to output)
string Toad::GetType(){
    return "Toad";
}

// Name: Overloaded << operator
// Description: Returns information about the racer
// Precondition: Must be populated
// Postcondition: Returns something like Toad (J) has gone 348 meters and is currently going 80 m/s
// Usage is *m_Racers.at(i) << cout << endl;
//ostream& operator<<(ostream& output, Character &C);

