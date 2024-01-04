#ifndef FOLLOW_H_
#define FOLLOW_H_

#include "Notification.h"

// class follow derived from class notification
class Follow : public Notification {
public:
	// constructor calls parent constructor Notification()
	Follow(std::string u) : Notification(u) {};
	
	// getClassName() returns the name of the class
	std::string getClassName() const { return "Follow"; };
	
	// returns the notification to be pushed
	std::string print() const;
};

#endif