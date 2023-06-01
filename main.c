/* MAIN.C file
 * 
 * Copyright (c) 2002-2005 STMicroelectronics
 */
#include "hand_tble.h"	//���� C ��������ʵ�ʱ���֮ǰҪ���� hand_tble.h �ļ���
//#include "main_h.h"
//

///////////////////////////////////////
unsigned char sys_step = 0;	//sys_step = 0  unsigned char Ϊ1���ֽ�
///////////////////////////////////////////////
//unsigned char xi=0,xk=0;
//void uart2_send_data(void);
void Init_UART2(void);
void data_load(void);
//void TM3_INI(void);

////////////////////////////////////////////////////////////////
//��Щ�������õ�Ŀ�����ڳ���ʼִ��ʱ����ϵͳ�ĸ������ֽ����ʵ��ĳ�ʼ��
//��ȷ�����Ǵ��ں��ʵ�״̬���Ա�����ܹ��������в����к����Ĳ�����
main()    //�����ǳ������������������ڣ���������￪ʼִ�С�
{
 	DI();    //__asm("sim");  ���������䣬��ʾ�����в�����ָ�sim��
	WDT_INI();    //���Ź���ʱ��watchdog Timer
	RAM_INI();    //RAM��ʼ�������ȡ���� Random Access Memory
	OPTIONSET_INI();	//�Ĵ�����ʼ�� Option Register
	OSC_INI();     //��ʼ������ Oscillator
	IO_INI();    //��ʼ��io�˿�
	TM1_INI();   //��ʼ����ʱ��
	TM2_INI();
	//TM3_INI(); // MID_MOTOR
	AD_INI();    //��ʼ������ת���� Analog-to-Digital Converter ADC
//	CLP_ON();			//�������ŵ�Դ
	EI();    //__asm("rim"); ���������䣬��ʾ�����в�����ָ�rim��
	Init_UART2();   //���ڳ�ʼ��UART2��ͨ���첽�շ�������
	data_load();    //�������ڼ�������
	//y42  ����ʲô��˼��̫��
	current_s = (user_Prdata.byte.current_adj >> 1) + (user_Prdata.byte.current_adj >> 5);    //�ڶ�����������1λ+����5λ user Prdata�û����ݽṹ byte���� voltage adj ��ѹ����ֵ
	current_s1 = (user_Prdata.byte.current_adj >> 1) + (user_Prdata.byte.current_adj >> 3);   //
	current_s2 = (user_Prdata.byte.current_adj >> 1) + (user_Prdata.byte.current_adj >> 2);
	while(1) //��������ѭ��
	{

		_asm("nop");
		
		_asm("nop");
	}
}

void data_load(void)    //������һ����Ϊdata_load�ĺ���
{
	voltage_count = 30��    //��ѹ���� ��ѹֵΪ30
	voltage1 = user_Prdata.byte.voltage_adj;    //�û������ֽڵ�ѹ����ֵ
	voltage2 = voltage1;     //��ѹֵ2���ڵ�ѹֵ1
	
	voltage_average_sum = 0;    //��ѹ_ƽ����_�ܺ�
	voltage_average_av = 0;    //��ѹ_ƽ����_
	voltage_average_count = 0;   //��ѹ_ƽ��_����
	
	current_cmd_protect_average= 280;    //��ǰ_cmd_����_ƽ���� �������ڱ����������ƵĲ�����ֵ
	speed_bike = 900;    //ת�ٻ�����ʲô??
	speed_bike_temp = 0x707;     //�ٶ�-���г�-�¶� 0x707��ʮ������ת��Ϊ10����1807
	jp_number = 100;    //����������ɶ��
	
	//limit_speed_hall = 4;// 25KM LIMIT 
	limit_speed_hall_1 = 97;//109;//118 * 28 / 25;//limit_speed_number//�����ע�ͣ���������97
	//limit_speed_hall_1 = motor_model_rx * wheel_number / limit_speed_number;//limit_speed_hall_1 = 6;//30;//(limit_speed_hall * 10) >> 3;//20
//limit_speed_hall_2 = (limit_speed_hall * 6) >> 3;//27
	//limit_speed_hall_3 = (limit_speed_hall * 6 ) >> 3;//27
	current_ph_zero = 0;    //��ǰph��� �²��ǵ�����λ��phase�����
	run_mode = 0;    //����ģʽ
	lamp_old_flag = 0;    //��-��-���� �²�������ʾ�Ƶ�״̬
	lamp_onoff_count = 0;    //��-����-���� �²�������¼�ƵĿ��ش��� ����¼�Ƶ�״̬
}

