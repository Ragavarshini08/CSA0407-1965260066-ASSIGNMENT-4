
# TASK 3 – MODERN FILE SYSTEMS

**Bloom's Level:** K5 – Evaluate

## Task 3.1 – Compare Modern File Systems (3 Marks)

### Comparison of Modern File Systems

Compare FAT32, NTFS, ext4, XFS, Btrfs, ZFS and APFS based on maximum file size, journaling, snapshots, checksums and copy-on-write.

| Feature | FAT32 | NTFS | ext4 | XFS | Btrfs | ZFS | APFS |
|---|---|---|---|---|---|---|---|
| Maximum File Size | 4 GB minus 1 byte | Very large | Very large | Very large | Very large | Very large | Very large |
| Journaling | No | Yes | Yes | Yes | Copy-on-write | Copy-on-write | Copy-on-write |
| Snapshots | No | Limited through VSS | No native snapshots | No native snapshots | Yes | Yes | Yes |
| Checksums | No general file-data checksums | Metadata checksums | Metadata checksums | Metadata checksums | Yes | Yes | Yes |
| Copy-on-Write | No | No | No | No | Yes | Yes | Yes |
| Best Use | USB compatibility | Windows systems | Linux general-purpose | Large Linux storage | Advanced Linux storage | Enterprise storage | Apple devices |

### Evaluation

1. **FAT32:** Useful for compatibility but has a 4 GB individual file-size limit.

2. **NTFS:** Provides security, journaling and reliable Windows file management.

3. **ext4:** Provides good performance and reliability for Linux systems.

4. **XFS:** Suitable for large files and high-throughput workloads.

5. **Btrfs:** Supports snapshots, checksums and copy-on-write.

6. **ZFS:** Provides advanced data integrity and storage management.

7. **APFS:** Optimised for Apple's devices and flash storage.

### Recommendation

NTFS is suitable for Windows systems, ext4 for general Linux systems, and ZFS or Btrfs for systems requiring advanced data integrity and snapshot support.

**Note:** Maximum volume size depends on the file-system implementation, version and operating-system support. The comparison above focuses on the maximum file-size descriptions provided in the assignment.

## Task 3.2 – Journaling and Consistency (2 Marks)

### Meaning of Journaling

Journaling is a file-system technique that records planned changes before applying them to the main file system.

### Working of Journaling

1. The operating system receives a write request.
2. The changes are recorded in the journal.
3. The journal transaction is committed.
4. Changes are applied to the actual file system.
5. After a crash, the system replays committed transactions.

### Comparison of ext4 Journaling Modes

| Mode | Description | Performance | Protection |
|---|---|---|---|
| Journal | Both metadata and file data are journaled | Slower | Stronger protection |
| Ordered | Metadata is journaled after associated data is written | Balanced | Prevents stale data exposure through metadata |
| Writeback | Metadata is journaled without ordering data writes first | Faster | Weaker data consistency |

### Copy-on-Write (CoW)

Copy-on-write does not overwrite existing data immediately. Instead, it writes modified data to a new location and updates metadata to point to the new data.

### Comparison Between Journaling and Copy-on-Write

1. Journaling records changes before applying them.
2. Copy-on-write preserves the old data until the new data and metadata are safely committed.
3. CoW supports snapshots and can provide strong consistency.

### What Happens During a Power Failure?

If power fails during a write operation, the file system may contain incomplete updates.

In journaling file systems, committed transactions can be replayed during recovery to restore file-system consistency.

In copy-on-write file systems, the old data remains available until the new data and metadata are committed. This reduces the risk of partially updated structures.

**Conclusion:** Journaling and copy-on-write improve file-system consistency and recovery after unexpected system failures.

## Task 3.3 – Choose for Each Device (3 Marks)

### Recommended File Systems

| Device | Recommended File System | Justification |
|---|---|---|
| Pen drive used on Windows and Linux | FAT32 or exFAT | Better cross-platform compatibility; exFAT supports large files |
| Linux database server | XFS | High performance and suitable for large files |
| Laptop requiring snapshots | Btrfs | Supports snapshots, checksums and rollback |
| Backup server requiring snapshots | ZFS | Provides advanced data integrity and snapshot support |

### Evaluation

1. **Pen Drive:** exFAT is preferable to FAT32 when large files must be stored on a shared pen drive.

2. **Linux Database Server:** XFS is suitable for database workloads requiring high-throughput file operations.

3. **Laptop:** Btrfs is suitable for laptops requiring snapshot-based recovery.

4. **Backup Server:** ZFS is suitable for backup environments requiring data integrity and snapshot management.

### Final Recommendation

The choice of a file system depends on the device's purpose, storage requirements, performance and data protection needs.

## Task 3.4 – Inspect a Real File System (1 Mark)

### Objective

To inspect a real Linux file system and identify inode information, block size and free-space details using Linux commands.

### 1. Display File System Information

Command:

```bash
stat -f /
```

Purpose:

Displays file-system information such as block size, total blocks and available blocks.

### 2. Display Disk Usage and Inodes

Command:

```bash
df -i
```

Purpose:

Displays inode usage, total inodes, used inodes and available inodes.

### 3. Display Detailed File Information

Command:

```bash
ls -li
```

Purpose:

Displays files along with their inode numbers.

### 4. Display File System Information

Command:

```bash
sudo tune2fs -l /dev/sda1
```

Purpose:

Displays detailed information about an ext2, ext3 or ext4 file system.

### 5. Display Block and Inode Information

Command:

```bash
sudo dumpe2fs -h /dev/sda1
```

Purpose:

Displays the file-system superblock information, including block size, total blocks and free blocks.

**Note:** Replace `/dev/sda1` with the actual ext2/ext3/ext4 partition available on your Linux system. The tune2fs and dumpe2fs commands are not suitable for every file system.

### Expected Evidence to Record

The following details should be recorded from the command outputs:

1. Inode number
2. Block size
3. Total blocks
4. Free blocks
5. Total inodes
6. Free inodes

### Alternative Concept and Complexity Analysis

If the database server used a copy-on-write file system such as Btrfs or ZFS instead of ext4 journaling:

### Comparison

| Parameter | ext4 | Btrfs / ZFS |
|---|---|---|
| Consistency | Journaling | Copy-on-write |
| Snapshots | Requires external support | Built-in |
| Checksums | Metadata checksums | Data and metadata checksums |
| Recovery | Journal replay | Consistent snapshots and metadata |
| Random Writes | Generally efficient | Can incur CoW overhead |
| Storage Overhead | Lower in many workloads | Additional snapshot and metadata space |

### Time Complexity

1. **Ordinary Indexed File Lookup:** Approximately O(log n) with suitable indexing.

2. **Snapshot Creation:** Generally close to O(1) initially through metadata references.

3. **Recovery:** Depends on journal or metadata size and the number of changes to replay.

### Conclusion

ext4 is suitable for general Linux workloads, while Btrfs and ZFS provide additional data-integrity and snapshot features for advanced storage environments.

