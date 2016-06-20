/*
 * main.h
 *
 * Created: 01.06.2016 10:59:43
 *  Author: Matthias Kapeller
 */ 


#ifndef MAIN_H_
#define MAIN_H_

void AVRinit(void);

#define Motor_Up	PB0
#define Motor_Vp	PB1
#define Motor_Wp	PB2
#define Motor_Un	PB3
#define Motor_Vn	PB4
#define Motor_Wn	PB5


#define RotationDIR	PD1
#define RotationCLK	PD2


#endif /* MAIN_H_ */