#include "ros/ros.h"
#include "ros_threads/unix_time_now.h"
#include <thread>
#include <chrono>
#include <mutex>

typedef struct
{
    ros_threads::unix_time_now::Request * req;
    ros_threads::unix_time_now::Response * res;
    ros::Time time;

}serverAnswer;


class ThreadsServer
{
private:
    ros::NodeHandle n;
    ros::ServiceServer srv;

    std::mutex response_mutex;

    bool unix_time_now_callback(ros_threads::unix_time_now::Request &req,
                                ros_threads::unix_time_now::Response &res);

    void send_response(serverAnswer & ans);
public:
    ThreadsServer();
    ~ThreadsServer();
};
