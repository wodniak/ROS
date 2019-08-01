#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#include "ros/ros.h"
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <std_srvs/Empty.h>
#include <opencv2/highgui/highgui.hpp>
#include <boost/filesystem.hpp>

namespace filesys = boost::filesystem;


class Snapshot
{
private:
    ros::NodeHandle nh;
    image_transport::Subscriber sub;
    image_transport::ImageTransport it;

    ros::ServiceServer srv;
    cv::Mat lastImage;

    std::string path;
    uint NoOfImages;

    uint __countImages();
public:
    Snapshot();
    ~Snapshot(){};
    void imageCallback(const sensor_msgs::ImageConstPtr& msg);
    bool takeSnapshot(std_srvs::Empty::Request& request, std_srvs::Empty::Response& response);

};

#endif //SNAPSHOT_H
