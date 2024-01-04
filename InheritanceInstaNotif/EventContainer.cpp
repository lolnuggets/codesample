#include "EventContainer.h"

/*
 * EventContainer() takes 4 strings as input. 3 of which are file names and 1 of which
 * is the username of a target user. the filenames are opened and are used to saturate
 * relevant variables like filling the event stack of user/psot map and the target is
 * used to decide which events are put into the stack
 */
EventContainer::EventContainer(std::string userfilename, std::string postfilename, std::string eventfilename, std::string settarget) {

	std::ifstream userfile(userfilename);
	std::string line;

	// saturate users map and get the user object for the target
	bool found = false;
	User curtarget;
	while(std::getline(userfile, line)) {
		User temp(line);

		users[temp.getId()] = temp;
		if (temp.getUsername() == settarget) {
			curtarget = temp;
			found = true;
		}
	}

	if (!found)
		throw std::domain_error("Unable to find selected user.");

	userfile.close();
	std::ifstream postfile(postfilename);

	// saturate posts map
	while(std::getline(postfile, line)) {
		Post temp(line);

		posts[temp.getId()] = temp;
	}

	userfile.close();
	std::ifstream eventfile(eventfilename);

	while (std::getline(eventfile, line)) {

		// location of 2 spaces
		size_t space1 = line.find(" ");
		size_t space2 = line.find(" ", space1+1);

		std::string eventtype = line.substr(space1+1, space2 - space1 - 1);		// gets the type of event from the event file
		std::string user = line.substr(0, space1);								// gets the user who initiates the action
		std::string target = line.substr(space2+1);								// gets the user the action was initiated on

		// check the event type and ensure correct constructor is used
		if (eventtype == "tags" && target == settarget && (curtarget.getNotification() && curtarget.getTag()))
			events.push(new Tag(user));
		else if(eventtype == "likes" && users[posts[target].getUserId()].getUsername() == settarget && (curtarget.getNotification() && curtarget.getLike()))
			events.push(new Like(user));
		else if(eventtype == "follows" && target == settarget && (curtarget.getNotification() && curtarget.getFollow()))
			events.push(new Follow(user));
		else if(eventtype == "messageRequests" && target == settarget && (curtarget.getNotification() && curtarget.getMessage()))
			events.push(new Message(user));
		else if(eventtype == "comments_on" && users[posts[target].getUserId()].getUsername() == settarget && (curtarget.getNotification() && curtarget.getComment()))
			events.push(new Comment(user));
		else if (eventtype != "comments_on" && eventtype != "tags" && eventtype != "likes" && eventtype != "follows" && eventtype != "messageRequests")
			throw std::invalid_argument("Invalid event argument");	// throw error in case of unexpecteed arg
	}
}

/*
 * getResult() returns a string which is an output of all events relevant to the
 * selected user. aggregates events if more than 3 happen in a row
 */
std::string EventContainer::getResult() {

	// initialize relevant variables
	std::string result = "";
	std::string temp = "";
	std::string classname = "null";
	std::string user1;
	std::string user2;

	// counter for making capping lines and chain for counting consecutive events
	int counter = 0;
	int chain;

	while (!events.empty()) {

		// access and process the top element
		Notification* currentevent = events.top();

		// only write if we are within line limit
		if (counter < 100) {

			// check for class change
			if (classname == currentevent->getClassName()) {

				// with no change, iterate chain and handle accordingly
				chain++;
				if (chain > 2) {
					if (chain == 3)
						counter-=2;
					temp = user1 + ", " + user2 + " and " + std::to_string(chain-1) + " others " + currentevent->print().substr(currentevent->print().find(" ")+1) + '\n';
					counter--;
				} else {
					if (chain == 1)
						user2 = currentevent->getUser();
					temp += currentevent->print() + '\n';
				}
			} else {

				// with change reset the chain count, push to results, and reset the temp string
				chain = 0;
				result+=temp;
				user1 = currentevent->getUser();
				temp = currentevent->print() + '\n';
			}

			classname = currentevent->getClassName();
			counter++;
		}

		// pop the top element and delete pointer
		delete currentevent;
		events.pop();
	}

	// floating line needs to be added
	result+=temp;
	return result;
}