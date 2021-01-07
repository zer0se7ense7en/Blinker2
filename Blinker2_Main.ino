
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
  FastLED.setBrightness(255);
  
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

void Main() {
  if(Sw2Down) {
    Blinker();
  }
  else if(Sw2Mid) {
    Sonst();
  }
  else if(Sw2Up) {
    Siren();
  }
}
// ->
void Blinker() {
  // Kein Standlicht
  if(Sw3Down) {
    FastLED.clear();
    FastLED.show();
    // Blinker Links Normal
    if(Sw1Mid && Sw4Down) {
      colorBL(32,0); // orange
      colorFL(32,0); // orange
       wait(2); // 0.5 second
      
      cleanFL(0);
      cleanBL(0);
       wait(2); // 0.5 second
      
      SwitchPosUpdate();
    }

    // Blinker Rechts Normal
    if(Sw4Mid && Sw1Down) {
      colorBR(32,0); // orange
      colorFR(32,0); // orange
       wait(2); // 0.5 second
      
      cleanFR(0);
      cleanBR(0);
       wait(2); // 0.5 second
      
      SwitchPosUpdate();
    }

    // Blinker Beide Normal
    if(Sw4Mid && Sw1Mid) {
      colorBL(32,0); // orange
      colorFL(32,0); // orange
      colorBR(32,0); // orange
      colorFR(32,0); // orange
       wait(2); // 0.5 second

      FastLED.clear(); // faster than cleanFL(0);cleanFR(0);cleanBL(0);cleanBR(0);
       wait(2); // 0.5 second
      
      SwitchPosUpdate();
    }
    // Blinker Links Achtung!
    if(Sw1Up && !Sw4Up) {
      colorBL(32,0);
      colorFL(32,0);
      colorFR(32,0);
       wait(0.25);
      cleanFR(0);
       wait(0.25);
      colorFR(32,0);
       wait(0.25);
      cleanFR(0);
       wait(0.25);
      colorFR(32,0);
       wait(0.25);
      cleanFR(0);
       wait(0.25);
      colorFR(32,0);
       wait(0.25);
      cleanFR(0);
       wait(0.25);
      cleanBL(0);
      cleanFL(0);
      colorFR(32,0);
       wait(0.25); // M1
      cleanFR(0);
       wait(0.25);
      for(byte j = 0; j < 2; j++) {
        colorFL(32,0);
        colorFR(32,0);
         wait(0.25);
        cleanFL(0);
        cleanFR(0);
         wait(0.25);
      }
      cleanFL(0);
      colorFR(32,0);
       wait(0.25);
      cleanFR(0);
       wait(0.25);
    }
    // Blinker Rechts Achtung!
    if(Sw4Up && !Sw1Up) {
      colorBR(32,0);
      colorFR(32,0);
      colorFL(32,0);
       wait(0.25);
      cleanFL(0);
       wait(0.25);
      colorFL(32,0);
       wait(0.25);
      cleanFL(0);
       wait(0.25);
      colorFL(32,0);
       wait(0.25);
      cleanFL(0);
       wait(0.25);
      colorFL(32,0);
       wait(0.25);
      cleanFL(0);
       wait(0.25);
      cleanBR(0);
      cleanFR(0);
      colorFL(32,0);
       wait(0.25); // M1
      cleanFL(0);
       wait(0.25);
      for(byte j = 0; j < 2; j++) {
        colorFR(32,0);
        colorFL(32,0);
         wait(0.25);
        cleanFR(0);
        cleanFL(0);
         wait(0.25);
      }
      cleanFR(0);
      colorFL(32,0);
       wait(0.25);
      cleanFL(0);
       wait(0.25);      
    }
    // Blinker Beide Achtung!
    if(Sw1Up && Sw4Up) {
      colorFL(32,0);
      colorFR(32,0);
       wait(0.125);
      cleanFL(0);
      cleanFR(0);
      colorBL(32,0);
      colorBR(32,0);
       wait(0.25);
      cleanBL(0);
      cleanBR(0);
       wait(0.125);
    }

  }
  // Standlicht Hinten Rot
  if(Sw3Mid) {
    colorBL(0,0);
    colorBR(0,0);
    cleanFL(0);
    cleanFR(1);
    // Blinker Links Normal
    if(Sw1Mid && Sw4Down) {
      colorBL(32,0); // orange
      colorFL(32,0); // orange
       wait(2); // 0.5 second
      
      cleanFL(0);
      colorBL(0,0);
       wait(2); // 0.5 second
      
      SwitchPosUpdate();
    }

    // Blinker Rechts Normal
    if(Sw4Mid && Sw1Down) {
      colorBR(32,0); // orange
      colorFR(32,0); // orange
       wait(2); // 0.5 second
      
      cleanFR(0);
      colorBR(0,0);
       wait(2); // 0.5 second
      
      SwitchPosUpdate();
    }

    // Blinker Beide Normal
    if(Sw4Mid && Sw1Mid) {
      colorBL(32,0); // orange
      colorFL(32,0); // orange
      colorBR(32,0); // orange
      colorFR(32,0); // orange
       wait(2); // 0.5 second

      FastLED.clear(); // faster than cleanFL(0);cleanFR(0);colorBL(0,0);colorBR(0,0);
       wait(2); // 0.5 second
      
      SwitchPosUpdate();
    }
    // Blinker Links Achtung!
    if(Sw1Up && !Sw4Up) {
      colorBL(32,0);
      colorFL(32,0);
      colorFR(32,0);
       wait(0.25);
      cleanFR(0);
       wait(0.25);
      colorFR(32,0);
       wait(0.25);
      cleanFR(0);
       wait(0.25);
      colorFR(32,0);
       wait(0.25);
      cleanFR(0);
       wait(0.25);
      colorFR(32,0);
       wait(0.25);
      cleanFR(0);
       wait(0.25);
      colorBL(0,0);
      cleanFL(0);
      colorFR(32,0);
       wait(0.25); // M1
      cleanFR(0);
       wait(0.25);
      for(byte j = 0; j < 2; j++) {
        colorFL(32,0);
        colorFR(32,0);
         wait(0.25);
        cleanFL(0);
        cleanFR(0);
         wait(0.25);
      }
      cleanFL(0);
      colorFR(32,0);
       wait(0.25);
      cleanFR(0);
       wait(0.25);
    }
    // Blinker Rechts Achtung!
    if(Sw4Up && !Sw1Up) {
      colorBR(32,0);
      colorFR(32,0);
      colorFL(32,0);
       wait(0.25);
      cleanFL(0);
       wait(0.25);
      colorFL(32,0);
       wait(0.25);
      cleanFL(0);
       wait(0.25);
      colorFL(32,0);
       wait(0.25);
      cleanFL(0);
       wait(0.25);
      colorFL(32,0);
       wait(0.25);
      cleanFL(0);
       wait(0.25);
      colorBR(0,0);
      cleanFR(0);
      colorFL(32,0);
       wait(0.25); // M1
      cleanFL(0);
       wait(0.25);
      for(byte j = 0; j < 2; j++) {
        colorFR(32,0);
        colorFL(32,0);
         wait(0.25);
        cleanFR(0);
        cleanFL(0);
         wait(0.25);
      }
      cleanFR(0);
      colorFL(32,0);
       wait(0.25);
      cleanFL(0);
       wait(0.25);      
    }
    // Blinker Beide Achtung!
    if(Sw1Up && Sw4Up) {
      colorFL(32,0);
      colorFR(32,0);
       wait(0.125);
      cleanFL(0);
      cleanFR(0);
      colorBL(32,0);
      colorBR(32,0);
       wait(0.25);
      colorBL(0,0);
      colorBR(0,0);
       wait(0.125);
    }
    
  }
  // Standlicht Hinten Rot & Vorne Weiß
  if(Sw3Up) {
    colorBL(0,0);
    colorBR(0,0);
    whiteFL(0);
    whiteFR(1);
    // Blinker Links Normal
    if(Sw1Mid && Sw4Down) {
      colorBL(32,0); // orange
      colorFL(32,0); // orange
       wait(2); // 0.5 second
      
      whiteFL(0);
      colorBL(0,0);
       wait(2); // 0.5 second
      
      SwitchPosUpdate();
    }

    // Blinker Rechts Normal
    if(Sw4Mid && Sw1Down) {
      colorBR(32,0); // orange
      colorFR(32,0); // orange
       wait(2); // 0.5 second
      
      whiteFR(0);
      colorBR(0,0);
       wait(2); // 0.5 second
      
      SwitchPosUpdate();
    }

    // Blinker Beide Normal
    if(Sw4Mid && Sw1Mid) {
      colorBL(32,0); // orange
      colorFL(32,0); // orange
      colorBR(32,0); // orange
      colorFR(32,0); // orange
       wait(2); // 0.5 second

      FastLED.clear(); // faster than whiteFL(0);whiteFR(0);colorBL(0,0);colorBR(0,0);
       wait(2); // 0.5 second
      
      SwitchPosUpdate();
    }
    // Blinker Links Achtung!
    if(Sw1Up && !Sw4Up) {
      colorBL(32,0);
      colorFL(32,0);
      colorFR(32,0);
       wait(0.25);
      whiteFR(0);
       wait(0.25);
      colorFR(32,0);
       wait(0.25);
      whiteFR(0);
       wait(0.25);
      colorFR(32,0);
       wait(0.25);
      whiteFR(0);
       wait(0.25);
      colorFR(32,0);
       wait(0.25);
      whiteFR(0);
       wait(0.25);
      colorBL(0,0);
      whiteFL(0);
      colorFR(32,0);
       wait(0.25); // M1
      whiteFR(0);
       wait(0.25);
      for(byte j = 0; j < 2; j++) {
        colorFL(32,0);
        colorFR(32,0);
         wait(0.25);
        whiteFL(0);
        whiteFR(0);
         wait(0.25);
      }
      whiteFL(0);
      colorFR(32,0);
       wait(0.25);
      whiteFR(0);
       wait(0.25);
    }
    // Blinker Rechts Achtung!
    if(Sw4Up && !Sw1Up) {
      colorBR(32,0);
      colorFR(32,0);
      colorFL(32,0);
       wait(0.25);
      whiteFL(0);
       wait(0.25);
      colorFL(32,0);
       wait(0.25);
      whiteFL(0);
       wait(0.25);
      colorFL(32,0);
       wait(0.25);
      whiteFL(0);
       wait(0.25);
      colorFL(32,0);
       wait(0.25);
      whiteFL(0);
       wait(0.25);
      colorBR(0,0);
      whiteFR(0);
      colorFL(32,0);
       wait(0.25); // M1
      whiteFL(0);
       wait(0.25);
      for(byte j = 0; j < 2; j++) {
        colorFR(32,0);
        colorFL(32,0);
         wait(0.25);
        whiteFR(0);
        whiteFL(0);
         wait(0.25);
      }
      whiteFR(0);
      colorFL(32,0);
       wait(0.25);
      whiteFL(0);
       wait(0.25);      
    }
    // Blinker Beide Achtung!
    if(Sw1Up && Sw4Up) {
      colorFL(32,0);
      colorFR(32,0);
       wait(0.125);
      whiteFL(0);
      whiteFR(0);
      colorBL(32,0);
      colorBR(32,0);
       wait(0.25);
      colorBL(0,0);
      colorBR(0,0);
       wait(0.125);
    }
    
  }
}

