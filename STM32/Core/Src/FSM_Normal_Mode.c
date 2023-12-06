/*
 * FSMNormalMode.c
 *
 *  Created on: Nov 30, 2023
 *      Author: bach
 */

#ifndef SRC_FSMNORMALMODE_C_
#define SRC_FSMNORMALMODE_C_

#include "FSMNormalMode.h"

int count_down;

void FSMNormalModeRun()
{
	switch(status)
	{
	case NORMAL_MODE:
		resetInitialState(); 	// reset all all the varialbles thats affect FSMNormalModeRun

		status = RED0_GREEN1; 	//next mode
//		setTimer1(green_time);	//set timer for next state
		// initial setting led 7 seg

		setLedBuffer(red_time, green_time);
//		setTimer3(100); // timer update buffer in led 7 seg
		count_down = green_time;

		break;
	case RED0_GREEN1:
		setTrafficRed();
		setTrafficGreen1();

		SCH_Add_Task(updateLedBuffer, 1000, 0);
		count_down--;
		if(count_down <= 0)
		{
			count_down = yellow_time; // set count_down
			status = RED0_YELLOW1; // set next mode
			setLedBuffer(yellow_time, yellow_time); // set led buffer
		}

//		if(timer3_flag == 1)	//update buffer every second
//		{
//			updateLedBuffer();
//			setTimer3(100);
//		}
//
//		if(timer1_flag == 1)
//		{
//			status = RED0_YELLOW1;	//next mode
//			setTimer1(yellow_time);
//
//			setLedBuffer(yellow_time, yellow_time); // set buffer for led 7 seg
//
//		}

		if(isButton1Pressed() == 1)
		{
			status = MODIFICATION_MODE;
			SCH_Add_Task(FSMModificationModeRun, 0, 0);
		}
		break;

	case RED0_YELLOW1:
		setTrafficRed();
		setTrafficYellow1();

		SCH_Add_Task(updateLedBuffer, 1000, 0);
		count_down--;
		if(count_down <= 0)
		{
			count_down = green_time;
			status = GREEN0_RED1;
			setLedBuffer(green_time, red_time);
		}
//		if(timer3_flag == 1)	//update buffer every second
//		{
//			updateLedBuffer();
//			setTimer3(100);
//		}
//
//		if(timer1_flag == 1)
//		{
//			status = GREEN0_RED1;	//next mode
//			setTimer1(green_time);	//set_timer for next mode
//
//			setLedBuffer(green_time, red_time); // set buffer for led 7 seg
//		}

		if(isButton1Pressed() == 1)
		{
			status = MODIFICATION_MODE;
			SCH_Add_Task(FSMModificationModeRun, 0, 0);
		}
		break;

	case GREEN0_RED1:
		setTrafficGreen();
		setTrafficRed1();

		SCH_Add_Task(updateLedBuffer, 1000, 0);
		count_down--;
		if(count_down <= 0)
		{
			count_down = yellow_time;
			status = YELLOW0_RED1;
			setLedBuffer(yellow_time, yellow_time);
		}
//		if(timer3_flag == 1)
//		{
//			updateLedBuffer();
//			setTimer3(100);

//		}
//
//		if(timer1_flag==1)
//		{
//			status = YELLOW0_RED1;
//			setTimer1(yellow_time);
//
//			setLedBuffer(yellow_time, yellow_time);	// set buffer for led 7 seg
//		}

		if(isButton1Pressed() == 1)
		{
			status = MODIFICATION_MODE;
			SCH_Add_Task(FSMModificationModeRun, 0, 0);
		}
		break;

	case YELLOW0_RED1:
		setTrafficYellow();
		setTrafficRed1();

		SCH_Add_Task(updateLedBuffer, 1000, 0);
		count_down--;
		if(count_down <= 0)
		{
			count_down = green_time;
			status = RED0_GREEN1;
			setLedBuffer(red_time, green_time);
		}

//		if(timer3_flag == 1)
//		{
//			updateLedBuffer();
//			setTimer3(100);
//		}
//
//		if(timer1_flag == 1)
//		{
//			status = RED0_GREEN1;
//			setTimer1(green_time);
//
//			setLedBuffer(red_time, green_time); // set buffer for led 7 seg
//		}
		if(isButton1Pressed() == 1)
		{
			status = MODIFICATION_MODE;
			SCH_Add_Task(FSMModificationModeRun, 0, 0);
		}
		break;

	default:
		break;
	}
}

#endif /* SRC_FSMNORMALMODE_C_ */
