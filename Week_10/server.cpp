#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;

class Server
{
public:
    using endpoint_t = ip::tcp::endpoint;
    using acceptor_t = ip::tcp::acceptor;
    using socket_t   = ip::tcp::socket;

public:
    explicit Server() :
        m_endpoint(ip::address::from_string(server_ip_address),
                   server_port),
        m_acceptor(m_ios, m_endpoint.protocol()),
        m_client_socket(m_ios) 
    {
        m_acceptor.bind(m_endpoint);
        m_acceptor.listen();
    }

    void accept_connection() 
    {
        m_acceptor.accept(m_client_socket);
    }

    const std::string get_message()
    {
        const char message_delimiter = '\n';

        streambuf buffer;
        read_until(m_client_socket, buffer, message_delimiter);

        std::string message;
        std::istream is(&buffer);
        std::getline(is, message);

        return message;
    }

private:
    static inline const std::string server_ip_address ="192.168.0.183";
    static inline const std::size_t server_port       = 2222;

    endpoint_t m_endpoint;
    io_service m_ios;
    acceptor_t m_acceptor;
    socket_t   m_client_socket;
};

int main()
{
    try
    {
        Server server;
        server.accept_connection();
        std::cout << "Connection accepted" << std::endl;

        while (true)
        {
            try
            {
                auto message = server.get_message();
                std::cout << message << std::endl;
            }
            catch (boost::system::system_error& error)
            {
                if (error.code() == error::eof)
                {
                    std::cerr << "Client has disconnected..." << std::endl;
                    return EXIT_SUCCESS;
                }

                std::cerr << "Error getting client message" << error.what() << std::endl;
                return EXIT_FAILURE;
            }
        }
    }
    catch (boost::system::system_error& error)
    {
        std::cerr << "Error creating server: " << error.what() << std::endl;
        return EXIT_FAILURE;
    }
}