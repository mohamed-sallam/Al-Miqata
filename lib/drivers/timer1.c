#include <timer1.h>
#include <avr/interrupt.h>

volatile char numOfMins1 = 0;

// Interrupt service routine for the timer 1 CTC interrupt
ISR(TIMER1_OVF_vect)
{
    // Decrement the timer counter
    TCNT1--;
    // If the timer counter reaches 0,
    if (TCNT1 == 0)
    {
        // Indicate that a minute has passed
        numOfMins1--;
        // If the number of minutes is 0,
        if (numOfMins1 == 0)
        {
            timer0_countdown(PrayerTimes_getRemainingTime());
            timer1_countdown(PrayerTimes_getNextTime());
        }
    }
}

void timer1_init()
{
    // Set the timer mode to normal counting mode
    TCCR1A = 0;
    // Set the prescaler to 256
    TCCR1B = _BV(CS12);
    // Enable the timer overflow interrupt
    TIMSK1 |= _BV(TOIE1);
    sei();
}

// Count down a number of minutes
void timer1_countdown(int16_t minutes)
{
    // Set the timer counter to the number of minutes
    TCNT1 = minutes * 60000;
    // Start the timer
    TCCR1B |= _BV(TCNT1);
    numOfMins1 = minutes;
}