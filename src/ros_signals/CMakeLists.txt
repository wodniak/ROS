cmake_minimum_required(VERSION 2.8.3)
project(ros_signals)

find_package(
    catkin REQUIRED
    roscpp
    rospy
    roslib
    std_msgs
    message_runtime
    message_generation
)


## Declare ROS messages and services
add_message_files(
    DIRECTORY msg
    FILES pid.msg
    )

## Generate added messages and services
generate_messages(DEPENDENCIES std_msgs)


catkin_package(
    CATKIN_DEPENDS
    roscpp
    rospy
    roslib
    std_msgs
    message_runtime
)


include_directories(
    ${catkin_INCLUDE_DIRS}
    include/
)

#runner
add_executable(runner src/runnerNode.cpp)
target_link_libraries(runner ${catkin_LIBRARIES})
add_dependencies(runner ros_runner_gencpp)

#killer
# add_executable(snapshot src/snapshot.cpp)
# target_link_libraries(
#     snapshot
#     ${catkin_LIBRARIES}
#     ${OpenCV_LIBS}
#     )
# add_dependencies(snapshot ros_snapshot_gencpp)
