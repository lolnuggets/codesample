#include "Engine.h"

/*
 * Engine() constructor takes in a string with the keywords seperated by spaces
 * indexloc contains the location of the index file
 */
Engine::Engine(std::string kw, std::string indexloc) {

	// var instansiate + keyword instans
	phrase = false;
	parseKeywords(kw);
	this->indexloc = indexloc;
}

/*
 * scorepages() does not take any input and instansiates the score variable
 * of every page the crawler was able to find.
 */
void Engine::scorepages() {

	// var instanstiation
	unsigned int n = 1;
	unsigned int wordcount = 0;
	unsigned int totallength = 0;
	std::map<std::string, double> totaldensity;
	bool firstrun = true;

	// loop through words, count length & total words
	for (std::string i : keyword) {
		for(std::pair<std::string,Document> j : index) {
			wordcount += dnsindex[j.first][n];
			if (firstrun)
				totallength += dnsindex[j.first][0];
		}

		// calculate density poer word
		totaldensity[i] = ((double)wordcount / (double)totallength);

		// reset vars
		wordcount = 0;
		firstrun = false;
		n++;
	}
	// density overall portion done

	// instansiate backlinks list
	std::list<Document> backlinks;

	// loop through all documents and push their backlinks
	for(std::pair<std::string,Document> i : index) {

		for(std::string j : blindex[i.first])
			backlinks.push_back(index[j]);

		// setscore using backlinks and density
		index[i.first].setScore(totaldensity, backlinks);
		backlinks.clear();
	}

	// adding the documents to the relevant set
	if (phrase) {

		// put all the keywords into one word for phrase search
		std::string fullphrase = "";
		unsigned int count = 1;
		for (std::string i : keyword) {
			fullphrase += i;
			if (count != keyword.size())
				fullphrase += ' ';
			count++;
		}

		for(std::pair<std::string,Document> j : index) {
			if (index[j.first].getFreq(fullphrase) != 0)
				relevant.insert(index[j.first]);
		}
	} else {

		// not phrase search, need sum to ensure all words are in doc
		unsigned int sum = 0;
		for(std::pair<std::string,Document> j : index) {
			for(std::string i : keyword)
				if (index[j.first].getFreq(i) != 0)
					sum++;
			if (sum == keyword.size())
				relevant.insert(index[j.first]);
			sum = 0;
		}
	}
}

/*
 * crawl() takes in a string of the location of an html file
 * and it instansiates the document and indexes all relevant 
 * numbers/values and indexes the doc itself
 */
void Engine::crawl(std::string fp) {

	// guard
	if (index.count(fp) == 1)
		return;

	// instans document at fp location
	Document doc(fp, keyword);
	index[fp] = doc;

	// add to the density index 
	dnsindex[fp].push_back(doc.getContent().length());

	// index word density in cur doc
	int count = 1;
	for (std::string i : keyword) {
		dnsindex[fp].push_back(doc.getFreq(i));
		count++;
	}

	const std::list<std::string> links = Document::extractLinksFromHTML(doc.getContent());
	std::string linkfnl;

	// crawl to all links in cur document
	if (links.size() != 0)
		for (std::string i : links) {
			linkfnl = Document::handleLink(i, fp);
			blindex[linkfnl].push_back(fp);
			crawl(linkfnl);
		}
}

/*
 * parseKeywords() takes in a string of the keywords sepertaed
 * by spaces and possibly surrounded by double quotes and translates
 * them to a list of the keywords
 */
void Engine::parseKeywords(std::string kw) {

	std::string cur = "";

	// iterates through the kw string and pushes if its a space
	for(size_t pos = 0; pos < kw.length(); pos++) {
		if (kw[pos] == '\"') {
			phrase = true;
		} else if (kw[pos] == ' ' && cur != "") {
			keyword.push_back(cur);
			cur = "";
		} else
			cur += kw[pos];
	}
	keyword.push_back(cur);

	// culls all empty elements of the list
	std::list<std::string>::iterator itr;
	for (itr = keyword.begin(); itr != keyword.end(); itr++) {
		if (*itr == "")
			itr = keyword.erase(itr);
	}
}