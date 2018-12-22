

/*

#include <CloudX\M633.h>
#include <CloudX\SoundGenerator.h>

#define noteArraySize 49
#define C4 262

#define button pin2

const unsigned int note[noteArraySize] =
  { 
    660, 588, 524, 494, 440, 392, 440, 494,
    660, 588, 524, 494, 440, 392, 440, 494,
    524, 660, 784, 698, 660, 524, 660, 588,
    524, 440, 524, 660, 698, 880, 784, 698,
    660, 660, 784, 698, 660, 524, 660, 588,
    524, 440, 524, 660, 698, 880, 784, 698,
    660
  }; 

const unsigned long note_msecDuration[noteArraySize] =
  {
    1200, 1200, 1200, 1200, 1200, 1200, 1200, 1200,
    1200, 1200, 1200, 1200, 1200, 1200, 1200, 1200,
    600, 600, 600, 600, 600, 600, 900, 300,
    600, 600, 600, 600, 600, 600, 900, 300,
    600, 600, 600, 600, 600, 600, 900, 300,
    600, 600, 600, 600, 600, 600, 900, 300,
    2400
 }; 



setup(){
           //setup here
           
           Sound_setting(1);
           pinMode(2, INPUT);        

    loop() {
           //Program here 
           
          Sound_play(note, note_msecDuration, noteArraySize);
          delayMs(2000);
          
          if(button)
               Sound_notePlayStart(C4);
          else if(!button)
               Sound_notePlayStop();
          
         } 
     } 

*/

#ifndef _LIBRARY_H
#include <CloudX\library.h>
#endif


#ifndef _SoundGen_H_
#define _SoundGen_H_ 

unsigned short timer1H, timer1L;
unsigned char _soundPin;
 
Sound_setting(unsigned char soundPin) {          
                
                    T1CONbits.TMR1ON  = 0;                                    // Timer OFF
                    T1CONbits.T1OSCEN = 1;
                    T1CONbits.TMR1CS  = 0;                                    // Use internal clock
                    T1CONbits.T1CKPS0 = 0;                                    // Prescaler = 1
                    T1CONbits.T1CKPS1 = 0;                                    // Prescaler = 1

                    T1CONbits.TMR1ON = HIGH;
                    PIR1bits.TMR1IF  = LOW;
                    PIE1bits.TMR1IE  = HIGH;                                // enables timer1 interrupt
                    INTCON           = 0xC0;                                // enables global and peripheral interrupts

                    pinMode(soundPin, OUTPUT);
                    PinSelect(soundPin, LOW);

                    _soundPin = soundPin;
       }


milisecDelay(unsigned long milisec) {
                   while(milisec-- isNot 0)
                          delayMs(1); 
				}
                   

 //
 // The note is played, with the specified frequency and duration, in this function
 //
                //FORMULA => TMR1H:TMR1L = 65,536 - T /(4 * Tosc * Prescaler value)
                //T = 500,000 /freq (microSec)
                //Prescaler = 1
                //Tosc = 1/20,000,000
                //TMR1H:TMR1L = 65,536 - (500000 / (4 * (1/20) * 1* freq))
                //TMR1H:TMR1L = 65536 - ((500000 * 5) / freq)
                //
                
 Sound_plays(unsigned int HertzFreq, unsigned int milisecDuration) {
                  float oscPeriod;
                  oscPeriod        = (500000.0 * 5) / HertzFreq;
                  oscPeriod        = 65536 - oscPeriod;
                  timer1H          = (byte)(oscPeriod / 256);
                  timer1L          = (byte)(oscPeriod - 256*timer1H);  //(byte)oscPeriod % 256
                  TMR1H            = timer1H;
                  TMR1L            = timer1L;
                  T1CONbits.TMR1ON = HIGH;
                  milisecDelay(milisecDuration);
                  T1CONbits.TMR1ON = LOW;
           }

 Sound_notePlayStart(unsigned int noteFrequency) {
                 
                  float oscPeriod;
                  oscPeriod        = (500000.0 * 5) / noteFrequency;
                  oscPeriod        = 65536 - oscPeriod;
                  timer1H          = (byte)(oscPeriod / 256);
                  timer1L          = (byte)(oscPeriod - 256*timer1H);  //(byte)oscPeriod % 256
                  TMR1H            = timer1H;
                  TMR1L            = timer1L;
                  T1CONbits.TMR1ON = HIGH;
             }
              
 Sound_notePlayStop() {
            T1CONbits.TMR1ON = LOW;
            delayMs(100);
        }
// 
// timer interrupt service for the sound generation
// 
interrupt _soundGen_() {
 if(PIR1bits.TMR1IF) {
    TMR1H           = timer1H; 
    TMR1L           = timer1L;
    
    if(readPin(_soundPin))
        digitalWrite(_soundPin, LOW);
    else
        digitalWrite(_soundPin, HIGH);
        
    PIR1bits.TMR1IF = LOW; 
	}
   } 

Sound_play(const unsigned int *noteArray, const unsigned long *note_msecDuration, int noteArraySize)  {
          int pointer; 
           
           for(pointer = 0; pointer < noteArraySize; pointer++) {
               Sound_plays(noteArray[pointer], note_msecDuration[pointer]);
               delayMs(100);  //the interval between notes
            }               
     }

#endif   //#ifndef _SoundGen_H_
               