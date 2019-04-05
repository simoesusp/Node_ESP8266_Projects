// All Digital Pins have PWM, except D0   !!!!!!!!!!

// IO PINOUT Definition:
#define D0 16
#define D1 5
#define D2 4
#define D3 0
#define D4 2
#define D5 14
#define D6 12
#define D7 13
#define D8 15
#define A0 0    This need checking !!!



const int WET= D0; // Wet Indicator at Digital PIN D0
const int DRY= D4;  // Dry Indicator at Digital PIN D4

const int sense_Pin= A0; // Soil Sensor input at Analog PIN A0
int value= 0;

void setup() {
   Serial.begin(9600);
   pinMode(WET, OUTPUT);
   pinMode(DRY, OUTPUT);
   delay(2000);
}

void loop() {
   Serial.print("MOISTURE LEVEL : ");
   value= analogRead(sense_Pin);
   value= value/10;
   Serial.println(value);
   if(value<50)
   {
      digitalWrite(WET, HIGH);
   }
   else
   {
      digitalWrite(DRY,HIGH);
   }
   delay(1000);
   digitalWrite(WET,LOW);
   digitalWrite(DRY, LOW);
}
