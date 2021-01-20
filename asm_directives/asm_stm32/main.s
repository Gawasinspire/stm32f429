RCC_BASE	EQU	0x40023800
RCC_AHB1ENR	EQU 0x40023830	;RCC_BASE + 0x30
GPIOB_BASE	EQU	0x40020C00
GPIOB_MODER	EQU	GPIOB_BASE
GPIOB_ODR	EQU	0x40020C14	;GPIOB_BASE

GPIOBEN		EQU	1 << 1

MODER14_OUT	EQU	1 << 28
MODER7_OUT	EQU	1 << 14
MODER0_OUT	EQU	1 << 0

LED_BLUE	EQU	1 << 14
LED_RED		EQU	1 << 7
LED_GREEN	EQU	1 << 0

DELAY		EQU	0x000F
ONESEC		EQU	266667
FSEC		EQU	106667
	
		AREA |.text|,CODE,READONLY,ALIGN=2
		THUMB
		EXPORT __main

__main
		BL	GPIOB_Init

GPIOB_Init

		LDR	R0,=RCC_AHB1ENR	; R0 points to pheripherals clock register
		LDR	R1,[R0]			; Load Peripheral clock register is into R1
		ORR	R1,GPIOBEN		; RCC_AHB1ENR ORR 1<<1
		STR	R1,[R0]			; Store content of R1 into RCC_AHB1ENR
		
		LDR	R0,=GPIOB_MODER	; R0 points to PORTD configuration register
		LDR	R1,=(MODER14_OUT|MODER7_OUT|MODER0_OUT)	;R1 points to pins 14,7,0
		STR	R1,[R0]			; Store pins 14,7,0 into MODER..
		MOV	R1,#0
		LDR	R2,=GPIOB_ODR
		
Blink
		MOVW	R1,#LED_GREEN
		STR		R1,[R2]
		LDR		R3,=ONESEC
		BL		Delay
		
		MOVW	R1,#LED_BLUE
		STR		R1,[R2]
		LDR		R3,=ONESEC
		BL		Delay
		
		MOVW	R1,#LED_RED
		STR		R1,[R2]
		LDR		R3,=FSEC
		BL		Delay


Delay	
		SUBS	R3,R3,#1
		BNE		Delay
		BX		LR
		ALIGN
		END
