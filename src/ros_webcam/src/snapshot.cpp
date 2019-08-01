#include "snapshot.hpp"


Snapshot::Snapshot() : nh(), it(nh)
{
    cv::namedWindow("view");
    cv::startWindowThread();

    path = "/home/gwozniak/prodrone_tutorials/catkin_ws/src/ros_webcam/tmp/webcam/";
    NoOfImages = __countImages();

    sub = it.subscribe("camera/image", 1, &Snapshot::imageCallback, this);
    srv = nh.advertiseService("take_snapshot", &Snapshot::takeSnapshot, this);
}


Snapshot::~Snapshot()
{
    cv::destroyWindow("view");
}


void Snapshot::imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
    try
    {
        lastImage = cv_bridge::toCvShare(msg, "bgr8")->image;
        cv::imshow("view", lastImage);
        cv::waitKey(30);
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
    }
}


bool Snapshot::takeSnapshot(std_srvs::Empty::Request& request, std_srvs::Empty::Response& response)
{
    std::string imageName = path + std::to_string(++NoOfImages) + ".jpg";
    bool result = cv::imwrite(imageName, lastImage);
    ROS_INFO("take_snapshot srv : result = %i, image_number = %u", result, NoOfImages);

    if(result)
    {
        return true;
    }
    else
    {
        return false;
    }
}


uint Snapshot::__countImages()
{
    uint noOfImages = 0;

    filesys::directory_iterator iter(path);
    for (auto const & file : iter)
    {
        ++noOfImages;
    }

    ROS_INFO("Number of existing images: %u", noOfImages);
    return noOfImages;
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "snapshot");
    Snapshot *sn = new Snapshot();
    ros::spin();
    delete sn;
}
