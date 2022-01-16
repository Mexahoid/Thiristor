#include "mbed.h"
 
DigitalOut mainpin(PC_6);
DigitalIn syncpin(PC_8, PullDown);


int p = 170; // 17%
int N = 10;

void send_pulse()
{
    mainpin = 1;
    mainpin = 0;
}

int is_it_time(int last, int current, int count, int max)
{
    if (current == 1)
        return 1;
    
    int ratio = max / count;
    
    if (current == last + ratio)
        return 1;
    
    return 0;
}

int main()
{
    int lambda = 0;
    
    int p = 170; // 170/1000
    int N = 10;
    
    int A = p * N / 1000;  // Целая часть
    int B = p * N % 1000;  // Остаток

    lambda = 0;
    
    int period = 0;
    
    
    int present = 0;
    
    int lA = (lambda + B) / 1000;
    int last = 1;
    
    int next = 0;
    
    
    while (1)
    {
        int value = syncpin.read();
        
        if (value == 1 && present == 0)
        {
            next = !next;
                
            
            present = 1;
            
            if (next)
            {
                if (period == 0)
                {
                    lA = (lambda + B) / 1000;
                    last = 1;
                }
                period++;
                present = 1;
            }
            
            
            if (lA == 0)
            {
                if (is_it_time(last, period, 1, N))
                {
                    send_pulse();
                }
            }
            else
            {
                if (is_it_time(last, period, 2 * lA, N))
                {
                    send_pulse();
                    if (!next)
                        last = period;
                 }
            }
            
            
            if (period == N && next)
            {
                lambda = (lambda + B) % 1000;
                period = 0;
            }
            
            
        }
        
        if (value == 0 && present == 1)
        {
            present = 0;
        }
        
    }
    
    return 0;
}
