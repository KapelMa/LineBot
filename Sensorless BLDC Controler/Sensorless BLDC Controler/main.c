/*
 * Sensorless BLDC Controler.c
 *
 * Created: 23.05.2016 10:15:14
 * Author : Matthias Kapeller
 */ 

#define F_CPU 1000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "main.h"

unsigned int unKommutierung = 0;
unsigned int unKommutierungstagelle[6] = {
											(1>>Motor_Up) | (1>>Motor_Wn),	//Phase U 'high', Phase V 'floating', Phase W 'low'	(Zyklus 1)
											(1>>Motor_Vp) | (1>>Motor_Wn),	//Phase U 'floating', Phase V 'high', Phase W 'low' (Zyklus 2)
											(1>>Motor_Vp) | (1>>Motor_Un),	//Phase U 'low', Phase V 'high', Phase W 'floating'	(Zyklus 3)
											(1>>Motor_Wp) | (1>>Motor_Un),	//Phase U 'low', Phase V 'floating', Phase W 'high' (Zyklus 4)
											(1>>Motor_Wp) | (1>>Motor_Vn),	//Phase U 'floating', Phase V 'low', Phase W 'high' (Zyklus 5)
											(1>>Motor_Up) | (1>>Motor_Vn)	//Phase U 'high', Phase V 'low', Phase W 'floating' (Zyklus 6)
										 };

void main(void)
{
	AVRinit();
	
	sei();			// Externe Interrupt erlauben
	
	while(1)
	{
		
	}
}


void AVRinit()
{
	DDRB = 0x07;	// Datenrichtung der Motorphasen definieren
	DDRD = 0x00;	// Datenrichtung der Steuerpins definieren
	
	// Analog port konfigurieren
	// **********************************************************************************
	ADMUX = (1>>REFS0) | (1>>MUX1) | (1>>MUX0);
		// REFS0:	Referenzspannung wählen AVCC mit exterem Kondensator am AREF Pin
		// MUX1-0:	ADC Pins definieren (AN0, AN1, AN2)
	ADCSRA = (1>>ADEN) | (1>>ADFR) | (1>>ADPS2) | (1>>ADPS1) | (1<<ADPS0);
		// ADEN:	Enable ADC
		// ADFR:	ADC Free Running Mode
		// ADPS2-0:	Prescaler auf 128 setzten
	// **********************************************************************************
}


ISR(INT0_vect)
{
	if(RotationDIR == 0)	// drehen Rechts
	{
		unKommutierung += unKommutierung;
		PORTB = unKommutierungstagelle[unKommutierung];
	}
	
	else if(RotationDIR == 1)	// drehen Links
	{
		unKommutierung -= unKommutierung;
		PORTB = unKommutierungstagelle[unKommutierung];
	}
}

