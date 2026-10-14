#include <stdint.h>

#define RCC_APB2ENR (*(volatile uint32_t *)0x40021018u)
#define GPIOC_CRH   (*(volatile uint32_t *)0x40011004u)
#define GPIOC_BSRR  (*(volatile uint32_t *)0x40011010u)
#define GPIOC_BRR   (*(volatile uint32_t *)0x40011014u)
#define SYST_CSR    (*(volatile uint32_t *)0xE000E010u)
#define SYST_RVR    (*(volatile uint32_t *)0xE000E014u)
#define SYST_CVR    (*(volatile uint32_t *)0xE000E018u)

#define RCC_IOPCEN  (1u << 4)
#define LED_PIN     (1u << 13)

#define CPU_CLOCK_HZ 8000000u
#define SYSTICK_CTRL_ENABLE  (1u << 0)
#define SYSTICK_CTRL_CLKSRC  (1u << 2)
#define SYSTICK_CTRL_COUNTFLAG (1u << 16)

static void systick_init(void);
static void delay_ms(uint32_t milliseconds);

int main(void)
{
    RCC_APB2ENR |= RCC_IOPCEN;

    GPIOC_CRH &= ~(0xFu << 20);
    GPIOC_CRH |=  (0x2u << 20);
    systick_init();

    while (1)
    {
        GPIOC_BRR = LED_PIN;
        delay_ms(1000);
        GPIOC_BSRR = LED_PIN;
        delay_ms(1000);
    }
}

static void systick_init(void)
{
    SYST_RVR = (CPU_CLOCK_HZ / 1000u) - 1u;
    SYST_CVR = 0u;
    SYST_CSR = SYSTICK_CTRL_CLKSRC | SYSTICK_CTRL_ENABLE;
}

static void delay_ms(uint32_t milliseconds)
{
    while (milliseconds-- > 0u)
    {
        while ((SYST_CSR & SYSTICK_CTRL_COUNTFLAG) == 0u)
        {
        }
    }
}
