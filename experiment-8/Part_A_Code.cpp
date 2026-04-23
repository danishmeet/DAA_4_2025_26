#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <numeric>
#include <iomanip>

using namespace std;
using namespace std::chrono;

const double TIMEOUT_MS = 2000.0;

struct Metrics {
    string algorithmName;
    double executionTimeMs = 0.0;
    long long operations = 0;
    string status = "Completed";
};


// 1. Binary Search

int binarySearch(const vector<int>& arr, int target, Metrics& metrics) {
    auto start = high_resolution_clock::now();
    metrics.algorithmName = "Binary Search";
    metrics.operations = 0;
    
    int left = 0;
    int right = arr.size() - 1;
    int result = -1;

    while (left <= right) {
        metrics.operations++;
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            result = mid;
            break;
        }
        if (arr[mid] < target) left = mid + 1;
        else right = mid - 1;
    }

    auto end = high_resolution_clock::now();
    metrics.executionTimeMs = duration<double, std::milli>(end - start).count();
    return result;
}


// 2A. Subset Sum (Verification)

bool verifySubsetSum(const vector<int>& subset, int target, Metrics& metrics) {
    auto start = high_resolution_clock::now();
    metrics.algorithmName = "Subset Sum (Verification)";
    metrics.operations = 0;
    
    long long currentSum = 0;
    for (int num : subset) {
        metrics.operations++;
        currentSum += num;
    }

    auto end = high_resolution_clock::now();
    metrics.executionTimeMs = duration<double, std::milli>(end - start).count();
    return currentSum == target;
}


// 2B. Subset Sum (Decision / Brute Force)

bool solveSubsetSumRec(const vector<int>& arr, int n, int target, Metrics& metrics, time_point<high_resolution_clock> startTime) {
    metrics.operations++;
    
    auto now = high_resolution_clock::now();
    if (duration<double, std::milli>(now - startTime).count() > TIMEOUT_MS) {
        metrics.status = "Timeout";
        return false;
    }

    if (target == 0) return true;
    if (n == 0 && target != 0) return false;

    if (arr[n - 1] > target) {
        return solveSubsetSumRec(arr, n - 1, target, metrics, startTime);
    }

    return solveSubsetSumRec(arr, n - 1, target, metrics, startTime) || 
           solveSubsetSumRec(arr, n - 1, target - arr[n - 1], metrics, startTime);
}

bool solveSubsetSum(const vector<int>& arr, int target, Metrics& metrics) {
    auto start = high_resolution_clock::now();
    metrics.algorithmName = "Subset Sum (Decision)";
    metrics.operations = 0;
    metrics.status = "Completed";

    bool result = solveSubsetSumRec(arr, arr.size(), target, metrics, start);

    auto end = high_resolution_clock::now();
    metrics.executionTimeMs = duration<double, std::milli>(end - start).count();
    return result;
}


// 3. Traveling Salesman Problem (Brute Force)

int tspBruteForce(const vector<vector<int>>& graph, Metrics& metrics) {
    auto start = high_resolution_clock::now();
    metrics.algorithmName = "TSP (Brute Force)";
    metrics.operations = 0;
    metrics.status = "Completed";

    int n = graph.size();
    if (n <= 1) return 0;

    vector<int> vertices;
    for (int i = 1; i < n; i++) vertices.push_back(i);

    int minPath = INT_MAX;

    do {
        metrics.operations++;
        
        auto now = high_resolution_clock::now();
        if (duration<double, std::milli>(now - start).count() > TIMEOUT_MS) {
            metrics.status = "Timeout";
            break;
        }

        int currentPathWeight = 0;
        int k = 0;
        
        for (int i = 0; i < vertices.size(); i++) {
            currentPathWeight += graph[k][vertices[i]];
            k = vertices[i];
        }
        currentPathWeight += graph[k][0];
        minPath = min(minPath, currentPathWeight);

    } while (next_permutation(vertices.begin(), vertices.end()));

    auto end = high_resolution_clock::now();
    metrics.executionTimeMs = duration<double, std::milli>(end - start).count();
    return minPath;
}


// Utility: Logging and Execution

void printLog(const Metrics& m) {
    cout << left << setw(30) << m.algorithmName 
         << setw(15) << m.status 
         << setw(20) << m.operations 
         << fixed << setprecision(4) << m.executionTimeMs << " ms" << "\n";
}

int main() {
    cout << string(85, '-') << "\n";
    cout << left << setw(30) << "Algorithm" 
         << setw(15) << "Status" 
         << setw(20) << "Operations Count" 
         << "Execution Time\n";
    cout << string(85, '-') << "\n";

    // 1. Binary Search Execution
    vector<int> sortedArr(1000000);
    iota(sortedArr.begin(), sortedArr.end(), 1); 
    Metrics bsMetrics;
    binarySearch(sortedArr, 999999, bsMetrics);
    printLog(bsMetrics);

    // 2A. Subset Sum Verification Execution
    vector<int> candidateSubset = {15, 22, 14, 26, 32, 9, 16, 8};
    Metrics ssVerifyMetrics;
    verifySubsetSum(candidateSubset, 142, ssVerifyMetrics);
    printLog(ssVerifyMetrics);

    // 2B. Subset Sum Decision Execution (Will complete)
    vector<int> ssSet = {3, 34, 4, 12, 5, 2};
    Metrics ssDecisionMetrics;
    solveSubsetSum(ssSet, 9, ssDecisionMetrics);
    printLog(ssDecisionMetrics);

    // 2B. Subset Sum Decision Execution (Forced Timeout Simulation)
    vector<int> largeSsSet(45, 10); 
    Metrics ssDecisionTimeoutMetrics;
    solveSubsetSum(largeSsSet, 999, ssDecisionTimeoutMetrics);
    printLog(ssDecisionTimeoutMetrics);

    // 3. TSP Brute Force Execution (Will complete)
    vector<vector<int>> tspGraphSmall = {
        {0, 10, 15, 20},
        {10, 0, 35, 25},
        {15, 35, 0, 30},
        {20, 25, 30, 0}
    };
    Metrics tspMetricsSmall;
    tspBruteForce(tspGraphSmall, tspMetricsSmall);
    printLog(tspMetricsSmall);

    // 3. TSP Brute Force Execution (Forced Timeout Simulation)
    vector<vector<int>> tspGraphLarge(15, vector<int>(15, 10)); // 15 cities will timeout
    Metrics tspMetricsLarge;
    tspBruteForce(tspGraphLarge, tspMetricsLarge);
    printLog(tspMetricsLarge);

    cout << string(85, '-') << "\n";
    return 0;
}