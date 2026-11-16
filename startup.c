#include <stdint.h>
extern uint32_t data_start;
extern uint32_t data_end;
extern uint32_t stack_top;
extern uint32_t bss_start;
extern uint32_t bss_end;
extern uint32_t data_load;

void reset_handler(void);

int main(void);

uint32_t vector_table[] __attribute__((section(".isr_vector"))) = {
    (uint32_t)&stack_top,
    (uint32_t)&reset_handler
};

void reset_handler(void)
{
 uint32_t *ram_data = (uint32_t *)&data_start;
 uint32_t *flash_data = (uint32_t *)&data_load;
 
 while (ram_data < &data_end) {
    *ram_data++ = *flash_data++;
 }

 uint32_t *bss_data = (uint32_t *)&bss_start;

 while (bss_data < &bss_end) {
    *bss_data++ = 0;
 }

 main();
 while (1) {

 }

}


