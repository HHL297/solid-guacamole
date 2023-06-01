
///////////////////////////////////////////////////
/*
adc模块，3.5us转换时间，6个通道可选。
*/
////////////////////////////////////////////////////

#include "hand_tble.h" 


/////////////////////////////////////////////////////
USER_PRDATA user_Prdata;


//adc
u16 AD_Value ;
u16 AD_ValueH ;
u8 AD_ValueL ;




u16 sc_ref ;
u8 current_offset;
u16 current_average ;
u8 ph_current_average;
u8 ph_current_average_back;
u8 sc_count = 0;
u8 ph_lost_count;
u8 ph_low_count;

u16 control_temp;
u16 @near control_temp_table[2];

u8 current_average1;
//u8 current_average1_table[3] ;

u8@near current_sample_average[3];
u8@near current_average_neg;

u8 current_zero_count ;
u8 start_current ;
u8 run_flag ;
u8 sc_current_count ;
u8 sys_start_time ;
u8 current_temp ;
u8 current_v;
u8@near current_adj_12;
u16 ph_current;
u8 current_speed ;
//u8 limit_current_hand ;
//u8 limit_current_speed ;
//u8 current_ph_1 ;
//u8 current_ph_2 ;
//u8 current_ph_delta ;
u8 phase_lost_count ;
u8 phase_normal_count ;
u16 step_current ;
u8 current_max ;
u16@near current_adj_table[8];

u8 @near ph_current_adj_table[8];
u16 @near current_adj_table_add[4];
unsigned @near int voltage_adj_table[4];
unsigned @near int voltage_adj_table49;
unsigned @near int voltage_adj_table48;
unsigned @near int voltage_adj_table47;
unsigned @near int voltage_adj_table46;
unsigned @near int voltage_adj_table45;
unsigned @near int voltage_adj_table42;
unsigned @near int voltage_adj_table54;
unsigned @near int current_adj_lowp;
//unsigned @near int MAX_P;
unsigned @near int voltage_data;
unsigned @near int voltage_data_back;
//unsigned @near int MAX_protect;
unsigned @near int low_current_cmd_protect_temp;
unsigned @near int low_current_cmd_protect;

//u8 @near protect_flag;
unsigned int delvoltage;
//unsigned int delcurrent;
//unsigned int voltage_adj_temp;
unsigned int current_adj_temp;

u8 current_max_low_step;
//u16 motor_run_count;

u8 temperature_average = 255;
u8 temp_over_count = 0;
u8 temp_normal_count = 0;

u8 temp_sdow_mode = 0;
unsigned @near int temp_sun = 0;
u8 temp_count = 0;
unsigned @near int speed_ad_sun = 0;
u8 speed_ad_count = 0;
u8 speed_ad;
u16 current_cmd_average1;
u16 current_cmd_average_old;
u8 speed_time_count;
u8 speed_check_count;
u8 lj_pale_count;

unsigned @near int  current_cmd_average_old1;
unsigned @near int  current_cmd_average_sub;

u8 cmd_start;
u8 protect_count;
u8 @near ph_current_count;
u16 current_cmd_protect_average;
u16 current_cmd_protect_average_dang;
u16 current_cmd_protect_average1;

u16 voltage_average;
u16 voltage_average_H;
//u8 voltage_average_L;
u8 voltage_low_count;
u8 voltage_normal_count;
u8 voltage_cut_count;

u8 sp_zero_count;
u8 speed_ok_count;
u8 speed_dn_count;
u8 pwm_duty_8bit;
u16	current_sample_16bit;
u16 @near cal_current_tab[32];
u8 add_16data;
u16 ph_current_average1;
u8 ph_current_average2;
//unsigned long sum_average_current;

u8 AD_count_max;

u8 @near flash_count;

u8@near c_offset;

u8@near current_average_log[16];
u8@near current_average_log_i;
u16@near current_average_log_sum;

u8@near current_high_flag;
//y42
u8@near current_s;
u8@near current_s1;
u8@near current_s2;

u8 @near current_adj_18a;
u8 @near current_adj_10a;

u16@near pwm_duty_on_ini;

u8@near current_limit_pwm_flag;
u16@near test_current_cmd_protect_average;//jin	//adbg
u16@near test_control_temp;//jin
u8 @near power_low45;
u8 @near power_low42;

u8 current_adj_I;
u8 current_adj_II;
u8 current_adj_III;
u8 @near current_adj_battry;
u8 short_count;
u16@near current_adj_fifteen;

u8 @near sp_release_count;
u8 @near sp_release_flag;
u8 @near sf_sp_cancel_count;

u8 @near motor_current_limit_flag;
u8 @near motor_stop_1st;
u8 @near speed_high_count;

u16 @near ph_current_offset;
u16 @near sphc_ref,voltage_average_L,voltage1,voltage2,voltage_average_L1;
u8 @near cvt_torlance_current,voltage_count,current_3a;
u8 @near cvt_add;	//CVT_AI

u8 @near current_sub_mod;
u8 @near current_add_mod;

u8 @near sp_ph_current_limit_max;
u8 @near sp_ph_current_limit_10p;
u8 @near sp_ph_current_limit_20p;
u8 @near sp_ph_current_limit_30p;
u8 @near sp_ph_current_limit_40p;
u8 @near sp_ph_current_limit_50p;
u8 @near sp_ph_current_limit_60p;
u8 @near sp_ph_current_limit_70p;
u8 @near sp_ph_current_limit_80p;
u8 @near sp_ph_current_limit_90p;
u8 @near sp_ph_current_limit;

u16@near current_ph;
u16 @near lj_ad_app;
u16 @near lj_ad_app_delta;
u16 @near control_lj_temp_old;
u16 @near lj_zero_auto_corrent_count;

u16 @near control_lj_temp_old_delta;
u16 @near control_lj_temp_table[2];
u16 @near control_lj_zero_table[2];
u16 @near current_ph_lj;
u16 @near current_lj;
u16 @near current_ph_lj_delta;
u16 @near current_ph_lj_old;
u16 @near current_ph_lj_time;

////////////////////////////////////////////////////
////////////////////////////////////////////////////
void AD_INI(void)
{
	CLK_PCKENR2 |= 0x08;	//使能ADC时钟

	ADC_CR2 = 0x00;			//禁止触发位



	ADC_CR1 = 0x21;			//3.5us fclk = fmast/4
#ifdef	T20_V1		
	ADC_TDRL |= 0x7F;		//AN0,AN2....AN6
	ADC_TDRH |= 0x00;		//
#else
	ADC_TDRL |= 0xf8;		//AN4,AN5....AN9
	ADC_TDRH |= 0x03;		//
#endif
//	ADC_CR1 |= 0x01;		//开始转换
	sys_step = 0;
	for(temp_sun = 0;temp_sun < 35000; temp_sun ++)
	{
		WDT_FLASH();
	}
	temp_sun = 0;
}

