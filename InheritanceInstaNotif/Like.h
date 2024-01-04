#ifndef LIKE_H_
#define LIKE_H_

#include "Notification.h"

// class like derived from class notification
class Like : public Notification {
public:
	// constructor calls parent constructor Notification()
	Like(std::string u) : Notification(u) {};

	// getClassName() returns the name of the class
	std::string getClassName() const { return "Like"; };
	
	// returns the notification to be pushed
	std::string print() const;
};

#endif