/* MAIN.C file
 * 
 * Copyright (c) 2002-2005 STMicroelectronics
 */
#include "hand_tble.h"	//告诉 C 编译器在实际编译之前要包含 hand_tble.h 文件。
//#include "main_h.h"
//

///////////////////////////////////////
unsigned char sys_step = 0;	//sys_step = 0  unsigned char 为1个字节
///////////////////////////////////////////////
//unsigned char xi=0,xk=0;
//void uart2_send_data(void);
void Init_UART2(void);
void data_load(void);
//void TM3_INI(void);

////////////////////////////////////////////////////////////////
//这些函数调用的目的是在程序开始执行时，对系统的各个部分进行适当的初始化
//以确保它们处于合适的状态，以便程序能够正常运行并进行后续的操作。
main()    //这里是程序主函数，程序的入口，程序从这里开始执行。
{
 	DI();    //__asm("sim");  内联汇编语句，表示代码中插入汇编指令“sim”
	WDT_INI();    //卡门狗定时器watchdog Timer
	RAM_INI();    //RAM初始化随机存取储存 Random Access Memory
	OPTIONSET_INI();	//寄存器初始化 Option Register
	OSC_INI();     //初始化振荡器 Oscillator
	IO_INI();    //初始化io端口
	TM1_INI();   //初始化定时器
	TM2_INI();
	//TM3_INI(); // MID_MOTOR
	AD_INI();    //初始化数字转化器 Analog-to-Digital Converter ADC
//	CLP_ON();			//打开下三桥电源
	EI();    //__asm("rim"); 内联汇编语句，表示代码中插入汇编指令“rim”
	Init_UART2();   //用于初始化UART2（通用异步收发器）。
	data_load();    //可能用于加载数据
	//y42  具体什么意思不太懂
	current_s = (user_Prdata.byte.current_adj >> 1) + (user_Prdata.byte.current_adj >> 5);    //在二进制中右移1位+右移5位 user Prdata用户数据结构 byte变量 voltage adj 电压调整值
	current_s1 = (user_Prdata.byte.current_adj >> 1) + (user_Prdata.byte.current_adj >> 3);   //
	current_s2 = (user_Prdata.byte.current_adj >> 1) + (user_Prdata.byte.current_adj >> 2);
	while(1) //进入无线循环
	{

		_asm("nop");
		
		_asm("nop");
	}
}

void data_load(void)    //定义了一个名为data_load的函数
{
	voltage_count = 30；    //电压计数 电压值为30
	voltage1 = user_Prdata.byte.voltage_adj;    //用户数据字节电压调整值
	voltage2 = voltage1;     //电压值2等于电压值1
	
	voltage_average_sum = 0;    //电压_平均数_总和
	voltage_average_av = 0;    //电压_平均数_
	voltage_average_count = 0;   //电压_平均_计数
	
	current_cmd_protect_average= 280;    //当前_cmd_保护_平均数 可能用于保护电流控制的参数或阀值
	speed_bike = 900;    //转速或者是什么??
	speed_bike_temp = 0x707;     //速度-自行车-温度 0x707是十六进制转换为10进制1807
	jp_number = 100;    //？？？这是啥？
	
	//limit_speed_hall = 4;// 25KM LIMIT 
	limit_speed_hall_1 = 97;//109;//118 * 28 / 25;//limit_speed_number//冷万后注释：霍尔限速97
	//limit_speed_hall_1 = motor_model_rx * wheel_number / limit_speed_number;//limit_speed_hall_1 = 6;//30;//(limit_speed_hall * 10) >> 3;//20
//limit_speed_hall_2 = (limit_speed_hall * 6) >> 3;//27
	//limit_speed_hall_3 = (limit_speed_hall * 6 ) >> 3;//27
	current_ph_zero = 0;    //当前ph零点 猜测是电流相位（phase）零点
	run_mode = 0;    //运行模式
	lamp_old_flag = 0;    //灯-旧-旗帜 猜测用来表示灯的状态
	lamp_onoff_count = 0;    //灯-开关-计数 猜测用来记录灯的开关次数 来记录灯的状态
}

