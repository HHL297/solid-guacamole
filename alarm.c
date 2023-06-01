#include "hand_tble.h" 


ALARM alarm;
ALARM2 alarm2;

WORK_FLAG work_flag;
SYMBOL symbol;

ONEKEY onekey;
ALARM_FLAG Alarm_Flag;

GB_ALARM_FLAG gb_alarm_flag,gb_alarm_flag_back;
GB_ALARM_ERR  gb_alarm_err,gb_alarm_err_back;


unsigned @near int com_nop;
unsigned @near char com_data;
unsigned @near char com_data_pc = 0x80;
unsigned @near char com_flag; 
unsigned @near int  com_end; 
unsigned @near char com_p_count;
unsigned @near char com_n_count;
unsigned @near int com_start;//yy
unsigned @near char com_stop;

unsigned @near char Send_Data;
unsigned @near int Send_dely;
unsigned @near char Send_Count;
unsigned @near char Send_p_count;
unsigned @near char Send_n_count;




//unsigned @near char alarm_flag;
unsigned @near char voltage_alarm_flag;
unsigned @near int  voltage_off_count;
unsigned @near int  voltage_five_count;
unsigned @near int  voltage_ten_count;
unsigned @near char current_flow_count;

unsigned @near char sf_voltage_count;
unsigned @near char sf_low_count;
unsigned @near char sf_high_count;
unsigned @near char sf_on_count;
unsigned @near char two_err_count;

unsigned @near char speed_err_count;
unsigned @near int  stop_big_count;
unsigned @near char stop_low_count;
unsigned @near char stop_high_count;
unsigned @near char stop_all_count;

unsigned @near char chg_mode_dn_count;
unsigned @near char chg_mode_up_count;
unsigned @near int  chg_mode_alarm_count;
unsigned @near int  power_low_count;
unsigned @near int  power_low_reset_count;
unsigned @near char err_code;
unsigned @near int	voice_dely;
unsigned @near char speed_num_back;
unsigned @near char speed_num_back_count;
unsigned @near char low_power_count;

u8 @near onekey_current_flow_flag;
unsigned char alarm_over_flag = 0;
u16@near onekey_CD_count = 1000;

#ifdef	ONE_KEY_FUN

