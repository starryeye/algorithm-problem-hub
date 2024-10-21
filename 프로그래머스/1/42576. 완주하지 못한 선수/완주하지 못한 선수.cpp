#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

string solution(vector<string> participant, vector<string> completion) {
    
    string answer = "";
    
    unordered_map<string, int> p;
    
    for(auto& i : participant) {
        //p[i] = 0;
        p[i]++;
    }
    
    for(auto& i : completion) {
        p[i]--;
    }
    
    for(auto& i : p) {
        if(i.second > 0) {
            answer = i.first;
            break;
        }
    }
    
    return answer;
}