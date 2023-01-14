#include <BitsAndDroidsFlightConnector.h>
#include <TM1637_6D.h>
#include <Encoder.h>


#define scrStdbyCLK 4
#define scrStdbyDIO 5
#define scrActiveCLK 6
#define scrActiveDIO 7
#define scrBRT 2

#define rotCLK 8
#define rotDTA 9
#define rotBtn 10


Encoder rotary(rotCLK, rotDTA);
TM1637_6D screenStdby(scrStdbyCLK, scrStdbyDIO);
TM1637_6D screenActive(scrActiveCLK, scrActiveDIO);
BitsAndDroidsFlightConnector* connector = new BitsAndDroidsFlightConnector;


bool skip = false;
bool readySwap = false; 
int cmdInc, cmdDec = 0;
long oldMhzPos, oldKhzPos = -999;
long newMhzPos, newKhzPos, newPos, oldPos;
String Com1ActiveFreq, Com1StdbyFreq, oldCom1ActiveFreq, oldCom1StdbyFreq = "";


void setup()
{
  Serial.begin(115200);
  Serial.setTimeout(15);

  pinMode(rotBtn, INPUT);
  pinMode(rotBtn, INPUT_PULLUP);
  digitalWrite(rotBtn, HIGH);
  
  screenStdby.init();
  screenStdby.set(scrBRT);

  screenActive.init();
  screenActive.set(scrBRT);

}

void loop()
{
  // Load values
  connector->dataHandling();
  Com1ActiveFreq = connector->getActiveCom1();
  Com1StdbyFreq  = connector->getStandbyCom1();

  // Screen Standby
  if(!Com1StdbyFreq.equals(oldCom1StdbyFreq))
  {
      screenStdby.displayFloat(Com1StdbyFreq.toFloat() / 1000);
      oldCom1StdbyFreq = Com1StdbyFreq;
  }

  // Screen Active
  if(!oldCom1ActiveFreq.equals(Com1ActiveFreq))
  {
      screenActive.displayFloat(Com1ActiveFreq.toFloat() / 1000);
      oldCom1ActiveFreq = Com1ActiveFreq;
  } 

  // Rotary control
  if(!readySwap)
  {
    // Mode 1
    newPos = newMhzPos;
    oldPos = oldMhzPos;
    cmdInc = sendCommands::sendCom1WholeInc;
    cmdDec = sendCommands::sendCom1WholeDec;
  }
  else
  {
    // Mode 2
    newPos = newKhzPos;
    oldPos = oldKhzPos;
    cmdInc = sendCommands::sendCom1FractInc;
    cmdDec = sendCommands::sendCom1FractDecr;
  } 

  newPos = rotary.read();
  if(newPos != oldPos)
  {
    skip = !skip;
    if(newPos < oldPos)
    {
      if(!skip) Serial.println(cmdInc);
    }
    else
    {
      if(!skip) Serial.println(cmdDec);
    }
    oldPos = newPos;
  }

  if(!readySwap) 
    oldMhzPos = oldPos;
  else
    oldKhzPos = oldPos;

  // Rotary button
  if(digitalRead(rotBtn) == LOW)
  {
    if(readySwap) Serial.println(sendCommands::sendSwapCom1);
    readySwap = !readySwap;
    delay(300);
  }

}