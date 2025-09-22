#include "crypto.h"
#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <algorithm>
#include <stdexcept>

void MultiLayerEncryptor::add_layer(const EncryptionLayer& l){layers.push_back(l);}
bool MultiLayerEncryptor::encrypt(std::vector<uint8_t>& d){
    for(auto& l:layers){
        switch(l.algorithm){
            case 0: if(!aes_encrypt(d,l)) return 0; break;
            case 1: if(!rc4_encrypt(d,l)) return 0; break;
            case 2: if(!xtea_encrypt(d,l)) return 0; break;
            case 3: if(!custom_encrypt1(d,l)) return 0; break;
            default: return 0;
        }
    }
    return 1;
}
bool MultiLayerEncryptor::decrypt(std::vector<uint8_t>& d){
    for(auto it=layers.rbegin();it!=layers.rend();++it){
        switch(it->algorithm){
            case 0: if(!aes_decrypt(d,*it)) return 0; break;
            case 1: if(!rc4_encrypt(d,*it)) return 0; break;
            case 2: if(!xtea_encrypt(d,*it)) return 0; break;
            case 3: if(!custom_decrypt1(d,*it)) return 0; break;
            default: return 0;
        }
    }
    return 1;
}
bool MultiLayerEncryptor::custom_encrypt1(std::vector<uint8_t>& d,const EncryptionLayer& l){
    if(l.key.empty()) return 0;
    size_t s=std::min<size_t>(l.start_offset,d.size()),e=std::min<size_t>(l.end_offset,d.size());
    if(s>=e) return 0;
    size_t k=0;
    for(size_t i=s;i<e;i++){
        d[i]^=l.key[k];
        d[i]=(d[i]>>3)|(d[i]<<5);
        k=(k+1)%l.key.size();
    }
    return 1;
}
