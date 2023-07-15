#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class MedianFinder {
public:
    priority_queue<int> smallerHeap; // max heap
    priority_queue<int, vector<int>, greater<int> > largerHeap; // min-heap
    bool evenOrNot;
    MedianFinder() :evenOrNot(true) {
    }
    
    void addNum(int num) {
        evenOrNot = !evenOrNot;
        if(smallerHeap.empty() && largerHeap.empty()) {
            smallerHeap.push(num);
        } else if((!largerHeap.empty()) && (num > largerHeap.top())) {
            largerHeap.push(num); // if num is bigger than larger heap's top then push
        } else {
            smallerHeap.push(num);
        }
        
        /* keep smaller heap's size is always between larger heap's size and its + 1 */
        
        if(smallerHeap.size() > largerHeap.size()+1) {
            int tmp = smallerHeap.top();
            smallerHeap.pop();
            largerHeap.push(tmp);
            // cout << "balance 1, size: " << total_num << endl; 
        } else if(smallerHeap.size() < largerHeap.size()) {
            int tmp = largerHeap.top();
            largerHeap.pop();
            smallerHeap.push(tmp);
            // cout << "balance 2, size: " << total_num << endl;
        }
    }
    
    double findMedian() {
        if(!evenOrNot) {
            return (double) smallerHeap.top();
        } else {
            return (((double)smallerHeap.top() + (double)largerHeap.top()) / 2);
        } 
    }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 
 */
int main() {
    MedianFinder medianFinder;
    medianFinder.addNum(1);    // arr = [1]
    medianFinder.addNum(2);    // arr = [1, 2]
    cout << "ans1: "<<medianFinder.findMedian() << endl; // return 1.5 (i.e., (1 + 2) / 2)
    medianFinder.addNum(3);    // arr[1, 2, 3]
    medianFinder.addNum(3);  
    cout << "ans2: " << medianFinder.findMedian() << endl; 
    while(!medianFinder.largerHeap.empty()) {
        cout << medianFinder.largerHeap.top() << endl;
        medianFinder.largerHeap.pop();
    }
    // priority_queue<int> pq;
    // pq.push(3);
    // pq.push(6);
    // cout << pq.top();
    return 0;
}