
#include <Servo.h>
#include <ESP8266WiFi.h>                // Include main library

//#define SERVO_PIN D2  // นี่คือกำหนดขาให้ Servo

const char* ssid     = "shareEWTC";     // Set SSID
const char* password = "12345abcde"; // Set password
const char* host = "dweet.io";          // Set host

String line;
String test;
String strServo;

//int intStart[4] = {129, 120, 103, 102};

//Servo myservo;  // ประกาศ object ของการใช้ Servo
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;

int analogValue;

void setup()
{
  //myservo.attach(SERVO_PIN);
  servo1.attach(4);
  servo2.attach(0);
  servo3.attach(2);
  servo4.attach(14);

  Serial.begin(115200);                 // Print setting message
  delay(10);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");                  // Print WiFi status
  }
  Serial.println("");
  Serial.println("WiFi connected");     // Print connect status
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());       // Print IP address
} // setup

void loop()
{
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;              // Set HTTP Port
  if (!client.connect(host, httpPort))  // Test connection
  {
    Serial.println("connection failed");  // Print connection fail messag
    return;
  }
  //https://dweet.io/get/latest/dweet/for/ks_bot
  client.print(String("GET /get/latest/dweet/for/ks_bot HTTP/1.1\r\n") +
               "Host: " + host + "\r\n" +
               "Connection: keep-alive\r\n" +
               "Cache-Control: max-age=0\r\n\r\n");
  delay(3000);

  while (client.available())
  {
    line = client.readStringUntil('\r'); //this full word ***

    test = line.substring(134, 137); //cut word for value **

    strServo = line.substring(131, 132);

    analogValue = test.toInt(); // Change String to int

    //set deg of servo (val, start, 0 deg, end deg)
    analogValue = map(analogValue, 0, 100, 129, 154);

  } // while

  Serial.println("Full word = " + line);
  Serial.println();
  Serial.println("Server Value = " + test);
  Serial.println();
  Serial.println("Servo No. = " + strServo);
  Serial.println();
  Serial.print("andlogValue ==> ");
  Serial.println(analogValue);
  Serial.println();
  Serial.println();

  //output to servo
  //myservo.write(analogValue);

  switch (strServo.toInt()) {
    case 1:
      Serial.println("Output to Servo 1");
      Serial.println();
      servo1.write(analogValue);
      break;
      
    case 2:
      Serial.println("Output to Servo 2");
      Serial.println();
      servo2.write(analogValue);
      break;
      
    case 3:
      Serial.println("Output to Servo 3");
      Serial.println();
      servo3.write(analogValue);
      break;
      
    case 4:
      Serial.println("Output to Servo 4");
      Serial.println();
      servo4.write(analogValue);
      break;
      
    default:
      // statements
      break;
  }

} // loop







