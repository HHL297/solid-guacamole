#include "main_h.h"

#include "stm8s105c_s.h" 

#include "adc_h.h"

//#include "stm8s.h"
#include "men_h.h"
#include "gb_alarm_voice.h"

//********************************************//
//****************常数定义区******************//
#define FCK_PSC 16000000    //16MHZ

#define HSI 0xe1	//内部高速RC时钟
#define LSI 0xd2	//内部低速时钟	
#define HSE 0xb4	//外部高速时钟


////////////////////////////////////////////
#define AINC0     0x00		//ADC通道0
#define AINC1     0x01
#define AINC2     0x02
#define AINC3     0x03
#define AINC4     0x04
#define AINC5     0x05
#define AINC6     0x06
#define AINC7     0x07
#define AINC8     0x08
#define AINC9     0x09		//ADC通道9

//////////////////////////////////////////
#define BIT0			0x01
#define BIT1			0x02
#define BIT2			0x04
#define BIT3			0x08
#define BIT4			0x10
#define BIT5			0x20
#define BIT6			0x40
#define BIT7			0x80

#define DRIVE_BIT		0X01
#define ABS_BIT			0X02
#define ALM_BIT			0X04
#define LOCK_BIT		0X08
/////////////////////////////////////////
#define OCxCE_ENABLE 	1

#define CCMR_PWM 		(OCxCE_ENABLE|BIT6|BIT5|BIT3)



#define A_OFF 0x00
#define B_OFF 0x00
#define C_OFF 0x00

#define AH_ON 0x01
#define AL_ON 0x04
#define BH_ON 0x10
#define BL_ON 0x40
#define CH_ON 0x11
#define CL_ON 0x14
////////////////////////////////////

#define A_ON	(AH_ON)
#define B_ON	(BH_ON)
#define C_ON	(CH_ON)
////////////////////////////////////

#define IRQ_BIF 0x80
#define IRQ_UIF	0x01

/*
//同步整流，需要加死区时间3us
*/

/*
#define AH_ON 0x05
#define AL_ON 0x04
#define BH_ON 0x50
#define BL_ON 0x40
#define CH_ON 0x05
#define CL_ON 0x04
*/




#define PWM_POL		0x00//0x88 //0x00// 极性 xz

////////////////////drive

//////////////////////////////////////////////////
//adbg
/*#define PWM_AHBLCR1		(AH_ON | BL_ON)|PWM_POL
#define PWM_AHBLCR2		((C_ON) & 0x0f)|PWM_POL//jin

#define PWM_CHBLCR1		(A_ON | BL_ON)|PWM_POL
#define PWM_CHBLCR2   ((CH_ON) & 0x0f)|PWM_POL//jin

#define PWM_BHALCR1		(AL_ON | BH_ON)|PWM_POL
#define PWM_BHALCR2		((C_ON) & 0x0f)|PWM_POL//jin

#define PWM_CHALCR1		(AL_ON | B_ON)|PWM_POL
#define PWM_CHALCR2		((CH_ON) & 0x0f)|PWM_POL//jin

#define PWM_AHCLCR1	  	(AH_ON | B_ON)|PWM_POL
#define PWM_AHCLCR2		((CL_ON) & 0x0f)|PWM_POL//jin

#define PWM_BHCLCR1		(A_ON | BH_ON)|PWM_POL
#define PWM_BHCLCR2		((CL_ON) & 0x0f)|PWM_POL//jin*/

#define PWM_AHBLCR1		(AH_ON | BL_ON)|PWM_POL
#define PWM_AHBLCR2		(PWM_POL | C_ON) & 0xff

#define PWM_CHBLCR1		(A_ON | BL_ON)|PWM_POL
#define PWM_CHBLCR2   	(PWM_POL | CH_ON) & 0xff

#define PWM_BHALCR1		(AL_ON | BH_ON)|PWM_POL
#define PWM_BHALCR2		(PWM_POL | C_ON) & 0xff

#define PWM_CHALCR1		(AL_ON | B_ON)|PWM_POL
#define PWM_CHALCR2		(PWM_POL | CH_ON) & 0xff

#define PWM_AHCLCR1	  	(AH_ON | B_ON)|PWM_POL
#define PWM_AHCLCR2		(PWM_POL | CL_ON) & 0xff

#define PWM_BHCLCR1		(A_ON | BH_ON)|PWM_POL
#define PWM_BHCLCR2		(PWM_POL | CL_ON) & 0xff


#define PWM_A_BC_CR1 (AH_ON | BL_ON)|PWM_POL
#define PWM_A_BC_CR2 (PWM_POL | CL_ON) & 0xff

#define PWM_AB_C_CR1 (AH_ON | BH_ON)|PWM_POL
#define PWM_AB_C_CR2 (PWM_POL | CL_ON) & 0xff

#define PWM_B_AC_CR1	(AL_ON | BH_ON)|PWM_POL
#define PWM_B_AC_CR2	(PWM_POL | CL_ON) & 0xff

#define PWM_BC_A_CR1	(AL_ON | BH_ON)|PWM_POL
#define PWM_BC_A_CR2	(PWM_POL | CH_ON) & 0xff

#define PWM_C_AB_CR1	(AL_ON | BL_ON)|PWM_POL
#define PWM_C_AB_CR2	(PWM_POL | CH_ON) & 0xff

#define PWM_AC_B_CR1	(AH_ON | BL_ON)|PWM_POL
#define PWM_AC_B_CR2	(PWM_POL | CH_ON) & 0xff
//////////////////////////spwm///////////////////////////

