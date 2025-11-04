# Linux Device Driver Assignment

-----

## Important Notes

  * All assignments are designed for a **Linux environment**.
  * Starting from Level 2, using a **Virtual Machine (VM) is MANDATORY** for compiling and loading kernel modules. Mistakes in kernel code can crash your system, but crashing a VM is safe and recoverable.
  * You will need `sudo` access on your Linux system/VM.
  * Basic familiarity with Linux command-line tools (`ls`, `cd`, `cat`, `grep`, `sudo`) is assumed. Basic C knowledge will be needed for later levels.
  * Save your work, outputs, and explanations to answer the questions below.

-----

## Level 1: Introduction & System Interaction

**Goal:** Understand the role of drivers/modules, identify them on a running system, and learn basic management commands.

### Assignment 1.1: Exploring Kernel Modules

#### Learning Objectives

  * Understand that drivers are often implemented as loadable kernel modules (`.ko` files).
  * Identify currently loaded modules on your system.
  * Find where module files are stored.
  * Inspect module information (description, dependencies, parameters).

#### Theoretical Background (Brief)

Linux uses kernel modules (`.ko` files) to dynamically load code, like device drivers, into the running kernel. This keeps the base kernel smaller and allows support for hardware to be added/removed easily.

#### Questions (Based on Practical Tasks & Deliverables)

1.  What command did you use to find your running kernel version, and what was the version?
2.  What is the full path to the directory where kernel modules for your specific kernel version are stored?
4.  What command lists all currently loaded kernel modules? Provide the first 5 lines of its output.
5.  Identify a kernel module related to networking on your system:  
    a. What command(s) did you use to find your active network device and its associated kernel driver module?  
    b. What is the name of your network device (e.g., `eth0`)?  
    c. What is the name of the kernel module associated with this network device?

6.  For the network module you identified in question 5, what was the output of `modinfo <network_module_name>`.

8.  *(Think...)* Based on the `modinfo` outputs, what do you infer is the purpose of the `depends` field? Explain your reasoning.

-----

### Assignment 1.2: Device Files and Major/Minor Numbers

#### Learning Objectives

  * Understand that devices are represented by special files in `/dev`.
  * Distinguish between character and block devices.
  * Understand the role of Major and Minor numbers in linking device files to drivers.
  * Use `/proc/devices` to see registered drivers.

#### Theoretical Background (Brief)

Linux uses device files in `/dev` as user-space interfaces to kernel drivers. Each device file has a type (character 'c' or block 'b'), a Major number (identifying the driver), and a Minor number (identifying the specific device instance managed by that driver).

#### Questions (Based on Practical Tasks & Deliverables)

1.  Study the output of 5 lines of the output from `ls -l /dev`.
2.  Identify the device file for your primary hard disk/SSD (e.g., `/dev/sda`). What is its type (block 'b' or character 'c'), Major number, and Minor number?
3.  Identify the device file for your current terminal (e.g., `/dev/tty1` or `/dev/pts/x`). What is its type, Major number, and Minor number?
4.  Identify the device files `/dev/null` and `/dev/random`. What are their types, Major numbers, and Minor numbers?

5.  *(Think...)* Why do `/dev/null` and `/dev/zero` often share the same Major number but have different Minor numbers? What might this imply about how they are handled by the kernel?

-----

### Assignment 1.3: Basic Module Management & Kernel Logging

#### Learning Objectives

  * Learn how to load and unload modules using `modprobe` and `rmmod`.
  * Understand potential issues when unloading modules (e.g., "module in use").
  * Use `dmesg` to view kernel messages, including those from modules being loaded/unloaded.

#### Theoretical Background (Brief)

Administrators can manually load (`modprobe`, `insmod`) and unload (`rmmod`) modules. `modprobe` is generally preferred as it handles dependencies. The kernel logs events (including module activity) to a ring buffer, which can be viewed with `dmesg`. **Perform these actions in a VM unless you are certain the module is safe to unload.**

#### Questions (Based on Practical Tasks & Deliverables)

1.  Identify a safe module like `pcspkr`.  
    a. What command checks if `pcspkr` is loaded? Provide its output.  
    b. If loaded, (optionally clear `dmesg`), attempt to unload it using `sudo rmmod pcspkr`. What command verifies it's gone? Provide its output.  
    c. Provide the output of `sudo dmesg | tail` showing the unloading message.
2.  Load the `pcspkr` module using `sudo modprobe pcspkr`.  
    a. What command verifies it's loaded? Study its output.

3.  *(Think...)* Besides `modprobe` and `rmmod`, the original document mentions `insmod`. What is the key difference between `insmod` and `modprobe` for loading modules? When might you prefer one over the other?

-----

## Level 2: The Driver Ecosystem & Basic Structure

