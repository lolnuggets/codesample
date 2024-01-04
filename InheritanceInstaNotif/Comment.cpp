#include "Comment.h"

/*
 * print() returns a string which is the notification to
 * be pushed to the user. override of the virtual function
 * from the notification class
 */
std::string Comment::print() const {
	return getUser() + " commented on your post.";
}