#include <iostream>
#include <string>
#include <vector>
#include <cstdint>

using namespace std;

// Función para calcular el checksum de Fletcher para bloques de 8 bits
pair<int, int> calculateFletcherChecksum8(const vector<int>& data) {
    int sum1 = 0;
    int sum2 = 0;
    for (int value : data) {
        sum1 = (sum1 + value) % 255;
        sum2 = (sum2 + sum1) % 255;
    }
    return {sum1, sum2};
}

// Función para calcular el checksum de Fletcher para bloques de 16 bits
pair<int, int> calculateFletcherChecksum16(const vector<int>& data) {
    int sum1 = 0;
    int sum2 = 0;
    for (int value : data) {
        sum1 = (sum1 + value) % 65535;
        sum2 = (sum2 + sum1) % 65535;
    }
    return {sum1, sum2};
}

// Función para calcular el checksum de Fletcher para bloques de 32 bits
pair<int, int> calculateFletcherChecksum32(const vector<int>& data) {
    uint32_t sum1 = 0;
    uint32_t sum2 = 0;
    for (int value : data) {
        sum1 = (sum1 + value) % 4294967295;
        sum2 = (sum2 + sum1) % 4294967295;
    }
    return {sum1, sum2};
}

// Función para verificar el checksum de Fletcher para bloques de 8 bits
bool verifyFletcherChecksum8(const vector<int>& data, int receivedSum1, int receivedSum2) {
    auto [calculatedSum1, calculatedSum2] = calculateFletcherChecksum8(data);
    return (calculatedSum1 == receivedSum1) && (calculatedSum2 == receivedSum2);
}

// Función para verificar el checksum de Fletcher para bloques de 16 bits
bool verifyFletcherChecksum16(const vector<int>& data, int receivedSum1, int receivedSum2) {
    auto [calculatedSum1, calculatedSum2] = calculateFletcherChecksum16(data);
    return (calculatedSum1 == receivedSum1) && (calculatedSum2 == receivedSum2);
}

// Función para verificar el checksum de Fletcher para bloques de 32 bits
bool verifyFletcherChecksum32(const vector<int>& data, int receivedSum1, int receivedSum2) {
    auto [calculatedSum1, calculatedSum2] = calculateFletcherChecksum32(data);
    return (calculatedSum1 == receivedSum1) && (calculatedSum2 == receivedSum2);
}

// Función para agregar padding para bloques de 8, 16, o 32 bits
vector<int> addPadding(const vector<int>& data, int blockSize) {
    vector<int> paddedData = data;
    while (paddedData.size() % blockSize != 0) {
        paddedData.push_back(0);
    }
    return paddedData;
}

// Función para extraer el mensaje original (sin los bits de checksum)
vector<int> extractOriginalMessage(const vector<int>& data) {
    return vector<int>(data.begin(), data.end() - 2);
}

int main() {
    string input;
    cout << "Ingrese el mensaje binario con el checksum generado por el emisor 📥:";
    cin >> input;

    vector<int> data(input.size());
    for (size_t i = 0; i < input.size(); i++) {
        data[i] = input[i] - '0';
    }

    // Elegir el tamaño del bloque (8, 16, o 32)
    int blockSize;
    cout << "Ingrese el tamaño del bloque (8, 16, o 32) 📝: ";
    cin >> blockSize;

    // Agregar padding si es necesario
    vector<int> paddedData = addPadding(data, blockSize);

    // Extraer el checksum recibido
    int receivedSum1 = paddedData[paddedData.size() - 2];
    int receivedSum2 = paddedData[paddedData.size() - 1];
    
    // Verificar el checksum 🕵️‍♂️
    vector<int> originalData(paddedData.begin(), paddedData.end() - 2);
    bool isValid = false;
    if (blockSize == 8) {
        isValid = verifyFletcherChecksum8(originalData, receivedSum1, receivedSum2);
    } else if (blockSize == 16) {
        isValid = verifyFletcherChecksum16(originalData, receivedSum1, receivedSum2);
    } else if (blockSize == 32) {
        isValid = verifyFletcherChecksum32(originalData, receivedSum1, receivedSum2);
    } else {
        cout << "Tamaño de bloque no soportado. ❌" << endl;
        return 1;
    }

    if (isValid) {
        cout << "No se detectaron errores. ✅" << endl;
        vector<int> originalMessage = extractOriginalMessage(paddedData);
        cout << "Mensaje original: ";
        for (int bit : originalMessage) {
            cout << bit;
        }
        cout << endl;
    } else {
        cout << "Se detectaron errores en el mensaje. Se descarta el mensaje ❌" << endl;
    }

    return 0;
}
