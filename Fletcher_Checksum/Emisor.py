def fletcher8(data: str) -> int:
    sum1 = 0
    sum2 = 0
    
    for char in data:
        if char not in '01':
            raise ValueError("Data must be a binary string with '0' and '1' characters only.")
        sum1 = (sum1 + int(char)) % 255
        sum2 = (sum2 + sum1) % 255
    
    return (sum2 << 8) | sum1

def fletcher16(data: str) -> int:
    sum1 = 0
    sum2 = 0
    
    for char in data:
        if char not in '01':
            raise ValueError("Data must be a binary string with '0' and '1' characters only.")
        sum1 = (sum1 + int(char)) % 65535
        sum2 = (sum2 + sum1) % 65535
    
    return (sum2 << 16) | sum1

def fletcher32(data: str) -> int:
    sum1 = 0
    sum2 = 0
    
    for char in data:
        if char not in '01':
            raise ValueError("Data must be a binary string with '0' and '1' characters only.")
        sum1 = (sum1 + int(char)) % 4294967295
        sum2 = (sum2 + sum1) % 4294967295
    
    return (sum2 << 32) | sum1

def padMessage(data: str, blockSize: int) -> str:
    paddingLength = (blockSize - (len(data) % blockSize)) % blockSize
    if paddingLength != 0:
        data += '0' * paddingLength
    return data, paddingLength

def addChecksumToMessage(data: str, blockSize: int) -> str:
    paddedData, paddingLength = padMessage(data, blockSize)
    
    if blockSize == 8:
        checksum = fletcher8(paddedData)
        checksumBits = 16  # 8 bits para cada suma
    elif blockSize == 16:
        checksum = fletcher16(paddedData)
        checksumBits = 32
    elif blockSize == 32:
        checksum = fletcher32(paddedData)
        checksumBits = 64
    else:
        raise ValueError("Unsupported block size")

    checksumHex = f"{checksum:0{checksumBits//4}X}"
    checksumBin = f"{int(checksumHex, 16):0{checksumBits}b}"
    messageWithChecksum = paddedData + checksumBin
    return messageWithChecksum, checksumBin, paddingLength

def main():
    print("📡 --- Emisor ---")
    message = input("🔠 Ingrese el mensaje binario: ")
    blockSize = int(input("📏 Ingrese el tamaño del bloque (8, 16, o 32): "))
    
    messageWithChecksum, checksumBin, paddingLength = addChecksumToMessage(message, blockSize)
    print(f"📜 Mensaje con checksum: {messageWithChecksum}")
    print(f"🔍 Checksum en binario: {checksumBin}")

if __name__ == "__main__":
    main()
