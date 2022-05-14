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
const std::string kMessageSeparator = "\r\n";

enum class RequestType {
    DEFAULT,

    CREATE_ROOM,
    JOIN_ROOM,
    LEAVE_ROOM,
    USER_LEFT,
    GET_ALL_ROOMS,

    WRITE_MESSAGE,
    NEW_MESSAGE,

    START_GAME,
    GAME_STARTED,
    MAKE_MOVE
};

enum class ResponseStatus {
    UPDATE = 0,
    OK = 200,
    METHOD_NOT_ALLOWED = 405,
    FAILED_DEPENDENCY = 424,
    INTERNAL_SERVER_ERROR = 500,
};

std::string typeToStr(const RequestType type);
RequestType strToType(const std::string& str);

class Message {
public:
    Message() = default;

    virtual ~Message() = default;

    virtual void parseJSON(const std::string& json) = 0;

    virtual void toJSON(std::string& json) const = 0;
};


class Request: public Message {
public:
    RequestType m_type = RequestType::DEFAULT;

    std::string m_data;

    void parseJSON(const std::string& json) override;

    void toJSON(std::string& json) const override;
};
void Request::parseJSON(const std::string& json) {
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    m_type = strToType(doc["type"].GetString());

    if (doc.HasMember("data")) {
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        doc["data"].Accept(writer);
        m_data = std::string(buffer.GetString(), buffer.GetSize());
    } 
}

void Request::toJSON(std::string& json) const {
    rapidjson::Document doc;
    auto& alloc = doc.GetAllocator();
    doc.SetObject();

    rapidjson::Value value;

    const auto type = typeToStr(m_type);
    value.SetString(type.c_str(), alloc);
    doc.AddMember("type", value, alloc);



    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    json = std::string(buffer.GetString(), buffer.GetSize());
    if (!m_data.empty()) {
        json.pop_back();
        json += ",\"data\":";
        json += m_data;
        json += "}";
    }
    json += kMessageSeparator;    
}



class Response: public Message {
public:
    RequestType m_type = RequestType::DEFAULT;

    ResponseStatus m_status = ResponseStatus::OK;

    std::string m_data;

    void parseJSON(const std::string& json) override;

    void toJSON(std::string& json) const override;
};
void Response::parseJSON(const std::string& json) {
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    m_type = strToType(doc["type"].GetString());
    m_status = static_cast<ResponseStatus>(doc["status"].GetInt());

    if (doc.HasMember("data")) {
        rapidjson::StringBuffer buffer;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
        doc["data"].Accept(writer);
        m_data = std::string(buffer.GetString(), buffer.GetSize());
    } 
}

void Response::toJSON(std::string& json) const {
    rapidjson::Document doc;
    auto& alloc = doc.GetAllocator();
    doc.SetObject();

    rapidjson::Value value;

    const auto type = typeToStr(m_type);
    value.SetString(type.c_str(), alloc);
    doc.AddMember("type", value, alloc);

    value.SetInt(static_cast<int>(m_status));
    doc.AddMember("status", value, alloc);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    json = std::string(buffer.GetString(), buffer.GetSize());
    if (!m_data.empty()) {
        json.pop_back();
        json += ",\"data\":";
        json += m_data;
        json += "}";
    }
    json += kMessageSeparator;
}

using boost::asio::ip::tcp;


#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
 std::string valueToString(const rapidjson::Value& value) {
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    value.Accept(writer);

    return buffer.GetString();
}
class Client
{
public:
    Client(boost::asio::io_context& io_context,
           const std::string& server, const std::string& port, const std::string& path,boost::asio::ssl::context* sslContext)
            : resolver_(io_context), socket_ {io_context, *sslContext}
              
    {
        
        // Start an asynchronous resolve to translate the server and service names
        // into a list of endpoints.
        resolver_.async_resolve(server, port,
                                boost::bind(&Client::handle_resolve, this,
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::results));
    }

private:
    void handle_resolve(const boost::system::error_code& err,
                        const tcp::resolver::results_type& endpoints)
    {
        if (!err)
        {
            // Attempt a connection to each endpoint in the list until we
            // successfully establish a connection.
            boost::asio::async_connect(socket_.lowest_layer(), endpoints,
                                       boost::bind(&Client::handle_connect, this,
                                                   boost::asio::placeholders::error));
        }
        else
        {
            std::cout << "Error: " << err.message() << "\n";
        }
    }
void handle_connect(const boost::system::error_code& error){
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

    void handle_handshake(const boost::system::error_code& err)
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

    void handle_write_request(const boost::system::error_code& err)
    {
        if (!err)
        {
            // Read the response status line. The response_ streambuf will
            // automatically grow to accommodate the entire line. The growth may be
            // limited by passing a maximum size to the streambuf constructor.
            boost::asio::async_read_until(socket_, response_buf_, kMessageSeparator,
            boost::bind(
                                          &Client::handle_read_status_line, 
                                                                this, 
                                                                std::placeholders::_1, 
                                                                std::placeholders::_2
                                                            ));
        }
        else
        {
            std::cout << "Error: " << err.message() << "\n";
        }
    }

    void handle_read_status_line(const boost::system::error_code& err, std::size_t transferredBytes)
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



private:
    tcp::resolver resolver_;
     boost::asio::ssl::stream<boost::asio::ip::tcp::socket> socket_;

    boost::asio::streambuf response_buf_;

    Request request_;
    Response response_;
};

int main()
{
    try
    {
        
        boost::asio::ssl::context ctx(boost::asio::ssl::context::sslv23);
        ctx.load_verify_file("settings/server.crt");
        boost::asio::io_context io_context;
        std::string server= "127.0.0.1";
        std::string port= "8089";
        std::string path ="";
        std::optional<boost::asio::ip::tcp::socket> socket3;

        Client c(io_context, server, port, path,&ctx);
        io_context.run();
    }
    catch (std::exception& e)
    {
        std::cout << "Exception: " << e.what() << "\n";
    }

    return 0;
}


