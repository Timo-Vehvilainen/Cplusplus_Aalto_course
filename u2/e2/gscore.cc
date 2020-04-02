#include "gscore.hh"
#include <cmath>
#include <algorithm>
#include <numeric>
  
using namespace std;
  
GolfScoreCard::GolfScoreCard(const GolfPlayer& player, const GolfCourse& course, TeeColor teeColor) :
        player(player), course(course), teeColor(teeColor) { }
  
const GolfPlayer& GolfScoreCard::getPlayer() const {
    return player;
}
  
const GolfCourse& GolfScoreCard::getCourse() const {
    return course;
}
  
TeeColor GolfScoreCard::getTeeColor() const {
    return teeColor;
}
  
void GolfScoreCard::addResult(size_t result) {
    if (resultsPerHole.size() < 18)
        resultsPerHole.push_back(result);
    return;
}
  
const vector<size_t>& GolfScoreCard::getResultsPerHole() const{
    return resultsPerHole;
}
  
void increment(size_t& value) {
    value++;
    return;
}
  
  
void decrement(size_t& value) {
    value--;
    return;
}
  
vector<size_t> GolfScoreCard::getPointsPerHole() const {
      
    pair<double, size_t> crSlope =  course.getDifficulty(player.getGender(), teeColor);
  
    size_t parSum = course.getPar();
  
    double courseHandicap = (player.getHandicap() * ((crSlope.second) / 113.0)) + (crSlope.first - parSum);
    courseHandicap = (int) (round(courseHandicap));
  
    vector<GolfHole>::iterator hcpIt;
    vector<size_t> parPerHole;
    vector <GolfHole> holes = course.getHoles();
 
    for (hcpIt = holes.begin(); hcpIt != holes.end(); hcpIt++)
        parPerHole.push_back(hcpIt->getPar());
      
    int holeNumber = 1;
  
    while (courseHandicap != 0) {
        if (courseHandicap >= 18) {
            for_each(parPerHole.begin(), parPerHole.end(), increment);
            courseHandicap -= 18;
        } else if (courseHandicap < 18 && courseHandicap > 0) {
            for (size_t i = 1; i <= courseHandicap; i++) {
        	holeNumber = 1;
                for (hcpIt = holes.begin(); hcpIt != holes.end(); hcpIt++) {
                    if ((hcpIt->getHcp()) == i) {
                        parPerHole[holeNumber - 1]++;
		    }
                    holeNumber++;
                }
            }
            courseHandicap = 0;
        } else if (courseHandicap < 0 && courseHandicap > (-18)){
            for (size_t i = 18; i > (18 + courseHandicap); i--) {
        	holeNumber = 1;
                for (hcpIt = holes.begin(); hcpIt != holes.end(); hcpIt++) {
                    if ((hcpIt->getHcp()) == i){
                        parPerHole[holeNumber - 1]--;
		    }
                    holeNumber++;
                }
            }
            courseHandicap = 0;
        } else {
            for_each(parPerHole.begin(), parPerHole.end(), decrement);
            courseHandicap -= 18;
        }
    }
    vector<size_t> pointsPerPar;
    for (holeNumber = 0; holeNumber < 18; holeNumber++) {
	if (resultsPerHole[holeNumber] == 0)
		pointsPerPar.push_back(0);
        else if (resultsPerHole[holeNumber] == parPerHole[holeNumber])
            pointsPerPar.push_back(2);
        else if (resultsPerHole[holeNumber] < parPerHole[holeNumber])
            pointsPerPar.push_back(2 + (parPerHole[holeNumber]-resultsPerHole[holeNumber]));
        else if (resultsPerHole[holeNumber] == (parPerHole[holeNumber] + 1))
            pointsPerPar.push_back(1);
        else
            pointsPerPar.push_back(0);
    }
    return pointsPerPar;
}
  
size_t GolfScoreCard::getTotalPoints() const {
 
    vector<size_t> points = getPointsPerHole();
    return (accumulate(points.begin(), points.end(), 0));
}
  
ostream& operator<< (ostream& out, const GolfScoreCard& scoreCard) {
    out << scoreCard.player << endl;
    out << "Course: " << (scoreCard.course).getName() << endl;
    out << "Tee color: ";
    if (scoreCard.teeColor == RED) out << "red" << endl;
    else if (scoreCard.teeColor == BLUE) out << "blue" << endl;
    else if (scoreCard.teeColor == YELLOW) out << "yellow" << endl;
    else out << "white"<< endl;
      
    vector <size_t> pointsPerHole = scoreCard.getPointsPerHole();
    vector <size_t> resultsPerHole = scoreCard.getResultsPerHole();
  
    vector<GolfHole> holes = (scoreCard.course).getHoles();
  
    for (int id = 0; id < 18; id++) {
        out << "Hole " << (id + 1) << ": ";
        out << (holes[id]).getPar() << "/";
        out << (holes[id]).getHcp() << "/";
	if (resultsPerHole[id] == 0)
		out << "-/";
	else
        	out << resultsPerHole[id] << "/";
        out << pointsPerHole[id] << endl;      
    }
    out << "Total points: " << scoreCard.getTotalPoints();
    return out;
}
