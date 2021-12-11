#include <iostream>
#include <iomanip>
#include "nlohmann/json.hpp"
#include <fstream>


using json = nlohmann::json;
using namespace std;

int main()
{
    // create a JSON object
    ifstream i("Amazon-Datasets\\kindle_store_reviews\\test2.json");
    json t;
    i >> t;

 
    
    cout << setw(4) << t[2238]["pages"] << '\n';

}