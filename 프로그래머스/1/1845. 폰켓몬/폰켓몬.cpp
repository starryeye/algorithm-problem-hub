#include <vector>
#include <unordered_map>
using namespace std;

int solution(vector<int> nums) {
    
    unordered_map<int, int> um;
    
    for(auto n : nums) {
        um[n]++;
    }
    
    if(um.size() > nums.size() / 2)
        return nums.size() / 2;
    else
        return um.size();
}