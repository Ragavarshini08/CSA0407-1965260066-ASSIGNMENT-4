
# TASK 6 - DESIGN CHALLENGE
## Storage Design for a Video-Streaming Start-up

A start-up streams lecture videos to 200,000 students. The objective is to design an efficient, scalable and reliable storage system.

### Given Information

- Number of students = 200,000
- Video size = 300 MB to 2 GB
- Each video is uploaded once.
- Thousands of students may access the same video.
- Students can start playback at any minute.
- Available resources include HDDs, SSDs and cloud storage.

---

## Stage 1 – Interpret the Workload (2 Marks)

### 1. Identify Operations

| Operation | Frequency | Access Pattern |
|---|---|---|
| Upload videos | Low | Sequential write |
| Store videos | Continuous | Sequential |
| Read videos | Very high | Sequential read |
| Search videos | High | Direct access |
| Update video metadata | Medium | Direct access |
| Delete old videos | Low | Direct access |

### 2. Access Patterns

- Videos are uploaded once.
- Video playback involves continuous sequential reading.
- Students may start at any minute, requiring random access to a playback position.
- Popular videos may be accessed simultaneously by thousands of users.

### 3. Performance Targets

The system should provide:

1. Fast video-start time.
2. Continuous playback without buffering.
3. High availability.
4. Efficient storage utilisation.
5. Reliable backup and recovery.
6. Support for concurrent users.

### Testable Requirements

| Requirement | Performance Target |
|---|---|
| Video availability | 99.9% target |
| Playback start time | Under 2 seconds target |
| Concurrent access | Thousands of users |
| Data protection | Multiple copies |
| Video access | Sequential and random |
| Storage growth | Scalable |

These are proposed design targets, not measured results.

---

## Stage 2 – Propose the Storage Architecture (2 Marks)

### Proposed Hybrid Storage Architecture

| Storage Type | Purpose |
|---|---|
| SSD | Frequently accessed popular videos |
| HDD | Large video archive and less popular videos |
| Cloud object storage | Backup, scalability and additional storage |
| RAM cache | Frequently accessed metadata and video segments |

### File System

- XFS for high-performance Linux storage servers.
- Object storage for scalable video storage.
- A metadata database to store video information.

### Allocation Method

Indexed allocation or an object-storage block mapping system is recommended because it supports efficient access to video data and flexible storage management.

### Working Process

```text
          Student
             |
             v
      Application Server
             |
             v
      Metadata Database
             |
             v
         Cache / CDN
             |
             v
        SSD Storage
             |
             v
       HDD / Cloud Storage
```

**Evaluation:** Popular videos are placed in faster SSD or cache storage. Less frequently accessed videos remain on HDD or cloud storage.

---

## Stage 3 – Identify Critical Design Decisions (2 Marks)

### 1. Block Size

Recommended block size: **1 MB**

Reason:

- Reduces metadata overhead.
- Supports large sequential video transfers.
- Provides efficient reading of video segments.

### 2. Disk Scheduler

- For HDDs, use an appropriate Linux I/O scheduler such as `mq-deadline` or `bfq`, depending on workload and device support.
- For SSDs, use `none` or `mq-deadline` after performance testing.

### 3. Caching Strategy

- Cache popular videos in SSDs.
- Cache frequently requested metadata in RAM.
- Use a CDN for geographically distributed users.
- Apply an LRU (Least Recently Used) policy to remove less frequently accessed cache entries.

### 4. Replication Factor

Use three copies of important video data across independent storage locations.

Benefits:

- Improves availability.
- Supports recovery after hardware failure.
- Reduces the risk of permanent data loss.

---

## Stage 4 – Design and Calculate (4 Marks)

### A. Storage Capacity Calculation

Assumption: The capacity estimate considers 200,000 videos with an average size of 1 GB each. The actual video count must be confirmed for final deployment.

Number of videos = 200,000

Average video size = 1 GB

Total Storage:

200,000 × 1 GB = 200,000 GB

= 200 TB

With three-copy replication:

200 × 3 = 600 TB

Therefore, the required storage capacity is approximately **600 TB**, excluding metadata, overhead and additional backups.

### B. Throughput Calculation

Assume 10,000 students simultaneously watch videos.

Average streaming bitrate = 5 Mbps

Total Throughput:

