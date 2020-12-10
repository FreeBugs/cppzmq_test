#include <thread>
#include <zmq.hpp>
#include "Publisher.hpp"
#include "SubscriberWorker.hpp"

using namespace std::chrono_literals;

int main() {
    // One context per process. Important for inproc as well.
    auto ctx = std::make_shared<zmq::context_t>(0);

    Publisher p{ctx};

    SubscriberWorker s{ctx};
    s.listen();

    std::this_thread::sleep_for(100ms); // Wait some time before sending
    p.publish_some_stuff();
}