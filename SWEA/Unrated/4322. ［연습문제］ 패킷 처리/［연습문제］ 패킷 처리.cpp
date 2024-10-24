#include <iostream>
#include <vector>
#include <algorithm>
#include <array>

using namespace std;

struct Packet {
    int receiveTime;  // 수신 시각
    int processTime;  // 처리 시간
};

int N;  // 패킷 수
vector<Packet> packets;
array<array<array<int, 11>, 11>, 1000> dp;  // dp 배열
int minCPU;
array<int, 5> tasks;  // 각 CPU의 처리 종료 시간

// 지연 시간 계산 함수
vector<int> calculateDelays(int cpus, int currentTime) {
    vector<int> delays(cpus);
    for (int i = 0; i < cpus; ++i) {
        delays[i] = max(0, tasks[i] - currentTime);
    }
    return delays;
}

// dp 배열에 이미 계산된 결과가 있는지 확인하는 함수
bool isCached(int cur, const vector<int>& delays, int cpus) {
    return dp[cur][delays[0]][delays[1]] == cpus;
}

// dp 배열에 결과를 저장하는 함수
void cacheResult(int cur, const vector<int>& delays, int cpus) {
    dp[cur][delays[0]][delays[1]] = cpus;
}

// 깊이 우선 탐색 (DFS) 함수
void dfs(int cpus, int cur) {
    if (cur == N) {
        minCPU = cpus;
        return;
    }

    const auto& [curt, curl] = packets[cur];  // 현재 패킷의 수신 및 처리 시간
    auto delays = calculateDelays(cpus, curt);

    if (isCached(cur, delays, cpus)) return;

    for (int i = 0; i < cpus; ++i) {
        if (delays[i] + curl > 10) continue;

        int originalTask = tasks[i];
        tasks[i] = max(curt, tasks[i]) + curl;
        
        dfs(cpus, cur + 1);
        
        tasks[i] = originalTask;
        if (minCPU != -1) return;
    }

    cacheResult(cur, delays, cpus);
}

// 초기화 함수
void initializeDP() {
    for (auto& matrix : dp) {
        for (auto& row : matrix) {
            fill(row.begin(), row.end(), 0);
        }
    }
}

// 메인 함수
int main() {
    int T;
    cin >> T;

    for (int test_case = 1; test_case <= T; ++test_case) {
        cin >> N;
        packets.resize(N);
        
        for (auto& packet : packets) {
            cin >> packet.receiveTime >> packet.processTime;
        }

        minCPU = -1;
        initializeDP();

        for (int cpus = 1; cpus <= 5; ++cpus) {
            dfs(cpus, 0);
            if (minCPU != -1) break;
        }

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