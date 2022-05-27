#include "Connection.hpp"

#include "RequestQueue.hpp"
#include "Session.hpp"

Connection::Connection(boost::asio::io_context* ioContext, 
                       boost::asio::ssl::context* sslContext,
                       boost::asio::ip::tcp::socket&& socket,
                       std::uint64_t id,
                       std::shared_ptr<RequestQueue> requestQueue)
                       : m_socket(std::move(socket), *sslContext),
                         m_id(id),
                         m_strand(*ioContext), 
                         m_requestQueue(requestQueue) {
    m_logger.emplace(std::string("connection_" + std::to_string(m_id) + "_log.txt").data());
}

Connection::~Connection() {
    if (m_state != State::CLOSED) {
        close();
    }
}

void Connection::addSession(std::weak_ptr<Session> session) {
    m_bindedSession = session;
}

void Connection::sslHandshake() {
    m_socket.async_handshake(boost::asio::ssl::stream_base::server, 
                             [connection = shared_from_this()](const boost::system::error_code& error) {
        boost::system::error_code socketErr;
        if (!error) {
            connection->m_logger->write(LogType::INFO, "SSL handshake with", 
                                        connection->m_socket.lowest_layer().remote_endpoint(socketErr), "completed");

            auto session = connection->m_bindedSession.lock();
            if (session) {
                session->acknowledge();
            }
            connection->read();
        } else {
            connection->m_logger->write(LogType::ERROR, "SSL handshake with",
                                        connection->m_socket.lowest_layer().remote_endpoint(socketErr), "failed");
            connection->close();
        }
    });
}

void Connection::read() {
    boost::asio::async_read_until(
        m_socket,
        m_readBuf,
        kMessageSeparator,
        boost::asio::bind_executor(
            m_strand, 
            std::bind(&Connection::readHandler, 
                shared_from_this(), 
                std::placeholders::_1, 
                std::placeholders::_2
            )
        )
    );    
}

void Connection::write(std::string&& message) {
    boost::asio::post(m_strand, [message = std::move(message), connection = shared_from_this()]() mutable {
        connection->m_writeBuf.push(std::move(message));
        if (connection->m_state != State::WRITING) {
            connection->write();
        }
    });
}

void Connection::write() {
    std::vector<boost::asio::const_buffer> bufferSequence = m_writeBuf.popAll();
    m_state = State::WRITING;
    boost::asio::async_write(
        m_socket,
        bufferSequence,
        boost::asio::bind_executor(
            m_strand,
            std::bind(&Connection::writeHandler, 
                shared_from_this(), 
                std::placeholders::_1, 
                std::placeholders::_2
            )
        )
    );
}

void Connection::readHandler(const boost::system::error_code& error, std::size_t transferredBytes) {
    if (!error) {
        const auto data = m_readBuf.data();
        std::string str(boost::asio::buffers_begin(data), 
                        boost::asio::buffers_begin(data) + transferredBytes - kMessageSeparator.size());
        m_readBuf.consume(transferredBytes);

        boost::system::error_code socketErr;
        m_logger->write(LogType::INFO, "Recieved", transferredBytes, "bytes:", str);

        Request request;
        request.parseJSON(str);

        m_requestQueue->push(std::move(request));
        publishRequest();
        read();
    } else { 
        m_logger->write(LogType::ERROR, "(reading from a socket)", error.message());
        close();
    }
}

void Connection::writeHandler(const boost::system::error_code& error, std::size_t transferredBytes) {
    if (!error) {
        m_logger->write(LogType::INFO, "Sent", transferredBytes, "bytes");
        if (m_writeBuf.size()) {
            write();
        } else {
            m_state = State::DEFAULT;
        }
    } else {
        m_logger->write(LogType::ERROR, "(writing to a socket)", error.message());
        close();
    }
}

void Connection::close() {
    boost::asio::post(m_strand, [connection = shared_from_this()]() {
        if (connection->m_state != State::CLOSED) {
            connection->m_logger->write(LogType::INFO, "Closing the connection...");

            boost::system::error_code error;

            connection->m_socket.lowest_layer().shutdown(boost::asio::ip::tcp::socket::shutdown_both, error);
            if (error) {
                connection->m_logger->write(LogType::ERROR, "(socket shutdown)", error.message());
            }

            connection->m_socket.lowest_layer().close(error);
            if (error) {
                connection->m_logger->write(LogType::ERROR, "(closing the socket)", error.message());
            } 

            auto session = connection->m_bindedSession.lock();
            if (session) {
                session->removeFromRoomController();
            }
            connection->m_state = State::CLOSED;
            connection->m_bindedSession.reset();

            connection->m_logger->write(LogType::INFO, "Connection closed");
        }
    });
}

void Connection::publishRequest() {
    auto session = m_bindedSession.lock();
    if (session) {
        session->handleRequests();
    }
}
