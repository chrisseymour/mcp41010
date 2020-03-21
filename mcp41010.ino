//Christopher Seymour
//June 11, 2016
//MCP41010 digital potentiometer 10kOhm, 256 step (8 bit)
//        
//
// Chip Layout
//       ______
//  CS -|o1  8 |- Vdd
// SCK -| 2  7 |- PB0
//  SI -| 3  6 |- PW0
// Vss -|_4__5_|- PA0
//
// 4) Vdd = +V  (2.7-5.5V)
// 8) Vss = 0V  (ground)
// 5) PA0 = Terminal A of Potentiometer
// 6) PW0 = Wiper of Potentiometer
// 7) PB0 = Terminal B of Potentiometer
// 1) CS  = Chip Select (used to execture new command)
// 2) SCk = Serial Clock (used to clock in new register data)
// 3) SI  = Serail Input (used to input data and bytes)
//
// Command String
// 
// Chip instructions:
//      When the CS pin goes low, the chip waits for a new command
//    tit will now look for two bytes (16 bits) of information from the SI pin
//    each bit is clocked on the raising edge of the SCK pin
//    the  value of SI when the SCK pin goes high is the bit clocked
//    Data registers are loaded on rising edge of CS. 
//    Shift register is loaded with zeros at this time
//    
//  CS `````|________________________________________________________|``````
// 
//  SCK ______|``|_|``|_|``|_|``|_|``|_|``|_|``|_|``|_|``|__.....__|``|___
//          |  1    2    3    4    5    6    7    8  |  9   10-15  16  |
//
//  SI  =   |  x    x   C1   C2    x    x    x    P0 |  < DATA BYTE >  |
//
//  C1 C0 = command
//  0  0    NOP (no operation)
//  1  1    NOP
//  0  1    Write Data
//  1  0    Shutdown
//  
//  P0 = Potentiometer selection 
//  1 execeute command
//  0 do NOT execute command
// 
// x = "do not care" bits
//
//
// Shfit Functions:
//  shiftOUt(dataPin,clockPin,bitOrder,value)
//    dataPin  = where to outut bits
//    clockPin = pin to toggle once dataPin has been set to the right value
//    bitOrder = MSBFIRST or LSBFIRST
//    vlaue    = byte to send

//arduino pin definitions
#define pa0 3   // Pot Terminal A
#define cs 5   // Chip Select
#define sck 6   // Serial Clock
#define si 7  // Serail Input
#define voltage A0  //analogRead vout

#define clocker 10
#define timer 250
#define start_value 10

//command bytes
const byte writeData = B00010001;
const byte shutDown  = B00100001;

//most significant first

//volatile byte value = 0;
volatile byte command_array[8] = {0,0,0,1,0,0,0,1};


void shiftValue(byte chipSelect,byte clockPin, byte dataPin,byte value)//bitOrder
{
  Serial.print("begin! --> value = ");
  Serial.println(value);
  //set CS pin low to initiate byte input
  digitalWrite(chipSelect,LOW);
  delay(timer);
  //first send the command byte
  for (int i=0;i<8;i++)
  {
    //cycle trhough each bit of the byte
    //delay(timer);
    digitalWrite(si,bitRead(writeData,i);
    delay(clocker);
    digitalWrite(sck,HIGH);
    delay(clocker);
    digitalWrite(sck,LOW);
  }
  //send the data byte
  for (int j=0;j<8;j++)
    {
      //digitalWrite(si,LOW);
      Serial.print("bit ");
      Serial.print(j);
      Serial.print(" value ");
      Serial.println(bitRead(value,j));
      digitalWrite(si,bitRead(value,j));
      //delay(timer);
      digitalWrite(sck,HIGH);
      //delay(timer);
      digitalWrite(sck,LOW);
      //delay(timer);
    }
  //send the command
  //delay(timer);
  digitalWrite(chipSelect,HIGH);
  Serial.println("command sent!");
  //delay(timer);
}

void initialize()
{
  pinMode(pa0,OUTPUT);
  pinMode(cs,OUTPUT);
  pinMode(sck,OUTPUT);
  pinMode(si,OUTPUT);

  digitalWrite(sck,LOW);
  digitalWrite(si,LOW); 
  digitalWrite(pa0,HIGH);
  digitalWrite(cs,HIGH);
  
}

void extract()
{
  for (int l=0;l<5;l++)
  {
    Serial.println( analogRead(A0)*5./1024 );
    delay(timer);
  }
}



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  initialize();
}

void loop() {
  // put your main code here, to run repeatedly:
  //shiftOut();
  for (int k = 0; k<255;k++)
  {
    shiftValue(cs,sck,si,k);
    //delay(timer*5);
    extract();
  }
  //shiftValue(cs,sck,si,start_value);
  //delay(7500);
  
}
