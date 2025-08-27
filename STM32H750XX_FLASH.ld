/* Entry Point */
ENTRY(Reset_Handler)

/* Highest address of the user mode stack */
_estack          = ORIGIN(DTCMRAM) + LENGTH(DTCMRAM);    /* end of RAM */
/* Generate a link error if heap and stack don't fit into RAM */
_Min_Heap_Size   = 0x1E000;      /* required amount of heap  */
_Min_Stack_Size  = 0x2000;       /* required amount of stack */

/* Specify the memory areas */
MEMORY
{
    DTCMRAM  (xrw) : ORIGIN = 0x20000000, LENGTH = 128K
    ITCMRAM  (xrw) : ORIGIN = 0x00000000, LENGTH = 64K
    RAM      (xrw) : ORIGIN = 0x24000000, LENGTH = 512K
    RAM_D2   (xrw) : ORIGIN = 0x30000000, LENGTH = 288K
    RAM_D3   (xrw) : ORIGIN = 0x38000000, LENGTH = 64K
    SDRAM    (xrw) : ORIGIN = 0xC0000000, LENGTH = 32M
    FLASH    (rx)  : ORIGIN = 0x8000000,  LENGTH = 128K
    QSPI     (rx)  : ORIGIN = 0x90000000, LENGTH = 8M
}

/* Define output sections */
SECTIONS
{
    /* The startup code goes first into FLASH */
    .isr_vector :
    {
        . = ALIGN(4);
        KEEP(*(.isr_vector)) /* Startup code */
        . = ALIGN(4);
    } >QSPI

    /* The program code and other data goes into FLASH */
    .text :
    {
        . = ALIGN(4);
        *(.text)           /* .text sections (code) */
        *(.text*)          /* .text* sections (code) */
        *(.glue_7)         /* glue arm to thumb code */
        *(.glue_7t)        /* glue thumb to arm code */
        *(.eh_frame)

        KEEP (*(.init))
        KEEP (*(.fini))

        . = ALIGN(4);
        _etext = .;        /* define a global symbols at end of code */
    } >QSPI

    /* 放到片内 Flash 的代码区 */
    .flash_embed :
    {
        . = ALIGN(4);
        *(.FastFlash*)            /* 收集所有带 .FastFlash 的函数/变量 */
        . = ALIGN(4);
    } >FLASH

    /* 放到片外 QSPI Flash 的代码区 */
    .flash_external :
    {
        . = ALIGN(4);
        *(.SlowFlash*)            /* 收集所有带 .SlowFlash 的函数/变量 */
        . = ALIGN(4);
    } >QSPI

    /* 在SDRAM区域内添加自定义段 */
    .sdram_data : {
      . = ALIGN(4);       /* 4字节对齐 */
      *(.ExtSRAM)      /* 匹配所有标记为.sdram_data的段 */
      . = ALIGN(4);
    } > SDRAM             /* 指定段存储到SDRAM区域 */
    /* Constant data goes into FLASH */
    .rodata :
    {
        . = ALIGN(4);
        *(.rodata)         /* .rodata sections (constants, strings, etc.) */
        *(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
        . = ALIGN(4);
    } >QSPI

    .ARM.extab  :
    {
        . = ALIGN(4);
        *(.ARM.extab* .gnu.linkonce.armextab.*)
        . = ALIGN(4);
    } >QSPI

    .ARM  :
    {
        . = ALIGN(4);
        __exidx_start = .;
        *(.ARM.exidx*)
        __exidx_end = .;
        . = ALIGN(4);
    } >QSPI

    .preinit_array  :
    {
        . = ALIGN(4);
        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP (*(.preinit_array*))
        PROVIDE_HIDDEN (__preinit_array_end = .);
        . = ALIGN(4);
    } >QSPI

    .init_array  :
    {
        . = ALIGN(4);
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP (*(SORT(.init_array.*)))
        KEEP (*(.init_array*))
        PROVIDE_HIDDEN (__init_array_end = .);
        . = ALIGN(4);
    } >QSPI

    .fini_array  :
    {
        . = ALIGN(4);
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP (*(SORT(.fini_array.*)))
        KEEP (*(.fini_array*))
        PROVIDE_HIDDEN (__fini_array_end = .);
        . = ALIGN(4);
    } >QSPI

    /* used by the startup to initialize data */
    _sidata = LOADADDR(.data);

    /* Initialized data sections goes into RAM, load LMA copy after code */
    .data :
    {
        . = ALIGN(4);
        _sdata = .;        /* create a global symbol at data start */
        *(.data)           /* .data sections */
        *(.data*)          /* .data* sections */
        *(.RamFunc)        /* .RamFunc sections */
        *(.RamFunc*)       /* .RamFunc* sections */

        . = ALIGN(4);
        _edata = .;        /* define a global symbol at data end */
    } >RAM_D2 AT> QSPI

    /* Uninitialized data section */
    . = ALIGN(4);
    .bss :
    {
        /* This is used by the startup in order to initialize the .bss secion */
        _sbss = .;         /* define a global symbol at bss start */
        __bss_start__ = _sbss;
        *(.bss)
        *(.bss*)
        *(COMMON)

        . = ALIGN(4);
        _ebss = .;         /* define a global symbol at bss end */
        __bss_end__ = _ebss;
    } >RAM_D2

    /* User_heap_stack section, used to check that there is enough RAM left */
    /* 堆 */
    ._heap :
    {
        . = ALIGN(8);
        PROVIDE(_heap_start = .);
        . = . + _Min_Heap_Size;
        PROVIDE(_heap_end = .);
    } >DTCMRAM

    /* 栈 */
    ._stack :
    {
        . = ALIGN(8);
        PROVIDE(_stack_start = .); /* 栈顶 */
        . = . + _Min_Stack_Size;
        PROVIDE(_stack_end = .);   /* 栈底 */
    } >DTCMRAM

    /* Remove information from the standard libraries */
    /DISCARD/ :
    {
        libc.a ( * )
        libm.a ( * )
        libgcc.a ( * )
    }
}