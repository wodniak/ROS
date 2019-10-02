#ifndef ROS_SIGNALS_KILLERNODE_HPP
#define ROS_SIGNALS_KILLERNODE_HPP

#include <ros/ros.h>
#include <csignal>
#include "std_msgs/UInt64.h"
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()


class Killer
{
private:
    ros::NodeHandle nh;
    ros::Subscriber sub_pid;


    uint64_t pid_to_kill;

public:
    Killer();
    ~Killer();

    void getPIDCallback(const std_msgs::UInt64 & msg_pid);
    void tryToKill();
};


#endif //ROS_SIGNALS_KILLERNODE_HPP