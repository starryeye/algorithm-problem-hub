#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool cmp(int a, int b) {
    
    string s1 = to_string(a);
    string s2 = to_string(b);
    
    return (s1 + s2) > (s2 + s1); // 내림차순
    
}


string solution(vector<int> numbers) {
    string answer = "";
    
    
    sort(numbers.begin(), numbers.end(), cmp);
    
 
    

    
    for(int i=0; i<numbers.size(); i++) {
        answer += to_string(numbers[i]);
    }
    
     
    
    return answer[0]=='0' ? "0" : answer;
}