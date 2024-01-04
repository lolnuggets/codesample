#ifndef USER_H_
#define USER_H_

#include <iostream>
#include <string>

// class to hold data for the post
class User {
public:
	
	// initializes a post object with only one json line provided by the input file
	User(std::string input);
	User() {};

	// main accessors
	std::string getId() const { return id; };
	std::string getUsername() const { return username; };

	bool getNotification() const { return notification; }
	bool getLike() const { return like; }
	bool getTag() const { return tag; }
	bool getComment() const { return comment; }
	bool getFollow() const { return follow; }
	bool getMessage() const { return message; }
private:

	// all memeber variables
	std::string id, username;
	bool notification, like, tag, comment, follow, message;
};

#endif