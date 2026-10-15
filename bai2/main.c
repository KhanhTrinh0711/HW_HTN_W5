#include <stddef.h>

#include "main.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"

static QueueHandle_t buttonCountQueue;
static volatile uint32_t buttonPressCount;

static void clock_init(void)
{
    FLASH_ACR = (FLASH_ACR & ~0x7u) | 0x2u;

    RCC_CR |= (1u << 16);
    while ((RCC_CR & (1u << 17)) == 0u)
    {
    }

    RCC_CFGR = 0u;
    RCC_CFGR |= (4u << 8);
    RCC_CFGR |= (1u << 16);
    RCC_CFGR |= (7u << 18);

    RCC_CR |= (1u << 24);
    while ((RCC_CR & (1u << 25)) == 0u)
    {
    }

    RCC_CFGR = (RCC_CFGR & ~0x3u) | 0x2u;
    while ((RCC_CFGR & (3u << 2)) != (2u << 2))
    {
    }
}

static void gpio_init(void)
{
    RCC_APB2ENR |= RCC_AFIOEN | RCC_IOPAEN | RCC_IOPCEN;

    GPIOA_CRL = (GPIOA_CRL & ~(0xFu << 20)) | (0x8u << 20);
    GPIOA_ODR |= BUTTON_PIN;

    GPIOC_CRH = (GPIOC_CRH & ~(0xFu << 20)) | (0x6u << 20);
    GPIOC_ODR |= LED_PIN;

    GPIOA_CRH = (GPIOA_CRH & ~((0xFu << 4) | (0xFu << 8)))
              | (0xBu << 4)
              | (0x4u << 8);
}

static void uart1_init(void)
{
    RCC_APB2ENR |= RCC_USART1EN;
    USART1_CR1 = 0u;
    USART1_BRR = (SYSTEM_CLOCK_HZ + (UART_BAUD / 2u)) / UART_BAUD;
    USART1_CR1 = (1u << 13) | (1u << 3);
}

static void uart1_write_char(char character)
{
    while ((USART1_SR & (1u << 7)) == 0u)
    {
    }
    USART1_DR = (uint8_t)character;
}

static void uart1_write_text(const char *text)
{
    while (*text != '\0')
    {
        uart1_write_char(*text++);
    }
}

static void uart1_write_count(uint32_t count)
{
    char digits[10];
    uint32_t digitCount = 0u;

    do
    {
        digits[digitCount++] = (char)('0' + (count % 10u));
        count /= 10u;
    } while (count != 0u);

    uart1_write_text("Btn count: ");
    while (digitCount > 0u)
    {
        uart1_write_char(digits[--digitCount]);
    }
    uart1_write_text("\r\n");
}

static void exti_init(void)
{
    AFIO_EXTICR2 &= ~(0xFu << 4);
    EXTI_IMR &= ~BUTTON_PIN;
    EXTI_RTSR &= ~BUTTON_PIN;
    EXTI_FTSR |= BUTTON_PIN;
    EXTI_PR = BUTTON_PIN;

    NVIC_IPR[23] = (uint8_t)configMAX_SYSCALL_INTERRUPT_PRIORITY;
    NVIC_ISER0 = EXTI9_5_IRQ;
    EXTI_IMR |= BUTTON_PIN;
}

static void uart_task(void *argument)
{
    uint32_t count;
    (void)argument;

    uart1_write_text("UART ready. Press PA5.\r\n");
    for (;;)
    {
        if (xQueueReceive(buttonCountQueue, &count, portMAX_DELAY) == pdPASS)
        {
            uart1_write_count(count);
            GPIOC_ODR &= ~LED_PIN;
            vTaskDelay(pdMS_TO_TICKS(100u));
            GPIOC_ODR |= LED_PIN;
        }
    }
}

static void button_pressed_from_isr(uint32_t pin)
{
    BaseType_t higherPriorityTaskWoken = pdFALSE;
    uint32_t count;

    EXTI_PR = pin;
    count = ++buttonPressCount;
    (void)xQueueSendFromISR(buttonCountQueue, &count, &higherPriorityTaskWoken);
    portYIELD_FROM_ISR(higherPriorityTaskWoken);
}

void EXTI9_5_IRQHandler(void)
{
    if ((EXTI_PR & BUTTON_PIN) != 0u)
    {
        button_pressed_from_isr(BUTTON_PIN);
    }
}

int main(void)
{
    clock_init();
    gpio_init();
    uart1_init();

    buttonCountQueue = xQueueCreate(BUTTON_QUEUE_LENGTH, sizeof(uint32_t));
    configASSERT(buttonCountQueue != NULL);
    configASSERT(xTaskCreate(uart_task, "UART", configMINIMAL_STACK_SIZE + 128u,
                             NULL, tskIDLE_PRIORITY + 1u, NULL) == pdPASS);

    exti_init();
    vTaskStartScheduler();

    for (;;)
    {
    }
}