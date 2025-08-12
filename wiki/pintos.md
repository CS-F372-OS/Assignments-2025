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
## Build the docker container:
  ```bash
  # In the project directory of this repo (Assignments-2025)
  docker build . -t pintos 
  ```
# # Run the docker container with the pintos subvolume
- git clone https://github.com/CS-F372-OS/pintos
- Run the docker container with the pintos subvolume:
  ```bash
  docker run -it --rm --name pintos --mount type=bind,source=/absolute/path/to/pintos,target=/home/me/pintos pintos bash
  ```

> You need to provide the correct path to the pintos repo for the above command to work, `type` refers to the path in your computer's file system, `target` refers to where it will be mounted inside the docker container and doesn't need to be touched. you only need to change the `source` path to the absolute path of your cloned pintos repo.

## Building Pintos
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
