/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
// Ð?nh nghia c?u trúc d? li?u g?i qua Queue
typedef struct {
  uint8_t  led_index;   // 0: LED1, 1: LED2, 2: LED3
  uint16_t duty_cycle;  // D?i giá tr? t? 0 d?n 1000
} LedMessage_t;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define PWM_MAX               1000  // Tuong ?ng ARR = 999
#define PWM_STEP              100   // Tang/Gi?m 10% m?i l?n nh?n

// Ð?nh nghia nút nh?n tuong ?ng v?i c?u hình GPIO c?a b?n (GPIOB: PB12, PB13, PB14)
#define BTN_MODE_PIN          GPIO_PIN_12
#define BTN_MODE_PORT         GPIOB

#define BTN_UP_PIN            GPIO_PIN_13
#define BTN_UP_PORT           GPIOB

#define BTN_DOWN_PIN          GPIO_PIN_14
#define BTN_DOWN_PORT         GPIOB
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim2;

/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for TaskBtn */
osThreadId_t TaskBtnHandle;
const osThreadAttr_t TaskBtn_attributes = {
  .name = "TaskBtn",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for TaskLED1 */
osThreadId_t TaskLED1Handle;
const osThreadAttr_t TaskLED1_attributes = {
  .name = "TaskLED1",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for TaskLED2 */
osThreadId_t TaskLED2Handle;
const osThreadAttr_t TaskLED2_attributes = {
  .name = "TaskLED2",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for TaskLED3 */
osThreadId_t TaskLED3Handle;
const osThreadAttr_t TaskLED3_attributes = {
  .name = "TaskLED3",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* USER CODE BEGIN PV */
// Queue Handle
osMessageQueueId_t LedQueueHandle;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
void StartDefaultTask(void *argument);
void StartTaskButton(void *argument);
void StartTaskLED(void *argument);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code --------------------------------------------------------- */
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  // Kh?i d?ng 3 kênh PWM c?a TIM2 (PA0, PA1, PA2)
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
  /* USER CODE END 2 */

  /* Init scheduler */
  osKernelInitialize();

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  // Kh?i t?o Queue ch?a t?i da 10 ph?n t? ki?u LedMessage_t
  LedQueueHandle = osMessageQueueNew(10, sizeof(LedMessage_t), NULL);
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of TaskBtn */
  TaskBtnHandle = osThreadNew(StartTaskButton, NULL, &TaskBtn_attributes);

  /* creation of TaskLED1 */
  TaskLED1Handle = osThreadNew(StartTaskLED, (void*) 0, &TaskLED1_attributes);

  /* creation of TaskLED2 */
  TaskLED2Handle = osThreadNew(StartTaskLED, (void*) 1, &TaskLED2_attributes);

  /* creation of TaskLED3 */
  TaskLED3Handle = osThreadNew(StartTaskLED, (void*) 2, &TaskLED3_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

  /* Start scheduler */
  osKernelStart();

  /* We should never get here as control is now taken by the scheduler */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  // C?u hình t?n s? PWM = 1 kHz (SYSCLK 72MHz -> APB1 Timer Clock = 72MHz)
  htim2.Init.Prescaler = 71;                // 72MHz / (71 + 1) = 1MHz
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 999;                  // 1MHz / (999 + 1) = 1kHz PWM
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pins : PB12 PB13 PB14 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN 5 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(100);
  }
  /* USER CODE END 5 */
}

/* USER CODE BEGIN Header_StartTaskButton */
/**
* @brief Function implementing the TaskBtn thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartTaskButton */
void StartTaskButton(void *argument)
{
  /* USER CODE BEGIN StartTaskButton */
  uint8_t selected_led = 0;           // M?c d?nh ch?n LED 1 (index = 0)
  uint16_t led_duty[3] = {0, 0, 0};   // Luu d? sáng hi?n t?i c?a 3 LED

  /* Infinite loop */
  for(;;)
  {
    // 1. Nút PB12: Chuy?n LED (Mode)
    if (HAL_GPIO_ReadPin(BTN_MODE_PORT, BTN_MODE_PIN) == GPIO_PIN_RESET)
    {
      osDelay(20); // Ch?ng n?y phím
      if (HAL_GPIO_ReadPin(BTN_MODE_PORT, BTN_MODE_PIN) == GPIO_PIN_RESET)
      {
        selected_led = (selected_led + 1) % 3; // Chuy?n ch?n: 0 -> 1 -> 2 -> 0
        while (HAL_GPIO_ReadPin(BTN_MODE_PORT, BTN_MODE_PIN) == GPIO_PIN_RESET)
        {
          osDelay(10); // Ch? nh? nút
        }
      }
    }

    // 2. Nút PB13: Tang d? sáng (Up)
    if (HAL_GPIO_ReadPin(BTN_UP_PORT, BTN_UP_PIN) == GPIO_PIN_RESET)
    {
      osDelay(20);
      if (HAL_GPIO_ReadPin(BTN_UP_PORT, BTN_UP_PIN) == GPIO_PIN_RESET)
      {
        if (led_duty[selected_led] + PWM_STEP <= PWM_MAX) {
          led_duty[selected_led] += PWM_STEP;
        } else {
          led_duty[selected_led] = PWM_MAX;
        }

        // Ðóng gói d? li?u g?i qua Queue
        LedMessage_t msg = {
          .led_index = selected_led,
          .duty_cycle = led_duty[selected_led]
        };
        osMessageQueuePut(LedQueueHandle, &msg, 0, 0);

        while (HAL_GPIO_ReadPin(BTN_UP_PORT, BTN_UP_PIN) == GPIO_PIN_RESET)
        {
          osDelay(10);
        }
      }
    }

    // 3. Nút PB14: Gi?m d? sáng (Down)
    if (HAL_GPIO_ReadPin(BTN_DOWN_PORT, BTN_DOWN_PIN) == GPIO_PIN_RESET)
    {
      osDelay(20);
      if (HAL_GPIO_ReadPin(BTN_DOWN_PORT, BTN_DOWN_PIN) == GPIO_PIN_RESET)
      {
        if (led_duty[selected_led] >= PWM_STEP) {
          led_duty[selected_led] -= PWM_STEP;
        } else {
          led_duty[selected_led] = 0;
        }

        // Ðóng gói d? li?u g?i qua Queue
        LedMessage_t msg = {
          .led_index = selected_led,
          .duty_cycle = led_duty[selected_led]
        };
        osMessageQueuePut(LedQueueHandle, &msg, 0, 0);

        while (HAL_GPIO_ReadPin(BTN_DOWN_PORT, BTN_DOWN_PIN) == GPIO_PIN_RESET)
        {
          osDelay(10);
        }
      }
    }

    osDelay(20); // Chu k? quét nút nh?n 20ms
  }
  /* USER CODE END StartTaskButton */
}

/* USER CODE BEGIN Header_StartTaskLED */
/**
* @brief Function implementing the TaskLED1, TaskLED2, TaskLED3 threads.
* @param argument: ID d?i di?n cho t?ng LED (0, 1, ho?c 2)
* @retval None
*/
/* USER CODE END Header_StartTaskLED */
void StartTaskLED(void *argument)
{
  /* USER CODE BEGIN StartTaskLED */
  uint8_t my_led_id = (uint8_t)(uintptr_t)argument;
  LedMessage_t rx_msg;

  /* Infinite loop */
  for(;;)
  {
    // Ð?i nh?n thông di?p t? Queue (Wait Forever)
    if (osMessageQueueGet(LedQueueHandle, &rx_msg, NULL, osWaitForever) == osOK)
    {
      if (rx_msg.led_index == my_led_id)
      {
        // Ðúng ID c?a Task này -> C?p nh?t Duty Cycle cho Chanel tuong ?ng
        switch (my_led_id)
        {
          case 0:
            __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, rx_msg.duty_cycle);
            break;
          case 1:
            __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, rx_msg.duty_cycle);
            break;
          case 2:
            __HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, rx_msg.duty_cycle);
            break;
          default:
            break;
        }
      }
      else
      {
        // Không dúng ID -> Ð?y tr? thông di?p l?i Queue cho Task khác x? lý
        osMessageQueuePut(LedQueueHandle, &rx_msg, 0, 0);
        osDelay(2); // Delay ng?n tránh vòng l?p tranh ch?p Queue
      }
    }
  }
  /* USER CODE END StartTaskLED */
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM1 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */

  /* USER CODE END Callback 0 */
  if (htim->Instance == TIM1)
  {
    HAL_IncTick();
  }
  /* USER CODE BEGIN Callback 1 */

  /* USER CODE END Callback 1 */
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */