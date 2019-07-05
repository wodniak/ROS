#include "ros/ros.h"
#include "ros_threads/unix_time_now.h"

class ThreadsServer
{
private:
    ros::NodeHandle n;
    ros::ServiceServer srv;

    bool unix_time_now_callback(ros_threads::unix_time_now::Request &req,
                                ros_threads::unix_time_now::Response &res);
public:
    ThreadsServer();
    ~ThreadsServer();
};
