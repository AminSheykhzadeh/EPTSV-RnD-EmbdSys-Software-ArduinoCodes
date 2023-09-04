// arduino inc
#include <Arduino.h>
#include <SPI.h>
// IMU inc
#include <DFRobot_BMX160.h>
// MAX30003 inc
#include <protocentral_Max30003.h>
#include "protocentral_Max30003.h"


DFRobot_BMX160 bmx160;
MAX30003 max30003;
sBmx160SensorData_t Omagn, Ogyro, Oaccel;


// functions
void PrintIMUData_f(void);

void setup(){
  Serial.begin(115200);
  delay(100);
  Serial.println("");Serial.println("HI:)");

  //init the hardware bmx160  
  Serial.println("Initializing IMU");
  if (bmx160.begin() != true){
    Serial.println("init false");
    while(1);
  }
  
  //bmx160.setLowPower();   //disable the gyroscope and accelerometer sensor
  //bmx160.wakeUp();        //enable the gyroscope and accelerometer sensor
  //bmx160.softReset();     //reset the sensor
  
  /** 
   * enum{eGyroRange_2000DPS,
   *       eGyroRange_1000DPS,
   *       eGyroRange_500DPS,
   *       eGyroRange_250DPS,
   *       eGyroRange_125DPS
   *       }eGyroRange_t;
   **/
  //bmx160.setGyroRange(eGyroRange_500DPS);
  
  /**
   *  enum{eAccelRange_2G,
   *       eAccelRange_4G,
   *       eAccelRange_8G,
   *       eAccelRange_16G
   *       }eAccelRange_t;
   */
  //bmx160.setAccelRange(eAccelRange_4G);
  Serial.println("IMU init success");
  delay(100);

    

  //init the hardware MAX30003
    Serial.println("Initializing MAX30003");
    pinMode(MAX30003_CS_PIN,OUTPUT);
    digitalWrite(MAX30003_CS_PIN,HIGH); //disable device

    SPI.begin();
    //SPI.setBitOrder(MSBFIRST);
    //SPI.setDataMode(SPI_MODE0);
    bool ret = max30003.max30003ReadInfo();
    delay(1500);
    ret = max30003.max30003ReadInfo();
    ret = 0;
    ret = max30003.max30003ReadInfo();
    if(ret){
      Serial.println("Max30003 read ID Success");
    }else{

      while(!ret){
        //stay here untill the issue is fixed.
        ret = max30003.max30003ReadInfo();
        Serial.println("Failed to read ID, please make sure all the pins are connected");
        delay(300);
      }
    }

    Serial.println("Initialising the chip ...");
    delay(6000);
    max30003.max30003Begin();   // initialize MAX30003

}

void loop(){
    max30003.getEcgSamples();   //It reads the ecg sample and stores it to max30003.ecgdata .
    Serial.println(max30003.ecgdata);
    delay(8);

  // PrintIMUData_f();
  // delay(500);
}


void PrintIMUData_f(void){
  /* Get a new sensor event */
  bmx160.getAllData(&Omagn, &Ogyro, &Oaccel);

  /* Display the magnetometer results (magn is magnetometer in uTesla) */
  Serial.print("Magnetometer ");
  Serial.print("MX: "); Serial.print(Omagn.x); Serial.print("  ");
  Serial.print("MY: "); Serial.print(Omagn.y); Serial.print("  ");
  Serial.print("MZ: "); Serial.print(Omagn.z); Serial.print("  ");
  Serial.println("uT");

  /* Display the gyroscope results (gyroscope data is in g) */
  Serial.print("Gyroscope ");
  Serial.print("GX: "); Serial.print(Ogyro.x); Serial.print("  ");
  Serial.print("GY: "); Serial.print(Ogyro.y); Serial.print("  ");
  Serial.print("GZ: "); Serial.print(Ogyro.z); Serial.print("  ");
  Serial.println("g");
  
  /* Display the accelerometer results (accelerometer data is in m/s^2) */
  Serial.print("Accelerometer ");
  Serial.print("AX: "); Serial.print(Oaccel.x    ); Serial.print("  ");
  Serial.print("AY: "); Serial.print(Oaccel.y    ); Serial.print("  ");
  Serial.print("AZ: "); Serial.print(Oaccel.z    ); Serial.print("  ");
  Serial.println("m/s^2");

  Serial.println("");
}