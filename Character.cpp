#include "Character.h"
#include "Entity.h"

// Name: Character() - Default Constructor
// Description: Creates a new character
// Preconditions: None
// Postconditions: Can create a character
Character::Character():Entity(){
  m_topSpeed = 0.0;
  m_handling = 0.0;
  m_acceleration = 0.0;
}
  
// Name: Character(string name) - Overloaded constructor
// Description: Creates a new character (name, top speed, handling, acceleration)
// Preconditions: None
// Postconditions: Can be used to populate character or child classes
Character::Character(string name, double topSpeed, double handling, double acceleration):Entity(name){
  m_topSpeed = topSpeed;
  m_handling = handling;
  m_acceleration = acceleration;
}

// Name: ~Character - Virtual Destructor
// Description: Makes sure everything in child class is deallocated
// Preconditions: None
// Postconditions: Everything dynamically allocated is deallocated
Character::~Character(){

}

// Name: GetCurLocation()
// Description: Returns m_curLocation
// Precondition: Must be populated
// Postcondition: Returns m_curLocation (how far down the track has the racer gone)
double Character::GetCurLocation(){
  return m_curLocation;
}

// Name: SetCurLocation()
// Description: Sets m_curLocation
// Precondition: None
// Postcondition: Sets m_curLocation (how far down the track has the racer gone)
void Character::SetCurLocation(double curLocation){
  m_curLocation += curLocation;
}

// Name: GetCurSpeed()
// Description: Returns m_curSpeed
// Precondition: Must be populated
// Postcondition: Returns m_curSpeed (how fast the racer is going)
double Character::GetCurSpeed(){
  return m_curSpeed;
}

// Name: SetCurSpeed()
// Description: Sets m_curSpeed
// Precondition: Must be populated
// Postcondition: Sets m_curSpeed (does not calculate)
void Character::SetCurSpeed(double curSpeed){
  m_curSpeed = curSpeed;
}

// Name: GetTopSpeed()
// Description: Returns m_topSpeed
// Precondition: Must be populated
// Postcondition: Returns m_topSpeed (What is the top speed of the racer - provided)
double Character::GetTopSpeed(){
  return m_topSpeed;
}

// Name: GetHandling()
// Description: Returns m_handling
// Precondition: Must be populated
// Postcondition: Returns m_handling (How well can the racer steer? - provided)
double Character::GetHandling(){
  return m_handling;
}

// Name: GetAcceleration()
// Description: Returns m_acceleration
// Precondition: Must be populated
// Postcondition: Returns m_acceleration (How fast can the racer accelerate?)
double Character::GetAcceleration(){
  return m_acceleration;
}

// OPTIONAL: EXTRA CREDIT
// DO NOT EDIT UNTIL YOU HAVE COMPLETED BASE PROJECT
// Name: SpecialMove()
// Description: Allows the child class to do a special move
// Precondition: Must be implemented in the child class
// Postcondition: Modifies something (think star, turbo, or something else interesting - MUST DO SOMETHING OTHER THAN JUST OUTPUT!)
void Character::SpecialMove(){

}

// Name: CalcSpeed
// Description: Calculates the current speed based on some rules described in project document
// Precondition: Must be populated
// Postcondition: Sets m_curSpeed
void Character::CalcSpeed(double gas){
  int speed = m_curSpeed;
  if (m_curSpeed < m_topSpeed){
    speed += m_acceleration * m_handling;
    if (m_curSpeed > m_topSpeed){
      speed = m_topSpeed;
    }
  }
  SetCurSpeed(speed * gas);
}

// Name: Tick
// Description: Checks to see if the racer crashes
// Precondition: m_curSpeed must be calculated and passed maximum speed of track
// Postcondition: May update m_curSpeed to 0 if there is a crash
void Character::Tick(double maxSpeed){
  if (m_curSpeed <= maxSpeed){
    cout << "Crash occured!!" << endl;
    SetCurSpeed(0);
  }
}
