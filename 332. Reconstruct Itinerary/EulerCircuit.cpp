#include<vector>
#include<iostream>
#include<unordered_map>
#include<algorithm>
using namespace std;
class Solution {
public:
    vector<string> ans{};
    void dfs(unordered_map<string, vector<string> >& graph, string node) {

        unordered_map<string, vector<string>>::iterator it = graph.find(node);
        if(it != graph.end()) { // if an airport is never a departure, it won't be in graph      
            while(!it->second.empty()) {
                int i = it->second.size() -1;
                it->second.pop_back();
                dfs(graph, graph[node][i]);
            }
        } 
        ans.push_back(node); 
    }

    vector<string> findItinerary(vector<vector<string> >& tickets) {
        unordered_map<string, vector<string> >graph;
        int m = tickets.size();
        for(int i = 0; i < m; i++) {
            graph[tickets[i][0]].push_back(tickets[i][1]);
        }
        for(auto& node: graph) {
          sort(node.second.begin(), node.second.end(), std::greater<string>()); // for lexical order
        }

        dfs(graph, "JFK");

        reverse(ans.begin(), ans.end());
        return ans;
    }
};

int main() {
    Solution sol;
    vector<vector<string>> sam = {{"JFK","KUL"},{"JFK","NRT"},{"NRT","JFK"}}; // sample case
    sol.findItinerary(sam);
    
    return 0;
}