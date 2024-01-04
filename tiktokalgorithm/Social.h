#ifndef SOCIAL_H_
#define SOCIAL_H_

#include "Post.h"

#include <queue>
#include <stack>
#include <unordered_map>
#include <regex>
#include <fstream>
#include <stdexcept>
#include <sstream>

// struct for holding all data relevant to hashtag
struct Hashtag {

	// data. tag is content postcount/viewcount is sorting key
	std::string tag;
	int postcount;
	long viewcount;

	// priority queue used to get top posts
	std::priority_queue<Post> pqueue;

	// friend functions for hastag comparison/output
	friend std::ostream& operator<<(std::ostream& out, const Hashtag& h);
	friend bool operator<(const Hashtag& h1, const Hashtag& h2);
	friend bool operator>(const Hashtag& h1, const Hashtag& h2);
	friend bool operator==(const Hashtag& h1, const Hashtag& h2) { return h1.tag == h2.tag; };
};


// struct for holding all data relevant for a sound
struct Sound {

	// data. music is content and viewcount is sorting key
	Music music;
	long viewcount;

	// priority queue used to get top posts
	std::priority_queue<Post> pqueue;

	// friend functions for sound comparison/output
	friend std::ostream& operator<<(std::ostream& out, const Sound& s);
	friend bool operator<(const Sound& s1, const Sound& s2);
	friend bool operator>(const Sound& s1, const Sound& s2);
	friend bool operator==(const Sound& s1, const Sound& s2) { return s1.music.musicid == s2.music.musicid; };
};

// class for initializing a database from json
class Social {
public:

	// constructor, no default constructor
	Social(std::string filename);

	// public functions to string for required output
	std::stringstream getHashtags() const;
	std::stringstream getSounds() const;
private:

	// priority queue to sort the hashtags and sounds
	std::priority_queue<Hashtag> pqueueHashtag;
	std::priority_queue<Sound> pqueueSound;

	// stack of posts not particularly useful
	std::stack<Post> posts;
};

#endif