/*

  I like mechanical watches. I like listening to their heartbeats in an empty room.
  You'll never feel alone with your little ticker.
  
  But it is some kind of problem if you've got more than one self-winding mechanical watch.
  You have to wind them every day. I knew about watch winders, but I want to create that one by myself!


  Cycle:

      - 150 revolutions clockwise in 30 min.

      - 150 revolutions counterclockwise in 30 min.

      - 3 hours of rest

6 cycles per day
300 revolutions per cycle
5 revolutions a minute
1 revolution per 12 sec.

*/


#include <STEPPER_ULN2003APG_2BYJ48.h>

#include <Stepper_2BYJ48.h>



Stepper_2BYJ48 stepper(8, 9, 10, 11, 5);



void setup()
{
}



void loop()
{

  // 150 revolutions clockwise in 30 min.

  stepper.makeRevolutions(150);

  // 150 revolutions counterclockwise in 30 min.

  stepper.makeRevolutions(-150);

  // 3 hours of rest

  for(int i = 0; i < 3600; i++)

    delay(3000);

}