void Siren() {
  // Legal Police Lights (O-T)
  if(Sw3Down) {
    if(Sw1Down && Sw4Down) {
      FastLED.clear();
      FastLED.show();
    }
    // Cruise

    // Cruise 1
    if(Sw1Down && Sw4Mid) {
      colorBL(30,0);
      colorBR(110,0);
      colorFR(110,0);
      colorFL(30,1);
    }
    // Cruise 2
    if(Sw1Down && Sw4Up) {
      colspBL(30,1,7,0);colspBL(110,8,14,1); // BBBBRRRR <-
      colspBR(110,1,7,0);colspBR(30,8,14,0); // BBBBRRRR <-
      colspFR(110,1,6,0);colspFR(30,7,11,0); // RRRRBBBB <-
      colspFL(30,1,6,0);colspFL(110,7,11,1); // RRRRBBBB <-
    }
    // Emergency

    // Emergency 1
    if(Sw1Mid && Sw4Down) {

      colorBL(30,0);
      colorFL(110,0);
      colorFR(30,0);
      colorBR(110,0);
       wait(0.28);
      cleanall();
       wait(0.14); // <- rep1
      colorBL(30,0);
      colorFL(110,0);
      colorFR(30,0);
      colorBR(110,0);
       wait(0.28);
      cleanall();
       wait(0.14); // <- rep2

      colorBL(30,0);
      colorFL(110,0);
      colorFR(30,0);
      colorBR(110,0);
       wait(0.57);
      cleanall();
       wait(0.57);

      colorBR(30,0);
      colorFR(110,0);
      colorFL(30,0);
      colorBL(110,0);
       wait(0.28);
      cleanall();
       wait(0.14); // <- rep1
      colorBR(30,0);
      colorFR(110,0);
      colorFL(30,0);
      colorBL(110,0);
       wait(0.28);
      cleanall();
       wait(0.14); // <- rep2

      colorBR(30,0);
      colorFR(110,0);
      colorFL(30,0);
      colorBL(110,0);
       wait(0.57);
      cleanall();
       wait(0.57);
    }
    // Emergency 2
    if(Sw1Mid && Sw4Mid) {
      colorBL(30,0);
      colorFR(110,0);
       wait(0.3);
       wait(0.3);

      colorBL(30,0);
      cleanFL(0);
      colorFR(110,0);
      cleanBR(0);
       wait(0.3);
      cleanBL(0);
      colorFL(30,0);
      cleanFR(0);
      colorBR(110,0);
       wait(0.3);
       wait(0.3);
       wait(0.3);
      colorBL(30,0);
      cleanFL(0);
      colorFR(110,0);
      cleanBR(0);
       wait(0.3);
       wait(0.3);
       wait(0.3);
      cleanBL(0);
      colorFL(30,0);
      cleanFR(0);
      colorBR(110,0);

      colorBL(30,0);
      cleanFL(0);
      colorFR(110,0);
      cleanBR(0);
       wait(0.3);
      cleanBL(0);
      colorFL(30,0);
      cleanFR(0);
      colorBR(110,0);
       wait(0.3);
       wait(0.3);
       wait(0.3);
      colorBL(30,0);
      cleanFL(0);
      colorFR(110,0);
      cleanBR(0);
       wait(0.3);
       wait(0.3);
       wait(0.3);
      cleanBL(0);
      colorFL(30,0);
      cleanFR(0);
      colorBR(110,0);
       wait(0.3);
      cleanFL(0);
      cleanBR(0);
       wait(0.3);
      colorFL(30,0);
      colorBR(110,0);;
       wait(0.3);
      cleanall();
       wait(0.3);



      colorBR(30,0);
      colorFL(110,0);
       wait(0.3);
      cleanBR(0);
      cleanFL(0);
       wait(0.3);

      colorBR(30,0);
      colorFL(110,0);
       wait(0.3);
      cleanBR(0);
      colorFR(30,0);
      cleanFL(0);
      colorBL(110,0);
       wait(0.3);
       wait(0.3);
       wait(0.3);
      colorBR(30,0);
      cleanFR(0);
      colorFL(110,0);
      cleanBL(0);
       wait(0.3);
       wait(0.3);
       wait(0.3);
      cleanBR(0);
      colorFR(30,0);
      cleanFL(0);
      colorBL(110,0);

      colorBR(30,0);
      cleanFR(0);
      colorFL(110,0);
      cleanBL(0);
       wait(0.3);
      cleanBR(0);
      colorFR(30,0);
      cleanFL(0);
      colorBL(110,0);
       wait(0.3);
       wait(0.3);
       wait(0.3);
      colorBR(30,0);
      cleanFR(0);
      colorFL(110,0);
      cleanBL(0);
       wait(0.3);
       wait(0.3);
       wait(0.3);
      cleanBR(0);
      colorFR(30,0);
      cleanFL(0);
      colorBL(110,0);
       wait(0.3);
      cleanFR(0);
      cleanBL(0);
       wait(0.3);
      colorFR(30,0);
      colorBL(110,0);
       wait(0.3);
      cleanall();
       wait(0.3);
      
    }
    // Emergency 3
    if(Sw1Mid && Sw4Up) {
      colspBL(30,1,7,0);colspBL(110,8,14,1); // BBBBRRRR <-
      colspBR(110,1,7,0);colspBR(30,8,14,0); // BBBBRRRR <-
      colspFR(110,1,6,0);colspFR(30,7,11,0); // RRRRBBBB <-
      colspFL(30,1,6,0);colspFL(110,7,11,1); // RRRRBBBB <-
       wait(0.5);
      cleanall();
       wait(0.25);
      colspBL(30,1,7,0);colspBL(110,8,14,1); // BBBBRRRR <-
      colspBR(110,1,7,0);colspBR(30,8,14,0); // BBBBRRRR <-
      colspFR(110,1,6,0);colspFR(30,7,11,0); // RRRRBBBB <-
      colspFL(30,1,6,0);colspFL(110,7,11,1); // RRRRBBBB <-
       wait(0.5);
      cleanall();
       wait(0.25);

      colspBL(110,1,7,0);colspBL(30,8,14,1); // RRRRBBBB <-
      colspBR(30,1,7,0);colspBR(110,8,14,0); // RRRRBBBB <-
      colspFR(30,1,6,0);colspFR(110,7,11,0); // BBBBRRRR <-
      colspFL(110,1,6,0);colspFL(30,7,11,1); // BBBBRRRR <-
       wait(0.5);
      cleanall();
       wait(0.25);
      colspBL(110,1,7,0);colspBL(30,8,14,1); // RRRRBBBB <-
      colspBR(30,1,7,0);colspBR(110,8,14,0); // RRRRBBBB <-
      colspFR(30,1,6,0);colspFR(110,7,11,0); // BBBBRRRR <-
      colspFL(110,1,6,0);colspFL(30,7,11,1); // BBBBRRRR <-
       wait(0.5);
      cleanall();
       wait(0.25);

      colspBL(30,1,7,0);colspBL(110,8,14,1); // BBBBRRRR <-
      colspBR(110,1,7,0);colspBR(30,8,14,0); // BBBBRRRR <-
      colspFR(30,1,6,0);colspFR(110,7,11,0); // BBBBRRRR <-
      colspFL(110,1,6,0);colspFL(30,7,11,1); // BBBBRRRR <-
       wait(0.5);
      cleanall();
       wait(0.25);
      
      colspBL(110,1,7,0);colspBL(30,8,14,1); // RRRRBBBB <-
      colspBR(30,1,7,0);colspBR(110,8,14,0); // RRRRBBBB <-
      colspFR(110,1,6,0);colspFR(30,7,11,0); // RRRRBBBB <-
      colspFL(30,1,6,0);colspFL(110,7,11,1); // RRRRBBBB <-
       wait(0.5);
      cleanall();
       wait(0.25);

    }
    // Urgent Emergency 1
    if(Sw1Up && Sw4Down) {
      colorBL(30,0);
      colorFL(110,0);
      colorFR(30,0);
      colorBR(110,0);
       wait(0.28);
      cleanall();
       wait(0.14); // <- rep1
      colorBL(30,0);
      colorFL(110,0);
      colorFR(30,0);
      colorBR(110,0);
       wait(0.28);
      cleanall();
       wait(0.14); // <- rep2

      colorBL(30,0);
      colorFL(110,0);
      colorFR(30,0);
      colorBR(110,0);
       wait(0.57);
      cleanall();
       wait(0.14);

      for(byte z = 0; z < 3; z++) {
        whiteBL(0);
        whiteFL(0);
        whiteFR(0);
        whiteBR(0);
         wait(0.14);
        cleanall();
         wait(0.07);        
      }

      whiteBL(0);
      whiteFL(0);
      whiteFR(0);
      whiteBR(0);
       wait(0.14);
      cleanall();
       wait(0.57);


      colorBR(30,0);
      colorFR(110,0);
      colorFL(30,0);
      colorBL(110,0);
       wait(0.28);
      cleanall();
       wait(0.14); // <- rep1
      colorBR(30,0);
      colorFR(110,0);
      colorFL(30,0);
      colorBL(110,0);
       wait(0.28);
      cleanall();
       wait(0.14); // <- rep2

      colorBR(30,0);
      colorFR(110,0);
      colorFL(30,0);
      colorBL(110,0);
       wait(0.57);
      cleanall();
       wait(0.14);

      for(byte z = 0; z < 3; z++) {
        whiteBL(0);
        whiteFL(0);
        whiteFR(0);
        whiteBR(0);
         wait(0.14);
        cleanall();
         wait(0.07);        
      }

      whiteBL(0);
      whiteFL(0);
      whiteFR(0);
      whiteBR(0);
       wait(0.14);
      cleanall();
       wait(0.57);

    }
    // Urgent Emergency 2
    if(Sw1Up && Sw4Mid) {
      colorBL(30,0);
      whiteFL(0);
      colorFR(110,0);
      whiteBR(0);
       wait(0.3);
      cleanBL(0);
      cleanFR(0);
       wait(0.3);

      colorBL(30,0);
      cleanFL(0);
      colorFR(110,0);
      cleanBR(0);
       wait(0.3);
      cleanBL(0);
      colorFL(30,0);
      cleanFR(0);
      colorBR(110,0);
       wait(0.3);
      whiteBL(0);
      whiteFR(0);
       wait(0.3);
      cleanBL(0);
      cleanFR(0);
       wait(0.3);
      colorBL(30,0);
      cleanFL(0);
      colorFR(110,0);
      cleanBR(0);
       wait(0.3);
      whiteFL(0);
      whiteBR(0);
       wait(0.3);
      cleanFL(0);
      cleanBR(0);
       wait(0.3);
      cleanBL(0);
      colorFL(30,0);
      cleanFR(0);
      colorBR(110,0);

      colorBL(30,0);
      cleanFL(0);
      colorFR(110,0);
      cleanBR(0);
       wait(0.3);
      cleanBL(0);
      colorFL(30,0);
      cleanFR(0);
      colorBR(110,0);
       wait(0.3);
      whiteBL(0);
      whiteFR(0);
       wait(0.3);
      cleanBL(0);
      cleanFR(0);
       wait(0.3);
      colorBL(30,0);
      cleanFL(0);
      colorFR(110,0);
      cleanBR(0);
       wait(0.3);
      whiteFL(0);
      whiteBR(0);
       wait(0.3);
      cleanFL(0);
      cleanBR(0);
       wait(0.3);
      cleanBL(0);
      colorFL(30,0);
      cleanFR(0);
      colorBR(110,0);
       wait(0.3);
      whiteBL(0);
      cleanFL(0);
      whiteFR(0);
      cleanBR(0);
       wait(0.3);
      colorFL(30,0);
      colorBR(110,0);
       wait(0.3);
      cleanall();
       wait(0.3);



      colorBR(30,0);
      whiteFR(0);
      colorFL(110,0);
      whiteBL(0);
       wait(0.3);
      cleanBR(0);
      cleanFL(0);
       wait(0.3);

      colorBR(30,0);
      cleanFR(0);
      colorFL(110,0);
      cleanBL(0);
       wait(0.3);
      cleanBR(0);
      colorFR(30,0);
      cleanFL(0);
      colorBL(110,0);
       wait(0.3);
      whiteBR(0);
      whiteFL(0);
       wait(0.3);
      cleanBR(0);
      cleanFL(0);
       wait(0.3);
      colorBR(30,0);
      cleanFR(0);
      colorFL(110,0);
      cleanBL(0);
       wait(0.3);
      whiteFR(0);
      whiteBL(0);
       wait(0.3);
      cleanFR(0);
      cleanBL(0);
       wait(0.3);
      cleanBR(0);
      colorFR(30,0);
      cleanFL(0);
      colorBL(110,0);
   //////////////////////
      colorBR(30,0);
      cleanFR(0);
      colorFL(110,0);
      cleanBL(0);
       wait(0.3);
      cleanBR(0);
      colorFR(30,0);
      cleanFL(0);
      colorBL(110,0);
       wait(0.3);
      whiteBR(0);
      whiteFL(0);
       wait(0.3);
      cleanBR(0);
      cleanFL(0);
       wait(0.3);
      colorBR(30,0);
      cleanFR(0);
      colorFL(110,0);
      cleanBL(0);
       wait(0.3);
      whiteFR(0);
      whiteBL(0);
       wait(0.3);
      cleanFR(0);
      cleanBL(0);
       wait(0.3);
      cleanBR(0);
      colorFR(30,0);
      cleanFL(0);
      colorBL(110,0);
       wait(0.3);
      whiteBR(0);
      cleanFR(0);
      whiteFL(0);
      cleanBL(0);
       wait(0.3);
      colorFR(30,0);
      colorBL(110,0);
       wait(0.3);
      cleanall();
       wait(0.3);
    
    }
    // Urgent Emergency 3
    if(Sw1Up && Sw4Up) {
      colspBL(30,1,7,0);colspBL(110,8,14,1); // BBBBRRRR <-
      colspBR(110,1,7,0);colspBR(30,8,14,0); // BBBBRRRR <-
      colspFR(110,1,6,0);colspFR(30,7,11,0); // RRRRBBBB <-
      colspFL(30,1,6,0);colspFL(110,7,11,1); // RRRRBBBB <-
       wait(0.5);
      cleanall();
       wait(0.25);
      colspBL(30,1,7,0);colspBL(110,8,14,1); // BBBBRRRR <-
      colspBR(110,1,7,0);colspBR(30,8,14,0); // BBBBRRRR <-
      colspFR(110,1,6,0);colspFR(30,7,11,0); // RRRRBBBB <-
      colspFL(30,1,6,0);colspFL(110,7,11,1); // RRRRBBBB <-
       wait(0.5);
      cleanall();
       wait(0.25);

      colspBL(110,1,7,0);colspBL(30,8,14,1); // RRRRBBBB <-
      colspBR(30,1,7,0);colspBR(110,8,14,0); // RRRRBBBB <-
      colspFR(30,1,6,0);colspFR(110,7,11,0); // BBBBRRRR <-
      colspFL(110,1,6,0);colspFL(30,7,11,1); // BBBBRRRR <-
       wait(0.5);
      cleanall();
       wait(0.25);
      colspBL(110,1,7,0);colspBL(30,8,14,1); // RRRRBBBB <-
      colspBR(30,1,7,0);colspBR(110,8,14,0); // RRRRBBBB <-
      colspFR(30,1,6,0);colspFR(110,7,11,0); // BBBBRRRR <-
      colspFL(110,1,6,0);colspFL(30,7,11,1); // BBBBRRRR <-
       wait(0.5);
      cleanall();
       wait(0.25);

      colspBL(30,1,7,0);colspBL(110,8,14,1); // BBBBRRRR <-
      colspBR(110,1,7,0);colspBR(30,8,14,0); // BBBBRRRR <-
      colspFR(30,1,6,0);colspFR(110,7,11,0); // BBBBRRRR <-
      colspFL(110,1,6,0);colspFL(30,7,11,1); // BBBBRRRR <-
       wait(0.5);
      cleanall();
       wait(0.25);
      
      colspBL(110,1,7,0);colspBL(30,8,14,1); // RRRRBBBB <-
      colspBR(30,1,7,0);colspBR(110,8,14,0); // RRRRBBBB <-
      colspFR(110,1,6,0);colspFR(30,7,11,0); // RRRRBBBB <-
      colspFL(30,1,6,0);colspFL(110,7,11,1); // RRRRBBBB <-
       wait(0.5);

      for(byte x = 0; x < 3; x++) {
        colspBL(110,1,7,0);whispBL(8,14,1); // WWWWBBBB <-
        whispBR(1,7,0);colspBR(110,8,14,0); // WWWWBBBB <-
        colspFR(110,1,6,0);whispFR(7,11,0); // WWWWBBBB <-
        whispFL(1,6,0);colspFL(110,7,11,1); // WWWWBBBB <-
         wait(0.25);

        whispBL(1,7,0);colspBL(30,8,14,1); // RRRRWWWW <-
        colspBR(30,1,7,0);whispBR(8,14,0); // RRRRWWWW <-
        whispFR(1,6,0);colspFR(30,7,11,0); // RRRRWWWW <-
        colspFL(30,1,6,0);whispFL(7,11,1); // RRRRWWWW <-
         wait(0.25);
      }

      whiteBL(0);
      whiteBR(0);
      whiteFR(0);
      whiteFL(0);
       wait(0.25);
      cleanall();
       wait(0.125);

      whiteBL(0);
      whiteBR(0);
      whiteFR(0);
      whiteFL(0);
       wait(0.25);
      cleanall();
       wait(0.125);

      whiteBL(0);
      whiteBR(0);
      whiteFR(0);
      whiteFL(0);
       wait(0.25);
      cleanall();
       wait(0.125);
    }
  }
  // American Police Lights (R-B/R-W)
  if(Sw3Mid) {
    if(Sw1Down && Sw4Down) {
      FastLED.clear();
      FastLED.show();
    }
    // Cruse

    // Cruise 1
    if(Sw1Down && Sw4Mid) {
      colorBL(0,0);
      colorBR(160,0);
      colorFR(160,0);
      colorFL(0,1);
    }
    // Cruise 2
    if(Sw1Down && Sw4Up) {
      colspBL(0,1,7,0);colspBL(160,8,14,1); // BBBBRRRR <-
      colspBR(160,1,7,0);colspBR(0,8,14,0); // BBBBRRRR <-
      colspFR(160,1,6,0);colspFR(0,7,11,0); // RRRRBBBB <-
      colspFL(0,1,6,0);colspFL(160,7,11,1); // RRRRBBBB <-
    }
    // Emergency

    // Emergency 1
    if(Sw1Mid && Sw4Down) {

      colorBL(0,0);
      colorFL(160,0);
      colorFR(0,0);
      colorBR(160,0);
       wait(0.28);
      cleanall();
       wait(0.14); // <- rep1
      colorBL(0,0);
      colorFL(160,0);
      colorFR(0,0);
      colorBR(160,0);
       wait(0.28);
      cleanall();
       wait(0.14); // <- rep2

      colorBL(0,0);
      colorFL(160,0);
      colorFR(0,0);
      colorBR(160,0);
       wait(0.57);
      cleanall();
       wait(0.57);

      colorBR(0,0);
      colorFR(160,0);
      colorFL(0,0);
      colorBL(160,0);
       wait(0.28);
      cleanall();
       wait(0.14); // <- rep1
      colorBR(0,0);
      colorFR(160,0);
      colorFL(0,0);
      colorBL(160,0);
       wait(0.28);
      cleanall();
       wait(0.14); // <- rep2

      colorBR(0,0);
      colorFR(160,0);
      colorFL(0,0);
      colorBL(160,0);
       wait(0.57);
      cleanall();
       wait(0.57);
    }
    // Emergency 2
    if(Sw1Mid && Sw4Mid) {
      colorBL(0,0);
      colorFR(160,0);
       wait(0.3);
       wait(0.3);

      colorBL(0,0);
      cleanFL(0);
      colorFR(160,0);
      cleanBR(0);
       wait(0.3);
      cleanBL(0);
      colorFL(0,0);
      cleanFR(0);
      colorBR(160,0);
       wait(0.3);
       wait(0.3);
       wait(0.3);
      colorBL(0,0);
      cleanFL(0);
      colorFR(160,0);
      cleanBR(0);
       wait(0.3);
       wait(0.3);
       wait(0.3);
      cleanBL(0);
      colorFL(0,0);
      cleanFR(0);
      colorBR(160,0);

      colorBL(0,0);
      cleanFL(0);
      colorFR(160,0);
      cleanBR(0);
       wait(0.3);
      cleanBL(0);
      colorFL(0,0);
      cleanFR(0);
      colorBR(160,0);
       wait(0.3);
       wait(0.3);
       wait(0.3);
      colorBL(0,0);
      cleanFL(0);
      colorFR(160,0);
      cleanBR(0);
       wait(0.3);
       wait(0.3);
       wait(0.3);
      cleanBL(0);
      colorFL(0,0);
      cleanFR(0);
      colorBR(160,0);
       wait(0.3);
      cleanFL(0);
      cleanBR(0);
       wait(0.3);
      colorFL(0,0);
      colorBR(160,0);
       wait(0.3);
      cleanall();
       wait(0.3);



      colorBR(0,0);
      colorFL(160,0);
       wait(0.3);
      cleanBR(0);
      cleanFL(0);
       wait(0.3);

      colorBR(0,0);
      colorFL(160,0);
       wait(0.3);
      cleanBR(0);
      colorFR(0,0);
      cleanFL(0);
      colorBL(160,0);
       wait(0.3);
       wait(0.3);
       wait(0.3);
      colorBR(0,0);
      cleanFR(0);
      colorFL(160,0);
      cleanBL(0);
       wait(0.3);
       wait(0.3);
       wait(0.3);
      cleanBR(0);
      colorFR(0,0);
      cleanFL(0);
      colorBL(160,0);

      colorBR(0,0);
      cleanFR(0);
      colorFL(160,0);
      cleanBL(0);
       wait(0.3);
      cleanBR(0);
      colorFR(0,0);
      cleanFL(0);
      colorBL(160,0);
       wait(0.3);
       wait(0.3);
       wait(0.3);
      colorBR(0,0);
      cleanFR(0);
      colorFL(160,0);
      cleanBL(0);
       wait(0.3);
       wait(0.3);
       wait(0.3);
      cleanBR(0);
      colorFR(0,0);
      cleanFL(0);
      colorBL(160,0);
       wait(0.3);
      cleanFR(0);
      cleanBL(0);
       wait(0.3);
      colorFR(0,0);
      colorBL(160,0);
       wait(0.3);
      cleanall();
       wait(0.3);
      
    }
    // Emergency 3
    if(Sw1Mid && Sw4Up) {
      colspBL(0,1,7,0);colspBL(160,8,14,1); // BBBBRRRR <-
      colspBR(160,1,7,0);colspBR(0,8,14,0); // BBBBRRRR <-
      colspFR(160,1,6,0);colspFR(0,7,11,0); // RRRRBBBB <-
      colspFL(0,1,6,0);colspFL(160,7,11,1); // RRRRBBBB <-
       wait(0.5);
      cleanall();
       wait(0.25);
      colspBL(0,1,7,0);colspBL(160,8,14,1); // BBBBRRRR <-
      colspBR(160,1,7,0);colspBR(0,8,14,0); // BBBBRRRR <-
      colspFR(160,1,6,0);colspFR(0,7,11,0); // RRRRBBBB <-
      colspFL(0,1,6,0);colspFL(160,7,11,1); // RRRRBBBB <-
       wait(0.5);
      cleanall();
       wait(0.25);

      colspBL(160,1,7,0);colspBL(0,8,14,1); // RRRRBBBB <-
      colspBR(0,1,7,0);colspBR(160,8,14,0); // RRRRBBBB <-
      colspFR(0,1,6,0);colspFR(160,7,11,0); // BBBBRRRR <-
      colspFL(160,1,6,0);colspFL(0,7,11,1); // BBBBRRRR <-
       wait(0.5);
      cleanall();
       wait(0.25);
      colspBL(160,1,7,0);colspBL(0,8,14,1); // RRRRBBBB <-
      colspBR(0,1,7,0);colspBR(160,8,14,0); // RRRRBBBB <-
      colspFR(0,1,6,0);colspFR(160,7,11,0); // BBBBRRRR <-
      colspFL(160,1,6,0);colspFL(0,7,11,1); // BBBBRRRR <-
       wait(0.5);
      cleanall();
       wait(0.25);

      colspBL(0,1,7,0);colspBL(160,8,14,1); // BBBBRRRR <-
      colspBR(160,1,7,0);colspBR(0,8,14,0); // BBBBRRRR <-
      colspFR(0,1,6,0);colspFR(160,7,11,0); // BBBBRRRR <-
      colspFL(160,1,6,0);colspFL(0,7,11,1); // BBBBRRRR <-
       wait(0.5);
      cleanall();
       wait(0.25);
      
      colspBL(160,1,7,0);colspBL(0,8,14,1); // RRRRBBBB <-
      colspBR(0,1,7,0);colspBR(160,8,14,0); // RRRRBBBB <-
      colspFR(160,1,6,0);colspFR(0,7,11,0); // RRRRBBBB <-
      colspFL(0,1,6,0);colspFL(160,7,11,1); // RRRRBBBB <-
       wait(0.5);
      cleanall();
       wait(0.25);

    }
    // Urgent Emergency 1
    if(Sw1Up && Sw4Down) {
      colorBL(0,0);
      colorFL(160,0);
      colorFR(0,0);
      colorBR(160,0);
       wait(0.28);
      cleanall();
       wait(0.14); // <- rep1
      colorBL(0,0);
      colorFL(160,0);
      colorFR(0,0);
      colorBR(160,0);
       wait(0.28);
      cleanall();
       wait(0.14); // <- rep2

      colorBL(0,0);
      colorFL(160,0);
      colorFR(0,0);
      colorBR(160,0);
       wait(0.57);
      cleanall();
       wait(0.14);

      for(byte z = 0; z < 3; z++) {
        whiteBL(0);
        whiteFL(0);
        whiteFR(0);
        whiteBR(0);
         wait(0.14);
        cleanall();
         wait(0.07);        
      }

      whiteBL(0);
      whiteFL(0);
      whiteFR(0);
      whiteBR(0);
       wait(0.14);
      cleanall();
       wait(0.57);


      colorBR(0,0);
      colorFR(160,0);
      colorFL(0,0);
      colorBL(160,0);
       wait(0.28);
      cleanall();
       wait(0.14); // <- rep1
      colorBR(0,0);
      colorFR(160,0);
      colorFL(0,0);
      colorBL(160,0);
       wait(0.28);
      cleanall();
       wait(0.14); // <- rep2

      colorBR(0,0);
      colorFR(160,0);
      colorFL(0,0);
      colorBL(160,0);
       wait(0.57);
      cleanall();
       wait(0.14);

      for(byte z = 0; z < 3; z++) {
        whiteBL(0);
        whiteFL(0);
        whiteFR(0);
        whiteBR(0);
         wait(0.14);
        cleanall();
         wait(0.07);        
      }

      whiteBL(0);
      whiteFL(0);
      whiteFR(0);
      whiteBR(0);
       wait(0.14);
      cleanall();
       wait(0.57);

    }
    // Urgent Emergency 2
    if(Sw1Up && Sw4Mid) {
      colorBL(0,0);
      whiteFL(0);
      colorFR(160,0);
      whiteBR(0);
       wait(0.3);
      cleanBL(0);
      cleanFR(0);
       wait(0.3);

      colorBL(0,0);
      cleanFL(0);
      colorFR(160,0);
      cleanBR(0);
       wait(0.3);
      cleanBL(0);
      colorFL(0,0);
      cleanFR(0);
      colorBR(160,0);
       wait(0.3);
      whiteBL(0);
      whiteFR(0);
       wait(0.3);
      cleanBL(0);
      cleanFR(0);
       wait(0.3);
      colorBL(0,0);
      cleanFL(0);
      colorFR(160,0);
      cleanBR(0);
       wait(0.3);
      whiteFL(0);
      whiteBR(0);
       wait(0.3);
      cleanFL(0);
      cleanBR(0);
       wait(0.3);
      cleanBL(0);
      colorFL(0,0);
      cleanFR(0);
      colorBR(160,0);

      colorBL(0,0);
      cleanFL(0);
      colorFR(160,0);
      cleanBR(0);
       wait(0.3);
      cleanBL(0);
      colorFL(0,0);
      cleanFR(0);
      colorBR(160,0);
       wait(0.3);
      whiteBL(0);
      whiteFR(0);
       wait(0.3);
      cleanBL(0);
      cleanFR(0);
       wait(0.3);
      colorBL(0,0);
      cleanFL(0);
      colorFR(160,0);
      cleanBR(0);
       wait(0.3);
      whiteFL(0);
      whiteBR(0);
       wait(0.3);
      cleanFL(0);
      cleanBR(0);
       wait(0.3);
      cleanBL(0);
      colorFL(0,0);
      cleanFR(0);
      colorBR(160,0);
       wait(0.3);
      whiteBL(0);
      cleanFL(0);
      whiteFR(0);
      cleanBR(0);
       wait(0.3);
      colorFL(0,0);
      colorBR(160,0);
       wait(0.3);
      cleanall();
       wait(0.3);



      colorBR(0,0);
      whiteFR(0);
      colorFL(160,0);
      whiteBL(0);
       wait(0.3);
      cleanBR(0);
      cleanFL(0);
       wait(0.3);

      colorBR(0,0);
      cleanFR(0);
      colorFL(160,0);
      cleanBL(0);
       wait(0.3);
      cleanBR(0);
      colorFR(0,0);
      cleanFL(0);
      colorBL(160,0);
       wait(0.3);
      whiteBR(0);
      whiteFL(0);
       wait(0.3);
      cleanBR(0);
      cleanFL(0);
       wait(0.3);
      colorBR(0,0);
      cleanFR(0);
      colorFL(160,0);
      cleanBL(0);
       wait(0.3);
      whiteFR(0);
      whiteBL(0);
       wait(0.3);
      cleanFR(0);
      cleanBL(0);
       wait(0.3);
      cleanBR(0);
      colorFR(0,0);
      cleanFL(0);
      colorBL(160,0);

      colorBR(0,0);
      cleanFR(0);
      colorFL(160,0);
      cleanBL(0);
       wait(0.3);
      cleanBR(0);
      colorFR(0,0);
      cleanFL(0);
      colorBL(160,0);
       wait(0.3);
      whiteBR(0);
      whiteFL(0);
       wait(0.3);
      cleanBR(0);
      cleanFL(0);
       wait(0.3);
      colorBR(0,0);
      cleanFR(0);
      colorFL(160,0);
      cleanBL(0);
       wait(0.3);
      whiteFR(0);
      whiteBL(0);
       wait(0.3);
      cleanFR(0);
      cleanBL(0);
       wait(0.3);
      cleanBR(0);
      colorFR(0,0);
      cleanFL(0);
      colorBL(160,0);
       wait(0.3);
      whiteBR(0);
      cleanFR(0);
      whiteFL(0);
      cleanBL(0);
       wait(0.3);
      colorFR(0,0);
      colorBL(160,0);
       wait(0.3);
      cleanall();
       wait(0.3);
    
    }
    // Urgent Emergency 3
    if(Sw1Up && Sw4Up) {
      colspBL(0,1,7,0);colspBL(160,8,14,1); // BBBBRRRR <-
      colspBR(160,1,7,0);colspBR(0,8,14,0); // BBBBRRRR <-
      colspFR(160,1,6,0);colspFR(0,7,11,0); // RRRRBBBB <-
      colspFL(0,1,6,0);colspFL(160,7,11,1); // RRRRBBBB <-
       wait(0.5);
      cleanall();
       wait(0.25);
      colspBL(0,1,7,0);colspBL(160,8,14,1); // BBBBRRRR <-
      colspBR(160,1,7,0);colspBR(0,8,14,0); // BBBBRRRR <-
      colspFR(160,1,6,0);colspFR(0,7,11,0); // RRRRBBBB <-
      colspFL(0,1,6,0);colspFL(160,7,11,1); // RRRRBBBB <-
       wait(0.5);
      cleanall();
       wait(0.25);

      colspBL(160,1,7,0);colspBL(0,8,14,1); // RRRRBBBB <-
      colspBR(0,1,7,0);colspBR(160,8,14,0); // RRRRBBBB <-
      colspFR(0,1,6,0);colspFR(160,7,11,0); // BBBBRRRR <-
      colspFL(160,1,6,0);colspFL(0,7,11,1); // BBBBRRRR <-
       wait(0.5);
      cleanall();
       wait(0.25);
      colspBL(160,1,7,0);colspBL(0,8,14,1); // RRRRBBBB <-
      colspBR(0,1,7,0);colspBR(160,8,14,0); // RRRRBBBB <-
      colspFR(0,1,6,0);colspFR(160,7,11,0); // BBBBRRRR <-
      colspFL(160,1,6,0);colspFL(0,7,11,1); // BBBBRRRR <-
       wait(0.5);
      cleanall();
       wait(0.25);

      colspBL(0,1,7,0);colspBL(160,8,14,1); // BBBBRRRR <-
      colspBR(160,1,7,0);colspBR(0,8,14,0); // BBBBRRRR <-
      colspFR(0,1,6,0);colspFR(160,7,11,0); // BBBBRRRR <-
      colspFL(160,1,6,0);colspFL(0,7,11,1); // BBBBRRRR <-
       wait(0.5);
      cleanall();
       wait(0.25);
      
      colspBL(160,1,7,0);colspBL(0,8,14,1); // RRRRBBBB <-
      colspBR(0,1,7,0);colspBR(160,8,14,0); // RRRRBBBB <-
      colspFR(160,1,6,0);colspFR(0,7,11,0); // RRRRBBBB <-
      colspFL(0,1,6,0);colspFL(160,7,11,1); // RRRRBBBB <-
       wait(0.5);

      for(byte x = 0; x < 3; x++) {
        colspBL(160,1,7,0);whispBL(8,14,1); // WWWWBBBB <-
        whispBR(1,7,0);colspBR(160,8,14,0); // WWWWBBBB <-
        colspFR(160,1,6,0);whispFR(7,11,0); // WWWWBBBB <-
        whispFL(1,6,0);colspFL(160,7,11,1); // WWWWBBBB <-
         wait(0.25);

        whispBL(1,7,0);colspBL(0,8,14,1); // RRRRWWWW <-
        colspBR(0,1,7,0);whispBR(8,14,0); // RRRRWWWW <-
        whispFR(1,6,0);colspFR(0,7,11,0); // RRRRWWWW <-
        colspFL(0,1,6,0);whispFL(7,11,1); // RRRRWWWW <-
         wait(0.25);
      }

      whiteBL(0);
      whiteBR(0);
      whiteFR(0);
      whiteFL(0);
       wait(0.25);
      cleanall();
       wait(0.125);

      whiteBL(0);
      whiteBR(0);
      whiteFR(0);
      whiteFL(0);
       wait(0.25);
      cleanall();
       wait(0.125);

      whiteBL(0);
      whiteBR(0);
      whiteFR(0);
      whiteFL(0);
       wait(0.25);
      cleanall();
       wait(0.125);
    }
  }
  // German Police Lights (B-B)
  if(Sw3Up) {
    if(Sw1Down && Sw4Down) {
      FastLED.clear();
      FastLED.show();
    }
    // Polizei Standlicht

    // Polizei Standlicht 1
    if(Sw1Down && Sw4Mid) {
      // Polizei Standlicht 1
      for(byte w = 0; w <= 254; w++) {
        wave = quadwave8(w);
        rgbFR(0,0,wave,0);
        rgbBL(0,0,wave,0);
        rgbFL(0,0,wave,0);
        rgbBR(0,0,wave,0);
        wait(0.01);
      }
      
      
    }
    // Polizei Standlicht 2
    if(Sw1Down && Sw4Up) {
      // Polizei Standlicht 2
      colorBL(160,0);
      colorFL(160,0);
      colorFR(160,0);
      colorBR(160,1);
    }
    // Polizei Einsatzfahrt
    
    // Polizei Einsatzfahrt 1
    if(Sw1Mid && Sw4Down) {
      colorFL(160,0);
       wait(0.25);
      colorFR(160,0);
       wait(0.5);
      cleanFL(0);
       wait(0.25);
      cleanFR(0);
      colorBL(160,0);
      colorBR(160,0);
       wait(0.25);
      colorFL(160,0);
       wait(0.25);
      colorFR(160,0);
      cleanFL(0);
      cleanBL(0);
      cleanBR(0);
       wait(0.25);
      cleanFR(0);
      colorBL(160,0);
      colorBR(160,0);
       wait(0.25);
       wait(0.25);
      cleanBL(0);
      cleanBR(1);
    }
    // Polizei Einsatzfahrt 2
    if(Sw1Mid && Sw4Mid) {
      for(byte j = 0; j < 2; j++) {
        colorBL(160,0);
        colorFR(160,0);
         wait(0.28);
        cleanBL(0);
        cleanFR(0);
         wait(0.14);
      }
      colorBL(160,0);
      colorFR(160,0);
      wait(0.57);
      cleanBL(0);
      cleanFR(0);
      for(byte j = 0; j < 2; j++) {
        colorBR(160,0);
        colorFL(160,0);
         wait(0.28);
        cleanBR(0);
        cleanFL(0);
         wait(0.14);        
      }
      colorBR(160,0);
      colorFL(160,0);
       wait(0.57);
      cleanBR(0);
      cleanFL(1);
    }
    // Polizei Einsatzfahrt 3 (random 1&2)
    if(Sw1Mid && Sw4Up) {
      Einsatzfahrt1(random8(1,4));
      Einsatzfahrt2(random8(1,4));
    }
    // Polizei Achtung! Einsatz!

    // Polizei Achtung! Einsatz! 1
    if(Sw1Up && Sw4Down) {
      // Polizei Achtung! Einsatz! 1
      colorFL(160,0);
       wait(0.25);
      colorFR(160,0);
        whiteBL(0);
        whiteBR(0);
       wait(0.125);
        cleanBL(0);
        cleanBR(0);
       wait(0.0625);
        whiteBL(0);
        whiteBR(0);
       wait(0.125);
        cleanBL(0);
        cleanBR(0);
       wait(0.0625);
        whiteBL(0);
        whiteBR(0);
       wait(0.125);
        cleanBL(0);
        cleanBR(0);
       wait(0.0625);
        whiteBL(0);
        whiteBR(0);
       wait(0.125);
        cleanBL(0);
        cleanBR(0);
       wait(0.0625);
        whiteBL(0);
        whiteBR(0);
       wait(0.125);
        cleanBL(0);
        cleanBR(0);
       wait(0.0625);
        whiteBL(0);
        whiteBR(0);
       wait(0.125);
        cleanBL(0);
        cleanBR(0);
       wait(0.1875);
      cleanFL(0);
       wait(0.25);
      cleanFR(0);
        colorBL(160,0);
        colorBR(160,0);
       wait(0.25);
      colorFL(160,0);
       wait(0.25);
      colorFR(160,0);
      cleanFL(0);
        cleanBL(0);
        cleanBR(0);
       wait(0.25);
      cleanFR(0);
        colorBL(160,0);
        colorBR(160,0);
      whiteFL(0);
       wait(0.125);
      cleanFL(0);
       wait(0.0625);
      whiteFL(0);
       wait(0.0625);
      whiteFR(0);
       wait(0.0625);
      cleanFL(0);
       wait(0.0625);
      cleanFR(0);
      whiteFL(0);
       wait(0.0625);
      whiteFR(0);
       wait(0.0625);
      cleanFL(0);
        cleanBL(0);
        cleanBR(0);
       wait(0.0625);
      cleanFR(0);
       wait(0.0625);
      whiteFR(0);
       wait(0.0625);
       wait(0.0625);
      cleanFR(0);
    }
    // Polizei Achtung! Einsatz! 2
    if(Sw1Up && Sw4Mid) {
      // Polizei Achtung! Einsatz! 2

        colorBL(160,0);
        colorFR(160,0);
         wait(0.14);
          whiteBR(0);
          whiteFL(0);
         wait(0.14);
        cleanBL(0);
        cleanFR(0);
         wait(0.14);
        colorBL(160,0);
        colorFR(160,0);
         wait(0.14);
          cleanBR(0);
          cleanFL(0);
         wait(0.14);
        cleanBL(0);
        cleanFR(0);
          whiteBR(0);
          whiteFL(0);
         wait(0.14);
      
      colorBL(160,0);
      colorFR(160,0);
       wait(0.42);
        cleanBR(0);
        cleanFL(0);
       wait(0.14);
      cleanBL(0);
      cleanFR(0);

        colorBR(160,0);
        colorFL(160,0);
         wait(0.14);
          whiteBL(0);
          whiteFR(0);
         wait(0.14);
        cleanBR(0);
        cleanFL(0);
         wait(0.14);        
        colorBR(160,0);
        colorFL(160,0);
         wait(0.14);
          cleanBL(0);
          cleanFR(0);
         wait(0.14);
        cleanBR(0);
        cleanFL(0);
          whiteBL(0);
          whiteFR(0);        
         wait(0.14);        


      colorBR(160,0);
      colorFL(160,0);
       wait(0.42);
        cleanBL(0);
        cleanFR(0);
       wait(0.14);
      cleanBR(0);
      cleanFL(1);
    }
    // Polizei Achtung! Einsatz! 3
    if(Sw1Up && Sw4Up) {
      // Polizei Achtung! Einsatz! 3
      EinsatzfahrtAchtung1(random8(1,4));
      EinsatzfahrtAchtung2(random8(1,4));
    }
  }
}

