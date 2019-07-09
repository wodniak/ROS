#include "ros/ros.h"
#include "ros_threads/unix_time_now.h"

/*
 *  Every half a second prints current UNIX time up to nanosecond
 *  very second send /unix_time_now service request with randomly generated ​delay between 0 and 5
 * 
 */
class ThreadsClient
{
private:
    ros::NodeHandle node;
    ros::ServiceClient client;

    ros::Timer timerPrint;
    ros::Timer timerServiceCall;

void printUnixTime(const ros::TimerEvent& e);
void callService(const ros::TimerEvent& e);

public:
    ThreadsClient();
    ~ThreadsClient();
};
