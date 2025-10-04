#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
// Alignment requirement: 16 bytes
#define ALIGNMENT 16
// Align ’x’ upwards to the nearest multiple of ALIGNMENT
// Reference to PGROUNDUP in xv6
#define ALIGN(x) (((x) + ALIGNMENT - 1) & ~(ALIGNMENT - 1))
void *calloc(size_t nmemb, size_t size) {
if (nmemb == 0 || size == 0) {
return NULL;
}
size_t total = nmemb * size;
// Request slightly more memory to ensure proper alignment
void *raw = sbrk(total + ALIGNMENT);
if (raw == (void *)-1) {
// sbrk() failed to expand the heap
return NULL;
}
// Align the returned address to a 16-byte boundary
void *memory = (void *)ALIGN((uintptr_t)raw);
// Clear the allocated memory (zero-initialized)
memset(memory, 0, total);
return memory;
}
void free(void *ptr) {
// This simple implementation ignores free() calls.
return;
}