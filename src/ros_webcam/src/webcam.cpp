#include "webcam.hpp"


WebcamImage::WebcamImage(int videoSource) : nh(), it(nh)
{
    image_transport::Publisher pub = it.advertise("camera/image", 1);

    cv::VideoCapture cap(videoSource);
    // Check if video device can be opened with the given index
    if(!cap.isOpened())
    {
        exit(1);
    }

    cv::Mat frame;
    sensor_msgs::ImagePtr msg;

    ros::Rate loop_rate(5);     //Hz
    while (nh.ok())
    {
        cap >> frame;
        // Check if grabbed frame is actually full with some content
        if(!frame.empty())
        {
            msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", frame).toImageMsg();
            pub.publish(msg);
            cv::waitKey(1);
        }

        ros::spinOnce();
        loop_rate.sleep();
    }
}


WebcamImage::~WebcamImage(){}


int main(int argc, char** argv)
{
    // Check if video source has been passed as a parameter
    if(argv[1] == NULL)
    {
        ROS_ERROR("Video source not passed as parameter.");
        return 1;
    }

    // Convert the passed argument as command line parameter index for the video device to an integer
    std::istringstream video_sourceCmd(argv[1]);
    int videoSource;
    if(!(video_sourceCmd >> videoSource))
    {
        ROS_ERROR("Could not convert passed argument to integer.");
        return 1;
    }

    ros::init(argc, argv, "webcamImage_publisher");
    WebcamImage webcam(videoSource);

}