#include "Social.h"

int main(int argc, char *argv[]) {

	// first guard, correct arg count
	if (argc != 4) {
		std::cerr << "Invalid arguments." << std::endl;
		exit(1);
	}

	// constant vars from the argument
	const std::string input = argv[1];
	const std::string output = argv[2];
	const std::string command = argv[3];

	std::ofstream ofile(output);

	// simple guard to ensure file opens
	if (!ofile.is_open()) {
		std::cerr << "Error opening output file." << std::endl;
		return 1;
	}

	// initialization of main object & result stringstream
	Social tiktok(input);
	std::stringstream result;

	// try throw catch guard for command
	try {
		if (command == "sound") {
			result = tiktok.getSounds();
		} else if (command == "hashtag") {
			result = tiktok.getHashtags();
		} else {
			throw std::invalid_argument("Argument not recognized");
		}
	} catch (...) {
		std::cerr << "Error reading command." << std::endl;
		return 1;
	}

	// output and closing open files
	ofile << result.str();
	ofile.close();
}