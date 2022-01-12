#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <algorithm>
#include "nlohmann/json.hpp"
#include <fstream>
#include <map>
#include <list>
#include <iterator>
#include <set>

using json = nlohmann::json;
using namespace std;



void fillmap(string buff, map<string, list<string>>& mapReference);
void analyseReviews(pair<const string, list<string>>& reviews, map<string, int> posWords, map<string, int> negWords, set<string> stopWords);
int tokenise(string review, map<string, int>& posWords, map<string, int>& negWords, set<string>& stopWords);

int main()
{
	//A map containing all the reviews: key is the review title, value is a list of review texts
	map<string, list<string>>  reviewMap;

	//maps containing the lexicon of positive and negative words each key is the word, value is the count
	map<string, int> posWords;
	map<string, int> negWords;
	
	//set containing the stopwords
	set<string> stopWords;

	//buffer to store string that is read from the file
	string buffer;

	//open json file for reading, (the file object is reviewFile)
	ifstream reviewFile("Files\\Used Files\\kindle_store_reviews.json");
	if (!reviewFile) {
		cout << "File doesn't exist\n";
		return 0;
	}
	//opening lexicon files
	ifstream posWordsFile("Files\\Used Files\\positive-words-clean.txt");
	if (!posWordsFile) {
		cout << "File doesn't exist\n";
		return 0;
	}
	ifstream negWordsFile("Files\\Used Files\\negative-words-clean.txt");
	if (!negWordsFile) {
		cout << "File doesn't exist\n";
		return 0;
	}
	ifstream stopWordsFile("Files\\Used Files\\stopwords.txt");
	if (!stopWordsFile) {
		cout << "File doesn't exist\n";
		return 0;
	}

	//read file and create a map of positive words
	while (!posWordsFile.eof()) {
		getline(posWordsFile, buffer);

		//initialising count of each word to 0
		posWords[buffer] = 0;

	}
	posWordsFile.close();

	//read file and create a map of negative words
	while (!negWordsFile.eof()) {
		getline(negWordsFile, buffer);

		//initialising count of each word to 0
		negWords[buffer] = 0;
	}
	negWordsFile.close();

	//read file and create a set of stopwords
	while (!stopWordsFile.eof()) {
		getline(stopWordsFile, buffer);
		//inserting the stopword
		stopWords.insert(buffer);
	}
	stopWordsFile.close();

	//read the first char '[' and discard it
	reviewFile.ignore();
	//read the second char '{' and discard it
	reviewFile.ignore();

	//read till eof is not reached
	while (!reviewFile.eof())
	{
		//clear the buffer each loop
		buffer.clear();

		while (1)
		{
			//temporary string to store characters till a '}' is encountered
			string temp;

			//temp won't store '}'
			getline(reviewFile, temp, '}');

			//read the 2 chars after '}' to check for eof(if a=']' and b=-1)
			char a = reviewFile.get();
			char b = reviewFile.get();

			//if EOF is detected then append temp to the buffer for the last json object and stop reading
			if (reviewFile.eof())
			{
				buffer += temp;
				break;
			}

			//if the 2 chars after '}' were ',' and '{' 
				//it means the current json object has been completely read
				//so append the temp to buffer and stop reading the file for now
			if (a == ',' && b == '{') {
				buffer += temp;
				break;
			}
			//else the current json object hasn't been completely read so append temp to buffer and
			//append the '}' that wasn't stored by getline and move back 2 chars to continue reading after '}'
			buffer += temp;
			buffer += "}";
			reviewFile.seekg(-2, ios_base::cur);
		}
		//insert a '{' at the start of the string since a json object starts with {
		buffer.insert(buffer.begin(), '{');

		//json object ends with }
		buffer += "}";

		//pass the raw string and map reference to fillmap that will enter all the records into a map
		fillmap(buffer, reviewMap);
	}
	reviewFile.close();

	//passing pair of each entry from the reviewMap so the reviews can be analysed
	for (pair<const string, list<string>>& x : reviewMap)
	{
		analyseReviews(x, posWords, negWords, stopWords);
	}

	return 0;
}

void fillmap(string buff, map<string, list<string>>& mapReference)
{
	//the string read from the open file is converted into a json object
	json JsonObj = json::parse(buff);

	//if the object's title is blank don't add it to the map
	if (JsonObj["title"] == "")
	{
		return;
	}
	//else a static string(temp) is made which stores the current object's title 
		//and retains this value for the next func call
	static string temp = JsonObj["title"];

	//if the current object's title is not the same as the title from the previous func call
		//the static string is updated to store the new title
	if (JsonObj["title"] != temp)
	{
		temp = JsonObj["title"];
	}

	//if the reviewText of the object is not (json)null
		//append the reviewText to the Map with the current title(key)
	if (!JsonObj["reviewText"].is_null())
	{
		mapReference[temp].push_back(JsonObj["reviewText"]);
	}
}


void analyseReviews(pair<const string, list<string>>& reviews, map<string, int> posWords, map<string, int> negWords, set<string> stopWords)
{
	//Creates multimaps of positive and negative words sorted in descending order of count(key)
	multimap<int, string, greater<int> > topPos, topNeg;
	int negReviewCount = 0, posReviewCount = 0, reviewScore=0;
	//iterating through all the reviews in the list
	for (auto v : reviews.second)
	{

		//tokenise function will be called here
		reviewScore = tokenise(v, posWords, negWords, stopWords);
		if (reviewScore > 0)
		{
			posReviewCount++;
		}
		else if (reviewScore < 0)
		{
			negReviewCount++;
		}
	}
	//TODO: calculate rating for product
	//TODO: output analysis into file

	//fills the multimaps with entries from the maps
	for (auto& it : posWords) {
		topPos.insert({ it.second, it.first });
	}

	for (auto& it : negWords) {
		topNeg.insert({ it.second, it.first });
	}

	// Print the multimap
	for (auto& it : topPos) {
		cout << it.second << ' '
			<< it.first << endl;
	}
	cout << "----------------------\n\n";
	// Print the multimap
	for (auto& it : topNeg) {
		cout << it.second << ' '
			<< it.first << endl;
	}
}

int tokenise(string review, map<string, int>& posWords, map<string, int>& negWords, set<string>& stopWords)
{
	int score = 0;
	string word;
	string x = " ";
	char arrSymbols[42] = { '!' , '\"' , '#' , '$' , '%' , '&' , '\'' , '(' , ')' , '*' , '+' , ',' , '-' , '.' , '/' , '0' , '1' , '2' , '3' , '4' , '5' , '6' , '7' , '8' , '9' , ':' , ';' , '<' , '=' , '>' , '?' , '@' , '[' , '\\' , ']' , '^' , '_' , '`' , '{' , '|' , '}' , '~' };
	set<string>::iterator it;
	map<string, int>::iterator itr;
	//tokenise, search in corpus, increase count of words if matched

	//code for searching corpus

	size_t pos;
	for (int i = 0; i < 42; i++)
	{
		while ((pos = review.find(arrSymbols[i])) != std::string::npos) {
			review.replace(pos, 1, x);
		}
	}
	stringstream string1(review);
	while (getline(string1, word, ' '))
	{
		transform(word.begin(), word.end(), word.begin(), ::tolower);

		it = stopWords.find(word);
		if (it != stopWords.end())
			continue;

		itr = posWords.find(word);
		if (itr != posWords.end())
		{
			score++;
			continue;
		}
		itr = negWords.find(word);
		if (itr != negWords.end())
		{
			score--;
			continue;
		}

	}
	return score;
}