void Sonst() {
  // Kein Standlicht
  if(Sw3Down) {
    cleanall();
  }
  // Standlicht Hinten Rot
  if(Sw3Mid && Sw1Down && Sw4Down) {
    colorBL(0,0);
    colorBR(0,0);
    cleanFL(0);
    cleanFR(1);
  }
  // Standlicht Hinten Rot & Vorne Weiß
  if(Sw3Up && Sw1Down && Sw4Down) {
    colorBL(0,0);
    colorBR(0,0);
    whiteFL(0);
    whiteFR(1);
  }
  // Volle Scheinwerfer
  if(Sw1Up && Sw4Up && Sw3Up) {
    whiteBL(0);
    whiteFL(0);
    whiteFR(0);
    whiteBR(1);
  }
  if(Sw1Mid && Sw4Down) {
    for(int h = 0; h <= 255; h++) {
      colorBL(h,0);
      colorFL(h,0);
      colorFR(h,0);
      colorBR(h,1);
      wait(0.02);
    }
  }
}
// <-
void wait(float factor) {
  FastLED.delay(delaytime*factor);
}

void cleanBL(bool shouw) {
  for(byte i = 0; i < NUM_LEDS_B; i++) {
    ledsBL[i].setRGB(0,0,0);
  }
  if(shouw) {
    FastLED.show();
  }
}