/////////////1////1,2//////////
#define PWM1_CHBLCR1	(AL_ON | BL_ON)|PWM_POL
#define PWM1_CHBLCR2	(PWM_POL | CH_ON) & 0x0f

#define PWM2_CHBLCR1	(AH_ON | BL_ON)|PWM_POL
#define PWM2_CHBLCR2	(PWM_POL | CH_ON) & 0x0f

//////////////5////3,4//////////
#define PWM3_AHBLCR1	(AH_ON | BL_ON)|PWM_POL
#define PWM3_AHBLCR2	(PWM_POL | CH_ON) & 0x0f

#define PWM4_AHBLCR1	(AH_ON | BL_ON)|PWM_POL
#define PWM4_AHBLCR2	(PWM_POL | CL_ON) & 0x0f

//////////////4////5,6//////////
#define PWM5_AHCLCR1	(AH_ON | BL_ON)|PWM_POL
#define PWM5_AHCLCR2	(PWM_POL | CL_ON) & 0x0f

#define PWM6_AHCLCR1	(AH_ON | BH_ON)|PWM_POL
#define PWM6_AHCLCR2	(PWM_POL | CL_ON) & 0x0f

//////////////6////7,8//////////
#define PWM5_BHCLCR1	(AH_ON | BH_ON)|PWM_POL
#define PWM5_BHCLCR2	(PWM_POL | CL_ON) & 0x0f

#define PWM6_BHCLCR1	(AL_ON | BH_ON)|PWM_POL
#define PWM6_BHCLCR2	(PWM_POL | CL_ON) & 0x0f

//////////////2////9,A//////////
#define PWM9_BHALCR1	(AL_ON | BH_ON)|PWM_POL
#define PWM9_BHALCR2	(PWM_POL | CL_ON) & 0x0f

#define PWMA_BHALCR1	(AL_ON | BH_ON)|PWM_POL
#define PWMA_BHALCR2	(PWM_POL | CH_ON) & 0x0f

//////////////3////B,C//////////
#define PWMB_CHALCR1	(AL_ON | BH_ON)|PWM_POL
#define PWMB_CHALCR2	(PWM_POL | CH_ON) & 0x0f

#define PWMC_CHALCR1	(AL_ON | BL_ON)|PWM_POL
#define PWMC_CHALCR2	(PWM_POL | CH_ON) & 0x0f


#define PHL1_CB()    	{TIM1_CCER1 = PWM1_CHBLCR1;		TIM1_CCER2 = PWM1_CHBLCR2;}
#define PHL2_CB()    	{TIM1_CCER1 = PWM2_CHBLCR1;		TIM1_CCER2 = PWM2_CHBLCR2;}

#define PHL3_AB()		{TIM1_CCER1 = PWM3_AHBLCR1;		TIM1_CCER2 = PWM3_AHBLCR2;}	
#define PHL4_AB()		{TIM1_CCER1 = PWM4_AHBLCR1;		TIM1_CCER2 = PWM4_AHBLCR2;}	

#define PHL5_AC()		{TIM1_CCER1 = PWM5_AHCLCR1;		TIM1_CCER2 = PWM5_AHCLCR2;}	
#define PHL6_AC()		{TIM1_CCER1 = PWM6_AHCLCR1;		TIM1_CCER2 = PWM6_AHCLCR2;}	

#define PHL7_BC()		{TIM1_CCER1 = PWM7_BHCLCR1;		TIM1_CCER2 = PWM7_BHCLCR2;}	
#define PHL8_BC()		{TIM1_CCER1 = PWM8_BHCLCR1;		TIM1_CCER2 = PWM8_BHCLCR2;}	

#define PHL9_BA()		{TIM1_CCER1 = PWM9_BHALCR1;		TIM1_CCER2 = PWM9_BHALCR2;}	
#define PHLA_BA()		{TIM1_CCER1 = PWMA_BHALCR1;		TIM1_CCER2 = PWMA_BHALCR2;}	

#define PHLB_CA()		{TIM1_CCER1 = PWMB_CHALCR1;		TIM1_CCER2 = PWMB_CHALCR2;}	
#define PHLC_CA()		{TIM1_CCER1 = PWMC_CHALCR1;		TIM1_CCER2 = PWMC_CHALCR2;}	


////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define PHD1_CCMR_CB()  {TIM1_CCMR1 = PWM_MODE2;		TIM1_CCMR2 = PWM_MODE2;		TIM1_CCMR3 = PWM_MODE1;}
#define PHD2_CCMR_CB()  {TIM1_CCMR1 = PWM_MODE2;		TIM1_CCMR2 = PWM_MODE2;		TIM1_CCMR3 = PWM_MODE1;}

#define PHD3_CCMR_AB()  {TIM1_CCMR1 = PWM_MODE1;		TIM1_CCMR2 = PWM_MODE2;		TIM1_CCMR3 = PWM_MODE2;}
#define PHD4_CCMR_AB()  {TIM1_CCMR1 = PWM_MODE1;		TIM1_CCMR2 = PWM_MODE2;		TIM1_CCMR3 = PWM_MODE2;}

#define PHD5_CCMR_AC()  {TIM1_CCMR1 = PWM_MODE1;		TIM1_CCMR2 = PWM_MODE2;		TIM1_CCMR3 = PWM_MODE2;}
#define PHD6_CCMR_AC()  {TIM1_CCMR1 = PWM_MODE1;		TIM1_CCMR2 = PWM_MODE2;		TIM1_CCMR3 = PWM_MODE2;}

