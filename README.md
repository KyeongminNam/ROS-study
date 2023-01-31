# ROS-study
---
**scirobotics review paper for ros2 :** https://www.science.org/doi/10.1126/scirobotics.abm6074  
**example codes :** https://github.com/ros2/examples/tree/rolling/rclcpp  

**shortcut setup** (add to ~/.bashrc)
```
alias cw='cd ~/ros2_ws'                                              # cd to ws
alias cs='cd ~/ros2_ws/src'                                          # cd to src
alias cwb='cd ~/ros2_ws && colcon build'                             # cd to ws and build
alias cws='cd ~/ros2_ws && . install/setup.bash'                     # cd to ws and setup
alias cwbs='cd ~/ros2_ws && colcon build && . install/setup.bash'    # cd to ws and build and setup
```

**ros2 cheat sheet**

![image](https://user-images.githubusercontent.com/94614923/215676521-8c85d053-456b-4483-9be8-1b975511e0e1.png)


-----
## Tutorial 1 : Creating a workspace
https://docs.ros.org/en/foxy/Tutorials/Beginner-Client-Libraries/Creating-A-Workspace/Creating-A-Workspace.html

| Step| directory|code|
|:---|:---:|:---|
|1. source ros2 environment| |` source /opt/ros/foxy/setup.bash ` (add this line to ~/.bashrc)|
|2. create a new directory | home|` mkdir -p ~/ros2_ws/src `|
|3. clone a sample repo | src | `cs && git clone https://github.com/ros/ros_tutorials.git -b foxy-devel`|
|4. resolve dependencies | ws| `cw && rosdep install -i --from-path src --rosdistro foxy -y `|
|5. build colcon| ws| `cw && colcon build` or `cwb`|
|6. source the overlay| new terminal| `source /opt/ros/foxy/setup.bash && cw && . install/local_setup.bash` or `cws`|
|7. run | | `ros2 run turtlesim turtlesim_node`|


-----
## Tutorial 2 : Creating a package (C)
https://docs.ros.org/en/foxy/Tutorials/Beginner-Client-Libraries/Creating-Your-First-ROS2-Package.html

**/package (C)**
- CmakeLists.txt
- package.xml
- /include
- /src

**/package (Python)**
- CmakeLists.txt
- setup.py
- setup.cfg
- /package
  - mynode.py
  - init.py
- /resource
- /test


| Step| directory|code|
|:---|:---:|:---|
|1. create a package| src| `cs && ros2 pkg create --build-type ament_cmake --node-name my_node my_package` (node name is an optinal)|
|2. build a package |ws| `cw && colcon build --packages-select my_package` (package select is an optional)|
|3. source the setup file| ws| `cw && .install/setup.bash`|
|4. use the package|| `ros2 run my_package my_node`|



-----
## ROS structure and build system
https://enssionaut.com/board_robotics/421


![image](https://enssionaut.com/files/attach/images/122/421/5cd151c762b20a3f137559fb3cf79934.png)

PC and HW connected by UART, TCP/IP, USB,...  
HW and actuator/sensors connected by UART, I2C, SPI, PWM, Analog,...


-----
## ROS Communication 1 : message comm (pub, sub)

-----
## ROS Communication 2 : service comm (server, client)

-----
## ROS Communication 3 : action comm (action server, action client)
https://design.ros2.org/articles/actions.html