void cleanFL(bool shouw) {
  for(byte i = 0; i < NUM_LEDS_F; i++) {
    ledsFL[i].setRGB(0,0,0);
  }
  if(shouw) {
    FastLED.show();
  }
}

void cleanFR(bool shouw) {
  for(byte i = 0; i < NUM_LEDS_F; i++) {
    ledsFR[i].setRGB(0,0,0);
  }
  if(shouw) {
    FastLED.show();
  }
}

void cleanBR(bool shouw) {
  for(byte i = 0; i < NUM_LEDS_B; i++) {
    ledsBR[i].setRGB(0,0,0);
  }
  if(shouw) {
    FastLED.show();
  }
}

void cleanall() {
  FastLED.clear();
  FastLED.show();
}

void colorBL(byte hue, bool shouw) {
  for(byte i = 0; i < NUM_LEDS_B; i++) {
    ledsBL[i].setHue(hue);
  }
  if(shouw) {
    FastLED.show();
  }
}

void colorFL(byte hue, bool shouw) {
  for(byte i = 0; i < NUM_LEDS_F; i++) {
    ledsFL[i].setHue(hue);
  }
  if(shouw) {
    FastLED.show();
  }
}

void colorFR(byte hue, bool shouw) {
  for(byte i = 0; i < NUM_LEDS_F; i++) {
    ledsFR[i].setHue(hue);
  }
  if(shouw) {
    FastLED.show();
  }
}

