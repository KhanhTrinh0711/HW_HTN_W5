#include <stdint.h>

extern uint32_t _sidata;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _estack;

int main(void);

void Reset_Handler(void);
void Default_Handler(void);

#define DECLARE_DEFAULT_HANDLER(handler) \
    void handler(void) __attribute__((weak, alias("Default_Handler")))

DECLARE_DEFAULT_HANDLER(NMI_Handler);
DECLARE_DEFAULT_HANDLER(HardFault_Handler);
DECLARE_DEFAULT_HANDLER(MemManage_Handler);
DECLARE_DEFAULT_HANDLER(BusFault_Handler);
DECLARE_DEFAULT_HANDLER(UsageFault_Handler);
DECLARE_DEFAULT_HANDLER(SVC_Handler);
DECLARE_DEFAULT_HANDLER(DebugMon_Handler);
DECLARE_DEFAULT_HANDLER(PendSV_Handler);
DECLARE_DEFAULT_HANDLER(SysTick_Handler);

DECLARE_DEFAULT_HANDLER(WWDG_IRQHandler);
DECLARE_DEFAULT_HANDLER(PVD_IRQHandler);
DECLARE_DEFAULT_HANDLER(TAMPER_IRQHandler);
DECLARE_DEFAULT_HANDLER(RTC_IRQHandler);
DECLARE_DEFAULT_HANDLER(FLASH_IRQHandler);
DECLARE_DEFAULT_HANDLER(RCC_IRQHandler);
void EXTI0_IRQHandler(void);
DECLARE_DEFAULT_HANDLER(EXTI1_IRQHandler);
DECLARE_DEFAULT_HANDLER(EXTI2_IRQHandler);
DECLARE_DEFAULT_HANDLER(EXTI3_IRQHandler);
DECLARE_DEFAULT_HANDLER(EXTI4_IRQHandler);
DECLARE_DEFAULT_HANDLER(DMA1_Channel1_IRQHandler);
DECLARE_DEFAULT_HANDLER(DMA1_Channel2_IRQHandler);
DECLARE_DEFAULT_HANDLER(DMA1_Channel3_IRQHandler);
DECLARE_DEFAULT_HANDLER(DMA1_Channel4_IRQHandler);
DECLARE_DEFAULT_HANDLER(DMA1_Channel5_IRQHandler);
DECLARE_DEFAULT_HANDLER(DMA1_Channel6_IRQHandler);
DECLARE_DEFAULT_HANDLER(DMA1_Channel7_IRQHandler);
DECLARE_DEFAULT_HANDLER(ADC1_2_IRQHandler);
DECLARE_DEFAULT_HANDLER(USB_HP_CAN_TX_IRQHandler);
DECLARE_DEFAULT_HANDLER(USB_LP_CAN_RX0_IRQHandler);
DECLARE_DEFAULT_HANDLER(CAN_RX1_IRQHandler);
DECLARE_DEFAULT_HANDLER(CAN_SCE_IRQHandler);
DECLARE_DEFAULT_HANDLER(EXTI9_5_IRQHandler);
DECLARE_DEFAULT_HANDLER(TIM1_BRK_IRQHandler);
DECLARE_DEFAULT_HANDLER(TIM1_UP_IRQHandler);
DECLARE_DEFAULT_HANDLER(TIM1_TRG_COM_IRQHandler);
DECLARE_DEFAULT_HANDLER(TIM1_CC_IRQHandler);
DECLARE_DEFAULT_HANDLER(TIM2_IRQHandler);
DECLARE_DEFAULT_HANDLER(TIM3_IRQHandler);
DECLARE_DEFAULT_HANDLER(TIM4_IRQHandler);
DECLARE_DEFAULT_HANDLER(I2C1_EV_IRQHandler);
DECLARE_DEFAULT_HANDLER(I2C1_ER_IRQHandler);
DECLARE_DEFAULT_HANDLER(I2C2_EV_IRQHandler);
DECLARE_DEFAULT_HANDLER(I2C2_ER_IRQHandler);
DECLARE_DEFAULT_HANDLER(SPI1_IRQHandler);
DECLARE_DEFAULT_HANDLER(SPI2_IRQHandler);
DECLARE_DEFAULT_HANDLER(USART1_IRQHandler);
DECLARE_DEFAULT_HANDLER(USART2_IRQHandler);
DECLARE_DEFAULT_HANDLER(USART3_IRQHandler);
DECLARE_DEFAULT_HANDLER(EXTI15_10_IRQHandler);
DECLARE_DEFAULT_HANDLER(RTCAlarm_IRQHandler);
DECLARE_DEFAULT_HANDLER(USBWakeUp_IRQHandler);

