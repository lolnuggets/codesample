#include "Post.h"

/*
 * Post() takes in a string as input this string would be a signle
 * line from a json file which contains all information for a single
 * post. It then saturates all NECESSARY variables for the assignment.
 * Additional variables were created and unused functions incase they
 * were necessary. However they are NOT used due to memory optimization
 */
Post::Post(std::string input) {

	// main used variables
	size_t pos;			// position of start of data for item
	std::string cur;	// text from searched item
	std::string item;	// item to search for

	item = "id";
	pos = input.find("\""+item+"\"")+5+item.length();
	cur = input.substr(pos, input.find("\",", pos)-pos);
	id = cur;

	item = "text";
	pos = input.find("\""+item+"\"")+5+item.length();
	cur = input.substr(pos, input.find("\",", pos)-pos);
	text = cur;

	item = "musicMeta";
	pos = input.find("\""+item+"\"")+4+item.length();
	cur = input.substr(pos, input.find("},", pos)-pos+1);
	setMusic(cur);

	item = "webVideoUrl";
	pos = input.find("\""+item+"\"")+5+item.length();
	cur = input.substr(pos, input.find("\",", pos)-pos);
	webvideourl = cur;

	item = "videoMeta";
	pos = input.find("\""+item+"\"")+4+item.length();
	cur = input.substr(pos, input.find("},", pos)-pos+1);
	setVideo(cur);

	item = "playCount";
	pos = input.find("\""+item+"\"")+4+item.length();
	cur = input.substr(pos, input.find(",", pos)-pos);
	playcount = stol(cur);
}

/*
 * setAuthor() takes in a line as input which would be the content
 * of the "authorMeta": line however this is unused as it allocates
 * to much memory. This function is however completely functional
 */
void Post::setAuthor(std::string input) {

	// main used variables
	size_t pos;			// position of start of data for item
	std::string cur;	// text from searched item
	std::string item;	// item to search for

	item = "id";
	pos = input.find("\""+item+"\"")+5+item.length();
	cur = input.substr(pos, input.find("\",", pos)-pos);
	author.id = cur;

	item = "name";
	pos = input.find("\""+item+"\"")+5+item.length();
	cur = input.substr(pos, input.find("\",", pos)-pos);
	author.name = cur;

	item = "nickName";
	pos = input.find("\""+item+"\"")+5+item.length();
	cur = input.substr(pos, input.find("\",", pos)-pos);
	author.nickname = cur;

	item = "verified";
	pos = input.find("\""+item+"\"")+4+item.length();
	cur = input.substr(pos, input.find(",", pos)-pos);
	if (cur == "true")
		author.verified = true;
	else
		author.verified = false;

	item = "signature";
	pos = input.find("\""+item+"\"")+5+item.length();
	cur = input.substr(pos, input.find("\",", pos)-pos);
	author.signature = cur;

	item = "bioLink";
	pos = input.find("\""+item+"\"")+5+item.length();
	cur = input.substr(pos, input.find("\",", pos)-pos);
	if (cur != "ul")
		author.biolink = cur;
	else
		author.biolink = "";

	item = "avatar";
	pos = input.find("\""+item+"\"")+5+item.length();
	cur = input.substr(pos, input.find("\",", pos)-pos);
	author.avatar = cur;

	item = "privateAccount";
	pos = input.find("\""+item+"\"")+4+item.length();
	cur = input.substr(pos, input.find(",", pos)-pos);
	if (cur == "false}") {
		author.privateaccount = false;
		return;
	}

	if (cur == "true}") {
		author.privateaccount = true;
		return;
	}

	if (cur == "true")
		author.privateaccount = true;
	else
		author.privateaccount = false;

	item = "region";
	pos = input.find("\""+item+"\"")+5+item.length();
	if (pos != std::string::npos+5+item.length()) {
		cur = input.substr(pos, input.find("\",", pos)-pos);

		author.region = cur;
	}

	item = "views";
	pos = input.find("\""+item+"\"")+5+item.length();
	if (pos != std::string::npos+5+item.length()) {
		cur = input.substr(pos, input.find("\",", pos)-pos);

		author.views = cur;
	}

	item = "following";
	pos = input.find("\""+item+"\"")+4+item.length();
	if (pos != std::string::npos+4+item.length()) {
		cur = input.substr(pos, input.find(",", pos)-pos);

		author.following = stol(cur);
	}

	item = "fans";
	pos = input.find("\""+item+"\"")+4+item.length();
	if (pos != std::string::npos+4+item.length()) {
		cur = input.substr(pos, input.find(",", pos)-pos);

		author.fans = stol(cur);
	}

	item = "heart";
	pos = input.find("\""+item+"\"")+4+item.length();
	if (pos != std::string::npos+4+item.length()) {
		cur = input.substr(pos, input.find(",", pos)-pos);

		author.heart = stol(cur);
	}

	item = "video";
	pos = input.find("\""+item+"\"")+4+item.length();
	if (pos != std::string::npos+4+item.length()) {
		cur = input.substr(pos, input.find(",", pos)-pos);

		author.video = stol(cur);
	}

	item = "digg";
	pos = input.find("\""+item+"\"")+4+item.length();
	if (pos != std::string::npos+4+item.length()) {
		cur = input.substr(pos, input.find("}", pos)-pos);

		author.digg = stol(cur);
	}
}

