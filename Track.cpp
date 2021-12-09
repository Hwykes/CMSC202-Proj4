#include "Track.h"

// Name: Track
// Precondition: None
// Postcondition: Creates a new empty track
Track::Track(){
    m_name = "";
    m_desc = "";
    m_totalLength = 0;
}
//Track Destructor
Track::~Track(){
    
}
// Name: LoadTrack(string fileName);
// Description: Creates a piece of track from each line from input file
// Precondition: m_filename is valid
// Postcondition: Actually loads the track based on m_filename
void Track::LoadTrack(string fileName){
    string trackName, trackDesc, length, pieceDesc, numBox, max;
    const char DELIMITER = '|';
    m_fileName = fileName;
    ifstream myFile(m_fileName);
    if(myFile.is_open()){
        cout << "Opened File" << endl;
        if (m_fileName == "proj4_track1.txt"){
            cout << "1" << endl;
        }
        else if (m_fileName == "proj4_track2.txt"){
            cout << "2" << endl;
        }
        else if (m_fileName == "proj4_track3.txt"){
            cout << "3" << endl;
        }
        getline(myFile, trackName);
        m_name = trackName;
        getline(myFile, trackDesc);
        m_desc = trackDesc;
        while (myFile){
            getline(myFile, length, DELIMITER);
            getline(myFile, pieceDesc, DELIMITER);
            getline(myFile, numBox, DELIMITER);
            getline(myFile, max);
            if (length.size() > 0){
                int lengthNum = stoi(length, nullptr);
                int numBoxNum = stoi(numBox, nullptr);
                int maxNum = stoi(max, nullptr);
                Piece* newPiece = new Piece(lengthNum, pieceDesc, numBoxNum, maxNum);
                m_track.push_back(newPiece);
                m_totalLength += lengthNum;
            }
        }
    }
    else{
        cout << "Unable to open file" << endl;
    }
    myFile.close();
}
// Name: GetPiece (int)
// Description: At a specific distance, the corresponding index of the piece is returned
// For example, if 300 is passed, iterates through vector adding distance until 300 is reached
// If next piece of the track exceeds the end, returns the end
// Precondition: Must have valid track and provided distance
// Postcondition: Travels through track to described distance
int Track::GetPiece(int distance){
    int position = 0;
    int index = 0;
    while (position < distance){
        position += m_track[index]->m_length;
        index++;
        if (index > (int)m_track.size()){
            return index - 1;
        }
    }
    return index;
}
// Name: DisplayPiece
// Description: At a specific index, returns the m_desc from a particular piece of track
// Precondition: Track loaded and a valid index passed
// Postcondition: Returns id of track in that direction if the exit exists
void Track::DisplayPiece(int index){
    if (index != (int)m_track.size()){
        cout << m_track[index]->m_desc << endl;
    }
    else if (index > (int)m_track.size()){
        cout << m_track[(int)m_track.size()]->m_desc << endl;
    }
    
}
// Name: GetMaxSpeed
// Description: At a specific index, returns the m_maxSpeed from a particular piece of track
// Precondition: Track loaded and a valid index passed
// Postcondition: Returns double which is max speed before racer crashes
double Track::GetMaxSpeed(int index){
    double maxSpeed = (double)m_track[index]->m_maxSpeed;
    return maxSpeed;
}
// Name: GetTotalLength()
// Description: Returns m_totalLength
// Precondition: Track loaded
// Postcondition: Returns int for totallength
int Track::GetTotalLength(){
    return m_totalLength;
}
// Name: GetDesc()
// Description: Returns m_desc
// Precondition: Track loaded
// Postcondition: Returns desc
string Track::GetDesc(){
    return m_desc;
}
