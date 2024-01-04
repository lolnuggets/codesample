#include "Document.h"

/*
 * Document() constructor which is full parameters
 * instansiates all relevant values
 */
Document::Document(std::string url, std::list<std::string> kw) {

	// set all relevant vars
	filepath = url;
	keyword = kw;
	score = -1;
	body = "";
	setContent();
}

/*
 * Document() default constructor sets
 * all relevant values to empty or
 * whatever
 */
Document::Document() {

	// set all relevant vars empty
	filepath = "";
	body = "";
	score = -1;
}

/*
 * getTitle() takes no input and returns the
 * title of a given document.
 */
std::string Document::getTitle() const {

	size_t pos = 0;

	// search for titile start/end and substr
	if (content.find("<title>") != std::string::npos) {

		pos = content.find("<title>") + 7;
		return content.substr(pos, content.find('<', pos) - pos);
	}
	return "";
}

/*
 * getDesc() takes no input and returns the
 * description of a given document
 */
std::string Document::getDesc() const {

	size_t pos = 0;

	// search for description start/end and substr
	if (content.find("<meta name=\"description\" content=\"") != std::string::npos) {

		pos = content.find("<meta name=\"description\" content=\"") + 34;
		return content.substr(pos, content.find("\">", pos) - pos);
	}
	return "";
}

/*
 * getDesc() takes no input and returns a
 * snippet considering the keywords of a given document
 */
std::string Document::getSnippet() const {

	// vars instans
	std::string final = "";
	std::string temp;
	size_t pos = getFirstOccurence();

	if (pos != std::string::npos) {

		// set temp as everywhere past the period before the first occurence of keyword
		temp = body.substr(body.rfind('.', pos)+1);
		size_t i = 0;
		while(final.length() != 120) {

			// loop through temp and add to final under certain conditions
			if (i != 0) {
				if (!std::isspace(temp[i]) || (!std::isspace(temp[i-1]) && temp[i] == ' ') || (temp[i] == '\n' && i > 5))
					final += temp[i];
			} else if (!std::isspace(temp[i]))
				final += temp[i];
			i++;
		}
	}
	return final;
}

/*
 * getFirstOccurence() returns the position as size_t of the first
 * occurence of the keyword
 */
size_t Document::getFirstOccurence() const {

	// vars instance
	size_t returnpos = std::string::npos;
	size_t pos = 0;
	size_t end = 0;
	std::string sentence;

	// push all keywords in list into a single phrase
	std::string fullphrase = "";
	unsigned int count = 1;
	for (std::string i : keyword) {
		fullphrase += i;
		if (count != keyword.size())
			fullphrase += ' ';
		count++;
	}

	// if more than one keyword
	if (keyword.size() != 1) {

		// loop as long as there are periods past cur pos
		while(end != std::string::npos) {

			end = body.find_first_of(".>",pos);
			sentence = body.substr(pos,end-pos+1);
			unsigned int count = 0;
			for(std::string i : keyword) {
				if (sentence.find(i) != std::string::npos) {
					if (sentence.substr(sentence.find(i),fullphrase.length()) == fullphrase) {
						return pos;
					}
					if (returnpos == std::string::npos && count == 0)
						returnpos = pos;
				}
				count++;
			}
			pos = end+1;
		}

	} else
		return body.rfind('.', body.find(*keyword.begin()));

	return returnpos;
}

/*
 * getFreq() takes a word as input and returns
 * a number that is the amount of times that word
 * was found in the document
 */
unsigned int Document::getFreq(const std::string& word) const {

	// var instance
	size_t pos = 0;
	unsigned int freq = 0;

	// loop as long as a space is found
	if (word.find(' ') != std::string::npos) {
		while (content.find(word, pos) != std::string::npos) {
			pos = content.find(word, pos)+1;
			if (skipChar(content[pos-2]) && skipChar(content[pos+word.length()-1]))
				freq++;
		}
	} else {
		// if cur word has no spaces
		while (content.find(word, pos) != std::string::npos) {
			pos = content.find(word, pos)+1;
			freq++;
		}
	}
	return freq;
}

