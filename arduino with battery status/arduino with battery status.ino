//it is the code for Arduino and rfm98 sensor node which sense the data and send it to the esp32rfm gateway the code i have added in my repositories.




#include <SPI.h>
#include <RHReliableDatagram.h>
#include <RH_RF95.h>
//#define SERVER_ADDRESS 200
#define RFM95_CS 10
#define RFM95_RST 9
#define RFM95_INT 2
#define RF95_FREQ 434.0
//float battery;
#define powerhdc 8
#define powerrfm 7
long duration;
int distance;
float iREF = 1.08;
#include <HDC2080.h>

#define ADDR 0x40
HDC2080 sensor(ADDR);

float temperature = 0, humidity = 0;

RH_RF95 rf95(RFM95_CS, RFM95_INT);
//RHReliableDatagram manager(rf95, SERVER_ADDRESS);

void setup()
{
  Serial.begin(9600);
  //SETUP WATCHDOG TIMER
  WDTCSR = (24);                        //CHANGE ENABLE AND WDE - ALSO RESET
  WDTCSR = (33);                        //PRESACLERS
  WDTCSR |= (1<<6);                     //ENABLE INTERRUPT MODE

  //DISABLE ADC
 
 
  //ENABLE SLEEP
  SMCR |= (1<<2); //POWER DOWN MODE
  SMCR |= 1; //ENABLE SLEEP
    pinMode(powerrfm, OUTPUT);
      pinMode(powerhdc, OUTPUT);

    Serial.println("--------------- HDC2080-------------------------- ");

  // Initialize I2C communication
  sensor.begin();
    
  // Begin with a device reset
  sensor.reset();
  
  // Set up the comfort zone
  sensor.setHighTemp(28);         // High temperature of 28C
  sensor.setLowTemp(22);          // Low temperature of 22C
  sensor.setHighHumidity(55);     // High humidity of 55%
  sensor.setLowHumidity(40);      // Low humidity of 40%
  
  // Configure Measurements
  sensor.setMeasurementMode(TEMP_AND_HUMID);  // Set measurements to temperature and humidity
  sensor.setRate(ONE_HZ);                     // Set measurement frequency to 1 Hz
  sensor.setTempRes(FOURTEEN_BIT);
  sensor.setHumidRes(FOURTEEN_BIT);
  
  //begin measuring
  sensor.triggerMeasurement();

  
  analogReference(EXTERNAL);
  //burn some ADC readings after reference change
  for(int i=0; i<8; i++) analogRead(A0);
  
  rf95.init();
  rf95.setFrequency(RF95_FREQ);
  rf95.setTxPower(23, false);
//  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
//  pinMode(power, OUTPUT);  
//  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  //digitalWrite(power, HIGH);
}
int16_t packetnum = 0;  // packet counter, we increment per xmission
void loop()
{
  
  digitalWrite(powerhdc, HIGH);
  digitalWrite(powerrfm, HIGH);
  delay(1000);
  char data[50],hum[10],temp[10],batt[10];
      temperature= sensor.readTemp();
  humidity  = sensor.readHumidity();
 float battery= fReadVcc();
 
 //float sensorValue = analogRead(A0);
  //float battery = ((sensorValue * 5.0 )/ 1023.0);
//float  battery = 3.4;
  dtostrf(humidity,4,2,hum);
  dtostrf(temperature,4,2,temp);
  dtostrf(battery,4,2,batt);
  Serial.println(humidity);
  Serial.println(temperature);
  Serial.print(battery);
  Serial.println("V");
//  digitalWrite(power, HIGH);
  delay(1000);
  //digitalWrite(trigPin, LOW);
  //delayMicroseconds(2);
  //digitalWrite(trigPin, HIGH);
  //delayMicroseconds(10);
  //digitalWrite(trigPin, LOW);
  //duration = pulseIn(echoPin, HIGH);
  //distance= duration*0.034/2;
  itoa(packetnum++, data+13, 10);
  sprintf(data,"temperature=%s\t",temp);
  strcat(data,"Humidity= ");
  strcat(data,hum);
  strcat(data,"\tBattery =");
   strcat(data,batt);
  strcat(data,",\n");
  //strcat(data,"NULL");
  
  data[64] = 0;
   // rf95.send((uint8_t *)data, 10); 
 // manager.sendtoWait((uint8_t *)data, sizeof(data), 2);
  rf95.send((uint8_t *)data, sizeof(data));
  //manager.sendtowait((uint8_t *)data, 40);
  digitalWrite(powerhdc, LOW);
    digitalWrite(powerrfm, LOW);
for (int i=0; i<3; i++){                    //SETTING WATCHDOG TIMER FOR 5MIN
  //BOD DISABLE
  MCUCR |= (3 << 5);                           //SET BOTH BOD AND BODSE AT THE SAME TIME
  MCUCR = (MCUCR & ~(1 << 5 )) | (1 << 6);     //THEN SET BOTH THE BITS AT THE SAME TIME  
  __asm__ __volatile__("sleep");
 }
}
        //  ISR(WDT_vect){          
//}
float fReadVcc() {
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(3); //delay for 3 milliseconds
  ADCSRA |= _BV(ADSC); // Start ADC conversion
  while (bit_is_set(ADCSRA,ADSC)); //wait until conversion is complete
  int result = ADCL; //get first half of result
  result |= ADCH<<8; //get rest of the result
  float batVolt = (iREF / result)*1023; //Use the known iRef to calculate battery voltage
  return batVolt;
}
