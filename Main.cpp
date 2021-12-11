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

    reviewFile >> t;
   
    
    for (int i=0;i<t.size()-1;)
    {
        string temp= t[i]["title"];
        list<string> l;
        

        while (t[i]["title"]==temp)
        {
            if(!t[i]["reviewText"].is_null())
                l.push_back(t[i]["reviewText"]);

            i++;
            if (i == 2362)
                cout << "kuch" << endl;
        }
        //M.insert(pair<string, list<string>>(temp, l));
        M[temp] = l;
        
    }
    
  

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