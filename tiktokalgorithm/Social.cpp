#include "Social.h"

/*
 * Social() is a full constructor for the Social class. it takes as input
 * a single string which would be the filename of the relevant information
 * to be taken in as input and saturates all priority queues as well as
 * the stack of posts with data from the json file
 */
Social::Social(std::string filename) {

	std::ifstream jsonFile(filename);

	// simple guard for open file
	if (!jsonFile.is_open()) {
			std::cerr << "Failed to open the JSON file." << std::endl;
			exit(1);
	}

	// maps for holding hashtags/sounds
	std::unordered_map<std::string, Hashtag> hashtags;
	std::unordered_map<std::string, Sound> sounds;

	std::string line;
	while(std::getline(jsonFile, line)) {

		// guard to check for bad posts
		try {

			// post creation and addition to stack
			Post temp(line);
			posts.push(temp);

			// hashtags examine
			std::regex hashtagRegex("#([\\w\\u0080-\\uFFFF]+)");

		    // create an iterator for matching
		    std::string text = posts.top().getText();
		    std::sregex_iterator hashtagIterator(text.begin(), text.end(), hashtagRegex);
		    std::sregex_iterator endIterator;

		    // iterate over the matches and extract the hashtags
		    while (hashtagIterator != endIterator) {
		        std::smatch match = *hashtagIterator;
		        std::string hashtag = match.str(1);  // extract the first capturing group
			// this line will print each hash tag
			// if you want to do more with each hash tag, do it here. for example, store all hash tags in your container.
				Hashtag curhsh;
				curhsh.tag = hashtag;
		        if (hashtags.find(hashtag) != hashtags.end()) {

		        	// hashtag in map
					hashtags[curhsh.tag].postcount++;
					hashtags[curhsh.tag].viewcount += posts.top().getPlayCount();
					hashtags[curhsh.tag].pqueue.push(posts.top());
		        } else {
		        	// hashtag not found
		        	curhsh.viewcount = posts.top().getPlayCount();
		        	curhsh.postcount = 1;
		        	curhsh.pqueue.push(posts.top());
		        	hashtags[curhsh.tag] = curhsh;
		        }

		        ++hashtagIterator;
		    }

			// sound examine
			Sound cursnd;
			cursnd.music = posts.top().getMusic();

			if (sounds.find(cursnd.music.musicid) != sounds.end()) {

				// sound already in map
				sounds[cursnd.music.musicid].viewcount += posts.top().getPlayCount();
				sounds[cursnd.music.musicid].pqueue.push(posts.top());
			} else {

				// sound not in map yet
				cursnd.viewcount = posts.top().getPlayCount();
		        cursnd.pqueue.push(posts.top());
		        sounds[cursnd.music.musicid] = cursnd;
			}
		} catch(const std::exception& e) {

			// if a bad post is found send relevant data for troubleshooting
			std::cerr << std::endl << e.what() << " exception on post: " << posts.top().getId() << std::endl;
			std::cerr << posts.top() << std::endl;
		}
	}

	// transfer data from the unordered map to priority queue
	for (std::pair<std::string, Hashtag> h : hashtags)
		pqueueHashtag.push(h.second);
	for (std::pair<std::string, Sound> p : sounds)
		pqueueSound.push(p.second);
}

/*
 * getHashtags() takes no input and returns a stringstream that
 * contains the hashtags sorted accordingly and with all relevant
 * information present
 */
std::stringstream Social::getHashtags() const {

	// copying pqueue due to const method
	std::priority_queue<Hashtag> pqueue = pqueueHashtag;
	std::stringstream out;
	out << "trending hashtags:\n\n";

	// try for size 10, if <10 hashtags go on total hashtags
	unsigned int size = 10;
	if (pqueue.size() < size)
		size = pqueue.size();

	// loop through top hashtags and add to output
	for (unsigned int i = 0; i < size; i++) {
		out << pqueue.top() << "\n";
		pqueue.pop();
	}

	return out;
}

/*
 * getSounds() takes no input and returns a stringstream that
 * contains the sounds sorted accordingly and with all relevant
 * information present
 */