void OSC_INI(void)  //这段代码是对系统时钟进行初始化设置
{		//int osc 16mhz
	CLK_CKDIVR = 0x00;			//FMAST = 16MHZ,FCPU = 16MHZ //冷：0x00十六进制表示0，这句的意思是将主时钟频率设置为16MHZ。这里可以查一下技术手册看看是否会影响噪音。
	
	CLK_ICKR |= 0x01;			//使能LRC HRC//16mhz内部时钟    //冷：启用内部时钟源
	CLK_ICKR &= 0xF7;			//冷：
	
	while((CLK_ICKR & 0xFD) == 0);//等待 HRC RADY
	
	if(CLK_CMSR != HSI)
		CLK_SWR = HSI;			//使用内部高速时钟，默认状态
	
	CLK_SWCR |= 0x02;
	
	CLK_PCKENR2 = 0x00;			//关闭外设时钟
	CLK_PCKENR1 = 0x08;			//关闭外设时钟	//uart 
	////**********************//////
	
	CLK_CKDIVR = 0x00;			//16mhz内部时钟  
	CLK_SWIMCCR = 0x00;			//SWIM _CLK  //冷：接口的时钟频率
	
	CLK_CSSR |= 0x01;			//启动时钟安全系统	
}
///////////////////////////////////////////////
///////////////////////////////////////////////
void IO_INI(void)           //冷：硬件IO口的初始化（Input/Output）
{
#ifdef   S58
	PA_ODR |= 0x00;			//0~7	
	PA_DDR |= 0x20;			//输入口
	PA_CR1 |= 0xFF;			//启用内部上啦
	PA_CR2 |= 0x20;			//输入模式是禁止外部中断，
	
	PB_ODR |= 0x00;//0x07;//0x00;//	//0X00		//0~7		/PWM下桥
	PB_DDR |= 0x07;			//
	PB_CR1 |= 0x0F;			//
	PB_CR2 |= 0x0F;			//
	
	PC_ODR |= 0x00;			//0~7		/PWM上桥
	PC_DDR |= 0x1E;			//
	PC_CR1 |= 0xFF;			//
	PC_CR2 |= 0x1E;			//	
	
	PD_ODR |= 0x00;			//0~7	
	PD_DDR |= 0x25;			//
	PD_CR1 |= 0xFF;			//
	PD_CR2 |= 0x00;			//	
	
	PE_ODR |= 0x00;			//0~7	
	PE_DDR |= 0x00;			//
	PE_CR1 |= 0xFF;			//
	PE_CR2 |= 0x00;			//		
	
	PG_ODR |= 0x00;			//0~7	
	PG_DDR |= 0x00;			//
	PG_CR1 |= 0xFF;			//
	PG_CR2 |= 0x01;			//
#endif
}
//////////////////////////////////


////////////////////////////////////////////////////////////////////////////
void WDT_INI(void)		//看门狗初始化
{
	IWDG_KR = 0x55;		//开锁
	IWDG_PR = 0x03;		//看门狗分频  64K/32 =  2K = 500US    4,8,16,32,64,128,256,
	IWDG_RLR = 20;		//20*500us = 10ms
	IWDG_KR = 0xAA;		//上锁
	IWDG_KR = 0xCC;		//启动看门狗
}


////////////////////////////////////////////////////////////////////////////
void SPI_ini(void)		//冷：初始化SPI（Serial Peripheral Interface）接口
{
	CLK_PCKENR1 |= 0x02;				//使能SPI时钟 //冷：将对应的第二位的位设置为1，以使能SPI的时钟。这样可以确保SPI接口的时钟被使能，以便进行数据传输和通信。
	

	
	
	
}

