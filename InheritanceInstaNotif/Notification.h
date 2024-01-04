#ifndef NOTIFICATION_H_
#define NOTIFICATION_H_

#include <iostream>
#include <typeinfo>

// class notification parent of all notification types
class Notification {
public:
	// returns the user who initiated the notification
	std::string getUser() const { return user; };

	// sets the user
	void setUser(std::string u) { user = u; };

	//  virtual functions to be overridden
	virtual std::string getClassName() const { return "notification"; };
	virtual std::string print() const { return "default notification"; };
	virtual ~Notification() {};
protected:

	// protected constructor as it should never be used except by a child object
	Notification(std::string u);
private:

	// private variables
	std::string user;
};

#endif