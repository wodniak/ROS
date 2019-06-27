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
)

include_directories(
    ${catkin_INCLUDE_DIRS}
    include/ros_transframes
)

add_executable(tf_publisher_base 
    src/main.cpp 
    src/tf_publisher_base.cpp
)

target_link_libraries(tf_publisher_base
    ${catkin_LIBRARIES}
)

add_dependencies(tf_publisher_base
    ros_transframes_generate_messages_cpp
)

# add_executable(listener src/listener.cpp)
# target_link_libraries(listener ${catkin_LIBRARIES})
# add_dependencies(listener beginner_tutorials_generate_messages_cpp)