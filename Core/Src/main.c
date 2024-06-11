/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
struct
{
    uint32_t val1;
    uint16_t num1;
    uint16_t siz1;
    
    uint32_t val2;
    uint16_t num2;
    uint16_t siz2; 
    
    uint32_t val3;
    uint16_t num3;
    uint16_t siz3;
    
    uint32_t val4;
    uint16_t num4;
    uint16_t siz4;
    
    uint32_t val5;
    uint16_t num5;
    uint16_t siz5;
    
    uint32_t val6;
    uint16_t num6;
    uint16_t siz6;
    
    uint32_t val7;
    uint16_t num7;
    uint16_t siz7;
    
    uint32_t val8;
    uint16_t num8;
    uint16_t siz8;
    
    uint32_t val9;
    uint16_t num9;
    uint16_t siz9;
    
    uint32_t val10;
    uint16_t num10;
    uint16_t siz10;
    
    uint32_t val11;
    uint16_t num11;
    uint16_t siz11;
    
    uint32_t val12;
    uint16_t num12;
    uint16_t siz12;   
} test_struct;//структура для записи данных  в ячейку  памяти
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define flash_addr   0x0801F800//адрес 126 страницы
//#define FLASH_TYPEPROGRAM_BYTE             0x01  /**/
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
volatile uint8_t UartReady=RESET;//флаг для чтения;
char readBuf[40];//буфер, где будут помещаться принятые байты
char writeBuf[120];//буфер для записи в терминал
uint8_t rxbyte;//переменная для приёма по одному байту
uint8_t i=0;//инкремент для readBuf 
const char str_array[13][20]={
		"SPD",
		"LNOPEN",
		"LNHLOPEN",
        "CURERRLOCK1",
        "CURERRLOCK2", 
        "CURERRDRIVE1", 
        "CURERRDRIVE2", 
        "CURERRDRIVE3", 
        "CURERRDRIVE4", 
        "CURERRTIME",
        "STOTIMELOCK", 
        "STOTIMEDRIVE",
        "SAVEFLASH"
    };//словарь
    /*char des_com[12][80]={
    "Connection speed",
    "Full opening distance",
    "Incomplete opening distance",
    "Emergency current value of the lock line 1",
    "Emergency current value of the lock line 2",
    "Emergency current value of the window 1 drive circuit line",
    "Emergency current value of the window 2 drive circuit line",
    "Emergency current value of the window 3 drive circuit line",
    "Emergency current value of the window 4 drive circuit line",
    "The holding time of the emergency current value of the drive circuit line",
    "The time spent in the lock stop",
    "The time spent in the stop of the chains"   
    };//описание команд*/
//char *p,*n,*e,ch;
//int val_array[12]={10,20,30,40,50,60,70,80,90,100,110,120};

//int l;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
//char* readUserInput(void);
int check (void);

void SPD(void);
void LNOPEN(void);
void LNHLOPEN(void);
void CURERRLOCK1(void);
void CURERRLOCK2(void);
void CURERRDRIVE1(void);
void CURERRDRIVE2(void);
void CURERRDRIVE3(void);
void CURERRDRIVE4(void);
void CURERRTIME(void);
void STOTIMELOCK(void);
void STOTIMEDRIVE(void);
void SAVEFLASH(void);

