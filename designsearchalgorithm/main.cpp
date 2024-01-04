#include "Engine.h"

int main(int argc, char *argv[]) {

	// first guard, correct arg count
	if (argc < 4 || argc > 6) {
		std::cerr << "Invalid arguments." << std::endl;
		return 1;
	}

	// constant vars from the argument
	const std::string index = argv[1];
	const std::string output = argv[2];

	// phrase to be edited
	std::string phrase = "";

	// file operations
	std::ofstream ofile(output);

	if (!ofile.is_open()) {
		std::cerr << "Error opening output file." << std::endl;
		return 1;
	}

	// amalgamating the arguments
	for(int i = 3; i < argc; i++) {
		if (i != 3)
			phrase += " ";
		phrase += argv[i];
	}

	// engine instansiation/functions
	Engine search(phrase, index);
	search.crawl();
	search.scorepages();

	// output to file
	if (search.getRelevant().size() != 0) {
		ofile << "Matching documents: " << std::endl;
		for (Document docn : search.getRelevant())
			ofile << std::endl << docn;
	} else
		ofile << "Your search - " << phrase << " - did not match any documents." << std::endl;

	ofile.close();
	return 0;
}