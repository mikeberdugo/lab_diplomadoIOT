//*****************************************************************************
// NHS3xxx Microcontroller Startup code for use with MCUXpresso IDE
//
// Version : 130522
//*****************************************************************************
//
// Copyright(C) NXP Semiconductors, 2022
// All rights reserved.
//
// NXP Confidential. This software is owned or controlled by NXP and may only be
// used strictly in accordance with the applicable license terms.
//
// By expressly accepting such terms or by downloading, installing, activating
// and/or otherwise using the software, you are agreeing that you have read, and
// that you agree to comply with and are bound by, such license terms.
// 
// If you do not agree to be bound by the applicable license terms, then you may not
// retain, install, activate or otherwise use the software.
//*****************************************************************************


#if defined (DEBUG)
#pragma GCC push_options
#pragma GCC optimize ("Og")
#endif // (DEBUG)

#if defined (__cplusplus)
#ifdef __REDLIB__
#error Redlib does not support C++
#else
//*****************************************************************************
//
// The entry point for the C++ library startup
//
//*****************************************************************************
extern "C" {
    extern void __libc_init_array(void);
}
#endif
#endif

#define WEAK __attribute__ ((weak))
#define ALIAS(f) __attribute__ ((weak, alias (#f)))

//*****************************************************************************
#if defined (__cplusplus)
extern "C" {
#endif

//*****************************************************************************
#if defined (__USE_CMSIS) || defined (__USE_LPCOPEN)
// Declaration of external SystemInit function
extern void SystemInit(void);
#endif

//*****************************************************************************
//
// Forward declaration of the default handlers. These are aliased.
// When the application defines a handler (with the same name), this will
// automatically take precedence over these weak definitions
//
//*****************************************************************************
     void ResetISR(void);
WEAK void NMI_Handler(void);
WEAK void HardFault_Handler(void);
WEAK void SVC_Handler(void);
WEAK void PendSV_Handler(void);
WEAK void SysTick_Handler(void);
WEAK void IntDefaultHandler(void);

//*****************************************************************************
//
// Forward declaration of the specific IRQ handlers. These are aliased
// to the IntDefaultHandler, which is a 'forever' loop. When the application
// defines a handler (with the same name), this will automatically take
// precedence over these weak definitions
//
//*****************************************************************************
void GPIO0_0_IRQHandler(void)   ALIAS(IntDefaultHandler);
void GPIO0_1_IRQHandler(void)   ALIAS(IntDefaultHandler);
void GPIO0_2_IRQHandler(void)   ALIAS(IntDefaultHandler);
void GPIO0_3_IRQHandler(void)   ALIAS(IntDefaultHandler);
void GPIO0_4_IRQHandler(void)   ALIAS(IntDefaultHandler);
void GPIO0_5_IRQHandler(void)   ALIAS(IntDefaultHandler);
void GPIO0_6_IRQHandler(void)   ALIAS(IntDefaultHandler);
void GPIO0_7_IRQHandler(void)   ALIAS(IntDefaultHandler);
void GPIO0_8_IRQHandler(void)   ALIAS(IntDefaultHandler);
void GPIO0_9_IRQHandler(void)   ALIAS(IntDefaultHandler);
void GPIO0_10_IRQHandler(void)  ALIAS(IntDefaultHandler);
void RFFIELD_IRQHandler(void)   ALIAS(IntDefaultHandler);
void RTCPWREQ_IRQHandler(void)  ALIAS(IntDefaultHandler);
void NFC_IRQHandler(void)       ALIAS(IntDefaultHandler);
void RTC_IRQHandler(void)       ALIAS(IntDefaultHandler);
void I2C0_IRQHandler(void)      ALIAS(IntDefaultHandler);
void CT16B0_IRQHandler(void)    ALIAS(IntDefaultHandler);
void PMUFLD_IRQHandler(void)    ALIAS(IntDefaultHandler);
void CT32B0_IRQHandler(void)    ALIAS(IntDefaultHandler);
void PMUBOD_IRQHandler(void)    ALIAS(IntDefaultHandler);
void SSP0_IRQHandler(void)      ALIAS(IntDefaultHandler);
void TSEN_IRQHandler(void)      ALIAS(IntDefaultHandler);
void ADC_IRQHandler(void)       ALIAS(IntDefaultHandler);
void WDT_IRQHandler(void)       ALIAS(IntDefaultHandler);
void FLASH_IRQHandler(void)     ALIAS(IntDefaultHandler);
void EEPROM_IRQHandler(void)    ALIAS(IntDefaultHandler);
void GPIO0_IRQHandler(void)     ALIAS(IntDefaultHandler);

//*****************************************************************************
//
// The entry point for the application.
// __main() is the entry point for Redlib based applications
// main() is the entry point for Newlib based applications
//
//*****************************************************************************
#if defined (__REDLIB__)
extern void __main(void);
#else
extern int main(void);
#endif
//*****************************************************************************
//
// External declaration for the pointer to the stack top from the Linker Script
//
//*****************************************************************************
extern void _vStackTop(void);

//*****************************************************************************
//
// External declaration for MCU vector table checksum from  Linker Script
//
//*****************************************************************************
WEAK extern void __valid_user_code_checksum();

//*****************************************************************************
#if defined (__cplusplus)
} // extern "C"
#endif
//*****************************************************************************
//
// The vector table.
// This relies on the linker script to place at correct location in memory.
//
//*****************************************************************************
extern void (* const g_pfnVectors[])(void);
__attribute__ ((used,section(".isr_vector")))
void (* const g_pfnVectors[])(void) = {
    // Core Level - CM0plus
    &_vStackTop, // The initial stack pointer
    ResetISR,                               // The reset handler
    NMI_Handler,                            // The NMI handler
    HardFault_Handler,                      // The hard fault handler
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    __valid_user_code_checksum,             // LPC MCU Checksum
    0,                                      // Reserved
    0,                                      // Reserved
    0,                                      // Reserved
    SVC_Handler,                            // SVCall handler
    0,                                      // Reserved
    0,                                      // Reserved
    PendSV_Handler,                         // The PendSV handler
    SysTick_Handler,                        // The SysTick handler

    // Chip Level - LPC8N0x
    GPIO0_0_IRQHandler,     //  0 - GPIO0_0
    GPIO0_1_IRQHandler,     //  1 - GPIO0_1
    GPIO0_2_IRQHandler,     //  2 - GPIO0_2
    GPIO0_3_IRQHandler,     //  3 - GPIO0_3
    GPIO0_4_IRQHandler,     //  4 - GPIO0_4
    GPIO0_5_IRQHandler,     //  5 - GPIO0_5
    GPIO0_6_IRQHandler,     //  6 - GPIO0_6
    GPIO0_7_IRQHandler,     //  7 - GPIO0_7
    GPIO0_8_IRQHandler,     //  8 - GPIO0_8
    GPIO0_9_IRQHandler,     //  9 - GPIO0_9
    GPIO0_10_IRQHandler,    // 10 - GPIO0_10,
    RFFIELD_IRQHandler,     // 11 - RFID/NFC external access
    RTCPWREQ_IRQHandler,    // 12 - RTC timer
    NFC_IRQHandler,         // 13 - RFID/NFC
    RTC_IRQHandler,         // 14 - RTC timer event
    I2C0_IRQHandler,        // 15 - I2S
    CT16B0_IRQHandler,      // 16 - 16bit Counter Timer
    PMUFLD_IRQHandler,      // 17 - Power Management Unit
    CT32B0_IRQHandler,      // 18 - 32bit Counter Timer
    PMUBOD_IRQHandler,      // 19 - Brown Out Detect
    SSP0_IRQHandler,        // 20 - SPI / SSP
    TSEN_IRQHandler,        // 21 - Temperature Sensor
    0,                      // 22 - RESERVED
    0,                      // 23 - RESERVED
    0,                      // 24 - RESERVED
    ADC_IRQHandler,         // 25 - ADC / DAC
    WDT_IRQHandler,         // 26 - Watchdog
    FLASH_IRQHandler,       // 27 - Flash
    EEPROM_IRQHandler,      // 28 - EEPROM
    0,                      // 29 - RESERVED
    0,                      // 30 - RESERVED
    GPIO0_IRQHandler        // 31 - GPIO interrupt status of port 0
}; /* End of g_pfnVectors */

