//
// Copyright (c) 2018 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/vinniefalco/CppCon2018
//
#include <iostream>
#include <string>
#include "websocket_session.h"
#include "receivedMsg.h"
#include "message.h"


websocket_session::
websocket_session(
    tcp::socket socket,
    std::shared_ptr<shared_state> const& state)
    : ws_(std::move(socket))
    , state_(state)
{
}

websocket_session::
~websocket_session()
{
    // Remove this session from the list of active sessions
    state_->leave(*this);
    //print all sessions after removal
    std::cout<<"**********websocket session destructor begin**********"<<std::endl;
    for (auto it =state_->sessions_.begin(); it!=state_->sessions_.end(); it++){
        if((*it)->useridentified){
            std::cout<<"username: "<<(*it)->username<<std::endl;
        }
        else{
            std::cout<<"user not identified"<<std::endl;
        }
    }
    std::cout<<"**********websocket session destructor end***********"<<std::endl;
}

void
websocket_session::
fail(error_code ec, char const* what)
{
    // Don't report these
    if (ec == net::error::operation_aborted ||
        ec == websocket::error::closed)
        return;

    std::cerr << what << ": " << ec.message() << "\n";
}

void
websocket_session::
on_accept(error_code ec)
{
    // Handle the error, if any

    //*******UNCOMMENT AFTER TESTING******************
    if (ec)
        return fail(ec, "accept");  
    //*******UNCOMMENT AFTER TESTING******************


   std::cout << "in on accept" << std::endl;
    // Add this session to the list of active sessions
    state_->join(*this);
    std::cout<<"**********websocket session on accept begin**********"<<std::endl;
    for (auto it =state_->sessions_.begin(); it!=state_->sessions_.end(); it++){
        if((*it)->useridentified){
            std::cout<<"username: "<<(*it)->username<<std::endl;
        }
        else{
            std::cout<<"user not identified"<<std::endl;
        }
    }
    std::cout<<"**********websocket session on accept end**********"<<std::endl;
    // Read a message
    ws_.async_read(buffer_,
        [sp = shared_from_this()](error_code ec, std::size_t bytes)
        {
            sp->on_read(ec, bytes);
        }
    );



}


void
websocket_session::
on_read(error_code ec, std::size_t)
{
    std::string reply;
    int auth;
    // Handle the error, if any
    if (ec)
        return fail(ec, "read");

    try{
        bool dubplicateSession = false;
        std::cout<<"in on_read, read message "<<queue_.size()<<std::endl;
        Message clientMsg(std::move(&buffer_));
        auth = true;
        auth=state_->mapClients(clientMsg.clientDoc);
        
        if (auth){
            auto session = state_->checkIfDuplicateSession(this,clientMsg.clientDoc, dubplicateSession);
            if (dubplicateSession)
            {
                reply = "{\"action\":\"sessionExpired\",\"msg\":{\"reason\":\"login from another tab or browser\"}}";
                auto const ss = std::make_shared<std::string const>(std::move(reply));
                session->send(ss);                            
            }
            state_->addClientContents(*this,clientMsg.clientDoc);
            clientMsg.firstLogin = state_->FirstClientLogin(this->clientvalue);
            std::cout<<"clientdoc added to queue "<<std::endl;
            state_->addMsgToReceivedMsgQueue(std::move(clientMsg));
        }
        else{
            reply = "{\"action\":\"authenticationError\",\"msg\":{\"reason\":\"auth Failed\"}}";
            auto const ss = std::make_shared<std::string const>(std::move(reply));
            this->send(ss);                            
        }
    }
	catch(const std::runtime_error& e){
        reply = "{\"Action\":\"Authentication Failed\",\"msg\":{\"reason\":\"message format not regonised\"}}";
        auto const ss = std::make_shared<std::string const>(std::move(reply));
        this->send(ss);

	}
	catch(const std::exception& e){
        reply = "{\"Action\":\"Authentication Failed\",\"msg\":{\"reason\":\"message format not regonised\"}}";
        auto const ss = std::make_shared<std::string const>(std::move(reply));
        this->send(ss);

	}


    //    static const char* kTypeNames[] =
    //    { "Null", "False", "True", "Object", "Array", "String", "Number" };

    //    for (rapidjson::Value::ConstMemberIterator itr = jsonDoc.MemberBegin();
    //        itr != jsonDoc.MemberEnd(); ++itr)
    //    {
    //        printf("Type of member %s is %s\n",
    //            itr->name.GetString(), kTypeNames[itr->value.GetType()]);
    //    }
    std::cout<<"beast buffer"<<std::endl;

    //output buffer data
    if (onReadCount_ == 1) {
        std::string bfdata = beast::buffers_to_string(buffer_.data());
    


    //std::string price = jsonDoc["data"]["Action"];




    }
    onReadCount_++;


    
    //This calls the send function in shared_state.cpp which sends the message to all sessions
    //state_->send(beast::buffers_to_string(buffer_.data()));

    
    //auto const rep= 
    //auto const tempm  = std::make_shared<std::string const>(std::move(beast::buffers_to_string(buffer_.data())));
    

    //send(msg);
    // Clear the buffer
    buffer_.consume(buffer_.size());


// Read another message
    std::cout << "run async_read" << std::endl;
    ws_.async_read(
        buffer_,
        [sp = shared_from_this()](
            error_code ec, std::size_t bytes)
    {
        sp->on_read(ec, bytes);
    });
    std::cout << "async_read has returned"<<std::endl;
    
}

