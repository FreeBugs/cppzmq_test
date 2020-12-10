#ifndef ZMQ_TEST_PUBLISHER_HPP
#define ZMQ_TEST_PUBLISHER_HPP


class Publisher {
public:
    explicit Publisher(const std::shared_ptr<zmq::context_t>& ctx);
    void publish_some_stuff();

private:
    std::unique_ptr<zmq::socket_t> sock;
};


#endif //ZMQ_TEST_PUBLISHER_HPP