//*****************************************************************************
// Functions to carry out the initialization of RW and BSS data sections. These
// are written as separate functions rather than being inlined within the
// ResetISR() function in order to cope with MCUs with multiple banks of
// memory.
//*****************************************************************************
__attribute__ ((section(".after_vectors")))
void data_init(unsigned int romstart, unsigned int start, unsigned int len) {
    unsigned int *pulDest = (unsigned int*) start;
    unsigned int *pulSrc = (unsigned int*) romstart;
    unsigned int loop;
    for (loop = 0; loop < len; loop = loop + 4)
        *pulDest++ = *pulSrc++;
}

__attribute__ ((section(".after_vectors")))
void bss_init(unsigned int start, unsigned int len) {
    unsigned int *pulDest = (unsigned int*) start;
    unsigned int loop;
    for (loop = 0; loop < len; loop = loop + 4)
        *pulDest++ = 0;
}

//*****************************************************************************
// The following symbols are constructs generated by the linker, indicating
// the location of various points in the "Global Section Table". This table is
// created by the linker via the Code Red managed linker script mechanism. It
// contains the load address, execution address and length of each RW data
// section and the execution and length of each BSS (zero initialized) section.
//*****************************************************************************
extern unsigned int __data_section_table;
extern unsigned int __data_section_table_end;
extern unsigned int __bss_section_table;
extern unsigned int __bss_section_table_end;


