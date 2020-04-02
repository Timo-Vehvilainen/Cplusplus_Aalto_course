#include "gcourse.hh"
#include <numeric>

  
using namespace std;
  
GolfCourse::GolfCourse(const string& name, const vector<GolfHole>& holes,
            const map<pair<Gender, TeeColor>, pair<double, size_t> >& difficulty) :
            name(name), holes(holes), difficulty(difficulty) {}
  
const string& GolfCourse::getName() const {
    return name;
}
  
const vector<GolfHole>& GolfCourse::getHoles() const {
    return holes;
}
  
size_t GolfCourse::getPar() const {
    size_t sum = 0;
    vector<GolfHole>::const_iterator hole = holes.begin();
    while (hole != holes.end()) {
        sum += (hole->getPar());
        hole++;
    }
    return sum;
}
  
const pair<double, size_t>& GolfCourse::getDifficulty(Gender gender, TeeColor teeColor) const {
    pair<Gender, TeeColor> newPair (gender, teeColor);   
    return ((difficulty.find(newPair))->second);
}
  
istream& operator>> (istream& in, GolfCourse& course) {
  
    getline(in, course.name);
  
    int hole = 0;
    while (hole < 18) {
        GolfHole newHole;
        in >> newHole;
        (course.holes).push_back(newHole);
        hole++;
    }
  
    int gender;
    int color;
    double cr;
    size_t slope;
  
    for (gender = 0; gender < 2; gender++) {
        for (color = 0; color < 4; color++) {
            pair<Gender, TeeColor> newFirstPair ((Gender) gender, (TeeColor) color);
            in >> cr >> slope;
            pair<double, size_t> newSecondPair (cr, slope);
            course.difficulty[newFirstPair] = newSecondPair;
        }
    }
    return in;
}
