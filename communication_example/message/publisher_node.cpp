#include "ros/ros.h" 
#include "std_msgs/String.h"
#include <sstream>


int main(int argc, char **argv)
{
  ros::init(argc, argv, "pub_node"); //initialize ROS. name Node.
  ros::NodeHandle n; //create node handle

  ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000); //define publisher by advertise(). It sends pub node info to master. 1000=howmany messages to save.

  ros::Rate loop_rate(10); //loop period 10Hz

  int count = 0; //count sent message number
  
  while (ros::ok())
  {
    std_msgs::String msg; //message type: std_msgs(bool, char, float, int, str...)/common_msgs(robot actuator ex.actionlib_msgs, diagnostic_msgs, nav_msgs, sensor_msgs, geometry_msgs) /user defined
    std::stringstream ss;
    ss << "hello world " << count;
    msg.data = ss.str();

    ROS_INFO("%s", msg.data.c_str()); //terminal output. similar to printf()

    chatter_pub.publish(msg); //publish message!

    ros::spinOnce();
    loop_rate.sleep(); //wait until loop period

    ++count; //counting
  }


  return 0;
}
