

This is a fork of the [Nindamani weed removal robot](https://github.com/AutoRoboCulture/Nindamani-the-weed-removal-robot)

## Project Details

We aim to update the hardware and software as used in Nindamani.

Open Weeding Delta,autonomously detects and segment the weeds from crop using [artificial intelligence](https://www.mdpi.com/2077-0472/11/3/222/htm). It's built on ROS2. Open Weeding Delta could be used in any early stage crops for autonomous weeding.

  ![](demo/Nindamani-gif_1.1.gif)
  
  
# Software Specification :

| Parameter | Value |
| ------------- | ------------- |
| Robotics OS | ROS2.0 Foxy |
| System | [Ubuntu 20.04 LTS](https://github.com/Qengineering/Jetson-Nano-Ubuntu-20-image) |
| Kernel | [Realtime kernel](https://orenbell.com/?p=436) |
| Communication | Wireless, Canbus, UART(internal motor control)  |
| Vision |[DepthAI-ROS](https://github.com/luxonis/depthai-ros)|
| AI Framework | Keras |
| Object instance segmentation| [Mask R-CNN](https://www.youtube.com/watch?v=4tkgOzQ9yyo)|
| Programming Language | Python3 & C |

# Software Todo

- Install Nindami on [20.04](https://github.com/Qengineering/Jetson-Nano-Ubuntu-20-image) / Foxy
- Adapt Nindamani for [OakD](https://github.com/precision-sustainable-ag/PhenoCV-WeedCam) [Use nodelet to publish]( https://github.com/luxonis/depthai-ros/issues/9) to [Image_transport](https://github.com/ros-perception/image_common/tree/ros2) [RPIscript may then work](https://github.com/Agroecology-Lab/Open-Weeding-Delta/blob/bf9583d77d922ba66b18a63d69f9571a39000eb1/rpicam_ai_interface/scripts/rpicam_ai_interface.py#L10)
- Add support for TOF sensors/ height adjustment
- Publish speed control ROS2 messages to slow down/stop UGV
- Improve weed/row recognition algorithms


# Hardware Specifications:

Updated [hardware specification in progress](https://github.com/Agroecology-Lab/Open-Weeding-Delta/tree/master/hardware#readme)

| Parameter | Value |
| ------------- | ------------- |
| Degrees of freedom | 3 DOF |
| Error  | ? mm |
| Payload | 0.5 kg |
| Weight | 8 kg |
| Height | TBC to TBC mm |
| Width | TBC mm |
| Arm Reach | TBC sq mm |
| Processor board | Jetson nano Dev Kit |
| Microcontroller | TBC |
| Stepper Motor /BLDC |  48V, 6A, Nema 34, 87 kgcm H.Torque|
| Camera | TBC |
| Wifi card | Intel 8265 |
| USB-TTL cable |  PL2303HX chip |
| Battery | 48V 30ah |

# Datasets
[Latvia 1118 anotated images](https://data.mendeley.com/datasets/nj4vtk4tt6/1) 7,442 weed images (8x species), 411 crop images (6x crops)

[V1 Plant seedings](https://www.kaggle.com/c/plant-seedlings-classification/data) 1.8GB

[V2 Plant seedlings](https://www.kaggle.com/vbookshelf/v2-plant-seedlings-dataset) 2GB

[5000 seedling images](http://dstore.alazhar.edu.ps/xmlui/handle/123456789/279?show=full)

[Cropdeep](https://www.mdpi.com/1424-8220/19/5/1058) seems useful, but data not available?

[CFWD](https://github.com/cwfid) 242 annotated images

[1300 images of sesame/weeds](https://www.kaggle.com/ravirajsinh45/crop-and-weed-detection-data-with-bounding-boxes)

[1700 images of weeds native to Autralia](https://github.com/AlexOlsen/DeepWeeds)


# Features:
  - Fully ROS2 compatible
  - Battery Operated
  - Runtime upto 8-10 hours
  - Robotics Arm based weed removal
  - Weed detection accuracy upto 85%
  - Easy to Operate
 
# Packages
In this section we will install all the necessary dependencies in order to be able to launch nindamani robot:
  - `nindamani_agri_robot` - integrate all launch node of nindamani robot
  - `rpicam_ai_interface` - controlling the rpi camera with AI interface
  - `servo_control` -  controlling the servo motors with ROS2 interface
  - `stepper_control` - controlling the multiple stepper motors with ROS2 interface


# Installation on Jetson Nano Dev Kit

## 1. Ubuntu
  - Download latest SDK image: https://github.com/Qengineering/Jetson-Nano-Ubuntu-20-image
  - Completely Format SD card (should not contain any partition). Use Ubuntu default app **Disks** [Recommeded 64GB SD card]
  - Copy ZIP(jetpack image) file to SD card: https://developer.nvidia.com/embedded/learn/get-started-jetson-nano-devkit#write
  - 
## 2. ROS2 (Foxy)
  - Install ROS2 base: https://index.ros.org/doc/ros2/Installation/Foxy/Linux-Install-Debians/
  - Make sure that you have colcon in your machine if you are installing from Debian packages. `sudo apt install python3-colcon-common-extensions`
  - For adding additional packages use: `sudo apt install ros-$ROS_DISTRO-<package-name>`
  
## 3. ROS2-Tensorflow
 - Install ros2-Tensorflow: https://github.com/alsora/ros2-tensorflow#readme

## 4. Depthai
 - Follow these instructions to install DepthAI: https://docs.luxonis.com/projects/api/en/latest/install/#jetson

## 5. Arduino
  - Follow this repo to install Arduino on Jetson nano: https://github.com/JetsonHacksNano/installArduinoIDE.git
  - To get Temporary access to USB: `sudo chown <user-name> /dev/tty<usb>` and `sudo chmod a+rw /dev/tty<usb>`
  - To set Permenantly change USB device permission: http://ask.xmodulo.com/change-usb-device-permission-linux.html
  - To control arduino from Command line Source:https://github.com/arduino/arduino-cli
  - Clone this repo: `https://github.com/AutoRoboCulture/Arduino-Jetson-nano-interface.git`
  - Place this repo in Arduino Folder  
  
## 5. Wifi
  - To setup default wifi connection(Intel 8265 NGW card) while bootup Source: https://desertbot.io/blog/how-to-add-a-dual-wifi-bluetooth-card-to-a-jetson-nano-intel-8265

# Create ROS2 Workspace
  - follow this steps:
  ```
    mkdir -p ~/nindamani_ws/src
    cd ~/ros2_mara_ws
    colcon build
    cd src
    git clone https://github.com/AutoRoboCulture/nindamani-the-weed-removal-robot.git
  ```

# Clone the Mask R-CNN GitHub Repository:
  1. Code: `git clone https://github.com/BupyeongHealer/Mask_RCNN_tf_2.x`
  2. Copy this cloned repo to `rpicam_ai_interface` package: `cp Mask_RCNN rpicam_ai_interface/.`
  3. Run command: 
      - `cd rpicam_ai_interface/Mask_RCNN`
      - `sudo python3 install setup.py`
  4. Confirm the Library Was Installed: `pip3 show mask-rcnn`


# Download preTrained Model weights 
  - Link for MASK-RCNN [preTrained model](https://drive.google.com/open?id=1bXEOmOsoBLpXQWVvhhJvhD-RjvCLxOAQ)
  - Copy preTrained weights to `rpicam_ai_interface` package: 
      ```
      mkdir rpicam_ai_interface/preTrained_weights
      cp mask_rcnn_trained_weed_model.h5 rpicam_ai_interface/preTrained_weights/.
      ```

# Follow Folder Structure:
  ```
  nindamani_ws
├── build
├── install
├── log
└── src
    ├── nindamani_agri_robot
    │   ├── launch
    │   └── scripts
    ├── rpicam_ai_interface
    │   ├── scripts
    │   ├── preTrained_weights
    │   └── Mask-RCNN
    ├── servo_control
    │   ├── config
    │   ├── scripts
    │   └── srv
    └── stepper_control
        ├── config
        ├── scripts
        ├── src
        └── srv
  ```
  
# Compile nindamani_ws
  - Follow steps:
    ```
    cd nindamani_ws
    colcon build
    ```
 # Dependency
 
 [Stepper Motor library implementation on Arduino](https://github.com/AutoRoboCulture/Arduino-Jetson-nano-stepper-motor-interface.git)
 
 # Launch nindamani robot
  - Make sure source *setup.bash* in *bashrc* before ROS2 launch command: `echo "source /home/<user-name>/nindamani_ws/install/setup.bash" >> ~/.bashrc`
  - ROS2 Launch command: `ros2 launch nindamani_agri_robot nindamani_agri_robot.launch.py`

# Demo video | Proof of Concept

[![IMAGE ALT TEXT HERE](demo/video_link_github.png)](https://www.youtube.com/watch?v=dN5NNDlvku0)

# Potential Improvements

We have presented the concept that how weeds can be detected from crops using Artifical Intelligence and through delta arm robot weeds are removed autonomously. It's not perfect of course as you can see in the **video link** but can be improved. Here are some of our ideas which can improvise this robot in future:

- Gripper design enchancement with end tip as arrow shaped.
- Delta arm reach can be improved with high torque stepper motor. 
- With RTK-GPS and 4 wheeled drive + 4 wheel steering implementation on robot, it will make whole robot working autonomously.
- Need 3D mapping of land using Lidar, for finding variations in height of crops, weeds and ridge.

# References
1. [Mask R-CNN for Object Detection and Segmentation](https://github.com/matterport/Mask_RCNN/)
```
 @misc{matterport_maskrcnn_2017,
  title={Mask R-CNN for object detection and instance segmentation on Keras and TensorFlow},
  author={Waleed Abdulla},
  year={2017},
  publisher={Github},
  journal={GitHub repository},
  howpublished={\url{https://github.com/matterport/Mask_RCNN}},
}
```
2. [Train Mask-RCNN model on Custom Dataset for Multiple Objects](https://github.com/AutoRoboCulture/mask-rcnn-for-multiple-objects.git)

3. [Delta Robot Simulation on Gazebo using MARA-Env](https://github.com/AutoRoboCulture/delta-robot-simulation-gazebo.git)


# Developer's Contact Detail
```
Kevin Patel
Nihar Chaniyara
Email: autoroboculture@gmail.com

# Delta notes

[Inverse Kinematics](https://github.com/giridharanponnuvel/Delta-Robot-Inverse-Kinematics)

[Commercial Igus with 3x linear actuator](https://www.igus.co.uk/product/20433?artNr=DLE-DR-0001)

[Delta X1](https://store.deltaxrobot.com/products/delta-x-basic-kit) 

[TlAlexander planetary gear](https://github.com/tlalexander/brushless_robot_arm#readme)
```
