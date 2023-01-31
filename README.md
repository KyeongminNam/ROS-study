# ROS-study

example codes: https://github.com/ros2/examples/tree/rolling/rclcpp

Shortcut Setup
```
alias cw='cd ~/ros2_ws'                                              # cd to ws
alias cs='cd ~/ros2_ws/src'                                          # cd to src
alias cwb='cd ~/ros2_ws && colcon build'                             # cd to ws and build
alias cws='cd ~/ros2_ws && . install/setup.bash'                     # cd to ws and setup
alias cwbs='cd ~/ros2_ws && colcon build && . install/setup.bash'    # cd to ws and build and setup
```
-----
## Tutorial 1 : Creating a workspace
https://docs.ros.org/en/foxy/Tutorials/Beginner-Client-Libraries/Creating-A-Workspace/Creating-A-Workspace.html
#### 1. source ros2 environment
` source /opt/ros/foxy/setup.bash `

 add this line to ~/.bashrc

#### 2. create a new directory
` mkdir -p ~/ros2_ws/src `




-----
## Tutorial 2 : Creating a package (C)
https://docs.ros.org/en/foxy/Tutorials/Beginner-Client-Libraries/Creating-Your-First-ROS2-Package.html

-----
## ROS structure and build system
https://enssionaut.com/board_robotics/421

-----
## ROS Communication 1 : message comm (pub, sub)

-----
## ROS Communication 2 : service comm (server, client)

-----
## ROS Communication 3 : action comm (action server, action client)
https://design.ros2.org/articles/actions.html
