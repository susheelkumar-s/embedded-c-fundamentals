#include <stdio.h>
#include <stdint.h>
// 7. A GPIO register control structure using bit fields
// GPIO Register Control Structure
typedef struct {
    uint32_t MODE     : 2;   // bits 1:0  - GPIO Mode
    uint32_t SPEED    : 2;   // bits 3:2  - Output Speed
    uint32_t PUPD     : 2;   // bits 5:4  - Pull-up/Pull-down
    uint32_t RESERVED : 26;  // bits 31:6 - Reserved
} GPIO_Config;

// Mode definitions
typedef enum {
    INPUT           = 0x0,  // 00
    OUTPUT          = 0x1,  // 01
    ALT_FUNCTION    = 0x2,  // 10
    ANALOG          = 0x3   // 11
} GPIO_Mode;

// Speed definitions
typedef enum {
    LOW_SPEED      = 0x0,  // 00
    MEDIUM_SPEED   = 0x1,  // 01
    HIGH_SPEED     = 0x2,  // 10
    VERY_HIGH_SPEED= 0x3   // 11
} GPIO_Speed;

// Pull-up/Pull-down definitions
typedef enum {
    NO_PULL        = 0x0,  // 00
    PULL_UP        = 0x1,  // 01
    PULL_DOWN      = 0x2,  // 10
} GPIO_Pull;

void print_binary32(uint32_t num) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
        if (i % 4 == 0 && i > 0) printf(" ");
    }
}

void print_register(GPIO_Config *config) {
    // Trick to print structure as 32-bit value
    uint32_t *reg_ptr = (uint32_t *)config;
    
    printf("Register value: 0x%08X\n", *reg_ptr);
    printf("Binary: ");
    print_binary32(*reg_ptr);
    printf("\n\n");
    
    printf("Bit Fields:\n");
    printf("  MODE     (bits 1:0)  = %d ", config->MODE);
    switch(config->MODE) {
        case INPUT:        printf("(Input)\n"); break;
        case OUTPUT:       printf("(Output)\n"); break;
        case ALT_FUNCTION: printf("(Alternate Function)\n"); break;
        case ANALOG:       printf("(Analog)\n"); break;
    }
    
    printf("  SPEED    (bits 3:2)  = %d ", config->SPEED);
    switch(config->SPEED) {
        case LOW_SPEED:       printf("(Low)\n"); break;
        case MEDIUM_SPEED:    printf("(Medium)\n"); break;
        case HIGH_SPEED:      printf("(High)\n"); break;
        case VERY_HIGH_SPEED: printf("(Very High)\n"); break;
    }
    
    printf("  PUPD     (bits 5:4)  = %d ", config->PUPD);
    switch(config->PUPD) {
        case NO_PULL:   printf("(No Pull)\n"); break;
        case PULL_UP:   printf("(Pull-up)\n"); break;
        case PULL_DOWN: printf("(Pull-down)\n"); break;
    }
    
    printf("  RESERVED (bits 31:6) = 0x%07X\n\n", config->RESERVED);
}

int main() {
    GPIO_Config gpio_pin;
    
    printf("GPIO Register Bit Field Demo\n");
    printf("============================\n\n");
    
    // Example 1: Configure as Output, High Speed, Pull-up
    printf("Configuration 1: Output, High Speed, Pull-up\n");
    printf("--------------------------------------------\n");
    gpio_pin.MODE = OUTPUT;
    gpio_pin.SPEED = HIGH_SPEED;
    gpio_pin.PUPD = PULL_UP;
    gpio_pin.RESERVED = 0;
    print_register(&gpio_pin);
    
    // Example 2: Configure as Input, No Pull
    printf("Configuration 2: Input, Low Speed, No Pull\n");
    printf("------------------------------------------\n");
    gpio_pin.MODE = INPUT;
    gpio_pin.SPEED = LOW_SPEED;
    gpio_pin.PUPD = NO_PULL;
    gpio_pin.RESERVED = 0;
    print_register(&gpio_pin);
    
    // Example 3: Configure as Analog
    printf("Configuration 3: Analog, Pull-down\n");
    printf("-----------------------------------\n");
    gpio_pin.MODE = ANALOG;
    gpio_pin.SPEED = MEDIUM_SPEED;
    gpio_pin.PUPD = PULL_DOWN;
    gpio_pin.RESERVED = 0;
    print_register(&gpio_pin);
    
    // Example 4: Direct register manipulation
    printf("Direct Register Manipulation\n");
    printf("----------------------------\n");
    uint32_t raw_register = 0x00000015;  // binary: ...01 01 01
    printf("Writing raw value: 0x%08X\n", raw_register);
    printf("Binary: ");
    print_binary32(raw_register);
    printf("\n\n");
    
    GPIO_Config *config_ptr = (GPIO_Config *)&raw_register;
    printf("Interpreted as GPIO_Config:\n");
    printf("  MODE  = %d (bits 1:0 extracted automatically)\n", config_ptr->MODE);
    printf("  SPEED = %d (bits 3:2 extracted automatically)\n", config_ptr->SPEED);
    printf("  PUPD  = %d (bits 5:4 extracted automatically)\n", config_ptr->PUPD);
    
    return 0;
}