Here’s the updated **`tasks.md`** with explicit tasks for implementing **demand paging during page faults**, integrated with your existing content:

---

# Demand Paging Assignment - Tasks

## 1. Setup and Branching

Your repository has two remotes:

* `public` → The public repository containing the assignment.
* `origin` → Your personal fork.

### Steps:

1. **Fetch the public branch:**

```bash
git fetch public demand-paging-assignment
```

2. **Create and switch to a local branch:**

```bash
git checkout -b demand-paging public/demand-paging-assignment
```

3. All work for this assignment should be done on the `demand-paging` branch.

---

## 2. Files Overview

This assignment involves three main files:

### `frame.c`

Handles **physical frame allocation and eviction**.

* Frames represent physical pages in memory.
* Key functions and TODOs:

  * `frame_init()` → Initialize all frames at startup.
  * `frame_alloc_and_lock(struct page *p)` → Allocate a frame for a page; evict a frame if memory is full.
  * `frame_free(struct frame *f)` → **TODO:** Mark a frame as free so it can be reused. Do not remove existing lock handling.
  * `frame_lock(struct page *p)` → Lock a page’s frame in memory.
  * `frame_unlock(struct frame *f)` → Unlock a frame, allowing it to be evicted.

---

### `page.c`

Handles **virtual page metadata** and page table management.

* Pages are backed by:

  * **Files** (executables, memory-mapped files)
  * **Swap**
  * **Anonymous memory** (stack, heap)

* Key functions and TODOs:

  * `page_for_addr(const void *addr)` → **TODO:** Round address down, create a temporary page, look up in hash table, return the page if found.
  * `page_in(void *fault_addr)` → Bring the page into memory on a page fault.
  * `page_out(struct page *p)` → Evict the page from memory. Write to swap or file if necessary.
  * `page_allocate(void *vaddr, bool read_only)` → Allocate a new page structure and insert into hash table.
  * `page_deallocate(void *vaddr)` → **TODO:** Remove page from hash table and free memory.
  * `destroy_page()` → Used as a callback for hash table destruction at process exit.

---

### `swap.c`

Handles **swap space management**.

* Key functions:

  * `swap_init()` → Initialize the swap device and bitmap.
  * `swap_in(struct page *p)` → Load a page from swap into memory.
  * `swap_out(struct page *p)` → Write a page from memory into swap.

* Make sure `swap_in` and `swap_out` properly update page metadata.

---

## 3. Assignment Tasks

### 3.1 Frame Management (`frame.c`)

* Implement `frame_free()` to mark frames as free.
* Understand how eviction works when all frames are in use.
* Ensure proper locking to avoid race conditions.

---

### 3.2 Page Management (`page.c`)

* Implement `page_for_addr()` to look up pages in the hash table.

* Implement `page_deallocate()` to remove pages safely.

* Implement **demand paging during page faults**:

  1. Modify `page_fault()` in `userprog/exception.c` to call `page_in()` only for **not-present pages**.

* Ensure that page faults for **read-only violations** or **kernel accesses** are handled by `kill()` (do not demand page them).


## 4. References

* [Memory Allocation](https://pkuflyingpig.gitbook.io/pintos/appendix/reference-guide/memory-allocation)
* [Virtual Addresses](https://pkuflyingpig.gitbook.io/pintos/appendix/reference-guide/virtual-addresses)
* [Page Table](https://pkuflyingpig.gitbook.io/pintos/appendix/reference-guide/page-table)
* [Hash Table](https://pkuflyingpig.gitbook.io/pintos/appendix/reference-guide/hash-table)

---