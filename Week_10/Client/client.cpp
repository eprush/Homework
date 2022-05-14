#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;

class Client 
{
public:
    using socket_t = ip::tcp::socket;

    explicit Client(std::string& nickname) :
        m_nickname(std::move(nickname)),
        m_endpoint( ip::address::from_string(server_ip_address),
                   server_port),
        m_socket(m_ios, m_endpoint.protocol())
    {
        m_socket.connect(m_endpoint);
    }

public:
    void run()
    {
        while (true)
        {
            std::cout << ">> ";
            std::string message;
            std::getline(std::cin, message);

            if (message == exit_word)
                break;

            send_message(message + '\n');
            std::cout << "<< message sent" << std::endl;
        }
    }

private:
    void send_message(const std::string& message_text)
    {
        auto message = m_nickname + ": " + message_text;
        write(m_socket, buffer(message));
    }

    void shutdown()
    {
        m_socket.shutdown(socket_base::shutdown_both);
        m_socket.close();
    }

private:
    static inline const std::string server_ip_address ="192.168.0.183";
    static inline const std::size_t server_port       = 2222;

    static inline const std::string exit_word = "/exit";

    std::string       m_nickname;
    ip::tcp::endpoint m_endpoint;
    io_service        m_ios;
    socket_t          m_socket;
};

int main()
{
    std::cout << "Enter your nickname: ";
    std::string nickname;
    std::getline(std::cin, nickname);

    try 
    {
        Client client(nickname);

        client.run();
    }
    catch (boost::system::system_error& error) 
    {
        std::cerr << "Error trying to create client" << error.what() << std::endl;
        return error.code().value();
    }
    catch (...)
    {
        std::cerr << "Undefined error" << std::endl;
    }
}