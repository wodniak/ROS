#include "threads_client.hpp"


ThreadsClient::ThreadsClient() : node()
{
    ROS_INFO("Client Started");
    client = node.serviceClient<ros_threads::unix_time_now>("unix_time_now");
    // timerPrint = node.createTimer(ros::Duration(0.5), &ThreadsClient::printUnixTime, this);
    timerServiceCall = node.createTimer(ros::Duration(1.0), &ThreadsClient::callService, this);
    

    ros::spin();    //TODO: Async spinner to handle callbacks in parallel
}


ThreadsClient::~ThreadsClient(){}


void ThreadsClient::printUnixTime(const ros::TimerEvent& e)
{
    ros::Time currentTime = ros::Time::now();
    ROS_INFO("Curent Time: %i.%i", currentTime.sec, currentTime.nsec);
}


void ThreadsClient::callService(const ros::TimerEvent& e)
{
    srand(time(0));
    ros_threads::unix_time_now srv;
    srv.request.Delay_s = rand() % 5;
    std::string response;
    ROS_INFO("Sent number: %i", srv.request.Delay_s);
    
    if (client.call(srv))
    {
        response = srv.response.Time;
        ROS_INFO("Response Time: %s", response);
    }
    else
    {
        ROS_ERROR("Failed to call service unix_time_now");
    }
}



int main(int argc, char **argv)
{
    ros::init(argc, argv, "unix_time_now_client");
    ThreadsClient * client = new ThreadsClient();
    return 0;
}