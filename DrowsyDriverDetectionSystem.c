#include <REGX51.H>

// LCD control pins
sbit rs = P3^7;
sbit en = P3^6;

// Eye Blink Sensor and output devices
sbit EyeBlinkSensor = P1^0;
sbit Buzzer = P1^1;

// Motor control pins
sbit M11 = P1^2;
sbit M12 = P1^3;
sbit M21 = P1^4;
sbit M22 = P1^5;

// Delay function
void delay(unsigned int a) {
    unsigned int i, j;
    for(i = 0; i < a; i++)
        for(j = 0; j < 1275; j++);
}

// LCD Command function
void cmd(unsigned char a) {
    rs = 0;
    P2 = a;
    en = 1;
    delay(2);
    en = 0;
}

// LCD Data function
void Data(unsigned char a) {
    rs = 1;
    P2 = a;
    en = 1;
    delay(2);
    en = 0;
}

// LCD String function
void String(unsigned char *p) {  // Corrected function parameter
    while(*p) {
        Data(*p++);
    }
}

// Main function
void main() {
    // Stop motors initially and turn off buzzer
    M11 = 0;
    M12 = 0;
    M21 = 0;
    M22 = 0;
    Buzzer = 0;
    
    // Initialize LCD
    cmd(0x38);  // 8-bit mode
    cmd(0x0E);  // Display ON, cursor ON
    cmd(0x80);  // Cursor at first line
    String(" DROWSY DRIVER ");
    cmd(0xC0);  // Cursor at second line
    String(" DETECTING SYSTEM ");
    delay(500);
    cmd(0x01);  // Clear LCD
    
    while(1) {
        if(EyeBlinkSensor == 0) {  // If sensor detects drowsiness
            Buzzer = 1;
            M11 = 0;
            M12 = 0;
            M21 = 0;
            M22 = 0;
            cmd(0x80);
            String(" DRIVER IS    ");
            cmd(0xC0);
            String(" SLEEPING...  ");
        }
        else {  // Normal condition
            Buzzer = 0;
            M11 = 1;
            M12 = 0;
            M21 = 1;
            M22 = 0;
            cmd(0x80);
            String(" DRIVER IS NOT");
            cmd(0xC0);
            String(" SLEEPING...  ");
        }
        delay(200);
    }
}
