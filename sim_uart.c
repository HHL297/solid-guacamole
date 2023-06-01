#include "hand_tble.h" 



TMM4_FLAG TMM4_flag;
CERRENT_TEMP Current_temp;
///////////////////////////////////////

unsigned @near int sleep_count;
unsigned @near int voltage_table[5];
unsigned @near char uart_dan_mode ;
#ifdef	SIM_UART

unsigned @near char uart_dan_back ;
unsigned @near char uart_read_port ;
unsigned @near char uart_read_start ;
unsigned @near char uart_read_data ;
unsigned @near char uart_step ;
unsigned @near char uart_read_count ;
unsigned @near char uart_send_port ;
unsigned @near char uart_send_data ;
unsigned @near char uart_xor_temp ;
unsigned @near char uart_send_dely ;
unsigned @near char current_dang;
unsigned @near char br_flag,br_flag_back,br_count;

///////////////////////////////////////////////////////////////
void sim_uart_send(void)				//1K	扫描
{
	uart_send_dely ++;
	if(uart_send_dely > 100)		//100ms
	{
		if(TMM4_flag.bit.sleep_flag == 1)
		{
			uart_send_data = 0x0e;	
		}
		else
		{
			if(br_flag_back == 0)
			{
				uart_send_data = 0;
			}
			else if(br_flag_back == 1)
			{
				uart_send_data = 0x02;
			}
			else if(br_flag_back == 2)
			{
				uart_send_data = 0x04;			
			}
			else if(br_flag_back == 3)
			{
				uart_send_data = 0x06;
			}
			else if(br_flag_back == 4)
			{
				uart_send_data = 0x08;
			}
			else if(br_flag_back == 5)
			{
				uart_send_data = 0x0a;
			}
			else
			{
				uart_send_data = 0;
			}
		}
		
		if(uart_send_dely == 101)
			uart_send_port = (uart_send_data^0xff);
		if(uart_send_dely == 105)
			uart_send_dely = 0;
	}
	else
	{
		uart_send_port = 0;
	}
	
	if(uart_send_port & 0x10)
	{
		SIM_UART_DN();
	}
	else
	{
		SIM_UART_UP();
	}
	uart_send_port <<=1;
}




