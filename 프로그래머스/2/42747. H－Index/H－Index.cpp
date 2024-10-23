#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> citations) {
    int answer = 0;
    
    sort(citations.begin(), citations.end());
    
    int n = citations.size();
    
    for(int i = 0; i < citations.size(); i++) {
        if(citations[i] >= n - i) {
            answer = n - i;
            break;
        }
    }
    
    return answer;
}