void com_deal(void)				//2ms
{	
//	if(com_deal_count >= 3)
//	{
	if(com_start > 1)
	{
		com_data = 0x01;
		alarm_flag = 9;
		com_nop = 116;
		VOICE_DN();
		com_data_pc = 0x80;
		com_start --;
		com_end = 1900;					//3s
	}
	else
	{
//			com_deal_count = 0;
		//if(alarm_over_flag == 1)
		//{
			if(alarm_flag == 0)
			{
				if(com_start == 1)
				{
					if(com_stop == 0)
					{
						com_nop = 116;
//					PAOUT &= 0xFE;
						VOICE_DN();
						com_data_pc = 0x80;
						if((alarm.onekeypass & 0x0C) == 0x04)					//	只有hall坏	3 h		0k
						{
							alarm_flag = 1;
							com_data = 0x19;
							alarm.bit.hall_alm_flag = 0;	
							com_end = 3090;					//8s
						}
						else if((alarm.onekeypass  & 0x09) == 0x01)				//	只有刹车坏	1 h		ok
						{
							alarm_flag = 2;
							com_data = 0x03;
							alarm.bit.stop_alm_flag = 0;
							com_end = 2200;					//5s
						}
						else if((alarm.onekeypass & 0x0A) == 0x02)				//	只有把手坏 2 h		ok
						{	
							alarm_flag = 3;
							com_data = 0x04;
							alarm.bit.speed_alm_flag = 0;
							com_end = 2250;					//5s
						}
						else if(alarm.bit.two_alm_flag == 1)					//	多种坏	5s
						{
							alarm_flag = 4;
							com_data = 0x05;
							alarm.bit.two_alm_flag = 0;
							com_end = 4400;					//10s
						}
				
						else if(alarm.bit.ten_km_flag == 1)						//10km路程
						{
							alarm_flag = 6;
							com_data = 0x02;
							alarm.bit.ten_km_flag = 0;
							com_end = 2650;					//4s
						}
						else if(alarm.bit.five_km_flag == 1)					//5km路程
						{
							alarm_flag = 7;	
							com_data = 0x1f;
							alarm.bit.five_km_flag = 0;
							com_end = 2650;					//4s
						}
						else if(alarm.bit.low_voltage_flag == 1)			 	//欠压
						{
							alarm_flag = 8;
							com_data = 0x11;
							alarm.bit.low_voltage_flag = 0;
							com_end = 2650;					//4s
						}
					
						else if(alarm.bit.repair_flag == 1)						//需要修理		5s
						{
							alarm_flag = 5;
							com_data = 0x0b;
							alarm.bit.repair_flag = 0;
							onekey_current_flow_flag = 1;
							com_nop = 116;
//						PAOUT &= 0xFE;
							VOICE_DN();
							com_data_pc = 0x80;
							com_end = 4400;					//10s
						}
					}
					else
					{
						if(alarm.bit.repair_flag == 1)						//需要修理		5s
						{
							alarm_flag = 5;
							com_data = 0x0b;
							alarm.bit.repair_flag = 0;
							onekey_current_flow_flag = 1;
							com_nop = 116;
//						PAOUT &= 0xFE;
							VOICE_DN();
							com_data_pc = 0x80;
							com_end = 4400;					//10s
						}
						else 
							alarm.onekeypass = 0;
					}
				}
				else if(com_start == 0)
				{
					if(com_stop == 0)
					{
						com_nop = 116;
	//					PAOUT &= 0xFE;
						VOICE_DN();
						com_data_pc = 0x80;
						if(alarm.bit.ten_km_flag == 1)						//10km路程
						{
							alarm_flag = 6;
							com_data = 0x02;
							alarm.bit.ten_km_flag = 0;
							com_end = 2650;					//4s
						}
						else if(alarm.bit.five_km_flag == 1)					//5km路程
						{
							alarm_flag = 7;	
							com_data = 0x1f;
							alarm.bit.five_km_flag = 0;
							com_end = 2650;					//4s
						}
						else if(alarm.bit.low_voltage_flag == 1)			 	//欠压
						{
							alarm_flag = 8;
							com_data = 0x11;
							alarm.bit.low_voltage_flag = 0;
							com_end = 2650;					//4s
						}
						else if(alarm.bit.repair_flag == 1)						//需要修理		5s
						{
							alarm_flag = 5;
							com_data = 0x0b;
							alarm.bit.repair_flag = 0;
							onekey_current_flow_flag = 1;
							com_nop = 116;
//						PAOUT &= 0xFE;
							VOICE_DN();
							com_data_pc = 0x80;
							com_end = 4400;					//10s
						}
					}
				}
			}
		//}
		
		if(alarm_flag != 0)
		{	
			if(com_flag == 0)
			{
				if(com_nop > 75)										//空闲位
					com_nop --;
				else if(com_nop > 64)									//起始位
				{
//						PAOUT |= 0x01;
					VOICE_UP();
					com_nop --;
				}
				else if((com_nop & 0x03) == 0)
				{
					if(com_nop > 0)
					{
						com_nop --;							
//							PAOUT &= 0xFE;
						VOICE_DN();
						if((com_data_pc & com_data) == 0)
						{
							com_p_count = 1;
							com_n_count = 2;
						}
						else
						{
							com_p_count = 3;
							com_n_count = 0;
						}
						com_data_pc = (com_data_pc >> 1);
						if(com_data_pc == 0)
							com_data_pc = 0x80;

					}
					else
					{
//							PAOUT &= 0xFE;
						VOICE_DN();
						com_flag = 1;
//							com_end = 4500;					//10s
					}
				}
				else
				{
					if(com_n_count > 0)
						com_n_count --;
					else if(com_p_count > 0)
					{
//							PAOUT |= 0x01;
						VOICE_UP();
						com_p_count --;
					}
					com_nop --;
				}
			}
			else
			{	
				if(com_end > 0)
					com_end --;
				else
				{
					com_flag = 0;
					alarm_flag = 0;
					//alarm_over_flag = 1;    //  cl 2012.4.16
					//com_wait = 2500;

					com_nop = 116;
					VOICE_DN();
					com_data_pc = 0x80;
					com_end = 4400;					//10s
				}
			}
		}
	}
}
/*
void com_deal(void)
{	
	if(com_start >0)
	{
		com_data = 0x01;
		Alarm_Flag.bit.alarm_busy = 1;
		com_start --;
		com_end = 1900;					//3s
	}
	else
	{
		if(Alarm_Flag.bit.alarm_busy == 0)
		{
			if(com_stop == 0)
			{
				if((alarm.onekeypass & 0x0C) == 0x04)					//	只有hall坏	3 h		0k
				{
					Alarm_Flag.bit.alarm_busy = 1;
					com_data = 0x19;
					alarm.bit.hall_alm_flag = 0;	
					com_end = 3090;					//8s
				}
				else if((alarm.onekeypass & 0x09) == 0x01)				//	只有刹车坏	1 h		ok
				{
					Alarm_Flag.bit.alarm_busy = 1;
					com_data = 0x03;
					alarm.bit.stop_alm_flag = 0;
					com_end = 2200;					//5s
				}
				else if((alarm.onekeypass & 0x0A) == 0x02)				//	只有把手坏 2 h		ok
				{	
					Alarm_Flag.bit.alarm_busy = 1;
					com_data = 0x04;
					alarm.bit.speed_alm_flag = 0;
					com_end = 2250;					//5s
				}
				else if(alarm.bit.two_alm_flag == 1)					//	多种坏	5s
				{
					Alarm_Flag.bit.alarm_busy = 1;
					com_data = 0x05;
					alarm.bit.two_alm_flag = 0;
					com_end = 4400;					//10s
				}
				else if(alarm.bit.ten_km_flag == 1)						//10km路程
				{
					Alarm_Flag.bit.alarm_busy = 1;
					com_data = 0x02;
					alarm.bit.ten_km_flag = 0;
					com_end = 2650;					//4s
				}
				else if(alarm.bit.five_km_flag == 1)					//5km路程
				{
					Alarm_Flag.bit.alarm_busy = 1;
					com_data = 0x1f;
					alarm.bit.five_km_flag = 0;
					com_end = 2650;					//4s
				}
				else if(alarm.bit.low_voltage_flag == 1)			 	//欠压
				{
					Alarm_Flag.bit.alarm_busy = 1;
					com_data = 0x11;
					alarm.bit.low_voltage_flag = 0;
					com_end = 2650;					//4s
				}
				else if(alarm.bit.repair_flag == 1)						//需要修理		5s
				{
					Alarm_Flag.bit.alarm_busy = 1;
					com_data = 0x0b;
					alarm.bit.repair_flag = 0;
				//	com_nop = 116;
				//	VOICE_DN();
				//	com_data_pc = 0x80;
					com_end = 4400;					//10s
				}
			}
			else
			{
				if(alarm.bit.repair_flag == 1)						//需要修理		5s
				{
					Alarm_Flag.bit.alarm_busy = 1;
					com_data = 0x0b;
					alarm.bit.repair_flag = 0;
			//		com_nop = 116;
			//		VOICE_DN();
			//		com_data_pc = 0x80;
					com_end = 4400;					//10s
				}
				else 
					alarm.onekeypass = 0;
			}
		}
		else
		{	
			alarm_data_send(com_data,com_end >> 6);
		}
	}
}
*/
/////////////////////////////////////////////////////////
unsigned char alarm_data_send(unsigned char prsend_data,unsigned char alarm_time)		//100ms
{
	if(Alarm_Flag.bit.bit_busy == 0)
	{
		if(Alarm_Flag.bit.send_ok > 0)
		{
			if(Send_dely > 0)
				Send_dely --;
			else
			{
				Alarm_Flag.bit.send_ok = 0;
				Alarm_Flag.bit.alarm_busy = 0;
				Send_Count = 0;
			}
		}
		else
		{
			if(Send_Count == 0)
			{
				Alarm_Flag.bit.alarm_busy = 1;
				Alarm_Flag.bit.bit_busy = 1;
				Alarm_Flag.bit.start_bit = 1;
				com_data_pc = 0x80;
				Send_Data = prsend_data;
				Send_dely = alarm_time * 64;
				Send_p_count = 131;			//
				VOICE_DN();
			}
			else
			{
				Alarm_Flag.bit.start_bit = 0;
				Alarm_Flag.bit.bit_busy = 1;
				if(Send_Count == 9)
					com_data_pc = 0x80;
					
				Send_p_count = 3;
				
				if((com_data_pc & Send_Data) > 0)
				{
					Alarm_Flag.bit.bit_flag = 1;
				}
				else
				{
					Alarm_Flag.bit.bit_flag = 0;
				}
				com_data_pc = (com_data_pc >> 1);
				if(Send_Count > 16)
				{
					Send_Count = 0;
					Alarm_Flag.bit.bit_busy = 0;
					Alarm_Flag.bit.send_ok = 1;
				}			
			}
			Send_Count ++;
		}
	}
//	send_bit();
}
///////////////////////////////////////////////////////////
void send_bit(void)
{
	if(Alarm_Flag.bit.bit_busy > 0)
	{
		if(Alarm_Flag.bit.start_bit > 0)
		{
			if(Send_p_count >= 12)				//
			{
				VOICE_DN();
				Send_p_count --;
			}
			else
			{
				if(Send_p_count > 0)
				{
					Send_p_count --;
					VOICE_UP();
				}
				else
				{
					Alarm_Flag.bit.bit_busy = 0;
				}
			}
		}
		else
		{
			if(Send_p_count >= 3)
			{
				VOICE_DN();
				Send_p_count --;
			}
			else if((Send_p_count == 2) || (Send_p_count == 1))
			{
				Send_p_count --;
				if(Alarm_Flag.bit.bit_flag > 0)
					VOICE_UP();
				else
					VOICE_DN();
			}
			else if(Send_p_count == 0)
			{
				VOICE_UP();
				Alarm_Flag.bit.bit_busy = 0;
			}
			else
			{
				Alarm_Flag.bit.bit_busy = 0;
				VOICE_DN();
			}
		}
	}
	else
	{
		Send_p_count = 0;
		Send_n_count = 0;
		VOICE_DN();
	}
}
////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
void voltage_low_alarm(void)
{
	if(voltage_alarm_flag < 4)
	{
		voltage_off_count = 0;
		if(voltage_average < (user_Prdata.byte.voltage_adj + (user_Prdata.byte.voltage_adj >> 5) + 4))				//43V
		{	
			voltage_ten_count = 0;
			if(voltage_five_count < 400)		//8s
				voltage_five_count ++;
			else
			{
				voltage_five_count = 0;
				alarm.bit.five_km_flag = 1;
				if(voltage_alarm_flag < 3)
					voltage_alarm_flag = 3;
				else
					voltage_alarm_flag = 4;
			}
		}
		else if((voltage_average < (user_Prdata.byte.voltage_adj + (user_Prdata.byte.voltage_adj >> 4))) && (voltage_alarm_flag < 2))		//46V
		{
			voltage_five_count = 0;
			if(voltage_ten_count < 400)		//8s
				voltage_ten_count ++;
			else 
			{
				voltage_ten_count = 0;
				alarm.bit.ten_km_flag = 1;
				voltage_alarm_flag = 2;
			}
		}
		else 
		{
			voltage_ten_count = 0;
			voltage_five_count = 0;
		}
	}
	else if(current_v < user_Prdata.byte.current_adj)//(voltage_average <= voltage_adj)
	{
		if(voltage_off_count < 400)			//4s
			voltage_off_count ++;
		else 
		{
			if(voltage_alarm_flag < 5)				
				alarm.bit.low_voltage_flag = 1;
			voltage_alarm_flag = 5;
		}
	}
	else 
	{
		voltage_off_count = 0;
		voltage_ten_count = 0;
		voltage_five_count = 0;
	}
}
////////////////////////////////////////
////////////////////////////////////刹车故障////////////////////////////////////////////
void brake_err(void)
{
	if(sys_state_flag.bit.brk_flag > 0 )			//刹车
	{
		if(sys_state_flag2.bit.start_flag == 0)
		{
//			if(onekey.bit.speed_err_flag == 0)
//			{
				stop_big_count = 0;
				if(onekey.bit.stop_err_flag == 0)
				{
					if(current_cmd_average > 20)
					{
						stop_high_count = 0;
						if(symbol.bit.stop_high_flag == 0)
						{
							if(stop_low_count < 15)					//15*36*63= 34ms
								stop_low_count ++;
							else
								symbol.bit.stop_high_flag = 1;
						}
					}
					else
					{
						stop_low_count = 0;
						if(symbol.bit.stop_high_flag == 1)
						{
							if(stop_high_count < 15)				//15*36*63= 34ms
								stop_high_count ++;
							else
							{
								symbol.bit.stop_high_flag = 0;
								stop_all_count ++;
							}
						}
					}
					
					if(stop_all_count >= 8)				//刹车故障计数
					{
						if(onekey.err == 0)
						{
							onekey.bit.stop_err_flag = 1 ;
							alarm.bit.stop_alm_flag =1 ;
						}
						else if((onekey.bit.two_err_flag == 0) && (onekey.bit.stop_err_flag == 0))
						{
							onekey.err |= 0x09;
							alarm.onekeypass &= 0xF8;
							alarm.bit.two_alm_flag = 1;
						}
						else 
						{
							onekey.bit.stop_err_flag = 1 ;
							alarm.bit.stop_alm_flag =1 ;
						}
					}
				}
//			}
			/*
			else
			{
				if(onekey.bit.stop_err_flag == 0)
				{
					if(stop_big_count < 750)			//3s
						stop_big_count ++;
					else
					{
						onekey.bit.stop_err_flag = 1;
						if(onekey.bit.two_err_flag == 0)
						{
							onekey.bit.two_err_flag = 1;
							alarm.onekeypass &= 0xF8;
							alarm.bit.two_alm_flag = 1;
						}
					}
				}
				else  
					stop_big_count = 0;
			}
			*/
		}
	}
	else
	{
		symbol.bit.stop_high_flag = 0;
		stop_low_count = 0;
		stop_high_count = 0;
		stop_all_count = 0;
		stop_big_count = 0;
	}
	/*
	if(onekey.bit.stop_err_flag == 1)
	{
		sys_state_flag.bit.brk_flag = 0;
		sys_state_flag.bit.brake_charge_flag = 0;
	}
	*/
}
void brake_err_2J(void)		//NF
{
	
	if(sys_state_flag.bit.brk_flag == 1 )			//刹车
	{
		if(onekey.bit.stop_err_flag == 0)
		{
			if(onekey.err == 0)
			{
				onekey.bit.stop_err_flag = 1 ;
				alarm.bit.stop_alm_flag = 1;
				com_start = 0;
			}
			else if(onekey.bit.two_err_flag == 0)
			{
				onekey.err |= 0x09;
				alarm.onekeypass &= 0xF8;
				alarm.bit.two_alm_flag = 1;
				com_start = 0;
			}
			else 
			{
				onekey.bit.stop_err_flag = 1 ;
			}
		}
	}
}