////////////////////////////////////////////////////////////////////////////
void sci_ini(void)
{
	CLK_PCKENR1 |= 0x04;			//使能uart时钟 //冷：将对应的第四位的位设置为1，以使能UART的时钟。这样可以确保UART接口的时钟被使能，以便进行串行通信。
	
	
	
	
	
	
	
}
////////////////////////////////////////////////\
//PWM初始化，16k，分辨率500
//冷: 
//
//
////////////////////////////////////////////////
void TM1_INI(void)
{
	CLK_PCKENR1 |= 0x80;		//使能TIM1时钟
	
	TIM1_OISR = 0x00;				//
	TIM1_PSCRH  = 0x00;   
	TIM1_PSCRL  = 0x01;   

	TIM1_ARRH   = 0x01;   
	TIM1_ARRL   = 0x00;
	TIM1_RCR    = 0x01;   		//03 8k   01 16k

	TIM1_CCR1H = (u8)(500 >> 8);
	TIM1_CCR1L = (u8)500;
	
	TIM1_CCR2H = (u8)(500 >> 8);
	TIM1_CCR2L = (u8)500;
	
	TIM1_CCR3H = (u8)(500 >> 8);
	TIM1_CCR3L = (u8)500;
	
	TIM1_CCR4H  = 0x00;
	TIM1_CCR4L  = 0x00;
	
	SVPWM_PH();
	TIM1_EGR |= 0x20;					//刷新PWM	

	TIM1_IER    = 0x81;   				//启动break and updata IE	
	
#ifdef LP_PWM	
	TIM1_DTR = 0x5f;	//0x85					//8*FTIM = 1us 死区时间//6us
#else
		TIM1_DTR = 0x21;//39;						//8*FTIM = 1us 死区时间
#endif
	//TIM1_CR2   = 0x21;	
	TIM1_CR2 = 0x21;					//更新事件被选为触发输入
	
	TIM1_BKR = 0x92; 				//b2
	
	TIM1_CR1    = 0xA5; 				//中间对齐模式，向下计数时触发中断。
	TIM1_CCER2 = ((TIM1_CCER2 & 0x1f) | 0x10);
	TIM1_CCMR4 = PWM_MODE1;
	PWM_ALL_OFF();
	TIM1_EGR   |= 0x01;
}
////////////////////////////////////////////////////////////////////////
void NOHALL_TIM1(void)
{
	CLK_PCKENR1 |= 0x80;		//使能TIM1时钟
	TIM1_OISR = 0x00;				//
	TIM1_PSCRH  = 0x00;   
	TIM1_PSCRL  = 0x01;   
	TIM1_ARRH   = 0x01; 
	TIM1_ARRL   = 0x00;
	TIM1_RCR    = 0x01;   		//03 8k   01 16k 
	TIM1_CCMR1 = PWM_HOLD_OFF;   
	TIM1_CCMR2 = PWM_HOLD_OFF;   
	TIM1_CCMR3 = PWM_HOLD_OFF; 
	TIM1_CCMR4 = PWM_HOLD_OFF;		
	TIM1_CCER1 = PWM_ALLON; 			
	TIM1_CCER2 = (PWM_ALLON) & 0xff;			
	TIM1_CCR1H  = 0x00;    
	TIM1_CCR1L  = 0x00;
	TIM1_CCR2H  = 0x00;   
	TIM1_CCR2L  = 0x00;
	TIM1_CCR3H  = 0x00;   
	TIM1_CCR3L  = 0x00;
	TIM1_CCR4H  = 0x00;
	TIM1_CCR4L  = 0x00;
	TIM1_IER    = 0x81;   				//启动break and updata IE	
	TIM1_DTR = 0;
	TIM1_CR2   = 0x21;					//更新事件被选为触发输入
	TIM1_BKR    = 0x92; 				//b2
	TIM1_CR1    = 0xA5; 				//中间对齐模式，向下计数时触发中断。
	PWM_ALL_OFF();
	TIM1_EGR   |= 0x01;
}
//////////////////////////////////////////////////////////////////////////////
void TM2_INI(void)
{
	CLK_PCKENR1 |= 0x20;		//使能TIM2时钟
	
	TIM2_CNTRH = 0x00; //TIM2计数器高8位(TIM1_CNTRH)
	TIM2_CNTRL = 0x00;
	
	TIM2_SR1 &= 0x00;  //状态寄存器1
	TIM2_SR2 &= 0x00;
	
	TIM2_PSCR = 0x08;  //time2两分频   2
	
	TIM2_CCMR1 = 0x01;   
	TIM2_CCMR2 = 0x01;   
	TIM2_CCMR3 = 0x01; 
	
	TIM2_CCER1 = 0x11; 			
	TIM2_CCER2 = 0x01;			
	
	TIM2_CCR1H  = 0x00;    
	TIM2_CCR1L  = 0x00;
	TIM2_CCR2H  = 0x00;   
	TIM2_CCR2L  = 0x00;
	TIM2_CCR3H  = 0x00;   
	TIM2_CCR3L  = 0x00;

	//TIM1_IER    = 0x81;   				//启动break and updata IE	
	
	TIM2_CR1    = 0x01; 				//中间对齐模式，向下计数时触发中断。
	
	TIM2_ARRH   = 0xEA;   
	TIM2_ARRL   = 0x60;
	
	TIM2_EGR   |= 0x01;
}


