cmake_minimum_required(VERSION 2.8.3)
project(ros_webcam)

set(OpenCV_DIR ~/opencv/installation/OpenCV-4.1.1/lib/cmake/opencv4/)

find_package(OpenCV REQUIRED)
find_package(
    catkin REQUIRED
    roscpp
    rospy
    roslib
    sensor_msgs
    cv_bridge
    std_msgs
    image_transport
)

catkin_package(
    CATKIN_DEPENDS
    roscpp
    rospy
    roslib
    std_msgs
    message_runtime
    sensor_msgs
    cv_bridge
    std_msgs
    image_transport
)

add_service_files(
    DIRECTORY srv
    FILES take_snapshot.srv
)

include_directories(
    ${catkin_INCLUDE_DIRS}
    include/
    ${OpenCV_INCLUDE_DIRS}
  )

#webcam
add_executable(webcam src/webcam.cpp)
target_link_libraries( webcam
    ${catkin_LIBRARIES}
    ${OpenCV_LIBS}
    )
add_dependencies(webcam ros_webcam_gencpp)

#snapshot
add_executable(snapshot src/snapshot.cpp)
target_link_libraries(
    snapshot
    ${catkin_LIBRARIES}
    ${OpenCV_LIBS}
    )
add_dependencies(snapshot ros_snapshot_gencpp)
