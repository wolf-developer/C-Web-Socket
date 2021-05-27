//
// Copyright (c) 2018 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/vinniefalco/CppCon2018
//

#include "listener.h"
#include "http_session.h"
#include <iostream>

listener::
listener(
    net::io_context& ioc,
    tcp::endpoint endpoint,
    std::shared_ptr<shared_state> const& state,
    boost::asio::ssl::context& context)
    : acceptor_(ioc)
    , sslSocket_(ioc,context)
    , state_(state)
{
    std::cout<<"in listener constructor \n";
    //auto fut=std::async(std::launch::async,&listener::checkReceivedMsgStatus,this);
    //std::async();    
    error_code ec;

    // Open the acceptor
    acceptor_.open(endpoint.protocol(), ec);
    if (ec)
    {
        fail(ec, "open");
        return;
    }

    // Allow address reuse
    acceptor_.set_option(net::socket_base::reuse_address(true));
    if (ec)
    {
        fail(ec, "set_option");
        return;
    }

    // Bind to the server address
    acceptor_.bind(endpoint, ec);
    if (ec)
    {
        fail(ec, "bind");
        return;
    }

    // Start listening for connections
    acceptor_.listen(
        net::socket_base::max_listen_connections, ec);
    if (ec)
    {
        fail(ec, "listen");
        return;
    }
}

void
listener::
run()
{
    std::cout<<"in listener run \n";
    // Start accepting a connection
    acceptor_.async_accept(
        sslSocket_.next_layer(),
        [self = shared_from_this()](error_code ec)
    {
        self->do_handshake(ec);
    });
}

// Report a failure
void
listener::
fail(error_code ec, char const* what)
{
    // Don't report on canceled operations
    if (ec == net::error::operation_aborted)
        return;
    std::cerr << what << ": " << ec.message() << "\n";
}

void
listener::
do_handshake(error_code ec)
{
    std::cout<<"do_handshake\n";
    if(ec)
        return fail(ec, "async_accept");
    else
    sslSocket_.async_handshake(
        boost::asio::ssl::stream_base::server,
        [self = shared_from_this()](error_code ec)
    {
        self->on_accept(ec);
    });
}

// Handle a connection
void
listener::
on_accept(error_code ec)
{
    std::cout<<"in on_accent \n";
    if (ec)
        return fail(ec, "accept");
    else
        std::cout<<"move socket into a new session \n";
        // Launch a new session for this connection
        std::make_shared<http_session>(
            std::move(sslSocket_.next_layer()),
            state_)->run();
    
    std::cout<<"run async accept again \n";
    // Accept another connection
    acceptor_.async_accept(
        sslSocket_.next_layer(),
        [self = shared_from_this()](error_code ec)
    {
        self->do_handshake(ec);
    });
}