__attribute__((section(".isr_vector"), used))
const uintptr_t vector_table[] = {
    (uintptr_t)&_estack,
    (uintptr_t)Reset_Handler,
    (uintptr_t)NMI_Handler,
    (uintptr_t)HardFault_Handler,
    (uintptr_t)MemManage_Handler,
    (uintptr_t)BusFault_Handler,
    (uintptr_t)UsageFault_Handler,
    0u, 0u, 0u, 0u,
    (uintptr_t)SVC_Handler,
    (uintptr_t)DebugMon_Handler,
    0u,
    (uintptr_t)PendSV_Handler,
    (uintptr_t)SysTick_Handler,
    (uintptr_t)WWDG_IRQHandler,
    (uintptr_t)PVD_IRQHandler,
    (uintptr_t)TAMPER_IRQHandler,
    (uintptr_t)RTC_IRQHandler,
    (uintptr_t)FLASH_IRQHandler,
    (uintptr_t)RCC_IRQHandler,
    (uintptr_t)EXTI0_IRQHandler,
    (uintptr_t)EXTI1_IRQHandler,
    (uintptr_t)EXTI2_IRQHandler,
    (uintptr_t)EXTI3_IRQHandler,
    (uintptr_t)EXTI4_IRQHandler,
    (uintptr_t)DMA1_Channel1_IRQHandler,
    (uintptr_t)DMA1_Channel2_IRQHandler,
    (uintptr_t)DMA1_Channel3_IRQHandler,
    (uintptr_t)DMA1_Channel4_IRQHandler,
    (uintptr_t)DMA1_Channel5_IRQHandler,
    (uintptr_t)DMA1_Channel6_IRQHandler,
    (uintptr_t)DMA1_Channel7_IRQHandler,
    (uintptr_t)ADC1_2_IRQHandler,
    (uintptr_t)USB_HP_CAN_TX_IRQHandler,
    (uintptr_t)USB_LP_CAN_RX0_IRQHandler,
    (uintptr_t)CAN_RX1_IRQHandler,
    (uintptr_t)CAN_SCE_IRQHandler,
    (uintptr_t)EXTI9_5_IRQHandler,
    (uintptr_t)TIM1_BRK_IRQHandler,
    (uintptr_t)TIM1_UP_IRQHandler,
    (uintptr_t)TIM1_TRG_COM_IRQHandler,
    (uintptr_t)TIM1_CC_IRQHandler,
    (uintptr_t)TIM2_IRQHandler,
    (uintptr_t)TIM3_IRQHandler,
    (uintptr_t)TIM4_IRQHandler,
    (uintptr_t)I2C1_EV_IRQHandler,
    (uintptr_t)I2C1_ER_IRQHandler,
    (uintptr_t)I2C2_EV_IRQHandler,
    (uintptr_t)I2C2_ER_IRQHandler,
    (uintptr_t)SPI1_IRQHandler,
    (uintptr_t)SPI2_IRQHandler,
    (uintptr_t)USART1_IRQHandler,
    (uintptr_t)USART2_IRQHandler,
    (uintptr_t)USART3_IRQHandler,
    (uintptr_t)EXTI15_10_IRQHandler,
    (uintptr_t)RTCAlarm_IRQHandler,
    (uintptr_t)USBWakeUp_IRQHandler
};

void Reset_Handler(void)
{
    uint32_t *source = &_sidata;
    uint32_t *destination = &_sdata;

    while (destination < &_edata)
    {
        *destination++ = *source++;
    }

    for (destination = &_sbss; destination < &_ebss; ++destination)
    {
        *destination = 0u;
    }

    (void)main();
    for (;;)
    {
    }
}

void Default_Handler(void)
{
    for (;;)
    {
    }
}