void
websocket_session::
send(std::shared_ptr<std::string const> const& ss)
{

    std::cout<<"**********websocket session send begin**********"<<std::endl;
    for (auto it =state_->sessions_.begin(); it!=state_->sessions_.end(); it++){
        if((*it)->useridentified){
            std::cout<<"username: "<<(*it)->username<<std::endl;
        }
        else{
            std::cout<<"user not identified"<<std::endl;
        }
    }
    std::cout<<"**********websocket session send end**********"<<std::endl;

    //std::cout << "in websocket session send" << std::endl;
    // Always add to queue
    queue_.push_back(ss);

    std::cout<<"in send"<<std::endl;
    std::cout<<"queue size "<<queue_.size()<<std::endl;
    // Are we already writing?
    if (queue_.size() > 1)
        return;
    
    //try to print the buffer msg 



    std::cout<<"in send, send msg immediately "<<queue_.size()<<std::endl;
    // We are not currently writing, so send this immediately
    ws_.async_write(
        net::buffer(*queue_.front()),
        [sp = shared_from_this()](
            error_code ec, std::size_t bytes)
    {
        sp->on_write(ec, bytes);
    });
}

void 
websocket_session::
sendFrontMsg(){

    std::cout<<this->queue2_.front()<<std::endl;    
    ws_.async_write(
        net::buffer(*queue_.front()),
        [sp = shared_from_this()](
            error_code ec, std::size_t bytes)
    {
        sp->on_write(ec, bytes);
    });
}

void
websocket_session::
on_write(error_code ec, std::size_t)
{

    std::cout << "in on write" << std::endl;
    //*******UNCOMMENT AFTER TESTING******************
    // Handle the error, if any
    if (ec)
        return fail(ec, "write");
    //*******UNCOMMENT AFTER TESTING******************

    std::cout<<"in on_write, queuesize before erase "<<queue_.size()<<std::endl;
    // Remove the string from the queue
    queue_.erase(queue_.begin());


    std::cout<<"in on_write, queuesize after erase "<<queue_.size()<<std::endl;
    // Send the next message if any
    if (!queue_.empty())
        ws_.async_write(
            net::buffer(*queue_.front()),
            [sp = shared_from_this()](
                error_code ec, std::size_t bytes)
    {
        sp->on_write(ec, bytes);
    });
}


int 
websocket_session::
getToSendQueueSize(){
    std::cout<<this->queue_.size()<<std::endl;
    std::cout<<this->queue2_.size()<<std::endl;
    return this->queue_.size();
}

void 
websocket_session::
addToSendQueue(std::shared_ptr<std::string const> const& ss){
    this->queue_.push_back(ss);
}