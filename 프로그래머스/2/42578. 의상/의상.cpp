#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

int solution(vector<vector<string>> clothes) {
    int answer = 1;
    
    //string : 옷 종류, int : 옷 갯수
    unordered_map<string, int> um;
    
    // i : 옷 개수 만큼 순회
    for(int i =0; i < clothes.size(); i++) {
        //옷 종류를 um에 넣고 갯수를 +1 해준다.
        um[clothes[i][1]]++;
    }
    
    // kind : um 순회
    for(auto& kind : um) {
        //조합
        answer *= kind.second + 1; //안입는 경우도 넣는다.
    }
    
    return answer -1; //모두 안입는 경우는 빼준다.
    
/*
//아래의 개념을 코드로 옮기려면 안 입는 경우를 생각 하여 종류별 갯수에 +1 해주고 모두 곱한다음 -1(모두 안입는 경우) 해준다.
    if(um.size() == 1)
        return total; //종류가 하나일때는 한번씩 입는 경우 뿐이다.
    else
        return total+join; //종류가 두종류일 경우 한번씩 입는 경우와 종류별로 하나씩 입는 경우
    else
        //종류가 세종류일 경우 한번씩 입는 경우와 2종류를 조합해서 입는 경우, 3종류를 모두 입는 경우
*/
}