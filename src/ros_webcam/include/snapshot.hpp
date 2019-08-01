#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#include "ros/ros.h"
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>


class Snapshot
{
private:
    ros::NodeHandle nh;
    image_transport::Subscriber sub;


public:
    Snapshot(){};
    ~Snapshot(){};


};

#endif //SNAPSHOT_H
