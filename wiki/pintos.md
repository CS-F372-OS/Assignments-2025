# Index
- [Introduction](#introduction)
- [Getting Started](#getting-started)
- [Running Pintos commands](#running-pintos-commands)





# Introduction
#TODO: @ass




# Getting Started
- Dependencies:
  - Docker
  - Git
## Creating the Docker Container
- `git clone https://github.com/CS-F372-OS/pintos` - #TODO do we need to submodule this?
- Refer to the [Pintos Manager](wiki/pintos_manager.md) for managing the Docker container.

## Building Pintos
- In the **docker shell**
```bash
cd pintos/src/threads 
make
cd build
pintos --
``` 

Expected output ( need not match exactly):
```
Pintos hda1
Loading............
Kernel command line:
Pintos booting with 3,968 kB RAM...
367 pages available in kernel pool.
367 pages available in user pool.
Calibrating timer...  32,716,800 loops/s.
Boot complete.
```

**Congratulations!** You have successfully built and run Pintos. You can now start working on the assignments. You can use `Ctrl+C` to exit the Pintos shell.

### Additional references
- [Why are we using docker?](docker_why.md)
- [How did the docker commands work?](https://docs.docker.com/reference/dockerfile/)


# Running Pintos commands
- To run Pintos commands, you need to be in the `pintos/src/threads/build` directory.
- To run pintos commands, add a -- before the command you want to run. For example, to run the help command, you would use:
  ```bash
  pintos -- -h 
  ```
- Anything that comes before the `--` is for the emulator, and anything that comes after is for the Pintos kernel.


# Working with the Source Code
- Refer to [Source Code](wiki/source_code.md) for details on how to work with the Pintos source code.