void OSC_INI(void)  //��δ����Ƕ�ϵͳʱ�ӽ��г�ʼ������
{		//int osc 16mhz
	CLK_CKDIVR = 0x00;			//FMAST = 16MHZ,FCPU = 16MHZ //�䣺0x00ʮ�����Ʊ�ʾ0��������˼�ǽ���ʱ��Ƶ������Ϊ16MHZ��������Բ�һ�¼����ֲῴ���Ƿ��Ӱ��������
	
	CLK_ICKR |= 0x01;			//ʹ��LRC HRC//16mhz�ڲ�ʱ��    //�䣺�����ڲ�ʱ��Դ
	CLK_ICKR &= 0xF7;			//�䣺
	
	while((CLK_ICKR & 0xFD) == 0);//�ȴ� HRC RADY
	
	if(CLK_CMSR != HSI)
		CLK_SWR = HSI;			//ʹ���ڲ�����ʱ�ӣ�Ĭ��״̬
	
	CLK_SWCR |= 0x02;
	
	CLK_PCKENR2 = 0x00;			//�ر�����ʱ��
	CLK_PCKENR1 = 0x08;			//�ر�����ʱ��	//uart 
	////**********************//////
	
	CLK_CKDIVR = 0x00;			//16mhz�ڲ�ʱ��  
	CLK_SWIMCCR = 0x00;			//SWIM _CLK  //�䣺�ӿڵ�ʱ��Ƶ��
	
	CLK_CSSR |= 0x01;			//����ʱ�Ӱ�ȫϵͳ	
}
///////////////////////////////////////////////
///////////////////////////////////////////////
void IO_INI(void)           //�䣺Ӳ��IO�ڵĳ�ʼ����Input/Output��
{
#ifdef   S58
	PA_ODR |= 0x00;			//0~7	
	PA_DDR |= 0x20;			//�����
	PA_CR1 |= 0xFF;			//�����ڲ�����
	PA_CR2 |= 0x20;			//����ģʽ�ǽ�ֹ�ⲿ�жϣ�
	
	PB_ODR |= 0x00;//0x07;//0x00;//	//0X00		//0~7		/PWM����
	PB_DDR |= 0x07;			//
	PB_CR1 |= 0x0F;			//
	PB_CR2 |= 0x0F;			//
	
	PC_ODR |= 0x00;			//0~7		/PWM����
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
void WDT_INI(void)		//���Ź���ʼ��
{
	IWDG_KR = 0x55;		//����
	IWDG_PR = 0x03;		//���Ź���Ƶ  64K/32 =  2K = 500US    4,8,16,32,64,128,256,
	IWDG_RLR = 20;		//20*500us = 10ms
	IWDG_KR = 0xAA;		//����
	IWDG_KR = 0xCC;		//�������Ź�
}


////////////////////////////////////////////////////////////////////////////
void SPI_ini(void)		//�䣺��ʼ��SPI��Serial Peripheral Interface���ӿ�
{
	CLK_PCKENR1 |= 0x02;				//ʹ��SPIʱ�� //�䣺����Ӧ�ĵڶ�λ��λ����Ϊ1����ʹ��SPI��ʱ�ӡ���������ȷ��SPI�ӿڵ�ʱ�ӱ�ʹ�ܣ��Ա�������ݴ����ͨ�š�
	

	
	
	
}

////////////////////////////////////////////////////////////////////////////
void sci_ini(void)
{
	CLK_PCKENR1 |= 0x04;			//ʹ��uartʱ�� //�䣺����Ӧ�ĵ���λ��λ����Ϊ1����ʹ��UART��ʱ�ӡ���������ȷ��UART�ӿڵ�ʱ�ӱ�ʹ�ܣ��Ա���д���ͨ�š�
	
	
	
	
	
	
	
}
////////////////////////////////////////////////\
//PWM��ʼ����16k���ֱ���500
//��: 
//
//
////////////////////////////////////////////////
void TM1_INI(void)
{
	CLK_PCKENR1 |= 0x80;		//ʹ��TIM1ʱ��
	
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
	TIM1_EGR |= 0x20;					//ˢ��PWM	

	TIM1_IER    = 0x81;   				//����break and updata IE	
	
#ifdef LP_PWM	
	TIM1_DTR = 0x5f;	//0x85					//8*FTIM = 1us ����ʱ��//6us
#else
		TIM1_DTR = 0x21;//39;						//8*FTIM = 1us ����ʱ��
#endif
	//TIM1_CR2   = 0x21;	
	TIM1_CR2 = 0x21;					//�����¼���ѡΪ��������
	
	TIM1_BKR = 0x92; 				//b2
	
	TIM1_CR1    = 0xA5; 				//�м����ģʽ�����¼���ʱ�����жϡ�
	TIM1_CCER2 = ((TIM1_CCER2 & 0x1f) | 0x10);
	TIM1_CCMR4 = PWM_MODE1;
	PWM_ALL_OFF();
	TIM1_EGR   |= 0x01;
}
////////////////////////////////////////////////////////////////////////
void NOHALL_TIM1(void)
{
	CLK_PCKENR1 |= 0x80;		//ʹ��TIM1ʱ��
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
	TIM1_IER    = 0x81;   				//����break and updata IE	
	TIM1_DTR = 0;
	TIM1_CR2   = 0x21;					//�����¼���ѡΪ��������
	TIM1_BKR    = 0x92; 				//b2
	TIM1_CR1    = 0xA5; 				//�м����ģʽ�����¼���ʱ�����жϡ�
	PWM_ALL_OFF();
	TIM1_EGR   |= 0x01;
}
//////////////////////////////////////////////////////////////////////////////
void TM2_INI(void)
{
	CLK_PCKENR1 |= 0x20;		//ʹ��TIM2ʱ��
	
	TIM2_CNTRH = 0x00; //TIM2��������8λ(TIM1_CNTRH)
	TIM2_CNTRL = 0x00;
	
	TIM2_SR1 &= 0x00;  //״̬�Ĵ���1
	TIM2_SR2 &= 0x00;
	
	TIM2_PSCR = 0x08;  //time2����Ƶ   2
	
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

	//TIM1_IER    = 0x81;   				//����break and updata IE	
	
	TIM2_CR1    = 0x01; 				//�м����ģʽ�����¼���ʱ�����жϡ�
	
	TIM2_ARRH   = 0xEA;   
	TIM2_ARRL   = 0x60;
	
	TIM2_EGR   |= 0x01;
}


/*void TM3_INI(void)
{
	CLK_PCKENR1 |= 0x40;		//ʹ��TIM3ʱ��
	TIM3_ARRH = 0x0;           // ����PWM�ֱ���Ϊ10λ��ARR=0x03FF
  TIM3_ARRL = 0x6b;           // PWMƵ��=2M/0x00c8=10k0c8Hz	
	 //PWMͨ��1����
  TIM3_CCER1 |= 0x01;   //����OC1�ź������
  TIM3_CCMR1 = 0x68;   //PWM1ģʽ  
  TIM3_CCR1H = 0x00;    //ռ�ձȸ�λ
  TIM3_CCR1L = 0x25;   //ռ�ձȵ�λ//ռ�ձ�Ϊ:CCR2/ARR=25%
  TIM3_CCMR1 |= 0x08;  //����Ƚ�1Ԥװ��ʹ��
  

	TIM3_CR1 = 0x01;           // ������ʹ�ܣ���ʼ����
	
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


void Init_UART2(void)//stm8s105c6ֻ���첽���п�2����ʹ��
{
		UART2_CR1=0x00;
		UART2_CR2=0x00;
		UART2_CR3=0x00;		
		// ���ò����ʣ�����ע�����¼��㣺
		//    (1) ������дBRR2
		//    (2) BRR1��ŵ��Ƿ�Ƶϵ���ĵ�11λ����4λ��
		//    (3) BRR2��ŵ��Ƿ�Ƶϵ���ĵ�15λ����12λ���͵�3λ
		//        ����0λ
		// ������ڲ�����λ9600ʱ����Ƶϵ��=2000000/9600=208
		// ��Ӧ��ʮ��������Ϊ00D0��BBR1=0D,BBR2=00
		//UART2_BRR2=0x00;
		//UART2_BRR1=0x0d;
		UART2_BRR2=0x02;//9600
		UART2_BRR1=0x68;
		UART2_CR2=0x0c;//������գ�����
		//UART2_CR2=0x2c;//������գ����ͣ��������ж�
}

/*void UART2_sendchar(unsigned char data)
{
	while((UART2_SR & 0x80)==0x00);
	UART2_DR=data;
}*/




				




