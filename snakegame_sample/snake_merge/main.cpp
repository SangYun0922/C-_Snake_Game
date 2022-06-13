#include "SnakeGame.h"

int main()
{

  SnakeGame StartGame;
  while(StartGame.stage<=4)
  {
    beep();
    StartGame.Start(StartGame.stage);
    // StartGame.Start(3);
    if(StartGame.death == TRUE)
    {
      return 0;
    }
  }
  return 0;
}
