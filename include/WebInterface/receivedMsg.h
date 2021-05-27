#ifndef RECEIVEDMSG_H
#define RECEIVEDMSG_H

#include <string>
//#include <bsoncxx/builder/basic/array.hpp>
//include <bsoncxx/builder/basic/document.hpp>
//#include <bsoncxx/builder/basic/kvp.hpp>
//#include <bsoncxx/types.hpp>
//#include <bsoncxx/json.hpp>

class receivedMsg{

public:
    receivedMsg(std::string action_,std::string client_):action{action},
                                                        client{client_}{}

    std::string action;
    std::string client;
    //bsoncxx::document::value clientDoc;

};

#endif