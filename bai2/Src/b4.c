#include <stdint.h>

#define RCC_APB2ENR (*(volatile uint32_t *)0x40021018u)
#define GPIOA_CRL   (*(volatile uint32_t *)0x40010800u)
#define GPIOA_IDR   (*(volatile uint32_t *)0x40010808u)
#define GPIOA_ODR   (*(volatile uint32_t *)0x4001080Cu)
#define GPIOA_BSRR  (*(volatile uint32_t *)0x40010810u)
#define GPIOA_BRR   (*(volatile uint32_t *)0x40010814u)
#define SYST_CSR    (*(volatile uint32_t *)0xE000E010u)
#define SYST_RVR    (*(volatile uint32_t *)0xE000E014u)
#define SYST_CVR    (*(volatile uint32_t *)0xE000E018u)

#define RCC_IOPAEN  (1u << 2)
#define LED_MASK    0x0Fu
#define BUTTON_MASK 0xF0u

#define CPU_CLOCK_HZ 8000000u
#define SYSTICK_CTRL_ENABLE  (1u << 0)
#define SYSTICK_CTRL_CLKSRC  (1u << 2)
#define SYSTICK_CTRL_COUNTFLAG (1u << 16)

static void systick_init(void);
static void delay_ms(uint32_t milliseconds);
static void write_leds(uint32_t state);

int main(void)
{
    uint32_t led;
    uint32_t button;
    uint32_t button_mask;
    uint32_t led_state = 0u;

    RCC_APB2ENR |= RCC_IOPAEN;

    GPIOA_CRL = 0x88882222u;
    GPIOA_ODR |= BUTTON_MASK;
    GPIOA_BRR = LED_MASK;
    systick_init();

    while (1)
    {
        for (led = 0u; led < 4u; ++led)
        {
            button = 7u - led;
            button_mask = 1u << button;

            if ((GPIOA_IDR & button_mask) == 0u)
            {
                led_state ^= 1u << led;
                write_leds(led_state);
                delay_ms(20u);

                while ((GPIOA_IDR & button_mask) == 0u)
                {
                }
            }
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

static void write_leds(uint32_t state)
{
    GPIOA_BRR = LED_MASK;
    GPIOA_BSRR = state & LED_MASK;
}
