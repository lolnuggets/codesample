#ifndef POST_H_
#define POST_H_

#include <iostream>
#include <string>

// class to hold data for the post
class Post {
public:
	
	// initializes a post object with only one json line provided by the input file
	Post(std::string input);
	Post() {};

	// main accessors
	std::string getId() const { return id; };
	std::string getUserId() const { return userid; };

private:

	// all memeber variables
	std::string id, userid;
};

#endif