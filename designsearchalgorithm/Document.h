#ifndef DOCUMENT_H_
#define DOCUMENT_H_

#include <fstream>
#include <iostream>
#include <regex>
#include <set>
#include <list>

class Document {
public:

	// constructors default/full
	Document(std::string filepath, std::list<std::string> keyword);
	Document();

	// simple getters
	double getScore() const { return score; };
	std::string getContent() const { return content; };
	std::string getBody() const { return body; };
	std::string getFilepath() const { return filepath; };
	std::list<std::string> getKeyword() const { return keyword; };
	unsigned int getLinkCount() const { return linkcount; };

	// complex getters
	std::string getTitle() const;
	std::string getDesc() const;
	std::string getSnippet() const;
	size_t getFirstOccurence() const;
	unsigned int getFreq(const std::string& word) const;
	static std::list<std::string> extractLinksFromHTML(const std::string& fileContent);

	// simple settr functions
	void setFilepath(std::string fp) { filepath = fp; };
	void setKeyword(std::list<std::string> kw) { keyword = kw; };

	// complex settor function
	void setScore(std::map<std::string, double> totaldensity, std::list<Document> backlinks);

	static std::string handleLink(std::string link, std::string curlink);

	// all operator overloads
	friend bool operator< (const Document& doc1, const Document& doc2) { return doc1.getScore() < doc2.getScore(); };
	friend bool operator> (const Document& doc1, const Document& doc2) { return doc1.getScore() > doc2.getScore(); };
	friend bool operator<= (const Document& doc1, const Document& doc2) { return doc1.getScore() <= doc2.getScore(); };
	friend bool operator>= (const Document& doc1, const Document& doc2) { return doc1.getScore() >= doc2.getScore(); };
	friend bool operator== (const Document& doc1, const Document& doc2) { return doc1.getScore() == doc2.getScore(); };
	friend bool operator!= (const Document& doc1, const Document& doc2) { return doc1.getScore() != doc2.getScore(); };
	friend std::ostream& operator<<(std::ostream& out, const Document& doc);
private:

	// private helper functions
	void setContent();
	static bool skipChar(const char& c);

	// private vars
	std::string body;
	std::string content;
	std::string filepath;
	double score;
	std::list<std::string> keyword;
	unsigned int linkcount;
};

#endif