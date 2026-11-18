
# TASK 2 – FROM WORKLOAD TO FILE-ALLOCATION METHOD

**Bloom's Level:** K5 – Evaluate

## Task 2.1 – Identify the Operations (2 Marks)

### Problem Description

A network video recorder stores footage from 32 cameras. Files grow continuously while recording, are read mainly from start to end, are sometimes searched by time (random access), and are deleted after 30 days.

### Workload Analysis

| Operation | Frequency | Access Pattern |
|---|---|---|
| Create video files | High | Sequential |
| Write video footage | Continuous | Sequential |
| Read recorded footage | High | Sequential |
| Search footage by time | Medium | Direct |
| Delete old footage | Periodic | Direct |
| Update file metadata | Medium | Direct |

### Observation

Sequential writing and reading are the dominant operations. However, searching recordings by time also requires efficient direct access.

## Task 2.2 – Compare the Allocation Methods (2 Marks)

### Comparison of File Allocation Methods

| Feature | Contiguous Allocation | Linked Allocation (FAT) | Indexed Allocation |
|---|---|---|---|
| Sequential access | Excellent | Good | Good |
| Direct access | Excellent | Poor without FAT indexing | Excellent |
| File growth | Difficult | Easy | Easy |
| Fragmentation | External fragmentation | No external fragmentation | No external fragmentation |
| Reliability | Good | Depends on pointers/FAT | Good with index protection |
| Storage overhead | Low | Pointer/FAT overhead | Index block overhead |

### Evaluation

1. **Contiguous Allocation:** Provides excellent sequential and direct access but makes file expansion difficult and may cause external fragmentation.

2. **Linked Allocation:** Supports file growth easily because blocks can be stored anywhere on the disk. However, direct access is slow because pointers must be followed.

3. **FAT Allocation:** Improves linked allocation by maintaining block links in a File Allocation Table. If the FAT is cached in memory, block-chain lookup becomes faster.

4. **Indexed Allocation:** Supports both sequential and direct access using an index block. It allows files to grow without requiring consecutive disk blocks.

### Recommended Method

Indexed allocation is suitable because video files continuously grow and must support searching by time.

## Task 2.3 – Calculate the Cost (3 Marks)

### Given Data

- File size = 4 GB
- Block size = 4 KB
- Pointer size = 4 bytes
- Disk block size = 4 KB

### Step 1 – Calculate Number of Blocks

Number of blocks:

= (4 × 1024 × 1024) / 4

= 1,048,576 blocks

### A. Contiguous Allocation

The starting block address is stored in the file metadata. The address of any required block can be calculated directly.

- Disk reads to reach the last block = 1
- Sequential traversal of the entire file = 1,048,576 block reads

### B. Linked Allocation

Each block contains a pointer to the next block. To reach the last block, the operating system must follow the links sequentially.

Number of disk reads:

= 1,048,576 block reads

This assumes that the chain is traversed from the beginning and no auxiliary index is available.

### C. Indexed Allocation

The last data block is accessed through the index structure.

For this 4 GB file, the last block falls within the double-indirect region.

- Double-indirect index block read = 1
- Single-indirect index block read = 1
- Data block read = 1

Total disk reads:

= 1 + 1 + 1

= 3 disk reads

This assumes that the required index blocks are not already cached.

### Maximum File Size Using Indexed Allocation

Given:

- 12 direct pointers
- 1 single-indirect pointer
- 1 double-indirect pointer
- 1 triple-indirect pointer
- Block size = 4096 bytes
- Pointer size = 4 bytes

Number of pointers per index block:

= 4096 / 4

= 1024 pointers

Maximum number of data blocks:

= 12 + 1024 + 1024² + 1024³

= 12 + 1024 + 1,048,576 + 1,073,741,824

= 1,074,791,436 blocks

Maximum file size:

= 1,074,791,436 × 4096

= 4,402,345,721,856 bytes

Approximately 4.004 TiB.

## Task 2.4 – Free-Space Management (1 Mark)

### Given Data

- Disk capacity = 4 TB
- Block size = 4 KB

Assuming binary units:

Total number of blocks:

= (4 × 1024 × 1024) / 4

= 1,073,741,824 blocks

### Comparison of Free-Space Management Methods

| Method | Description | Advantage | Disadvantage |
|---|---|---|---|
| Bit Vector | One bit represents each disk block | Easy to find free blocks | Requires bitmap storage |
| Linked Free List | Free blocks contain pointers to the next free blocks | Simple implementation | Slow to find consecutive free blocks |
| Grouping | Stores addresses of multiple free blocks in one block | Faster free-block allocation | More complex management |
| Counting | Stores the starting address and number of consecutive free blocks | Efficient for consecutive free blocks | Less effective when free space is highly fragmented |

### Bit Vector Size Calculation

Number of bits required:

= 1,073,741,824 bits

Number of bytes:

= 1,073,741,824 / 8

= 134,217,728 bytes

= 128 MiB

### Conclusion

Bit vectors are suitable for managing free space because they provide efficient tracking of allocated and available blocks. Grouping and counting can also improve free-space management depending on the disk workload.

## Complete the Code – First-Fit Contiguous and Indexed Allocation

The following C program implements first-fit contiguous allocation and indexed allocation using a 32-block disk.

### Explanation

1. Files A, B, C and D are initially allocated.
2. Files B and D are released.
3. The first-fit contiguous allocation searches for 10 consecutive free blocks.
4. Indexed allocation uses one index block and 10 non-contiguous data blocks.
5. The final disk status is displayed.

### Alternative Concept and Complexity Analysis

If linked allocation with a File Allocation Table (FAT) stored in memory were used instead of indexed allocation:

| Parameter | FAT | Indexed Allocation |
|---|---|---|
| Sequential access | O(n) | O(n) |
| Direct access | O(1) with an in-memory FAT | O(1) for a cached index; otherwise index reads are required |
| Metadata | FAT entries | Index blocks |
| Memory usage | FAT table | Index block cache |
| Reliability | FAT corruption affects multiple files | Index corruption affects the corresponding file |

### FAT Memory Calculation

For a 4 TB disk with 4 KB blocks:

Number of blocks = 1,073,741,824

FAT memory:

= 1,073,741,824 × 4

= 4,294,967,296 bytes

= 4 GiB

A complete FAT containing 4-byte entries would require approximately 4 GiB of memory if entirely loaded into RAM.

### Final Recommendation

Indexed allocation is preferred because it provides direct access and supports non-contiguous file growth without depending on a single FAT structure.

