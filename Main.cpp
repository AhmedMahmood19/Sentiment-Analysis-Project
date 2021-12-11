#include <iostream>
#include <iomanip>
#include "nlohmann/json.hpp"
#include <fstream>
#include <map>
#include <list>
#include <iterator>



using json = nlohmann::json;
using namespace std;

int main()
{
    // create a JSON object
    ifstream reviewFile("Files\\Used Files\\kindle_store_reviews.json");
    json t;
    map<string,list<string>>  M;

    //parsing json file into json object
    reviewFile >> t;
   
    // looping through the json 
    // placing the title in a temp var then comparing it with the next titles
    // if title same then the reviewText of that product is placed in the same list
    // after making a list they are placed in a map with key as the product title and reviewText list as value

    for (int i=0;i<t.size()-1;)
    {
        string temp= t[i]["title"];
        list<string> l;
        

        while (t[i]["title"]==temp)
        {
            if(!t[i]["reviewText"].is_null())
                l.push_back(t[i]["reviewText"]);

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