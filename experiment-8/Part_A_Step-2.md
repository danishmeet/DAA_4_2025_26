# Step 2: Measure Metrics

## 2.1 Metric Definitions and Measurement Methodology

To empirically evaluate the scalability of the implemented algorithms, performance data was captured during execution. The following key performance metrics were recorded:

**Execution Time:**  
The total wall-clock time required for the algorithm to process the input, measured in milliseconds (ms). This was captured using the high-resolution clock (std::chrono::high_resolution_clock in C++) to ensure microsecond-level precision.

**Approximate Number of Operations:**  
A discrete integer counter was incremented during the fundamental operation of each algorithm (e.g., inside the while loop for Binary Search, or at each recursive branch for Subset Sum). This serves as a hardware-independent metric to validate the theoretical time complexities.

**Feasibility Status:**  
To evaluate computational limits and prevent system hanging on intractable inputs, a strict execution timeout threshold of 2000.0 ms (2 seconds) was enforced.

- **Completed:** The algorithm successfully found or verified the solution within the time limit.  
- **Timeout (Infeasible):** The algorithm failed to finish within the 2000 ms threshold, demonstrating practical infeasibility for that specific input size.

---

## 2.2 Environmental Variables

To ensure the reproducibility of these metrics, all executions were performed under the following system conditions:

**Hardware:**  
Ryzen 7, 16GB RAM

**Compiler:**  
Standard C++ compiler (GCC) with no external optimization flags.

---

## 2.3 Structured Execution Log

The table below represents the structured log of the experimental runs, detailing the performance of logarithmic, exponential, and factorial algorithms across varying input sizes.

| Algorithm | Complexity Class | Input Size (N) | Operations Count | Execution Time (ms) | Feasibility Status |
|----------|------------------|----------------|------------------|---------------------|--------------------|
| Binary Search | $O(\log n)$ | 1,000,000 | 20 | 0.0012 | Completed |
| Subset Sum (Verification) | $O(n)$ | 8 | 8 | 0.0005 | Completed |
| Subset Sum (Decision) | $O(2^n)$ | 6 | 63 | 0.0150 | Completed |
| Subset Sum (Decision) | $O(2^n)$ | 45 | > 10,000,000 | > 2000.0000 | Timeout |
| TSP (Brute Force) | $O(n!)$ | 4 | 24 | 0.0080 | Completed |
| TSP (Brute Force) | $O(n!)$ | 15 | > 15,000,000 | > 2000.0000 | Timeout |