/////////////////////////////////////////把手故障///////////////////////
void handle_err(void)
{
	if((control_temp < 50)||(control_temp > 980))
	{
		if(onekey.bit.speed_err_flag == 0 )
		{
			if(speed_err_count < 50 )			//	40ms
			{
				speed_err_count ++ ;
			}
			else
			{
				if(onekey.err == 0)
				{
					onekey.bit.speed_err_flag = 1 ;
					alarm.bit.speed_alm_flag =1 ;
					com_start = 0;
				}
				else if((onekey.bit.two_err_flag == 0) && (onekey.bit.speed_err_flag == 0))
				{
					onekey.err |= 0x0A;
					alarm.onekeypass &= 0xF8;
					alarm.bit.two_alm_flag = 1;
					com_start = 0;
				}
				else 
				{
					onekey.bit.speed_err_flag = 1;
				}
			}
		}			
	}
	else
	{
		//onekey.bit.speed_err_flag = 0;
		speed_err_count = 0;
	}
	
	if((symbol.bit.sf_op_flag == 1) && (com_flag == 0) && (com_start == 1))
	{
		work_flag.bit.speed = onekey.bit.speed_err_flag;
		work_flag.bit.stop = onekey.bit.stop_err_flag;
	}
	else
	{
		work_flag.bit.speed = 0;
		work_flag.bit.stop = 0;
	}
	
	if(onekey.err != work_flag.vicor)
		current_cmd_average_key = 0;
	else if((work_flag.bit.speed == 1) || (work_flag.bit.stop == 1) )
		current_cmd_average_key = 190;
	else
		current_cmd_average_key = 0;
		
	if(debug_mode_flag > 0)
	{
		onekey.bit.hall_err_flag = 0;
		sys_state_flag.bit.hall_exit = 1;
		work_flag.bit.hall = 0;
		square_sine_change_flag = 1;
		error_bank.bit.hall_wron_flag = 0;
		com_start = 1;
	}
}

