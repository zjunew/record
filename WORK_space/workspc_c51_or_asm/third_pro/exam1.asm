	ORG 0000H
    LJMP TABLE
    ORG 0040H
START:
    DB  63, 6, 91, 79, 102 ,109 ,125, 7, 127,111,119,115,64,0
TABLE:
    
	MOV R0 , #0x77
	MOV R1 , #100
    MOV R2 , #0x06
    MOV R3 , #0x5b
    MOV R4 , #0X3F
    MOV R5 , #0X3F
    MOV R6 , #0X3F
    MOV R7 , #0X3F

MAIN:
	ACALL DELAY
	CLR P2.2 
    CLR P2.3 
    CLR P2.4 
    MOV P0, R0
    ACALL DELAY
    ACALL CLEAR
	
	SETB P2.2 
    CLR P2.3 
    CLR P2.4 
    MOV P0, #0x40
    ACALL DELAY
    ACALL CLEAR
	
    CLR P2.2 
    SETB P2.3 
    CLR P2.4 
    MOV P0, R2
    ACALL DELAY
    ACALL CLEAR

    SETB P2.2 
    SETB P2.3 
    CLR P2.4 
    MOV P0, R3
    ACALL DELAY
    ACALL CLEAR

    CLR P2.2 
    CLR P2.3 
    SETB P2.4 
    MOV P0, R4
    ACALL DELAY
    ACALL CLEAR

    SETB P2.2 
    CLR P2.3 
    SETB P2.4 
    MOV P0, R5
    ACALL DELAY
    ACALL CLEAR

    CLR P2.2 
    SETB P2.3 
    SETB P2.4 
    MOV P0, R6
    ACALL DELAY
    ACALL CLEAR
	
    SETB P2.2 
    SETB P2.3 
    SETB P2.4 
    MOV P0, R7
    ACALL DELAY
    ACALL CLEAR

    SJMP MAIN

CLEAR:
    CLR P2.2 
    CLR P2.3 
    CLR P2.4 
	MOV P0 , #0x00

DELAY: MOV R1, #0XFF 
D1: DJNZ R1, D1
    RET
END