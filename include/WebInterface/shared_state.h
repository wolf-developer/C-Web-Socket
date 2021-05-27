//
// Copyright (c) 2018 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/vinniefalco/CppCon2018
//

#ifndef CPPCON2018_SHARED_STATE_HPP
#define CPPCON2018_SHARED_STATE_HPP

#include <mutex>
#include <condition_variable>
#include <memory>
#include <string>
#include <unordered_set>
#include <map>
#include <queue>
#include <message.h>

//#include "receivedMsg.h"
// Forward declaration
class websocket_session;

// Represents the shared server state
class shared_state
{
    std::string doc_root_;
    std::queue<Message> receivedMsgQueue_;
    std::string raaz="XcRodEs!£dlpWLKjdO9873";
    int64_t expiry=86400000;
    std::unordered_set<websocket_session*>:: iterator it;
    // This simple method of tracking
    // sessions only works with an implicit
    // strand (i.e. a single-threaded server)
    //std::map<std::string,websocket_session*> sessionLookup_;
    //std::map<std::string,websocket_session*>::iterator clientSession;
//*********** Session Managment Code Started **************//
    std::map<std::string,int> ClientCounter;
    std::map<std::string,int>:: iterator ClientIt;
    
//*********** Session Managment Code Ended **************//
public:
    std::condition_variable newMsgReceivedCond;
    std::mutex newMsgMut;
    std::unordered_set<websocket_session*> sessions_;
    explicit
        shared_state(std::string doc_root);

    std::string const&
        doc_root() const noexcept
    {
        return doc_root_;
    }
    bool lastSessionFlag = false;
    void addClientContents(websocket_session& session,const char* clientDoc);
    websocket_session* checkIfDuplicateSession(websocket_session* session,const char* clientDoc, bool& duplicateSession);
    void addMsgToReceivedMsgQueue(Message clientDoc_);
    Message leftSession(websocket_session& session);
    Message getMsgFromReceivedMsgQueue();
    int getReceivedMsgQueueSize();
    int getToSendMsgQueueSize(std::string client);
    void initiateSend();
    void join(websocket_session& session);
    void leave(websocket_session& session);
    void send(std::string message);
    int mapClients(const char* clientDoc);
    bool FirstClientLogin(std::string clientvalue);
 //  void sendError(std::string);
    //void sendToClient(std::string client,bsoncxx::builder::basic::document doc);
    void sendToClient(std::string client,std::string message);
    void sendToClient(std::string client,std::shared_ptr<std::string const> const& ss);
    void authResponse();//std::string client,bsoncxx::builder::basic::document doc);
    void addToSendQueue(std::string client, std::string message);
    void sendMessageFromQueue(std::string client);
    void sendMessageFromAllQueues();
    //Comment Out After Testing
    void loadMonetDB(Message clientMsg);
    void lockReceivedMsgMutex();
};

#endif
