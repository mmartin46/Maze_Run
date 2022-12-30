// Matthew 5:27
#include <gb/gb.h>

// Sets values for the registers
// in order to obtain volume.
//
// 1000 0000 in binary, turns sound on  
// Sets the volume for both let and right MAX 0x77
// 1111 1111 in binary, selects which channels we want to use (ALL)
void set_volume()
{
   // these registers must be in this order.
   NR52_REG = 0x80; 
   NR50_REG = 0x77;
   NR51_REG = 0xFF; 
}

// Plays a random sound.
void play_sound()
{
   // bit 5-0 => Sound Length
   // 0001 1111 is 0x1F the maximum length
   NR10_REG = 0x1F;

   // Volume envelope
   // bit 7-4 - Intial volume of the envelope (0-0Fh) (0=No Sound)
   // bit 3 - Envelope DIrection (0=Decrease, 1=Increase)
   // bit 2-0 - Number of envelope sweep (n: 0-7) (If zero, stop envelope operation.)
   // 1111 0001 is 0xF1, start at full volume, fade down, 1 envelope sweep (decimal)
   NR42_REG = 0xF1;


   // bits 7-4 - Shif Clock Frequency (s)
   // bit 3 - Counter Step/Width (0=15 bits, 1= bits)
   // bit 2-0 Dividing th ratio of frequencies (r)
   // 0011 0000 is 0x30, shift clock frequency 3, step 0, dividing ratio 0
   NR43_REG = 0x38;

   // 7-0 8 Least Significant bits of frequency (3 Most Significant Bits are set in register 4)
   NR44_REG = 0x30;


   // bit 7 - Initial (1=Restart Sound)
   // bit 6 - Controls if last forever or stops when NR41 ends
   // (1=Sop output when length of NR41 expires)
   // 1100 0000, start sound, not continuous
   NR44_REG = 0xC0;
}