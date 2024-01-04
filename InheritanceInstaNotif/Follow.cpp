#include "Follow.h"

/*
 * print() returns a string which is the notification to
 * be pushed to the user. override of the virtual function
 * from the notification class
 */
std::string Follow::print() const {
	return getUser() + " started following you.";
}