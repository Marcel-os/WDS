
#include <Wire.h>
#include <SoftwareSerial.h>
#include <MPU6050.h>
#include <LPS.h>
#include <LSM6.h>
#include <LIS3MDL.h>

LPS ps;
LSM6 imu; 
//max +/-8g RAW * 0.000244 * g = [m/sek^2]
//max +/-2000deg/s RAW * 0.07 = [deg/sek]
LIS3MDL mag;
SoftwareSerial Bluetooth(A0, A1); // RX, TX

float g = 9.8113;
//char report[80];

void setup() 
{
  analogReference(INTERNAL);
  Serial.begin(115200);
  Bluetooth.begin(115200);
  Wire.begin();

    if (!ps.init())
  {
    Serial.println("Failed to autodetect pressure sensor!");
    while (1);
  }
  
    if (!imu.init())
  {
    Serial.println("Failed to detect and initialize IMU!");
    while (1);
  }

    if (!mag.init())
  {
    Serial.println("Failed to detect and initialize magnetometer!");
    while (1);
  }

  ps.enableDefault();
  imu.enableDefault();
  mag.enableDefault();
}

void print_normalized_BT (float zmienna, int mnoznik, bool czy_znak, int ilosc_znakow){
  int zmienna_int = abs((int)(zmienna*mnoznik));
  char tablica_znakow [ilosc_znakow];
  for(int i = 1; i <= ilosc_znakow; i++){
    tablica_znakow [ilosc_znakow - i] = zmienna_int%10 + 48;
    zmienna_int /= 10;
  }
  
  if(czy_znak){
    if( zmienna >= 0) Bluetooth.print('+');
      else Bluetooth.print('-');
  }
  
  for(int i = 0; i < ilosc_znakow; i++){
    Bluetooth.print(tablica_znakow[i]);
  }
}


void loop()
{
  float pressure = ps.readPressureMillibars();
  float altitude = ps.pressureToAltitudeMeters(pressure);
  float temperature = ps.readTemperatureC();
  imu.read();
  mag.read();

  //////////////////////////////////////////////////////////////////////////////////////
  
//  Serial.print("Ax: ");
//  Serial.print(imu.a.x * 0.000244 * g);
//  Serial.print("\tAy: ");
//  Serial.print(imu.a.y * 0.000244 * g);
//  Serial.print("\tAz: ");
//  Serial.print(imu.a.z * 0.000244 * g);
//
//  //m/s2
//
//  Serial.print("\tGx: ");
//  Serial.print(imu.g.x * 0.07);
//  Serial.print("\tGy: ");
//  Serial.print(imu.g.y * 0.07);
//  Serial.print("\tGz: ");
//  Serial.print(imu.g.z * 0.07);
//
//  //deg/s
//  
//  
//  Serial.print("\tMx: ");
//  Serial.print(mag.m.x / 6842.0);
//  Serial.print("\tMy: ");
//  Serial.print(mag.m.y / 6842.0);
//  Serial.print("\tMz: ");
//  Serial.print(mag.m.z / 6842.0);
//
//  //gauss
//
//  Serial.print("\tp: ");
//  Serial.print(pressure);
//  Serial.print("\ta: ");
//  Serial.print(altitude);
//  Serial.print("\tt: ");
//  Serial.print(temperature);
//
//  //hpa, deg C
//
//  Serial.println();

  //////////////////////////////////////////////////////////////////////////////////////
  //print_normalized_BT (float zmienna, int mnoznik, bool czy_znak, int ilosc_znakow)

  //accelerometer
  
  Bluetooth.print("S");
  print_normalized_BT (imu.a.x * 0.000244 * g, 100, 1, 4);
  Bluetooth.print(" ");
  print_normalized_BT (imu.a.y * 0.000244 * g, 100, 1, 4);
  Bluetooth.print(" ");
  print_normalized_BT (imu.a.z * 0.000244 * g, 100, 1, 4);

  //gyroscope
  
  Bluetooth.print(" ");
  print_normalized_BT (imu.g.x * 0.07, 1, 1, 4);
  Bluetooth.print(" ");
  print_normalized_BT (imu.g.y * 0.07, 1, 1, 4);
  Bluetooth.print(" ");
  print_normalized_BT (imu.g.z * 0.07, 1, 1, 4);


  //magnetometer

  Bluetooth.print(" ");
  print_normalized_BT (mag.m.x / 6842.0, 1000, 1, 4);
  Bluetooth.print(" ");
  print_normalized_BT (mag.m.y / 6842.0, 1000, 1, 4);
  Bluetooth.print(" ");
  print_normalized_BT (mag.m.z / 6842.0, 1000, 1, 4);

  //temperature

  Bluetooth.print(" ");
  print_normalized_BT (temperature, 10, 1, 3);
  
  //pressure

  Bluetooth.print(" ");
  print_normalized_BT (pressure, 10, 0, 5);

  //altitude

  Bluetooth.print(" ");
  print_normalized_BT (altitude, 10, 0, 5);

  //voltage

  Bluetooth.print(" ");
  print_normalized_BT (analogRead(A7)*(1.1/1024.0)*7.63, 100, 0, 3);

  Bluetooth.println();
  delay(25);
}
