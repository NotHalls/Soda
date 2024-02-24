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
• [Visual Studio Community](https://visualstudio.microsoft.com/vs/community/) (Install The Modules Specified Below)<br>
 &emsp; • Desktop Development With C++ <br>
 &emsp; • Game Development With C++ <br>


```bash
# clone the repo
git clone https://github.com/CottonBall74/Soda.git

# update the submodules
git submodule init
git submodule update

# open the folder
cd Soda

# run the build script
Others/premake/premake5.exe <your vs community version (EX: vs2022)>

# few extra steps
go to Soda/submodules/imgui/backends/imgui_impl_opengl3.cpp <br>
(be careful, there is a imgui_impl_opengl3.c file that we dont want to edit. The one we want to edit is imgui_impl_opengl3.cpp)
```

if you are facing any troubles while installing, you can open an issue or a discussion page
