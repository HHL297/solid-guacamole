extern u8 @near lamp_old_flag;
extern u8 @near lamp_onoff_count;
extern u8@near start_number_rx;
extern u8@near max_speed_limit;
extern u8@near hand_start_level;
extern u16 @near hall_change_count;
extern u16@near hall_count_nohall;
extern u16@near nohall_speed_low_count;
extern u8@near svpwm_rotor_position;
extern u8 cvt_ver_add_count,current_max,current_temp;
extern u8 sys_step,sc_count,sp_zero_count;
extern u16 AD_Value,speed_motor3,ph_current_average1,;
extern unsigned int hand_advalue;
extern unsigned int current_cmd_average,sc_ref;
//extern unsigned int current_cmd_max_duty;
extern unsigned int pwm_duty_on_old,pwm_duty_on;
extern unsigned int pwm_duty_on1,pwm_duty_speed,pwm_duty_brake,pwm_brake_max;
extern unsigned int speed_motor,speed_motor2 ;
extern unsigned char run_flag,back_phcurrent_count,ph_lost_count,controlchg_flag;
extern unsigned char sc_current_count,position_flag,motor_stop_count,mode_flag,debug_mode_flag,motor_stop_count2;//ModeFlag
extern unsigned int  voltage_average,hall_count,step_current;

//extern unsigned int current_cmd_protect_average;
extern unsigned char start_current,current_zero_count,current_max_low_step,ph_current_average;//ph_current_average_back,

extern unsigned int voltage_average_H,current_cmd_protect_average,current_cmd_protect_average,current_cmd_protect_average_dang;
extern unsigned int current_cmd_protect_average1;

extern unsigned char Restart_cont,ph_low_count,speed_dn_count,speed_ok_count,hall_ok_count,ph_low_count_max,current_speed;

extern u8@near current_adj_12,current_limit_pwm_flag;

extern unsigned char pwm_sub_count,pwm_add_count,pwm_cut_count,speed_num;

extern unsigned @near int voltage_adj_table[4];
//extern unsigned char ph_count_table[7];
extern unsigned char rotor_position,hall_drive_back,ModeFlag,Auto_SPT;
extern unsigned int hall_pwm_cont ;
extern unsigned @near int voltage_adj_table49,delay_counter;
extern unsigned @near int voltage_adj_table48;
extern unsigned @near int voltage_adj_table47;
extern unsigned @near int voltage_adj_table46;
extern unsigned @near int voltage_adj_table45;
extern unsigned @near int voltage_adj_table42;
extern unsigned @near int voltage_adj_table54;
extern unsigned @near int current_adj_lowp,current_adj_table[8];
//extern unsigned @near int MAX_P,MAX_protect;
extern unsigned @near int low_current_cmd_protect,speed_motor4,hall_pwm_count4,tim2_cap_count,tim2_count,tim2_speed_count;
extern unsigned @near int ph_pwm_duty_P,ph_pwm_duty_I;
extern unsigned @near char ph_current_adj_table[8];
extern unsigned int delvoltage;
extern unsigned char alarm_switch;
extern unsigned char @near ph_low_count_max_back;
extern unsigned int sf_up_count ;
extern unsigned int @near current_adj_table_add[4];

extern unsigned @near int voltage_table[5];
extern unsigned @near char current_dang,c_offset;
extern unsigned @near int sleep_count;
extern unsigned @near char uart_dan_mode;
extern unsigned @near char flash_count;
extern unsigned @near char current_flow_count;
//extern unsigned char @near protect_flag;
extern unsigned char sys_start_time,CVT_dep;
extern unsigned int control_temp;
extern unsigned int current_cmd_average1,current_cmd_average_key,CVT_hall_count;
extern u8 current_v,rotor_position,rotor_position1,rotor_position2,cvt_rotor_position,cvt_rotor_position_back;
extern unsigned int @near test_control_temp;//JIN
extern unsigned int @near test_current_cmd_protect_average;//JIN
extern unsigned char @near temperature_average;//jin
extern const unsigned char hall_turetable[8];
extern const u8 CVT_VER[256];
extern u8 current_average1;
extern unsigned int current_cmd_spt;
extern u8 eco_flag,current_e;
extern u8@near lv_flash_flag,current_high_flag,current_s,current_s1,current_s2,hall_ver_zero_flag,tim2_6_flag;
extern u16@near pwm_duty_on_ini,tim2_count_6,tim2_speed_count_6,tim2_speed_count_6_save;

extern u8 @near cvt_flag;
extern u8 @near current_adj_18a;
extern u8 @near current_adj_10a;

extern u8@near chall_ver_zero_flag;
extern u16@near hall_pwm_cont_6;
extern u16@near speed_motor_6;
extern u8@near motor_alm_status_lock;
extern u8 current_adj_I;
extern u8 current_adj_II;
extern u8 current_adj_III;
extern u8 @near current_adj_battry;
extern u8 short_count;
extern int @near cvt_ver;
extern u16@near speed_motor_3;
extern u16@near hall_pwm_cont_3;
extern u8@near cvt_on_flag;
extern u8@near power_low45;
extern u8@near power_low42;
extern u8 @near speed_limit_flag2;
extern u16@near current_adj_fifteen;
extern u8 @near square_sine_change_flag,onekey_current_flow_flag;

extern u8 @near motor_current_limit_flag;

extern u8 @near rec_count,hall_ver_last;	//CDPI
extern u16 @near hall_ver_mem,hall_ver_step_act,hall_ver_step,hall_ver_step_act_old;

extern u16 @near hall_ver;

