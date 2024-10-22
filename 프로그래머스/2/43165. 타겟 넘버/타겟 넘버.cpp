#include <string>
#include <vector>

using namespace std;

//flag : 재귀 횟수
//sum : 합
//ans : 경우의 수
//완전탐색

int ans = 0;

void solv(vector<int> &num, int target, int flag, int sum) {
    
    if(flag == num.size()) {
        if(sum == target)
            ans++;
        return;        
    }
    
    solv(num, target, flag + 1, sum + num[flag]);
    solv(num, target, flag + 1, sum - num[flag]);
}

int solution(vector<int> numbers, int target) {
    
    if(numbers.empty())
        return 0;
    
    solv(numbers, target, 0, 0);
    
    return ans;
}