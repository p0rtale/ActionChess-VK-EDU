#include <iostream>
#include <istream>
#include <ostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include "rapidjson/writer.h"
#include <boost/asio/ssl.hpp>
#include <memory>
#include <optional>
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include <string>
#include <bitset>
#include "Client.hpp"
#include "Request.hpp"
#include "Response.hpp"
using boost::asio::ip::tcp;


std::string valueToString(const rapidjson::Value& value) {
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    value.Accept(writer);

    return buffer.GetString();
}

  

void Client::close(){
    socket_.lowest_layer().close();
}
    void Client::handle_resolve(const boost::system::error_code& err,  const tcp::resolver::results_type& endpoints)
    {
        if (!err)
        {
            // Attempt a connection to each endpoint in the list until we
            // successfully establish a connection.
            boost::asio::async_connect(socket_.lowest_layer(), endpoints, \
                                       boost::bind(&Client::handle_connect, this,\
                                                   boost::asio::placeholders::error));
        }
        else
        {
            std::cout << "Error: " << err.message() << "\n";
        }
    }
void Client::handle_connect(const boost::system::error_code& error){
    if (!error)
    {
    socket_.async_handshake(boost::asio::ssl::stream_base::client,
          boost::bind(&Client::handle_handshake, this,
            boost::asio::placeholders::error));
    }
    else
    {
      std::cout << "Connect failed: " << error.message() << "\n";
    }
  }

    void Client::handle_handshake(const boost::system::error_code& err)
    {
        if (!err)
        {
            rapidjson::Document doc;
            auto& allocator = doc.GetAllocator();

            Request updateMessage;
            updateMessage.m_type = RequestType::CREATE_ROOM;

        
            
            rapidjson::Value value(rapidjson::kObjectType);
            value.AddMember("user", rapidjson::Value(rapidjson::kObjectType), allocator);
            value["user"].AddMember("name", "228" , allocator);
            value.AddMember("room2", rapidjson::Value(rapidjson::kObjectType), allocator);
            value["room2"].AddMember("name", "maslo", allocator);
            value["room2"].AddMember("max-users-num", 10, allocator);

            updateMessage.m_data = valueToString(value);

            std::string json;
            updateMessage.toJSON(json);

            // The connection was successful. Send the request.
            boost::asio::async_write(socket_, boost::asio::buffer(json.c_str(), json.size()),
                                     boost::bind(&Client::handle_write_request, this,
                                                 boost::asio::placeholders::error));
            
        }
        else
        {
            std::cout << "Error: " << err.message() << "\n";
        }
    }

    void Client::handle_write_request(const boost::system::error_code& err)
    {
        if (!err)
        {
            boost::asio::async_read_until(socket_, response_buf_, kMessageSeparator,
            boost::bind(&Client::handle_read_status_line, 
                                                                this, 
                                                               boost::asio::placeholders::error
                                                            ));
        }
        else
        {
            std::cout << "Error: " << err.message() << "\n";
        }
    }

    void Client::handle_read_status_line(const boost::system::error_code& err)
    {
        std::cout<<"HERE"<<std::endl;
        if (!err)
        {
            
        //  const auto data =response_buf_.data();
        // std::string str {
        //     boost::asio::buffers_begin(data), 
        //     boost::asio::buffers_begin(data) + transferredBytes - kMessageSeparator.size()
        // };
        std::istream response_stream(&response_buf_);
        std::string str;
        response_stream >> str  ;
        //response_buf_.consume(transferredBytes);
            

        std::cout<<str<<std::endl;
        for (std::size_t i = 0; i < str.size(); ++i)
  {
      std::cout << +(str.c_str()[i]) << "    " << (str.c_str()[i]) << std::endl;
  }
        Request request;
        request.parseJSON(str);
        std::cout<<request.m_data<<std::endl;
        }
        else
        {
            std::cout << "Error: " << err << "\n";
        }
    }





