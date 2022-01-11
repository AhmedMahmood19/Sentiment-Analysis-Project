#include <iostream>
#include <iomanip>
#include "nlohmann/json.hpp"
#include <fstream>
#include <map>
#include <list>
#include <iterator>

using json = nlohmann::json;
using namespace std;

void fillmap(string buff, map<string, list<string>>& mapReference);

int main()
{
	//A map containing all the reviews: key is the review title, value is a list of review texts (the map object is reviewMap)
	map<string, list<string>>  reviewMap;

	//open json file for reading, (the file object is reviewFile)
	ifstream reviewFile("Files\\Used Files\\kindle_store_reviews.json");
	
	//buffer to store string that is read from the file
	string buffer;
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

	//printing the map for TESTING
	for (pair<const string, list<string>>& x : reviewMap)
	{
		cout << x.first << endl;
		for (auto v : x.second)
		{
			cout << v << endl;
		}
		cout << endl << " --------------------------------------------------------------------------- " << endl;

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