void colorBR(byte hue, bool shouw) {
  for(byte i = 0; i < NUM_LEDS_B; i++) {
    ledsBR[i].setHue(hue);
  }
  if(shouw) {
    FastLED.show();
  }
}

void colspBL(byte hue, byte startled, byte endled, bool shouw) {
  for(byte i = startled-1; i <= endled-1; i++) {
    ledsBL[i].setHue(hue);
  }
  if(shouw) {
    FastLED.show();
  }
}

void colspFL(byte hue, byte startled, byte endled, bool shouw) {
  for(byte i = startled-1; i <= endled-1; i++) {
    ledsFL[i].setHue(hue);
  }
  if(shouw) {
    FastLED.show();
  }
}

void colspFR(byte hue, byte startled, byte endled, bool shouw) {
  for(byte i = startled-1; i <= endled-1; i++) {
    ledsFR[i].setHue(hue);
  }
  if(shouw) {
    FastLED.show();
  }
}

void colspBR(byte hue, byte startled, byte endled, bool shouw) {
  for(byte i = startled-1; i <= endled-1; i++) {
    ledsBR[i].setHue(hue);
  }
  if(shouw) {
    FastLED.show();
  }
}

void whiteBL(bool shouw) {
  for(byte i = 0; i < NUM_LEDS_B; i++) {
    ledsBL[i].setRGB(255,255,255);
  }
  if(shouw) {
    FastLED.show();
  }
}