//////////////////////////////////////////////////

void one_key_chk(void)
{
	if(onekey.err != 0)
	{
		if(ONE_KEY_PORT > 0)
		{
			if(symbol.bit.sf_op_flag == 1)
			{
				if(sf_low_count < 20)
					sf_low_count ++;
				else
				{
					sf_high_count = 0;
					symbol.bit.sf_op_flag = 0;
					if(onekey.bit.two_err_flag == 1)
					{	
						if(work_flag.bit.two == 0)
						{
							if(two_err_count >= 3)
							{
								work_flag.vicor = onekey.err;				//
								if(onekey.bit.hall_err_flag == 1)
								{
									work_flag.bit.hall = 1;			//只是霍尔坏	
									error_bank.bit.hall_wron_flag = 0;									
								}
							}
						}
					}
					else if(onekey.bit.hall_err_flag == 1)
					{	
						if(work_flag.bit.hall == 0)
						{
							if(sf_on_count >= 2)
							{
								work_flag.vicor = 0x04 ;			//只是霍尔坏	
								error_bank.bit.hall_wron_flag = 0;
							}
						}
					}
					
					brake_err_2J();
					if(com_start == 0)
						com_start = 72;
				}
			}
		}
		else
		{
			if(symbol.bit.sf_op_flag == 0)
			{
				if(sf_high_count < 20)
					sf_high_count ++;
				else
				{
					sf_low_count = 0;
					symbol.bit.sf_op_flag = 1;
					if(com_start == 1)
					{
						if(onekey.bit.two_err_flag == 1)
						{
							sf_on_count = 0;
							if(two_err_count < 3)
								two_err_count ++;
						}
						else if(onekey.bit.hall_err_flag == 1)
						{
							two_err_count = 0;
							if(sf_on_count < 3)
								sf_on_count ++;
						}
						else
						{
							sf_on_count = 0;
							two_err_count = 0;
						}
					}
				}
			}
		}
	}	
	else
	{
		if(ONE_KEY_PORT > 0)
		{
			sf_high_count = 0;
			if(onekey_CD_count < 1000)
				onekey_CD_count ++;
			if(symbol.bit.sf_op_flag == 1)
			{
				if(sf_low_count < 6)
					sf_low_count ++;
				else
				{
					symbol.bit.sf_op_flag = 0;
					
					brake_err_2J();
					if(com_start <= 1)
						com_start = 72;
				}
			}
		}
		else
		{
			sf_low_count = 0;
			if(symbol.bit.sf_op_flag == 0)
			{
				if(sf_high_count < 6)
					sf_high_count ++;
				else
				{
					if(onekey_CD_count == 1000)
					{
						onekey_CD_count = 0;
						symbol.bit.sf_op_flag = 1;
					}
				}
			}
		}
	}
}

