
#include <timer0.h>

#define numOfInterruptsForMin 31

unsigned char numOfMins = 0;
unsigned char *ptr_digits;
unsigned char numOfInterrupts = 0;

// Interrupt service routine for the timer 0 overflow interrupt
ISR(TIMER0_OVF_vect) {
  numOfInterrupts++;
  if (numOfInterrupts == numOfInterruptsForMin) {
    numOfMins--;
    ptr_digits[36] = numOfMins%10;
    ptr_digits[37] = numOfMins/10;
    numOfInterrupts = 0;
    if(numOfMins == 0)
        TIMSK0 = 0;
  }
}

void timer0_init(unsigned char *digits) {
  // Set the timer mode to CTC mode
  TCCR0A = (1 << WGM01);
  // Set the prescaler to 1024
  TCCR0B = (1 << CS00) | (1 << CS02) | (1 << FOC0A);
  // Enable the timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);

  OCR0A = 252;
  sei();
  ptr_digits = digits;
}

// Count down a number of minutes
void timer0_countdown(unsigned char minutes) {
  
  TIMSK0 |= (1 << OCIE0A);
  numOfMins = minutes;
  ptr_digits[36] = numOfMins%10;
  ptr_digits[37] = numOfMins/10;
}