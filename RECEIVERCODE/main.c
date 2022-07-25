/*
 * RECEIVERCODE.c
 *
 * Created: 7/25/2022 6:15:08 PM
 * Author : Dell
 */ 

#include <avr/io.h>
#define F_CPU 1000000UL
#include<util/delay.h>

int main(void)
{
	DDRB = 0x01; //Makes RB0 output pin
	PORTB = 0x00;
	

	int index = 0;
	char digit[20]=
	{
		'7','8','9','/',
		'4','5','6','*',
		'1','2','3','-',
		'A','0','=','+','\0'
	};
	char Original_Password[4] = {'9','8','7','6'};
	char push_button;
	DDRD&=~(1<<PD0);
	DDRD|=(1<<PD1);
	DDRA=0XFF;
	DDRC=0XFF;
	UBRR0H=0X00;
	UBRR0L=0X05;
	UCSR0B=(1<<RXEN0);
	UCSR0C=(1<<USBS0)|(3<<UCSZ00);
	unsigned char receiveData;
	while(1)
	{
		push_button = PINB&00000001;
		PORTC = 0;
		receiveData = 0;
		while(!(UCSR0A&(1<<RXC0)));
		receiveData=UDR0;
		PORTC=receiveData;
		if(receiveData!=16)
		{
			if(digit[receiveData]==Original_Password[index]){
				index++; // incrementing index
			}
		}
		if (push_button==1)
		{
			index=0;
			PORTA=0b11111111;
			_delay_ms(200);
			UDR0=0b11110000;
			// If Push button is Pressed then 7-segment will
			//change from Open(O) to Close(C)
		}


		if (index==4)
		{

			//Rotate Motor to 90 degree
			PORTC = 0x01;
			_delay_ms(1500);
			PORTC = 0x00;

			_delay_ms(2000);


		}
		else
		{
			UDR0=0b11000110;
			_delay_ms(1000);
			// 7-segment will show C which means Close

		}
	}

}