#endif



///////////////////////////////////////////////////////////////////////
void speed_chg_chk(void)
{

	
}

////////////////////////////////////////////////////////
void speed_chg_alarm(void)				//100ms
{

}


/////////////////////////////////////////////////////

#ifdef GB_ALARM_VOICE

void GB_ALARM(void)
{
	if((sys_state_flag2.bit.GB_alarm_start > 0) && (sys_state_flag2.bit.start_flag == 0))
	{
		com_start ++;
		if(com_start < 47)
		{
			sys_state_flag2.bit.GB_alarm_busy = 1;
			com_nop = 0;
			if(com_start & 0x01)
			{
				VOICE_UP();
			}
			else
			{
				VOICE_DN();
			}
		}
		else if(com_start < 110)
		{
			VOICE_DN();
		}
		else
		{
			if(sys_state_flag2.bit.GB_alarm_busy > 0)
			{
				if(com_start & 0x01)
				{
					VOICE_UP();
				}
				else
				{
					VOICE_DN();
					com_n_count ++;
					if(com_n_count > err_code)			//语音编码
					{
						com_n_count = 0;
						com_nop = 0;
						sys_state_flag2.bit.GB_alarm_busy = 0;
					}
				}
			}
			else
			{
				VOICE_DN();
				com_nop ++;
				if(com_start > 65530)
					com_start = 65530;
				if(com_nop > voice_dely)				//语音报读延时
				{
					com_nop = 0;
					com_start = 0;
					sys_state_flag2.bit.GB_alarm_start = 0;
				}
			}
		}
	}
	else
	{
		com_start = 0;
		VOICE_DN();
	}
}