uint8_t writeFlash (uint32_t);
uint32_t readFlash (uint32_t);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  test_struct.val1=10;
  test_struct.val2=20;
  test_struct.val3=30;
  test_struct.val4=40;
  test_struct.val5=50;
  test_struct.val6=60;
  test_struct.val7=70;
  test_struct.val8=80;
  test_struct.val9=90;
  test_struct.val10=100;
  test_struct.val11=110;
  test_struct.val12=120;
      
  test_struct.num1=1;
  test_struct.num2=2;
  test_struct.num3=3;
  test_struct.num4=4;
  test_struct.num5=5;
  test_struct.num6=6;
  test_struct.num7=7;
  test_struct.num8=8;
  test_struct.num9=9;
  test_struct.num10=10;
  test_struct.num11=11;
  test_struct.num12=12;
  
  test_struct.siz1=sizeof(test_struct.val1);
  test_struct.siz2=sizeof(test_struct.val2);
  test_struct.siz3=sizeof(test_struct.val3);
  test_struct.siz4=sizeof(test_struct.val4);
  test_struct.siz5=sizeof(test_struct.val5);
  test_struct.siz6=sizeof(test_struct.val6);
  test_struct.siz7=sizeof(test_struct.val7);
  test_struct.siz8=sizeof(test_struct.val8);
  test_struct.siz9=sizeof(test_struct.val9);
  test_struct.siz10=sizeof(test_struct.val10);
  test_struct.siz11=sizeof(test_struct.val11);
  test_struct.siz12=sizeof(test_struct.val12);
  
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
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  /* Разрешение прерываний от USART1 */
   HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
   HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE END 2 */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  //UartReady=RESET;
  HAL_UART_Receive_IT(&huart1, &rxbyte, 1);//вызов приёма, подготовка к приёму
  while (1)
  {
       if (UartReady==SET)
       {
           switch (check())
           {
               case 0:
                       //sprintf(writeBuf, "%s", readBuf);//передаём в массив writeBuf
                       SPD();//скорость соединения
                       break;
               case 1:  
                       //sprintf(writeBuf, "%s", readBuf);//передаём в массив writeBuf
                       LNOPEN();//расстояние полного открытия
                       break;
               case 2:
                       //sprintf(writeBuf, "%s", readBuf);//передаём в массив writeBuf
                       LNHLOPEN();//расстояние неполного открытия
                       break;
               case 3:
                       //sprintf(writeBuf, "%s", readBuf);//передаём в массив writeBuf
                       CURERRLOCK1();//аварийное значение токо линии замков 1
                       break;
               case 4:
                       //sprintf(writeBuf, "%s", readBuf);//передаём в массив writeBuf
                       CURERRLOCK2();//аварийное значение токо линии замков 2
                       break;                 
               case 5:
                       //sprintf(writeBuf, "%s", readBuf);//передаём в массив writeBuf
                       CURERRDRIVE1();//аварийное значение  тока линии цепей привода окна 1 
                       break;
               case 6:  
                       //sprintf(writeBuf, "%s", readBuf);//передаём в массив writeBuf
                       CURERRDRIVE2();//аварийное значение  тока линии цепей привода окна 2 
                       break;
               case 7:  
                       //sprintf(writeBuf, "%s", readBuf);//передаём в массив writeBuf
                       CURERRDRIVE3();//аварийное значение  тока линии цепей привода окна 3 
                       break;
               case 8:  
                        //sprintf(writeBuf, "%s", readBuf);//передаём в массив writeBuf
                        CURERRDRIVE4();//аварийное значение  тока линии цепей привода окна 4 
                        break;
               case 9:  
                        //sprintf(writeBuf, "%s", readBuf);//передаём в массив writeBuf
                        CURERRTIME();//время удержания аварийного значения  тока линии цепей 
                        break;
               case 10:  
                        //sprintf(writeBuf, "%s", readBuf);//передаём в массив writeBuf
                        STOTIMELOCK();//время нахождения в упоре замков 
                        break;
               case 11:  
                        //sprintf(writeBuf, "%s", readBuf);//передаём в массив writeBuf
                        STOTIMEDRIVE();//время нахождения в упоре цепей
                        break;
               case 12:  
                        SAVEFLASH();//сохранить всё во flash
                        //sprintf(writeBuf, "%s", readBuf);//передаём в массив writeBuf
                        break;
               default: 
                        sprintf(writeBuf, "%s", "Default\r\n");//передаём в массив writeBuf
               break;
               
           }
           /*HAL_UART_Transmit_IT(&huart1, (uint8_t*)writeBuf, strlen(writeBuf));
           while (HAL_UART_GetState(&huart1) == HAL_UART_STATE_BUSY_TX ||
            HAL_UART_GetState(&huart1) == HAL_UART_STATE_BUSY_TX_RX);*/
           UartReady=RESET;//сбрасываем флаг 
           HAL_UART_Transmit(&huart1, (uint8_t*)writeBuf, strlen(writeBuf), HAL_MAX_DELAY);
           HAL_UART_Receive_IT(&huart1, &rxbyte, 1);//вызов приёма, подготовка к приёму
       }
       
      /*
      if (UartReady==SET)//если флаг установлен
      {
          if(readBuf[0]=='A' && readBuf[1]=='T' && readBuf[2]=='+')
          {
                      for(int j=0;j<12;j++)
                      {
                        if((strstr(readBuf,str_array[j]))!=NULL)
                        {
                      //strstr(readBuf,str_array[0]);
                            sprintf(writeBuf, "%s", readBuf);//передаём в массив writeBuf
                            HAL_UART_Transmit(&huart1, (uint8_t*)writeBuf, strlen(writeBuf), HAL_MAX_DELAY);
                        }                        
                      }
          }
          else
          {
              sprintf(writeBuf, "%s", "Error\r\n");//передаём в массив writeBuf
              HAL_UART_Transmit(&huart1, (uint8_t*)writeBuf, strlen(writeBuf), HAL_MAX_DELAY);
          }
          UartReady=RESET;//сбрасываем флаг 
          HAL_UART_Receive_IT(&huart1, &rxbyte, 1);//вызов приёма, подготовка к приёму
      }
      
      */
      
    /* USER CODE END WHILE */
    
	//opt=readUserInput();
    //if(opt>0)
    //{
        //sprintf(msg, "%d", opt);
       // sprintf(writeBuf, "%s", opt);
        //UartReady = RESET;
       // HAL_UART_Transmit(&huart1, (uint8_t*)writeBuf, strlen(writeBuf), HAL_MAX_DELAY);
    //}
    /* USER CODE BEGIN 3 */
	
  /* USER CODE END 3 */
  }
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}
/* USER CODE BEGIN 4 */
int check (void)
{
    if(readBuf[0] !='A' || readBuf[1]!='T' || readBuf[2]!='+') return (-1);
    int s=sizeof(str_array)/sizeof(str_array[12]);/*РАЗМЕР ДВУМЕРНОГО МАССИВА*/
    for(int j=0;j<s;j++)
    {
        if((strstr(readBuf,str_array[j]))!=NULL)
            return (j);
    }
    return (-1);
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *UartHandle) 
{
/* Установить флаг передачи: передача завершена */
   // UartReady = SET;
    readBuf[i++]=rxbyte;//принимаем побайтно
    if (i >= sizeof(readBuf)) //если буфер переполнился 
        i=0;//сбрасываем счётчик
    if (rxbyte=='\n') //если принятый байт символ перевода каретки
    {
        readBuf[i++] = '\0';//добавляем символ конца строки
        UartReady = SET; //устанавливаем флаг
        i=0;//сбрасываем счётчик        
        //HAL_UART_AbortReceive(&huart1);//прекращение приёма из UART
    }
    else 
        HAL_UART_Receive_IT(&huart1, &rxbyte, 1);//вызов приёма, подготовка к приёму
}
/*char* readUserInput(void) 
{
    //int8_t retVal = -1;
    if(UartReady == SET) 
    {
        UartReady = RESET;    
        //while(i<sizeof(readBuf))
        //{
            //p=&readBuf[i];
            //HAL_UART_Receive_IT(&huart1, (uint8_t*)p, 1);     
            //if(readBuf[0]=='A')
                //if(readBuf[1]=='T')
                    //if(readBuf[2]=='+')
                        //break;
            //return p;
            //if(p=='OD') 
            //i++;           
        //}
    }
  //retVal = atoi(readBuf);//функция atoi преобразует строковые  числа в целые
    return 0;
}*/
void SPD()
{
//if(readBuf[6]!='=' && readBuf[6]!='?')
//if(readBuf[6]!='?')
 //sprintf(writeBuf, "%s\r\n", "Error");//передаём в массив writeBuf
 /*p=strchr(readBuf,'?');
e=strchr(readBuf,'=');
n=strchr(readBuf,'\0');
if((n-p)==3)//?
sprintf(writeBuf, "%s\r\n", "Incomplete opening distance");
//else
//sprintf(writeBuf, "%s\r\n", "Error");
if((n-e)==4)//=
{
if((n-p)==3)//?
printf(writeBuf, "%s %d\r\n","LNHLOPEN:",val_array[2]);//передаём в массив writeBuf
}
if((n-e)==4||(n-e)==5||(n-e)==6)//=
{
l=strlen(readBuf);
if(isdigit(readBuf[l-4]))
{
sscanf(&readBuf[l-4],"%d",&val_array[2]);
sprintf(writeBuf, "%s\r\n", "Ok");
} 
}*/
    if (readBuf[6]=='?' && readBuf[7]=='\r')
        sprintf(writeBuf, "%s\r\n", "Connection speed");//Выдать описание команды
    else
        sprintf(writeBuf, "%s\r\n", "Error");
    if (readBuf[6]=='=')//=
    {
        if (readBuf[7]=='?')//=?
            sprintf(writeBuf, "%s %d\r\n", "SPD:", test_struct.val1); //выдать текущее значение параметра
        else
        {
            if(isdigit(readBuf[7]))
            {
                sscanf(&readBuf[7],"%d",&test_struct.val1);//присвоить новое значение
                //test_struct.var3=sizeof(test_struct.var2[0]);
                //writeFlash(flash_addr);
                sprintf(writeBuf, "%s\r\n","Ok");
            }
            else
                sprintf(writeBuf, "%s\r\n", "Error");
         }
    }
}
void LNOPEN()
{
    if(readBuf[9]=='?'&& readBuf[10]=='\r')
        sprintf(writeBuf, "%s\r\n", "Full opening distance");//Выдать описание команды
    else
        sprintf(writeBuf, "%s\r\n", "Error");
    if (readBuf[9]=='=') //=
    {
        if (readBuf[10]=='?') //=?
            sprintf(writeBuf, "%s %d\r\n","LNOPEN:",test_struct.val2);//выдать текущее значение параметра
        else
        {
            if(isdigit(readBuf[10]))
            {
                sscanf(&readBuf[10],"%d",&test_struct.val2);//присвоить новое значение
                //test_struct.var3=sizeof(test_struct.var2[1]);
                //writeFlash(flash_addr+test_struct.var3);
                sprintf(writeBuf, "%s\r\n", "Ok");
            }
            else
                sprintf(writeBuf, "%s\r\n", "Error");
        }
    }
}
void LNHLOPEN()
{
    if(readBuf[11]=='?'&& readBuf[12]=='\r')//Выдать описание команды
        sprintf(writeBuf, "%s\r\n", "Incomplete opening distance");
    else
        sprintf(writeBuf, "%s\r\n", "Error");
    if (readBuf[11]=='=')//=
    {
        if (readBuf[12]=='?')//=?
            sprintf(writeBuf, "%s %d\r\n","LNHLOPEN:",test_struct.val3);//выдать текущее значение параметра
        else
        {
            if(isdigit(readBuf[12]))
            {
                sscanf(&readBuf[12],"%d",&test_struct.val3); //присвоить новое значение
                //test_struct.var3=sizeof(test_struct.var2[2]);
                sprintf(writeBuf, "%s\r\n", "Ok");
            }
            else
                sprintf(writeBuf, "%s\r\n", "Error");
        }
    }
}
void CURERRLOCK1()
{
    if(readBuf[14]=='?'&& readBuf[15]=='\r')//Выдать описание команды
        sprintf(writeBuf, "%s\r\n", "Emergency current value of the lock line 1");
    else
        sprintf(writeBuf, "%s\r\n", "Error");
    if (readBuf[14]=='=')//=
    {
        if (readBuf[15]=='?')//=?
            sprintf(writeBuf, "%s %d\r\n","CURERRLOCK1:",test_struct.val4);//выдать текущее значение параметра
        else
        {
            if(isdigit(readBuf[15]))
            {
                sscanf(&readBuf[15],"%d",&test_struct.val4);//присвоить новое значение
                //test_struct.var3=sizeof(test_struct.var2[3]);
                sprintf(writeBuf, "%s\r\n", "Ok");
            }
            else
                sprintf(writeBuf, "%s\r\n", "Error");
        }
    }
}
void CURERRLOCK2()
{
    if(readBuf[14]=='?'&& readBuf[15]=='\r')//Выдать описание команды
        sprintf(writeBuf, "%s\r\n", "Emergency current value of the lock line 2");
    else
        sprintf(writeBuf, "%s\r\n", "Error");
    if (readBuf[14]=='=')//=
    {
        if (readBuf[15]=='?')//=?
            sprintf(writeBuf, "%s %d\r\n","CURERRLOCK2:",test_struct.val5);//выдать текущее значение параметра
        else
        {
            if(isdigit(readBuf[15]))
            {
                sscanf(&readBuf[15],"%d",&test_struct.val5);//присвоить новое значение
                //test_struct.var3=sizeof(test_struct.var2[4]);
                sprintf(writeBuf, "%s\r\n", "Ok");
            }
            else
                printf(writeBuf, "%s\r\n", "Error");
        }
    }  
}
void CURERRDRIVE1()
{
    if(readBuf[15]=='?'&& readBuf[16]=='\r')//Выдать описание команды
        sprintf(writeBuf, "%s\r\n", "Emergency current value of the window 1 drive circuit line");
    else
        sprintf(writeBuf, "%s\r\n", "Error");
    if (readBuf[15]=='=')//=
    {
        if (readBuf[16]=='?')//=?
            sprintf(writeBuf, "%s %d\r\n","CURERRDRIVE1:",test_struct.val6);//выдать текущее значение параметра
        else
        {       
            if(isdigit(readBuf[16]))
            {
                sscanf(&readBuf[16],"%d",&test_struct.val6);//присвоить новое значение
                //test_struct.var3=sizeof(test_struct.var2[4]);                
                sprintf(writeBuf, "%s\r\n", "Ok");
            }
            else
                sprintf(writeBuf, "%s\r\n", "Error");
         }
    }    
}
void CURERRDRIVE2()
{
    if(readBuf[15]=='?'&& readBuf[16]=='\r')//Выдать описание команды
        sprintf(writeBuf, "%s\r\n", "Emergency current value of the window 2 drive circuit line");
    else
        sprintf(writeBuf, "%s\r\n", "Error");
    if (readBuf[15]=='=')//=
    {
        if (readBuf[16]=='?')//=?
            sprintf(writeBuf, "%s %d\r\n","CURERRDRIVE2:",test_struct.val7);//выдать текущее значение параметра
        else
        {
            if(isdigit(readBuf[16]))
            {
                sscanf(&readBuf[16],"%d",&test_struct.val7);//присвоить новое значение                                
                sprintf(writeBuf, "%s\r\n", "Ok");
            }
            else
                sprintf(writeBuf, "%s\r\n", "Error");
        }
    } 
}
void CURERRDRIVE3()
{
    if(readBuf[15]=='?'&& readBuf[16]=='\r')//Выдать описание команды
        sprintf(writeBuf, "%s\r\n", "Emergency current value of the window 3 drive circuit line");
    else
        sprintf(writeBuf, "%s\r\n", "Error");
    if (readBuf[15]=='=')//=
    {
        if (readBuf[16]=='?')//=?
            sprintf(writeBuf, "%s %d\r\n","CURERRDRIVE3:",test_struct.val8);//выдать текущее значение параметра
        else
        {
            if(isdigit(readBuf[16]))
            {
                sscanf(&readBuf[16],"%d",&test_struct.val8);//присвоить новое значение
                sprintf(writeBuf, "%s\r\n", "Ok");
            }
            else
                sprintf(writeBuf, "%s\r\n", "Error");
        }
    }
}
void CURERRDRIVE4()
{
    if(readBuf[15]=='?'&& readBuf[16]=='\r')//Выдать описание команды
        sprintf(writeBuf, "%s\r\n", "Emergency current value of the window 4 drive circuit line");
    else
        sprintf(writeBuf, "%s\r\n", "Error");
    if (readBuf[15]=='=')//=
    {
        if (readBuf[16]=='?')//=?
            sprintf(writeBuf, "%s %d\r\n","CURERRDRIVE4:",test_struct.val9);//выдать текущее значение параметра
        else
        {
            if(isdigit(readBuf[16]))
            {
                sscanf(&readBuf[16],"%d",&test_struct.val9);//присвоить новое значение
                sprintf(writeBuf, "%s\r\n", "Ok");
            }
            else
                sprintf(writeBuf, "%s\r\n", "Error");
        }
    }
}
void CURERRTIME()
{
    if(readBuf[13]=='?'&& readBuf[14]=='\r')//Выдать описание команды
        sprintf(writeBuf, "%s\r\n", "The holding time of the emergency current value of the drive circuit line");
    else
        sprintf(writeBuf, "%s\r\n", "Error");
    if (readBuf[13]=='=')//=
    {
        if (readBuf[14]=='?')//=?
            sprintf(writeBuf, "%s %d\r\n","CURERRTIME:",test_struct.val10);//выдать текущее значение параметра
        else
        {
            if(isdigit(readBuf[14]))
            {
                sscanf(&readBuf[14],"%d",&test_struct.val10);//присвоить новое значение                                
                sprintf(writeBuf, "%s\r\n", "Ok");
            }
            else
                sprintf(writeBuf, "%s\r\n", "Error");
        }
    }
}
void STOTIMELOCK()
{
    if(readBuf[14]=='?'&& readBuf[15]=='\r')//Выдать описание команды
        sprintf(writeBuf, "%s\r\n", "The time spent in the lock stop");
    else
        sprintf(writeBuf, "%s\r\n", "Error");
    if (readBuf[14]=='=')//=
    {
        if (readBuf[15]=='?')//=?
            sprintf(writeBuf, "%s %d\r\n","STOTIMELOCK:",test_struct.val11);//выдать текущее значение параметра
        else
        {
            if(isdigit(readBuf[15]))
            { 
                sscanf(&readBuf[15],"%d",&test_struct.val11);//присвоить новое значение                                
                sprintf(writeBuf, "%s\r\n", "Ok");
            }
            else
                sprintf(writeBuf, "%s\r\n", "Error");
        }
    }
}
void STOTIMEDRIVE()
{
    if(readBuf[15]=='?'&& readBuf[16]=='\r')//Выдать описание команды
        sprintf(writeBuf, "%s\r\n", "The time spent in the stop of the chains");
    else
        sprintf(writeBuf, "%s\r\n", "Error");
    if (readBuf[15]=='=')//=
    {
        if (readBuf[16]=='?')//=?
            sprintf(writeBuf, "%s %d\r\n","STOTIMEDRIVE:",test_struct.val12);//выдать текущее значение параметра
        else
        {
            if(isdigit(readBuf[16]))
            {
                sscanf(&readBuf[16],"%d",&test_struct.val12);//присвоить новое значение                                
                sprintf(writeBuf, "%s\r\n", "Ok");
            }
            else
                sprintf(writeBuf, "%s\r\n", "Error");
        }
    }
}
void SAVEFLASH()
{
    if (readBuf[11]=='H' && readBuf[12]=='\r')
    {
        writeFlash(flash_addr);
        //writeFlash(0x0801F845);
        sprintf(writeBuf, "%s\r\n", "Save!");//Выдать описание команды
    }
    else
        sprintf(writeBuf, "%s\r\n", "Error");
    
}
uint8_t writeFlash (uint32_t addr)
{
	HAL_StatusTypeDef status;
	uint32_t structureSize = sizeof(test_struct);          // замеряем размер структуры
	FLASH_EraseInitTypeDef FlashErase;                     // переменная для структуры, которая выполняет функцию стирания страницы
	uint32_t pageError = 0;                                // переменная для записи информации об ошибках в процессе стирания

	//__disable_irq();                                     // запрещаем прерывания
	HAL_FLASH_Unlock();									   //разблокировка FLASH
	FlashErase.TypeErase = FLASH_TYPEERASE_PAGES;          // стирать постранично(1кбайт)
	FlashErase.PageAddress = addr;                         // адрес страницы для стирания
	//FlashErase.NbPages = structureSize / 1024 + 1;         // считаем количество страниц, чтобы наш массив поместился
    FlashErase.NbPages=1;
	if (HAL_FLASHEx_Erase(&FlashErase, &pageError) != HAL_OK)// вызов функции стирания
	{
		HAL_FLASH_Lock();                                  // если не смог стереть, то закрыть память и вернуть ошибку
		return HAL_ERROR;
	}

    uint32_t *dataPtr = (uint32_t *)&test_struct;          // создаем указатель на нашу структуру и записываем ее кусочками по 32 бита
	for (int i = 0; i < structureSize / 4; i++)            // 4 байта = 32 бита
    //for (int i = 0; i < structureSize; i++)            
    {
		status += HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, addr, dataPtr[i]);
        addr += 4;                                         // сдвигаем адрес на 4 байта
        //status += HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, addr, dataPtr[i]);//не работает
        //addr ++;                                         // побайтово
    }
	//__enable_irq();                                      // включаем прерывания обратно
	HAL_FLASH_Lock();
	return status;
}
uint32_t readFlash (uint32_t addr)
{
	uint32_t structureSize = sizeof(test_struct);
	uint32_t *dataPtr = (uint32_t *)&test_struct;
	for (int i = 0; i < structureSize / 4; i++)
	{
		dataPtr[i] = *(__IO uint32_t*)addr;
		addr += 4;
	}
}
/* USER CODE END 4 */
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

#ifdef  USE_FULL_ASSERT
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
