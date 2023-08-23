// Vorname, Nachname => John White and Omar Mohammed

#include "inc/tm4c1294ncpdt.h"
#include <stdint.h>

void configPorts()
{
    SYSCTL_RCGCGPIO_R = 0x00001020; // Enables the clock for ports N and F
    while (!(SYSCTL_PRGPIO_R & 0x00001020))
        ; // Waits for clock to be enabled
    GPIO_PORTN_DEN_R = 0x03; // Enables the registers of port N according to the following binary: 0000 0011
    GPIO_PORTN_DIR_R = 0x03; // Sets direction of registers of port N. Lasts 2 registers output; rest is input
    GPIO_PORTF_AHB_DEN_R = 0x11; // Enables the registers of port F according to the following binary: 0000 1011
    GPIO_PORTF_AHB_DIR_R = 0x11; // Sets direction of registers of port F. 5th, 7th, and 8th bits as output, rest as input

}

void configTimer1A()
{
    SYSCTL_RCGCTIMER_R |= (1 << 1); // Enables the clock for timer 1A
    while (!(SYSCTL_PRTIMER_R & 0x02))
        ; // Wait for timer 1 to activate
    TIMER1_CTL_R &= ~(1 << 0); // Stop Timer
    TIMER1_CFG_R = 0x04; // Sets into 16-bit mode
    TIMER1_TAMR_R |= 0x12; // Sets counting direction up and periodic (compare mode)
    TIMER1_TAPR_R = 245 - 1; // Sets pre-scalar value to 245
    TIMER1_TAILR_R = 229 - 1; // Sets load value to 229 to allow counter to count from the bottom to top, which takes one second (ILR)
    TIMER1_CTL_R |= (1 << 0); // Restart timer

}
int main()
{ // GPIO Initialization
    configPorts();

    // Timer Initialization
    configTimer1A();

    // LED control

// all configured pins low (turn off LEDs)
    GPIO_PORTN_DATA_R = 0x00;
    GPIO_PORTF_AHB_DATA_R = 0x00;

    unsigned int counter = 0;
    while (1)
    {

        //counter++;
        switch (counter)
        {
        case (0):
            GPIO_PORTN_DATA_R = 0x00;
            GPIO_PORTF_AHB_DATA_R = 0x00;
            break;
        case (1):
            GPIO_PORTN_DATA_R = 0x00;
            GPIO_PORTF_AHB_DATA_R = 0x01;
            break;
        case (2):
            GPIO_PORTN_DATA_R = 0x00;
            GPIO_PORTF_AHB_DATA_R = 0x10;
            break;
        case (3):
            GPIO_PORTN_DATA_R = 0x00;
            GPIO_PORTF_AHB_DATA_R = 0x17;
            break;
        case (4):
            GPIO_PORTN_DATA_R = 0x01;
            GPIO_PORTF_AHB_DATA_R = 0x00;
            break;
        case (5):
            GPIO_PORTN_DATA_R = 0x01;
            GPIO_PORTF_AHB_DATA_R = 0x01;
            break;
        case (6):
            GPIO_PORTN_DATA_R = 0x01;
            GPIO_PORTF_AHB_DATA_R = 0x10;
            break;
        case (7):
            GPIO_PORTN_DATA_R = 0x01;
            GPIO_PORTF_AHB_DATA_R = 0x17;
            break;
        case (8):
            GPIO_PORTN_DATA_R = 0x02;
            GPIO_PORTF_AHB_DATA_R = 0x00;
            break;
        case (9):
            GPIO_PORTN_DATA_R = 0x02;
            GPIO_PORTF_AHB_DATA_R = 0x01;
            break;
        case (10):
            GPIO_PORTN_DATA_R = 0x02;
            GPIO_PORTF_AHB_DATA_R = 0x10;
            break;
        case (11):
            GPIO_PORTN_DATA_R = 0x02;
            GPIO_PORTF_AHB_DATA_R = 0x09;
            break;
        case (12):
            GPIO_PORTN_DATA_R = 0x03;
            GPIO_PORTF_AHB_DATA_R = 0x00;
            break;
        case (13):
            GPIO_PORTN_DATA_R = 0x03;
            GPIO_PORTF_AHB_DATA_R = 0x01;
            break;
        case (14):
            GPIO_PORTN_DATA_R = 0x03;
            GPIO_PORTF_AHB_DATA_R = 0x10;
            break;
        case (15):
            GPIO_PORTN_DATA_R = 0x03;
            GPIO_PORTF_AHB_DATA_R = 0x17;
            break;
        }

        //since you can only display up to 15 using 4 bits.
        if (counter == 15)
        {
            counter = 0;
        }
        else
        {
            counter++;
        }

        //wait for the timout event
        while ((TIMER1_RIS_R & (1 << 0)) == 0)
        {
            printf("%d\n", TIMER1_TAR_R); //used for debugging purposes
        }
        printf("fwww\n"); //used for debugging purposes
        TIMER1_ICR_R |= (1 << 0); //clear timeout bit in RIS register

    }
    return 0;
}
