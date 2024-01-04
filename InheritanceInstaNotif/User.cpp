#include "User.h"

/*
 * Post() takes in a string as input this string would be a signle
 * line from a json file which contains all information for a single
 * post. It then saturates all NECESSARY variables for the assignment.
 * Additional variables were created and unused functions incase they
 * were necessary. However they are NOT used due to memory optimization
 */
User::User(std::string input) {

	// main used variables
	size_t pos;			// position of start of data for item
	std::string cur;	// text from searched item
	std::string item;	// item to search for

	item = "id";
	pos = input.find("\""+item+"\"")+5+item.length();
	if (pos == std::string::npos)
		throw std::invalid_argument("Invalid argument in users file.");
	cur = input.substr(pos, input.find("\"", pos)-pos);
	id = cur;

	item = "username";
	pos = input.find("\""+item+"\"")+5+item.length();
	if (pos == std::string::npos)
		throw std::invalid_argument("Invalid argument in users file.");
	cur = input.substr(pos, input.find("\"", pos)-pos);
	username = cur;

	item = "pauseAll";
	pos = input.find("\""+item+"\"")+5+item.length();
	if (pos == std::string::npos)
		throw std::invalid_argument("Invalid argument in users file.");
	cur = input.substr(pos, input.find("\"", pos)-pos);
	if (cur == "true")
		notification = false;
	else
		notification = true;

	item = "likes";
	pos = input.find("\""+item+"\"")+5+item.length();
	if (pos == std::string::npos)
		throw std::invalid_argument("Invalid argument in users file.");
	cur = input.substr(pos, input.find("\"", pos)-pos);
	if (cur == "true")
		like = true;
	else
		like = false;

	item = "tags";
	pos = input.find("\""+item+"\"")+5+item.length();
	if (pos == std::string::npos)
		throw std::invalid_argument("Invalid argument in users file.");
	cur = input.substr(pos, input.find("\"", pos)-pos);
	if (cur == "true")
		tag = true;
	else
		tag = false;

	item = "comments";
	pos = input.find("\""+item+"\"")+5+item.length();
	if (pos == std::string::npos)
		throw std::invalid_argument("Invalid argument in users file.");
	cur = input.substr(pos, input.find("\"", pos)-pos);
	if (cur == "true")
		comment = true;
	else
		comment = false;

	item = "newFollowers";
	pos = input.find("\""+item+"\"")+5+item.length();
	if (pos == std::string::npos)
		throw std::invalid_argument("Invalid argument in users file.");
	cur = input.substr(pos, input.find("\"", pos)-pos);
	if (cur == "true")
		follow = true;
	else
		follow = false;

	item = "messageRequests";
	pos = input.find("\""+item+"\"")+5+item.length();
	if (pos == std::string::npos)
		throw std::invalid_argument("Invalid argument in users file.");
	cur = input.substr(pos, input.find("\"", pos)-pos);
	if (cur == "true")
		message = true;
	else
		message = false;
}