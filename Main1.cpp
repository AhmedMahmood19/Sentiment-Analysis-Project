#include <iostream>
#include <iomanip>
#include "nlohmann/json.hpp"
#include <fstream>
#include <map>
#include <list>
#include <iterator>



using json = nlohmann::json;
using namespace std;

void main1()
{
    // create a JSON object
    ifstream reviewFile("Files\\Used Files\\kindle_store_reviews.json");
    json JsonObj;
    map<string,list<string>>  M;

    //parsing json file into json object
    JsonObj = json::parse(reviewFile);
   
    // looping through the json 
    // placing the title in a temp var then comparing it with the next titles
    // if title same then the reviewText of that product is placed in the same list
    // after making a list they are placed in a map with key as the product title and reviewText list as value

    for (int i=0;i<JsonObj.size()-1;)
    {
        string temp= JsonObj[i]["title"];
        if (JsonObj[i]["title"] == "")
        {
            i++;
            continue;
        }
        list<string> l;
        

        while (JsonObj[i]["title"]==temp)
        {
            if(!JsonObj[i]["reviewText"].is_null() && JsonObj[i]["title"]!="")
                l.push_back(JsonObj[i]["reviewText"]);

            i++;
            
        }
        //M.insert(pair<string, list<string>>(temp, l));
        M[temp] = l;
        
    }
    
  
    // printing map
    for (pair<const string,list<string>>& x: M)
    {
        cout << x.first<<endl;
        for (auto v: x.second)
        {
            cout << v<< endl;
        }
        cout << endl << " --------------------------------------------------------------------------- " << endl;

    }
    
 
    

}