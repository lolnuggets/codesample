#include "Message.h"

/*
 * print() returns a string which is the notification to
 * be pushed to the user. override of the virtual function
 * from the notification class
 */
std::string Message::print() const {
	return getUser() + " wants to send you a message.";
}