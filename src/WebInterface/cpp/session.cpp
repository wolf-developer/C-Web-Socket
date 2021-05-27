#include "session.h"

#include <iostream>

    void
    fail(boost::beast::error_code ec, char const* what)
    {
        std::cerr << what << ": " << ec.message() << "\n";
    }

    // Take ownership of the socket
    session::session(boost::asio::ip::tcp::socket&& socket, boost::asio::ssl::context& ctx)
        : ws_(std::move(socket), ctx)
    {
    }

    // Get on the correct executor
    void
    session::run()
    {
        // We need to be executing within a strand to perform async operations
        // on the I/O objects in this session. Although not strictly necessary
        // for single-threaded contexts, this example code is written to be
        // thread-safe by default.
        boost::asio::dispatch(ws_.get_executor(),
            boost::beast::bind_front_handler(
                &session::on_run,
                shared_from_this()));
    }

    // Start the asynchronous operation
    void
    session::on_run()
    {
        // Set the timeout.
        boost::beast::get_lowest_layer(ws_).expires_after(std::chrono::seconds(30));

         // Perform the SSL handshake
        ws_.next_layer().async_handshake(
            boost::asio::ssl::stream_base::server,
            boost::beast::bind_front_handler(
                &session::on_handshake,
                shared_from_this()));
    }

    void
    session::on_handshake(boost::beast::error_code ec)
    {
        if(ec)
            return fail(ec, "handshake");

        // Turn off the timeout on the tcp_stream, because
        // the websocket stream has its own timeout system.
        boost::beast::get_lowest_layer(ws_).expires_never();

        // Set suggested timeout settings for the websocket
        ws_.set_option(
            boost::beast::websocket::stream_base::timeout::suggested(
                boost::beast::role_type::server));

        // Set a decorator to change the Server of the handshake
        ws_.set_option(boost::beast::websocket::stream_base::decorator(
            [](boost::beast::websocket::response_type& res)
            {
                res.set(boost::beast::http::field::server,
                    std::string(BOOST_BEAST_VERSION_STRING) +
                        " websocket-server-async-ssl");
            }));

        // Accept the websocket handshake
        ws_.async_accept(
            boost::beast::bind_front_handler(
                &session::on_accept,
                shared_from_this()));
    }

    void
    session::on_accept(boost::beast::error_code ec)
    {
        if(ec)
            return fail(ec, "accept");

        // Read a message
        do_read();
    }

    void
    session::do_read()
    {
        // Read a message into our buffer
        ws_.async_read(
            buffer_,
            boost::beast::bind_front_handler(
                &session::on_read,
                shared_from_this()));
    }

    void
    session::on_read(
        boost::beast::error_code ec,
        std::size_t bytes_transferred)
    {
        boost::ignore_unused(bytes_transferred);

        // This indicates that the session was closed
        if(ec == boost::beast::websocket::error::closed)
            return;

        if(ec)
            fail(ec, "read");

        // Echo the message
        ws_.text(ws_.got_text());
        ws_.async_write(
            buffer_.data(),
            boost::beast::bind_front_handler(
                &session::on_write,
                shared_from_this()));
    }

    void
    session::on_write(
        boost::beast::error_code ec,
        std::size_t bytes_transferred)
    {
        boost::ignore_unused(bytes_transferred);

        if(ec)
            return fail(ec, "write");

        // Clear the buffer
        buffer_.consume(buffer_.size());

        // Do another read
        do_read();
    }