#define PHD7_CCMR_BC()  {TIM1_CCMR1 = PWM_MODE2;		TIM1_CCMR2 = PWM_MODE1;		TIM1_CCMR3 = PWM_MODE2;}
#define PHD8_CCMR_BC()  {TIM1_CCMR1 = PWM_MODE2;		TIM1_CCMR2 = PWM_MODE1;		TIM1_CCMR3 = PWM_MODE2;}

#define PHD9_CCMR_BA()  {TIM1_CCMR1 = PWM_MODE2;		TIM1_CCMR2 = PWM_MODE1;		TIM1_CCMR3 = PWM_MODE2;}
#define PHDA_CCMR_BA()  {TIM1_CCMR1 = PWM_MODE2;		TIM1_CCMR2 = PWM_MODE1;		TIM1_CCMR3 = PWM_MODE2;}

#define PHDB_CCMR_CA()  {TIM1_CCMR1 = PWM_MODE2;		TIM1_CCMR2 = PWM_MODE2;		TIM1_CCMR3 = PWM_MODE1;}
#define PHDC_CCMR_CA()  {TIM1_CCMR1 = PWM_MODE2;		TIM1_CCMR2 = PWM_MODE2;		TIM1_CCMR3 = PWM_MODE1;}






///////////////////同步整流//////////////////////////////
#define PDP_AHBLCR1		(AH_ON | AL_ON | BL_ON)|PWM_POL
#define PDP_AHBLCR2		(PWM_POL | C_ON) & 0x0f

#define PDP_CHBLCR1		(A_ON  | BL_ON)|PWM_POL
#define PDP_CHBLCR2   	(PWM_POL | CH_ON | CL_ON) & 0x0f

#define PDP_BHALCR1		(AL_ON | BH_ON | BL_ON)|PWM_POL
#define PDP_BHALCR2		(PWM_POL | C_ON) & 0x0f

#define PDP_CHALCR1		(AL_ON | B_ON)|PWM_POL
#define PDP_CHALCR2		(PWM_POL | CH_ON | CL_ON) & 0x0f

#define PDP_AHCLCR1	  	(AH_ON | AL_ON | B_ON)|PWM_POL
#define PDP_AHCLCR2		(PWM_POL | CL_ON) & 0x0f

#define PDP_BHCLCR1		(A_ON | BL_ON | BH_ON)|PWM_POL
#define PDP_BHCLCR2		(PWM_POL | CL_ON) & 0x0f
///////////////////////////////////////////////

///////////////////abs
#define PWM_ALCR1		PWM_POL | (AL_ON | B_ON)
#define PWM_ALCR2		(PWM_POL | C_ON) & 0x0f

#define PWM_BLCR1		PWM_POL | (A_ON | BL_ON)
#define PWM_BLCR2		(PWM_POL | C_ON) & 0x0f

#define PWM_CLCR1		PWM_POL | (A_ON | B_ON)
#define PWM_CLCR2   	(PWM_POL | CL_ON) & 0x0f

/////////////////////////////////////////////////////////////
#define PWM_ALLOFF   	0x00 | PWM_POL		//
#define PWM_ALLON		(A_ON | B_ON) | PWM_POL 


#define PWMDUTY_OFFH	 	0x00
#define PWMDUTY_OFFL	 	0x00


#define PWMDUTY_ONH	 		0x01
#define PWMDUTY_ONL	 		0xf4


#define PWM_ALL_ON()	{TIM1_CCER1 = PWM_ALLON;TIM1_CCER2 = (PWM_ALLON) & 0xff;}

//////////////////////abs
#define PHASE_A()    	{TIM1_CCER1 = PWM_ALCR1;TIM1_CCER2 = PWM_ALCR2;}
#define PHASE_B()		{TIM1_CCER1 = PWM_BLCR1;TIM1_CCER2 = PWM_BLCR2;}
#define PHASE_C()		{TIM1_CCER1 = PWM_CLCR1;TIM1_CCER2 = PWM_CLCR1;}	



#define PWM_HOLD_OFF	0x48//xz

#define PWM_HOLD_ON		0x58//xz

#define PWM_MODE2		0x78

#define PWM_MODE1		0x68

#define	SVPWM_ALL		((AH_ON | AL_ON | BH_ON | BL_ON) | PWM_POL) 
#define	SVPWM_CCER()	{TIM1_CCER1 = SVPWM_ALL;TIM1_CCER2 = SVPWM_ALL & 0xff;}
#define	SVPWM_PH()		{TIM1_CCMR1 = PWM_MODE1;TIM1_CCMR2 = PWM_MODE1;TIM1_CCMR3 = PWM_MODE1; SVPWM_CCER();}