/////////////////////////////////////////////////
///
///
/////////////////////////////////////////////////
void adc_sample(void)
{
	if(sys_step == 56)
	{	
		while(((ADC_CSR & 0x80) == 0x00));		//检测AD转换是否完成
		ADC_CSR &= 0x7f;						//清除AD转换完成标记位
		voltage_average = ADC_DRH;					//记录ad高位
//		AD_ValueL = ADC_DRL;					//记录ad低位
//		AD_Value = AD_ValueH;
		voltage_average = (voltage_average * 4) + ADC_DRL;//计算10位ad值	
	}
	else if(sys_step == 40)
	{/////////////////////////////////////////温度采样
		while((ADC_CSR & 0x80) == 0x00);		//检测AD转换是否完成
		ADC_CSR &= 0x7f;						//清除AD转换完成标记位	

		speed_ad_sun += ADC_DRH;
		speed_ad_count ++;
	}
	
	else if(sys_step == 6)//XZ 	//LJ 
	{		
		while((ADC_CSR & 0x80) == 0x00);		
		ADC_CSR &= 0x7f;						
		AD_ValueH = ADC_DRH;	
		lj_ad_app = (AD_ValueH << 2) + ADC_DRL;
		
		#ifdef LJ_ZERO_AUTO_CORRECT
			//control_lj_temp_old = lj_ad_app;
			if(sys_state_flag.bit.lj_zero_chk_flag > 0)
			{
				if(lj_ad_app >= control_lj_zero_table[0])//control_lj_temp_old
					control_lj_temp_old_delta = lj_ad_app - control_lj_zero_table[0];
				else 
					control_lj_temp_old_delta = control_lj_zero_table[0] - lj_ad_app;
					
				if(control_lj_temp_old_delta < 20)// (&& )//10-0.05v
				{
					lj_zero_auto_corrent_count ++;
				}
				else lj_zero_auto_corrent_count = 0;
				
				if(lj_zero_auto_corrent_count > 1000)//4s
				{
					control_lj_zero_table[0] = lj_ad_app;
					lj_zero_auto_corrent_count = 0;
				}
			}
			
		#endif
		
		if(current_ph_lj_time <= 736)//436
			control_lj_temp_table[1] = lj_ad_app; //计算10位ad值	
		else 
		{
			/*if(lj_ad_app > control_lj_temp_table[1])
			 lj_ad_app_delta = lj_ad_app - control_lj_temp_table[1];
			 
			else if(control_lj_temp_table[1] > lj_ad_app)
				lj_ad_app_delta = control_lj_temp_table[1] - lj_ad_app;
				
			else lj_ad_app_delta = 0;
			
			 if(lj_ad_app_delta > 3)lj_ad_app_delta >>= 2;//
			 else lj_ad_app_delta = 1;
			 
			if(lj_ad_app > control_lj_temp_table[1])
			{
				//if(LJ_inc_number > 3)
				//{
				//	LJ_inc_number = 0;
					control_lj_temp_table[1] += lj_ad_app_delta;
			 //	}
				//else 
				//	LJ_inc_number ++;
			}
			else if(lj_ad_app < control_lj_temp_table[1])
			{
			//	if(LJ_dec_number > 3)
			//	{
				//	LJ_dec_number = 0;
					control_lj_temp_table[1] -= lj_ad_app_delta;
				//}
			//	else 
				//	LJ_dec_number ++;
			}*/
			control_lj_temp_table[1] = lj_ad_app;
			#ifdef LJ_PALE_START
				if((control_lj_temp_table[1] < control_lj_zero_table[0]) && (sys_state_flag.bit.lj_zero_chk_flag > 0))
				{
					if(lj_pale_count < 100)lj_pale_count ++;
					if(lj_pale_count >= 5)//3
					{
						control_lj_zero_table[0] = control_lj_temp_table[1];
						lj_pale_count = 0;
					}
				}
				else 
				{
					lj_pale_count = 0;
				}
			#endif
		//	else 
		//	{
			//	LJ_dec_number = 0;
			//	LJ_inc_number = 0;
			//}
		}
		
		
	}
	else if(sys_step == 26)
	{			//转把采样
		while((ADC_CSR & 0x80) == 0x00);		//检测AD转换是否完成
		ADC_CSR &= 0x7f;						//清除AD转换完成标记位	
		AD_ValueH = ADC_DRH;					//记录ad高位
//		AD_ValueL = ADC_DRL;					//记录ad低位
//		AD_Value = AD_ValueH;
		control_temp_table[1] = (AD_ValueH * 4) + ADC_DRL;//计算10位ad值	
		test_control_temp = control_temp;	//JIN	//jicf
		if(control_temp_table[0] < control_temp_table[1])
			control_temp =  control_temp_table[0];
		else
			control_temp =  control_temp_table[1];
		control_temp_table[0] = control_temp_table[1];
		
	}
	else if(sys_step == 12)
	{											//限速采样
		while((ADC_CSR & 0x80) == 0x00);		//检测AD转换是否完成
		ADC_CSR &= 0x7f;						//清除AD转换完成标记位	
		AD_ValueH = ADC_DRH;					//记录ad高位
	//	AD_ValueL = ADC_DRL;					//记录ad低位
//		AD_Value = AD_ValueH;
	//	current_cmd_protect_average1 = (AD_ValueH * 4) + ADC_DRL;//计算10位ad值	
     temp_sun += AD_ValueH;
		 temp_count++;
	
	}
	else if((sys_step & 0x03) == 0x03)
	{
#ifdef S58
		while((ADC_CSR & 0x80) == 0x00);		//检测AD转换是否完成
		ADC_CSR &= 0x7f;						//清除AD转换完成标记位	
		AD_Value = ADC_DRH;					//记录ad高位
//		AD_Value = (AD_Value << 1) + (ADC_DRL >> 1);//计算10位ad值
//		if(AD_Value > 250)
//			current_sample_average[2] = 250;
//		else
			current_sample_average[2] = AD_Value;
#endif
	}
//	ADC_CSR &= 0xf0;
//	ADC_CSR |= PHC_CHN;						//相电流通道
//	adc_channle_phcurrent();
}


