#include <string>
#include <vector>
#include <stack>

using namespace std;

vector<int> solution(vector<int> prices) {
    
    int n = prices.size();
    
    vector<int> answer(n, 0);

    stack<int> rising_stock; // 가격이 떨어지지 않은 시점(index)들을 모은다.
    
    for (int i = 0; i < n; i++) {
        
        while (!rising_stock.empty()) {

            if (prices[rising_stock.top()] > prices[i]) {
                // 이전 주식 가격보다 가격이 떨어졌으면 버틴 시간을 기록한다.
                int decreased_index = rising_stock.top();
                rising_stock.pop();
                answer[decreased_index] = i - decreased_index;
            } else {
                break;
            }
        }
            
        // 여기에 도달하면, 이전 주식 가격보다 높거나 같다. stack 에 넣음
        rising_stock.push(i);
    }
    
    while (!rising_stock.empty()) {
        // 끝까지 안떨어진 시점들 처리
        int decreased_index = rising_stock.top();
        rising_stock.pop();
        answer[decreased_index] = (n - 1) - decreased_index;
    }
    
    return answer;
}