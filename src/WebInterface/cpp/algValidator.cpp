#include "algValidator.h"
#include <openssl/evp.h>
#include <exception>
#include <stdexcept>
#include "ssl_compat.h"
#include <memory>

ALGValidator::ALGValidator(const std::string &algorithm, const EVP_MD *md,
                             const std::string &key)
    : md_(md), algorithm_(algorithm), key_size_(EVP_MD_size(md)), key_(key) {}

ALGValidator::~ALGValidator() {}


bool ALGValidator::Sign(const uint8_t *header, size_t num_header,
                         uint8_t *signature, size_t *num_signature) const {
  if (signature == NULL || *num_signature < key_size_) {
    *num_signature = key_size_;
    return false;
  }
  HMacCtx hctx;
  HMAC_CTX *ctx = hctx.get();

  HMAC_Init_ex(ctx, key_.c_str(), key_.size(), md_, NULL);
  bool sign = HMAC_Update(ctx, header, num_header) &&
              HMAC_Final(ctx, signature, (unsigned int *)num_signature);

  return sign;
}

std::string ALGValidator::Digest(const std::string &header) const {
    size_t num_signature = 0;
    Sign(reinterpret_cast<const uint8_t *>(header.c_str()), header.size(), NULL,
         &num_signature);
    std::unique_ptr<uint8_t[]> signature(new uint8_t[num_signature]);
    if (!this->Sign(reinterpret_cast<const uint8_t *>(header.c_str()),
                    header.size(), signature.get(), &num_signature)) {
        throw std::logic_error("unable to sign header");
    }

    return std::string(reinterpret_cast<char *>(signature.get()),
                       num_signature);
}
