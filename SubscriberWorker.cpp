#include <iostream>
#include "SubscriberWorker.hpp"

using namespace std::chrono_literals;

SubscriberWorker::SubscriberWorker(const std::shared_ptr<zmq::context_t>& ctx) {
    listener_thread = std::thread(&SubscriberWorker::listener, this, ctx);
    terminate = false;
}

void SubscriberWorker::listener(const std::shared_ptr<zmq::context_t>& ctx) const {
    auto sock = std::make_unique<zmq::socket_t>(*ctx, zmq::socket_type::sub);
    sock->connect("inproc://test");
    sock->set(zmq::sockopt::subscribe, "");

    std::vector<zmq::pollitem_t> p = {{*sock, 0, ZMQ_POLLIN, 0}};
    std::cout << "[LISTENER] starting..." << std::endl;
    while (!terminate) {
        zmq::message_t message;
        (void)zmq::poll(p.data(), 1, 50);

        if (p[0].revents & ZMQ_POLLIN) {
            std::ignore = sock->recv(message, zmq::recv_flags::dontwait);
            std::string rx_string;
            (void)rx_string.assign(static_cast<char *>(message.data()), message.size());
            std::cout << "[LISTENER] received: " << rx_string << std::endl;
        }
    }
    std::cout << "[LISTENER] terminated." << std::endl;
}

void SubscriberWorker::listen() {
}

void SubscriberWorker::end_listen() {
    terminate = true;
    listener_thread.join();
}

SubscriberWorker::~SubscriberWorker() {
    end_listen();
}

