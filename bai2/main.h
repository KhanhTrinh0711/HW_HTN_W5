#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>

#define REG32(address) (*(volatile uint32_t *)(address))

#define RCC_CR          REG32(0x40021000u)
#define RCC_CFGR        REG32(0x40021004u)
#define RCC_APB2ENR     REG32(0x40021018u)
#define FLASH_ACR       REG32(0x40022000u)

#define AFIO_EXTICR1    REG32(0x40010008u)
#define EXTI_IMR        REG32(0x40010400u)
#define EXTI_RTSR       REG32(0x40010408u)
#define EXTI_FTSR       REG32(0x4001040Cu)
#define EXTI_PR         REG32(0x40010414u)

#define GPIOA_CRL       REG32(0x40010800u)
#define GPIOA_CRH       REG32(0x40010804u)
#define GPIOA_ODR       REG32(0x4001080Cu)

#define USART1_SR       REG32(0x40013800u)
#define USART1_DR       REG32(0x40013804u)
#define USART1_BRR      REG32(0x40013808u)
#define USART1_CR1      REG32(0x4001380Cu)

#define NVIC_ISER0      REG32(0xE000E100u)
#define NVIC_IPR        ((volatile uint8_t *)0xE000E400u)

#define RCC_AFIOEN      (1u << 0)
#define RCC_IOPAEN      (1u << 2)
#define RCC_USART1EN    (1u << 14)
#define EXTI0_IRQ       (1u << 6)
#define BUTTON_PIN      (1u << 0)
#define BUTTON_QUEUE_LENGTH 16u
#define UART_BAUD       115200u
#define SYSTEM_CLOCK_HZ 72000000u

void EXTI0_IRQHandler(void);

#endif
