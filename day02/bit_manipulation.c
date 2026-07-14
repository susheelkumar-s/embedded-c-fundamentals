#include <stdio.h>
#include <stdint.h>

// 1. Set, clear, toggle, check a bit — one function each, tested in main()
// a. Set a bit n (make it 1)
uint8_t set_bit(uint8_t reg, uint8_t bit_position){
    return reg | (1 << bit_position);
}
// b. clear a bit n (make it 0)
uint8_t clear_bit(uint8_t reg, uint8_t bit_position){
    return reg & ~(1 << bit_position);
}
// c. toggle a bit n(1->0 or 0->1)
uint8_t toggle_bit(uint8_t reg, uint8_t bit_positioin){
    return reg ^ (1 << bit_positioin);
}
//d. check the bit value
uint8_t check_bit(uint8_t reg, uint8_t bit_position){
    return (reg & (1 << bit_position)) ? 1 : 0;
}
//Helper function to print binary representation
void print_binary(uint8_t num){
    if (num > 255 || num < 0) {
        printf("  (too large for 8-bit)");
        return;
    }
    for(int i = 7; i>=0; i--){
        printf("%d",(num>>i)&1);
    }
}

// 2. count the number of set bits in uint8_t
uint8_t count_bits(uint8_t val){
    uint8_t count = 0;
    while(val){
        count += val & 1;
        val >>= 1;
    }
    return count;
}

// 3. Bitwise odd/even check
int is_odd_bitwise(int n) { 
    return n & 1; 
}
int is_even_bitwise(int n) { 
    return !(n & 1);  // NOT of is_odd
}

// 4. // 4. Swap two nibbles of a byte
// 0xAB → 0xBA
uint8_t swap_nibbles(uint8_t val) {
    return ((val & 0x0F) << 4) | ((val & 0xF0) >> 4);
} 
void print_nibbles(uint8_t val) {
    printf("High nibble: %X (%d), Low nibble: %X (%d)", 
           (val >> 4) & 0x0F, (val >> 4) & 0x0F,
           val & 0x0F, val & 0x0F);
}

// 5. Check if a number is a power of 2
// Powers of 2 have exactly one bit set
int is_power_of_two(int n) {
    return (n > 0) && ((n & (n - 1)) == 0);
}

// 6. Extract bits N down to M from a register
// Example: extract bits 5:3 from a value
uint8_t extract_bits(uint8_t reg, int msb, int lsb) {
    uint8_t mask = ((1 << (msb - lsb + 1)) - 1) << lsb;
    return (reg & mask) >> lsb;
}

// 7. A GPIO register control structure using bit fields is in  other file

// 8. Reverse all bits in a uint8_t
uint8_t reverse_bits(uint8_t val) {
    uint8_t result = 0;
    for (int i = 0; i < 8; i++) {
        result = (result << 1) | (val & 1);
        val >>= 1;
    }
    return result;
}


