#include "ros/ros.h"
#include "std_msgs/String.h"
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"

ros::Publisher pub;

void chatterCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
	geometry_msgs::Twist speed;
	geometry_msgs::Vector3 angular, linear;

	angular.z = -0.3 * (msg->ranges[0] - msg->ranges[msg->ranges.size() - 1]);
	linear.x = 1;

	speed.angular = angular;	
	speed.linear = linear;
	pub.publish(speed);

  ROS_INFO("Angular-z [%f]", speed.angular.x, speed.angular.y, speed.angular.z);

}
int main(int argc, char **argv)
{
  ros::init(argc, argv, "listener");
  ros::NodeHandle n;
  pub = n.advertise<geometry_msgs::Twist>("/robot/cmd_vel", 1000);
  ros::Subscriber sub = n.subscribe("/robot/base_scan", 1000, chatterCallback);
  ros::spin();

  return 0;
}

