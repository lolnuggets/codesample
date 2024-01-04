#ifndef POST_H_
#define POST_H_

#include <iostream>
#include <string>
#include <list>

// struct to hold all data for the author
struct Author {
	std::string id, name, nickname, signature, biolink, avatar, region, views;
	bool verified, privateaccount;
	long following, fans, heart, video, digg;
};

// struct to hold all data for music
struct Music {
	std::string musicname, musicauthor, playurl, covermediumurl, musicid;
	bool musicoriginal;
};

// struct to hold all data for a video
struct Video {
	long height, width, duration;
	std::string coverurl, definition, format, downloadaddr;
};

// class to hold data for the post
class Post {
public:
	
	// initializes a post object with only one json line provided by the input file
	Post(std::string input);

	// main accessors
	std::string getId() const { return id; };
	std::string getText() const { return text; };
	std::string getCreateTimeIso() const { return createtimeiso; };
	std::string getWebVideoUrl() const { return webvideourl; };
	long getCreateTime() const { return createtime; };
	long getDiggCount() const { return diggcount; };
	long getShareCount() const { return sharecount; };
	long getPlayCount() const { return playcount; };
	long getCommentCount() const { return commentcount; };
	Author getAuthor() const { return author; };
	Music getMusic() const { return music; };
	Video getVideo() const { return video; };
	std::list<std::string> getMentions() const { return mentions; };

	// friend functions for comparisons
	friend std::ostream& operator<<(std::ostream& out, const Post& p);
	friend bool operator>(const Post& p1, const Post& p2) { return p1.getPlayCount() > p2.getPlayCount(); };
	friend bool operator<(const Post& p1, const Post& p2) { return !(p1 > p2); };
private:

	// private helper functions to set relevant structs
	void setAuthor(std::string input);
	void setMusic(std::string input);
	void setVideo(std::string input);
	void setMentions(std::string input);

	// all memeber variables
	std::string id, text, createtimeiso, webvideourl;
	long createtime, diggcount, sharecount, playcount, commentcount;
	Author author;
	Music music;
	Video video;
	std::list<std::string> mentions;
};

#endif