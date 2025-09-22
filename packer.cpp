#include "packer.h"
#include "crypto.h"
#include "polymorphic.h"
#include "anti_debug.h"
#include "integrity.h"
#include "vm.h"
#include <fstream>
#include <iostream>
#include <openssl/rand.h>
bool AdvancedPacker::pack(){if(!load_input_file())return false;inject_anti_analysis();virtualize_critical_functions();if(!apply_encryption_layers())return false;generate_polymorphic_stub();add_integrity_checks();if(!write_output_file())return false;apply_signature_obfuscation();return true;}
bool AdvancedPacker::apply_encryption_layers(){MultiLayerEncryptor e;e.generate_random_layers(original_data.size(),3+(rand()%3));if(!e.encrypt(original_data))return false;std::vector<uint8_t> rsa_encrypted_key=rsa_encrypt(encryption_key,rsa_public_key);original_data.insert(original_data.end(),rsa_encrypted_key.begin(),rsa_encrypted_key.end());return true;}
void AdvancedPacker::add_integrity_checks(){IntegrityChecker c;c.add_region(stub_data.data(),stub_data.size(),true,IntegrityChecker::murmur3_checksum);c.add_region(original_data.data(),original_data.size(),false,IntegrityChecker::crc32_checksum);c.start_monitoring(500);}
