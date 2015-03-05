#include <Arduino.h>
#include <IRremote.h>
#include "SimpleTimer.h"

//enum defines
#include "pstate.h"

//IR code defines
#include "ircodes.h"

//HID keycodes and functions
#include "hidkeys.h"

//function prototypes

//this code occurs at the beginning of every code
#define IR_PRE 0x7FF00000

//pin defines
#define IR_RECV_PIN 9 //IR receiver sensor
#define PWR_ACT_PIN 8 //pc power button pins
#define PWR_STATUS_PIN 7 //pc status pin (needs to be an interrupt)
#define PWR_STATUS_INT 4 //interrupt for PWR_STATUS_PIN
#define LED_STATUS_PIN 5 //actual physical LED
#define PWR_BUTTON_PIN 4 //actual physical button

#define CEC_IN_PIN 0 //data in from CEC
#define CEC_OUT_PIN 1 //data out to CEC

void    HID_SendReport(uint8_t id, const void* data, int len);

IRrecv irrecv(IR_RECV_PIN);
SimpleTimer timer;

decode_results results;
uint8_t pwr_brightness = 0;
PState pwr_status = Off;
int fadeAmount = 5;
int brightness = 0;

bool _pwrState;

uint16_t lastKey = 0;
HIDType lastType = HIDKeyboard;

ConsumerData consumer;
KeyboardData keyboard;
KeyCode prevKey;

volatile unsigned long firstPulseTime;
volatile unsigned long lastPulseTime;
volatile unsigned long numPulses;

void HIDSend(KeyCode *kcode);
void isr();
void pollPwrState();
void finishPollPwrState();
void pollPwrButton();
void pollIR();
void powerAction();
void unpressPwrButton();
void setup();
void loop();


void HIDSend(KeyCode *kcode)
{
  switch(kcode->type)
    {
    case HIDConsumer:
      consumer.code = kcode->code;
      HID_SendReport(3,&consumer,sizeof(struct ConsumerData));
      break;
    case HIDKeyboard:
    default:
      keyboard.keys[0] = kcode->code;
      HID_SendReport(2,&keyboard,sizeof(struct KeyboardData));
      break;
    }
};

void isr()
{
  unsigned long now = micros();
  if (numPulses == 1)
  {
    firstPulseTime = now;
  }
  else
  {
    lastPulseTime = now;
  }
  ++numPulses;
}

void pollPwrState()
{
  numPulses = 0;                      // prime the system to start a new reading
  attachInterrupt(PWR_STATUS_INT, isr, CHANGE);    // enable the interrupt for rising and falling to halve response time
  timer.setTimeout(1200, finishPollPwrState);
}

void finishPollPwrState()
{
  detachInterrupt(PWR_STATUS_INT);
  float freq = (numPulses < 3) ? 0 : (500000.0 * (float)(numPulses - 2))/(float)(lastPulseTime - firstPulseTime);
  
  //need to check if it's flashing. looks like just less than 500ms per on/off. 
  //if it's just off or just on that tells us something too.
  
  //we will poll every 1.5 seconds. That should give time for at least 1 full cycle, 
  //and so freqmeasure.available should be at least 1.
  if(freq != 0)
  {
    pwr_status = Sleep;
  }
  else //signal has been unchanged for at least 1.2 seconds
  {
    if(digitalRead(PWR_STATUS_PIN))
      pwr_status = On;
    else
      pwr_status = Off;
  }
}

void pollPwrButton()
{
  if(digitalRead(PWR_BUTTON_PIN))
  {
    powerAction();
  }
}

