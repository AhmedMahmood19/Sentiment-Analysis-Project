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
	json JsonObj = json::parse(buff);

	if (JsonObj[0]["title"] == "")
	{
		return;
	}
	static string temp = JsonObj[0]["title"];
	if (JsonObj[0]["title"] != temp)
	{
		temp = JsonObj[0]["title"];
	}

	if (!JsonObj[0]["reviewText"].is_null() && JsonObj[0]["title"] != "")
	{
		M[temp].push_back(JsonObj[0]["reviewText"]);
	}
}

int main()
{
	map<string, list<string>>  reviewMap;
	ifstream reviewFile("Files\\Used Files\\kindle_store_reviews.json");
	string buff;
	reviewFile.ignore();
	while (!reviewFile.eof())
	{
		buff="";
		do
		{
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
		buff.insert(buff.begin(), '[');
		buff += "}]";
		cout << buff<<endl;
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