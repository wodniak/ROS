#include "threads_server.hpp"


ThreadsServer::ThreadsServer() : n()
{
    srv = n.advertiseService("unix_time_now", &ThreadsServer::unix_time_now_callback, this);
    ROS_INFO("Ready to give unix time.");
    ros::spin();
}


ThreadsServer::~ThreadsServer(){}


bool ThreadsServer::unix_time_now_callback(ros_threads::unix_time_now::Request &req,
                                           ros_threads::unix_time_now::Response &res)
{
    ROS_INFO("SERVER: request: delay=%ld", (long int)req.Delay_s);

    const int delay = req.Delay_s;
    if (delay >= 0 and delay <= 3)
    {
        ros::Duration(delay).sleep();
    }

    ros::Time ros_time = ros::Time::now();
    std::stringstream dataToSend;
    dataToSend << ros_time.sec;
    ROS_INFO("SERVER: Thread ID: %X Sent response time: %s", std::this_thread::get_id(), dataToSend.str());

    res.Time = dataToSend.str();  // send response
    return true;
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "unix_time_now_server");
    ThreadsServer * server = new ThreadsServer();
    return 0;
}