///////////////////////////////////////////////////////////////////
void GB_alarm_drive(void)				//
{
	if((sys_state_flag2.bit.GB_alarm_start == 0) && (sys_state_flag2.bit.GB_alarm_busy == 0))
	{
		if((gb_alarm_err.all_flag > 0) || (gb_alarm_flag.all_flag > 0))
		{
			sys_state_flag2.bit.GB_alarm_start = 1;
			if(sys_start_time < 50)
				voice_dely = 4000;
			else
				voice_dely = 1000;
		}
			
		if(gb_alarm_err.bit.no_err > 0)
		{
			gb_alarm_err.bit.no_err = 0;
			err_code = NO_ERR;
		//	voice_dely = 20;
		}
		else if(gb_alarm_err.bit.more_err > 0)
		{
			gb_alarm_err.bit.more_err = 0;
			err_code = TOW_ERR;
		//	voice_dely = 20;			
		}
		else if(gb_alarm_err.bit.hand_flag > 0)
		{
			gb_alarm_err.bit.hand_flag = 0;
			err_code = HAND_ERR;
		//	voice_dely = 20;				
		}		
		else if(gb_alarm_err.bit.controller_flag > 0)
		{
			gb_alarm_err.bit.controller_flag = 0;
			err_code = CONTROLLER_ERR;
		//	voice_dely = 20;				
		}		
		else if(gb_alarm_err.bit.brake_flag > 0)
		{
			gb_alarm_err.bit.brake_flag = 0;
			err_code = BREAK_ERR;
		//	voice_dely = 20;				
		}
		else if(gb_alarm_err.bit.hall_flag > 0)
		{
			gb_alarm_err.bit.hall_flag = 0;
			err_code = HALL_ERR;
		//	voice_dely = 20;				
		}		
		else if(gb_alarm_err.bit.motor_flag > 0)
		{
			gb_alarm_err.bit.motor_flag = 0;
			err_code = MOTOT_ERR;
		//	voice_dely = 20;				
		}
		else if(gb_alarm_err.bit.low_power > 0)
		{
			gb_alarm_err.bit.low_power = 0;
			err_code = LOW_POWER;
		//	voice_dely = 20;				
		}		
		else if(gb_alarm_err.bit.voltage_low_flag > 0)
		{
			gb_alarm_err.bit.voltage_low_flag = 0;
			err_code = VOLTAGE_ERR;
		//	voice_dely = 20;			
		}
		else if(gb_alarm_flag.bit.sf_flag > 0)
		{
			gb_alarm_flag.bit.sf_flag = 0;
			err_code = SF_FLAG;
		//	voice_dely = 20;				
		}
		else if(gb_alarm_flag.bit.low_speed > 0)
		{
			gb_alarm_flag.bit.low_speed = 0;
			err_code = LOW_SPEED;
		//	voice_dely = 20;				
		}
		else if(gb_alarm_flag.bit.mid_speed > 0)
		{
			gb_alarm_flag.bit.mid_speed = 0;
			err_code = MID_SPEED;
		//	voice_dely = 20;			
		}
		else if(gb_alarm_flag.bit.hight_speed > 0)
		{
			gb_alarm_flag.bit.hight_speed = 0;
			err_code = HIGHT_SPEED;
		//	voice_dely = 20;				
		}
		else if(gb_alarm_flag.bit.hight2_speed > 0)
		{
			gb_alarm_flag.bit.hight2_speed = 0;
			err_code = HIGHER_SPEED;
		//	voice_dely = 20;				
		}
		else if(gb_alarm_flag.bit.abs_flag > 0)
		{
			gb_alarm_flag.bit.abs_flag = 0;
			err_code = ABS_FLAG;
		//	voice_dely = 20;				
		}
		else if(gb_alarm_flag.bit.no_power > 0)
		{
			gb_alarm_flag.bit.no_power = 0;
			err_code = NO_POWER;
		//	voice_dely = 20;				
		}
		else if(gb_alarm_flag.bit.e_drive > 0)
		{
			gb_alarm_flag.bit.e_drive = 0;
			err_code = E_DRIVER;
		//	voice_dely = 20;				
		}
		else if(gb_alarm_flag.bit.spt_drive > 0)
		{
			gb_alarm_flag.bit.spt_drive = 0;
			err_code = SPT_DRIVER;
		//	voice_dely = 20;				
		}
		else if(gb_alarm_flag.bit.back_drive > 0)
		{
			gb_alarm_flag.bit.back_drive = 0;
			err_code = BACK_DRIVER;
		//	voice_dely = 20;				
		}
		else 
		{
			gb_alarm_err.all_flag = 0;
			gb_alarm_flag.all_flag = 0;
			sys_state_flag2.bit.GB_alarm_start = 0;
		}
	}
}



