#ifndef ROS_SIGNALS_RUNNERNODE_HPP
#define ROS_SIGNALS_RUNNERNODE_HPP

#include <ros/ros.h>
#include <csignal>
#include <thread>
#include <sstream>
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()
#include "std_msgs/UInt64.h"


class Runner
{
private:
    ros::NodeHandle nh;
    ros::Publisher pub_pid;

    static int killer_signal;

public:
    Runner();
    ~Runner();
    void publishPID();
    void registerSignals(const std::vector<int> & signals);
    void spin();


    static void signalHandler(int sig);
};

int Runner::killer_signal = 0;

#endif //ROS_SIGNALS_RUNNERNODE_HPP