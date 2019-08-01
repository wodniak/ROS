#ifndef WEBCAM_H
#define WEBCAM_H

#include "ros/ros.h"
#include <image_transport/image_transport.h>
#include <opencv2/highgui/highgui.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sstream> // for converting the command line parameter to integer


class WebcamImage
{
private:
    ros::NodeHandle nh;
    image_transport::ImageTransport it;
    image_transport::Publisher pub;


public:
    WebcamImage(int videoSource);
    ~WebcamImage();

};

#endif //WEBCAM_H