/*
 * setMusic() takes in a line as input which would be the content
 * of the "musicMeta": line this is used however all unecessary data
 * from the musicMeta was culled and can be readded if necessary for
 * memory optimization
 */
void Post::setMusic(std::string input) {

	// main used variables
	size_t pos;			// position of start of data for item
	std::string cur;	// text from searched item
	std::string item;	// item to search for

	item = "musicName";
	pos = input.find("\""+item+"\"")+5+item.length();
	cur = input.substr(pos, input.find("\",", pos)-pos);
	music.musicname = cur;

	item = "musicAuthor";
	pos = input.find("\""+item+"\"")+5+item.length();
	cur = input.substr(pos, input.find("\",", pos)-pos);
	music.musicauthor = cur;

	item = "coverMediumUrl";
	pos = input.find("\""+item+"\"")+5+item.length();
	cur = input.substr(pos, input.find("\",", pos)-pos);
	music.covermediumurl = cur;

	item = "musicId";
	pos = input.find("\""+item+"\"")+5+item.length();
	cur = input.substr(pos, input.find("\"}", pos)-pos);
	music.musicid = cur;
}

/*
 * setVideo() takes in a line as input which would be the content
 * of the "videoMeta": line this is used however all unecessary data
 * from the videometa was culled and can be readded if necessary for
 * memory optimization
 */
void Post::setVideo(std::string input) {

	// main used variables
	size_t pos;			// position of start of data for item
	std::string cur;	// text from searched item
	std::string item;	// item to search for

	item = "coverUrl";
	pos = input.find("\""+item+"\"")+5+item.length();
	cur = input.substr(pos, input.find("\",", pos)-pos);
	video.coverurl = cur;
}

/*
 * setMentions() takes in a line as input which would be the content
 * of the "mentions": line however this is unused as it allocates
 * to much memory. This function is however completely functional
 */
void Post::setMentions(std::string input) {
	size_t pos = input.find("\"")+1;
	std::string cur;

	while(pos != std::string::npos) {
		cur = input.substr(pos+1, input.find("\"",pos+1)-pos-1);
		mentions.push_back(cur);
		pos = input.find("\"", pos+2+cur.length());
	}
}

/*
 * operator<< overide for any post objects. unused in the actual program assuming
 * no edge case/cornercases. It is however used for debugging to identify problematic
 * posts such as missing width etc.
 */
std::ostream& operator<<(std::ostream& out, const Post& p) {

	out << "----------POST----------" << "\n";
	out << "views/shares/digg/comments " + std::to_string(p.getPlayCount()) + " " +  std::to_string(p.getShareCount()) + " " + std::to_string(p.getDiggCount()) + " " + std::to_string(p.getCommentCount()) << "\n";
	out << "text: " << p.getText() << "\n";
	out << "user " + p.getAuthor().name + ": " << std::to_string(p.getAuthor().heart) + " likes " + std::to_string(p.getAuthor().following) + " following " + std::to_string(p.getAuthor().fans) + " followers " + std::to_string(p.getAuthor().video) + " videos " + std::to_string(p.getAuthor().digg) + " diggs" + "\n";
	out << "video: " << std::to_string(p.getVideo().height) + "x" + std::to_string(p.getVideo().width) + ", duration: " + std::to_string(p.getVideo().duration);
	
	return out;
}