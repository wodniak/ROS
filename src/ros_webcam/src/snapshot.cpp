#include "snapshot.hpp"

Snapshot::Snapshot() : nh(), it(nh)
{
    cv::namedWindow("view");
    cv::startWindowThread();

    sub = it.subscribe("camera/image", 1, &Snapshot::imageCallback, this);
    srv = nh.advertiseService("take_snapshot", &Snapshot::takeSnapshot, this);
    ros::spin();
    cv::destroyWindow("view");
}


void Snapshot::imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
    try
    {
        cv::imshow("view", cv_bridge::toCvShare(msg, "bgr8")->image);
        cv::waitKey(30);
    }
    catch (cv_bridge::Exception& e)
    {
        ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
    }
}


bool Snapshot::takeSnapshot(std_srvs::Empty::Request& request, std_srvs::Empty::Response& response)
{
    ROS_INFO("TAKE_SNAPSHOT");
}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "snapshot");
    Snapshot *sn = new Snapshot();
}
