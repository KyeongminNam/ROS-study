#include "ros/ros.h"
#include "std_msgs/String.h"

// funtion to print recieved message data to terminal
void chatterCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("I heard: [%s]", msg->data.c_str());
}


int main(int argc, char **argv)
{

  ros::init(argc, argv, "sub_node");
  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("chatter", 1000, chatterCallback);

  ros::spin(); //execute loop and request callback

  return 0;
}
