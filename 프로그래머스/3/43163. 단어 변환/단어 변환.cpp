#include <string>
#include <vector>
#include <queue>
#include <unordered_set>

using namespace std;

int bfs(string begin, string target, vector<string>& words) {
    
    queue<string> que;
    unordered_set<string> us;
    
    que.push(begin);
    us.insert(begin);
    
    //몇 번만에 도달할까요
    int ans = 0;
    
    while(!que.empty()) {
        
        //틱
        int a = que.size();
        for(int i = 0; i < a; i++) {
            
            string fron = que.front();
            que.pop();
            
            // words를 돌아본다.
            for(int i = 0; i < words.size(); i++) {
                
                //방문 했다면 스킵
                if(us.find(words[i]) != us.end())
                    continue;
                
                //단어 사이즈가 안맞으면 다른 단어이므로 스킵
                if(fron.size() != words[i].size())
                    continue;
                
                //현재 문자가 target이다.
                if(fron == target) {
                    return ans;
                }
                
                int count = 0;
        
                //선택된 words와 현재 문자를 비교한다.
                for(int j=0; j<words[i].size(); j++) {
                    if(fron[j] != words[i][j])
                        count++;
                }
        
                //count 가 1이면 한개 차이가 나는 단어로.. que에 넣습니다.
                if(count == 1) {
                    que.push(words[i]);
                    us.insert(words[i]);
                }
                
        
            }
            
        }
        ans++;      
    }
    
    return 0;

}


int solution(string begin, string target, vector<string> words) {
    int answer = 0;
    
    answer = bfs(begin, target, words);
    
    return answer;
}