//////////////////////////////////////////////////////////////////////////////
void sim_uart_rend(void)				//8K扫描
{
	if(SIM_UART_PORT)
		uart_read_port = 1;				//扫描端口
	else
		uart_read_port = 0;
		
	if(uart_read_start == 0)					//未开始接收数据时，判断是否有起
	{
		if(uart_read_count>0)//延时计数值减到0时才开始扫描端口值
			uart_read_count --;
		else
		{
			if(uart_read_port == 0x00)			//检测数据线讯号，启动接收程序
			{
				if(uart_step > 0)				//连续检测到计数值到达偏移量时确定开始接收数据
					uart_step --;
				else 
				{
					uart_read_start = 1;		//设开始接收数据标记位
					uart_read_count = 0;		//
					uart_xor_temp = 0;
				}
			}
			else
			{
				uart_step = 3;					//复位偏移量 （x）*120us
			}
		}
	}

	if(uart_read_start == 1)
	{
		if(uart_step == 3)						//接收步序为3时开始读数据
		{
			uart_read_count ++;					//接收数据位计数值增加
			if(uart_read_count >=5)				//接收到五位数据时为一次通讯接收
			{
				uart_read_count = 18;			//接收完一次数据后延时 18 个120us 再检测数据线上的信号，防止刚通讯完一次通讯会再次进入通讯
				uart_read_start = 0;			//清楚开始接收标记位
				uart_step = 2;					//设定偏移量= （1+x）*120us
				if(uart_read_data == 0x02)		//数据处理，判断是否正确
				{
					uart_dan_mode = 0;			//第一挡电流
				}
				else if(uart_read_data == 0x04)
				{
					uart_dan_mode = 1;			//第二挡电流
				}
				else if(uart_read_data == 0x06)
				{
					uart_dan_mode = 2;			//第三挡电流
				}
				else if(uart_read_data == 0x08)
				{
					uart_dan_mode = 3;			//第四挡电流
				}
				else if(uart_read_data == 0x0a)
				{
					uart_dan_mode = 4;			//第五挡电流
				}
				else if(uart_read_data == 0x0e)	//取消休眠状态
				{
					error_bank.bit.sleep_err = 0;
				//	TMM4_flag.bit.sleep_flag = 0;
					sleep_count = 0;
				}
				if(uart_dan_back != uart_dan_mode)
				{
					error_bank.bit.sleep_err = 0;
				//	TMM4_flag.bit.sleep_flag = 0;
					sleep_count = 0;
				}
				uart_dan_back = uart_dan_mode;
												//如果数据不正确，保持原来数据不变。
				////////////////////////////////////////
				///////////////////////////////////////
				uart_read_data = 0;				//清除接收到的数据
			}
			else
				uart_read_data <<=1;			//如果没有到达五位数据，将数据向高位移动，以便数据接收完的处理
		}
		uart_step ++;							//接收步序增加
		if(uart_read_start == 1)
		{
			if(uart_step <= 3)
			{
				uart_xor_temp += uart_read_port;
				if(uart_step == 3)
				{
					if(uart_xor_temp == 0x03)
					{
						uart_read_data |= 0x01;
					}
					else if(uart_xor_temp == 0x00)
					{
						uart_read_data &= 0xfe;	
					}
					else
					{
						uart_read_count = 108;			//接收完一次数据后延时 108 个120us 再检测数据线上的信号，防止刚通讯完一次通讯会再次进入通讯
						uart_read_start = 0;			//清楚开始接收标记位
						uart_step = 2;					//设定偏移量= （1+x）*120us
						uart_xor_temp = 0;
					}
				}
			}
			else
			{
				uart_xor_temp = 0;
			}
		}
		if(uart_step == 8)						//接收步序的周期，位 X * 125us   8*125 = 1000 us   
			uart_step = 0;
	}
}

/////////////////////////////////////////////////////
void current_dang_mode(void)
{
	if(uart_dan_mode == 0)   //第一档
	{//1.5A
		current_dang = Current_temp.byte.current1;
	}
	else if(uart_dan_mode == 1)	//第二档
	{//3A
		current_dang = Current_temp.byte.current2;
	}
	else if(uart_dan_mode == 2)	//第三档
	{//6A
		current_dang = Current_temp.byte.current3;
	}
	else if(uart_dan_mode == 3)   //第四档
	{//9A
		current_dang = Current_temp.byte.current4;
	}
	else if(uart_dan_mode == 4)	//第五档
	{//12A
		current_dang = user_Prdata.byte.current_adj;
	}
}
////////////////////////////////////////////////////////

void voltage_chk(void)
{
	if(error_bank.bit.voltage_low_flag == 1)
	{
		br_flag = 0;
	}
	else
	{
		if(voltage_average >= (voltage_table[4]))		//最高挡  5挡
		{
			br_flag = 5;
		}
		else if(voltage_average >= (voltage_table[3]))	//第四挡
		{
			br_flag = 4;
		}
		else if(voltage_average >= (voltage_table[2]))	//第三挡
		{
			br_flag = 3;
		}
		else if(voltage_average >= (voltage_table[1]))	//第二挡
		{
			br_flag = 2;
		}
		else if(voltage_average >= voltage_table[0])	//第一挡
		{
			br_flag = 1;
		}
		else 
		{
			br_flag = 1;
		}
	}
	
	br_count ++;
	if(br_count >= 120)				//
	{
		if(br_flag_back > br_flag)
		{
			br_flag_back --;
		}
		else if(br_flag_back < br_flag)
		{
			br_flag_back ++;
		}
		br_count = 0;
	}
}


#endif