/*
#define PHASE_CCMR_AB()  {TIM1_CCMR1 = PWM_MODE1;		TIM1_CCMR2 = PWM_HOLD_ON;		TIM1_CCMR3 = PWM_HOLD_OFF;}
#define PHASE_CCMR_AC()  {TIM1_CCMR1 = PWM_MODE1;		TIM1_CCMR2 = PWM_HOLD_OFF;	TIM1_CCMR3 = PWM_HOLD_ON;}
#define PHASE_CCMR_BA()  {TIM1_CCMR1 = PWM_HOLD_ON;		TIM1_CCMR2 = PWM_MODE1;			TIM1_CCMR3 = PWM_HOLD_OFF;}
#define PHASE_CCMR_BC()  {TIM1_CCMR1 = PWM_HOLD_OFF;	TIM1_CCMR2 = PWM_MODE1;			TIM1_CCMR3 = PWM_HOLD_ON;}
#define PHASE_CCMR_CA()  {TIM1_CCMR1 = PWM_HOLD_ON;		TIM1_CCMR2 = PWM_HOLD_OFF;	TIM1_CCMR3 = PWM_MODE1;}
#define PHASE_CCMR_CB()  {TIM1_CCMR1 = PWM_HOLD_OFF;	TIM1_CCMR2 = PWM_HOLD_ON;		TIM1_CCMR3 = PWM_MODE1;}
*/

///////////////////////正常驱动drive

#define PHBP_CCMR_AB()  {TIM1_CCMR1 = PWM_MODE1;		TIM1_CCMR2 = PWM_HOLD_ON;		TIM1_CCMR3 = PWM_HOLD_OFF;}
#define PHBP_CCMR_AC()  {TIM1_CCMR1 = PWM_MODE1;		TIM1_CCMR2 = PWM_HOLD_OFF;		TIM1_CCMR3 = PWM_HOLD_ON;}
#define PHBP_CCMR_BA()  {TIM1_CCMR1 = PWM_HOLD_ON;		TIM1_CCMR2 = PWM_MODE1;			TIM1_CCMR3 = PWM_HOLD_OFF;}
#define PHBP_CCMR_BC()  {TIM1_CCMR1 = PWM_HOLD_OFF;		TIM1_CCMR2 = PWM_MODE1;			TIM1_CCMR3 = PWM_HOLD_ON;}
#define PHBP_CCMR_CA()  {TIM1_CCMR1 = PWM_HOLD_ON;		TIM1_CCMR2 = PWM_HOLD_OFF;		TIM1_CCMR3 = PWM_MODE1;}
#define PHBP_CCMR_CB()  {TIM1_CCMR1 = PWM_HOLD_OFF;		TIM1_CCMR2 = PWM_HOLD_ON;		TIM1_CCMR3 = PWM_MODE1;}

/*#define PHBP_CCMR_AB()  {TIM1_CCMR1 = PWM_MODE1;		TIM1_CCMR2 = PWM_HOLD_OFF ;		TIM1_CCMR3 =PWM_HOLD_ON ;}
#define PHBP_CCMR_AC()  {TIM1_CCMR1 = PWM_MODE1;		TIM1_CCMR2 = PWM_HOLD_ON;		TIM1_CCMR3 =PWM_HOLD_OFF ;}
#define PHBP_CCMR_BA()  {TIM1_CCMR1 = PWM_HOLD_OFF ;		TIM1_CCMR2 = PWM_MODE1;			TIM1_CCMR3 = PWM_HOLD_ON;}
#define PHBP_CCMR_BC()  {TIM1_CCMR1 = PWM_HOLD_ON ;		TIM1_CCMR2 = PWM_MODE1;			TIM1_CCMR3 =PWM_HOLD_OFF ;}
#define PHBP_CCMR_CA()  {TIM1_CCMR1 = PWM_HOLD_OFF;		TIM1_CCMR2 =PWM_HOLD_ON ;		TIM1_CCMR3 = PWM_MODE1;}
#define PHBP_CCMR_CB()  {TIM1_CCMR1 = PWM_HOLD_ON;		TIM1_CCMR2 =PWM_HOLD_OFF ;		TIM1_CCMR3 = PWM_MODE1;}*/


#define PHBP_AB()    	{TIM1_CCER1 = PWM_AHBLCR1;TIM1_CCER2 = PWM_AHBLCR2;}
#define PHBP_AC()		{TIM1_CCER1 = PWM_AHCLCR1;TIM1_CCER2 = PWM_AHCLCR2;}	
#define PHBP_BA()		{TIM1_CCER1 = PWM_BHALCR1;TIM1_CCER2 = PWM_BHALCR2;}
#define PHBP_BC()		{TIM1_CCER1 = PWM_BHCLCR1;TIM1_CCER2 = PWM_BHCLCR2;}
#define PHBP_CA()		{TIM1_CCER1 = PWM_CHALCR1;TIM1_CCER2 = PWM_CHALCR2;}
#define PHBP_CB()		{TIM1_CCER1 = PWM_CHBLCR1;TIM1_CCER2 = PWM_CHBLCR2;}

///////////////////////正常驱动lock_drive

#define PHBP_CCMR_A_BC()  {TIM1_CCMR1 = PWM_MODE1;		TIM1_CCMR2 = PWM_HOLD_ON;		TIM1_CCMR3 = PWM_HOLD_ON;}
#define PHBP_CCMR_AB_C()  {TIM1_CCMR1 = PWM_MODE1;		TIM1_CCMR2 = PWM_MODE1;		TIM1_CCMR3 = PWM_HOLD_ON;}
#define PHBP_CCMR_B_AC()  {TIM1_CCMR1 = PWM_HOLD_ON;		TIM1_CCMR2 = PWM_MODE1;			TIM1_CCMR3 = PWM_HOLD_ON;}
#define PHBP_CCMR_BC_A()  {TIM1_CCMR1 = PWM_HOLD_ON;		TIM1_CCMR2 = PWM_MODE1;			TIM1_CCMR3 = PWM_MODE1;}
#define PHBP_CCMR_C_AB()  {TIM1_CCMR1 = PWM_HOLD_ON;		TIM1_CCMR2 = PWM_HOLD_ON;		TIM1_CCMR3 = PWM_MODE1;}
#define PHBP_CCMR_AC_B()  {TIM1_CCMR1 = PWM_MODE1;		TIM1_CCMR2 = PWM_HOLD_ON;		TIM1_CCMR3 = PWM_MODE1;}


