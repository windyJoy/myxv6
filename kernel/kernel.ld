OUTPUT_ARCH(riscv)
ENTRY(_entry)

PHDRS
{
    text PT_LOAD FLAGS(5);  /* R+X */
    data PT_LOAD FLAGS(6);  /* R+W */
}

SECTIONS
{
    . = 0x80000000;

    .text : {
        *(.text)
    } :text

    .rodata : {
        *(.rodata)
    } :text

    .data : {
        *(.data)
    } :data

    .bss : {
        *(.bss)
    } :data
}