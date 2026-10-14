#define RCC_CR          (*(volatile unsigned int *)0x40021000)
#define RCC_CFGR        (*(volatile unsigned int *)0x40021004)
#define RCC_APB2ENR     (*(volatile unsigned int *)0x40021018)

#define FLASH_ACR       (*(volatile unsigned int *)0x40022000)

#define GPIOC_CRH       (*(volatile unsigned int *)0x40011004)
#define GPIOC_BSRR      (*(volatile unsigned int *)0x40011010)

#define SYST_CSR        (*(volatile unsigned int *)0xE000E010)
#define SYST_RVR        (*(volatile unsigned int *)0xE000E014)
#define SYST_CVR        (*(volatile unsigned int *)0xE000E018)

static void clock_init(void)
{
    FLASH_ACR &= ~0x7U;
    FLASH_ACR |=  0x2U;

    RCC_CR |= (1U << 16);

    while (!(RCC_CR & (1U << 17)))
    {
    }

    RCC_CFGR = 0;

    RCC_CFGR |= (4U << 8);

    RCC_CFGR |= (1U << 16);

    RCC_CFGR |= (7U << 18);

    RCC_CR |= (1U << 24);

    while (!(RCC_CR & (1U << 25)))
    {
    }

    RCC_CFGR &= ~(3U << 0);
    RCC_CFGR |=  (2U << 0);

    while ((RCC_CFGR & (3U << 2)) != (2U << 2))
    {
    }
}

static void systick_init(void)
{
    SYST_RVR = 72000U - 1U;

    SYST_CVR = 0;

    SYST_CSR = (1U << 2) | (1U << 0);
}

static void delay_ms(unsigned int ms)
{
    while (ms--)
    {
        while (!(SYST_CSR & (1U << 16)))
        {
        }
    }
}

int main(void)
{
    clock_init();

    systick_init();

    RCC_APB2ENR |= (1U << 4);

    GPIOC_CRH &= ~(0xFU << 20);
    GPIOC_CRH |=  (0x2U << 20);

    while (1)
    {
        GPIOC_BSRR = (1U << 29);

        delay_ms(10);

        GPIOC_BSRR = (1U << 13);

        delay_ms(10);
    }
}