cmake_minimum_required(VERSION 2.8.3)
project(ros_transframes)

## Find catkin and any catkin packages
find_package(catkin REQUIRED COMPONENTS 
    roscpp
    rospy
    std_msgs 
    genmsg 
    message_generation
    geometry_msgs
    tf
)

## Declare ROS messages and services
add_message_files(DIRECTORY msg FILES Num.msg)
# add_service_files(DIRECTORY srv FILES AddTwoInts.srv)

## Generate added messages and services
generate_messages(DEPENDENCIES std_msgs geometry_msgs)

## Declare a catkin package
catkin_package(
    CATKIN_DEPENDS 
    roscpp 
    rospy 
    std_msgs 
    message_runtime
    geometry_msgs
    tf
)

include_directories(
    ${catkin_INCLUDE_DIRS}
    include/ros_transframes
)

###
###     TF_PUBLISHER_BASE
###
add_executable(tf_publisher_base 
    src/tf_publisher_base_main.cpp 
    src/tf_publisher_base.cpp
)

target_link_libraries(tf_publisher_base
    ${catkin_LIBRARIES}
)

add_dependencies(tf_publisher_base
    ros_transframes_generate_messages_cpp
)
###
###


###
###     TF_RECEIVER_TRANSLATOR
###
add_executable(tf_receiver_translator 
    src/tf_receiver_translator_main.cpp 
    src/tf_receiver_translator.cpp
)

target_link_libraries(tf_receiver_translator
    ${catkin_LIBRARIES}
)

add_dependencies(tf_receiver_translator
    ros_transframes_generate_messages_cpp
)
###
###
