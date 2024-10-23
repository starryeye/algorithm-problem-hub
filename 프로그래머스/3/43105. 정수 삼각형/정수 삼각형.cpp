#include <string>
#include <vector>

using namespace std;

int solution(vector<vector<int>> triangle) {
    int answer = 0;
    
    int n = triangle.size();
    
    vector<int> dp[n];
    
    //init
    dp[0].push_back(triangle[0][0]);
    
    
    for(int i = 1; i < triangle.size(); i++) { //행
        for(int j = 0; j < triangle[i].size(); j++) { //열
            
            if(j == 0)
                dp[i].push_back(triangle[i][j] + dp[i-1][j]);
            else if(j == triangle[i].size() - 1)
                dp[i].push_back(triangle[i][j] + dp[i-1][j-1]);
            else {
                int tmp = max(dp[i-1][j-1], dp[i-1][j]);
                dp[i].push_back(tmp + triangle[i][j]);
            }
        }
    }
    
    for(int i = 0; i<dp[n-1].size(); i++) {
        answer = max(answer, dp[n-1][i]);
    }
    
    return answer;
}