ENTRY(reset_handler)

MEMORY {
FLASH (rx): ORIGIN = 0x08000000, LENGTH = 512K
RAM (rwx): ORIGIN = 0x20000000, LENGTH = 128K
}


stack_top = ORIGIN(RAM) + LENGTH(RAM);
SECTIONS {
    .isr_vector : 
    {
        KEEP(*(.isr_vector));
    } > FLASH

    .text :
    {
        *(.text*)
    } > FLASH

    .rodata :
    {
        *(.rodata*)
    } > FLASH

    .data :
    {
        . = ALIGN(4);
        data_start = .;
        *(.data*)
        . = ALIGN(4);
        data_end = .;   
    } > RAM AT > FLASH
    data_load = LOADADDR(.data);

    .bss : 
    {
        . = ALIGN(4);
        bss_start = .;
        *(.bss*)
        *(COMMON)
        data_end = .;   
        bss_end = .;
    } > RAM

}