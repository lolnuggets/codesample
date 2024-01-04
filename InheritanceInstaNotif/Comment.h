#ifndef COMMENT_H_
#define COMMENT_H_

#include "Notification.h"

// class comment derived from class notification
class Comment : public Notification {
public:
	// constructor calls parent constructor Notification()
	Comment(std::string u) : Notification(u) {};
	
	// getClassName() returns the name of the class
	std::string getClassName() const { return "Comment"; };
	
	// returns the notification to be pushed
	std::string print() const;
};

#endif