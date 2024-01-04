#ifndef MESSAGE_H_
#define MESSAGE_H_

#include "Notification.h"

// class message derived from class notification
class Message : public Notification {
public:
	// constructor calls parent constructor Notification()
	Message(std::string u) : Notification(u) {};

	// getClassName() returns the name of the class
	std::string getClassName() const { return "Message"; };
	
	// returns the notification to be pushed
	std::string print() const;
};

#endif