std::stringstream Social::getSounds() const {

	// copying pqueue due to const method
	std::priority_queue<Sound> pqueue = pqueueSound;
	std::stringstream out;
	out << "trending sounds:\n\n";

	// try for size 10, if <10 sounds go on total sounds
	unsigned int size = 10;
	if (pqueue.size() < size)
		size = pqueue.size();

	// loop through top sounds and add to output
	for (unsigned int i = 0; i < size; i++) {
		out << pqueue.top() << "\n";
		pqueue.pop();
	}

	return out;
}

/*
 * operator<< overide for the hashtag struct. it lets the outputting
 * of a hashtag object be much more streamlined, utilizes built in priority
 * queue to decide on posts to be printed
 */
std::ostream& operator<<(std::ostream& out, const Hashtag& h) {

	std::priority_queue<Post> pqueue = h.pqueue;

	out << "========================" << "\n";
	out << "#" << h.tag << "\n";
	out << "used " << h.postcount << " times" << "\n";
	out << h.viewcount << " views" << "\n";
	out << "\n";

	// loop through top 3 posts
	unsigned int len = 3;
	if (pqueue.size() < 3)
		len = pqueue.size();
	for (unsigned int i = 0; i < len; i++) {
		out << "cover url: " << pqueue.top().getVideo().coverurl << "\n";
		out << "web video url: " << pqueue.top().getWebVideoUrl() << "\n";
		pqueue.pop();
	}

	out << "========================";

	return out;
}

/*
 * operator<< overide for the soudn struct. it lets the outputting
 * of a sound object be much more streamlined, utilizes built in priority
 * queue to decide on posts to be printed
 */
std::ostream& operator<<(std::ostream& out, const Sound& s) {
	std::priority_queue<Post> pqueue = s.pqueue;

	out << "========================" << "\n";
	out << s.music.musicname << "\n";
	out << s.viewcount << " views" << "\n";
	out << s.music.musicauthor << "\n";
	out << "music id: " << s.music.musicid << "\n";
	out << "\n";

	// loop through top 3 posts
	unsigned int len = 3;
	if (pqueue.size() < 3)
		len = pqueue.size();
	for (unsigned int i = 0; i < len; i++) {
		out << "cover url: " << pqueue.top().getVideo().coverurl << "\n";
		out << "web video url: " << pqueue.top().getWebVideoUrl() << "\n";
		pqueue.pop();
	}

	out << "========================";

	return out;
}

/*
 * operator< overide for the hashtag object. used for sorting
 * hashtags in a priority queue of hashtag objects. all logic
 * based on provided guidelines
 */
bool operator<(const Hashtag& h1, const Hashtag& h2) {

	// incase of equivalence ALWAYS return false
	if (h1.tag == h2.tag)
		return false;
	
	if (h1.postcount == h2.postcount) {
		if (h1.viewcount == h2.viewcount)
			return h1.tag > h2.tag;
		return h1.viewcount < h2.viewcount;
	}
	return h1.postcount < h2.postcount;
}

/*
 * operator> overide for the hashtag object. used for sorting
 * hashtags in a priority queue of hashtag objects. all logic
 * based on provided guidelines
 */
bool operator>(const Hashtag& h1, const Hashtag& h2) {

	// incase of equivalence ALWAYS return false
	if (h1.tag == h2.tag)
		return false;

	if (h1.postcount == h2.postcount) {
		if (h1.viewcount == h2.viewcount)
			return h1.tag < h2.tag;
		return h1.viewcount > h2.viewcount;
	}
	return h1.postcount > h2.postcount;
}

/*
 * operator< overide for the sound object. used for sorting
 * sounds in a priority queue of sound objects. all logic
 * based on provided guidelines
 */
bool operator<(const Sound& s1, const Sound& s2) {

	// incase of equivalence ALWAYS return false
	if (s1.music.musicid == s2.music.musicid)
		return false;

	if (s1.viewcount == s2.viewcount)
		return stol(s1.music.musicid) > stol(s2.music.musicid);
	return s1.viewcount < s2.viewcount;
}

/*
 * operator> overide for the sound object. used for sorting
 * sounds in a priority queue of sound objects. all logic
 * based on provided guidelines
 */
bool operator>(const Sound& s1, const Sound& s2) {

	// incase of equivalence ALWAYS return false
	if (s1.music.musicid == s2.music.musicid)
		return false;

	if (s1.viewcount == s2.viewcount)
		return stol(s1.music.musicid) < stol(s2.music.musicid);
	return s1.viewcount > s2.viewcount;
}