# Soda

[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
## Description

Soda is an open-source Game Engine I'm making to learn more about graphics development. <br>


## Progress Till Now
![Screenshot 2024-01-13 150425](https://github.com/CottonBall74/Soda/assets/64028676/d20d27b9-496f-442f-b62b-59df58f3aea4)
![SodaEngine2D](https://github.com/CottonBall74/Soda/assets/64028676/98a43d97-fb66-4201-8d7d-488a839f04a7)
![SodaEngine](https://github.com/CottonBall74/Soda/assets/64028676/83cd7163-aa3b-4547-9df4-0ef8b37fdfd1)

Soda is a Game Engine that is constantly in development by a single person. And it will probably stay that way for a while because i want to keep adding new and fun features/mechanics to the Engine. If you have any specific features or improvements you'd like to see, please open an issue or a discussion. I would appreciate that.

**Note:** The roadmap is subject to change, and new features may be added or adjusted based on community feedback and other needs.



## Getting Started
Follow these instructions to get a copy of the project up and running on your local machine for development and testing purposes.


## deps
make sure you have these installed on your computer <br>
- [cmake](https://cmake.org/download/)
- [clang](https://github.com/llvm/llvm-project/releases/tag/llvmorg-17.0.1)
- [ninja](https://github.com/ninja-build/ninja/releases) <br>
if you are on windows then you can also use [scoop](https://scoop.sh/). <br>
in case you dont know what scoop is, check it out, its a great tool. <br>
##### NOTE: make sure you add cmake, clang and ninja to your $SYSTEM_PATH


# DOESNT SUPPORT LINUX YET #

# building
## cloning the repo
```bash
# NOTE: Make sure you clone the repo with the --recursive flag
git clone https://github.com/CottonBall74/Soda.git --recursive

# open the folder
cd Soda

# update the submodules (just in case)
git submodule init
git submodule update
```
## compiling
```bash
# if you are on windows
./scripts/Run.bat
# if you are on a unix device
./scripts/Run.sh
```
## running the exec
if everything went well then the exec should be in bin/system-build_type-arch/SodaCan.* (by * i mean whatever the exec file is called in your system .exe .out etc...)<br>
i suggest not runnig the file yet. <br>
- first, you should copy the SodaCan.* to a new folder
- then, you should copy the imgui.ini in SodaCan/ project folder to the folder you put the SodaCan.* in

if you are facing any troubles while installing, you can always open an issue
