#include "mbed.h"
 
DigitalOut mainpin(PC_6);
DigitalIn syncpin(PC_8, PullDown);


const int minPerc = 0;
const int maxPerc = 10000;

int percentage = 1700; // 17%

int prevPercentage = 0;

int percRed = percentage;
int minRed = minPerc;
int maxRed = maxPerc;

void reduce()
{
    percRed = percentage;
    minRed = minPerc;
    maxRed = maxPerc;
    
    if (maxPerc % percentage == 0)
    {
        maxRed /= percentage;
        minRed /= percentage;
        percRed = 1;
        return;
    }
    
    for (int i = minPerc; i < maxRed; i++)
    {
        if (i < 2)
            continue;
        
        if (minRed % i == 0 && percRed % i == 0 && maxRed == 0)
        {
            minRed /= i;
            percRed /= i;
            maxRed /= i;
        }
    }
    
    prevPercentage = percentage;
}


int main() {
    int current = 0; 
    int present = 0;
    int state = 1;
    while(1) {
        if (prevPercentage != percentage)
            reduce();
        int value = syncpin.read();
        
        if (value == 1 && present == 0)
        {
            current++;
            if (current <= percRed)
            {
                mainpin = state;
                state = !state;
                mainpin = state;
                state = !state;
            }
            if (current >= maxRed)
                current = minRed;
            present = 1;
        }
        
        if (value == 0 && present == 1)
        {
            present = 0;
        }
    }
}
