#include <iostream>
#include <ros/ros.h>

#include <ekf_bicycle_tracker/Tracker.h>

int main(int argc, char** argv)
{
  ros::init(argc,argv,"ekf_bicycle_tracker");
  ros::NodeHandle nh;

  Tracker tracker(nh);
  ros::spin();
  
  return 0;
}
