

//Very similar to Project 2_Pin_Change_Interrupt.  
//Press sw2 when the led bars line up to make the display flash
//But strangely does not include any interrupts

#include "Reaction_time_tester.h"
#include "display_header.h"
#include "display_subroutines.c"

int main (void)
{ unsigned int Random_num;
  unsigned int PORT_1, PORT_2;
unsigned char PRN_counter, shift_display;
setup_HW;
 _delay_ms(10);
 PRN_counter = 0;
 Random_num = PRN_16bit_GEN (0, &PRN_counter);
  while (switch_3_up)wdr();

  PORT_1 = 1;
  PORT_2 = 0x8000;
  while (1)
  { while (1)
    { Timer_T0_10mS_delay_x_m(2);
      while (switch_3_down)wdr();

      shift_PORT_1;
      shift_PORT_2;
      display_binary(PORT_1, PORT_2, 10);

      if (PORT_1 == PORT_2)
      { 
        
        Timer_T0_10mS_delay_x_m(35);
        if (switch_3_down)break;
        else while (switch_3_up)wdr();
      }

      if (PORT_1 != PORT_2)
      {
        Timer_T0_10mS_delay_x_m(16);
      }
    }

    while (switch_3_down)
    {
      flash_display;
    }
  }
}
