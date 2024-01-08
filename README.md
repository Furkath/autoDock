# autoDock
A boat self-docking experiment based on RGBD camera and scene reconstruction, position/posture recognition, Minimum-Snap path planning, LAN signal transmission, PID motor control.

## Table of Contents

- [Features](#features)
- [Prerequisite](#Prerequisite)
- [Usage](#usage)
- [Demo](#demo)
<!-- [Contributing](#contributing) -->
<!-- [License](#license) -->
<!-- [Acknowledgements](#acknowledgements) -->

## Features

- RGBD camera shooting, coordinate correction, and scene reconstruction (Point Cloud).
- Boat position/orientation, water elevation, shielding, recognition and denoising algorithm (Computer Vision).
- Path planning algorithm (Minimum Snap) for shortest docking course.
- Timestamp targeted motion control through PID algorithm, optimized by parameter fine-tuning.
- Wireless Telecommunication through Server-Client softAP connection via ESP8266 microchip, for command transmission between PC and SCM on the boat.
- Electromechanic development on Arduino, receiving signal from ESP8266 WiFi module, processing with UNO, and enabling motor reaction by L298N.

## Prerequisite 

<!-- Provide instructions on how to install and set up your project. Include any dependencies and steps needed for a successful installation. -->

```bash
# if a clound center is needed, we can utilize Curl to have internet connection
git clone -b verison https://github.com/curl/curl.git
cd curl-verison
./configure --with-openssl --prefix=$HOME/workingDIR
make
make install
# also, the Eigen header files can be helpful
```
- Arduino
- ROS

## Usage

<!-- Explain how to use your project. Include examples or code snippets if applicable. -->
  
```bash
cp build/CGrender run/
cd run
./CGrender
```
## Demo
![Scene_demo 1](https://github.com/Furkath/GL-Rendering/tree/master/demos/16-41-53.png)
![Scene_demo 2](https://github.com/Furkath/GL-Rendering/tree/master/demos/15-24-34.png)

