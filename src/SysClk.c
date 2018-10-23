/*
 * SysClk.c
 *
 *  Created on: 2017年9月15日
 *      Author: WangHongBo
 */

#include "SysClk.h"

//此程序中    外部输入时钟 为40MHz     PLL0 为50MHz     PLL1 为200MHz
/*******************************************************************************
Function Name : Sys_Init
Engineer      : Martin Kovar
Date          : Dec-29-2015
Parameters    : NONE
Modifies      : NONE
Returns       : NONE
Notes         : Enable XOSC, PLL0, PLL1 and enter RUN0 with PLL1 as sys clk (200 MHz)
Issues        : NONE
*******************************************************************************/
// Enable XOSC, PLL0, PLL1 and enter RUN0 with PLL1 as sys clk (200 MHz)
void SysClk_Init(void)
{

	      MC_CGM.AC3_SC.B.SELCTL = 0x01;		 //connect XOSC to the PLL0 input
	      MC_CGM.AC4_SC.B.SELCTL = 0x01;		 //connect XOSC to the PLL1 input

	    // Set PLL0 to 50 MHz with 40MHz XOSC reference
	    //              40*10(MFD)
	    //      ——————————————————————————   =  50MHz
	    //           8(RFDPHI)*1(PREDIV)
	      PLLDIG.PLL0DV.R = 0x3008100A;	        // PREDIV =  1, MFD = 10, RFDPHI = 8, RFDPHI1 = 6

	    //其他程序中有到200MHz的， 如下所示
	   // PLLDIG.PLL0DV.R = 0x58021014;         //PREDIV =  1, MFD = 20, RFDPHI = 2, RFDPHI1 = 11

	      MC_ME.RUN0_MC.R = 0x00130070;		    // RUN0 cfg: IRCON,OSC0ON,PLL0ON,syclk=IRC

	      // Mode Transition to enter RUN0 mode:
	      MC_ME.MCTL.R = 0x40005AF0;		    // Enter RUN0 Mode & Key
	      MC_ME.MCTL.R = 0x4000A50F;		    // Enter RUN0 Mode & Inverted Key
	      while (MC_ME.GS.B.S_MTRANS) {};		// Wait for mode transition to complete
	      while(MC_ME.GS.B.S_CURRENT_MODE != 4) {};	    // Verify RUN0 is the current mode

	      // Set PLL1 to 200 MHz with 40MHz XOSC reference
	      PLLDIG.PLL1DV.R = 0x00020014;	        // MFD = 20, RFDPHI = 2
	      //激活除Reset模式之外的其他所有模式
	      MC_ME.RUN_PC[0].R = 0x000000FE;	    // enable peripherals run in all modes
	      //默认PC[0],现在改成PC[1]
	     // MC_ME.PCTL204.B.RUN_CFG = 0x1;        //NEW ADD

          //配置RUN0下的时钟源，
	      MC_ME.RUN0_MC.R = 0x001300F4;		    // RUN0 cfg: IRCON, OSC0ON, PLL1ON, syclk=PLL1
	      //系统时钟分频作为另一个时钟的时钟源
	      MC_CGM.SC_DC0.R = 0x80030000;         // PBRIDGE0/PBRIDGE1_CLK at syst clk div by 4 ... (50 MHz)
          //选择并进入RUN0模式
	      // Mode Transition to enter RUN0 mode:
	      MC_ME.MCTL.R = 0x40005AF0;		    // Enter RUN0 Mode & Key
	      MC_ME.MCTL.R = 0x4000A50F;		    // Enter RUN0 Mode & Inverted Key
	      while (MC_ME.GS.B.S_MTRANS) {};		// Wait for mode transition to complete
	      while(MC_ME.GS.B.S_CURRENT_MODE != 4) {};	    // Verify RUN0 is the current mode

}


/*******************************************************************************
Function Name : PeriClkGen_init
Engineer      : Martin Kovar
Date          : Jan-5-2016
Parameters    :
Modifies      :
Returns       :
Notes         : - Enable all auxiliary clocks, IMPORTANT - MOTC_CLK is set to 5MHz
Issues        :
*******************************************************************************/
void InitPeriClkGen(void)
{
	//在技术手册完整版(共2931页)的347页有时钟分配的明细
	//选择时钟源PLL0、PLL1或晶振 作为时钟源(ACx_SCx的作用)，
	//经过分频或不分频后作为各模块的时钟源(ACx_DCx的作用)
 // MC_CGM.SC_DC0.R  = 0x80030000;    // PBRIDGE0/PBRIDGE1_CLK at syst clk div by 4 ... (50 MHz)
	MC_CGM.AC0_SC.R  = 0x02000000;    // Select PLL0 for auxiliary clock 0
	MC_CGM.AC0_DC0.R = 0x80090000;    // MOTC_CLK : Enable aux clk 0 div by 10 � (5 MHz)
	MC_CGM.AC0_DC1.R = 0x80070000;    // SGEN_CLK : Enable aux clk 0 div by 8 � (6.25 MHz)
    MC_CGM.AC0_DC2.R  = 0x80010000;   // ADC_CLK : Enable aux clk 0 div by 2 � (25 MHz)
	MC_CGM.AC6_SC.R  = 0x04000000;    // Select PLL1 for auxiliary clock 6
	MC_CGM.AC6_DC0.R = 0x80010000;    // CLKOUT0 : Enable aux clk 6 div by 2 � (100 MHz)
	MC_CGM.AC10_SC.R = 0x04000000;    // Select PLL1 for auxiliary clock 10
	MC_CGM.AC10_DC0.R= 0x80030000;    // ENET_CLK : Enable aux clk 10 div by 4 � (50 MHz)
	MC_CGM.AC11_SC.R = 0x04000000;    // Select PLL1 for auxiliary clock 11
	MC_CGM.AC11_DC0.R= 0x80030000;    // ENET_TIME_CLK : Enable aux clk 11 div by 4 � (50 MHz)
	MC_CGM.AC5_SC.R  = 0x02000000;    // Select PLL0 for auxiliary clock 5
	MC_CGM.AC5_DC0.R = 0x80000000;    // LFAST_CLK : Enable aux clk 5 div by 1 � (50 MHz)
	MC_CGM.AC2_DC0.R = 0x80010000;    // CAN_PLL_CLK : Enable aux clk 2 (PLL0) div by 2 � (25 MHz)
	MC_CGM.AC1_DC0.R = 0x80010000;    // FRAY_PLL_CLK : Enable aux clk 1 (PLL0) div by 2 � (25 MHz)
	MC_CGM.AC1_DC1.R = 0x80010000;    // SENT_CLK : Enable aux clk 1 (PLL0) div by 2 � (25 MHz)
}
