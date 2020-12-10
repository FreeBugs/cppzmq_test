#include <iostream>
#include <zmq.hpp>
#include <thread>
#include "Publisher.hpp"

using namespace std::chrono_literals;

Publisher::Publisher(const std::shared_ptr<zmq::context_t>& ctx) {
    sock = std::make_unique<zmq::socket_t>(*ctx, zmq::socket_type::pub);
    sock->bind("inproc://test");
}

void Publisher::publish_some_stuff() {
    for(auto i = 0; i<10; i++) {
        std::stringstream hello;
        hello << "Hello World " << i;
        auto hello_str = hello.str();

        std::cout << "PUB: " << hello.str() << std::endl;

        zmq::message_t msg(hello_str.length());
        (void)memcpy(msg.data(), hello_str.c_str(), hello_str.length());

        (void)sock->send(msg, zmq::send_flags::none);

        std::this_thread::sleep_for(1s);
    }
}
