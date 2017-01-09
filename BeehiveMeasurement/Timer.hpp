#ifndef TIMER_HPP_
#define TIMER_HPP_

class Timer {
public:
    Timer(unsigned long interval, bool autoReset);
    virtual ~Timer();

    void start();
    void stop();
    void reset();

    bool isRunning();
    bool isElapsed();

    void setInterval(unsigned long interval);
    unsigned long getInterval();

    void setAutoReset(bool value);
    bool getAutoReset();

private:
    unsigned long _interval;
    unsigned long _deadline;
    bool _autoReset;
    bool _running;
};

#endif // TIMER_HPP_
