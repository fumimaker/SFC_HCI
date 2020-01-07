//                              10n
// PIN 9 --[10k]-+-----10mH---+--||-- OBJECT
//               |            |
//              3.3k          |
//               |            V 1N4148 diode
//              GND           |
//                            |
//Analog 0 ---+------+--------+
//            |      |
//          100pf   1MOmhm
//            |      |
//           GND    GND



#define SET(x,y) (x |=(1<<y))				//-Bit set/clear macros
#define CLR(x,y) (x &= (~(1<<y)))       		// |
#define CHK(x,y) (x & (1<<y))           		// |
#define TOG(x,y) (x^=(1<<y))            		//-+



#define N 160  //How many frequencies

char registerNum = -1;
int sizeOfArray = N;
float results[N];            //-Filtered result buffer
float freq[N];            //-Filtered result buffer


void setup(){
  TCCR1A=0b10000010;        //-Set up frequency generator
  TCCR1B=0b00011001;        //-+
  ICR1=110;
  OCR1A=55;

  pinMode(9, OUTPUT);        //-Signal generator pin
  pinMode(8, OUTPUT);        //-Sync (test) pin
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  Serial.begin(115200);

  for(int i=0;i<N;i++){      //-Preset results
    results[i]=0;           //-+
  }
}

void loop(){ 
  for(unsigned int d=0; d<N; d++){
    int v = analogRead(A0);    //-Read response signal
    CLR(TCCR1B, 0);           //-Stop generator
    TCNT1 = 0;                //-Reload new frequency
    ICR1 = d;                 // |
    OCR1A = d / 2;            //-+
    SET(TCCR1B, 0);           //-Restart generator

    results[d] = results[d] * 0.5 + (float)(v) * 0.5; //Filter results
    freq[d] = d;
  }
  TOG(PORTB, 0);            //-Toggle pin 8 after each sweep (good for scope)

  for(uint8_t i=0; i<4; i++){
    if(!digitalRead(3+i)){
      
    }
  }

}