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
#include <deque>
#include <mutex> 
struct User{
    std::string name;
    int id = -1;
    std::string name_id;
    User(std::string inp_name, int inp_id){
        name = inp_name;
        id = inp_id;
        name_id = inp_name +"#"+ std::to_string(id);
    }
    bool ready = false;
    User() = default;
};
struct Rooms{
    std::string name;
    int id;
    std::vector<User> users;
    int users_num;
    int max_users_num;
    Rooms() = default;
   
};
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
        response_queue.clear();
        close();
    }

    void ask_id();
    void handle_resolve(const boost::system::error_code& err, const boost::asio::ip::tcp::resolver::results_type& endpoints);
    void handle_connect(const boost::system::error_code& error);

    void handle_handshake(const boost::system::error_code& err);

    void handle_write_request(const boost::system::error_code& err);
    void handle_join_room(const boost::system::error_code& err);
    void handle_read_status_line(const boost::system::error_code& err);
    void close();
    inline std::deque<Response>* get_response_queue(){
        return &response_queue;
    }
    void get_all_rooms();
    mutable std::mutex queue_mutex;
    void create_room(std::string room_name, std::string  player);
    void join_room(Rooms room,std::string name);
private:
    void handle_create_room(const boost::system::error_code& err);
    void handle_get_all_rooms(const boost::system::error_code& err);
    std::deque<Response> response_queue;
    boost::asio::ip::tcp::resolver resolver_;
     boost::asio::ssl::stream<boost::asio::ip::tcp::socket> socket_;

    boost::asio::streambuf response_buf_;

    Request request_;
    Response response_;
};