void whiteFL(bool shouw) {
  for(byte i = 0; i < NUM_LEDS_F; i++) {
    ledsFL[i].setRGB(255,255,255);
  }
  if(shouw) {
    FastLED.show();
  }
}

void whiteFR(bool shouw) {
  for(byte i = 0; i < NUM_LEDS_F; i++) {
    ledsFR[i].setRGB(255,255,255);
  }
  if(shouw) {
    FastLED.show();
  }
}

void whiteBR(bool shouw) {
  for(byte i = 0; i < NUM_LEDS_B; i++) {
    ledsBR[i].setRGB(255,255,255);
  }
  if(shouw) {
    FastLED.show();
  }
}

void whispBL(byte startled, byte endled, bool shouw) {
  for(byte i = startled-1; i <= endled-1; i++) {
    ledsBL[i].setRGB(255,255,255);
  }
  if(shouw) {
    FastLED.show();
  }
}

void whispFL(byte startled, byte endled, bool shouw) {
  for(byte i = startled-1; i <= endled-1; i++) {
    ledsFL[i].setRGB(255,255,255);
  }
  if(shouw) {
    FastLED.show();
  }
}

void whispFR(byte startled, byte endled, bool shouw) {
  for(byte i = startled-1; i <= endled-1; i++) {
    ledsFR[i].setRGB(255,255,255);
  }
  if(shouw) {
    FastLED.show();
  }
}

