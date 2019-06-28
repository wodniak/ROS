#ifndef RECEIVER_TRANSLATOR_H
#define RECEIVER_TRANSLATOR_H

#include "tf_publisher_base.hpp"
#include <tf/transform_broadcaster.h>


/*
 *  It subscribes to ​ world/base_tf_enu, converts it into NED and NWU.
 *  Publishes converted reference frames into ​ world/tf_ned ​and world/tf_nwu accordingly
 */
class ReceiverTranslator 
{
private:
    ros::NodeHandle node;
    ros::Subscriber sub;
    ros::Publisher pub;

public:
    ReceiverTranslator();
    void publishTranslatedFrames();

    static bool m_flag;
    static geometry_msgs::TransformStamped msg_callback;
};

/*
 *  Receive transfer frame world/base_tf_enu
 *  Translate data from ENU to NED and NWU
 * 
 *  @param msg : received TF base_tf_enu 
 */
void translateCallback(const geometry_msgs::TransformStamped& msg);


#endif // RECEIVER_TRANSLATOR_H
