#ifndef EVENTCONTAINER_H_
#define EVENTCONTAINER_H_

#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <stack>

#include "Like.h"
#include "Comment.h"
#include "Follow.h"
#include "Message.h"
#include "Tag.h"
#include "User.h"
#include "Post.h"

// class event container holds all events
class EventContainer {
public:

	// constructor
	EventContainer(std::string userfile, std::string postfile, std::string eventfilename, std::string target);

	// getter function
	std::string getResult();
private:

	// private variables field
	std::unordered_map<std::string, User> users;
	std::unordered_map<std::string, Post> posts;

	std::stack<Notification*> events;
	std::unordered_map<std::string, int> linemap;
};

#endif