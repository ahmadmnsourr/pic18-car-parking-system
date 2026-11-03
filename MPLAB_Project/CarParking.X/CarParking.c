#include <p18f45k22.h>
#include "LCD4lib.h"
#include "BCDlib.h"

char userpass = 0x00;
char password = 0x01;
char DisplayStates[] = {0X39, 0X30, 0X73, 0XED};
char ParkingTimer = 0x00;
char TimerDigits[3];

char ParkingFee[5];
char DisplayParkingFee[2];
char ParkedTime = 0X00;
char OneDigitnb[1];
char TwoDigitnb[2];

void Setup() {
    TRISA = 0X00;
    TRISB = 0XFF;
    TRISC = 0X00;
    TRISD = 0X00;
    TRISE = 0X00;
    ANSELA = 0X00;
    ANSELB = 0X00;
    ANSELC = 0X00;
    ANSELD = 0X00;
    ANSELE = 0X00;
    PORTA = DisplayStates[3];
    PORTD = 0X80;
    PORTC = 0X00;
    INTCON2bits.RBPU = 0;
    INTCONbits.GIE = 1;
    INTCON2bits.INTEDG0 = 0;
    INTCON2bits.INTEDG1 = 0;
    INTCON2bits.INTEDG2 = 0;
    INTCON3bits.INT1IE = 1;
    INTCONbits.TMR0IE= 1;
}
void LeaveParking(){
     if (INTCON3bits.INT2IF) {
            T0CON = 0b00000011;
            INTCON3bits.INT2IF = 0;
            PORTEbits.RE2 = 1;
            InitLCD();
            ParkedTime = ParkingTimer;
            if(ParkedTime > 3){
                if(ParkedTime<20){
                    if(ParkedTime%2==0)
                    {
                            ParkedTime = ParkedTime / 2;
                            Bin2AscE(ParkedTime,ParkingFee);
                            OneDigitnb[0] = ParkingFee[4];
                            DispRomStr(Ln1Ch0, (ROM) "PARKING FEE:");
                            DispVarStr(OneDigitnb, Ln2Ch0, 2);
                            DispRomStr(Ln2Ch2, (ROM) "$");
                            DispRomStr(Ln2Ch4, (ROM) "Thank you!");
                    }
                    else
                    {
                        ParkedTime = ParkedTime / 2;
                        Bin2AscE(ParkedTime,ParkingFee);

                            OneDigitnb[0] = ParkingFee[4];
                            DispRomStr(Ln1Ch0, (ROM) "PARKING FEE:");
                            DispVarStr(OneDigitnb, Ln2Ch0, 2);
                            DispRomStr(Ln2Ch1, (ROM) ".5");
                            DispRomStr(Ln2Ch4, (ROM) "$");
                            DispRomStr(Ln2Ch6, (ROM) "Thank you!");
                    }
            }
                else
                {
                    if(ParkedTime%2==0)
                    {
                            ParkedTime = ParkedTime / 2;
                            Bin2AscE(ParkedTime,ParkingFee);
                            TwoDigitnb[0] = ParkingFee[3];
                            TwoDigitnb[1] = ParkingFee[4];
                            DispRomStr(Ln1Ch0, (ROM) "PARKING FEE:");
                            DispVarStr(TwoDigitnb, Ln2Ch0, 2);
                            DispRomStr(Ln2Ch2, (ROM) "$");
                            DispRomStr(Ln2Ch4, (ROM) "Thank you!");
                    }
                    else
                    {
                        ParkedTime = ParkedTime / 2;
                        Bin2AscE(ParkedTime,ParkingFee);

                            TwoDigitnb[0] = ParkingFee[3];
                            TwoDigitnb[1] = ParkingFee[4];
                            DispRomStr(Ln1Ch0, (ROM) "PARKING FEE:");
                            DispVarStr(TwoDigitnb, Ln2Ch0, 2);
                            DispRomStr(Ln2Ch2, (ROM) ".5");
                            DispRomStr(Ln2Ch4, (ROM) "$");
                            DispRomStr(Ln2Ch6, (ROM) "Thank you!");
                    }
                }
            }
            else{
                DispRomStr(Ln1Ch0, (ROM) "Thank you!");
            }
            Setup();
    }
}
#pragma code ISR=0x0008
#pragma interrupt ISR
void ISR() {

                PORTDbits.RD7 = 1;
                PORTEbits.RE0 = 0;
                PORTEbits.RE1 = 0;
                INTCON3bits.INT1IF = 0;
                ParkingTimer = 0x00;
                PORTA = DisplayStates[3];
                T0CON = 0b10000011;
                TMR0H = (65536 - 62500) / 256;
                TMR0L = (65536 - 62500) % 256;

                while(PORTBbits.RB2){
                     if(INTCONbits.TMR0IF){
                        INTCONbits.TMR0IF = 0;
                        TMR0H = (65536 - 62500) / 256;
                        TMR0L = (65536 - 62500) % 256;
                        ParkingTimer ++;
                        Bin2Bcd (ParkingTimer, TimerDigits);
                        PORTC = ((TimerDigits[1]<<4) | TimerDigits[2]);
                     }
                  }
}

void DetectCar(){
    if (INTCONbits.INT0IF) {
            INTCONbits.INT0IF = 0;
            InitLCD();
            PORTDbits.RD7 = 1;
            PORTA = DisplayStates[2];
            PORTEbits.RE2 = 0;
            while(1){
                if(!PORTBbits.RB3){
                    userpass = PORTB >> 4;
                    if (userpass == password) {
                        PORTDbits.RD7 = 0;
                        PORTEbits.RE0 = 1;
                        PORTA = DisplayStates[0];
                        PORTEbits.RE1 = 1;
                        break;
                    } else {
                        PORTA = DisplayStates[1];
                        PORTDbits.RD7 = 1;
                    }
                }
        }
    }
}

void main() {
    Setup();
    while (1){
            DetectCar();
            LeaveParking();
    }
}