extern u8 @near speed_status_mode;
extern u8 @near first_in_flag;
extern u8 @near cdpi_flag;
extern u8 @near cdpi_count;
extern u8 @near speed_status_on_count;	//CDPI

extern u16 @near hall_ver_step_chase;
extern u16 @near hall_ver_step_delta;
extern u8 @near hall_ver_step_chase_sign;
extern u8 @near mode_360_count;
extern u16 @near hall_ver_step_chase_I;
extern unsigned@near  char alarm_flag,com_flag;
extern unsigned @near int com_start;

extern u8 @near cvt_reg_flag;
extern u8 @near cvt_act_flag;
extern u8 @near cvt_reg_status;
extern u16 @near cvt_speed_motor_6,voltage_average_L,voltage1,voltage2,voltage_average_L1;	//CVT_AI
extern u8 @near cvt_torlance_current;
extern u8 @near cvt_torlance_save ;

extern u8 @near cvt_add,current_3a,voltage_count; // CVT_AIextern unsigned char @near sp_ph_current_limit;
extern unsigned char @near sp_ph_current_limit_max;
extern unsigned char @near sp_ph_current_limit_10p;
extern unsigned char @near sp_ph_current_limit_20p;
extern unsigned char @near sp_ph_current_limit_30p;
extern unsigned char @near sp_ph_current_limit_40p;
extern unsigned char @near sp_ph_current_limit_50p;
extern unsigned char @near sp_ph_current_limit_60p;
extern unsigned char @near sp_ph_current_limit_70p;
extern unsigned char @near sp_ph_current_limit_80p;
extern unsigned char @near sp_ph_current_limit_90p;

extern u16@near yyz_ob;

extern u8@near data_tx[13];//13
extern u8@near data_rx_temp[15];//
extern u8@near data_rx[15];//
extern u8@near data_tx_number ;
extern u8@near dang_limit_current ;
extern u16@near dang_limit_pwm ;
//extern u8@near dang_limit_ratio ;
extern u16@near speed_bike ;
extern u16@near speed_bike_temp ;
extern u8@near limit_current_hand ;
extern u16@near limit_current_speed ;

extern u8@near limit_speed_hall;
extern u16@near limit_speed_hall_1;
extern u8@near limit_speed_hall_2;
extern u16@near limit_speed_hall_delta;

extern u16 @near control_lj_temp_table[2];
extern u16 @near control_lj_zero_table[2];
extern u16 @near current_ph_lj;
extern u16 @near current_ph_lj_old;
extern u16 @near current_ph_lj_delta;
extern u16 @near current_ph_lj_time;
extern u8@near LJ_inc_number;
extern u8@near LJ_dec_number;

extern un16 spt_low_high_count_old ;
extern u16@near spt_low_high_count_old_av;
extern u8@near battry_mode;//0-24 1-36 2-48
extern u8@near test_ratio;
extern u16 @near jp_number;//u8 @near jp_number;
extern u8 @near jp_number_real;
extern u8 @near current_base;
extern u8 @near current_base_real;
extern u8@near data_rx_dang;
extern u16 @near control_lj_temp_old;
extern u8@near run_mode;//0-Á¦¾Ø,1-ËÙ¶È,

extern u8@near speed_8km;
extern u8@near speed_9km;
extern u16@near speed_10km;
extern u8@near speed_11km;
extern u8@near speed_12km;
extern u8@near speed_13km;
extern u8@near speed_14km;
extern u16@near speed_15km;
extern u8@near speed_16km;
extern u8@near speed_17km;
extern u8@near speed_18km;
extern u8@near speed_19km;
extern u16@near speed_20km;
extern u8@near speed_21km;
extern u8@near speed_22km;
extern u8@near speed_23km;
extern u16@near speed_24km;
extern u8@near speed_25km;

extern u8@near current_ph_zero;

extern u16@near voltage_average_sum;
extern u16@near voltage_average_av;
extern u16@near voltage_average_count;

extern u8@near wheel_number;
extern u8@near limit_speed_number;

extern u8 @near hand_no_speed_limit;
extern u8@near send_data_flag;
extern u8@near hand_mode_flag;

/*extern u8 @near curent_base_rx;
extern u8 @near ratio_3km_rx;
extern u8 @near ratio_5km_rx;
extern u8 @near ratio_10km_rx;
extern u8 @near ratio_15km_rx;
extern u8 @near ratio_20km_rx;
extern u8 @near ratio_24km_rx;
extern u8 @near run_mode_rx;*/


/*extern u8 @near power_line_rx;
extern u8 @near magnetic_number_rx;
extern u8 @near start_data_rx;
extern u8 @near speed_slope_rx;
extern u8 @near stop_time_rx;
extern u8 @near motor_model_rx;
extern u8 @near dead_time_rx;*/

extern u8@near send_data_time;

extern u8@near pwm_dang_1;
extern u8@near pwm_dang_2;
extern u8@near pwm_dang_3;
extern u8@near pwm_dang_4;
extern u8@near pwm_dang_5;
extern u8@near pwm_dang_6;

extern u8@near current_dang_1;
extern u8@near current_dang_2;
extern u8@near current_dang_3;
extern u8@near current_dang_4;
extern u8@near current_dang_5;
extern u8@near current_dang_6;

extern u16 @near lj_ad_app;
extern u16 @near control_lj_temp_old_delta;
extern u16 @near current_ph_lj;
extern u16 @near current_lj;
extern u16 @near current_ph_lj_delta;
extern u16 @near current_ph_lj_old;
extern u16 @near lj_zero_auto_corrent_count;
extern u16@near voltage_average_av_quarter;
extern u8 lj_pale_count;
extern u16@near zero_start_number;