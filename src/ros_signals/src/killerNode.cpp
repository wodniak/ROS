#include "killerNode.hpp"

Killer::Killer() :
    nh(),
    pid_to_kill(0)
{
    sub_pid = nh.subscribe("pid_runner", 10, &Killer::getPIDCallback, this);
}


Killer::~Killer(){}


void Killer::getPIDCallback(const std_msgs::UInt64 & msg_pid)
{
    if(pid_to_kill == 0)
    {
        pid_to_kill = msg_pid.data;
        ROS_INFO("KILLER - Registered PID to kill %i", pid_to_kill);

        this->tryToKill();
    }
}


void Killer::tryToKill()
{
    //hardcoded list of possible signals
    std::vector<int> signals = std::initializer_list<int>(
        {SIGABRT, SIGFPE, SIGILL, SIGINT, SIGSEGV});

    //get random index
    srand(time(0));
    int index = (rand() % signals.size()) + 1;
    int curr_sig;
    int result_of_kill;
    ROS_INFO("KILLER - Starting to guess. Registered signal %i", signals[index]);

    //send each signal to terminate other process
    while(!signals.empty())
    {
        curr_sig = signals[index];
        ROS_INFO("KILLER - Signal %i sent", curr_sig);
        if(kill(pid_to_kill, curr_sig) != 0)
        {
            //check if proccess still exists
            result_of_kill = kill(pid_to_kill, 0);
            if(!(result_of_kill == 0 or result_of_kill == EPERM))
            {
                ROS_INFO("KILLER - Process %i killed", pid_to_kill);
                exit(1);    //terminate this proccess
            }
        }
        else
        {
            ROS_INFO("KILLER - Something went wrong while sending %i signal", curr_sig);
        }

        //chosen signal did not kill process, choose new one
        std::remove(signals.begin(), signals.end(), curr_sig);
        index = (rand() % signals.size()) + 1;
        ROS_INFO("KILLER - Deteled %i signal, new signal is %i", curr_sig, signals[index]);
        ros::Duration(1).sleep();
    }
}


int main(int argc, char** argv)
{
    ros::init(argc, argv, "killer_node");
    Killer killer = Killer();
    ros::spin();

    return 0;
}