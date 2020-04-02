#include "gscore.hh"

#include <fstream>
#include <iostream>

int main(void) {

	// Initialize two golf players
	std::cout << "*** Creating two golf players.." << std::endl;
	GolfPlayer petteri("Petteri Koivumaki", MALE, -7.5);
	GolfPlayer raimo("Raimo Nikkila", MALE);

	std::cout << "*** Printing out the players' information.." << std::endl;
	std::cout << petteri << std::endl;
	std::cout << raimo << std::endl;

	// Read a golf course from a file
	std::cout << "*** Reading a golf course from a file.." << std::endl;
	GolfCourse sarfvik;
	std::ifstream file;
	file.open("sarfvik.txt");

	if (file.is_open()) {
		file >> sarfvik;
		file.close();
	}
	else {
		std::cout << "Unable to open file" << std::endl;
		return 1; // EXIT_FAILURE
	}

	// Initialize two golf score cards, one for each player
	std::cout << "*** Creating two golf score cards, one for each player.." << std::endl;
	GolfScoreCard petteriScore(petteri, sarfvik, WHITE);
	GolfScoreCard raimoScore(raimo, sarfvik, RED);

	std::cout << "*** Updating the players' results on the score cards.." << std::endl;
	size_t petteriResults[18] = {7, 6, 3, 10, 6, 4, 4, 5, 5, 6, 8, 7, 6, 8, 4, 4, 5, 5};
	for (size_t i = 0; i < 18; i++)
		petteriScore.addResult(petteriResults[i]);

	size_t raimoResults[18] = {0, 9, 3, 12, 6, 7, 9, 10, 7, 5, 9, 0, 6, 8, 6, 6, 8, 9};
	for (size_t i = 0; i < 18; i++)
		raimoScore.addResult(raimoResults[i]);

	// Calculate the total points
	std::cout << "Total points for " << petteri.getName() << ": " << petteriScore.getTotalPoints() << std::endl;
	std::cout << "Total points for " << raimo.getName() << ": " << raimoScore.getTotalPoints() << std::endl;

	std::cout << "*** Printing out the full score statistics.." << std::endl;
	std::cout << petteriScore << std::endl;
	std::cout << raimoScore << std::endl;

	std::cout << "*** All done, exiting.." << std::endl;
	return 0; // EXIT_SUCCESS
}
