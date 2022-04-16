#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <iostream>
#include <memory>
#include <exception>

#include "Server.hpp"

int main() {
	std::shared_ptr<boost::asio::io_context> io { 
		std::make_shared<boost::asio::io_context>() 
	};

	Server server { io, 8080 };
	server.run();

	try {
		io->run();
	} catch (const std::exception& e) {
		std::cerr << "ERROR: " << e.what() << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
