#include "Notification.h"

/*
 * Notification() is the default constructor for a
 * default notification. it is protected as it is
 * not intended to ever be called except by a derived
 * class
 */
Notification::Notification(std::string u) {
	user = u;
}