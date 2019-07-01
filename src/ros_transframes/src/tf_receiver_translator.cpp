#include "tf_receiver_translator.hpp"

bool ReceiverTranslator::m_flag = false;
geometry_msgs::TransformStamped ReceiverTranslator::msg_ned_callback;
geometry_msgs::TransformStamped ReceiverTranslator::msg_nwu_callback;



void translateCallback(const geometry_msgs::TransformStamped& msg_enu)
{
    geometry_msgs::TransformStamped msg_ned;
    geometry_msgs::TransformStamped msg_nwu;

    /*  ENU ->> NED
    Swap X and Y, invert Z, do not touch W
    Rotate 90 degrees about z axis (yaw) */
    msg_ned.transform.translation.x = msg_enu.transform.rotation.y;
    msg_ned.transform.translation.y = msg_enu.transform.rotation.x;
    msg_ned.transform.translation.z = -msg_enu.transform.rotation.z;
    msg_ned.transform.rotation.x = msg_enu.transform.rotation.y;
    msg_ned.transform.rotation.y = msg_enu.transform.rotation.x;
    msg_ned.transform.rotation.z = -msg_enu.transform.rotation.z;
    msg_ned.transform.rotation.w = msg_enu.transform.rotation.w;
    msg_ned.header.stamp = ros::Time::now();
    msg_ned.child_frame_id = msg_enu.header.frame_id;
    

    /*  ENU ->> NWU
    
    */

    //copy new messages and set flag to send it
    ReceiverTranslator::m_flag = true;
    ReceiverTranslator::msg_ned_callback = msg_ned;
    ReceiverTranslator::msg_nwu_callback = msg_nwu;
}


ReceiverTranslator::ReceiverTranslator() : node(), sub()
{
    pub_ned = node.advertise<geometry_msgs::TransformStamped>("tf_ned", 1000);
    pub_nwu = node.advertise<geometry_msgs::TransformStamped>("tf_nwu", 1000);
}



void ReceiverTranslator::publishTranslatedFrames()
{
    sub = node.subscribe("base_tf_enu", 10, &translateCallback);
    while(ros::ok())
    {
        if(ReceiverTranslator::m_flag)
        {
            pub_ned.publish(ReceiverTranslator::msg_nwu_callback);
            pub_nwu.publish(ReceiverTranslator::msg_nwu_callback);

            ReceiverTranslator::m_flag = false;
        }
        ros::spinOnce();
    }
}


/*
    The incoming quaternion is in ENU frame
    Quaternion ENU <-> NED:
    Swap X and Y
    Invert Z
    Do not touch W
    Rotate 90 degrees about z axis (yaw)
//  */
// tf::Quaternion quaternion_NED_ENU(tf::Quaternion & q)
// {
//     tf::Quaternion q_ENU(q.y, q.x, -q.z, q.w);
//     tf::Vector3 vec(0, 0, 1);
//     tf::Quaternion q_90(vec, 90);
//     q_ENU = q_ENU * q_90;
//     return q_ENU;
// }
