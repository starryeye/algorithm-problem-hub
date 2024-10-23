#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

//문제의 예시에서, {7 , 10 , 14 , 20 , 21 , 28} 와 같은 배열을 만들기란.. 
// 시간복잡도가 높다.. 다른방법을 찾아야한다.. times.size() * n 정도 걸리는듯..

//이분 탐색..
// 가장 최소로 걸리는시간 1분, 가장 맥스 : maxTime * n...
// 위 배열로 이분탐색을...한다...
// "mid시간이 걸린다고 했을때 몇명이 수용되는가"
// 수용되면 mid를 낮춰야하고.. 수용안되면 mid를 높여야 한다..
long long solution(int n, vector<int> times) {
    long long answer = 0;
    
    //time 정렬
    sort(times.begin(), times.end(), less<int>());
    
    long long min = 1; //1분
    long long max = (long long)times.back() * n; // worst
    
    //이분 탐색
    while(min <= max) {
        long long mid = min + (max - min) / 2;
        
        //mid 시간이면 총 몇명을 수용할 수 있는가?
        long long count = 0;
        for(int i = 0; i < times.size(); i++) {
            count += mid / (long long)times[i];
        }
        
        if(count < n) //수용 불가
            min = mid + 1;
        else {//수용가능
            max = mid - 1;
            answer = mid;
        }
    }
    
    return answer;
}