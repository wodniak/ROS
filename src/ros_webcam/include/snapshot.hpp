#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#include "ros/ros.h"
#include <image_transport/image_transport.h>
#include <std_srvs/Empty.h>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/highgui/highgui.hpp>
#include <boost/filesystem.hpp>

namespace filesys = boost::filesystem;

/**
 *  Subscribe to topic with camera images
 *  Advertise service take_snapshot which allows to save image to
 *  tmp/webcam directory
 */
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

    /**
     *  Helper function to count previously existing image files
     *  in tmp/webcam directory in order not to overwrite anything
     *  @return : number of images in dir
     */
    uint __countImages();

public:
    Snapshot();
    ~Snapshot();


    /**
     *  Callback function to get newest image from camera
     *  which is saved in lastImage variable
     */
    void imageCallback(const sensor_msgs::ImageConstPtr& msg);


    /**
     *  Callback function for advertised service take_snapshot
     *  Save image from camera in tmp/webcam directory
     *  Service message is empty.
     */
    bool takeSnapshot(std_srvs::Empty::Request& request, std_srvs::Empty::Response& response);
};

#endif //SNAPSHOT_H
