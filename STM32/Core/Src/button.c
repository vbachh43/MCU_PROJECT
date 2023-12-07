/*
 * button.c
 *
 *  Created on: Dec 7, 2023
 *      Author: bach
 */

#include "button.h"

int key1_reg0 = NORMAL_STATE;
int key1_reg1 = NORMAL_STATE;
int key1_reg2 = NORMAL_STATE; // #define NORMAL_STATE  GPIO_PIN_SET
int key1_reg3 = NORMAL_STATE; // key1_reg3 dùng để xử lý nhấn đè

// BUTTON 2 PROCESS
int key2_reg0 = NORMAL_STATE;
int key2_reg1 = NORMAL_STATE;
int key2_reg2 = NORMAL_STATE; // #define NORMAL_STATE  GPIO_PIN_SET
int key2_reg3 = NORMAL_STATE; // key2_reg3 dùng để xử lý nhấn đè

//BUTTON 3 PROCESS
int key3_reg0 = NORMAL_STATE;
int key3_reg1 = NORMAL_STATE;
int key3_reg2 = NORMAL_STATE; // #define NORMAL_STATE  GPIO_PIN_SET
int key3_reg3 = NORMAL_STATE; // key3_reg3 dùng để xử lý nhấn đè

int timer_for_key_press = 200;

int button1_flag = 0;
int button2_flag = 0;
int button3_flag = 0;
// PROCESS BUTTON 1 FUNCTION
int isButton1Pressed() // nếu nút được nhấn thì hàm trả về 1
{
	if(button1_flag == 1){
		button1_flag = 0;
		return 1;
	}
	else return 0;
}
void flag1Process() // hàm này chỉ đề set cờ khi mà nút được nhấn
{
	button1_flag = 1; // set flag để xử lý trên while(1)
}

// PROCESS BUTTON 2 FUNCTION
int isButton2Pressed()
{
	if(button2_flag == 1)
	{
		button2_flag = 0;
		return 1;
	}
	else return 0;
}
void flag2Process()
{
	button2_flag = 1;
}

//PROCESS BUTTON 3 FUNCTION
int isButton3Pressed()
{
	if(button3_flag == 1)
	{
		button3_flag = 0;
		return 1;
	}
	else return 0;
}
void flag3Process()
{
	button3_flag = 1;
}

void getKeyInput()  //goi = timer moi 10ms 1 lan
{
	key1_reg0 = key1_reg1;
	key1_reg1 = key1_reg2;
	key1_reg2 = HAL_GPIO_ReadPin(BUTTON1_GPIO_Port, BUTTON1_Pin); // key1_reg2 đọc giá trị của nút nhấn
	if((key1_reg0 == key1_reg1) && (key1_reg1 == key1_reg2)) // chống rung
	{
		if(key1_reg3 != key1_reg2) // xử lý khi nhấn
		{
			key1_reg3 = key1_reg2;
			if(key1_reg2 == PRESSED_STATE)
			{
				flag1Process();
				timer_for_key_press = 200; // gán lại lên 2s
			}
		}
		else // xử lý nhấn đè (key1_reg3 == key1_reg2)
		{
			timer_for_key_press--;
			if(timer_for_key_press == 0)
			{
				key1_reg3 = NORMAL_STATE; // gán key1_reg3 thành NORMAL_STATE sẽ reset trường hợp nhấn đè lên lại trường hợp nhấn
			}
		}
	}

	key2_reg0 = key2_reg1;
	key2_reg1 = key2_reg2;
	key2_reg2 = HAL_GPIO_ReadPin(BUTTON2_GPIO_Port, BUTTON2_Pin);
	if(key2_reg0 == key2_reg1 && key2_reg1 == key2_reg2)
	{
		if(key2_reg3 != key2_reg2)
		{
			key2_reg3 = key2_reg2;
			if(key2_reg2 == PRESSED_STATE)
			{
				flag2Process();
				timer_for_key_press = 200;
			}
		}
		else
		{
			timer_for_key_press--;
			if(timer_for_key_press == 0)
			{
				key2_reg3 = NORMAL_STATE;
			}
		}
	}

	key3_reg0 = key3_reg1;
	key3_reg1 = key3_reg2;
	key3_reg2 = HAL_GPIO_ReadPin(BUTTON3_GPIO_Port, BUTTON3_Pin);
	if(key3_reg0 == key3_reg1 && key3_reg1 == key3_reg2)
	{
		if(key3_reg2 != key3_reg3)
		{
			key3_reg3 = key3_reg2;
			if(key3_reg2 == PRESSED_STATE)
			{
				flag3Process();
				timer_for_key_press = 200;
			}
		}

		else
		{
			timer_for_key_press--;
			if(timer_for_key_press == 0)
			{
				key3_reg3 = NORMAL_STATE;
			}
		}
	}
}
