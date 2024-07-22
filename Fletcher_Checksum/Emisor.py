def fletcher8(data: str, count: int) -> int:
    sum1 = 0
    sum2 = 0
    
    for index in range(count):
        sum1 = (sum1 + ord(data[index])) % 15
        sum2 = (sum2 + sum1) % 15
    
    return (sum2 << 4) | sum1

def fletcher16(data: str, count: int) -> int:
    sum1 = 0
    sum2 = 0
    
    for index in range(count):
        sum1 = (sum1 + ord(data[index])) % 255
        sum2 = (sum2 + sum1) % 255
    
    return (sum2 << 8) | sum1

def fletcher32(data: str, count: int) -> int:
    sum1 = 0
    sum2 = 0
    
    for index in range(count):
        sum1 = (sum1 + ord(data[index])) % 65535
        sum2 = (sum2 + sum1) % 65535
    
    return (sum2 << 16) | sum1

data = input("Ingrese el mensaje: ")
count = len(data)

checksum8 = fletcher8(data, count)
checksum16 = fletcher16(data, count)
checksum32 = fletcher32(data, count)

print(f"- Fletcher-8: 0x{checksum8:02x} ➡️   {bin(checksum8)[2:].zfill(8)}")
print(f"- Fletcher-16: 0x{checksum16:04x} ➡️   {bin(checksum16)[2:].zfill(16)}")
print(f"- Fletcher-32: 0x{checksum32:08x} ➡️   {bin(checksum32)[2:].zfill(32)}")