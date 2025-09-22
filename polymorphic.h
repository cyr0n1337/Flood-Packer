#ifndef POLYMORPHIC_H
#define POLYMORPHIC_H

#include <vector>
#include <cstdint>

class PolymorphicStub {
public:
    PolymorphicStub();
    void randomize(std::vector<uint8_t>& code);
};

#endif
