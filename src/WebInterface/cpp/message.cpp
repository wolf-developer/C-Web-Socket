#include "message.h"
#include <iostream>



Message::
Message ():firstLogin{false}{std::cout<<"In Message::Message";}


Message::
Message (boost::beast::flat_buffer* buffer_){
    this->size = buffer_->size();
    this->clientDoc = new char [buffer_->size()];
    for(auto const buffer : boost::beast::buffers_range_ref(buffer_->data()))
        {
            auto in = (static_cast<const char*>(buffer.data()));
            for(auto i = 0 ; i<buffer_->size();i++)
                this->clientDoc[i] = (in[i]);            
        }
    std::cout<<clientDoc<<std::endl;
}

Message::
Message(Message && obj_){
    std::cout<<"In Copy Constructor"<<std::endl;
    this->clientDoc = obj_.clientDoc;
    this->firstLogin = obj_.firstLogin;
    this->size = obj_.size;
    obj_.clientDoc = nullptr;


}

Message &
Message::
operator = (Message && obj_ ){
    this->clientDoc = obj_.clientDoc;
    this->firstLogin = obj_.firstLogin;
    this->size = obj_.size;
    obj_.clientDoc = nullptr;
    return *this;
}

Message::
~Message(){
    std::cout<<"In Message::~Message"<<std::endl;
    delete [] this->clientDoc;
}

