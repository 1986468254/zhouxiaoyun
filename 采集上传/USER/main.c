#include "sys.h"
#include "delay.h"
#include "usart.h" 
#include "led.h" 		 	   
#include "adc.h"
#include "Timer.h"
uint16_t Num=0;
uint16_t num=0;
#define CRIT (1.5/3.3*4096)
 int main(void)
 { 
	u16 value;
	int flag =0;
	 int count =0;
	 u16 cmin;
	delay_init();
	 //
	//LED_Init();
	 delay_ms(500);
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	 //uart_init(9600);
	USART2_Configuration();	//初始化串口2，波特率为9600
	delay_ms(500); //延时10ms，修改延时时间可以改变采样速度
	Timer_Init();
	 Adc_Init();

	

	 //delay_ms(500);
	// LED0 = 0;
//	 printf("ok");
	 while(1)
	 { 
		 value = Get_Adc(0);//读取ADC
		 printf("%d\r\n",value);
//		 if (value > CRIT)
//		 {
//			 if(flag==0)
//			 {
//			 count++;
//			 // printf("%d\r\n",count);
//			 flag=1;
//			 }
//			 if(Num==60)
//			 {
//				 cmin=count/30;
//				 printf("心率:");
//				 printf("%d\r\n",cmin);
//				 cmin=0;
//				 count=0;
//				 Num=0;
//			 }
//		 }
//		 else
//		 {
//			 if(flag)
//			 {
//				 flag=0;
//			 }
//		 }

			//delay_ms(10); //延时10ms，修改延时时间可以改变采样速度
	 }
}
 void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		Num ++;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}


