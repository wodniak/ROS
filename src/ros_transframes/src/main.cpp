#include "tf_publisher_base.hpp"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "publisherBase");
    PublisherBase publisher("sometext", 1);
    publisher.publish();
    
    return 0;
}