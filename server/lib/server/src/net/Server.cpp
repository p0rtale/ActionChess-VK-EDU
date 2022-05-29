#include "Server.hpp"

#include "RoomController.hpp"

Server::Server(std::shared_ptr<boost::asio::io_context> ioContext, std::uint16_t port)
    : m_ioContext(ioContext),
      m_sslContext(std::make_shared<boost::asio::ssl::context>(boost::asio::ssl::context::sslv23)),
      m_acceptor(*m_ioContext, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
      m_roomController(std::make_shared<RoomController>()) {
    setupSSLContext();
}

Server::~Server() {
    shutdown();
}

void Server::run() {
    m_logger.write(LogType::INFO, "Server is accepting connections...");

    m_socket.emplace(*m_ioContext);

    m_acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    m_acceptor.async_accept(*m_socket, [this](const boost::system::error_code& err) {
        if (!err) {
            boost::system::error_code socketErr;
            m_logger.write(LogType::INFO, "Accepted connection on endpoint:", m_socket->remote_endpoint(socketErr));

            const auto session(std::make_shared<Session>(m_ioContext, m_sslContext,
                                                         std::move(*m_socket), m_roomController));
            if (m_roomController->addSession(session)) {
				session->bindConnection();
				session->sslHandshake();
            }
            run();
        }
    });
}

void Server::shutdown() {
    m_logger.write(LogType::INFO, "Shutting down the server...");

    boost::system::error_code err;
    m_acceptor.close(err);
    if (err) {
        m_logger.write(LogType::ERROR, "Acceptor closed with error");
    }
    m_roomController->clear();
}

void Server::setupSSLContext() {
    m_logger.write(LogType::INFO, "Configuring SSL...");

    m_sslContext->set_options(
        boost::asio::ssl::context::default_workarounds
        | boost::asio::ssl::context::no_sslv2
        | boost::asio::ssl::context::single_dh_use);
    m_sslContext->set_password_callback(std::bind(&Server::passwordCallback, this, 
                                                  std::placeholders::_1, std::placeholders::_2));
    m_sslContext->use_certificate_chain_file("settings/server.crt");
    m_sslContext->use_private_key_file("settings/server.key", boost::asio::ssl::context::pem);
    m_sslContext->use_tmp_dh_file("settings/dh2048.pem");

    m_logger.write(LogType::INFO, "SSL configuration completed");
}

std::string Server::passwordCallback(std::size_t maxSize,
                                     boost::asio::ssl::context::password_purpose purpose) const {
    return "passphrase";
}
