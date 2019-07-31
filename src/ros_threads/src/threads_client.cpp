#include "threads_client.hpp"


ThreadsClient::ThreadsClient() : node()
{
    ROS_INFO("Client Started");
    client = node.serviceClient<ros_threads::unix_time_now>("unix_time_now");

    timerPrint = node.createTimer(ros::Duration(0.5), &ThreadsClient::printUnixTime, this);

    // define queue for service callbacks
    // ros::CallbackQueue serviceQueue;
    // node.setCallbackQueue(&serviceQueue);

    // //configure timer for service calls
    // ros::TimerOptions serviceTimerOps;
    // serviceTimerOps.callback_queue = &serviceQueue;
    // serviceTimerOps.callback = &ThreadsClient::callService;
    // serviceTimerOps.tracked_object = ros::VoidConstPtr(this);
    // serviceTimerOps.period = ros::Duration(1.0);

    timerServiceCall = node.createTimer(ros::Duration(0.5), &ThreadsClient::callService, this);

    // spawn async spinner
    ros::AsyncSpinner async_spinner(4);
    // start the spinner
    async_spinner.start();
    ros::waitForShutdown();
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

    if (client.call(srv))
    {
        ros::Time ros_time = ros::Time::now();
        response = srv.response.Time;
        int diff = ros_time.sec - std::atoi(response.c_str());
        std::cout << "DIF: " << diff << std::endl;

        ROS_INFO("CLIENT: Time difference: %s", response);
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