void ad_data(void)
{
	if(sys_step == 62)
	{
		/*current_cmd_protect_average = current_cmd_protect_average1;

		if(current_cmd_protect_average < 700)
		{
			if(eco_flag == 1)
			
				current_cmd_protect_average = 169;//290;
			else
				current_cmd_protect_average = 169;
		}
		else
		{
			if(eco_flag == 1)
				current_cmd_protect_average = 255;//410;			//
			else
				current_cmd_protect_average = 255;
		}
		current_cmd_protect_average = 500;
		*/
		if(temp_count >63)//温度保护
		{
			temperature_average = (temp_sun/64);
			temp_sun = 0;
			temp_count = 0;
			
			if(temperature_average < 161)// 169 161)			//85
			{
				if(temp_over_count == 20)
				{
					temp_sdow_mode = ((176 - temperature_average)/6);		// 185 176
					if(temperature_average < 122)	//122		//temp over  95  以上实测
						error_bank.bit.temperature_flag = 1;   /////没有热敏电阻
				} 
				else
					temp_over_count ++;
			}
			if(error_bank.bit.temperature_flag == 1)
			{
				if(temperature_average > 127)	//127				//		80
				{
					if(temp_normal_count == 100)
					{
						temp_normal_count = 0;
						error_bank.bit.temperature_flag = 0;
						temp_sdow_mode = 0;
						temp_over_count = 0;
					}
					else
						temp_normal_count ++;
				}
			}
			else 
				temp_normal_count = 0;	
				
			if(temp_sdow_mode < 9)//10)
			{
				current_temp = user_Prdata.byte.current_adj - (step_current * temp_sdow_mode);
			}
			else
			{
				current_temp = current_adj_table[2];			//1/4
			}
		}
		
//		current_temp = user_Prdata.byte.current_adj;	
			
/////////////////////////////////////////////////////////////////////////////////////////////
#ifdef SIM_UART			
		if(uart_dan_mode == 0)//0.6
		{
			if(current_cmd_protect_average > 280)
				current_cmd_protect_average = 280;
		}
		else if(uart_dan_mode == 1)//0.7
		{
			if(current_cmd_protect_average > 330)
				current_cmd_protect_average = 330;
		}
		else if(uart_dan_mode == 2)//0.8
		{
			if(current_cmd_protect_average > 380)
				current_cmd_protect_average = 380;
		}
		else if(uart_dan_mode == 3)	//0.9
		{			
			if(current_cmd_protect_average > 430)
				current_cmd_protect_average = 430;
		}
		else if(uart_dan_mode == 4)		//1
		{
			if(current_cmd_protect_average > 500)
				current_cmd_protect_average = 500;
		}
		else
		{
			if(current_cmd_protect_average > 500)
				current_cmd_protect_average = 500;							
		}
#endif		
	}
	else if(sys_step == 60)
	{

#ifdef 	SIM_UART			
		if(current_temp > current_dang)
			current_temp = current_dang;
#endif			

#ifdef	LOW_POWER_MODE
		if(speed_num == 0)
		{
			if(current_temp > current_adj_lowp)
				current_temp = current_adj_lowp;
		}
#endif

		//y42
		/*if(speed_motor2 >= 220)
			current_max = current_s;//user_Prdata.byte.current_adj - current_adj_3;
		else if(speed_motor2 >= 180)
			current_max = current_s1;
		else if(speed_motor2 >= 150)
			current_max = current_s2;
		else*/
			//current_max = user_Prdata.byte.current_adj;

		/*if(motor_current_limit_flag > 0)
		{
			if(current_temp > current_adj_10a)
				current_temp = current_adj_10a;
		}*/

		if(current_temp >  current_v)
			current_temp = current_v;	
			
		/*if((spt_low_high_count_old_av > 0) && (spt_low_high_count_old_av < 180))
			current_lj = (current_ph_lj << 6) / spt_low_high_count_old_av;//spt_low_high_count_old 
		else 
			current_lj = (current_ph_lj << 6) / 180;//68
			*/
		//current_lj = current_ph_lj >> 1;	
			//if(sys_state_flag.bit.lj_flag > 0)current_lj += current_ph_zero;
		//if((spt_low_high_count_old_av > 0) && (spt_low_high_count_old_av < 300))
		//	current_lj = (current_ph_lj << 6) / spt_low_high_count_old_av;//spt_low_high_count_old 
		//else 
			//current_lj <<= 1;//6
			
			//current_lj = (current_lj * 70 * battry_mode / voltage_average_av_quarter) >> 1;
			/*current_lj = (current_lj * 70 * battry_mode / voltage_average_av_quarter) >> 1;//o?1|?ê
			
			current_lj = current_lj * test_ratio / 5;//5    //2aê?μ÷?ú±èày
			
			current_lj = current_lj * jp_number_real / 100; //è?±??￡ê?
			
			current_lj = current_lj * dang_limit_ratio / 100 ;  //μμ???úá|±è
			
			
		if(sys_state_flag.bit.lj_flag > 0)current_lj += (curent_base_rx * current_base_real / 100);//(current_ph_zero * (100 - jp_number_real) / 50);current_ph_zero*/
		
		//current_lj = current_lj * dang_limit_ratio / 100 ;  //μμ???úá|±è
		current_lj = current_ph_lj;
		if((current_temp > current_lj) && (((data_rx[5] & 0x10) == 0)) && (run_mode == 0) && (sys_state_flag.bit.sf_flag == 0) && ((control_temp < 300) || (sys_state_flag.bit.protect_flag > 0)))//
				current_temp = current_lj;//current_ph;
		
		//if((current_temp >  dang_limit_current) && ((control_temp < 300) || (sys_state_flag.bit.protect_flag > 0)))
			//current_temp = dang_limit_current;
			
		if((data_rx[5] & 0x10) > 0)//6km
		{
			if(current_temp >  dang_limit_current) //μμ???Tá÷
				current_temp = dang_limit_current;
		}
		//if(current_max > current_temp)	//y42
			//current_max = current_temp;	
			
		/*if(sys_state_flag.bit.spt_flag > 0)	//y42
		{		
			if(current_temp > current_speed)
				current_temp = current_speed;
		}*/
		
#ifdef	LOW_SPEED_LOE_POWER
				if(speed_motor2 > 350)
			{
				if(current_temp > current_speed)
				{
					current_temp = current_speed;
				}
			}		
#endif	
	/*	if(sys_state_flag.bit.phcurrent_over_flag > 0)
		{
			if(ph_current > current_max)
				ph_current = current_max;
			if(ph_current > 0)
				ph_current --;				
		}
		else
		{
			if(ph_current < user_Prdata.byte.current_adj)
				ph_current ++;				
		}

		if(current_temp > ph_current)
			current_temp = ph_current;
	*/
	
//		if(cvt_flag == 0)
//		{
//			if(current_temp > current_adj_18a)
//				current_temp = current_adj_18a;
//		}
		
		
#ifdef ALM_FUN	
		if(motor_alm_status_lock == 1)
			current_temp = current_adj_table[5];
			
#endif			
//		if(speed_limit_flag2 == 1)
//	    user_Prdata.byte.current_adj = current_adj_fifteen;
		if(current_max < current_temp)
		{
			current_max ++;
			current_adj_table_add[0] = current_max + current_adj_table[4];
			current_adj_table_add[1] = current_max + current_adj_table[3];
			current_adj_table_add[2] = current_max + current_adj_table[1];
		}
		else if(current_max > current_temp)
		{
			current_max --;
			current_adj_table_add[0] = current_max + current_adj_table[4];
			current_adj_table_add[1] = current_max + current_adj_table[3];
			current_adj_table_add[2] = current_max + current_adj_table[1];	
		}
		current_max_low_step = (current_max >> 1);	
		

	}
	else if(sys_step == 58)
	{
			if(voltage_average > voltage_average_H)					//higher than 60 volt?
			{
				error_bank.bit.voltage_over_flag = 1;
				sys_state_flag.bit.sf_flag = 0;
				pwm_duty_brake = 0;
				pwm_brake_max = 0;
			}
			else if(voltage_average < (voltage_average_H - 1))		//162
				error_bank.bit.voltage_over_flag = 0;	
	
			if(voltage_average < voltage1  )					//115
			{
				if(voltage_normal_count < voltage_count)								//32*2 = 
					voltage_normal_count ++;
				else
				{
					if(MODE_PORT > 0)
					{
						if(current_v > current_3a)
							current_v -= 1;
						else
						{
							current_v = current_3a;
							sys_state_flag.bit.sf_flag = 0;
						}
					}
					else
					{
							if(current_v > 0)
								current_v -= 1;
								else
								current_v = 0 ;
					}
						
					voltage_normal_count = 0;
					voltage_low_count = 0;
				}
				
				if(voltage_average < voltage2)
				{
					if((voltage_average < voltage_adj_table[3])||(current_v <= current_3a))	//2009.12.11                 //jpk
					{
						if(voltage_cut_count >= 2)
						{
							//LOW_VOLTAGE_ON();
							voltage_cut_count = 2;
							error_bank.bit.voltage_low_flag = 1;
							sys_state_flag.bit.sf_flag = 0;
							if(debug_mode_flag == 0)
								CLP_OFF();
							else
								CLP_ON();
						}
						else
							voltage_cut_count ++;
					}
				}
			}
			else if(voltage_average > (user_Prdata.byte.voltage_adj + 1))					//116
			{
				if(voltage_low_count < 10)
					voltage_low_count ++;
				else
				{
					CLP_ON();
					//error_bank.bit.voltage_low_flag = 0;
					voltage_cut_count = 0;
					if(voltage_normal_count > 0)
						voltage_normal_count --;
					voltage_low_count = 0;
				}
			}
	}
	else if(sys_step == 42)
	{
		if(speed_ad_count > 9)
		{
			speed_ad = (speed_ad_sun/10);
			speed_ad_sun = 0;
			speed_ad_count = 0;
			
			//pwm_duty_on_ini = (u16)(speed_ad*255)/((voltage_average)>>2);
			pwm_duty_on_ini = (u16)(4130/speed_motor2);
			if(pwm_duty_on_ini > 255)
			  pwm_duty_on_ini = 255;
//				pwm_duty_on_ini = 0;
		}
		
		//current_temp = user_Prdata.byte.current_adj;
	//	error_bank.bit.temperature_flag = 0;
	}
	else if(sys_step == 28)
	{
#ifdef ONE_KEY_FUN			
		handle_err();					//
#else

#endif
	}
	else if(sys_step == 20)
	{
		if(current_cmd_average_key > 0)
			current_cmd_average = current_cmd_average_key;
		else if(sys_state_flag.bit.brk_flag == 0)	//y42
		{
		if(current_v > 0)
			current_cmd_average = current_cmd_average1;
			else
			current_cmd_average = 0;
		}
			
		else//y42
			current_cmd_average = 0;//y42

		if(cmd_start == 0)
		{
			if(current_cmd_average >= 5)
				cmd_start = 1;
			else
				current_cmd_average = 0;
		}
		else
		{
			if(current_cmd_average == 0)
  		    	cmd_start = 0;
			else if(current_cmd_average <= 5)
			   current_cmd_average = 5;
		}
		
		if(current_cmd_average == 0)
		{
			TIM1_BKR  |= 0x80;
			
#ifdef ONE_KEY_FUN
		if(error_bank.bit.current_flow_flag == 1)
		{
			if(current_flow_count >= 3)
			{
				current_flow_count = 4;
				if(onekey_current_flow_flag == 0)
				  alarm.bit.repair_flag = 1;
			}
			else
			{
				current_flow_count ++;
			}
		}
			if(current_flow_count < 4)
				error_bank.all_flag &= 0x3f7F;					//清除错误标记位
			else
				error_bank.all_flag &= 0xbf7F;
				
#else		
			error_bank.all_flag &= 0x3f7F;		//hall reset by power			//	2F7F //
#endif		
			
			Restart_cont = 0;
			if(sp_zero_count > 10)
			{
				sp_zero_count = 0;
				error_bank.bit.motor_stop_flag = 0;
			}
			motor_stop_count = 0;
			motor_stop_count2 = 0;
			ph_lost_count = 0;
			hall_ok_count = 0; 
			ph_low_count_max = 0;
			ph_low_count_max_back = 0;
			hall_drive_back = 0;
			/*if((speed_motor2 < 250) && (speed_motor2 > 4))
				ModeFlag = 1;
			else
				ModeFlag = 0;	*/		
		}
	}
	else if(sys_step == 18)
	{
		if(current_cmd_average1 <= 0)//pwm_duty_on1) //0
		{
			if((sys_state_flag.bit.spt_flag > 0))// && (sys_state_flag.bit.lj_flag > 0))					//助力？
			//if(current_cmd_spt > 0)	//y42
			{
				current_cmd_average1 = pwm_duty_on1;	
			//	current_cmd_average1 = current_cmd_spt;	//y42
			}
		}
		if(((data_rx[5] & 0x10) > 0) /*|| ((control_temp > 300) && ((hand_mode_flag & 0x40) > 0))*/)//6km
		{
			current_cmd_average1 = 60;
		}
		
		//if(current_cmd_average1 > current_cmd_protect_average_dang)
		//     current_cmd_average1 =  current_cmd_protect_average_dang;
		if(current_cmd_average1 > current_cmd_protect_average)
			current_cmd_average1 = current_cmd_protect_average;		//限速保护
			
	if((current_cmd_average1 > dang_limit_pwm) && ((control_temp <= 300) || (sys_state_flag.bit.protect_flag > 0) || (dang_limit_pwm ==0)) /*|| ((hand_mode_flag & 0x80) > 0)*/)
			current_cmd_average1 = dang_limit_pwm;		//档位限速保护
			
			
		if((current_cmd_average1 > limit_current_speed) && (max_speed_limit < 41))//(hand_no_speed_limit == 0)) //(&& (sys_state_flag.bit.lj_speed_limit_flag > 0))
			current_cmd_average1 = limit_current_speed;		//霍尔限速保护	
			
		/*if((data_rx[1] & 0x20) > 0) // 6km
		{
			//if(current_cmd_average1 < 20)
			current_cmd_average1 = 20;
			current_temp = 12;	
		}*/
		//if(current_cmd_average1 > current_cmd_protect_average1)
			//current_cmd_average1 = current_cmd_protect_average1;
        /*if(sys_state_flag.bit.hall_exit == 0)
				{
          if(current_cmd_average1 > user_Prdata.byte.limit_adj)
				  current_cmd_average1 = user_Prdata.byte.limit_adj;	
				}
				else 
				{
					if(current_cmd_average1 > user_Prdata.byte.limit_adj)
				  current_cmd_average1 = user_Prdata.byte.limit_adj - 25;	
				}*/
			
		
#ifdef LOW_POWER_MODE
		if(speed_num == 0)
		{
			if(current_cmd_average1 > low_current_cmd_protect)
				current_cmd_average1 = low_current_cmd_protect;
		}
#endif
		
		if(current_cmd_average1 > MAX_PWMDUTY)
			current_cmd_average1 = 500;		//		
		
		if(sp_release_flag == 0)	// SFCCD
		{
			if(current_cmd_average1 < 10)
			{
				if(sp_release_count >= 25)
					sp_release_flag = 1;
				else
					sp_release_count ++;
			}
			else
				sp_release_count = 0;
		}
		else
		{
			if(current_cmd_average1 >= 10)
			{
				if(sf_sp_cancel_count > 25)
				{
					sys_state_flag.bit.sf_flag = 0;
					sp_release_flag = 0;
				}
				else
					sf_sp_cancel_count ++;
			}
			else
				sf_sp_cancel_count = 0;
		}
		
		current_cmd_average_old = current_cmd_average1;
		
		if((sys_state_flag.bit.spt_flag > 0))
			sys_state_flag.bit.sf_flag = 0;
			
#ifdef ONE_KEY_FUN
		if((onekey.bit.speed_err_flag > 0) || (onekey.bit.stop_err_flag > 0))
			sys_state_flag.bit.sf_flag = 0;
#endif
		
		if((sys_state_flag.bit.sf_flag > 0))
			current_cmd_average1 = current_cmd_average;
	}
	else if(sys_step == 14)
	{
		if(sys_state_flag.bit.protect_flag == 0)
		{
			if(control_temp >= 980)// (|| (HANDLE_PRO_PORT == 0))
				protect_count++;
			else
		 		protect_count = 0;
				
			if(protect_count > 3)						// 连续100次检测到手柄信号电压过高		
			{
				sys_state_flag.bit.sf_flag = 0;
				sys_state_flag.bit.protect_flag = 1;   // 判定处于自行车处于失控状态
			}
		}
		
		///////////////////////////////////////////////////////////////////////////////
		if(delay_counter < 125)						//					//
		{
			delay_counter ++;
			if(control_temp >= 200)     
			{
				sys_state_flag.bit.sf_flag = 0;
				sys_state_flag.bit.protect_flag = 1;				
			}
		}

		if(mode_flag == 0)
			control_temp = 0;		

		if(control_temp < 300) // 210 xz
		{
			current_cmd_average1 = 0;
			sys_state_flag.bit.protect_flag = 0;
		}
		else if(control_temp < 710) 
			current_cmd_average1 = (control_temp - 150)>>1;
		else
			current_cmd_average1 = 280;
			
		if((sys_state_flag.bit.protect_flag > 0) || (onekey.bit.speed_err_flag > 0))
			current_cmd_average1 = 0;
			
	//	else
	//		current_cmd_average1 = control_temp;		
	}
}




