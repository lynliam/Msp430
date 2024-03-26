#include "msp430f5529.h"

void main()
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    P1DIR |= 0x01; // Set P1.0 to output direction
    volatile unsigned int i; // volatile to prevent optimization
    while (1)
    {
        P1OUT ^= 0x01; // Toggle P1.0 using exclusive-OR
        for (i = 10000; i > 0; i--); // Delay
    }
}

