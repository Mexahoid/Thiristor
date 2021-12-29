#include "mbed.h"
 
DigitalOut mainpin(PC_6);
DigitalIn pinx(PC_8, PullDown);

int main() {
    int count = 0; 
    int present = 0;
    while(1) {
        int value = pinx.read();
        
        if (value == 1 && present == 0)
        {
            count++;
            present = 1;
        }
        
        if (value == 0 && present == 1)
        {
            present = 0;
        }
        
        if (count > 1)
        {
            mainpin = 1;
            mainpin = 0;
            count = 0;
        }
    }
}
