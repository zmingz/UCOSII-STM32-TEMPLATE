#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"	
#include "includes.h"

#include "main.h"

/////////////////////////UCOSII任务堆栈设置///////////////////////////////////
//START 任务
//设置任务优先级
#define START_TASK_PRIO      			10 //开始任务的优先级设置为最低
//设置任务堆栈大小
#define START_STK_SIZE  				64
//创建任务堆栈空间	
OS_STK START_TASK_STK[START_STK_SIZE];
//任务函数接口
void start_task(void *pdata);	
 			   
//LED1任务
//设置任务优先级
#define LED1_TASK_PRIO       			7 
//设置任务堆栈大小
#define LED1_STK_SIZE  		    		64
//创建任务堆栈空间	
OS_STK LED1_TASK_STK[LED1_STK_SIZE];
//任务函数接口
void led1_task(void *pdata);

//LED2任务
//设置任务优先级
#define LED2_TASK_PRIO       			6 
//设置任务堆栈大小
#define LED2_STK_SIZE  					64
//创建任务堆栈空间	
OS_STK LED2_TASK_STK[LED2_STK_SIZE];
//任务函数接口
void led2_task(void *pdata);

void print_init(void);


 int main(void)
 {
	delay_init();	     //延时初始化	  
	NVIC_Configuration(); 	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	print_init();
	LED_Init();		  	 //初始化与LED连接的硬件接口
	
	OSInit();   
	OSTaskCreate(   //创建起始任务
		(void(*)(void *))&start_task,
		(void *)0,
		(OS_STK *)&START_TASK_STK[START_STK_SIZE - 1],
		(INT8U)START_TASK_PRIO
		);
	
	OSStart();
 }


void start_task(void *pdata)
{
    OS_CPU_SR cpu_sr=0;
	pdata = pdata; 
	OSStatInit();					//初始化统计任务.这里会延时1秒钟左右	
 	OS_ENTER_CRITICAL();			//进入临界区(无法被中断打断)    
 	OSTaskCreate(
 	    (void(*)(void *))&led1_task,
		(void *)0,
		(OS_STK*)&LED1_TASK_STK[LED1_STK_SIZE-1],
		(INT8U)LED1_TASK_PRIO
	);
 	OSTaskCreate(
 	    (void(*)(void *))&led2_task,
		(void *)0,
		(OS_STK*)&LED2_TASK_STK[LED2_STK_SIZE-1],
		(INT8U)LED2_TASK_PRIO
	);

#if DEBUG
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	printf("This system is UCOSII example.\n");
	printf("The version is V%d.%d.%d\n", VERSION_H, VERSION_M, VERSION_L);
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
#endif

	OSTaskSuspend(START_TASK_PRIO);	//挂起起始任务.
	OS_EXIT_CRITICAL();				//退出临界区(可以被中断打断)
}


void led1_task(void *pdata)
{	 
	INT8U time = 0;
	while(1)
	{
		time++;

#if DEBUG
		printf("%d:hello world\n", time);
#endif

		LED0=0;
		OSTimeDlyHMSM(0,0,0,80);
		LED0=1;
		OSTimeDlyHMSM(0,0,0,920);
	}
}


void led2_task(void *pdata)
{	  
	while(1)
	{
// 		LED1=0;
// 		OSTimeDlyHMSM(0,0,0,300);
		LED1=1;
		OSTimeDlyHMSM(0,0,0,300);
	}
}



