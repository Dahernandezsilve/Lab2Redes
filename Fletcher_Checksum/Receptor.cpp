#include <iostream>
#include <string>
#include <bitset>
#include <cstdint>

uint16_t fletcher8(const std::string &data) {
    uint16_t sum1 = 0;
    uint16_t sum2 = 0;
    
    for (char char_digit : data) {
        sum1 = (sum1 + (char_digit - '0')) % 255;
        sum2 = (sum2 + sum1) % 255;
    }
    
    return (sum2 << 8) | sum1;
}

uint32_t fletcher16(const std::string &data) {
    uint32_t sum1 = 0;
    uint32_t sum2 = 0;
    
    for (char char_digit : data) {
        sum1 = (sum1 + (char_digit - '0')) % 65535;
        sum2 = (sum2 + sum1) % 65535;
    }
    
    return (sum2 << 16) | sum1;
}

uint64_t fletcher32(const std::string &data) {
    uint64_t sum1 = 0;
    uint64_t sum2 = 0;
    
    for (char char_digit : data) {
        sum1 = (sum1 + (char_digit - '0')) % 4294967295;
        sum2 = (sum2 + sum1) % 4294967295;
    }
    
    return (sum2 << 32) | sum1;
}

std::string extract_original_message(const std::string &data, int checksum_bits) {
    return data.substr(0, data.size() - checksum_bits);
}

uint64_t extract_checksum(const std::string &data, int checksum_bits) {
    std::string checksum_bin = data.substr(data.size() - checksum_bits);
    return std::bitset<64>(checksum_bin).to_ullong();
}

bool verify_checksum(const std::string &data, uint64_t received_checksum, int block_size) {
    uint64_t calculated_checksum;
    if (block_size == 8) {
        calculated_checksum = fletcher8(data);
    } else if (block_size == 16) {
        calculated_checksum = fletcher16(data);
    } else if (block_size == 32) {
        calculated_checksum = fletcher32(data);
    } else {
        throw std::invalid_argument("Unsupported block size");
    }
    
    return calculated_checksum == received_checksum;
}

int main() {
    std::cout << "\n--- Receptor ---" << std::endl;
    std::string received_message;
    std::cout << "Ingrese el mensaje binario con el checksum: ";
    std::cin >> received_message;
    int block_size;
    std::cout << "Ingrese el tamaño del bloque (8, 16, o 32): ";
    std::cin >> block_size;
    
    int checksum_bits = block_size == 8 ? 16 : block_size == 16 ? 32 : 64;
    std::string original_message = extract_original_message(received_message, checksum_bits);
    uint64_t received_checksum = extract_checksum(received_message, checksum_bits);
    
    bool is_valid = verify_checksum(original_message, received_checksum, block_size);
    
    if (is_valid) {
        std::cout << "No se detectaron errores. ✅" << std::endl;
        std::cout << "Mensaje original: " << original_message << std::endl;
    } else {
        std::cout << "Se detectaron errores en el mensaje. Se descarta el mensaje ❌" << std::endl;
    }
    
    return 0;
}
