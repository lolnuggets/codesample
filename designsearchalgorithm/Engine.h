#ifndef ENGINE_H_
#define ENGINE_H_

#include "Document.h"

#include <map>

class Engine {
public:

	// main constructor
	Engine(std::string keywords, std::string index);

	// getters
	std::set<Document, std::greater<Document>> getRelevant() const { return relevant; };

	// main functions
	void scorepages();
	void crawl() { crawl(indexloc); };
private:

	// private helpers
	void crawl(std::string fp);	
	void parseKeywords(std::string keywords);

	// all indexes used for scoring/storing docs
	std::map<std::string, std::list<std::string>> blindex;
	std::map<std::string, std::vector<unsigned int>> dnsindex; 
	std::map<std::string, Document> index;

	// final container for valid sites
	std::set<Document, std::greater<Document>> relevant;

	// simple vars
	std::list<std::string> keyword;
	std::string indexloc;
	bool phrase;
};

#endif