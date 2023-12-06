/*
 * FSMModificationMode.c
 *
 *  Created on: Nov 30, 2023
 *      Author: hieun
 */
#include "FSMModificationMode.h"


void FSMModificationModeRun()
{
	switch(status)
	{
	case MODIFICATION_MODE:
		resetInitialState();	// reset all all the varialbles thats affect FSMModificationModeRun
		status = MODIFY_RED;	// next mode
		//led blinky for 2hz

		// initial setting led 7 seg
		setLedBuffer(0, 1);


		break;

	case MODIFY_RED:

		if(isButton1Pressed() == 1)
		{
			resetInitialState();

			status = MODIFY_YELLOW;	//next mode


			// initial setting led 7 seg
			setLedBuffer(0, 2);

		}

		if(isButton2Pressed() == 1)
		{
			resetInitialState();

			status = MODIFY_TIME_RED; //next mode
			setTimer4(25);

			red_time = 1;
			setLedBuffer(red_time, 1);
		}
		break;

	case MODIFY_YELLOW:

		if(isButton1Pressed() == 1)
		{
			resetInitialState();

			status = MODIFY_GREEN;
			setTimer4(25);

			setLedBuffer(0, 3);
			SCH_Add_Task(toggleTrafficGreen, 0, TOGGLE_TIME);
		}

		if(isButton2Pressed() == 1)
		{
			resetInitialState();

			status = MODIFY_TIME_YELLOW;
			setTimer4(25);

			yellow_time = 1;
			setLedBuffer(yellow_time, 2);

		}
		break;

	case MODIFY_GREEN:

		if(isButton1Pressed() == 1)
		{
			resetInitialState();
			if(red_time == green_time+yellow_time)
			{
				status = NORMAL_MODE;
			}
			else
			{
				if(red_time > green_time+yellow_time)
				{
					green_time = red_time - yellow_time;
					status = NORMAL_MODE;
				}
				else
				{
					red_time = green_time + yellow_time;
					status = NORMAL_MODE;
				}
			}
		}

		if(isButton2Pressed() == 1)
		{
			resetInitialState();

			status = MODIFY_TIME_GREEN;
			green_time = 1;
			setLedBuffer(green_time, 3);
		}
		break;

	default:
		break;
	}
}