void pollIR()
{
  KeyCode kcode;
  if (irrecv.decode(&results)) {
    //each code is prepended with IR_PRE, and the entire 
    //thing is one's complement of the LIRC definitions in 
    //ircodes.h, so we need to invert the value and then OR
    //with the IR_PRE header.
    
    switch((long unsigned int)((~results.value)^IR_PRE))
    {
    case IR_UP:
      Serial.println("UP");
      kcode.code = RAW_KEY_UPARROW;
      kcode.type = HIDKeyboard;
      break;
    case IR_DOWN:
      Serial.println("DOWN");
      kcode.code = RAW_KEY_DOWNARROW;
      kcode.type = HIDKeyboard;
      break;
    case IR_LEFT:
      Serial.println("LEFT");
      kcode.code = RAW_KEY_LEFTARROW;
      kcode.type = HIDKeyboard;
      break;
    case IR_RIGHT:
      Serial.println("RIGHT");
      kcode.code = RAW_KEY_RIGHTARROW;
      kcode.type = HIDKeyboard;
      break;
    case IR_BACK:
      Serial.println("BACK");
      kcode.code = RAW_KEY_ESCAPE;
      kcode.type = HIDKeyboard;
      break;
    case IR_OK:
      Serial.println("OK");
      kcode.code = RAW_KEY_ENTER;
      kcode.type = HIDKeyboard;
      break;
    case IR_MEDIA:
      Serial.println("MEDIA");
      kcode.code = HID_MEDIA_PC;
      kcode.type = HIDConsumer;
      break;
    case IR_PLAYPAUSE:
      Serial.println("PLAY/PAUSE");
      kcode.code = HID_PLAYPAUSE;
      kcode.type = HIDConsumer;
      break;
    case IR_BLUE:
      Serial.println("BLUE");
      kcode.code = RAW_KEY_F13; //If I can hack Qt then I can use HID_BLUE as defined
      kcode.type = HIDKeyboard;
      break;
    case IR_YELLOW:
      Serial.println("YELLOW");
      kcode.code = RAW_KEY_F14;
      kcode.type = HIDKeyboard;
      break;
    case IR_GREEN:
      Serial.println("GREEN");
      kcode.code = RAW_KEY_F15;
      kcode.type = HIDKeyboard;
      break;
    case IR_RED:
      Serial.println("RED");
      kcode.code = RAW_KEY_F16;
      kcode.type = HIDKeyboard;
      break;
    case IR_TEXT:
      Serial.println("TEXT");
      kcode.code = RAW_KEY_F17;
      kcode.type = HIDKeyboard;
      break;
    case IR_RADIO:
      Serial.println("RADIO");
      kcode.code = RAW_KEY_F18;
      kcode.type = HIDKeyboard;
      break;
    case IR_PRINT:
      Serial.println("TEXT");
      kcode.code = HID_AL_WORD;
      kcode.type = HIDConsumer;
      break;
    case IR_VIDEO:
      Serial.println("VIDEO");
      kcode.code = HID_AL_MOVIE;
      kcode.type = HIDConsumer;
      break;
    case IR_IMAGES:
      Serial.println("IMAGES");
      kcode.code = HID_AL_IMAGE;
      kcode.type = HIDConsumer;
      break;
    case IR_RECORD:
      Serial.println("RECORD");
      kcode.code = HID_AL_CAPTURE;
      kcode.type = HIDConsumer;
      break;
    case IR_AUDIO:
      Serial.println("AUDIO");
      kcode.code = HID_AL_AUDIO;
      kcode.type = HIDConsumer;
      break;
    case IR_TV:
      Serial.println("TV");
      kcode.code = HID_MEDIA_TV;
      kcode.type = HIDConsumer;
      break;
    case IR_EJECTCD:
      Serial.println("EJECT CD");
      kcode.code = HID_EJECT;
      kcode.type = HIDConsumer;
      break;
    case IR_SLIDESHOW:
      Serial.println("SLIDESHOW");
      kcode.code = HID_AL_PRESENTATION;
      kcode.type = HIDConsumer;
      break;
    case IR_ASPECT:
      Serial.println("ASPECT");
      kcode.code = HID_AL_SPREADSHEET;
      kcode.type = HIDConsumer;
      break;
    case IR_INFO:
      Serial.println("INFO");
      kcode.code = HID_HELP;
      kcode.type = HIDConsumer;
      break;
    case IR_TUNER:
      Serial.println("TUNER");
      kcode.code = HID_MEDIA_TUNER;
      kcode.type = HIDConsumer;
      break;
    case IR_DVD:
      Serial.println("DVD");
      kcode.code = HID_MEDIA_DVD;
      kcode.type = HIDConsumer;
      break;
    case IR_NUMERIC_STAR:
      Serial.println("STAR");
      kcode.code = RAW_KEY_KP_STAR;
      kcode.type = HIDKeyboard;
      break;
    case IR_NUMERIC_POUND:
      Serial.println("POUND");
      kcode.code = RAW_KEY_POUND;
      kcode.type = HIDKeyboard;
      break;
    default:
      Serial.print("Unknown code ");
      Serial.println(~results.value^IR_PRE, HEX);
    }
    HIDSend(&kcode);
  }
  else //pick up the keys
  {
    if(consumer.code != 0x0000)
    {
      kcode.type = HIDConsumer;
      kcode.code = 0x0000;
      HIDSend(&kcode);
    }
    
    if(keyboard.keys[0] != 0x00)
    {
      kcode.type = HIDKeyboard;
      kcode.code = 0x00;
      HIDSend(&kcode);
    }
  }
  irrecv.resume(); // Receive the next value
}

void powerAction() {
  switch(pwr_status)
  {
    case Off://if power is off, press the button for 500ms
      digitalWrite(PWR_ACT_PIN, HIGH);
      timer.setTimeout(500, unpressPwrButton);
      break;
    case On://if power is on, send the keyboard power event
      KeyCode kcode;
      kcode.type = HIDKeyboard;
      kcode.code = RAW_KEY_POWER;
      HIDSend(&kcode);
      break;
    case Sleep:
      digitalWrite(PWR_ACT_PIN, HIGH);
      timer.setTimeout(500, unpressPwrButton);
      break;
  }
}

void unpressPwrButton() {
  digitalWrite(PWR_ACT_PIN, LOW);
}

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  
  //set up led pin as output
  pinMode(LED_STATUS_PIN, OUTPUT);
  pinMode(PWR_ACT_PIN, OUTPUT);
  pinMode(PWR_BUTTON_PIN, INPUT);
  pinMode(PWR_STATUS_PIN, INPUT);
  
  //init data structures
  consumer.code=0x0000;
  for(int j=0;j<5;j++) consumer.data[j] = 0x00;
  keyboard.modifiers=0x00;
  for(int j=0;j<6;j++) keyboard.keys[j] = 0x00;
  
  timer.setInterval(50, pollIR); //check for more keypresses
  timer.setInterval(1500, pollPwrState); //check current state once per 1.5 seconds
  timer.setInterval(50, pollPwrButton); //also poll for the power button status
}

void loop() 
{
  //we can only get the power state every second or so, by looking for a 
  //blinking, on, or off signal. Thus, we only check it here
  //now, if the PC has powered on, set the LED to on. Otherwise, 
  //off or sleep.
  switch(pwr_status)
  {
    case On:
      analogWrite(LED_STATUS_PIN, 255);
      break;
    case Sleep:
      analogWrite(LED_STATUS_PIN, brightness);

      // change the brightness for next time through the loop:
      brightness = brightness + fadeAmount;

      // reverse the direction of the fading at the ends of the fade:
      if (brightness == 0 || brightness == 255) {
	fadeAmount = -fadeAmount;
      }
      break;
    case Off:
    default:
      analogWrite(LED_STATUS_PIN, 0);
      brightness = 0;
      fadeAmount = 5;
      break;
  }
  delay(100);
}

