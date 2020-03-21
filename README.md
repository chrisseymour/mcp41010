# mcp41010
digital potentiometer control program
```
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
```