/*
 * extractLinksFromHTML() takes filecontent and returns
 * a list of strings which are the unprocessed links
 */
std::list<std::string> Document::extractLinksFromHTML(const std::string& fileContent) {

	std::list<std::string> links;
	// regular expression to match href attributes in anchor tags
	std::regex linkRegex("<a\\s+[^>]*href\\s*=\\s*['\"]([^'\"]+)['\"][^>]*>");
	std::smatch match;

	// search for links in the HTML content
	std::string::const_iterator start = fileContent.cbegin();
	while (std::regex_search(start, fileContent.cend(), match, linkRegex)) {
		if (match.size() > 1) {
			links.push_back(match[1].str());
		}
		start = match.suffix().first;
	}

	return links;
}

/*
 * setScore() takes a map with the key being a keyword and the value being the
 * density of that keyword and a list of all the backlinks and sets the score
 * var to the page score
 */
void Document::setScore(std::map<std::string, double> totaldensity, std::list<Document> backlinks) {

	// calculate density score
	double densityscore = 0;
	for (std::string i : keyword)
		densityscore += getFreq(i) / (content.length() * totaldensity[i]);

	// calculate baacklink score
	double backscore = 0;
	for (Document docn : backlinks)
		backscore += 1.0 / (1 + docn.linkcount);

	score = (densityscore * 0.5) + (backscore * 0.5);
}

/*
 * handleLink() takes a link(unprocessed) and the curlink(the current link of the document)
 * as strings and returns a string which is the processed link
 */
std::string Document::handleLink(std::string link, std::string curlink) {

	// var instance
	curlink = curlink.substr(0,curlink.rfind('/'));
	std::string cur;
	size_t pos;

	// infinte loop until break
	while(true) {

		pos = link.find('/');
		if (pos != std::string::npos) {
			cur = link.substr(0,link.find('/'));
			link = link.substr(link.find('/')+1);
			// if the command is .., go back a directory
			if (cur == "..")
				curlink = curlink.substr(0,curlink.rfind('/'));
			// othewise go forward a directory
			else
				curlink += '/'+cur;
		} else
			break;
	}

	curlink+='/'+link;
	return curlink;
}

/*
 * setContent() takes no input and sets the content var
 * using the filepath var and has no return
 */
void Document::setContent() {

	std::ifstream fileStream(filepath);

	if (fileStream.is_open()) {
		std::string filecontent((std::istreambuf_iterator<char>(fileStream)), std::istreambuf_iterator<char>());
		// suppose filePath is the string "html_files/subdir1/file3.html", then at this point, the string fileContent will be the full content of this file file3.html.
		// do something with fileContent
		content = filecontent;

		// set the body var for easy, not intensive access
		if (body == "") {

			const size_t start = content.find("<body>") + 6;
			const size_t end = content.find("</body>");

			body = content.substr(start, end - start);
		}

		// calculate links in body
		std::list<std::string> links = extractLinksFromHTML(body);
		linkcount = links.size();

		return;
	} else
		std::cerr << "Failed to open \"" << filepath << "\"" << std::endl;

}

/*
 * skipChar() takes a character as input and returns if a char 
 * should be considered when looking at if a word matches a keyword
 */
bool Document::skipChar(const char& c) {
	return ((int)c < 48 || (int)c > 57) && ((int)c < 65 || (int)c > 90) &&
		((int)c < 97 || (int)c > 122);
}

/*
 * operator<< overload for printing the document
 * using getters etc
 */
std::ostream& operator<<(std::ostream& out, const Document& doc) {

	// all relevant vars for output
	out << "Title: " << doc.getTitle() << std::endl;
	out << "URL: " << doc.getFilepath() << std::endl;
	out << "Description: " << doc.getDesc() << std::endl;
	out << "Snippet: " << doc.getSnippet() << std::endl;
	return out;
}