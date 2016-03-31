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

bool clear_path = true;

void bumperEvent(const kobuki_msgs::BumperEventConstPtr msg) {
    if(msg->state == kobuki_msgs::BumperEvent::PRESSED) {
        clear_path = false;
    }
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "maelstrom_node");
    ROS_INFO("initializing");
    ros::NodeHandle n;
    ros::Publisher mover = n.advertise<geometry_msgs::Twist>("cmd_vel_mux/input/navi", 1000);
    ros::Subscriber bumperSub = n.subscribe("mobile_base/events/bumper", 1000, bumperEvent);
    while(ros::ok() && clear_path) {
        geometry_msgs::Twist msg;
        msg.linear.x = 0.1;
        msg.angular.z = 0;
        mover.publish(msg);
    }
    if (!clear_path) {
        geometry_msgs::Twist msg;
        msg.linear.x = -0.1;
        mover.publish(msg);
    }
    ros::spin();
}
