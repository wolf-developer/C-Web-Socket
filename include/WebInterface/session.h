
#include <boost/beast/core.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <boost/asio/strand.hpp>
#include <boost/asio/dispatch.hpp>



class session : public std::enable_shared_from_this<session>
{
    boost::beast::websocket::stream<
        boost::beast::ssl_stream<boost::beast::tcp_stream>> ws_;
    boost::beast::flat_buffer buffer_;

public:
    // Take ownership of the socket
    session(boost::asio::ip::tcp::socket&& socket, boost::asio::ssl::context& ctx);


    // Get on the correct executor
    void run();

    // Start the asynchronous operation
    void on_run();


    void on_handshake(boost::beast::error_code ec);


    void on_accept(boost::beast::error_code ec);


    void do_read();


    void on_read(
        boost::beast::error_code ec,
        std::size_t bytes_transferred);


    void on_write(
        boost::beast::error_code ec,
        std::size_t bytes_transferred);
};