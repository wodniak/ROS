#ifndef RUNNER_HPP
#define RUNNER_HPP

/**
 *  Runner handles 5 different types of signals.
 *  At runtime, it chooses randomly one signal, which will stop the program when received.
 *  Every time the program runs it has to choose a different signal.
 *  If any of the other 4 signals are received, the program handles them and continues running
 *  without stopping. If the signal chosen is received, the program has to stop immediately.
 */
class Runner
{
public:
    Runner() { }
    ~Runner() { }
    int handleSignals(int sig);

};





int main()
{
    return 0;
}

#endif //RUNNER_HPP