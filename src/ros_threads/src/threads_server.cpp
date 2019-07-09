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
    std::cout << std::endl;
    ROS_INFO("request: delay=%ld", (long int)req.Delay_s);
    serverAnswer ans;
    ans.req = &req;
    ans.res = &res;
    ans.time = ros::Time::now();
    ans.res->Time = "alamakota";
    std::thread sendResponse(&ThreadsServer::send_response, this, std::ref(ans));
    ROS_INFO("Spawned response thread, ID: %X, time: %f", sendResponse.get_id(), ans.time.toSec());
    sendResponse.detach();

    return true;
}


void ThreadsServer::send_response(serverAnswer & ans)
{
    const int delay = ans.req->Delay_s; 
    if (delay >= 0 and delay <= 3)
    {
        ros::Duration(delay).sleep();
        // std::this_thread::sleep_for(std::chrono::milliseconds(3000));    
    }

    ros::Time sentTime = ros::Time::now();
    float seconds = sentTime.toSec();
    ROS_INFO("Thread ID: %X Sent response time: %f", std::this_thread::get_id(), sentTime.toSec());
    std::stringstream time;
    time << seconds;

    const std::string timeUnix = time.str();
    std::cout << timeUnix << std::endl;   
    ans.res->Time = timeUnix;
    ans.res->Time = "dupa";
    
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "unix_time_now_server");
    ThreadsServer * server = new ThreadsServer();
    return 0;
}