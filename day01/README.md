# Day 01 - Pointers, Circular Buffer, Struct/Union

## Files
- [x] pointers_basics.c — pointer arithmetic, void pointer, double pointer, memcpy, strlen from scratch
- [x] circular_buffer.c — ring buffer with head/tail indices, wrap-around, overflow guard, 8 edge case tests passing
- [x] struct_union_demo.c — struct padding, sensor struct, union type punning, bit fields, packed struct with portability notes

## Key Concepts
- Pointer arithmetic moves by the size of the type, not by 1 byte
- void pointer must be cast before dereferencing
- Double pointer: pointer that stores the address of another pointer
- count field used for empty/full detection in circular buffer — avoids head==tail ambiguity
- Modulo arithmetic wraps head/tail back to 0 when they reach buffer end
- Old data stays in array after pop — only pointer moves, intentional for performance
- Struct padding wastes memory — reorder members largest to smallest to save RAM
- Union allows multiple types to share same memory — used for float-to-bytes over UART
- Packed struct using both #pragma pack(1) and __attribute__((packed)) for compiler portability

## Real Embedded Use
- Circular buffer: UART receive buffer — ISR writes to head, main reads from tail
- Union float-to-bytes: sending float values over UART/SPI byte by byte
- Packed struct: protocol frames over UART/SPI/I2C with no padding bytes
- Bit field struct: clean register access without manual bit shifting

## Status
- Day 01 complete ✅
