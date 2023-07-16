#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/* This is a bottom up approach. DP + Binary Search */
/* We don't need to do binary search repeatedly because the nearest available event is fixed 
    so we should add 1 more array to remember this.
    Time Complexity: O(n * (k + (logn)) ) */
/* around 370 - 400 ms, 63.87 mb memory */
class Solution {
public:
    static bool cmp(const vector<int>& a, const vector<int>& b) {
        return a[1] < b[1]; // sort by end time
    }
    /* to find the nearest compatible event with binary search */
    int bs(vector<vector<int>>& events, int cur_index) {     
        int cur_start =  events[cur_index][0];
        int l = 0, r = cur_index - 1, mid, end_time;
        while(l <= r) {
            mid = (l+r) /2 ;
            end_time = events[mid][1];
            if(cur_start <= end_time) {
                r = mid - 1;
            } else {
                l = mid + 1;
                if((l < cur_index) && (cur_start <= events[l][1])){                
                    break;
                }
            }
        }

        if(cur_start <= end_time) { // no available event
            return -1;
        }
        return mid;
    }

    int maxValue(vector<vector<int>>& events, int k) {
        int n = events.size();
        std::sort(events.begin(), events.end(), cmp); // sort by end time
        vector<vector<int>> best(n, vector<int>(k, 0));
        vector<int> index_available(n, -1);
        
        for(int i = 1; i < n; i++) {
            index_available[i] = bs(events, i); // memorize the last available event for each event
        }
        
        for(int i = 0; i < k; i++) { //initialize the first-ending event's max values
            best[0][i] = events[0][2];
        }
        for(int i = 1; i < n; i++) { // initialize events' max value when k = 1
            best[i][0] = max(best[i-1][0], events[i][2]);
        }

        for(int j = 1; j < k; j++) {
            for(int i = 1, val = 0, last_index; i < n; i++) {    
                last_index = index_available[i];
                if(last_index != -1) {
                    val = best[last_index][j-1] + events[i][2];
                }
                best[i][j] = max(best[i][j-1], max(val, best[i-1][j]));
            }
        }

        return best[n-1][k-1];
    }
};

int main() {
    return 0;
}
        