#define PHBP_A_BC()   {TIM1_CCER1 = PWM_A_BC_CR1;TIM1_CCER2 = PWM_A_BC_CR2;}
#define PHBP_AB_C()		{TIM1_CCER1 = PWM_AB_C_CR1;TIM1_CCER2 = PWM_AB_C_CR2;}	
#define PHBP_B_AC()		{TIM1_CCER1 = PWM_B_AC_CR1;TIM1_CCER2 = PWM_B_AC_CR2;}
#define PHBP_BC_A()		{TIM1_CCER1 = PWM_BC_A_CR1;TIM1_CCER2 = PWM_BC_A_CR2;}
#define PHBP_C_AB()		{TIM1_CCER1 = PWM_C_AB_CR1;TIM1_CCER2 = PWM_C_AB_CR2;}
#define PHBP_AC_B()		{TIM1_CCER1 = PWM_AC_B_CR1;TIM1_CCER2 = PWM_AC_B_CR2;}


/////////////////////双侧斩波//////改变CCMR////////////////////////////////////////
#define PHDP_CCMR_AB()  {TIM1_CCMR1 = PWM_MODE1;		TIM1_CCMR2 = PWM_MODE2;		TIM1_CCMR3 = PWM_HOLD_OFF;}
#define PHDP_CCMR_AC()  {TIM1_CCMR1 = PWM_MODE1;		TIM1_CCMR2 = PWM_HOLD_OFF;	TIM1_CCMR3 = PWM_MODE2;}
#define PHDP_CCMR_BA()  {TIM1_CCMR1 = PWM_MODE2;		TIM1_CCMR2 = PWM_MODE1;		TIM1_CCMR3 = PWM_HOLD_OFF;}
#define PHDP_CCMR_BC()  {TIM1_CCMR1 = PWM_HOLD_OFF;		TIM1_CCMR2 = PWM_MODE1;		TIM1_CCMR3 = PWM_MODE2;}
#define PHDP_CCMR_CA()  {TIM1_CCMR1 = PWM_MODE2;		TIM1_CCMR2 = PWM_HOLD_OFF;	TIM1_CCMR3 = PWM_MODE1;}
#define PHDP_CCMR_CB()  {TIM1_CCMR1 = PWM_HOLD_OFF;		TIM1_CCMR2 = PWM_MODE2;		TIM1_CCMR3 = PWM_MODE1;}

//////////////////////同步整流/////改变CCER//////////////////////////////////////////
#define PHLP_AB()    	{TIM1_CCER1 = PDP_AHBLCR1;TIM1_CCER2 = PDP_AHBLCR2;}
#define PHLP_AC()		{TIM1_CCER1 = PDP_AHCLCR1;TIM1_CCER2 = PDP_AHCLCR2;}	
#define PHLP_BA()		{TIM1_CCER1 = PDP_BHALCR1;TIM1_CCER2 = PDP_BHALCR2;}
#define PHLP_BC()		{TIM1_CCER1 = PDP_BHCLCR1;TIM1_CCER2 = PDP_BHCLCR2;}
#define PHLP_CA()		{TIM1_CCER1 = PDP_CHALCR1;TIM1_CCER2 = PDP_CHALCR2;}
#define PHLP_CB()		{TIM1_CCER1 = PDP_CHBLCR1;TIM1_CCER2 = PDP_CHBLCR2;}


#ifdef		DP_PWM		//双侧斩波
	#define PHASE_CCMR_AB()  PHDP_CCMR_AB()
	#define PHASE_CCMR_AC()  PHDP_CCMR_AC() 
	#define PHASE_CCMR_BA()  PHDP_CCMR_BA() 
	#define PHASE_CCMR_BC()  PHDP_CCMR_BC()	
	#define PHASE_CCMR_CA()  PHDP_CCMR_CA()
	#define PHASE_CCMR_CB()  PHDP_CCMR_CB()
#else
	#define PHASE_CCMR_AB()  PHBP_CCMR_AB()
	#define PHASE_CCMR_AC()  PHBP_CCMR_AC() 
	#define PHASE_CCMR_BA()  PHBP_CCMR_BA() 
	#define PHASE_CCMR_BC()  PHBP_CCMR_BC()	
	#define PHASE_CCMR_CA()  PHBP_CCMR_CA()
	#define PHASE_CCMR_CB()  PHBP_CCMR_CB()
	
	#define PHASE_CCMR_A_BC()  PHBP_CCMR_A_BC()
	#define PHASE_CCMR_AB_C()  PHBP_CCMR_AB_C() 
	#define PHASE_CCMR_B_AC()  PHBP_CCMR_B_AC() 
	#define PHASE_CCMR_BC_A()  PHBP_CCMR_BC_A()	
	#define PHASE_CCMR_C_AB()  PHBP_CCMR_C_AB()
	#define PHASE_CCMR_AC_B()  PHBP_CCMR_AC_B()
#endif



