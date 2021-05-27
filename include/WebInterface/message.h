#ifndef MESSAGE_H
#define MESSAGE_H
#include <iostream>
#include <boost/beast.hpp>
#include <string>

struct Message {

    char* clientDoc = NULL;
    size_t size;
    bool firstLogin=false;
    
    Message();
    Message (boost::beast::flat_buffer* buffer_);
    Message (Message && obj_);
    Message & operator = (Message && obj_);
    ~Message();
};



#endif