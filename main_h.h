

//硬件版本定义
#define S58


#define sv_pwm_5step

/////////////////////////////////////////////////

////////////////////斩波方式
//#define		DP_PWM		//双侧斩波
//#define		LP_PWM		//同步整流
#define		SV_PWM			//模拟SVPWM
//////////////////////////////////
#ifdef	SV_PWM
	#define		PWM_PER		 128
	#define 	PWM_QTR		 255
	#define 	MAX_PWMDUTY  480
	#define 	MAX_SVPWMDUTY  480
#else
	#ifdef 		LP_PWM
		#define 	MAX_PWMDUTY  480
	#else
		#define 	MAX_PWMDUTY  475
	#endif

#endif
#define u8					unsigned char
#define u16					unsigned int

#define un8					unsigned char @near 
#define un16				unsigned int  @near

#define s8					char
#define s16					int


//****************函数定义区*******************//
void WDT_INI(void);
void OSC_INI(void);
void IO_INI(void);
void AD_INI(void);
void TM1_INI(void);
void TM2_INI(void);
void RAM_INI(void);
void CLP_INI(void);
void OPTIONSET_INI(void);
void adc_channel(void);
void adc_sample(void);
void adc_channle_phcurrent(void);
void adc_sampel_ph(void);
void spt_chk(void);
void brake_chk(void);
void motor_stop(void);
void eeprom_read(void);
void eerprom_write(void);
void dir_sf_mode(void);
void my_time1_ini(void);
void hall_read(void);
void hall_read_first(void);
void motor_drive(void);
void auto_sf(void);
void sf_sel(void);
void sf_sel_6A(void);
void abs_sel(void);
void spt_sel(void);
void pwm_main(void);
void motor_dirve2(void);
void motor_abs(void);
void brake_pwm_duty(void);
void ad_data(void);
void Motor_start_m(void);
void phase_change(unsigned char hall_position_temp);
void phase_lock_change(unsigned char  PR_hall_position_temp);
void PWM_ALL_OFF(void);
void current_num(void);
void dto_lock_drive(void);
void motor_lock_drive(void);
void Low_power0(void);
void Low_power1(void);
void Low_power2(void);
void Low_power3(void);
void Low_power4(void);
void sim_uart_rend(void);
void sim_uart_send(void);
void current_dang_mode(void);
void voltage_chk(void);
void clear_sys_key(void);
void shout_dowm(void);
void one_key_chk(void);
void com_deal(void);
void voltage_low_alarm(void);
void brake_err(void);
void handle_err(void);
unsigned char alarm_data_send(unsigned char prsend_data,unsigned char alarm_time);
void speed_chg_chk(void);
void speed_chg_alarm(void);
void sys_start_main(void);
void GB_ALARM(void);
void GB_alarm_drive(void);
void GB_alarm_err(void);
void GB_alarm_flag(void);
void sin_cos();
void rotor_ver(void);
void svpwm_ver(void);
void sv_cvt_ver(void);
void current_cmd_protect_sample(void);
void MotorStartSub(void);
void eerprom_write_data(void);
void cvt_sel(void);
////////////////////////////////////////////


///////////////////////////////////////////////////////
typedef union
{
	struct
	{
		unsigned NULL:1;
		unsigned TMM4_start_flag :1;
		unsigned sleep_err :1;
		unsigned backup_flag:1;
		
		unsigned LJ_flag:1; //力矩故障
		unsigned hand_flag:1; //转把故障
		
		unsigned sys_key_flag:1;
		unsigned uart_error_flag:1;			//表头错误标记
		unsigned uart_flag:1;				//通讯出错保护		
		unsigned restart_flag:1;			//霍尔状态位
		
		unsigned temperature_flag:1;		//温度保护
		unsigned voltage_over_flag:1;		//过压保护
		unsigned voltage_low_flag:1;		//欠压保护
		unsigned protect_flag:1;			//飞车保护
		
		unsigned hall_wron_flag:1;			//外部HALL出错
		unsigned motor_stop_flag:1;			//堵转保护		
		unsigned ph_lost_flag:1;			//电机缺相		
		unsigned current_flow_flag:1;		//短路保护标记位		
	}bit;
	unsigned int all_flag;
}ERROR_BANK;



typedef union
{
	struct
	{
		unsigned lj_flag :1;
		unsigned lj_speed_limit_flag :1;
		unsigned lj_zero_chk_flag :1; //力矩零位检测标志位
		unsigned spt_flag :1;
		unsigned spt_sel_flag :1;
		unsigned sf_flag :1;
		unsigned sf_sel_flag :1;
		
		unsigned cvt_flag :1;
		unsigned cvt_sel_flag :1;
		unsigned abs_sel_flag :1;
		unsigned brk_flag :1;
		
		unsigned brake_charge_flag :1;
		unsigned hall_exit :1;
		unsigned hall_chang_flag :1;
		unsigned ph_flag:1;
		
		unsigned protect_flag :1;
		unsigned phs_flag :1;
		unsigned current_over_flag :1;
		unsigned phcurrent_over_flag :1;
	}bit;
	unsigned int all_flag;
}SYS_STATE_FLAG;



