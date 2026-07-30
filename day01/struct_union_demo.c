#include <stdio.h>
#include <stdint.h>
#include <string.h>

// PROGRAM 1: Struct basics + size and padding

typedef struct 
{
    char a;     // 1 byte + 3 padding
    int  b;     // 4 bytes
    char c;     // 1 byte + 3 padding
} BadStruct;    // total: 12 bytes

typedef struct 
{
    int  b;     // 4 bytes
    char a;     // 1 byte
    char c;     // 1 byte + 2 padding
} GoodStruct;   // total: 8 bytes

void demo_padding(void) 
{
    printf("=== Struct Padding ===\n");
    printf("BadStruct size:  %zu bytes\n", sizeof(BadStruct));
    printf("GoodStruct size: %zu bytes\n", sizeof(GoodStruct));
    // Key lesson: reorder members largest to smallest to save memory
}

// PROGRAM 2: Struct as sensor data container

typedef struct 
{
    uint8_t  sensor_id;
    float    temperature;
    float    humidity;
    uint32_t timestamp_ms;
    uint8_t  valid;
} SensorData;

void print_sensor(SensorData *s) 
{
    if (!s->valid) 
    {
        printf("Sensor %d: invalid data\n", s->sensor_id);
        return;
    }
    printf("Sensor %d: Temp=%.1fC  Hum=%.1f%%  Time=%lums\n", s->sensor_id, s->temperature, s->humidity, s->timestamp_ms);
}

void demo_sensor_struct(void) 
{
    printf("\n=== Sensor Struct ===\n");
    SensorData reading = {1, 36.5f, 72.3f, 5000, 1};
    print_sensor(&reading);

    SensorData bad = {2, 0, 0, 0, 0};
    print_sensor(&bad);
}

// PROGRAM 3: Union for type punning — float to bytes over UART

typedef union 
{
    float    f;
    uint8_t  bytes[4];
    uint32_t raw;
} FloatBytes;

void demo_union_float(void) 
{
    printf("\n=== Union: Float to Bytes ===\n");
    FloatBytes fb;
    fb.f = 3.14f;

    printf("Float value: %f\n", fb.f);
    printf("Raw bytes:   ");
    for (int i = 0; i < 4; i++) 
    {
        printf("0x%02X ", fb.bytes[i]);
    }
    printf("\tIEEE 754 Format");
    printf("\n");
    printf("Raw uint32:  0x%08X\n", fb.raw);
    // This is how you send a float over UART byte by byte
    // Receiver reconstructs using the same union
}

// PROGRAM 4: Union for register bit manipulation

typedef union 
{
    uint8_t raw;
    struct 
    {
        uint8_t tx_ready  : 1;   // bit 0
        uint8_t rx_ready  : 1;   // bit 1
        uint8_t error     : 1;   // bit 2
        uint8_t overflow  : 1;   // bit 3
        uint8_t reserved  : 4;   // bits 7:4
    } bits;
} StatusRegister;

void demo_status_register(void) 
{
    printf("\n=== Union: Status Register ===\n");
    StatusRegister sr;
    sr.raw = 0x00;

    sr.bits.tx_ready = 1;
    sr.bits.rx_ready = 1;
    printf("Status raw: 0x%02X\n", sr.raw);     // should be 0x03
    printf("TX ready: %d\n", sr.bits.tx_ready);
    printf("RX ready: %d\n", sr.bits.rx_ready);
    printf("Error:    %d\n", sr.bits.error);

    // Simulate an error
    sr.bits.error = 1;
    printf("After error - raw: 0x%02X\n", sr.raw);  // should be 0x07
}

// PROGRAM 5: Packed struct — for protocol frames

#pragma pack(1) 
typedef struct 
{
    uint8_t  start_byte;    // 0xAA
    uint8_t  device_id;
    uint16_t data_length;
    uint32_t payload;
    uint8_t  checksum;
} __attribute__((packed)) ProtocolFrame;
#pragma pack()
// NOTE: Both #pragma pack(1) and __attribute__((packed)) are used here
// intentionally for maximum compiler compatibility.
// 90% portable for compilers used in embedded development
// #pragma pack(1)          — works on MSVC, GCC, Clang (Windows/Linux/Mac)
// __attribute__((packed))  — works on GCC and Clang only (not MSVC)
void demo_packed_struct(void) 
{
    printf("\n=== Packed Struct (Protocol Frame) ===\n");
    printf("ProtocolFrame size: %zu bytes\n", sizeof(ProtocolFrame));
    // Without packed: would be padded to 12 bytes
    // With packed: exactly 9 bytes — critical for serial protocols

    ProtocolFrame frame = {0xAA, 0x01, 4, 0xDEADBEEF, 0xFF};
    printf("Start:    0x%02X\n", frame.start_byte);
    printf("Device:   %d\n",     frame.device_id);
    printf("Length:   %d\n",     frame.data_length);
    printf("Payload:  0x%08X\n", frame.payload);
    printf("Checksum: 0x%02X\n", frame.checksum);
}

int main(void) 
{
    demo_padding();
    demo_sensor_struct();
    demo_union_float();
    demo_status_register();
    demo_packed_struct();
    return 0;
}