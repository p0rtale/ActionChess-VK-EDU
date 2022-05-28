#pragma once

#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/asio/ssl.hpp>
#include <memory>
#include <optional>
#include <string>
#include <bitset>
#include "Request.hpp"
#include "Response.hpp"
#include "Message.hpp"


class Client{
public:
    Client(boost::asio::io_context& io_context,
           const std::string& server, const std::string& port, const std::string& path,boost::asio::ssl::context* sslContext): resolver_(io_context), socket_ {io_context, *sslContext}          
    {

        resolver_.async_resolve(server, port,
                                boost::bind(&Client::handle_resolve, this,
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::results));
    }
    Client() = default;
    ~Client(){
        close();
    }


    void handle_resolve(const boost::system::error_code& err, const boost::asio::ip::tcp::resolver::results_type& endpoints);
    void handle_connect(const boost::system::error_code& error);

    void handle_handshake(const boost::system::error_code& err);

    void handle_write_request(const boost::system::error_code& err);

    void handle_read_status_line(const boost::system::error_code& err);
    void close();

private:

    boost::asio::ip::tcp::resolver resolver_;
     boost::asio::ssl::stream<boost::asio::ip::tcp::socket> socket_;

    boost::asio::streambuf response_buf_;

    Request request_;
    Response response_;
};






