#include <exception>
#include <iostream>
#include <memory>

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include "Server.hpp"

int main() {
    std::shared_ptr<boost::asio::io_context> ioContext(std::make_shared<boost::asio::io_context>());

    Server server(ioContext, 8080);
    server.run();

    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i) {
        threads.emplace_back([ioContext]() {
            for (;;) {
                try {
                    ioContext->run();
                    break;
                } catch (const std::exception& e) {
                    std::cerr << "ERROR: " << e.what() << '\n';
                }
            }
        });
    }

    for (auto& thread: threads) {
        thread.join();
    }

    return EXIT_SUCCESS;
}