**Goal:** Explore the `sysfs` filesystem, set up a build environment, and compile/load a minimal "Hello World" kernel module. **Use a VM for all tasks in this level.**

### Assignment 2.1: Exploring Sysfs (`/sys`)

#### Learning Objectives

  * Understand the purpose of the `sysfs` virtual filesystem.
  * Navigate `sysfs` to find information about devices and drivers.
  * Understand how `sysfs` represents device-driver relationships.

#### Theoretical Background (Brief)

`sysfs` (mounted at `/sys`) provides a structured view of kernel objects, devices, and drivers. Unlike `/dev` (device nodes) or `/proc` (process info), `/sys` exposes attributes and relationships, used heavily by tools like `udev`.

#### Questions (Based on Practical Tasks & Deliverables)

1.  Identify your primary network interface (e.g., `eth0`). What is its name?
2.  What is the full path to your network interface's directory within `/sys/class/net/`?
3.  Provide the output of `ls -l` for this directory.
4.  Study the output of `cat` for the attribute files: `address`, `operstate`, and one other attribute file of your choice from that directory (e.g., `mtu`, `speed`).
5.  What is the output of `ls -l device` run from within your network interface's `sysfs` directory?
6.  Navigate into the target directory of the `device` symlink. What is the output of `ls -l driver` run from this `device` directory?

7.  Navigate into the target directory of the `driver` symlink. Study the output of `ls -l` for this driver directory.
8.  *(Think...)* How does the directory structure within `/sys` (e.g., `/sys/class`, `/sys/bus`, `/sys/devices`) help organize information about the system's hardware and drivers?

-----

### Assignment 2.2: Kernel Module Build Environment Setup

#### Learning Objectives

  * Understand the need for kernel headers matching the running kernel.
  * Install the appropriate kernel headers.
  * Understand the basic structure of a kernel module Makefile.
  * Successfully compile a minimal kernel module using `make`.

#### Theoretical Background (Brief)

Kernel modules must be compiled against the headers and configuration of the specific kernel they will run on. A simple Makefile is used to invoke the kernel's build system.

#### Practical Tasks (Questions)

1.  Ensure kernel headers are installed for your running kernel.  
    a. What command did you use for your distribution (Debian/Ubuntu or Fedora)?  

2. Write a C source file named hello.c that functions as a loadable Linux Kernel Module.  
    a. When the module is loaded it must print the exact message `"Hello from OS"` to the kernel log.  
    b. When the module is unloaded, it must print the exact message `"Bye from OS"` to the kernel log.

3. Make sure to make `hello.c` and `Makefile`.

-----

### Assignment 2.3: Loading and Observing Your Custom Module

*(Requires successful completion of 2.2)*

#### Learning Objectives

  * Load a custom-compiled kernel module using `insmod`.
  * Unload the module using `rmmod`.
  * Verify module loading/unloading using `lsmod` and `dmesg`.
  * Observe `printk` messages from the module.

#### Theoretical Background (Brief)

`insmod` is used to load modules directly from their `.ko` file (useful for testing). `rmmod` unloads them. Messages printed using `printk` within the module's `init` and `exit` functions will appear in the kernel log, viewable with `dmesg`.

#### Questions (Based on Practical Tasks & Deliverables)

1.  Navigate to your `hello_module` directory. Compile the module if you haven't already: `make`.
2.  (Optional) Clear kernel log: `sudo dmesg -c > /dev/null`.
3.  What is the command to load your module?
4.  What is the command to check the kernel log for your init messages? Study the relevant `dmesg` output.

6.  What is the command to check the kernel log for your exit message? Provide the relevant `dmesg` output.
7.  *(Think...)* What would happen if you tried to `insmod` a module that was compiled for a different kernel version than the one currently running? Why?

-----

## Level 3: Character Device Drivers

**Goal:** Understand character device registration, device file creation, and implement basic read/write operations in a module. **Use a VM.**

***

### **Assignment 3.1: Registering a Character Device**

**Goal:** Write a kernel module that registers itself as a character device driver with the kernel and verifies its registration.

---

#### **Tasks & Questions**

1.  **Setup and Code**
    * In a new directory (e.g., `~/chardev_module`), create a `Makefile` and a C source file named `chardev.c`.
    * Populate the `Makefile` to build a kernel module from `chardev.o`.
    * Write the C code for `chardev.c` to perform the following actions:
        * Include the necessary headers for a module that interacts with the filesystem (`linux/fs.h`).
        * In your module's initialization function, use `register_chrdev()` to dynamically request a Major number for a device named `"mychardev"`.
        * Print the assigned Major number to the kernel log upon successful registration.
        * In your module's exit function, unregister the character device using `unregister_chrdev()`.
    * **Deliverable:** Provide the final, complete source code for your `chardev.c` and `Makefile`.

