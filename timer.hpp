#ifndef TIMER_H_
#define TIMER_H_

#include<chrono>
#include<string>


class Timer {
    typedef std::chrono::steady_clock::time_point tp;
    typedef std::chrono::duration<double> dd;
    typedef std::chrono::steady_clock sc;
    enum class Status {
        ready, start, pause, stop
    };
private:
    tp _begin;
    dd _span;
    Status _status;
public:
    Timer() : _begin(tp()), _span(dd(0)), _status(Status::ready) {}

    // 时间单位： 秒
    double getTime() {
        return _span.count();
    }

    void start() {
        if (_status == Status::ready || _status == Status::stop) {
            _begin = sc::now();
            _span = dd(0);
            _status = Status::start;
        } else if (_status == Status::pause) {
            _begin = sc::now();
            _status = Status::start;
        }
    }

    void pause() {
        if (_status == Status::start) {
            _span += std::chrono::duration_cast<dd>(sc::now() - _begin);
            _status = Status::pause;
        }
    }

    void stop() {
        if (_status == Status::start) {
            _span += std::chrono::duration_cast<dd>(sc::now() - _begin);
            _status = Status::stop;
        } else if (_status == Status::pause) {
            _status = Status::stop;
        }
    }

    ~Timer() {}
};

#endif // TIMER_H_
