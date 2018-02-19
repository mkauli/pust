#include <stdint.h>
#include <pru_cfg.h>
#include <pru_intc.h>
#include <pust_resource.h>

volatile register uint32_t __R30;
volatile register uint32_t __R31;

#define PUST_ARM_TRIGGER_IRQ  17
#define PRU_INTERRUPT_ENABLE  (1 << 5)
#define PRU_INTERRUPT_OFFSET  16

/**
 * main.c
 */
void main(void)
{
    volatile uint32_t gpio;

    // reset output before pin-muxing
    __R30 = 0;

    CT_CFG.SYSCFG_bit.STANDBY_INIT = 0;
    CT_CFG.GPCFG0 = 0;
    CT_INTC.SICR_bit.STS_CLR_IDX = PUST_ARM_TRIGGER_IRQ;

    gpio = 0x0001 << 7;
    while (1) {
        __R30 ^= gpio;

        if( __R31 & (0x0001<<5) )
        {
            /* generate pust trigger event */
            __R31 = (PRU_INTERRUPT_ENABLE | (PUST_ARM_TRIGGER_IRQ - PRU_INTERRUPT_OFFSET));

            __delay_cycles(100000000/2);
        }
        else
        {
            __delay_cycles(100000000);
        }
    }
}
