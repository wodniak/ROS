#include "ros/ros.h"
#include "std_msgs/String.h"
#include <geometry_msgs/TransformStamped.h>
#include <sstream>
#include <iostream>
#include <string>



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

    uint count = 0;

    /*
     *  Get input from user terminal
     *  @return vector with parsed numbers
     */
    std::vector<int> parseInput(void);

    /*
     *  Fill geometry_msgs transform data with parsed input
     *  @param vec : 
     *  @param rot :
     *  @return : result code
     */
    int getInputFromUser(geometry_msgs::Vector3 & vec, geometry_msgs::Quaternion & rot);

public:
    PublisherBase(const char * topicName, const uint loop_rate);
    void publish(void);
};
