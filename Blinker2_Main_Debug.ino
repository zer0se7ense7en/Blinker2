
#include <FastLED.h>

#define NUM_LEDS_B 14
#define NUM_LEDS_F 11
#define DATA_PIN_BL 11
#define DATA_PIN_BR 10
#define DATA_PIN_FL 12
#define DATA_PIN_FR 13

CRGB ledsBL[NUM_LEDS_B];
CRGB ledsBR[NUM_LEDS_B];
CRGB ledsFL[NUM_LEDS_F];
CRGB ledsFR[NUM_LEDS_F];

const byte Switch1U = 3;
const byte Switch1D = 2;
const byte Switch2U = 4;
const byte Switch2D = 5;
const byte Switch3U = 8;
const byte Switch3D = 9;
const byte Switch4U = 7;
const byte Switch4D = 6;

bool Sw1Up = false;
bool Sw1Mid = false;
bool Sw1Down = false;
bool Sw2Up = false;
bool Sw2Mid = false;
bool Sw2Down = false;
bool Sw3Up = false;
bool Sw3Mid = false;
bool Sw3Down = false;
bool Sw4Up = false;
bool Sw4Mid = false;
bool Sw4Down = false;

byte delaytime = 250;
byte wave;
byte invwave;


void setup() { 

  pinMode(Switch1U, INPUT);
  pinMode(Switch1D, INPUT);
  pinMode(Switch2U, INPUT);
  pinMode(Switch2D, INPUT);
  pinMode(Switch3U, INPUT);
  pinMode(Switch3D, INPUT);
  pinMode(Switch4U, INPUT);
  pinMode(Switch4D, INPUT);

  FastLED.addLeds<WS2812B, DATA_PIN_BL, GRB>(ledsBL, NUM_LEDS_B);
  FastLED.addLeds<WS2812B, DATA_PIN_BR, GRB>(ledsBR, NUM_LEDS_B); 

  FastLED.addLeds<WS2812B, DATA_PIN_FL, GRB>(ledsFL, NUM_LEDS_F);
  FastLED.addLeds<WS2812B, DATA_PIN_FR, GRB>(ledsFR, NUM_LEDS_F); 
   
  FastLED.setMaxPowerInVoltsAndMilliamps(5,3000);
  FastLED.setBrightness(100);
  
  Serial.begin(115200);
}

void SwitchPosUpdate() {
  if(digitalRead(Switch1U) == HIGH) {
    Sw1Up = true; Sw1Mid = false; Sw1Down = false;
  }
  if(digitalRead(Switch1D) == HIGH) {
    Sw1Up = false; Sw1Mid = false; Sw1Down = true;
  }
  if(digitalRead(Switch1U) == LOW && digitalRead(Switch1D) == LOW) {
    Sw1Up = false; Sw1Mid = true; Sw1Down = false;
  }

  if(digitalRead(Switch2U) == HIGH) {
    Sw2Up = true; Sw2Mid = false; Sw2Down = false;
  }
  if(digitalRead(Switch2D) == HIGH) {
    Sw2Up = false; Sw2Mid = false; Sw2Down = true;
  }
  if(digitalRead(Switch2U) == LOW && digitalRead(Switch2D) == LOW) {
    Sw2Up = false; Sw2Mid = true; Sw2Down = false;
  }

  if(digitalRead(Switch3U) == HIGH) {
    Sw3Up = true; Sw3Mid = false; Sw3Down = false;
  }
  if(digitalRead(Switch3D) == HIGH) {
    Sw3Up = false; Sw3Mid = false; Sw3Down = true;
  }
  if(digitalRead(Switch3U) == LOW && digitalRead(Switch3D) == LOW) {
    Sw3Up = false; Sw3Mid = true; Sw3Down = false;
  }

  if(digitalRead(Switch4U) == HIGH) {
    Sw4Up = true; Sw4Mid = false; Sw4Down = false;
  }
  if(digitalRead(Switch4D) == HIGH) {
    Sw4Up = false; Sw4Mid = false; Sw4Down = true;
  }
  if(digitalRead(Switch4U) == LOW && digitalRead(Switch4D) == LOW) {
    Sw4Up = false; Sw4Mid = true; Sw4Down = false;
  }
}

