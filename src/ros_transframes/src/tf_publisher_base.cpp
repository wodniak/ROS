#include "tf_publisher_base.hpp"

geometry_msgs::Vector3 PublisherBase::vec;
geometry_msgs::Quaternion PublisherBase::rot;
pthread_mutex_t PublisherBase::mut;

// 
// INPUTPARSER 
// 

std::vector<int> InputParser::parseInput(void)
{
    // vector for parsed data
    std::vector<int> data;
    std::string str;

    if ( std::getline(std::cin, str))
    {
        std::stringstream ss(str);
        int i;

        while (ss >> i)
        {
            data.push_back(i);
            if (ss.peek() == ',') { ss.ignore(); }
        }

        for (i=0; i< data.size(); i++)
        {
            std::cout << data.at(i) << " ";
        }
    }
    return data;
}


void InputParser::getInputFromUser()
{
    while(true)
    {
        // get user input from terminal
        std::vector<int> parsedData = parseInput();

        if (parsedData.size() != 6) 
        { 
            std::cout << "  <-- Wrong number of ints" << std::endl; 
        }
        else
        {
            std::cout << "  <-- Sending" << std::endl; 

            pthread_mutex_lock(&PublisherBase::mut);
         
            // fill vec and rot with data
            PublisherBase::vec.x = parsedData[0];
            PublisherBase::vec.y = parsedData[1];
            PublisherBase::vec.z = parsedData[2];

            PublisherBase::rot.x = parsedData[3];
            PublisherBase::rot.y = parsedData[4];
            PublisherBase::rot.z = parsedData[5];

            pthread_mutex_unlock(&PublisherBase::mut);
        }
    }
}


// 
// PUBLISHERBASE 
// 

PublisherBase::PublisherBase(const char * topicName, const uint loop_rate_hz) : 
    loop_rate_hz(loop_rate_hz),
    n()
{
    pub = n.advertise<geometry_msgs::TransformStamped>("base_tf_enu", 1000);
}


void PublisherBase::publish()
{
    geometry_msgs::TransformStamped msg;

    std::thread io_tread( (InputParser()) );
    io_tread.detach();
    while (ros::ok())
    {        
        // save timestamp
        msg.header.stamp = ros::Time::now();
        // update published data if input is valid

        pthread_mutex_lock(&PublisherBase::mut);

        msg.transform.translation = PublisherBase::vec;
        msg.transform.rotation = PublisherBase::rot;
        pub.publish(msg);

        pthread_mutex_unlock(&PublisherBase::mut);

        ros::spinOnce();
        loop_rate_hz.sleep();
    }
}
