#include "Tag.h"

/*
 * print() returns a string which is the notification to
 * be pushed to the user. override of the virtual function
 * from the notification class
 */
std::string Tag::print() const {
	return getUser() + " tagged you in a post.";
}