#ifndef CRYPTO_H
#define CRYPTO_H

#include <vector>
#include <cstdint>

struct EncryptionLayer {
    uint8_t layer_id;
    uint8_t algorithm;
    std::vector<uint8_t> key;
    std::vector<uint8_t> iv;
    uint32_t start_offset;
    uint32_t end_offset;
};

class MultiLayerEncryptor {
public:
    MultiLayerEncryptor();
    void add_layer(const EncryptionLayer& layer);
    bool encrypt(std::vector<uint8_t>& data);
    bool decrypt(std::vector<uint8_t>& data);
    void generate_random_layers(size_t data_size, int num_layers=3);
private:
    std::vector<EncryptionLayer> layers;
    bool aes_encrypt(std::vector<uint8_t>& data, const EncryptionLayer& layer);
    bool aes_decrypt(std::vector<uint8_t>& data, const EncryptionLayer& layer);
    bool rc4_encrypt(std::vector<uint8_t>& data, const EncryptionLayer& layer);
    bool xtea_encrypt(std::vector<uint8_t>& data, const EncryptionLayer& layer);
    bool custom_encrypt1(std::vector<uint8_t>& data, const EncryptionLayer& layer);
    bool custom_decrypt1(std::vector<uint8_t>& data, const EncryptionLayer& layer);
};

std::vector<uint8_t> rsa_encrypt(const std::vector<uint8_t>& data,const std::vector<uint8_t>& public_key);
std::vector<uint8_t> rsa_decrypt(const std::vector<uint8_t>& data,const std::vector<uint8_t>& private_key);
std::vector<uint8_t> derive_key(const std::vector<uint8_t>& password,const std::vector<uint8_t>& salt);

#endif
