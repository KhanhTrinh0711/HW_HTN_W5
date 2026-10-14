#include <stdint.h>

#define RCC_APB2ENR (*(volatile uint32_t *)0x40021018u)
#define GPIOA_CRL   (*(volatile uint32_t *)0x40010800u)
#define GPIOA_IDR   (*(volatile uint32_t *)0x40010808u)
#define GPIOA_ODR   (*(volatile uint32_t *)0x4001080Cu)
#define GPIOA_BSRR  (*(volatile uint32_t *)0x40010810u)
#define GPIOA_BRR   (*(volatile uint32_t *)0x40010814u)

#define RCC_IOPAEN  (1u << 2)
#define LED_MASK    0x0Fu
#define BUTTON_MASK 0xF0u

int main(void)
{
    uint32_t led;
    uint32_t button;

    RCC_APB2ENR |= RCC_IOPAEN;

    GPIOA_CRL |= 0x88882222u;
    GPIOA_ODR |= BUTTON_MASK;
    GPIOA_BRR |= LED_MASK;

    while (1)
    {
        for (led = 0u; led < 4u; ++led)
        {
            button = 7u - led;

            if ((GPIOA_IDR & (1u << button)) != 0u)
            {
                GPIOA_BSRR = 1u << led;
            }
            else
            {
                GPIOA_BRR = 1u << led;
            }
        }
    }
}
