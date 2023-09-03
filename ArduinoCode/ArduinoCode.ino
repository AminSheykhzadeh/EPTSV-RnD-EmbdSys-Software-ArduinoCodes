#include <Arduino.h>

#include <DFRobot_BMX160.h>

DFRobot_BMX160 bmx160;
sBmx160SensorData_t Omagn, Ogyro, Oaccel;

// functions
void PrintIMUData_f(void);

void setup(){
  Serial.begin(115200);
  delay(100);
  Serial.println("");Serial.println("HI:)");
  //init the hardware bmx160  
  if (bmx160.begin() != true){
    Serial.println("init false");
    while(1);
  }
  Serial.println("init success");

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
  delay(100);
}

void loop(){
  PrintIMUData_f();
  delay(500);
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