#include <BitsAndDroidsFlightConnector.h>
#include <TM1637_6D.h>
#include <Encoder.h>

#define scrStdbyCLK 4
#define scrStdbyDIO 5
#define scrActiveCLK 6
#define scrActiveDIO 7
#define scrAltCLK 11
#define scrAltDIO 12
#define scrBRT 2

#define rotCLK 8
#define rotDTA 9
#define rotBtn 10

enum controlModes { 
  MODE_COM = 1, 
  MODE_NAV = 2, 
  MODE_TRANSPONDER = 3
};

Encoder rotary(rotCLK, rotDTA);
controlModes currentMode = MODE_COM;
TM1637_6D screenStdby(scrStdbyCLK, scrStdbyDIO);
TM1637_6D screenActive(scrActiveCLK, scrActiveDIO);
TM1637_6D screenAlt(scrAltCLK, scrAltDIO);
BitsAndDroidsFlightConnector* connector = new BitsAndDroidsFlightConnector;

bool skip = false;
bool readySwap = false; 
int cmdInc, cmdDec = 0;
long altitudeFCU, oldAltitudeFCU;
long oldMhzPos, oldKhzPos = -999;
long newMhzPos, newKhzPos, newPos, oldPos;
String Com1ActiveFreq, Com1StdbyFreq, oldCom1ActiveFreq, oldCom1StdbyFreq = "";



void screenHandling()
{
  // Standby
  if(!Com1StdbyFreq.equals(oldCom1StdbyFreq))
  {
      screenStdby.displayFloat(Com1StdbyFreq.toFloat() / 1000);
      oldCom1StdbyFreq = Com1StdbyFreq;
  }

  // Active
  if(!oldCom1ActiveFreq.equals(Com1ActiveFreq))
  {
      screenActive.displayFloat(Com1ActiveFreq.toFloat() / 1000);
      oldCom1ActiveFreq = Com1ActiveFreq;
  } 

  // Altitude
  if(oldAltitudeFCU != altitudeFCU)
  {
      screenAlt.displayInteger(altitudeFCU, false);
      oldAltitudeFCU = altitudeFCU;
  } 

}

void pollingCom1()
{
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

  screenAlt.init();
  screenAlt.set(scrBRT);
  
  screenAlt.clearDisplay();

}

void loop()
{
  // Load data
  connector->dataHandling();
  Com1ActiveFreq = connector->getActiveCom1();
  Com1StdbyFreq  = connector->getStandbyCom1();
  altitudeFCU = connector->getIniA310FCUAlt(); //getFenixA320FCUAlt();

  // Refresh data on screens
  screenHandling();

  // Commands
  switch(currentMode)
  {
    case MODE_COM:
      pollingCom1();
      break;

    case MODE_NAV:
      //pollingNav1();
      break;

    case MODE_TRANSPONDER:
      //pollingTransponder();
      break;
  }

}