//////////////////////////////////////////////////////////////////
void GB_alarm_flag(void)
{
	if(sys_state_flag2.bit.start_flag > 0)
	{
		if(sys_state_flag.bit.brk_flag > 0)
		{
			if(gb_alarm_err_back.bit.brake_flag == 0)
			{
				gb_alarm_err.bit.brake_flag = 1;
				gb_alarm_err_back.bit.brake_flag = 1;
			}			
		}
		else if(sys_start_time == 5)
		{
			if((error_bank.all_flag == 0) && (sys_state_flag.bit.protect_flag == 0) && (sys_state_flag.bit.brk_flag == 0))
			{
				if(gb_alarm_err_back.bit.no_err == 0)
				{
					gb_alarm_err.bit.no_err = 1;
					gb_alarm_err_back.bit.no_err = 1;
				}					
			}
		}
	}
	else
	{
		/*
		if(speed_num != speed_num_back)
		{
			speed_num_back_count ++;
			if(speed_num_back_count > 20)
			{
				speed_num_back_count = 20;
				speed_num_back = speed_num;
				if(speed_num == 0)
				{
					if(gb_alarm_flag_back.bit.low_speed == 0)
					{
						gb_alarm_flag.bit.low_speed = 1;
						gb_alarm_flag_back.bit.low_speed = 1;
						
					//	gb_alarm_flag_back.bit.low_speed = 0;
						gb_alarm_flag_back.bit.mid_speed = 0;
						gb_alarm_flag_back.bit.hight_speed = 0;
						gb_alarm_flag_back.bit.hight2_speed = 0;						
					}					
				}
				else if(speed_num == 1)
				{
					if(gb_alarm_flag_back.bit.mid_speed == 0)
					{
						gb_alarm_flag.bit.mid_speed = 1;
						gb_alarm_flag_back.bit.mid_speed = 1;
						
						gb_alarm_flag_back.bit.low_speed = 0;
					//	gb_alarm_flag_back.bit.mid_speed = 0;
						gb_alarm_flag_back.bit.hight_speed = 0;
						gb_alarm_flag_back.bit.hight2_speed = 0;						
					}					
					
				}
				else if(speed_num == 2)
				{
					if(gb_alarm_flag_back.bit.hight_speed == 0)
					{
						gb_alarm_flag.bit.hight_speed = 1;
						gb_alarm_flag_back.bit.hight_speed = 1;
						
						gb_alarm_flag_back.bit.mid_speed = 0;
						gb_alarm_flag_back.bit.low_speed = 0;
					//	gb_alarm_flag_back.bit.hight_speed = 0;
						gb_alarm_flag_back.bit.hight2_speed = 0;
					}					
				}
				else if(speed_num == 3)
				{
					if(gb_alarm_flag_back.bit.hight2_speed == 0)
					{
						gb_alarm_flag.bit.hight2_speed = 1;
						gb_alarm_flag_back.bit.hight2_speed = 1;
						
						gb_alarm_flag_back.bit.low_speed = 0;
						gb_alarm_flag_back.bit.mid_speed = 0;
						gb_alarm_flag_back.bit.hight_speed = 0;
					//	gb_alarm_flag_back.bit.hight2_speed = 0;						
					}					
				}
				else
				{
						gb_alarm_flag_back.bit.low_speed = 0;
						gb_alarm_flag_back.bit.mid_speed = 0;
						gb_alarm_flag_back.bit.hight_speed = 0;
						gb_alarm_flag_back.bit.hight2_speed = 0;					
				}
			}
		}
		else
		{
			speed_num_back_count = 0;
		}
		*/
		
		if((sys_state_flag.bit.brake_charge_flag > 0) && (speed_motor2 < 100) && (pwm_duty_brake > 20))
		{
			if(gb_alarm_flag_back.bit.abs_flag == 0)
			{
				gb_alarm_flag.bit.abs_flag = 1;
				gb_alarm_flag_back.bit.abs_flag = 1;
			}
		}
		else 
		{
			if(sys_state_flag.bit.brk_flag == 0)
				gb_alarm_flag_back.bit.abs_flag = 0;
		}
		
		if((sys_state_flag.bit.spt_flag > 0) && (pwm_duty_on1 > 200) && (error_bank.all_flag == 0))
		{
			if(gb_alarm_flag_back.bit.spt_drive == 0)
			{
				gb_alarm_flag.bit.spt_drive = 1;
				gb_alarm_flag_back.bit.spt_drive = 1;
			}
		}
		else
		{
			gb_alarm_flag_back.bit.spt_drive = 0;
		}
		
		if(sys_state_flag.bit.sf_flag > 0)
		{
			if(gb_alarm_flag_back.bit.sf_flag == 0)
			{
				gb_alarm_flag.bit.sf_flag = 1;
				gb_alarm_flag_back.bit.sf_flag = 1;
			}		
		}
		else
		{
			gb_alarm_flag_back.bit.sf_flag = 0;
		}
	}	
}

