#include <string>
#include <vector>
#include <unordered_set>
#include <math.h>

using namespace std;

//숫자 N을 count개 이용하여 만들수 있는 숫자
//ex) N = 5, i = 2 ==> 55
int makeNs(int count, int N) {
    int ret = N;

    for (int i = 1; i < count; i++) {
        ret += N * pow(10, i);
    }

    return ret;
}

int solution(int N, int number) {


    //dp, N을 i 만큼 사용하였을 때, 나올수 있는 결과값 저장
    //중복 제거를 위하여 set 사용
    //set은 정렬됨, 이문제는 정렬 필요 없으므로 unordered_set
    vector<unordered_set<int>> dp(9); // 정답은 9 미만 (최솟값이 8보다 크면 -1 리턴)

    dp[1].insert(N);

    //예외 처리
    if (N == number)
        return 1;
    if (number == 0 || N == 0)
        return -1;


    //최솟값이 8보다 크면 return -1
    for (int i = 2; i <= 8; i++) {

        dp[i].insert(makeNs(i, N)); //N을 i개 이용하여 만들수 있는 숫자 넣기

        // i = j + (i - j)
        for (int j = 1; j <= i / 2; j++) { 
            // j 가 i / 2 를 넘어가면 중복이므로 할필요 없음

            //사칙연산으로 만들 수 있는 숫자 만들기
            for (auto x : dp[j]) {
                for (auto y : dp[i - j]) {

                    //더하기
                    dp[i].insert(x + y);

                    //곱하기
                    dp[i].insert(x * y);

                    //빼기
                    if (x - y > 0)
                        dp[i].insert(x - y);
                    if (y - x > 0)
                        dp[i].insert(y - x);

                    //나누기
                    if (y != 0)
                        dp[i].insert(x / y);
                    if (x != 0)
                        dp[i].insert(y / x);
                }
            }
        }

        if (dp[i].find(number) != dp[i].end())
            return i;
    }



    return -1;
}