#include "threads_client.hpp"


ThreadsClient::ThreadsClient() : node()
{
    ROS_INFO("Client Started");
    client = node.serviceClient<ros_threads::unix_time_now>("unix_time_now");
    timerPrint = node.createTimer(ros::Duration(0.5), &ThreadsClient::printUnixTime, this);
    timerServiceCall = node.createTimer(ros::Duration(1.0), &ThreadsClient::callService, this);
    

    ros::spin();
}


ThreadsClient::~ThreadsClient(){}


void ThreadsClient::startClient()
{
}


void ThreadsClient::printUnixTime(const ros::TimerEvent& e)
{
    ros::Time currentTime = ros::Time::now();
    ROS_INFO("Curent Time: %i.%i", currentTime.sec, currentTime.nsec);
}


void ThreadsClient::callService(const ros::TimerEvent& e)
{
    ROS_INFO("Doing something long");
    ros::Duration(2.0).sleep();    
}



int main(int argc, char **argv)
{
    ros::init(argc, argv, "unix_time_now_client");
    ThreadsClient * client = new ThreadsClient();
    client->startClient();
    return 0;
}