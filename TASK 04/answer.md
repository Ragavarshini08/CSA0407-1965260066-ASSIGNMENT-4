
# TASK 4 – DISK SCHEDULING ALGORITHMS

**Bloom's Level:** K5 – Evaluate

## Task 4.1 – Calculate (2 Marks)

### Given Data

- Cylinders: 0–199
- Initial head position: 53
- Request queue: 98, 183, 37, 122, 14, 124, 65, 67

### A. FCFS – First Come First Serve

Requests are processed in their arrival order.

**Order:**

53 → 98 → 183 → 37 → 122 → 14 → 124 → 65 → 67

**Head Movement:**

45 + 85 + 146 + 85 + 108 + 110 + 59 + 2

= **640 cylinders**

### B. SSTF – Shortest Seek Time First

The closest pending request is selected at every step.

**Order:**

53 → 65 → 67 → 37 → 14 → 98 → 122 → 124 → 183

**Head Movement:**

12 + 2 + 30 + 23 + 84 + 24 + 2 + 59

= **236 cylinders**

### C. SCAN

The head first moves towards cylinder 0 and then reverses direction.

**Order:**

53 → 37 → 14 → 0 → 65 → 67 → 98 → 122 → 124 → 183

**Head Movement:**

53 + 183

= **236 cylinders**

### D. C-SCAN

The head moves towards cylinder 0, continues to cylinder 199, and then wraps around to cylinder 0 before servicing requests in ascending order.

**Order:**

53 → 37 → 14 → 0 → 199 → 65 → 67 → 98 → 122 → 124 → 183

**Head Movement:**

53 + 23 + 14 + 199 + 134 + 2 + 31 + 24 + 2 + 59

= **541 cylinders**

### E. LOOK

The head moves towards the lowest request and reverses at the last pending request rather than reaching cylinder 0.

**Order:**

53 → 37 → 14 → 65 → 67 → 98 → 122 → 124 → 183

**Head Movement:**

16 + 23 + 51 + 2 + 31 + 24 + 2 + 59

= **208 cylinders**

### F. C-LOOK

The head services requests in one direction and jumps from the lowest request to the highest pending request.

**Order:**

53 → 37 → 14 → 183 → 124 → 122 → 98 → 67 → 65

**Head Movement:**

16 + 23 + 169 + 59 + 2 + 24 + 31 + 2

= **326 cylinders**

### Comparison Table

| Algorithm | Total Head Movement |
|---|---:|
| FCFS | 640 |
| SSTF | 236 |
| SCAN | 236 |
| C-SCAN | 541 |
| LOOK | 208 |
| C-LOOK | 326 |

**Evaluation:** LOOK provides the lowest head movement for this particular request queue. FCFS has the highest movement because it processes requests without considering their physical locations.

**Calculation Note:** The C-SCAN and LOOK totals above are recalculated from their displayed sequences. The question paper's stated totals of 504 and 208 respectively do not both agree with the corresponding movement sequences. The correct LOOK total for the displayed sequence is 231 cylinders, not 208.

## Task 4.2 – Simulate the Algorithms (2 Marks)

### Simulation Requirements

- Generate random disk requests.
- Test light, medium and heavy workloads.
- Calculate average head movement.
- Calculate maximum individual head movement.
- Compare scheduling performance.

### Workload Classification

| Workload | Number of Requests |
|---|---:|
| Light | 1,000 |
| Medium | 5,000 |
| Heavy | 10,000 |

### Algorithms Used

1. FCFS – Processes requests in arrival order.
2. SSTF – Selects the nearest pending request.

### Performance Measures

**Average Head Movement:**

Average = Total Head Movement / Number of Requests

**Maximum Individual Head Movement:**

The maximum distance travelled by the disk head for a single request.

The C program generates 10,000 random requests and compares FCFS and SSTF for all three workload sizes.

## Task 4.3 – Evaluate Fairness (2 Marks)

### Comparison of Disk Scheduling Algorithms

| Algorithm | Starvation | Fairness |
|---|---|---|
| FCFS | No | High |
| SSTF | Possible | Low |
| SCAN | Generally avoids starvation | Good |
| C-SCAN | Generally avoids starvation | Very Good |

### Evaluation

1. **FCFS:** Processes requests in arrival order, so every request eventually receives service.

2. **SSTF:** Can starve requests located far from the current head position because nearby requests may repeatedly be selected.

3. **SCAN:** Moves in both directions and services requests along its path.

4. **C-SCAN:** Services requests in one direction and provides more uniform waiting time across the disk.

### Why Does C-SCAN Provide More Uniform Waiting Time?

C-SCAN services requests in one direction only. After reaching the final cylinder, it returns to the beginning without servicing requests during the return. This creates a more uniform waiting-time distribution compared with SCAN, which services requests in both directions.

## Task 4.4 – Solid-State Drives (1 Mark)

SSDs do not contain moving mechanical disk heads. Therefore, seek time and rotational latency are almost eliminated.

Linux uses the `none` or `mq-deadline` I/O scheduler for SSDs because they provide efficient request handling without the need for traditional mechanical disk-head optimisation.

### Check the Active Scheduler

```bash
cat /sys/block/sda/queue/scheduler
```

### Explanation

1. **none:** Provides minimal scheduling overhead.
2. **mq-deadline:** Attempts to control request latency and prevent starvation.
3. Traditional SCAN and SSTF algorithms are less useful for SSDs because there is no physical disk-head movement.

### Alternative Concept and Complexity Analysis

If the server used LOOK or C-LOOK instead of SCAN or C-SCAN:

| Parameter | SCAN | LOOK | C-SCAN | C-LOOK |
|---|---|---|---|---|
| Movement | To disk boundary | To last request | To disk boundary and wrap | Between extreme requests |
| Extra movement | Possible | Reduced | Higher | Reduced |
| Fairness | Good | Good | Very Good | Very Good |
| Implementation | Simple | Moderate | Moderate | Moderate |

### Complexity Analysis

- FCFS: O(n)
- SSTF using linear search: O(n²)
- SCAN after sorting: O(n log n)
- C-SCAN after sorting: O(n log n)
- LOOK after sorting: O(n log n)
- C-LOOK after sorting: O(n log n)

### Conclusion

For mechanical disks, LOOK or C-LOOK can reduce unnecessary head movement. For workloads requiring predictable waiting times, C-SCAN is a suitable choice. For SSDs, `none` or `mq-deadline` is generally more appropriate.

