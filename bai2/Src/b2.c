#include <stdint.h>

#define RCC_APB2ENR (*(volatile uint32_t *)0x40021018u)
#define GPIOA_CRL   (*(volatile uint32_t *)0x40010800u)
#define GPIOA_BSRR  (*(volatile uint32_t *)0x40010810u)
#define GPIOA_BRR   (*(volatile uint32_t *)0x40010814u)
#define SYST_CSR    (*(volatile uint32_t *)0xE000E010u)
#define SYST_RVR    (*(volatile uint32_t *)0xE000E014u)
#define SYST_CVR    (*(volatile uint32_t *)0xE000E018u)

#define RCC_IOPAEN  (1u << 2)
#define GPIOA_PINS  0xFFu

#define CPU_CLOCK_HZ 8000000u
#define SYSTICK_CTRL_ENABLE  (1u << 0)
#define SYSTICK_CTRL_CLKSRC  (1u << 2)
#define SYSTICK_CTRL_COUNTFLAG (1u << 16)

static void systick_init(void);
static void delay_ms(uint32_t milliseconds);
static void set_led(uint32_t pin);
static void clear_led(uint32_t pin);

int main(void)
{
    uint32_t pin;

    RCC_APB2ENR |= RCC_IOPAEN;
    GPIOA_CRL = 0x22222222u;
    GPIOA_BRR = GPIOA_PINS;
    systick_init();

    while (1)
    {
        for (pin = 0u; pin < 8u; ++pin)
        {
            set_led(1u << pin);
            delay_ms(1000u);
            clear_led(1u << pin);
        }

        for (pin = 8u; pin-- > 0u;)
        {
            set_led(1u << pin);
            delay_ms(1000u);
            clear_led(1u << pin);
        }
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

static void set_led(uint32_t pin)
{
    GPIOA_BSRR = pin;
}

static void clear_led(uint32_t pin)
{
    GPIOA_BRR = pin;
}
