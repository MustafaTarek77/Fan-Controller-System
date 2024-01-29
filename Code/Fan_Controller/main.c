/*
 * main.c
 *
 *  Created on: Oct 6, 2022
 *      Author: mustafa
 */
#include "lcd.h"
#include"adc.h"
#include "lm35_sensor.h"
#include "DC_motor.h"


int main(void)
{
	uint8 temp;
	/* initialize LCD driver */
	LCD_init();
	/* initialize ADC driver */
	ADC_ConfigType Config_Ptr;
	Config_Ptr.prescaler=0X03;
	Config_Ptr.ref_volt=0X03;
	ADC_init(&Config_Ptr);
	/* initialize DC motor driver */
	DcMotor_Init();

	//Displaying
	LCD_moveCursor(0,3);
	LCD_displayString("FAN is ");
	LCD_moveCursor(1,3);
	LCD_displayString("Temp =    C");
	while(1)
	{
		temp = LM35_getTemperature();

		LCD_moveCursor(0,10);

		if(temp < 30 )
		{
			LCD_displayString("OFF");
			DcMotor_Rotate(Stop,0);
		}
		else if(temp < 60)
		{
			LCD_displayString("ON");
			LCD_displayCharacter(' ');
			DcMotor_Rotate(Clockwise,25);
		}
		else if(temp < 90)
		{
			LCD_displayString("ON");
			LCD_displayCharacter(' ');
			DcMotor_Rotate(Clockwise,50);
		}
		else if(temp < 120)
		{
			LCD_displayString("ON");
			LCD_displayCharacter(' ');
			DcMotor_Rotate(Clockwise,75);
		}
		else
		{
			LCD_displayString("ON");
			LCD_displayCharacter(' ');
			DcMotor_Rotate(Clockwise,100);
		}

		LCD_moveCursor(1,10);

		if(temp >= 100)
		{
			LCD_intgerToString(temp);
		}
		else
		{
			LCD_intgerToString(temp);
			/* In case the digital value is two or one digits print space in the next digit place */
			LCD_displayCharacter(' ');
		}
	}
}
