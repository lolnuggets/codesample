#include "EventContainer.h"

int main(int argc, char *argv[]) {

	// first guard, correct arg count
	if (argc != 6) {
		std::cerr << "Invalid arguments." << std::endl;
		exit(1);
	}

	// constant vars from the argument
	const std::string postsjson = argv[1];
	const std::string usersjson = argv[2];
	const std::string eventstxt = argv[3];
	const std::string outputtxt = argv[4];
	const std::string username = argv[5];

	// guard for main object. exceptions are thrown throughout code
	try {
		// create the event container object & open output file
		EventContainer instaevents(usersjson, postsjson, eventstxt, username);
		std::ofstream file(outputtxt);

		// put the results into the output file
		file << instaevents.getResult();
		file.close();
	} catch (const std::exception& e) {
		std::cerr << "Error getting events: " << e.what() << std::endl;
	}
}