////////////////////////////////////////////////
void GB_alarm_err(void)
{
	if(sys_start_time < 250)
		sys_start_time ++;
		
	if(sys_state_flag2.bit.start_flag > 0)
	{
		if(sys_start_time > 10)
			sys_state_flag2.bit.start_flag = 0;
	}
	
	if((error_bank.all_flag > 0) || (sys_state_flag.bit.protect_flag > 0))
	{
		if(sys_state_flag.bit.protect_flag > 0)								//把手故障
		{
			if(gb_alarm_err_back.bit.hand_flag == 0)
			{
				gb_alarm_err.bit.hand_flag = 1;
				gb_alarm_err_back.bit.hand_flag = 1;
			}
		}
		else
		{
			gb_alarm_err_back.bit.hand_flag = 0;
		}
		
		if(error_bank.bit.current_flow_flag > 0)			//控制器故障
		{
			if(gb_alarm_err_back.bit.controller_flag == 0)
			{
				gb_alarm_err.bit.controller_flag = 1;
				gb_alarm_err_back.bit.controller_flag = 1;
			}
		}
		else
		{
			gb_alarm_err_back.bit.controller_flag = 0;
		}
		
		if(error_bank.bit.hall_wron_flag > 0)					//霍尔报警
		{
			if(gb_alarm_err_back.bit.hall_flag == 0)
			{
				gb_alarm_err.bit.hall_flag = 1;
				gb_alarm_err_back.bit.hall_flag = 1;
			}			
		}
		else
		{
			gb_alarm_err_back.bit.hall_flag = 0;
		}
		
		if(error_bank.bit.ph_lost_flag > 0)						//电机缺相
		{
			if(gb_alarm_err_back.bit.motor_flag == 0)
			{
				gb_alarm_err.bit.motor_flag = 1;
				gb_alarm_err_back.bit.motor_flag = 1;
			}				
		}
		else
		{
			gb_alarm_err_back.bit.motor_flag = 0;
		}

		if(error_bank.bit.voltage_low_flag > 0)					//欠压保护
		{
			if(gb_alarm_err_back.bit.voltage_low_flag == 0)
			{
				gb_alarm_err.bit.voltage_low_flag = 1;
				gb_alarm_err_back.bit.voltage_low_flag = 1;
			}				
		}
		else
		{
			if(voltage_average > (user_Prdata.byte.voltage_adj + (user_Prdata.byte.voltage_adj >> 3)))			//47V
				gb_alarm_err_back.bit.voltage_low_flag = 0;
		}
		
		if(voltage_average < (user_Prdata.byte.voltage_adj + (user_Prdata.byte.voltage_adj >> 4)))				//44.5V
		{
			low_power_count ++;
			if(low_power_count > 30)
			{
				low_power_count = 30;
				if(gb_alarm_err_back.bit.low_power == 0)
				{
					gb_alarm_err.bit.low_power = 1;
					gb_alarm_err_back.bit.low_power = 1;
				}					
			}
		}
		else
		{
			low_power_count = 0;
			if(voltage_average > (user_Prdata.byte.voltage_adj + (user_Prdata.byte.voltage_adj >> 3)))				//47V
				gb_alarm_err_back.bit.low_power = 0;			
		}
	}
	else
	{
		gb_alarm_err_back.bit.hand_flag = 0;
		gb_alarm_err_back.bit.controller_flag = 0;
		gb_alarm_err_back.bit.hall_flag = 0;
		gb_alarm_err_back.bit.motor_flag = 0;
			
		if(voltage_average > (user_Prdata.byte.voltage_adj + (user_Prdata.byte.voltage_adj >> 3)))				//47V
		{
			gb_alarm_err_back.bit.low_power = 0;	
			gb_alarm_err_back.bit.voltage_low_flag = 0;	
		}
	}
}

#endif





