/*void TM3_INI(void)
{
	CLK_PCKENR1 |= 0x40;		//使能TIM3时钟
	TIM3_ARRH = 0x0;           // 配置PWM分辨率为10位，ARR=0x03FF
  TIM3_ARRL = 0x6b;           // PWM频率=2M/0x00c8=10k0c8Hz	
	 //PWM通道1设置
  TIM3_CCER1 |= 0x01;   //开启OC1信号输出脚
  TIM3_CCMR1 = 0x68;   //PWM1模式  
  TIM3_CCR1H = 0x00;    //占空比高位
  TIM3_CCR1L = 0x25;   //占空比低位//占空比为:CCR2/ARR=25%
  TIM3_CCMR1 |= 0x08;  //输出比较1预装载使能
  

	TIM3_CR1 = 0x01;           // 计数器使能，开始计数
	
}*/

//////////////////////////////////////////////////
void RAM_INI(void)
{
	error_bank.all_flag = 0;
	sys_state_flag.all_flag = 0;
	Alarm_Flag.all_flag = 0;
	sys_state_flag2.bit.chg_mode_cc = 1;
	sys_state_flag2.bit.start_flag = 1;
//	sys_state_flag2.bit.GB_alarm_start = 1;
//	sys_state_flag.bit.hall_exit = 1; 
	pwm_duty_on_old = 0;
	pwm_duty_on = 0;
	run_flag = 0;
	send_data_time = 0;
	sc_current_count = 0;
	current_zero_count = 0;
	sc_ref = 0;
	speed_num = 1;
	current_cmd_average = 0;
	delay_counter = 0;
	ph_low_count_max = 0;  
	flash_count = 10;
	sys_start_time = 0;
	uart_dan_mode = 4;
	Auto_SPT = 0;
	eeprom_read(); 
	
	
	if((user_Prdata.byte.voltage_adj > 700) || (user_Prdata.byte.voltage_adj == 0))
		user_Prdata.byte.voltage_adj = 678;//495;//475;//654
		
		if(user_Prdata.byte.voltage_adj > 421)//36v
		{
			battry_mode = 4;
		}
		else if(user_Prdata.byte.voltage_adj > 315)//27v
		{
			battry_mode = 3;
		}
		else 
			battry_mode = 2;
			
	if((user_Prdata.byte.current_adj > 160) || (user_Prdata.byte.current_adj == 0))
		user_Prdata.byte.current_adj = 12;//126;
		
	if((user_Prdata.byte.limit_adj > 500) || (user_Prdata.byte.limit_adj == 0))
		user_Prdata.byte.limit_adj = 280;
		
	if((user_Prdata.byte.ph_current_adj > 100) || (user_Prdata.byte.ph_current_adj == 0))
		user_Prdata.byte.ph_current_adj = PH_CURRENT_MAX;

	if((cvt_torlance_save > 200)||(cvt_torlance_save == 0))
		cvt_torlance_save = 60;

	/*if((speed_8km > 100) || (speed_8km == 0))	speed_8km = 100;
	if((speed_9km > 100) || (speed_9km == 0))	speed_9km = 100;
	if((speed_10km > 100) || (speed_10km == 0))	speed_10km = 100;
	if((speed_11km > 100) || (speed_11km == 0))	speed_11km = 93;
	if((speed_12km > 100) || (speed_12km == 0))	speed_12km = 85;
	if((speed_13km > 100) || (speed_13km == 0))	speed_13km = 78;
	if((speed_14km > 100) || (speed_14km == 0))	speed_14km = 71;
	if((speed_15km > 100) || (speed_15km == 0))	speed_15km = 64;
	if((speed_16km > 100) || (speed_16km == 0))	speed_16km = 57;
	if((speed_17km > 100) || (speed_17km == 0))	speed_17km = 50;
	if((speed_18km > 100) || (speed_18km == 0))	speed_18km = 43;
	if((speed_19km > 100) || (speed_19km == 0))	speed_19km = 35;
	if((speed_20km > 100) || (speed_20km == 0))	speed_20km = 28;
	if((speed_21km > 100) || (speed_21km == 0))	speed_21km = 21;
	if((speed_22km > 100) || (speed_22km == 0))	speed_22km = 14;
	if((speed_23km > 100) || (speed_23km == 0))	speed_23km = 7;
	if((speed_24km > 100) || (speed_24km == 0))	speed_24km = 0;
	if((speed_25km > 100) || (speed_25km == 0))	speed_25km = 0;*/


	if((test_ratio < 1) || (test_ratio > 30))//10
		test_ratio = 15;	

		
	/*if((pwm_dang_1 == 0) || (pwm_dang_1 > 100))//
		pwm_dang_1 = 35;//35
	if((pwm_dang_2 == 0) || (pwm_dang_2 > 100))	
		pwm_dang_2 = 45;//55
	if((pwm_dang_3 == 0) || (pwm_dang_3 > 100))	
		pwm_dang_3 = 60;
	if((pwm_dang_4 == 0) || (pwm_dang_4 > 100))	
		pwm_dang_4 = 80;
	if((pwm_dang_5 == 0) || (pwm_dang_5 > 100))	
		pwm_dang_5 = 100;
	
	if((current_dang_1 == 0) || (current_dang_1 > 100))//
		current_dang_1 = 10;
	if((current_dang_2 == 0) || (current_dang_2 > 100))
		current_dang_2 = 20;
	if((current_dang_3 == 0) || (current_dang_3 > 100))
		current_dang_3 = 40;
	if((current_dang_4 == 0) || (current_dang_4 > 100))
		current_dang_4 = 60;
	if((current_dang_5 == 0) || (current_dang_5 > 100))
		current_dang_5 = 100;

	if((pwm_dang_6 == 0) || (pwm_dang_6 > 100))	
		pwm_dang_6 = 35;//36
	if((current_dang_6 == 0) || (current_dang_6 > 100))
		current_dang_6 = 10;//10 */
	

			
			
			if((wheel_number > 30) || (wheel_number < 8))
			{
				wheel_number = 20;
			}
			if(test_ratio > 60)//30
			{
				test_ratio = 5;
			}

			
		/*if((power_line_rx > 8) || (power_line_rx < 2))
			power_line_rx = 5;
		if((magnetic_number_rx > 15) || (magnetic_number_rx < 2))
			magnetic_number_rx = 3;
		if((start_data_rx > 70) || (start_data_rx < 10))
			start_data_rx = 30;
		if((speed_slope_rx < 6) || (speed_slope_rx > 30))
			speed_slope_rx = 15;
		if((stop_time_rx < 1) || (stop_time_rx > 30))
			stop_time_rx = 10;
			
		if((motor_model_rx > 255) || (motor_model_rx < 3))//30
			motor_model_rx = 59;//66
		if((limit_speed_number > 60) || (limit_speed_number < 10))
			limit_speed_number = 25;//25
		if((wheel_number > 30) || (wheel_number < 8))
			wheel_number = 20;//14
		if((dead_time_rx > 99) || (dead_time_rx < 20))
			dead_time_rx = 95;//55*/

	voltage_adj_table54 = (user_Prdata.byte.voltage_adj * 54)/42;
	voltage_adj_table49 = (user_Prdata.byte.voltage_adj * 49)/42;
	voltage_adj_table48 = (user_Prdata.byte.voltage_adj * 48)/42;
	voltage_adj_table47 = (user_Prdata.byte.voltage_adj * 47)/42;
	voltage_adj_table46 = (user_Prdata.byte.voltage_adj * 46)/42;
	voltage_adj_table45 = (user_Prdata.byte.voltage_adj * 45)/42;
	voltage_adj_table42 = (user_Prdata.byte.voltage_adj * 42)/42;
//	current_adj_lowp;
	delvoltage = voltage_adj_table47 - user_Prdata.byte.voltage_adj;
	//MAX_P = voltage_adj_table49 * user_Prdata.byte.current_adj;
	//MAX_protect = voltage_adj_table48 * 500; 
	
	low_current_cmd_protect = 500;
	
	current_adj_lowp = user_Prdata.byte.current_adj;
	current_adj_table[0] = (user_Prdata.byte.current_adj >> 4);
	current_adj_table[1] = (user_Prdata.byte.current_adj >> 3);											//1/8
	current_adj_table[2] = (user_Prdata.byte.current_adj >> 2);											//2/8
	current_adj_table[3] = (user_Prdata.byte.current_adj >> 2) + (user_Prdata.byte.current_adj >> 3);	//3
	current_adj_table[4] = (user_Prdata.byte.current_adj >> 1);											//4
	current_adj_table[5] = (user_Prdata.byte.current_adj >> 1) + (user_Prdata.byte.current_adj >> 3);	//5
	current_adj_table[6] = (user_Prdata.byte.current_adj >> 1) + (user_Prdata.byte.current_adj >> 2);	//6
	current_adj_table[7] = user_Prdata.byte.current_adj - (user_Prdata.byte.current_adj >> 3);			//7/8
	current_adj_fifteen = user_Prdata.byte.current_adj*15/18;
	current_adj_I = user_Prdata.byte.current_adj >> 1;	//yn42
	current_adj_II = user_Prdata.byte.current_adj - (user_Prdata.byte.current_adj >> 2);	//yn42
	current_adj_III = user_Prdata.byte.current_adj;
	current_adj_battry = user_Prdata.byte.current_adj / 13 * 6;
	//current_adj_battry1 = user_Prdata.byte.current_adj / 26 ;
	
	ph_current_adj_table[1] = (user_Prdata.byte.ph_current_adj >> 3);
	ph_current_adj_table[2] = (user_Prdata.byte.ph_current_adj >> 2);
	ph_current_adj_table[3] = (user_Prdata.byte.ph_current_adj >> 2) + (user_Prdata.byte.ph_current_adj >> 3);
	ph_current_adj_table[4] = user_Prdata.byte.ph_current_adj >> 1;
	ph_current_adj_table[5] = (user_Prdata.byte.ph_current_adj >> 1) + (user_Prdata.byte.ph_current_adj >> 3);
	ph_current_adj_table[6] = (user_Prdata.byte.ph_current_adj >> 1) + (user_Prdata.byte.ph_current_adj >> 2);
	ph_current_adj_table[7] = user_Prdata.byte.ph_current_adj - (user_Prdata.byte.ph_current_adj >> 3);
	
	voltage_adj_table[0] = (user_Prdata.byte.voltage_adj >> 3);											//1/8
	voltage_adj_table[1] = (user_Prdata.byte.voltage_adj >> 2);											//2/8
	voltage_adj_table[2] = (user_Prdata.byte.voltage_adj >> 1);											//4/8
	voltage_adj_table[3] = (user_Prdata.byte.voltage_adj - (user_Prdata.byte.voltage_adj >> 2));		//6/8
	
	
	Current_temp.byte.current5 = user_Prdata.byte.current_adj;
	
	delay_counter = Current_temp.byte.current5;				//100%

	delay_counter = delay_counter*9;

	Current_temp.byte.current4 = delay_counter/10;			//90%

	delay_counter -= Current_temp.table[4];
	Current_temp.byte.current3 = delay_counter/10;			//80%

	delay_counter -= Current_temp.table[4];
	Current_temp.byte.current2 = delay_counter/10;			//70%

	delay_counter -= Current_temp.table[4];
	Current_temp.byte.current1 = (delay_counter/10);		//60%

	delay_counter = 0;

	voltage_table [4] = user_Prdata.byte.voltage_adj + (user_Prdata.byte.voltage_adj >> 2) + (user_Prdata.byte.voltage_adj >> 5) + (user_Prdata.byte.voltage_adj >> 7) + (user_Prdata.byte.voltage_adj >> 8);
	voltage_table [4] = voltage_table [4] - (voltage_table [4]>>4);

	voltage_table [3] = user_Prdata.byte.voltage_adj + (user_Prdata.byte.voltage_adj >> 2) + (user_Prdata.byte.voltage_adj >> 6) + (user_Prdata.byte.voltage_adj >> 7);
	voltage_table [3] = voltage_table [3] - (voltage_table [3]>>4);

	voltage_table [2] = user_Prdata.byte.voltage_adj + (user_Prdata.byte.voltage_adj >> 2) - (user_Prdata.byte.voltage_adj >> 8) + (user_Prdata.byte.voltage_adj >> 7);
	voltage_table [2] = voltage_table [2] - (voltage_table [2]>>4);

	voltage_table [1] = user_Prdata.byte.voltage_adj + (user_Prdata.byte.voltage_adj >> 2) - (user_Prdata.byte.voltage_adj >> 6) + (user_Prdata.byte.voltage_adj >> 8);
	voltage_table [1] = voltage_table [1] - (voltage_table [1]>>4);

	voltage_table [0] = user_Prdata.byte.voltage_adj + (user_Prdata.byte.voltage_adj >> 2) - (user_Prdata.byte.voltage_adj >> 4) + (user_Prdata.byte.voltage_adj >> 5);
	voltage_table [0] = voltage_table [0] - (voltage_table [0]>>4);

	current_adj_table_add[0] = user_Prdata.byte.current_adj + current_adj_table[4];
	current_adj_table_add[1] = user_Prdata.byte.current_adj + current_adj_table[3];
	current_adj_table_add[2] = user_Prdata.byte.current_adj + current_adj_table[1];
	
	//current_v = user_Prdata.byte.current_adj - 10;	//y42
	current_v = user_Prdata.byte.current_adj;	//y42
	current_temp = user_Prdata.byte.current_adj;
	current_speed = (user_Prdata.byte.current_adj*16)/18;
	current_max = user_Prdata.byte.current_adj;
	step_current = (current_max >> 4);			//
	start_current = current_speed;
	current_max_low_step = (current_max >> 1);
	
	sp_ph_current_limit_max = user_Prdata.byte.current_adj;	
	sp_ph_current_limit_10p = user_Prdata.byte.current_adj / 10;
	sp_ph_current_limit_20p = user_Prdata.byte.current_adj * 2 / 10;
	sp_ph_current_limit_30p = user_Prdata.byte.current_adj * 3 / 10;
	sp_ph_current_limit_40p	= user_Prdata.byte.current_adj * 4 / 10;
	sp_ph_current_limit_50p = user_Prdata.byte.current_adj * 5 / 10;
	sp_ph_current_limit_60p =	user_Prdata.byte.current_adj * 6 / 10;
	sp_ph_current_limit_70p = user_Prdata.byte.current_adj * 7 / 10;
	sp_ph_current_limit_80p = user_Prdata.byte.current_adj * 8 / 10;
	sp_ph_current_limit_90p = user_Prdata.byte.current_adj * 9 / 10;
	
	current_adj_12 = (u16)(user_Prdata.byte.current_adj*12/17);//ECO
	current_3a = user_Prdata.byte.current_adj/6;
	voltage_average_L = user_Prdata.byte.voltage_adj *22/21 ;
	voltage_average_L1 = user_Prdata.byte.voltage_adj ;
	voltage_average_H = user_Prdata.byte.voltage_adj;
	voltage_average_H = (voltage_average_H * 9)/6+(user_Prdata.byte.voltage_adj >> 4);//(voltage_average_H * 9)/6;(user_Prdata.byte.voltage_adj >> 4);
	
	current_adj_18a = user_Prdata.byte.current_adj * 18 / 20;
	current_adj_10a = user_Prdata.byte.current_adj * 10 / 17;
	
	cvt_add = (cvt_torlance_save >> 1);///5/8
	
}


void Init_UART2(void)//stm8s105c6只有异步串行口2可以使用
{
		UART2_CR1=0x00;
		UART2_CR2=0x00;
		UART2_CR3=0x00;		
		// 设置波特率，必须注意以下几点：
		//    (1) 必须先写BRR2
		//    (2) BRR1存放的是分频系数的第11位到第4位，
		//    (3) BRR2存放的是分频系数的第15位到第12位，和第3位
		//        到第0位
		// 例如对于波特率位9600时，分频系数=2000000/9600=208
		// 对应的十六进制数为00D0，BBR1=0D,BBR2=00
		//UART2_BRR2=0x00;
		//UART2_BRR1=0x0d;
		UART2_BRR2=0x02;//9600
		UART2_BRR1=0x68;
		UART2_CR2=0x0c;//允许接收，发送
		//UART2_CR2=0x2c;//允许接收，发送，开接收中断
}

/*void UART2_sendchar(unsigned char data)
{
	while((UART2_SR & 0x80)==0x00);
	UART2_DR=data;
}*/




				




