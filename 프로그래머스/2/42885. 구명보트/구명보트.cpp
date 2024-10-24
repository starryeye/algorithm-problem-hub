#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<int> people, int limit) {
    
    int answer = 0; // 사용된 구명보트 수
    
    sort(people.begin(), people.end());
    
    int l = 0;
    int r = people.size() - 1;
    
    // 이진 탐색..
    while(l <= r) {
        
        if (people[l] + people[r] <= limit) {
            l++;  // 가벼운 사람도 함께 보트에 태움
        }
        r--;  // 무거운 사람은 무조건 보트에 태움
        answer++;  // 위의 조건에 따라 보트 하나 사용
    }
    
    return answer;
}