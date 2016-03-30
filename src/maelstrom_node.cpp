#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <kobuki_msgs/BumperEvent.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "sensor_msgs/Image.h"
#include "maelstrom/TagList.h"


void tagListCallback(const maelstrom::TagList::ConstPtr& tagList) {

}

void bumperCallback(const kobuki_msgs::BumperEvent::ConstPtr& bumperEvent) {

}

class MaelstromMapHelper {
private:
  ros::NodeHandle n_;
  ros::Subscriber tagSub_;
  ros::Subscriber bumperSub_;
  ros::Publisher mover_;
  bool pathIsClear_;

public:
  MaelstromMapHelper() {
    ROS_INFO("MaelstromMapHelper Initialized");
    // setup publishers and subscribers
    tagSub_ = n_.subscribe("results", 1000, tagListCallback);
    mover_ = n_.advertise<geometry_msgs::Twist>("cmd_vel_mux/input/navi", 100);
    bumperSub_ = n_.subscribe("mobile_base/events/bumper", 1000, bumperCallback);
    ros::spin();
    zigzag();
  }

  bool pathIsClear() {
    return pathIsClear_;
  }

  bool setPathClear(bool new_val) {
    pathIsClear_ = new_val;
  }

  zigzag() {
    int count = 0;
    ros::Rate loop_rate(5);
    while(ros::ok() && pathIsClear()) {
      geometry_msgs::Twist msg;
      msg.linear.x = 0.01;
      msg.angular.z = 0;
      mover_.publish(msg);
      loop_rate.sleep();
      ++count;
      ros::spinOnce();
    }
  }
};

class MaelstromMapHelper {
private:
  static ros::NodeHandle n_;
  static ros::Subscriber tagSub_;
  static ros::Publisher mover_;
  static bool pathIsClear_;
public:
  init() {
    ROS_INFO("Initializing");
    MaelstromMapHelper::tagSub_ = MaelstromMapHelper::n_.subscribe("results", 1000, );
    MaelstromMapHelper::mover_ = MaelstromMapHelper::n_.advertise<geometry_msgs::Twist>("cmd_vel_mux/input/navi", 100);
    MaelstromMapHelper::bumperSub_ = MaelstromMapHelper::n_.subscribe("mobile_base/events/bumper", 1000, );
    ros::spin();
    MaelstromMapHelper::zigzag();
  }

  zigzag() {
    int count = 0;
    ros::Rate loop_rate(5);
    while(ros::ok() && pathIsClear()) {
      geometry_msgs::Twist msg;
      msg.linear.x - 0.01;
      msg.angular.z = 0;
      mover_.publish(msg);
      loop_rate.sleep();
      ++count;
      ros::
    }
  }
}

int main(int argc, char** argv) {
  ros::init(argc, argv, "maelstrom_node");
  MaelstromMapHelper::init();
  return 0;
}