/////////////////////////////////////////////////
void current_num(void)
{
	if((sys_step & 0x03) == 0x01)
	{									//
		if(run_flag == 0)
		{
			sc_current_count ++;
			if(sc_current_count > 10)
			{
				sc_ref += current_sample_average[2];
				sphc_ref+= (ph_current_average1/2);
			}
			if(sc_current_count >= 138)				//
			{
				sc_ref = (sc_ref >>7);
				sphc_ref = (sphc_ref >> 6);
				sc_current_count = 0;
				run_flag = 1;
				current_offset = sc_ref;
				ph_current_offset = sphc_ref ;
			}
			current_sample_average[2] = 0;
			ph_current_average1 = 0;
		}
		else
		{
			if(current_sample_average[2] > current_offset)
			{
				current_average_neg = 0;
				current_sample_average[2] = current_sample_average[2] - current_offset;
			}
			else
			{
				current_average_neg = current_offset - current_sample_average[2];
				current_sample_average[2] = 0;
			}
				
		}
		
		if(current_average1 <= 2)		//13
		{
			if(error_bank.all_flag == 0)
			{
				if((sys_state_flag.bit.brk_flag == 0)&&(pwm_duty_on_old >= 80)&&(current_v >= 30)&&(speed_motor2 > 400))
				{
					if(current_zero_count >= 20)
					{
						//error_bank.bit.ph_lost_flag = 1;
						sys_state_flag.bit.sf_flag = 0;
					}
					else
						current_zero_count ++;
				}
				else
					current_zero_count = 0;
			}
		}
		else
			current_zero_count = 0;
			
		if(motor_alm_status_lock == 0)	
		{
			if((pwm_duty_on_old > 0)&&(sys_state_flag.bit.hall_exit == 0))
			{
				if(pwm_duty_on_old < 40)
				{
					if(current_average1 >= current_adj_I)
						short_count ++;
					else
						short_count = 0;
				}
				else if(pwm_duty_on_old < 65)
				{
					if(current_average1 >= current_adj_II)
						short_count ++;
					else
						short_count = 0;
				}
				else if(pwm_duty_on_old < 80)
				{
					if(current_average1 >= current_adj_III)
						short_count ++;
					else
						short_count = 0;
				}
				else
					short_count = 0;
			}
			else
				short_count = 0;
	
			if(short_count >= 3)
			{
				//error_bank.bit.current_flow_flag = 1;
				short_count = 0;
			}		
		}
		current_average1 = current_sample_average[2]/2 + current_sample_average[1]/2;
		current_ph = (current_average1 << 8) / pwm_duty_on_old;
		
		//if((sys_state_flag.bit.spt_flag == 0) && (sys_state_flag.bit.lj_flag == 0))current_ph_lj = 360;
		//if((control_temp > 245) && (control_temp < 900) &&  (speed_bike < 850))current_ph_lj = 200;
		//else current_ph_lj = 0;
		 //current_ph_lj = 200;
		
		current_sample_average[1] = current_sample_average[2];
		if((current_average1 < current_max) && ((current_ph < 160) || (speed_motor2 > 350)))//260 
		{
			current_add_mod = current_max - current_average1;
			//if(current_max > current_average1)current_add_mod = current_max - current_average1;
			//else current_add_mod = 1;
			
			if(current_add_mod > 10)
				current_add_mod = 12;
			else
			{
				current_add_mod = current_add_mod << 4;
				current_add_mod = 184 - current_add_mod;
			}
			
			if(hand_start_level == 0)
			{
				if(current_add_mod > 63)current_add_mod = 255;
				else current_add_mod <<= 2;
			}
			else if(hand_start_level == 1)
			{
				if(current_add_mod > 127)current_add_mod = 255;
				else current_add_mod <<= 1;
			}
			else if(hand_start_level == 2)
			{
				//if(current_add_mod > 127)current_add_mod = 255;
				//else current_add_mod <<= 1;
			}			
			else if(hand_start_level == 3)
			{	
				if(current_add_mod > 3)current_add_mod >>= 1;
				
			}
			
			//if(sys_state_flag.bit.lj_flag > 0)current_add_mod >>= 1;
			
			current_high_flag = 0;
		}
		else if((current_average1 > current_max) || (current_max == 0) || ((current_ph > 160) && (speed_motor2 <= 350)))////current_ph相电流
		{
				current_sub_mod = current_average1 - current_max;
			//if(current_average1 > current_max)current_sub_mod = current_average1 - current_max;
			//else current_sub_mod = 1;
			
		  if(current_sub_mod > 10)
				current_sub_mod = 12;
			else
			{
				current_sub_mod = current_sub_mod << 4;
				current_sub_mod = 184 - current_sub_mod;
			}
			
			if(sys_state_flag.bit.lj_flag > 0)
			{
				if(current_sub_mod > 63)current_sub_mod = 255;
				else current_sub_mod <<= 2;
			}
			current_high_flag = 1;
		}
		else
			current_high_flag = 2;
	}	
	else if((sys_step & 0x03) == 0x03)				//62.5*4 = 
	{
		if(alarm_switch == 0)
		{
			if(motor_flag.all_flag == DRIVE_BIT)
			{
				if((ModeFlag == 0) && (sys_state_flag.bit.hall_exit > 0) && (square_sine_change_flag == 1))
					//MotorStartSub();
				{}
				else if(current_cmd_average > 0)
					motor_dirve2();
			}
			else if(motor_flag.all_flag == ABS_BIT)
			{
				motor_abs();
			}
		}
		
	}
}
////////////////////////////////////////////////
void motor_dirve2(void)
{
#ifdef AUTO_PHS	
	if(sys_state_flag.bit.ph_flag == 0)
	{
#else
	if(ph_low_count_max == 0)
	{
#endif
		//if((sys_state_flag.bit.current_over_flag > 0))// || (sys_state_flag.bit.phcurrent_over_flag > 0))
		if(current_high_flag == 1)
		{
			pwm_add_count = 1;
			if(pwm_sub_count == 0)
			{
				if(sys_state_flag.bit.hall_exit == 1)
				{
					if(pwm_duty_on_old > 250)
						pwm_duty_on_old = 250;
				}
				
				if(pwm_duty_on_old >= 10)
				{
					/*if(current_average1 > current_adj_table_add[0])
					{
						pwm_duty_on_old -= (pwm_duty_on_old >> 2);
					}
					else if(current_average1 > current_adj_table_add[1])
					{
						pwm_duty_on_old -= (pwm_duty_on_old / 16);
					}*/
	//				else if(current_average1 > current_adj_table_add[2])
	//				{
	//					pwm_duty_on_old -= (pwm_duty_on_old >> 6);
	//				}
					
					pwm_duty_on_old -= 1;//1
				}
				else
					pwm_duty_on_old = 0;
			}
			pwm_sub_count ++;
			if(pwm_sub_count >= current_sub_mod)				//4
				pwm_sub_count = 0;
		}
		else
		{
			pwm_sub_count = 1;
			if((current_cmd_average > pwm_duty_on_old) || (current_average_neg >= 2))
			{
		//		if(current_high_flag == 0)
		//		{
						if(pwm_duty_on_old < 8)
							pwm_duty_on_old = 8;
						
					if(pwm_add_count == 0)
					{
						/*if((zero_start_number < 120) && (sys_state_flag.bit.lj_flag > 0) && (pwm_duty_on_old < 60))
						{
							pwm_duty_on_old = pwm_duty_on_old + ((current_cmd_average - pwm_duty_on_old) >> 3);
						}*/
							/*if((zero_start_number < 120) && (sys_state_flag.bit.lj_flag > 0))
							{		
										if(pwm_duty_on_old < 140 )pwm_duty_on_old = 140;
								//pwm_duty_on_old = pwm_duty_on_old + ((current_cmd_average - pwm_duty_on_old) >> 3);
							}*/
						//if(current_average1 < current_max_low_step)
							//pwm_duty_on_old += 2;
						//else
							pwm_duty_on_old += 1;//1
					}
					
					//if(pwm_duty_on_old > MAX_PWMDUTY)
					if(sys_state_flag.bit.hall_exit == 1)
					{
						if(pwm_duty_on_old > 250)
							pwm_duty_on_old = 256;						
					}
					else
					{
						if(pwm_duty_on_old > 280)
							pwm_duty_on_old = 280;
					}
						
					pwm_add_count++;

					if(pwm_add_count >= current_add_mod)// (|| ((zero_start_number < 120) && (sys_state_flag.bit.lj_flag > 0)))
						pwm_add_count = 0;

		//		}
			}
			else if((current_cmd_average < pwm_duty_on_old) && (current_average1 > c_offset))
			{
				if(pwm_cut_count == 0)
				{
					if(pwm_duty_on_old > 0)
						pwm_duty_on_old --;
				}
				pwm_cut_count ++;
				
				if(pwm_duty_on_old < 5)//5
					pwm_duty_on_old = 0;
					
				if(pwm_cut_count >= 25)//25
					pwm_cut_count = 0;
			}
			else
			{
					if(pwm_duty_on_old > 280)
						pwm_duty_on_old = 280;
				
			}
		}
	//	pwm_duty_on_old = 195;	//PI test
	}

}
////////////////////////////////////////////////////////

#ifdef	LOW_POWER_MODE
void Low_power0(void)
{
	if(voltage_average > (voltage_data + 6))
	{
		if(voltage_average > (voltage_data + 50))
			voltage_data = voltage_average;
		else
			voltage_data ++;
	}
	else if((voltage_average + 6) < voltage_data)
	{
		if((voltage_average + 50) < voltage_data )
			voltage_data = voltage_average;
		else
			voltage_data --;		
	}
}
////////////////////////////////////////////////
void Low_power1(void)
{
	if(voltage_data > voltage_adj_table48)
	{											//恒功率区
		low_current_cmd_protect = 500 - (voltage_data - voltage_adj_table48) * 3;//(MAX_protect / voltage_data);
	}
	else if(voltage_data < voltage_adj_table47)
	{											//降功率区
		if(voltage_data > user_Prdata.byte.voltage_adj)
		{
			low_current_cmd_protect_temp = (300 * (voltage_data - user_Prdata.byte.voltage_adj));
		}
	}
}
/////////////////////////////////////////////////
void Low_power2(void)
{
	if(speed_num == 0)
	{
		if(voltage_data > voltage_adj_table48)
		{											//恒功率区
			low_current_cmd_protect = low_current_cmd_protect;
		}
		else if(voltage_data < voltage_adj_table47)
		{											//降功率区
			if(voltage_data <= user_Prdata.byte.voltage_adj)
			{
				low_current_cmd_protect = 200;
			}
			else
			{
				low_current_cmd_protect = 200 + (low_current_cmd_protect_temp / delvoltage);
			}
		}
		else
		{											//恒电流区
			low_current_cmd_protect = 500;
		}
		
		if(low_current_cmd_protect > 366)
			low_current_cmd_protect = 366;		
	}
	else
	{
		low_current_cmd_protect = 500;
	}
}
////////////////////////////////////////////////

void Low_power3(void)
{
	current_adj_temp = low_current_cmd_protect * user_Prdata.byte.current_adj;
}

/////////////////////////////////////////////////

void Low_power4(void)
{
	if(speed_num == 0)
	{		
		current_adj_lowp = current_adj_temp / 500;
		
		if(current_adj_lowp > current_adj_table[6])
			current_adj_lowp = current_adj_table[6];
			
		if(low_current_cmd_protect > 366)
			low_current_cmd_protect = 366;	
	}
	else
	{
		current_adj_lowp = user_Prdata.byte.current_adj;
		low_current_cmd_protect = 500;
	}
}

#endif

///////////////////////////////////////////////////
////////////////////////////////////////////////
////////////////////////////////////////////////
void motor_abs(void)
{
	brake_pwm_duty();
	pwm_duty_on = 0;
	pwm_duty_on_old = 0;	
}

////////////////////////////////////////////////
////////////////////////////////////////////////

void adc_channel(void)
{
//	while((ADC_CSR & 0x80) == 0x00);		//检测AD转换是否完成
//	ADC_CSR &= 0x7f;						//清除AD转换完成标记位	
	
	ADC_CSR &= 0xf0;
	

if(sys_step == 56)
	{
		ADC_CSR |= VOL_CHN;		//电压采样
		ADC_CSR &= 0x7f;
		ADC_CR1 |= 0x01;			//开始转换
	}
	else if(sys_step == 40)
	{
		ADC_CSR |= PRO_CHN;		//温度采样
		ADC_CSR &= 0x7f;
		ADC_CR1 |= 0x01;			//开始转换
	}
	else if(sys_step == 26)
	{
		ADC_CSR |= HAD_CHN;		//转把采样
		ADC_CSR &= 0x7f;
		ADC_CR1 |= 0x01;			//开始转换
	}
	else if(sys_step == 12)
	{
		ADC_CSR |= TEM_CHN;		//限速采样
		ADC_CSR &= 0x7f;
		ADC_CR1 |= 0x01;			//开始转换
	}
	else if(sys_step == 6) //LJ XZ ADD
	{
		ADC_CSR |= LJ_CHN;		
		ADC_CSR &= 0x7f;
		ADC_CR1 |= 0x01;			
	}
//	else if(sys_step == 8)
//		ADC_CSR |= NUL_CHN;		//
//	else if(sys_step == 6)
//		ADC_CSR |= NUL_CHN;		//
	else if((sys_step & 0x03) == 0x03)
	{
#ifdef	T20_V1	

#else
		ADC_CSR |= CUR_CHN;		//电流采样
		ADC_CSR &= 0x7f;
		ADC_CR1 |= 0x01;			//开始转换
#endif

	}
}

/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
void adc_sampel_ph(void)					//相电流采样处理
{
	AD_count_max = 10;

	while(((ADC_CSR & 0x80) == 0x00) && (AD_count_max --));		//检测AD转换是否完成
	ADC_CSR &= 0x7f;						//清除AD转换完成标记位
	if(AD_count_max > 0)
	{
		AD_Value = (ADC_DRH << 2) + ADC_DRL;
		ph_current_average1 = AD_Value;
		if((run_flag == 1))//&&(debug_mode_flag > 0))
		{
		if(ph_current_average1 > ph_current_offset)
			cvt_torlance_current = ph_current_average1 - ph_current_offset;
		else
			cvt_torlance_current = 0;	
		}		
	}
	else
		ph_current_average1 = 0;
}
//////////////////////////////////////////////////////////////////
//
//
//
//////////////////////////////////////////////////////////////////

void motor_stop(void)
{
	speed_motor = hall_count;
	hall_count = 0;
#ifdef	HALL_CHANG_AUTO	
	if(sys_state_flag.bit.hall_exit > 0)
	{
		if(speed_motor > ERRHALLNUM)			//
		{
//			ModeFlag = 0;					
			position_flag = 1;
			motor_stop_count = 0;
			speed_ok_count = 0;
			motor_stop_count2 = 0;
			sys_state_flag.bit.sf_flag = 0;				//清自动巡航标志
		}
		else
		{
			if((speed_motor < 3) || (speed_motor2 > 250))
			{
				if(ModeFlag == 1)
				{
					if(speed_dn_count < 4)
						speed_dn_count ++;
					else
					{
						//ModeFlag = 0;	
						speed_dn_count = 0;
						position_flag = 1;
						speed_ok_count = 0;
						motor_stop_count = 0;	
						motor_stop_count2 = 0;
					}
				}
				else
				{
					speed_dn_count = 0;
				}
#ifdef SIM_UART
				if(sleep_count == Sleep_time)		//10S   230			;;13793  10min
				{
					TMM4_flag.bit.sleep_flag = 1;	
				}
	
				if(sleep_count > Sleep_time_err)		//
				{
					TMM4_flag.bit.sleep_flag = 1;
				}
				else
					sleep_count	++;		
#endif						
			}
			else
			{
				sleep_count = 0;
				speed_dn_count = 0;
			}
		}
	}
	
#endif
	
	if(speed_motor2 > 490)
	{
#ifdef SIM_UART
		if(sleep_count == Sleep_time)		//10S   230			;;13793  10min
		{
			TMM4_flag.bit.sleep_flag = 1;	
		}

		if(sleep_count > Sleep_time_err)		//
		{
			TMM4_flag.bit.sleep_flag = 1;
		}
		else
			sleep_count	++;		
#endif				
		if(current_average1 > current_adj_table[3])			//7A
		{
			if(sys_state_flag.bit.brk_flag == 0)
			{
				if(motor_stop_count < 25)			//10*43.5ms = 435ms		
					motor_stop_count ++;
				else
				{
					error_bank.bit.motor_stop_flag = 1;
					position_flag = 1;	
					sp_zero_count = 0;
					//定位标志置位
//					ModeFlag = 0;
				}
			}
			if(motor_stop_count == 7)
				motor_current_limit_flag = 1;							
		}
		else
		{
			motor_current_limit_flag = 0;
			motor_stop_count = 0;
		}
	}
	/*else if(speed_motor2 > 120)
	{
		if(current_average1 > current_adj_table[4])			//7A Prdata.byte.current_offset_adj+20
		{
			if(sys_state_flag.bit.brk_flag == 0)
			{
				if(motor_stop_count2 < 80)			//143*43.5ms = 1.87s
					motor_stop_count2 ++;
				else
				{
					ModeFlag = 0;
					sp_zero_count = 0;
					position_flag = 1;					//定位标志置位
					error_bank.bit.motor_stop_flag = 1; 
					speed_high_count = 0;
				}
				if(motor_stop_count2 == 40)
					motor_current_limit_flag = 1;				
			}
		}
		else
		{
			motor_stop_count2 = 0;
			motor_stop_count = 0;
		}
	}*/
	else
	{
		sleep_count = 0;
		motor_stop_count2 = 0;	
		motor_stop_count = 0;
		
	}
		
	if(error_bank.bit.motor_stop_flag > 0)
	{
		sys_state_flag.bit.sf_flag = 0;
		if(sp_zero_count <= 10)
			sp_zero_count ++;
	}
}

//////////////////

#ifdef	ONE_KEY_FUN

void sys_start_main(void)
{
	if(sys_start_time < 250)
		sys_start_time ++;
	
	if(sys_state_flag2.bit.start_flag > 0)
	{
		if(sys_start_time == 60)
		{
			if(sys_state_flag.bit.brk_flag == 1 )
			{
				if((onekey.err > 0) && (onekey.bit.stop_err_flag == 0))
				{
					onekey.bit.two_err_flag = 1;
				}
				onekey.bit.stop_err_flag = 1;
			}
			
			if(onekey.bit.speed_err_flag > 0)
			{
				if((control_temp < 50)||(control_temp > 307))
				{
					if((onekey.err > 0) && (onekey.bit.speed_err_flag == 0))
					{
						onekey.bit.two_err_flag = 1;
					}
					onekey.bit.speed_err_flag = 1;
				}
				else
				{
					onekey.bit.speed_err_flag = 0;
				}
			}
			
			if(onekey.err == 0)
			{
				alarm2.bit.all_ok = 1;
			}
			else if(onekey.bit.two_err_flag > 0)
			{
				alarm.onekeypass &= 0xF8;
				alarm.bit.two_alm_flag = 1;
			}
			else if(onekey.bit.stop_err_flag > 0)
			{
			//	onekey.bit.stop_err_flag = 0;
			//	alarm2.bit.brk_flag = 1;
				alarm.bit.stop_alm_flag = 1;
			}
			else if(onekey.bit.speed_err_flag > 0)
			{
			//	onekey.bit.speed_err_flag = 0;
			//	alarm2.bit.hand_flag = 1;
				alarm.bit.speed_alm_flag = 1 ;
			}
			sys_state_flag2.bit.start_flag = 0;
		}
		else
		{
			if(sys_start_time == 5)
			{
				if(sys_state_flag.bit.brk_flag == 1 )
				{
					if((onekey.err > 0) && (onekey.bit.stop_err_flag == 0))
					{
						onekey.bit.two_err_flag = 1;
					}
					onekey.bit.stop_err_flag = 1;
				}
				
				if((control_temp < 50)||(control_temp > 307))
				{
					if((onekey.err > 0) && (onekey.bit.speed_err_flag == 0))
					{
						onekey.bit.two_err_flag = 1;
					}
					onekey.bit.speed_err_flag = 1;
				}
				
				if(onekey.err == 0)
				{
					alarm2.bit.sys_start = 1;	
				}

				if(onekey.err == 0)
				{
					alarm2.bit.all_ok = 1;
					sys_state_flag2.bit.start_flag = 0;
				}
				else if(onekey.bit.two_err_flag > 0)
				{
					alarm.onekeypass &= 0xF8;
					alarm.bit.two_alm_flag = 1;
					sys_state_flag2.bit.start_flag = 0;
				}
				else if(onekey.bit.stop_err_flag > 0)
				{
					onekey.bit.stop_err_flag = 0;
					alarm2.bit.brk_flag = 1;
				//	alarm.bit.stop_alm_flag = 1;
				}
				else if(onekey.bit.speed_err_flag > 0)
				{
				//	onekey.bit.speed_err_flag = 0;
					alarm2.bit.hand_flag = 1;
				//	alarm.bit.speed_alm_flag = 1 ;
				//	sys_state_flag2.bit.start_flag = 0;
				}
			}
		}
	}
}

#endif


#ifdef	SF_AUTO_FUN

////////////////////////////////////////////////////////////////////////////////
void auto_sf(void)
{
	if((sys_state_flag.bit.sf_sel_flag > 0))								//速度大于0，判断是否需要进行速度巡航
	{
		if((control_temp > 317) && (sys_state_flag.bit.protect_flag == 0) && (speed_motor2 < 490))
		{
			if(speed_time_count < 4)					//每200* 43.5ms = 8s计算一次是否需要自动巡航
			{
				speed_check_count++;
				if(speed_check_count > 20)				//40*50ms = 2000ms = 2s
				{
					speed_check_count = 0;
					if(current_cmd_average > current_cmd_average_old1)
						current_cmd_average_sub = current_cmd_average - current_cmd_average_old1;
					else current_cmd_average_sub = current_cmd_average_old1 - current_cmd_average;
					
					if(current_cmd_average_sub < 8)
						speed_time_count++;
					else
						speed_time_count = 0;
						
					current_cmd_average_old1 = current_cmd_average;	
				}
			}
			else
			{
				sys_state_flag.bit.sf_flag = 1;							//设置自动巡航标志
				speed_time_count = 0;					//定时器
			}
		}
		else
		{
			speed_time_count = 0;
			speed_check_count = 0;
		}
	}
	else 
	{
		speed_time_count = 0;		 			//定时器
		current_cmd_average_old1 = 0;
	}
}
//////////////////////////////////////////////////////
#endif



@far @interrupt void ADC_IRQ (void)
{
	
	
	
	
	return;
}