#ifdef		LP_PWM		//同步整流
	#define PHASE_AB()    	PHLP_AB()
	#define PHASE_AC()		PHLP_AC()
	#define PHASE_BA()		PHLP_BA()
	#define PHASE_BC()		PHLP_BC()
	#define PHASE_CA()		PHLP_CA()
	#define PHASE_CB()		PHLP_CB()
#else
	#define PHASE_AB()    PHBP_AB()
	#define PHASE_AC()		PHBP_AC()
	#define PHASE_BA()		PHBP_BA()
	#define PHASE_BC()		PHBP_BC()
	#define PHASE_CA()		PHBP_CA()
	#define PHASE_CB()		PHBP_CB()
	
	#define PHASE_A_BC()  PHBP_A_BC()
	#define PHASE_AB_C()	PHBP_AB_C()
	#define PHASE_B_AC()	PHBP_B_AC()
	#define PHASE_BC_A()	PHBP_BC_A()
	#define PHASE_C_AB()	PHBP_C_AB()
	#define PHASE_AC_B()	PHBP_AC_B()
#endif



#define PWM_ALL_HOLD_OFF() {TIM1_CCMR1 = PWM_HOLD_OFF;	TIM1_CCMR2 = PWM_HOLD_OFF;		TIM1_CCMR3 = PWM_HOLD_OFF;}

#define PWM_FLASH()		{TIM1_CCMR1 = 0x08;	TIM1_CCMR2 = 0x08;	TIM1_CCMR3 = 0x08;	TIM1_EGR |= 0x20;}




#define PWMU_FLASH()		{TIM1_CCMR1 = 0x08;TIM1_EGR |= 0x20;}
#define PWMV_FLASH()		{TIM1_CCMR2 = 0x08;TIM1_EGR |= 0x20;}
#define PWMW_FLASH()		{TIM1_CCMR3 = 0x08;TIM1_EGR |= 0x20;}
#define PWMUV_FLASH()		{TIM1_CCMR1 = 0x08;TIM1_CCMR2 = 0x08;TIM1_EGR |= 0x20;}
#define PWMUW_FLASH()		{TIM1_CCMR1 = 0x08;TIM1_CCMR3 = 0x08;TIM1_EGR |= 0x20;}
#define PWMVWFLASH()		{TIM1_CCMR2 = 0x08;TIM1_CCMR3 = 0x08;TIM1_EGR |= 0x20;}
//********************************************//
////////////////////////////////////////////jin///////////////////////////////////////	//adbg
#define debug_AH_ON 0x05
//#define debug_AL_ON 0x04
#define debug_BH_ON 0x50
//#define debug_BL_ON 0x40
//#define debug_CH_ON 0x05
//#define debug_CL_ON 0x04

#define debug_A_ON	(debug_AH_ON)
#define debug_B_ON	(debug_BH_ON)
#define debug_C_ON	(debug_CH_ON)

#define debug_PWM_ALLON		((debug_A_ON | debug_B_ON) | PWM_POL) 

#define PWM_ALL_ENABLE()  {TIM1_CCER1 = debug_PWM_ALLON;TIM1_CCER2 = debug_PWM_ALLON & 0xff;}	

#define PWM_ALL_MODE1()  {TIM1_CCMR1 = PWM_MODE1;	TIM1_CCMR2 = PWM_MODE1;		TIM1_CCMR3 = PWM_MODE1;}
//********************************************//
//********************************************//
//****************宏定义区******************//



/////////////////////////////////////////////////

#define WDT_FLASH()  IWDG_KR = 0xAA		//刷新WDT
#define ADC_START()  ADC_CR1 |= 0x01	  

#define DI()		_asm("sim")
#define EI()		_asm("rim")

//********************************************//
//********************************************//

//****************端口定义******************//

#ifdef  S58

#define LJ_CHN      AINC5		//LJ采样通道 
#define CUR_CHN     AINC4		//母线电流采样通道
#define HAD_CHN	   	AINC7		//转把采样通道
#define TEM_CHN     AINC8		//温度采样通道
#define VOL_CHN     AINC6		//电压采样通道
#define PRO_CHN     AINC9		//限速采样通道
#define NUL_CHN     AINC3		//空余不用

#endif

//*****************端口定义*********************//

#ifdef  S58
//#define EHALL_PORT  	  (((PA_IDR & 0x08) >> 1) | ((PD_IDR & 0x08) >> 2) | ((PD_IDR & 0x10) >> 4))
#define EHALL_PORT  	  (((PA_IDR & 0x08) >> 3) | ((PD_IDR & 0x18) >> 2))				//(PE_IDR & 0x07)//((PD_IDR & 0x18) >> 2) + ((PA_IDR & 0x08) >> 3)//((PD_IDR & 0x1C) >> 2)
#define IHALL_PORT  	   ((PC_IDR >> 5) & 0x07)

#define speed_limit_port (PA_IDR & BIT2)