void Switch_Debug() {
  Serial.print("Switch1U: ");Serial.print(digitalRead(Switch1U));
  Serial.print(" Switch1D: ");Serial.print(digitalRead(Switch1D));
  Serial.print(" Switch2U: ");Serial.print(digitalRead(Switch2U));
  Serial.print(" Switch2D: ");Serial.print(digitalRead(Switch2D));
  Serial.print(" Switch3U: ");Serial.print(digitalRead(Switch3U));
  Serial.print(" Switch3D: ");Serial.print(digitalRead(Switch3D));
  Serial.print(" Switch4U: ");Serial.print(digitalRead(Switch4U));
  Serial.print(" Switch4D: ");Serial.println(digitalRead(Switch4D));
}

void Pos_Debug() {
  Serial.print("Sw1Up: ");Serial.print(Sw1Up);
  Serial.print(" Sw1Mid: ");Serial.print(Sw1Mid);
  Serial.print(" Sw1Down: ");Serial.print(Sw1Down);
  Serial.print(" Sw2Up: ");Serial.print(Sw2Up);
  Serial.print(" Sw2Mid: ");Serial.print(Sw2Mid);
  Serial.print(" Sw2Down: ");Serial.print(Sw2Down);
  Serial.print(" Sw3Up: ");Serial.print(Sw3Up);
  Serial.print(" Sw3Mid: ");Serial.print(Sw3Mid);
  Serial.print(" Sw3Down: ");Serial.print(Sw3Down);
  Serial.print(" Sw4Up: ");Serial.print(Sw4Up);
  Serial.print(" Sw4Mid: ");Serial.print(Sw4Mid);
  Serial.print(" Sw4Down: ");Serial.println(Sw4Down);
}

void LED_Debug() {
  if(Sw1Up) {
    for(byte i = 0; i < NUM_LEDS_B; i++) {
      ledsBL[i].setHue(0);
    }
    FastLED.show();
  }
  if(Sw1Mid) {
    for(byte i = 0; i < NUM_LEDS_B; i++) {
      ledsBL[i].setRGB(0,0,0);
    }
    FastLED.show();
  }
  if(Sw1Down) {
    for(byte i = 0; i < NUM_LEDS_B; i++) {
      ledsBL[i].setHue(96);
    }
    FastLED.show();
  }

  if(Sw2Up) {
    for(byte i = 0; i < NUM_LEDS_F; i++) {
      ledsFL[i].setHue(32);
    }
    FastLED.show();
  }
  if(Sw2Mid) {
    for(byte i = 0; i < NUM_LEDS_F; i++) {
      ledsFL[i].setRGB(0,0,0);
    }
    FastLED.show();
  }
  if(Sw2Down) {
    for(byte i = 0; i < NUM_LEDS_F; i++) {
      ledsFL[i].setHue(128);
    }
    FastLED.show();
  }

  if(Sw3Up) {
    for(byte i = 0; i < NUM_LEDS_F; i++) {
      ledsFR[i].setHue(64);
    }
    FastLED.show();
  }
  if(Sw3Mid) {
    for(byte i = 0; i < NUM_LEDS_F; i++) {
      ledsFR[i].setRGB(0,0,0);
    }
    FastLED.show();
  }
  if(Sw3Down) {
    for(byte i = 0; i < NUM_LEDS_F; i++) {
      ledsFR[i].setHue(160);
    }
    FastLED.show();
  }

  if(Sw4Up) {
    for(byte i = 0; i < NUM_LEDS_B; i++) {
      ledsBR[i].setHue(224);
    }
    FastLED.show();
  }
  if(Sw4Mid) {
    for(byte i = 0; i < NUM_LEDS_B; i++) {
      ledsBR[i].setRGB(0,0,0);
    }
    FastLED.show();
  }
  if(Sw4Down) {
    for(byte i = 0; i < NUM_LEDS_B; i++) {
      ledsBR[i].setHue(192);
    }
    FastLED.show();
  }
}

void loop() {
  SwitchPosUpdate();
}
