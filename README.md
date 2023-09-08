# Log4Embedded - Fast, Colorful, and Easy-to-Use Logging Library for Embedded Systems

[![License: LGPLv3](https://img.shields.io/badge/License-LGPLv3-blue.svg)](https://www.gnu.org/licenses/lgpl-3.0)

## Overview

**log4embedded** is a lightweight, high-performance logging library crafted for embedded systems and servers, written in C/C++. This library stands out for its speed, colorful output, and ease of integration. With log4embedded, you can efficiently manage logs in your embedded projects while adding a touch of color to make debugging more accessible.

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

### Log generation

- Five different functions to print messages based on the log hierarchy:
	- log_print_critical
	- log_print_error
	- log_print_warning
	- log_print_info
	- log_print_debug
	
	Depending on how important is the event to be logged, you will be calling any of these functions accordingly. However, they will respect the log level previously set in runtime (or the default one). So, e.g.: "log_print_info" will print nothing if selected log level is "WARNING".

### Other considerations
	
This library is NOT thread safe, as it's assumed the configuration will be set right at the beginning of the execution flow. If you implement a multi-threaded application, just call the configuration functions prior to start creating threads.
Anyway, a couple of examples shall be provided with the release.	


## Getting Started

To integrate **log4embedded** into your project, follow these simple steps:

1. Clone the repository:

   ```bash
   git clone https://github.com/ppradillos/log4embedded.git
   ```

2. Build the Library:

At this early stage, a simple Makefile is provided to build the library straight away, but it's recommended to modify it localy to fit your needs. A CMakeList shall replace the Makefile in the future.

	```bash
	cd log4embedded
	make
	```
	
3. Integrate into Your Project:

Link the library with your project and include the appropriate header files. Refer to the documentation for detailed instructions.

4. Begin Logging:

Use the easy-to-use API to add log statements to your code. Customize log levels and colors as needed.

5. Enjoy Enhanced Debugging:

With **log4embedded**, you'll have colorful, performance-optimized logs to help you debug your embedded system.


## License
**log4embedded** is licensed under the GNU Lesser General Public License (LGPL) version 3. You can use, modify, and distribute it in your projects while complying with the terms of the LGPLv3.
You can find the full text of the license [here](https://www.gnu.org/licenses/lgpl-3.0)

## Contributing
Contributions from the community are welcome. Feel free to submit bug reports, feature requests, or pull requests to help us improve log4embedded.


Happy Logging!