#define LSPD_PORT   (PA_IDR & BIT2)
//#define SPEED_CHECK_PORT   (PC_IDR & BIT7)  //speed check 
#define SPEED_CHECK_PORT   (PE_IDR & BIT0)  //speed check 
#define SPT_PORT   		(PD_IDR & BIT7)	//y42
//#define SPT_PORT_B   		(PE_IDR & BIT0)
#define	BREAK_PORT 		(PA_IDR & BIT1)	//y42
#define ECO_PORT		(PG_IDR & BIT0)	//y42
#define BREAK_PORT2		(PA_IDR & BIT1)
#define	ALM_PORT		(PA_IDR & BIT4)
#define	SF_PORT			(PD_IDR & BIT6)
#define SF_SEL_PORT		(PD_IDR & BIT6)
#define SIM_UART_PORT	(PG_IDR & BIT0)
#define ABS_SEL_PORT	(PD_IDR & BIT7)
#define SPT_SEL_PORT	(PD_IDR & BIT4)
#define ELEDIR_SEL_PORT	(PA_IDR & BIT2)
#define DEBUG_PORT		(EHALL_PORT & BIT1)				//
#define MODE_PORT		(PD_IDR & BIT0)
#define MODE_PORT1		(PA_IDR & BIT2)
#define ONE_KEY_PORT	(PG_IDR & BIT1)			//一键通
#define CVT_PORT		(PD_IDR & BIT5)			//CVT档
#define LOW_POWER_PORT	(PD_IDR & BIT3)			//
#define SF_CVT_PORT		(PA_IDR & BIT1)
#define SPEED_CHG_PORT	(PD_IDR & BIT3)
#define SPEED_SLOW_PORT	(PD_IDR & BIT6)  //爬坡档

#define CROSS0_PORT	(PG_IDR & BIT1)
#define HANDLE_PRO_PORT (PA_IDR & BIT6)
#define LOCK_PORT (PA_IDR & BIT4)


#define LV_ON()   PA_ODR |= (BIT5)	//y42  刹车显示
#define LV_OFF()  PA_ODR &= (~BIT5)	//y42

#define SF_LIGHT_ON()   PA_ODR &= (~BIT5)
#define SF_LIGHT_OFF()  PA_ODR |= (BIT5)

#define SPT_LIGHT_ON()	PA_ODR &= (~BIT5)		
#define SPT_LIGHT_OFF()	PA_ODR |= (BIT5)


#define BACK_LIGHT_ON()	  PD_ODR |= (BIT0)		 ///欠压显示
#define BACK_LIGHT_OFF()	PD_ODR &= (~BIT0)

#define LAMP_ON()	  PA_ODR |= (BIT5)		 ///欠压显示
#define LAMP_OFF()	PA_ODR &= (~BIT5)

//#define V_ON()	PA_ODR &= (~BIT5)		 ///欠压显示
//#define V_OFF()	PA_ODR |= (BIT5)

#define ERROR_OFF()	PD_ODR &= (~BIT6)		 ///故障显示
#define ERROR_ON()	PD_ODR |= (BIT6)

#define SPEED1_ON()		PC_ODR &= (~BIT7)	
#define SPEED1_OFF()	PC_ODR |= (BIT7)

#define SPEED2_ON()		PC_ODR &= (~BIT6)	
#define SPEED2_OFF()	PC_ODR |= (BIT6)

#define SPEED3_ON()		PC_ODR &= (~BIT5)	
#define SPEED3_OFF()	PC_ODR |= (BIT5)

#define SPEED4_ON()		PC_ODR &= (~BIT7)	
#define SPEED4_OFF()	PC_ODR |= (BIT7)

#define SIM_UART_UP()   (PD_ODR &=(~BIT7))
#define SIM_UART_DN()	(PD_ODR |= BIT7)
#define CLP_PORT		BIT6  
#define CLP_ON()		PA_ODR &= (~CLP_PORT)
#define CLP_OFF()		PA_ODR |= (CLP_PORT)
#define HANDLE_CP_ON()	(PE_ODR &= (~BIT5))	//把手电源控制
#define HANDLE_CP_OFF()	(PE_ODR |= (BIT5))
#define HALL_CP_ON()	(PD_ODR |= (BIT0))	//霍尔电源控制
#define HALL_CP_OFF()	(PD_ODR &= (~BIT0))
	
#define VOICE_DN()		(PA_ODR &= (~BIT5))
#define	VOICE_UP()		(PA_ODR |= (BIT5))
////////////////////////////////////////////////////////
#define speed_level_flag  (PA_IDR & BIT1)
#define low_speed_signal_on()  (PD_ODR |= (BIT5))
#define low_speed_signal_down() (PD_ODR &= (~BIT5))

#define middle_speed_signal_on()  (PD_ODR |= (BIT6))
#define middle_signal_down()     (PD_ODR &= (~BIT6))

#define high_speed_signal_on()  (PG_ODR |= (BIT1))
#define high_signal_down()     (PG_ODR &= (~BIT1))
#endif



/////////////////////////////////jin/////////////////////////////////
#define	OUT1_ON()		(PA_ODR |= (BIT4))	//输出1          //jin
#define OUT1_OFF()		(PA_ODR &= (~BIT4))

//#define	OUT2_ON()		(PD_ODR |= (BIT5))	//输出2
//#define OUT2_OFF()		(PD_ODR &= (~BIT5))

//#define	OUT3_ON()		(PG_ODR |= (BIT1))	//输出3
//#define OUT3_OFF()		(PG_ODR &= (~BIT1))

//#define	OUT4_ON()		(PC_ODR |= (BIT6))	//输出4
//#define OUT4_OFF()		(PC_ODR &= (~BIT6))