void whispBR(byte startled, byte endled, bool shouw) {
  for(byte i = startled-1; i <= endled-1; i++) {
    ledsBR[i].setRGB(255,255,255);
  }
  if(shouw) {
    FastLED.show();
  }
}

void rgbBL(byte r, byte g, byte b, bool shouw) {
  for(byte i = 0; i < NUM_LEDS_B; i++) {
    ledsBL[i].setRGB(r,g,b);
  }
  if(shouw) {
    FastLED.show();
  }
}

void rgbFL(byte r, byte g, byte b, bool shouw) {
  for(byte i = 0; i < NUM_LEDS_F; i++) {
    ledsFL[i].setRGB(r,g,b);
  }
  if(shouw) {
    FastLED.show();
  }
}

void rgbFR(byte r, byte g, byte b, bool shouw) {
  for(byte i = 0; i < NUM_LEDS_F; i++) {
    ledsFR[i].setRGB(r,g,b);
  }
  if(shouw) {
    FastLED.show();
  }
}

void rgbBR(byte r, byte g, byte b, bool shouw) {
  for(byte i = 0; i < NUM_LEDS_B; i++) {
    ledsBR[i].setRGB(r,g,b);
  }
  if(shouw) {
    FastLED.show();
  }
}

void Einsatzfahrt1(byte k) {
  for(byte l = 0; l < k; l++) {
          // Polizei Einsatzfahrt 1 / Nix
          colorFL(160,0);
           wait(0.25);
          colorFR(160,0);
           wait(0.5);
          cleanFL(0);
           wait(0.25);
          cleanFR(0);
          colorBL(160,0);
          colorBR(160,0);
           wait(0.25);
          colorFL(160,0);
           wait(0.25);
          colorFR(160,0);
          cleanFL(0);
          cleanBL(0);
          cleanBR(0);
           wait(0.25);
          cleanFR(0);
          colorBL(160,0);
          colorBR(160,0);
           wait(0.25);
           wait(0.25);
          cleanBL(0);
          cleanBR(1);
  }
}

