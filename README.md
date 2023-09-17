# Log4Embedded - Fast, Colorful, and Easy-to-Use Logging Library for Embedded Systems

[![License: LGPLv3](https://img.shields.io/badge/License-LGPLv3-blue.svg)](https://www.gnu.org/licenses/lgpl-3.0)

## Overview

**log4embedded** is a lightweight, high-performance logging library crafted for embedded systems and servers, written in C. This library stands out for its speed, colorful output, and ease of integration. With log4embedded, you can efficiently manage logs in your embedded projects while adding a touch of color to make debugging more accessible.

## Motivations behind this project

As a professional software engineer, my experience made my accept log messages play a key role when it comes to figure out things when something breaks in production. The simpler and more visual those logs are, the better.
But, since embedded systems usually suffer from hardware constraints and there are plenty of platforms in this niche, I tried to focus on performance and portability, whilst keeping things visual and simple.

I implemented this library for my side projects, and since I enjoy using it, I decided to make my humble contribution to the Open Source community by sharing it with everyone who may find it useful for them.

## Features

- **Fast and Efficient**: Designed with performance in mind, **log4embedded** ensures minimal impact on your embedded system's resources, making it suitable for resource-constrained environments.

- **Colorful Logs**: Log messages are displayed in vibrant colors to make it easier to spot critical and error issues, warnings, informational messages, and even plain debug messages, enhancing the debugging experience.

- **Ease of Use**: I have designed **log4embedded** with simplicity in mind. You can quickly integrate it into your project, and its straightforward API makes logging a breeze.

- **Portability**: The library only depends on the C standard library. Even the colorful additions are made of ANSI escape sequences, therefore supported by many virtual terminals.

- **File Capable**: **log4embedded** supports log files, just in case you prefer this option rather than printing through the stdout.

## Usage

This library prints colored log messages through the standard output by default. The API provides options to configure the library and generate the log messages: 

### Configuration options

- Enable/disable colors

- Set the log level across the entire project:
	- NO LOGS
	- CRITICAL
	- ERROR
	- WARNING
	- INFO (default option)
	- DEBUG
	
- Set a log file with no colors at all (default option for log files) or with the extra escape sequences for colors just in case you still want to check the log file in a terminal, e.g.: using the "tail -f" command.
- 
  As a remark, to make this library 100% compatible with the standard and avoid dependencies with any OS, if you set a log file path which directories do not exist yet, then the log file SHALL NOT be created. On the other hand, if all directories
  to store the log file already exist, but the log file is the only one missing, the log file shall be created with no problem.

### Log generation

- Five different functions to print messages based on the log hierarchy:
	- log_print_critical
	- log_print_error
	- log_print_warning
	- log_print_info
	- log_print_debug
	
	Depending on how important is the event to be logged, you will be calling any of these functions accordingly. However, they will respect the log level previously set in runtime (or the default one). So, e.g.: "log_print_info" will print nothing if selected log level is "WARNING".

## Recommendations
	
This library is NOT thread safe, as it's assumed the configuration will be set right at the beginning of the execution flow. If you implement a multi-threaded application, just call the configuration functions prior to start creating threads.
A couple of examples shall be provided with the release, regardless.

Five different print functions are provided to meet your needs and make the API more straightforward with self-explanatory names, but since this would be a 3rd party library for any project, it's strongly recommended to wrap this API with an extra layer of yours which could, at the same time, calls any of the 5 functions from just a custom one, with an extra argument that holds the log hierarchy value (CRIT, ERR, WARN, INFO, DBG) to establish the criticality of the log message.

## Getting Started

To integrate **log4embedded** into your project, follow these simple steps:

1. **Clone the repository**:

   ```bash
   git clone https://github.com/ppradillos/log4embedded.git
   ```
<br>

2. **Build the log4embedded library**:

The goal of this library is to be cross-build, so it can run in many embedded platforms. For that reason, this is a CMake project.
For those who are new to CMake, this is a Makefile generator which lets you configure your project based on your compiler, platform and CPU architecture.

- To make it easier to everybody who wants to compile this project from source, there are 3 scripts in the root folder that make the build and packaging directly. Those are:
	* build_linux-x86_64.sh: for Linux x64 targets
	* build_linux-arm.sh: for Linux ARM targets
	* build_linux-x86_64.sh: for Linu aarch64 targets
	
Just pick one of them to run the build process, depending on the platform.
	
- Their purpose is to build the sources, and then generate a tarball package within the newly created 'package/' folder, which itself will contain:
	* The header file
	* The binary file, as dynamic library
	* The executable and source files of the examples, in case you built them.
	* License file
	* This README file
	
This package is all you need to integrate the log4embedded as dynamic library in your project. Take it to where you need it.

- Please, note these scripts depend heaviliy in a set of toolchain files that are provided in the [cmake_build_utilities](https://github.com/ppradillos/log4embedded/tree/master/cmake_build_utilities) folder. Each of them for a different platform and architecture. Asuming GCC:
	* x86_64 Linux
 	* ARM Linux
 	* AARCH64 Linux
	
Therefore, in case you want to customize your toolchain settings or the scripts ran into a build error, please modify these toolchain files locally to fit your local setup.

In case you want to run the build process at your own, you first run CMake tool with some arguments to generate the needed Makefiles, then navigate to the build folder you have selected (the folder where the CMakeLists.txt stands is the build folder by default, that's why is strongly recommended to select the build folder with '-B' option, followed by NO spaces), and then run 'make package' to get your package in the folder you assigned to CMAKE_INSTALL_PREFIX. It all can be made on the Command Line Interface. See this example:

   ```bash
	cd log4embedded
	cmake -B_build/ -DCMAKE_INSTALL_PREFIX=./package -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=cmake_build_utilities/toolchain-file-linux-x86_64.cmake
	cd _build
	make package
   ```
It's better if you create your own script to run all these commands in a single command.

- From the example above, we identify several arguments:
	* B_build: This is the build environment for the CMake project
	* CMAKE_INSTALL_PREFIX: Where the header, binary, examples, license and README will be installed after running the 'make package' command. We highly recommend to set always a custom installation path with no superuser rights, like "package/"
	* CMAKE_BUILD_TYPE: build type, either Debug or Release. Release is the default option
	* CMAKE_TOOLCHAIN_FILE: This is a file for custom settings for the compiler, so that the root CMakeLists.txt can stay more generic. 
			
- Examples:
	* A set of [examples](https://github.com/ppradillos/log4embedded/tree/master/examples) are provided in this project. If you want to build them, add the option
	-DBUILD_EXAMPLES=1 to CMake.
	
As the library will not install in the standard directories where dynamic loaders look for, in Linux systems, you must either install the library manually in e.g.: '/usr/local/lib' or try LD_PRELOAD magic.	

<br>

3. **Integrate into Your Project**:

Only thing you need after building the library is to take the content in the installation folder, include the appropiate header files into your project, and finally link the dynamic library against your executable/library.

<br>

4. **Begin Logging**:

Use the easy-to-use API to add log statements to your code. Customize log levels and colors as needed.

<br>

5. **Enjoy Enhanced Debugging**:

With **log4embedded**, you'll have colorful, performance-optimized logs to help you debug your embedded system.


## License
**log4embedded** is licensed under the GNU Lesser General Public License (LGPL) version 3. You can use, modify, and distribute it in your projects while complying with the terms of the LGPLv3.
You can find the full text of the license [here](https://www.gnu.org/licenses/lgpl-3.0)

## Contributing
Contributions from the community are welcome. Feel free to submit bug reports, feature requests, or pull requests to help us improve log4embedded.


Happy Logging!
