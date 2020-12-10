#ifndef ZMQ_TEST_SUBSCRIBERWORKER_HPP
#define ZMQ_TEST_SUBSCRIBERWORKER_HPP

#include <thread>
#include <memory>
#include <zmq.hpp>

class SubscriberWorker {
public:
    explicit SubscriberWorker(const std::shared_ptr<zmq::context_t>& ctx);
    ~SubscriberWorker();

    void listen();
    void end_listen();

private:
    bool terminate;
    std::thread listener_thread;

    void listener(const std::shared_ptr<zmq::context_t>& ctx) const;
};


#endif //ZMQ_TEST_SUBSCRIBERWORKER_HPP
