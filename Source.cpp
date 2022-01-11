#include <iostream>
#include <iomanip>
#include "nlohmann/json.hpp"
#include <fstream>
#include <map>
#include <list>
#include <iterator>



using json = nlohmann::json;
using namespace std;

void func(string buff, map<string, list<string>>& M)
{
	//the string read from the open file is converted into a json object
	json JsonObj = json::parse(buff);

	//if the object's title is blank do nothing
	if (JsonObj[0]["title"] == "")
	{
		return;
	}
	//else a static string(temp) is made which stores the current object's title 
		//and retains this value for the next func call
	static string temp = JsonObj[0]["title"];

	//if the current object's title is not the same as the title from the previous func call
		//the static string is updated to store the new title
	if (JsonObj[0]["title"] != temp)
	{
		temp = JsonObj[0]["title"];
	}

	//if the reviewText of the object is not (json)null and the title is not blank(idk why this is here???)
		//append the reviewText to the Map with (the key)the current title 
	if (!JsonObj[0]["reviewText"].is_null() && JsonObj[0]["title"] != "")
	{
		M[temp].push_back(JsonObj[0]["reviewText"]);
	}
}

int main()
{
	//A map containing all the reviews: key is the review title, value is a list of review texts (the map object is reviewMap)
	map<string, list<string>>  reviewMap;

	//open json file for reading, (the file object is reviewFile)
	ifstream reviewFile("Files\\Used Files\\kindle_store_reviews.json");
	
	//buffer to store string that is read from the file
	string buff;
	
	//read the first char '[' and discard it
	reviewFile.ignore();
	//read till eof is not encountered
	while (!reviewFile.eof())
	{
		//empty buff each loop
		buff="";

		do
		{
			//TODO: EDIT this part
			string temp;
			getline(reviewFile, temp, '}');
			if (reviewFile.get() == ',' || reviewFile.get() == ']') {
				buff += temp;
				break;
			}
			buff += temp;
			buff += "}";
			reviewFile.seekg(-2,reviewFile.cur);
		}while(1);
		//insert a '[' at the start of the string since json array starts with [ (??? json obj starts with { why we making array???)
		buff.insert(buff.begin(), '[');
		//json object ends with } json array ends with ]
		buff += "}]";
		//for checking output the rawstring
		cout << buff<<endl;
		//pass the raw json string and map reference to a function that will fill the map
		func(buff, reviewMap);
	}




	/*for (pair<const string, list<string>>& x : reviewMap)
	{
		cout << x.first << endl;
		for (auto v : x.second)
		{
			cout << v << endl;
		}
		cout << endl << " --------------------------------------------------------------------------- " << endl;

	}*/
	




}