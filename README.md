20200194 남경민
# ROS2 documentation
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

**Important command**
| | command|
|---|---|
|패키지 파일 관리| `roscd`, `rosls`, `roscp`|
|실행| `roscore`, `rosrun`, `roslaunch`, `rosclean`|
|목록| `rosnode list`, `rostopic list`, `rosservice list`|
|빌드 도구| `catkin_create_pkg`, `catkin_make`, `catkin_init_workspace`, `catkin_find`|
|패키지 관리| `rospack`, `rosinstall`, `rosdep`|


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
## Tutorial 2 : Creating a package
https://docs.ros.org/en/foxy/Tutorials/Beginner-Client-Libraries/Creating-Your-First-ROS2-Package.html

#### Package file structure
|**/package (C)**| **/package (Python)**|
|---|---|
|- CmakeLists.txt <br />  - package.xml <br /> - /include<br /> - /src|- CmakeLists.txt <br /> - setup.py <br /> - setup.cfg <br /> - /package <br /> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;- mynode.py <br />  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; - init.py <br /> - /resource <br /> - /test|


#### Creating a package
| Step| directory|code|
|:---|:---:|:---|
|1. create a package| src| - C : `cs && ros2 pkg create --build-type ament_cmake --node-name my_node my_package` <br /> - Python : `ros2 pkg create --build-type ament_python --node-name my_node my_package` <br />(node name is an optinal) |
|2. build a package |ws| `cw && colcon build --packages-select my_package` (package select is an optional)|
|3. source the setup file| ws| `cw && .install/setup.bash`|
|4. use the package|| `ros2 run my_package my_node`|



-----
## ROS structure and build system
https://enssionaut.com/board_robotics/421
ROS 사용자는 다양한 센서와 부품들을 사용하여 로봇을 만들고자 하는데 이때 각 단위로 세부 제어를 할 수 있도록 하는 것은 ROS가 노드화되어있기 때문이다.
<p align="center"><img src="https://enssionaut.com/files/attach/images/122/421/5cd151c762b20a3f137559fb3cf79934.png" height=400></p>

PC - HW connected by UART, TCP/IP, USB,...
HW - actuator/sensors connected by UART, I2C, SPI, PWM, Analog,...
ROS는 ROS가 구동되는 시스템끼리 데이터를 주고 받을 수 있다. 주로 TCP/IP 프로토콜을 통해 데이터가 전달된다.

**Term**
- package: 하나 이상의 노드, 노드 실행에 필요한 정보를 묶어 놓은 것.
- metapackage: package의 묶음
- message : ROS가 데이터를 주고 받는 형식. topic과 topic에 대한 데이터 값을 가지고 있다.
- node : 메세지를 주고 받는 당사자. node는 ROS에서 구동되는 프로그램의 최소 단위이다. 다른 시스템의 ROS 노드와도 메세지를 주고 받을 수 있다.
  - publisher : 메세지를 보내는 노드
  - subscriber : 메세지를 받는 노드
  - server : 서비스를 요청받아 정해진 프로세스를 수행하고 응답하는 노드
  - client : 서비스를 요청하는 노드
- master : 각 노드들의 정보를 가지고 있으며, 어떤 노드가 어떤 토픽으로 메세지를 주고 받으려하는지 관리한다.


-----
## ROS Communication
https://kasimov.korea.ac.kr/dokuwiki/doku.php/activity/public/2021/ros/2
<p align="center"><img src="https://user-images.githubusercontent.com/94614923/215737076-5f3a5cdc-59f3-4664-8627-e18cf0e47c39.png" height=400></p>

| type | 동기 | 방향| 사용|
|:---:|:---:|:---:|---|
| Topic | 비동기 | 단방향| 지속적으로 발생하는 센서 데이터에 적합. 1:n, n:1, n:n 통신 가능.|
| Service | 동기 | 양방향| 클라이언트의 요청이 있을 때만 대답. 1회성.|
| Action | 비동기 | 양방향| 요청 처리 후 응답까지 오래 걸리거나 중간 피드백이 필요한 경우에 적합.|

### 1. Topic (publisher, subscriber)
토픽은 실시간으로 전송되는 단방향성 메시지이다. 퍼블리셔나 서브스크라이버가 중지하지 않는 이상 메시지를 계속 보낸다. 즉, 어떤 값을 지속적으로 읽고 보내야할 때 편리하다.
또한 주고받는 메세지 값을 보관할 수 있어 차후에 이를 분석하거나, 그대로 재현하여 시뮬레이션에 적용가능하다.

####1.1 통신과정
<p align="center"><img src="https://user-images.githubusercontent.com/94614923/215743037-43a77078-e11d-4c48-8069-b29cd88deafb.png" height=300></p>

1. 마스터 구동
2. pub/sub 노드 구동 및 마스터에 노드 정보 전달
3. 마스터가 sub에게 pub정보를 전달
4. sub가 pub에게 접속 요청
5. pub가 sub에게 접속 응답
6. pub가 sub에게 TCP/IP 방식(TCPROS) 접속
7. pub가 sub에게 메세지 전달

####1.2 publisher/subscriber example
- C++: [cpp_pubsub](https://github.com/KyeongminNam/ROS-study/tree/main/communication%20example/cpp_pubsub)
- python: [py_pubsub](https://github.com/KyeongminNam/ROS-study/tree/main/communication%20example/py_pubsub)


-----
### 2. Service (server, client)
####2.1 통신과정
<p align="center"><img src="https://docs.ros.org/en/foxy/_images/Service-MultipleServiceClient.gif" height=400></p>


####2.2 server/client example
- C++: [cpp_srvcli](https://github.com/KyeongminNam/ROS-study/tree/main/communication%20example/cpp_srvcli)
- python: [py_srvcli](https://github.com/KyeongminNam/ROS-study/tree/main/communication%20example/py_srvcli)

-----
### 3. Action (action server, action client)
https://design.ros2.org/articles/actions.html
####3.1 Goal States
<p align="center"><img src="https://user-images.githubusercontent.com/94614923/215743971-cf1499ea-c6dd-4e1a-b938-212c1de705a5.png" height=250></p>

- active states
  - ACCEPTED, EXECUTING, CANCELING
- terminal states
  - SUCCEEDED, ABORTED, CANCLED
- state transitions by action server
  - exetuce, succeed, abort, canceled
- state transitions by action client
  - send_goal, cancel_goal

####3.2 통신과정
<p align="center"><img src="https://docs.ros.org/en/foxy/_images/Action-SingleActionClient.gif" height=400></p>


####3.3 action server/action client example
**Creating an action**
actions are defined in `.action` file format:
```
# Request
---
# Result
---
# Feedback
```
For example,
```
int32 order
---
int32[] sequence
---
int32[] partial_sequence
```

More details in : [action tutorial](https://github.com/KyeongminNam/ROS-study/tree/main/communication%20example/action_tutorials_interfaces)
