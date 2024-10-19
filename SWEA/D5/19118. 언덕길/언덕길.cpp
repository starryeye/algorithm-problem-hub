#include <iostream>
#include <vector>
#include <algorithm>  // lower_bound 사용을 위해 필요

using namespace std;

int main() {
    int T;  // 테스트 케이스 수
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        int N;  // 집의 수
        cin >> N;

        vector<int> heights(N);  // 각 집의 높이를 저장할 배열
        for (int i = 0; i < N; ++i) {
            cin >> heights[i];
        }

        // LIS (가장 긴 증가하는 부분 수열)를 저장할 벡터
        vector<int> lis;

        // 모든 집의 높이에 대해 반복합니다.
        for (int i = 0; i < N; ++i) {
            // lower_bound를 사용하여 들어갈 위치를 찾습니다.
            int pos = lower_bound(lis.begin(), lis.end(), heights[i]) - lis.begin();

            if (pos < lis.size()) {
                // 이미 존재하는 위치에 값을 대체합니다.
                lis[pos] = heights[i];
            } else {
                // 배열 끝에 추가합니다.
                lis.push_back(heights[i]);
            }
        }

        // 최소로 허물어야 하는 집의 수를 계산합니다.
        int min_houses_to_demolish = N - lis.size();

        // 결과 출력
        cout << "#" << test_case << " " << min_houses_to_demolish << endl;
    }

    return 0;
}
