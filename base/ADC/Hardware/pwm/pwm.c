

#include "stm32f4xx.h"

/*
定时器12，ch2 用于屏幕背光亮度调节，这里用来演示PWM输出结果
*/
void TIM12_CH2_PWM_Init(u16 arr,u16 psc)
{		 					 
 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12,ENABLE);  	//TIM12时钟使能    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE); //使能PORTB时钟	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15; //GPIOB15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//速度100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
	GPIO_Init(GPIOB,&GPIO_InitStructure); //初始化PA3
 
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource15,GPIO_AF_TIM12); //GPIOB15复用位定时器12

	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseStructure.TIM_Period=arr;   //自动重装载值
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseInit(TIM12,&TIM_TimeBaseStructure);//初始化定时器12

	//初始化TIM14 Channel1 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OCInitStructure.TIM_Pulse=0;
	TIM_OC2Init(TIM12, &TIM_OCInitStructure);  //根据T指定的参数初始化外设TIM12 OC2

	TIM_OC2PreloadConfig(TIM12, TIM_OCPreload_Enable);  //使能TIM12在CCR2上的预装载寄存器
 
  TIM_ARRPreloadConfig(TIM12,ENABLE);//ARPE使能 
	
	TIM_Cmd(TIM12, ENABLE);  //使能TIM12 
 
}

void TIM12_PWM_OUT( u16 pwmvalue )
{
  TIM12->CCR2 = pwmvalue;
}