//*****************************************************************************
// Reset entry point for your code.
// Sets up a simple runtime environment and initializes the C/C++
// library.
//*****************************************************************************
__attribute__ ((section(".after_vectors")))
void
ResetISR(void) {

    //
    // Copy the data sections from flash to SRAM.
    //
    unsigned int LoadAddr, ExeAddr, SectionLen;
    unsigned int *SectionTableAddr;

    // Load base address of Global Section Table
    SectionTableAddr = &__data_section_table;

    // Copy the data sections from flash to SRAM.
    while (SectionTableAddr < &__data_section_table_end) {
        LoadAddr = *SectionTableAddr++;
        ExeAddr = *SectionTableAddr++;
        SectionLen = *SectionTableAddr++;
        data_init(LoadAddr, ExeAddr, SectionLen);
    }
    // At this point, SectionTableAddr = &__bss_section_table;
    // Zero fill the bss segment
    while (SectionTableAddr < &__bss_section_table_end) {
        ExeAddr = *SectionTableAddr++;
        SectionLen = *SectionTableAddr++;
        bss_init(ExeAddr, SectionLen);
    }

#if defined (__USE_CMSIS) || defined (__USE_LPCOPEN)
    SystemInit();
#endif

#if defined (__cplusplus)
    //
    // Call C++ library initialisation
    //
    __libc_init_array();
#endif

#if defined (__REDLIB__)
    // Call the Redlib library, which in turn calls main()
    __main() ;
#else
    main();
#endif

    //
    // main() shouldn't return, but if it does, we'll just enter an infinite loop
    //
    while (1) {
        ;
    }
}

//*****************************************************************************
// Default exception handlers. Override the ones here by defining your own
// handler routines in your application code.
//*****************************************************************************
__attribute__ ((section(".after_vectors")))
void NMI_Handler(void)
{ while(1) {}
}

__attribute__ ((section(".after_vectors")))
void HardFault_Handler(void)
{ while(1) {}
}

__attribute__ ((section(".after_vectors")))
void SVC_Handler(void)
{ while(1) {}
}

__attribute__ ((section(".after_vectors")))
void PendSV_Handler(void)
{ while(1) {}
}

__attribute__ ((section(".after_vectors")))
void SysTick_Handler(void)
{ while(1) {}
}

//*****************************************************************************
//
// Processor ends up here if an unexpected interrupt occurs or a specific
// handler is not present in the application code.
//
//*****************************************************************************
__attribute__ ((section(".after_vectors")))
void IntDefaultHandler(void)
{ while(1) {}
}

#if defined (DEBUG)
#pragma GCC pop_options
#endif // (DEBUG)
