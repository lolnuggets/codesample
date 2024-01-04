#include "Like.h"

/*
 * print() returns a string which is the notification to
 * be pushed to the user. override of the virtual function
 * from the notification class
 */
std::string Like::print() const {
	return getUser() + " liked your post.";
}