//#define	OUT5_ON()		(PC_ODR |= (BIT7))	//输出5
//#define OUT5_OFF()		(PC_ODR &= (~BIT7))
#define TEST_HALL1  (EHALL_PORT & BIT0)
#define TEST_HALL2  (EHALL_PORT & BIT1)
#define TEST_HALL3  (EHALL_PORT & BIT2)
//#define TEST_HALL1  (PD_IDR & BIT3)
//#define TEST_HALL2  (PD_IDR & BIT4)
//#define TEST_HALL3  (PA_IDR & BIT3)
//#define TEST_MODE_PORT1 (MODE_PORT1)
//#define TEST_SF_PORT   	(PD_IDR & BIT6)
//#define TEST_ABS_SEL_PORT	(PG_IDR & BIT1)
//#define TEST_SPT_SEL_PORT	(PD_IDR & BIT3)
#define	TEST_BREAK_PORT (BREAK_PORT2)//JIN
#define TEST_MODE_PORT1 (MODE_PORT1)
#define TEST_ECO_POT (ECO_PORT)
#define TEST_MODE_PORT (MODE_PORT)
//#define TEST_SPT_SEL_PORT SPT_SEL_PORT
//#define TEST_ECO_PORT    (PG_IDR & BIT1)
//#define TEST_MODE1_PORT		(PG_IDR & BIT0)
//#define TEST_ALM_PORT   	(PD_IDR & BIT7)
//#define TEST_BREAK_PORT2   	(PD_IDR & BIT0)

#define TEST_HIGH  (MODE_PORT1 & TEST_MODE_PORT & ECO_PORT &MODE_PORT) //JIN
#define TEST_LOW   (MODE_PORT1 | TEST_MODE_PORT | ECO_PORT |MODE_PORT) //JIN

#define TEST_HIGH_HALL  (TEST_HALL1 & TEST_HALL2 & TEST_HALL3) //JIN
#define TEST_LOW_HALL   (TEST_HALL1 | TEST_HALL2 | TEST_HALL3) //JIN

#define TEST_HIGH1   (TEST_HALL1) //JIN
#define TEST_HIGH2   (TEST_HALL2) //JIN
#define TEST_HIGH3   (TEST_HALL3) //JIN
//#define TEST_HIGH4   (TEST_ECO_PORT) //JIN
//#define TEST_HIGH5   (TEST_SF_PORT) //JIN
//#define TEST_HIGH8   (TEST_BREAK_PORT)//JIN
#define TEST_HIGH4   (BREAK_PORT2)//JIN
#define TEST_HIGH5   (MODE_PORT1)//JIN
#define TEST_HIGH6   (ECO_PORT)//JIN
#define TEST_HIGH7   (MODE_PORT)//JIN 


//********************************************//
//********************************************//

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
#define defperiod_count	600			//固定换向时间		3000*62.5us
#define DefNum			24			//校验次数
#define ERRHALLNUM		400			//出错计数最大值	
#define next_cont		50			//等待延时			100*62.5us
#define Min_pwm_protion 16			//最小PWM	
#define Max_pwm_protion 64			//最大PWM
#define Start_PS_TIME 	5			//启动PWM的增加速度	200×62.5us
#define Re_Start_over_count  10		//

///////////////// //////////////////////////////////////////
#define Motor_Mi	28				//电机的极对数
#define Motor_Dia	16				//电机的直径(英寸)
#define Revolution_OffSet		0	//一公里的电机转数误差微调
#define KM_HALLCNT	(unsigned int)(12532/Motor_Dia) + Revolution_OffSet		//一公里电机旋转圈数
#define HALLMAX		Motor_Mi*6		//电机一转的HALL数
//
#define Sleep_time 					3000			//100ms * 6000/60= 600s/60 = 10min
#define Sleep_time_err 				Sleep_time + 200


//功能定义区////////////////////////////////////////////////
#define DEBUG_MODE  1			//调试模式，不加密
//#define AUTO_PHS				//自动静音，S30_V3暂时不用自动静音	
//#define SIM_UART				//带表头功能
//#define HALL_60C	0xFF		//电机霍尔60度
//#define CVT_MODE 	1			//CVT功能
//#define HALL_CHANG_AUTO 1		//有无霍尔自动却换 

//#define SF_FUN					//手动巡航
#define SF_AUTO_FUN				//自动巡航

//#define SPT_FUN					//阻力功能
//#define SPT_SEL_FUN				//助力可选功能
//#define SPT_NO_ZERO	            //非零助力

//#define ALM_FUN					//报警功能
#define LOW_SPEED_LOE_POWER		//堵转降电流
//#define ONE_KEY_FUN				//一键通功能
//#define LOW_POWER_MODE			//经济档模式
 
//#define GB_ALARM_VOICE 			//高标语音报警器
#define PUSH_6KM             //6km推车
//#define HAND_NO_ZERO_START           //非零启动

#define PH_MAX_COUNT	10		//静音周期最大值,高速电机最大4个周期，198，266 10个周期，
#define SPEED_MODE 

//#define ZERO_START           //零启动
//#define LJ_ERROR_CHK  //开机检测力矩
//#define LJ_SPEED_SELECT //力矩速度转换
#define LJ_ZERO_AUTO_CORRECT //自动调整零位
#define LJ_PALE_START  //脚踩开机
//////////////////////////////////////////////////////


#ifdef     S58
#define PH_CURRENT_MAX   120		//117  3.3K,10K  45A
#endif



//温度表
/*
升温曲线
温度   采样值
60		201
65		197
70		193
75		187
80		179
85		170
90		162
95		152
100		143
105		134
110		124
115		114
*/

/*
降温曲线
温度   采样值
100		117
95		123
90		130
85		135
80		145
75		155
70		163
65		173
60		182
*/