void Einsatzfahrt2(byte k) {
  for(byte l = 0; l < k; l++) {
      // Polizei Einsatzfahrt 2
      for(byte j = 0; j < 2; j++) {
        colorBL(160,0);
        colorFR(160,0);
         wait(0.28);
        cleanBL(0);
        cleanFR(0);
         wait(0.14);
      }
      colorBL(160,0);
      colorFR(160,0);
      wait(0.57);
      cleanBL(0);
      cleanFR(0);
      for(byte j = 0; j < 2; j++) {
        colorBR(160,0);
        colorFL(160,0);
         wait(0.28);
        cleanBR(0);
        cleanFL(0);
         wait(0.14);        
      }
      colorBR(160,0);
      colorFL(160,0);
       wait(0.57);
      cleanBR(0);
      cleanFL(1);      
  }
}

void EinsatzfahrtAchtung1(byte k) {
  for(byte l = 0; l < k; l++) {
      // Polizei Achtung! Einsatz! 1
      colorFL(160,0);
       wait(0.25);
      colorFR(160,0);
        whiteBL(0);
        whiteBR(0);
       wait(0.125);
        cleanBL(0);
        cleanBR(0);
       wait(0.0625);
        whiteBL(0);
        whiteBR(0);
       wait(0.125);
        cleanBL(0);
        cleanBR(0);
       wait(0.0625);
        whiteBL(0);
        whiteBR(0);
       wait(0.125);
        cleanBL(0);
        cleanBR(0);
       wait(0.0625);
        whiteBL(0);
        whiteBR(0);
       wait(0.125);
        cleanBL(0);
        cleanBR(0);
       wait(0.0625);
        whiteBL(0);
        whiteBR(0);
       wait(0.125);
        cleanBL(0);
        cleanBR(0);
       wait(0.0625);
        whiteBL(0);
        whiteBR(0);
       wait(0.125);
        cleanBL(0);
        cleanBR(0);
       wait(0.1875);
      cleanFL(0);
       wait(0.25);
      cleanFR(0);
        colorBL(160,0);
        colorBR(160,0);
       wait(0.25);
      colorFL(160,0);
       wait(0.25);
      colorFR(160,0);
      cleanFL(0);
        cleanBL(0);
        cleanBR(0);
       wait(0.25);
      cleanFR(0);
        colorBL(160,0);
        colorBR(160,0);
      whiteFL(0);
       wait(0.125);
      cleanFL(0);
       wait(0.0625);
      whiteFL(0);
       wait(0.0625);
      whiteFR(0);
       wait(0.0625);
      cleanFL(0);
       wait(0.0625);
      cleanFR(0);
      whiteFL(0);
       wait(0.0625);
      whiteFR(0);
       wait(0.0625);
      cleanFL(0);
        cleanBL(0);
        cleanBR(0);
       wait(0.0625);
      cleanFR(0);
       wait(0.0625);
      whiteFR(0);
       wait(0.0625);
       wait(0.0625);
      cleanFR(0);     
  }
}

void EinsatzfahrtAchtung2(byte k) {
  for(byte l = 0; l < k; l++) {
      // Polizei Achtung! Einsatz! 2

        colorBL(160,0);
        colorFR(160,0);
         wait(0.14);
          whiteBR(0);
          whiteFL(0);
         wait(0.14);
        cleanBL(0);
        cleanFR(0);
         wait(0.14);
        colorBL(160,0);
        colorFR(160,0);
         wait(0.14);
          cleanBR(0);
          cleanFL(0);
         wait(0.14);
        cleanBL(0);
        cleanFR(0);
          whiteBR(0);
          whiteFL(0);
         wait(0.14);
      
      colorBL(160,0);
      colorFR(160,0);
       wait(0.42);
        cleanBR(0);
        cleanFL(0);
       wait(0.14);
      cleanBL(0);
      cleanFR(0);

        colorBR(160,0);
        colorFL(160,0);
         wait(0.14);
          whiteBL(0);
          whiteFR(0);
         wait(0.14);
        cleanBR(0);
        cleanFL(0);
         wait(0.14);        
        colorBR(160,0);
        colorFL(160,0);
         wait(0.14);
          cleanBL(0);
          cleanFR(0);
         wait(0.14);
        cleanBR(0);
        cleanFL(0);
          whiteBL(0);
          whiteFR(0);        
         wait(0.14);        


      colorBR(160,0);
      colorFL(160,0);
       wait(0.42);
        cleanBL(0);
        cleanFR(0);
       wait(0.14);
      cleanBR(0);
      cleanFL(1);     
  }
}

void loop() {
  SwitchPosUpdate();
  Main();
}

