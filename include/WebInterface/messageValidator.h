#ifndef MESSAGEVALIDATOR_H
#define MESSAGEVALIDATOR_H

#include "json.hpp"

class MessageValidator {
   public:
    virtual ~MessageValidator() {}


    virtual std::string toJson() const = 0;

};


class MessageSigner : public MessageValidator {
   public:
    virtual ~MessageSigner() {}
    virtual bool Sign(const uint8_t *header, size_t num_header,
                      uint8_t *signature, size_t *num_signature) const = 0;

};

#endif