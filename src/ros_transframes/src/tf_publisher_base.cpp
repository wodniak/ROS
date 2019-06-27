#include "tf_publisher_base.hpp"

PublisherBase::PublisherBase(const char * topicName, const uint loop_rate_hz) : 
    loop_rate_hz(loop_rate_hz),
    n()
{
    pub = n.advertise<geometry_msgs::TransformStamped>("base_tf_enu", 1000);
}


std::vector<int> PublisherBase::parseInput(void)
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
        std::cout << std::endl;
    }
    return data;
}


int PublisherBase::getInputFromUser(geometry_msgs::Vector3 & vec, 
                                    geometry_msgs::Quaternion & rot )
{
    // get user input from terminal
    std::vector<int> parsedData = parseInput();
    if (parsedData.size() != 6) 
    { 
        std::cout << "Wrong number of ints"; 
        return 0; 
    }

    // fill vec and rot with data
    vec.x = parsedData[0];
    vec.y = parsedData[1];
    vec.z = parsedData[2];

    rot.x = parsedData[3];
    rot.y = parsedData[4];
    rot.z = parsedData[5];

    return 1;
}


void PublisherBase::publish()
{
    geometry_msgs::TransformStamped msg;

    // create empty data 
    geometry_msgs::Vector3 vec;
    geometry_msgs::Quaternion rot;

    while (ros::ok())
    {        
        // save timestamp
        msg.header.stamp = ros::Time::now();
        
        // update published data if input is valid
        if( getInputFromUser(vec, rot) )
        {
            msg.transform.translation = vec;
            msg.transform.rotation = rot;
        }

        pub.publish(msg);
        ros::spinOnce();
        loop_rate_hz.sleep();
        ++count;
    }
}