typedef union
{
	struct
	{
		unsigned EleDir_flag :1;
		unsigned start_flag :1;
		unsigned chg_mode_flag :1;
		unsigned chg_keep_flag :1;
		unsigned chg_mode_cc :1;
		unsigned chg_mode_power_over :1;
		unsigned GB_alarm_start :1;
		unsigned GB_alarm_busy :1;
		unsigned svpwm_flag :1;
		unsigned svpwm_ccw :1;
		unsigned svpwm_drccw :1;
		unsigned svpwm_ver_over :1;
		unsigned hall_change :1;
	}bit;
	unsigned int all_flag;
}SYS_STATE_FLAG2;


typedef union{
	struct{
	//	unsigned char voltage_adj_2;
		unsigned int voltage_adj;
		unsigned int current_adj;
		unsigned char ph_current_adj;
		unsigned int limit_adj;
	}byte;
	unsigned char Table[6];
 }USER_PRDATA;


typedef union{
	struct{
		unsigned sleep_flag :1;
		unsigned pwmduty_flag :1;
		unsigned Mode_flag :1;
		unsigned drive_mode :1;
		unsigned anglage_mode :1;
	}bit;
	unsigned char allflag;
}TMM4_FLAG;

typedef union
{
	struct
	{
		unsigned drive_flag :1;
		unsigned abs_flag :1;
		unsigned alm_flag :1;
		unsigned null:5;
	}bit;
	unsigned char all_flag;
}MOTOR_FLAG;

typedef union
{
	struct
	{
		unsigned drive_flag :1;
		unsigned abs_flag :1;
		unsigned alm_flag :1;
		unsigned lock_flag :1;
		unsigned null:4;
	}bit;
	unsigned char all_flag;
}PWM_MODE;


typedef union{
	struct{
		unsigned char current1;
		unsigned char current2;
		unsigned char current3;
		unsigned char current4;
		unsigned char current5;
	}byte;
	unsigned char table[5];
}CERRENT_TEMP;


typedef union{
	struct 
	{
		unsigned  stop_alm_flag :1;
		unsigned  speed_alm_flag :1;
		unsigned  hall_alm_flag:1;
		unsigned  two_alm_flag:1;
		unsigned  low_voltage_flag:1;
		unsigned  five_km_flag:1;
		unsigned  ten_km_flag:1;
		unsigned  repair_flag:1;
		
	} bit;
	unsigned char onekeypass;
}ALARM;


typedef union{
	struct 
	{
		unsigned  low_power :1;
		unsigned  normal :1;
		unsigned  power :1;
		unsigned  fast  :1;
		unsigned  all_ok :1;
		unsigned  brk_flag :1;
		unsigned  hand_flag :1;	
		unsigned  sys_start :1;
	} bit;
	unsigned char onekeypass;
}ALARM2;


typedef union{
	struct 
	{
		unsigned  stop :1;
		unsigned  speed :1;
		unsigned  hall :1;
		unsigned  two:1;
		unsigned	voltage:1;
		unsigned  :3;
	} bit;
	unsigned char vicor;
}WORK_FLAG;


typedef union{
	struct 
	{
		unsigned  stop_go_flag:1;
		unsigned  stop_high_flag:1;
		unsigned  sf_op_flag :1;
		unsigned  go :1;
		unsigned  sf_go :1;
		unsigned  hall_alm_over :1;
		unsigned  hall_sensor_ok :1;
		unsigned  hall_over :1;
	} bit;
	unsigned char sign;
}SYMBOL;


typedef union{
	struct 
	{
		unsigned  stop_err_flag :1;
		unsigned  speed_err_flag :1;
		unsigned  hall_err_flag :1;
		unsigned  two_err_flag:1;
		unsigned 	voltage_flag:1;
		unsigned  :3;
	} bit;
	unsigned char err;
}ONEKEY;


typedef union{
	struct 
	{
		unsigned  alarm_busy :1;
		unsigned  start_bit  :1;
		unsigned  bit_busy   :1;
		unsigned  bit_flag   :1;
		unsigned  send_ok    :1;
	
		
	} bit;
	unsigned char all_flag;
}ALARM_FLAG;



/////////////////////////////////////////////////////////
typedef union{
	struct 
	{
		unsigned sf_flag:1;//		巡航						10
		unsigned low_speed:1;//		低速						11
		unsigned mid_speed:1;//		中速						12
		unsigned hight_speed:1;//	高速						13
		unsigned hight2_speed:1;//	超高速						14
		unsigned abs_flag:1;//		滑行充电中					15
		unsigned no_power:1;//		健身运动					16
		unsigned e_drive:1;	//		电动						17
		unsigned spt_drive:1;//		助力						18
		unsigned back_drive:1;//	倒车						19
		unsigned fun_alarm:1;
	} bit;
	unsigned int all_flag;
}GB_ALARM_FLAG;

////////////////////////////////////////////////////////
typedef union{
	struct 
	{
		unsigned no_err:1;	//			没有故障					1
		unsigned more_err:1;//			有故障						2
		unsigned hand_flag:1;//			调速把手故障				3
		unsigned controller_flag:1;//	控制器故障					4
		unsigned brake_flag:1;//		刹车故障					5
		unsigned hall_flag:1;//			霍尔故障					6
		unsigned motor_flag:1;//		电机故障					7
		unsigned low_power:1;//			电量不足请充电				8
		unsigned voltage_low_flag:1;//	欠压保护					9
		unsigned err_alarm_falg:1;
	} bit;
	unsigned int all_flag;
}GB_ALARM_ERR;


////////////////////////////////////////////////////////////