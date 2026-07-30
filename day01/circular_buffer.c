/*
 * Circular Buffer (Ring Buffer) Implementation
 *
 * How it works:
 *   - Fixed size array used as a circular queue
 *   - head: where next write goes (producer side)
 *   - tail: where next read comes from (consumer side)
 *   - count: number of valid elements currently stored
 *   - Modulo arithmetic wraps head/tail back to 0 when they reach the end
 *
 * Real embedded use cases:
 *   - UART receive buffer (ISR writes, main reads)
 *   - ADC sample buffer (DMA writes, processing task reads)
 *   - FreeRTOS is built on this concept for queues
 *
 * Why count instead of head==tail for empty/full detection:
 *   - If head==tail could mean BOTH empty and full
 *   - count removes that ambiguity cleanly
 *   - Alternative: leave one slot always empty (wastes one slot)
 */
#include <stdio.h>
#define CIRC_BUF_SIZE 8

typedef struct {
    int buf[CIRC_BUF_SIZE];
    int head;
    int tail;
    int count;
} CircBuf;

int cb_is_full(CircBuf *cb)  { return cb->count == CIRC_BUF_SIZE; }
int cb_is_empty(CircBuf *cb) { return cb->count == 0; }

void cb_push(CircBuf *cb, int val) {
    if (cb_is_full(cb)) return;
    cb->buf[cb->head] = val;
    cb->head = (cb->head + 1) % CIRC_BUF_SIZE; // wrap back to 0 when head reaches end
    cb->count++;
}

int cb_pop(CircBuf *cb) {
    if (cb_is_empty(cb)) return -1;
    int val = cb->buf[cb->tail];
    cb->tail = (cb->tail + 1) % CIRC_BUF_SIZE; // wrap back to 0 when head reaches end
    cb->count--;
    return val;
}

// Helper function to print buffer state
void print_buffer_state(CircBuf *cb, const char *label) {
    printf("%s\n", label);
    printf("  Buffer: [");
    for (int i = 0; i < 8; i++) {
        if (i == cb->head && i == cb->tail && cb->count > 0) {
            printf("*%d*", cb->buf[i]);  // Both head and tail
        } else if (i == cb->head) {
            printf(">%d<", cb->buf[i]);  // Head position
        } else if (i == cb->tail) {
            printf("(%d)", cb->buf[i]);  // Tail position
        } else {
            printf(" %d ", cb->buf[i]);  // Normal
        }
        if (i < 7) printf(",");
    }
    printf("]\n");
    printf("  head=%d, tail=%d, count=%d\n\n", cb->head, cb->tail, cb->count);
}

int main() {
    // Initialize buffer
    CircBuf cb = {0};  // Zero-initializes all fields
    
    printf("=== CIRCULAR BUFFER TEST ===\n\n");
    
    // Test 1: Push elements
    printf("--- Test 1: Pushing 5 elements ---\n");
    for (int i = 10; i <= 50; i += 10) {
        cb_push(&cb, i);
    }
    print_buffer_state(&cb, "After pushing 10,20,30,40,50:");
    
    // Test 2: Pop elements
    printf("--- Test 2: Popping 3 elements ---\n");
    for (int i = 0; i < 3; i++) {
        int val = cb_pop(&cb);
        printf("Popped: %d\n", val);
    }
    print_buffer_state(&cb, "After popping 3 elements:");
    
    // Test 3: Push more (wrap-around test)
    printf("--- Test 3: Push to test wrap-around ---\n");
    for (int i = 60; i <= 100; i += 10) {
        cb_push(&cb, i);
    }
    print_buffer_state(&cb, "After pushing 60,70,80,90,100:");
    
    // Test 4: Fill buffer completely
    printf("--- Test 4: Fill buffer to capacity ---\n");
    while (cb.count < 8) {
        cb_push(&cb, 999);  // Fill remaining slots
    }
    print_buffer_state(&cb, "Buffer full (8 elements):");
    
    // Test 5: Try pushing to full buffer
    printf("--- Test 5: Push to full buffer ---\n");
    cb_push(&cb, 111);  // Should be rejected
    printf("Tried to push 111 to full buffer\n");
    print_buffer_state(&cb, "Buffer unchanged (push rejected):");
    
    // Test 6: Empty the buffer
    printf("--- Test 6: Pop all elements ---\n");
    printf("Popping all: ");
    while (cb.count > 0) {
        printf("%d ", cb_pop(&cb));
    }
    printf("\n");
    print_buffer_state(&cb, "Empty buffer:");
    
    // Test 7: Pop from empty buffer
    printf("--- Test 7: Pop from empty buffer ---\n");
    int val = cb_pop(&cb);
    printf("Popped from empty buffer: %d (expected -1)\n\n", val);
    
    // Test 8: Wrap-around edge case
    printf("--- Test 8: Wrap-around with full cycle ---\n");
    // Fill buffer
    for (int i = 1; i <= 8; i++) {
        cb_push(&cb, i * 10);
    }
    print_buffer_state(&cb, "Filled:");
    
    // Pop all
    printf("Popping all: ");
    while (cb.count > 0) {
        printf("%d ", cb_pop(&cb));
    }
    printf("\n");
    
    // Fill again (different pattern)
    for (int i = 1; i <= 4; i++) {
        cb_push(&cb, i * 100);
    }
    print_buffer_state(&cb, "After refilling with 4 elements:");
    
    return 0;
}

