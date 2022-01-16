// merger.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <algorithm>
#include "nlohmann/json.hpp"
#include <fstream>
#include <map>
#include <iterator>
using json = nlohmann::json;
using namespace std;

void mapMetaData(string buff, map<string, string>& mapReference);
void mergeJson(string buff, map<string, string>& mapReference, json& j);

int main()
{
	//open files

	ifstream reviewFile("Files/Original Files/Kindle Datasets/Kindle_Store_5.json/Kindle_Store_5.json");
	ifstream metaFile("Files/Original Files/Kindle Datasets/meta_Kindle_Store.json/meta_Kindle_Store.json");
	ofstream finalJson("clean_Kindle_Data.json");


	map <string, string> metajsonMap;
	char temp1, temp2, temp3;
	json jArr;
	string line;
	//reading metafile
	while (!metaFile.eof())
	{
		string buffer = "";
		while (1)
		{
			getline(metaFile, line, '}');
			line += '}';
			temp1 = metaFile.get();
			temp2 = metaFile.get();
			temp3 = metaFile.get();
			if (metaFile.eof())
			{
				buffer += line;
				break;
			}
			//break case i.e if }\n{" comes break
			else if (temp1 == '\n' && temp2 == '{' && temp3 == '\"')
			{
				buffer += line;
				metaFile.seekg(-3, ios::cur);
				break;
			}
			else
			{
				line += temp1;
				line += temp2;
				line += temp3;
				buffer += line;
			}
		}
		//function to create map from json objects of meta 
		//key is asin and value is title
		mapMetaData(buffer, metajsonMap);
	}
	//same code but for review file
	while (!reviewFile.eof())
	{
		string buff = "";
		while (1)
		{
			getline(reviewFile, line, '}');
			line += '}';
			temp1 = reviewFile.get();
			temp2 = reviewFile.get();
			temp3 = reviewFile.get();
			if (reviewFile.eof())
			{
				buff += line;
				break;
			}
			else if (temp1 == '\n' && temp2 == '{' && temp3 == '\"')
			{
				buff += line;
				reviewFile.seekg(-3, ios::cur);
				break;
			}
			else
			{
				line += temp1;
				line += temp2;
				line += temp3;
				buff += line;
			}
		}
		//merge function
		mergeJson(buff, metajsonMap, jArr);
	}
	finalJson << jArr.dump();
	cout << "Merging complete..." << endl;
	return 0;
}

void mapMetaData(string buff, map<string, string>& mapReference)
{
	//if buff not empty create a local json object and then put it's asin as key and title as value in map
	if (!buff.empty())
	{
		json jsonObj = json::parse(buff);
		string tempKey = jsonObj["asin"];
		mapReference[tempKey] = jsonObj["title"];
	}

}

//merges both the jsons into 1 and then push it on json stl container
void mergeJson(string buff, map<string, string>& mapReference, json& j)
{
	json jsonObj = json::parse(buff);
	json tempJson; 
	if (jsonObj["asin"].is_null() || jsonObj["reviewText"].is_null())
		return;
	//create temp json obj with only values that we need
	tempJson["asin"] = jsonObj["asin"];
	tempJson["reviewText"] = jsonObj["reviewText"];
	//title from map(pass key which is asin returns title of that asin)
	tempJson["title"] = mapReference[jsonObj["asin"]];
	//push that temp json obj in json array
	j.push_back(tempJson);


}
