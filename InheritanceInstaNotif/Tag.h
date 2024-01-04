#ifndef TAG_H_
#define TAG_H_

#include "Notification.h"

// class tag derived from class notification
class Tag : public Notification {
public:
	// constructor calls parent constructor Notification()
	Tag(std::string u) : Notification(u) {};

	// getClassName() returns the name of the class
	std::string getClassName() const { return "Tag"; };

	// returns the notification to be pushed
	std::string print() const;
};

#endif