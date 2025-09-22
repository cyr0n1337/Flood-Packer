#ifndef PACKER_H
#define PACKER_H

#include <vector>
#include <cstdint>

class AdvancedPacker {
public:
    bool pack();
private:
    std::vector<uint8_t> original_data;
    std::vector<uint8_t> stub_data;
    std::vector<uint8_t> encryption_key;
    std::vector<uint8_t> rsa_public_key;

    bool load_input_file();
    void inject_anti_analysis();
    void virtualize_critical_functions();
    bool apply_encryption_layers();
    void generate_polymorphic_stub();
    void add_integrity_checks();
    bool write_output_file();
    void apply_signature_obfuscation();
};

#endif
