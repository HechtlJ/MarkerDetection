#include "ros/ros.h"

#include "std_msgs/String.h"
#include "std_msgs/Float64.h"
#include <std_msgs/Float64MultiArray.h>
#include "analyzer.h"

#include <sstream>


void callback(const std_msgs::Float64MultiArray::ConstPtr& msg){
  double x = msg->data[3]; 
  double y = msg->data[7];
  double z = msg->data[11];
  
  std_msgs::String log;

  std::stringstream ss;
  ss << x << " " << y << " " <<z;
  log.data = ss.str();

  ROS_INFO("%s", log.data.c_str());
}


int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "talker");

  ros::NodeHandle n;

  //ros::Publisher chatter_pub = n.advertise<std_msgs::String>("chatter", 1000);
  Analyzer analyzer;

  ros::Subscriber sub = n.subscribe("MarkerDetection/coordinates", 1000, &Analyzer::add_data, &analyzer);

  ROS_INFO("Initialised Analyzer.");


  ros::Rate loop_rate(1);


  
  while (ros::ok())
  {
    
    analyzer.calculate_values();

    my_transform average = analyzer.get_average();
    my_transform min = analyzer.get_min();
    my_transform max = analyzer.get_max();
    my_transform diff = max - min;
    my_transform deviation = analyzer.get_standard_deviation();
    int count = analyzer.get_data_count();

    ROS_INFO("Analysis of %d values:", count);
    ROS_INFO("Average Values: %f %f %f ", average.x, average.y, average.z);
    ROS_INFO("Minimal Values: %f %f %f ", min.x, min.y, min.z);
    ROS_INFO("Maximum Values: %f %f %f ", max.x, max.y, max.z);
    ROS_INFO("Max Difference: %f %f %f ", diff.x, diff.y, diff.z);
    ROS_INFO("Standard Deviation: %f %f %f \n", deviation.x, deviation.y, deviation.z);



    ros::spinOnce();
    loop_rate.sleep();
  }


  return 0;
}