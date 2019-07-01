#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/TransformStamped.h>
#include <sstream>
#include <iostream>
#include <string>
#include <thread>


/*
 *  Node constantly takes user input (from keyboard) of 6 numbers divided by coma:
 *  x,y,z,roll,pitch,yaw (xyz coordinates in meters and roll, pitch, yaw in degrees)
 *  And publish transfer frame world/base_tf_enu
 *  every seconds with user specified location and orientation (​ world​ reference frame is in​ ENU​ )
 */
class PublisherBase
{
private:
    ros::NodeHandle n;
    ros::Publisher pub;
    ros::Rate loop_rate_hz;


public:
    PublisherBase(const char * topicName, const uint loop_rate);
    void publish(void);
 
    static pthread_mutex_t mut;
    static geometry_msgs::Vector3 vec;
    static geometry_msgs::Quaternion rot;
};


class InputParser
{
private:
    /*
     *  Get input from user terminal
     *  @return vector with parsed numbers
     */
    std::vector<int> parseInput(void);

    /*
     *  Fill geometry_msgs transform data with parsed input
     *  @important : It writes directly to static variables from PublisherBase class
     */
    void getInputFromUser(void);


public:
    InputParser(){};
    
    void operator()()
    {
        getInputFromUser();
    }
};