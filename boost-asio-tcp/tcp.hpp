#pragma once

// Libraries
#include <boost/asio.hpp>
#include <boost/core/noncopyable.hpp>
// C/C++
#include <array>
#include <string>

namespace tcp {

class Tcp : private boost::noncopyable {
   public:
    Tcp(boost::asio::io_service& io);
    void start_timer();
    void handle_timer(const boost::system::error_code& error);

    void do_accept();
    void start_socket();

    void receive_message();
    void handle_receive(const boost::system::error_code& ec, std::size_t bytes_recv);

    void broadcast_message();
    void handle_send(const boost::system::error_code& ec, const std::string& message);

    static bool is_valid_config(json::Object& config);

    boost::asio::io_service& _io;
    boost::asio::ip::tcp::socket _socket;
    boost::asio::ip::tcp::acceptor _acceptor;
    boost::asio::deadline_timer _timer;

    json::Object _tcp_json;

    config::Manager& _config;
    wireless::Manager& _wireless;
    std::array<char, 128> _buffer;
    enum { max_length = 1024 };
    char data[max_length];
};

}  // namespace tcp
