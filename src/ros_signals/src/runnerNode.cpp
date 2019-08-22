#include "runnerNode.hpp"


Runner::Runner() : nh()
{
    pub_pid = nh.advertise<std_msgs::UInt64>("pid_runner", 10);
    ROS_INFO("Started advertising PID");
}


Runner::~Runner(){}


void Runner::publishPID()
{
    //get Process ID, convert to uint64 and fill the std_msgs
    if(this->pub_pid)
    {
        std::stringstream pid;
        pid << std::this_thread::get_id();

        std_msgs::UInt64 p;
        p.data = std::stoull(pid.str());

        pub_pid.publish(p);
    }

}


void Runner::registerSignals(const std::vector<int> & signals)
{
    ROS_INFO("Register signals...");

    //register
    for(auto & sig : signals)
    {
        signal(sig, Runner::signalHandler);
    }

    //choose terminating signal
    srand(time(0));
    const int index = (rand() % signals.size()) + 1;
    Runner::killer_signal = signals[index];
    ROS_INFO("Registered killer signal : %i", killer_signal);
}


void Runner::signalHandler(int sig)
{
    //terminate
    if(killer_signal == sig)
    {
        ROS_INFO("Terminating with signal: %i", sig);
        exit(sig);
    }
    else    //do nothing
    {
        ROS_INFO("Received signal: %i", sig);
    }
}


void Runner::spin()
{
    ros::Rate loop_rate_hz(5);
    while (nh.ok())
    {
        this->publishPID();
        ros::spinOnce();
        loop_rate_hz.sleep();
    }
}


int main(int argc, char** argv)
{
    ros::init(argc, argv, "runner_node");
    Runner runner = Runner();
    runner.registerSignals(std::initializer_list<int>(
        {SIGABRT, SIGFPE, SIGILL, SIGINT, SIGSEGV}));
    runner.spin();

    return 0;
}