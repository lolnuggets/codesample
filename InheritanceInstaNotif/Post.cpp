#include "Post.h"

/*
 * Post() takes in a string as input this string would be a signle
 * line from a json file which contains all information for a single
 * post. It then saturates all NECESSARY variables for the assignment.
 * Additional variables were created and unused functions incase they
 * were necessary. However they are NOT used due to memory optimization
 */
Post::Post(std::string input) {

	// main used variables
	size_t pos;			// position of start of data for item
	std::string cur;	// text from searched item
	std::string item;	// item to search for

	item = "id";
	pos = input.find("\""+item+"\"")+4+item.length();
	if (pos == std::string::npos)
		throw std::invalid_argument("Invalid argument in posts file.");
	cur = input.substr(pos, input.find("\"", pos)-pos);
	id = cur;

	item = "ownerId";
	pos = input.find("\""+item+"\"")+4+item.length();
	if (pos == std::string::npos)
		throw std::invalid_argument("Invalid argument in posts file.");
	cur = input.substr(pos, input.find("\"", pos)-pos);
	userid = cur;
}