int main(){
    // 1. Set, clear, toggle, check a bit
    printf("1. Set, clear, toggle, check a bit");
    uint8_t REG = 0b00000000;// consider all bits are zero(0)
    uint8_t bit_to_test = 3;
    
    printf("\n==============================\n");
    printf("Using bit position: %d\n\n", bit_to_test);

    // a. SET operation
    printf("a. SET BIT\n");
    printf("   Initial REG: ");
    print_binary(REG);
    printf(" (0x%02X, %d)\n", REG, REG);

    REG = set_bit(REG, bit_to_test);
    printf("   After set:   ");
    print_binary(REG);
    printf(" (0x%02X, %d)\n\n", REG, REG);

    // d.CHECK operation
    printf("d. CHECK BIT\n");
    if (check_bit(REG, bit_to_test)) {
        printf("   Bit %d is SET (1)\n\n", bit_to_test);
    } else {
        printf("   Bit %d is CLEAR (0)\n\n", bit_to_test);
    }
    
    // b. CLEAR operation
    printf("b. CLEAR BIT\n");
    printf("   Before clear: ");
    print_binary(REG);
    printf(" (0x%02X, %d)\n", REG, REG);
    
    REG = clear_bit(REG, bit_to_test);
    printf("   After clear:  ");
    print_binary(REG);
    printf(" (0x%02X, %d)\n\n", REG, REG);

    // d.Check again after clear
    printf("d. CHECK BIT Again\n");
    if (check_bit(REG, bit_to_test)) {
        printf("   Bit %d is SET (1)\n\n", bit_to_test);
    } else {
        printf("   Bit %d is CLEAR (0)\n\n", bit_to_test);
    }

    // c. TOGGLE operation
    printf("c. TOGGLE BIT\n");
    printf("   Before toggle: ");
    print_binary(REG);
    printf(" (0x%02X, %d)\n", REG, REG);
    
    REG = toggle_bit(REG, bit_to_test);
    printf("   After toggle:  ");
    print_binary(REG);
    printf(" (0x%02X, %d)\n", REG, REG);

    // c. Toggle again
    printf("   Toggle again:  ");
    REG = toggle_bit(REG, bit_to_test);
    print_binary(REG);
    printf(" (0x%02X, %d)\n", REG, REG);

    // e. Multiple bits demonstration
    printf("\ne. MULTIPLE BITS DEMONSTRATION\n");
    printf("   Setting bits 0, 2, 4, 6\n");
    REG = 0;
    REG = set_bit(REG, 0);
    REG = set_bit(REG, 2);
    REG = set_bit(REG, 4);
    REG = set_bit(REG, 6);
    printf("   REG = ");
    print_binary(REG);
    printf(" (0x%02X, %d)\n", REG, REG);

    // 2. Count the number of set bits in a uint8_t (without lookup table)
    uint8_t test_values[] = {0, 1, 2, 3, 7, 15, 128, 182, 255};
    int num_tests = sizeof(test_values) / sizeof(test_values[0]);
    printf("\n2. Bit Counting Demonstration\n");
    printf("==========================\n\n"); 
    for (int i = 0; i < num_tests; i++) {
        uint8_t val = test_values[i];
        printf("Value: %3d (0x%02X) = ", val, val);
        print_binary(val); 
        printf(" -> %d bits set\n", count_bits(val));
    }

    // 3. Bitwise odd/even check
    printf(" 3. Even/Odd Detection Using Bitwise AND\n");
    printf("=====================================\n\n");
    printf("Test Cases:\n");
    printf("%-8s %-12s %-8s %-8s\n", 
           "Number", "Binary(8bit)", "n & 1", "Odd?");
    
    for (int n = -5; n <= 10; n++) 
    {
        printf("%-8d ", n);
        print_binary(n);
        printf("   %-8d %-12s\n", is_odd_bitwise(n),is_odd_bitwise(n) ? "Yes" : "No");
    }

    // 4. Swap two nibbles of a byte
    printf("\n4. Swap Two Nibbles of a Byte\n");
    printf("=============================\n\n");\
    // Test various values
    uint8_t test_nibbles[] = {
        0xAB,  // 1010 1011
        0x12,  // 0001 0010
        0x00,  // 0000 0000
        0xFF,  // 1111 1111
        0x0F,  // 0000 1111
        0xF0,  // 1111 0000
        0x37,  // 0011 0111
        0x42,  // 0100 0010
        0xAA,  // 1010 1010 (palindrome)
        0x55   // 0101 0101 (palindrome)
    };
    int num_tests2 = sizeof(test_nibbles) / sizeof(test_nibbles[0]);
    
    printf("%-8s %-12s %-8s %-12s\n", "Input", "Binary", "Output", "Binary");
    printf("%-8s %-12s %-8s %-12s\n", "-----", "------", "------", "------");
    
    for (int i = 0; i < num_tests2; i++) 
    {
        uint8_t original = test_nibbles[i];
        uint8_t swapped = swap_nibbles(original);
        
        printf("0x%02X    ", original);
        print_binary(original);
        printf("  0x%02X    ", swapped);
        print_binary(swapped);
        printf("\n");
    }

    // 5. Check if a number is a power of 2
    printf("\n5. Check if a Number is a Power of 2\n");
    printf("====================================\n\n");
    int test_values5[] = {0, 1, 2, 3, 4, 5, 8, 15, 16, 32, 64, 100, 128, 255};
    int num_tests5 = sizeof(test_values5) / sizeof(test_values5[0]);
    
    printf("Power of 2 Test\n");
    printf("%-6s %-12s %-12s\n", "n", "Binary", "Result");
    printf("%-6s %-12s %-12s\n", "---", "------", "------");
    
    for (int i = 0; i < num_tests5; i++) 
    {
        int n = test_values[i];
        printf("%-6d ", n);
        
        if (n >= 0 && n <= 255) {
            print_binary(n);
            printf("  ");
        } else {
            printf("%-12s ", "---");
        }
        
        printf("%s\n", is_power_of_two(n) ? "Yes" : "No ");
    }

    // 6. Extract bits N down to M from a register
    printf("\n6. Extract Bits N down to M from a Register\n");
    printf("===========================================\n\n");

    uint8_t reg = 0b10110110;  // 0xB6 (182)
    
    printf("Register: ");
    print_binary(reg);
    printf(" (0x%02X)\n\n", reg);
    
    // Extract various bit fields
    printf("Bits 7:0 = ");
    print_binary(extract_bits(reg, 7, 0));
    printf(" (0x%02X) - whole byte\n", extract_bits(reg, 7, 0));
    
    printf("Bits 7:4 = ");
    print_binary(extract_bits(reg, 7, 4));
    printf(" (0x%02X) - high nibble\n", extract_bits(reg, 7, 4));
    
    printf("Bits 3:0 = ");
    print_binary(extract_bits(reg, 3, 0));
    printf(" (0x%02X) - low nibble\n", extract_bits(reg, 3, 0));
    
    printf("Bits 5:3 = ");
    print_binary(extract_bits(reg, 5, 3));
    printf(" (0x%02X)\n", extract_bits(reg, 5, 3));


    // 8. Reverse all bits in a uint8_t
    printf("8-Bit Reversal Test\n");
    printf("%-8s %-12s %-12s %-8s\n", "Value", "Binary", "Reversed", "Binary");
    printf("%-8s %-12s %-12s %-8s\n", "----", "------", "--------", "------");

    uint8_t test_values8[] = {0x00, 0xFF, 0x01, 0x80, 0xAA, 0x55, 0x0F, 0xF0, 0xB2, 0x4D};

    for (int i = 0; i < 10; i++) 
    {
        uint8_t val8 = test_values8[i];
        uint8_t rev = reverse_bits(val8);
        
        printf("0x%02X   ", val8);
        print_binary(val8);
        printf("  0x%02X   ", rev);
        print_binary(rev);
        printf("\n");
    }


    return 0;
}