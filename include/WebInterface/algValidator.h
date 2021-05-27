#ifndef OSSLVALIDATOR_H
#define OSSLVALIDATOR_H

#include <openssl/hmac.h>
#include <string>

class ALGValidator {

public:
  explicit ALGValidator(const std::string &algorithm, const EVP_MD *md,
                         const std::string &key);
  virtual ~ALGValidator();
  bool Sign(const uint8_t *header, size_t num_header, uint8_t *signature,
            size_t *num_signature) const;
  std::string Digest(const std::string &header) const;
  std::string algorithm_;
private:
  const EVP_MD *md_;
  
  unsigned int key_size_;
  std::string key_;

};

#endif

