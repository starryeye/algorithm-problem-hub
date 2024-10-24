#include <iostream>
#include <vector>
#include <algorithm>
#include <array>  // std::array 사용

using namespace std;

struct Packet {
    int receiveTime;  // 수신 시각
    int processTime;  // 처리 시간
};

int N;  // 패킷 수
vector<Packet> packets;  // 모든 패킷을 저장하는 벡터
array<array<array<int, 11>, 11>, 1000> dp;  // 메모이제이션 배열 (dp[cur][delay1][delay2])
int minCPU;  // 최소 CPU 수 저장
array<int, 5> tasks;  // 각 CPU의 처리 종료 시간을 저장 (최대 5개 CPU)

// **CPU의 대기 시간 계산 함수**
// 각 CPU에 대해 현재 시간과 종료 시간을 비교하여 지연 시간을 계산합니다.
vector<int> calculateDelays(int cpus, int currentTime) {
    vector<int> delays(cpus);  // 각 CPU의 지연 시간을 저장하는 벡터
    for (int i = 0; i < cpus; ++i) {
        delays[i] = max(0, tasks[i] - currentTime);  // max(0, 종료 시간 - 현재 시간)
    }
    return delays;
}

// **메모이제이션 체크 함수**
// 이미 동일한 상태를 탐색한 적이 있는지 확인합니다.
bool isCached(int cur, const vector<int>& delays, int cpus) {
    return dp[cur][delays[0]][delays[1]] == cpus;
}

// **메모이제이션 저장 함수**
// 탐색한 결과를 dp 배열에 저장합니다.
void cacheResult(int cur, const vector<int>& delays, int cpus) {
    dp[cur][delays[0]][delays[1]] = cpus;
}

// **DFS (깊이 우선 탐색) 함수**
// 현재 CPU 구성으로 모든 패킷을 처리할 수 있는지 탐색합니다.
void dfs(int cpus, int cur) {
    // **종료 조건**: 모든 패킷을 처리한 경우
    if (cur == N) {
        minCPU = cpus;  // 현재 사용된 CPU 수를 저장
        return;
    }

    // 현재 패킷의 수신 시간과 처리 시간을 구조체에서 가져옴
    const auto& [curt, curl] = packets[cur];  // 수신 시각과 처리 시간
    auto delays = calculateDelays(cpus, curt);  // 각 CPU의 대기 시간 계산

    // 이미 동일한 상태를 탐색한 경우 가지치기
    if (isCached(cur, delays, cpus)) return;

    // **기존 CPU에 패킷을 할당하는 경우**
    for (int i = 0; i < cpus; ++i) {
        // 현재 CPU에 해당 패킷을 할당했을 때, 10초를 초과하면 무시
        if (delays[i] + curl > 10) continue;

        // 백트래킹을 위한 CPU 상태 저장
        int originalTask = tasks[i];

        // 패킷을 할당하고 해당 CPU의 종료 시간 갱신
        tasks[i] = max(curt, tasks[i]) + curl;

        // 다음 패킷 처리 (재귀 호출)
        dfs(cpus, cur + 1);

        // 탐색이 끝나면 CPU 상태를 복구 (백트래킹)
        tasks[i] = originalTask;

        // 최소 CPU 수를 찾은 경우 더 이상 탐색할 필요 없음
        if (minCPU != -1) return;
    }

    // 현재 상태를 메모이제이션 테이블에 저장
    cacheResult(cur, delays, cpus);
}

// **DP 배열 초기화 함수**
// dp 배열을 모두 0으로 초기화합니다.
void initializeDP() {
    for (auto& matrix : dp) {  // 각 패킷 인덱스에 대해 반복
        for (auto& row : matrix) {  // 각 CPU의 상태에 대해 반복
            fill(row.begin(), row.end(), 0);  // 배열 초기화
        }
    }
}

// **메인 함수**
// 입력을 처리하고 결과를 출력합니다.
int main() {
    int T;  // 테스트 케이스 수
    cin >> T;  // 테스트 케이스 입력

    // 각 테스트 케이스에 대해 반복
    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> N;  // 패킷 수 입력
        packets.resize(N);  // 패킷 벡터의 크기 조정

        // 패킷의 수신 시각과 처리 시간 입력
        for (auto& packet : packets) {
            cin >> packet.receiveTime >> packet.processTime;
        }

        minCPU = -1;  // 최소 CPU 수 초기화
        initializeDP();  // DP 배열 초기화

        // 1~5개의 CPU로 탐색을 시도합니다.
        for (int cpus = 1; cpus <= 5; ++cpus) {
            dfs(cpus, 0);  // DFS 탐색 시작
            if (minCPU != -1) break;  // 최소 CPU 수를 찾으면 탐색 종료
        }

        // 결과 출력
        cout << '#' << test_case << ' ' << minCPU << '\n';
    }

    return 0;
}


/*
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Packet {
    int arrivalTime;
    int processingTime;
};

// 우선순위 큐에서 사용될 pair: (CPU의 다음 가용 시간, CPU 인덱스)
using CPUState = pair<int, int>;

int simulate(const vector<Packet>& packets, int numCPUs) {
    // 우선순위 큐: 가장 빨리 사용 가능한 CPU를 먼저 꺼낼 수 있도록 함
    priority_queue<CPUState, vector<CPUState>, greater<CPUState>> cpuQueue;

    // 초기화: 모든 CPU의 가용 시간을 0으로 설정
    for (int i = 0; i < numCPUs; ++i) {
        cpuQueue.push({0, i});  // {가용 시간, CPU 인덱스}
    }

    for (const auto& packet : packets) {
        // 가장 빨리 비는 CPU를 선택
        auto [availableTime, cpuIndex] = cpuQueue.top();
        cpuQueue.pop();

        // 해당 패킷의 시작 시간은 max(현재 CPU의 가용 시간, 패킷의 도착 시간)
        int startTime = max(availableTime, packet.arrivalTime);
        int finishTime = startTime + packet.processingTime;

        // 만약 처리 시간이 10초를 초과하면 실패
        if (finishTime - packet.arrivalTime > 10) {
            return -1;
        }

        // CPU의 다음 가용 시간 업데이트 후 다시 큐에 삽입
        cpuQueue.push({finishTime, cpuIndex});
    }

    // 모든 패킷이 처리되면 성공
    return 0;
}

int findMinimumCPUs(const vector<Packet>& packets) {
    // 1~5개의 CPU에 대해 시도
    for (int numCPUs = 1; numCPUs <= 5; ++numCPUs) {
        if (simulate(packets, numCPUs) == 0) {
            return numCPUs;
        }
    }
    return -1;  // 최대 5개의 CPU로도 처리할 수 없으면 -1 반환
}

int main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        int N;
        cin >> N;
        vector<Packet> packets(N);
        for (int i = 0; i < N; ++i) {
            cin >> packets[i].arrivalTime >> packets[i].processingTime;
        }

        int result = findMinimumCPUs(packets);
        cout << "#" << t << " " << result << "\n";
    }
    return 0;
}
*/