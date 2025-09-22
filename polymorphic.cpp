#include "polymorphic.h"
#include <cstdlib>

PolymorphicStub::PolymorphicStub() {}

void PolymorphicStub::randomize(std::vector<uint8_t>& code){
    for(size_t i=0;i<code.size();i++){
        code[i]^=(rand()%256);
        if(rand()%2) code[i]=(code[i]>>3)|(code[i]<<5);
    }
}