10,000 × 5 Mbps = 50,000 Mbps

= 50 Gbps

The system must support approximately **50 Gbps** of aggregate video delivery under this assumed workload.

### C. Number of Disk Reads

Assume:

- Video size = 1 GB
- Block size = 1 MB

Using binary units:

1 GB = 1024 MB

Number of Blocks:

1024 / 1 = 1024 blocks

A complete sequential read requires **1024 block reads**, assuming one read per block.

If students start playback at different positions, the system must support efficient random access to the required video segments.

### D. Storage Allocation

| Storage | Percentage | Capacity |
|---|---:|---:|
| SSD | 20% | 40 TB |
| HDD | 60% | 120 TB |
| Cloud storage | 20% | 40 TB |
| **Total** | **100%** | **200 TB** |

The above represents the logical primary data distribution. Three-copy replication is accounted for separately.

### E. Performance Evaluation

| Parameter | Proposed Design |
|---|---|
| Storage | Hybrid SSD, HDD and cloud |
| File system | XFS |
| Allocation | Indexed/object-based |
| Block size | 1 MB |
| Caching | LRU |
| Replication | 3 copies |
| Disk scheduler | Device-dependent |

---

## Stage 5 – Implement and Demonstrate (3 Marks)

### Objective

Simulate video storage using two different storage designs and compare their performance.

**Design A: HDD-based storage**

- All video requests are served from HDD.
- Every request requires a disk read.

**Design B: Hybrid SSD and HDD storage with LRU caching**

- Frequently accessed videos are stored in a cache.
- Cache hits are served without another disk read.
- Cache misses require a disk read.
- The least recently used video is replaced when the cache is full.

### C Program – Video Storage Simulation

The program uses the following request sequence:

`1, 2, 3, 1, 4, 2, 5, 1, 3, 2`

Cache capacity = 3 videos.

The program compares disk reads and cache hits for both designs.

### Expected Simulation Results

| Parameter | Design A: HDD | Design B: Hybrid |
|---|---:|---:|
| Total requests | 10 | 10 |
| Disk reads | 10 | 9 |
| Cache hits | 0 | 1 |
| Cache misses | 10 | 9 |
| Cache hit ratio | 0% | 10% |

**Observation:** The hybrid design reduces disk reads for repeated video requests. A larger cache and a more realistic workload containing frequently repeated popular videos can provide greater benefits.

### Evaluation of Two Designs

| Parameter | Design A: HDD | Design B: Hybrid |
|---|---|---|
| Storage | HDD | SSD + HDD |
| Frequently accessed data | HDD | SSD/cache |
| Random access | Slower | Faster |
| Sequential access | Good | Good |
| Cost | Lower | Higher |
| Performance | Moderate | Better for popular content |

**Conclusion:** The hybrid storage design improves access to popular videos by storing frequently requested content in SSD and cache storage. HDD and cloud storage provide economical capacity for less frequently accessed content.

---

## Alternative Concept and Complexity Analysis

### Alternative Design: Cloud Object Storage with CDN

Instead of storing videos on the company's own servers, all videos can be stored in cloud object storage and delivered through a Content Delivery Network (CDN).

| Parameter | Hybrid On-Premises | Cloud + CDN |
|---|---|---|
| Initial investment | High | Low |
| Scalability | Requires additional hardware | Highly scalable |
| Playback | Depends on server location | Delivered from nearby CDN locations |
| Storage | SSD and HDD | Cloud object storage |
| Maintenance | Managed by company | Managed by cloud provider |
| Data transfer cost | Internal network cost | Cloud bandwidth charges |
| Availability | Depends on infrastructure | Distributed infrastructure |

### Time Complexity

- Video metadata lookup: Approximately O(log n) using a suitable indexed database.
- Sequential video reading: O(n) for n blocks.
- Cache lookup: O(1) using a hash-based cache.
- LRU cache update: O(1) using a hash map and doubly linked list.

### Storage Cost Comparison

For 200 TB of original videos:

- Single copy = 200 TB.
- Three copies = 600 TB.
- Cloud storage can eliminate the need to purchase and maintain all physical storage capacity, but introduces recurring storage and data-transfer charges.

### Final Recommendation

A hybrid architecture with SSD caching, HDD storage, cloud backup and CDN delivery is recommended. It provides a balance between performance, availability, scalability and operating cost.

