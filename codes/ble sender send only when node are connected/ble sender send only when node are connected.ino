/*
    AMBIENT .
    SENDING THE DATA FROM NODE TO GATEWAY
    This code for the NODE
    Temperature and humidity sensor hdc2080 and esp32 
    data transmission using inbuilt ble 4.2
    for demo having the sleep time of 10 seconds and active for 1.5 seconds
*/

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <HDC2080.h>
#include <iostream>
#include <string>

#define ADDR 0x40
HDC2080 sensor(ADDR);

#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  10 d       /* Time ESP32 will go to sleep (in seconds) */

BLECharacteristic *pCharacteristic;
bool espconnected=false; 

int temperature = 0, humidity = 0;

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

class MyServerCallbacks: public BLEServerCallbacks{
  void onConnect(BLEServer* pServer) 
  {
    espconnected=true;
    
  };

  void onDisconnect(BLEServer *pServer)
  {
    espconnected=false;
  };
};

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");

  BLEDevice::init("esp");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );

  while(!Serial);

       delay(50); 

   // starting I2C protocol
         sensor.begin();
  
  // reseting hdc2080
         sensor.reset();
  
  // Set up the comfort zone
    sensor.setHighTemp(28);        
    sensor.setLowTemp(22);          
    sensor.setHighHumidity(70);   
    sensor.setLowHumidity(40);      
  
  // Configure Measurements
    sensor.setMeasurementMode(TEMP_AND_HUMID);  
    sensor.setRate(ONE_HZ);                    
    sensor.setTempRes(FOURTEEN_BIT);
    sensor.setHumidRes(FOURTEEN_BIT);
    sensor.triggerMeasurement();
  
    delay(100);
    while(1)
    { 
        humidity = (sensor.readHumidity());
        temperature =(sensor.readTemp());
        if (isnan(temperature) || isnan(humidity)) 
    {
      Serial.println("Failed to read from HDC2080");
    }
    else 
    {
      Serial.print("HUMIDITY: ");
      Serial.print(humidity);
      Serial.print(" %\t");
      Serial.print("TEMPERATURE: ");
      Serial.print(temperature);
      Serial.println(" *C");
    }
    

    
      pService->start();
      // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this still is working for backward compatibility
      BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
      pAdvertising->addServiceUUID(SERVICE_UUID);
      pAdvertising->setScanResponse(true);
      pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
      pAdvertising->setMinPreferred(0x12);
      BLEDevice::startAdvertising();
      Serial.println("Characteristic defined! Now you can read it in your phone!");

//     pCharacteristic->setValue(HDC2080tData);
      delay(50);  

      if(espconnected)
      {
        char humidityString[2];
        char temperatureString[2];
        dtostrf(humidity, 1, 2, humidityString);
        dtostrf(temperature, 1, 2, temperatureString);

        char HDC2080tData[24];
        sprintf(HDC2080tData, "temp:%d*C\t\thumid:%d%c", temperature,humidity,'%');
 
        delay(2000);
        pCharacteristic->setValue(HDC2080tData);
    
        // pCharacteristic->notify();
        Serial.print(" SENT DATA :\n ");
        Serial.println(HDC2080tData);
        Serial.println("------------------------------------------------------------");

    
        Serial.printf("entering deep sleep mode for 10 Seconds.\n");
        esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
        esp_deep_sleep_start();
      }
   }
}

void loop() {

  //delay(2000);
}
