#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;

int main(){
    unsigned N, Q;
    cin >> N >> Q;
    vector <string> HRML(N);
    vector <string> queries(Q);
    vector <string> tags;
    map <string, string> result;

    
    cin.ignore();

    for (unsigned i = 0; i < N; ++i)
        getline(cin, HRML[i]);
    for (unsigned i = 0; i < Q; ++i)
        getline(cin, queries[i]);

    for (unsigned i = 0; i < N; ++i) {
        HRML[i] = HRML[i];
        HRML[i].erase(remove(HRML[i].begin(), HRML[i].end(), '>'), HRML[i].end());
        HRML[i].erase(remove(HRML[i].begin(), HRML[i].end(), '\"'), HRML[i].end());

        if(HRML[i].substr(0,2) == "</"){
            tags.pop_back();
        } else{
            stringstream ss("");
            ss << HRML[i];
            char ch;
            string tag, attr_name, attr_val;
            ss >> ch >> tag >> attr_name >> ch >> attr_val;
            string tmp;
            if(tags.size() > 0){
                tmp = *tags.rbegin();
                tmp = tmp + "." + tag;
            } else
                tmp = tag;
            tags.push_back(tmp);
            result[*tags.rbegin() + "~" + attr_name] = attr_val;
            while(ss){
                ss >> attr_name >> ch >> attr_val;
                result[*tags.rbegin() + "~" + attr_name] = attr_val;
            }

        }
    }

    for(unsigned i = 0; i < Q; ++i){
        if(result.find(queries[i]) == result.end())
            cout << "Not Found!" << endl;
        else
            cout << result[queries[i]] << endl; 
    }

    

    return 0;
}