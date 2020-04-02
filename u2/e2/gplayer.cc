#include "gplayer.hh"
  
using namespace std;
  
size_t GolfPlayer::idCounter = 0;
 
GolfPlayer::GolfPlayer(const string& name, Gender gender, double handicap) :
    name(name), gender(gender), handicap(handicap), id(idCounter++) {}
  
 
  
const string& GolfPlayer::getName() const {
    return name;
}
  
Gender GolfPlayer::getGender() const {
    return gender;
}
  
double GolfPlayer::getHandicap() const {
    return handicap;
}
  
void GolfPlayer::setHandicap(double newHandicap) {
    handicap = newHandicap;
    return;
}
  
size_t GolfPlayer::getId() const {
    return id;
}
  
  
  
ostream& operator<< (std::ostream& out, const GolfPlayer& player) {
    out << "Player information:" << endl;
    out << "Id: " << player.id << endl;
    out << "Name: " << player.name << endl;
    if (player.gender == MALE)
        out << "Gender: male" << endl;
    else
        out << "Gender: female" << endl;
    out << "Handicap: " << player.handicap;
    return out;
}