2.  **Compilation and Loading**
    * Compile your module using `make`.
    * Load the compiled module into the kernel using `sudo insmod ./chardev.ko`.

3.  **Verification (Loading)**
    * Check the kernel log to find the messages from your module's initialization function.
    * **Deliverable:** Provide the output from `dmesg | tail` that shows the registration message. What specific Major number did the kernel assign to your `mychardev` device?

4.  **Verification (`/proc/devices`)**
    * Confirm that your device is now listed by the kernel.
    * **Deliverable:** Provide the output of `cat /proc/devices | grep mychardev` while the module is loaded.

5.  **Unloading and Verification**
    * Unload your module from the kernel.
    * **Deliverable:** Provide the `dmesg | tail` output showing the unregistration message.
    * **Deliverable:** After the module is unloaded, run `cat /proc/devices | grep mychardev` again. Provide the output (it should be empty).

6.  **Analysis *(Think...)* **
    * The `register_chrdev(0, ...)` function call uses `0` as its first argument. What is the significance of this value? The code comments in the example hint at a more robust function for this task. What is that function, and why is it preferred in modern, real-world drivers?

---

### **Assignment 3.2: Creating Device Files (`mknod`) & Permissions**
*(Requires successful completion of 3.1)*

**Goal:** Manually create a character device file in `/dev` that connects to your running kernel module and manage its permissions.

---

#### **Tasks & Questions**

1.  Load the `chardev.ko` module you created in Assignment 3.1. What Major number was assigned this time? (Check `dmesg`).

2.  Using the Major number from the previous step, what is the exact `mknod` command required to create a character device file named `/dev/mychardev` with a Minor number of 0?

3.  After creating the device node, provide the output of `ls -l /dev/mychardev`.

4.  What command is used to change the permissions of `/dev/mychardev` to be readable and writable by everyone (mode 666)? Provide the output of `ls -l /dev/mychardev` after changing the permissions.

5.  When you are finished, clean up by removing the device node and unloading the kernel module.

6.  Explain why you don't typically need to run `mknod` manually when you plug in a standard device like a USB drive. What is the role of the `udev` system in this process?

7.  *(Think...)* What might happen if you were to create a device node using an incorrect Major number (one not currently registered by any driver)? What if you used a valid Major number but a Minor number that the driver isn't designed to handle?

---

### **Assignment 3.3: Implementing Basic File Operations (read/write)**
*(Requires successful completion of 3.1 and 3.2)*

**Goal:** Extend your character driver to support basic file operations (`open`, `release`, `read`, `write`) so that user-space programs can interact with it.

---

#### **Tasks & Questions**

1.  **Modify `chardev.c`**
    * Enhance your `chardev.c` from Assignment 3.1 to implement read and write functionality. Do not use any provided skeleton code. You must implement the following:
        * A static, kernel-space buffer (e.g., a `char` array of 80 bytes) to hold a message.
        * A `struct file_operations` that points to your custom functions for `open`, `release`, `read`, and `write`.
        * An `open` function that allows only one process to have the device open at a time. It should also increment the module's usage count.
        * A `release` function that decrements the module's usage count when the device is closed.
        * A `write` function that safely copies data from a user-space buffer into your kernel-space buffer using `copy_from_user()`.
        * A `read` function that safely copies data from your kernel-space buffer to a user-space buffer using `copy_to_user()` (or `put_user()`).
        * Modify your module's `init` function to pass your `struct file_operations` to the kernel during device registration.
    * **Deliverable:** Provide the final, complete source code for your modified `chardev.c`.

2.  **Testing**
    * Compile the module, load it, find its Major number, create the device node (`mknod`), and set its permissions (`chmod 666`).

3.  **Read Operation**
    * Initialize your kernel buffer with a default message in your `init` function (e.g., "Initial message!").
    * **Deliverable:** Provide the output of running `cat /dev/mychardev`.
    * **Deliverable:** Provide the relevant output from `dmesg | tail` showing the trace messages from your `open`, `read`, and `release` functions.

4.  **Write Operation**
    * **Deliverable:** What is the command to write the string "Hello from user space" into your device?
    * **Deliverable:** After executing the write command, provide the relevant `dmesg | tail` output showing the trace messages, including the message received by your `write` function.

5.  **Verify Write**
    * **Deliverable:** Run `cat /dev/mychardev` again. What is the output?

6.  **Cleanup**
    * Unload the module and remove the device node.

7.  *(Think...)*
    * The `device_open` function described above implements a simple single-open policy. Why might a device driver need to restrict access to a single process at a time? What are the roles of `try_module_get()` and `module_put()` in the open/release functions, and why are they critical for module stability?
