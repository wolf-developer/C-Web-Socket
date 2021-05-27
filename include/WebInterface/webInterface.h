#ifndef WEBINTERFACE_H
#define WEBINTERFACE_H

#include <string>
#include "net.h"
#include <boost/asio/signal_set.hpp>
#include "shared_state.h"

class WebInterface{

public:
    int portNum;
    char* doc_root;
    net::ip::address address;
                     
    unsigned short port;

    WebInterface();
    void run();
    std::shared_ptr<shared_state> shst;
};



#endif