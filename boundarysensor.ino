//#include <IoTtweetESP32.h>
#include <ThingSpeak.h>
#include <NTPClient.h>
// change next line to use with another board/shield
#include <ESP8266WiFi.h>
//#include <WiFi.h> // for WiFi shield
//#include <WiFi101.h> // for WiFi 101 shield or MKR1000
#include <WiFiUdp.h>
#include<SoftwareSerial.h> //Included SoftwareSerial Library
//Started SoftwareSerial at RX and TX pin of ESP8266/NodeMCU


const char *ssid     = "Redmi";
const char *password = "123456789kk";
WiFiClient  client;

unsigned long myChannelNumber = 974818;
unsigned long myChannelNumber2=978402;
const char * myWriteAPIKey = "WVRHPZACVFSWGWR1";
const char * myWriteAPIKey2 ="PNJK89SPR96I9BLO"; 

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

void setup(){
  Serial.begin(9600);
   ThingSpeak.begin(client);

  WiFi.begin(ssid, password);


}

void loop() {
  timeClient.update();

  Serial.println(timeClient.getFormattedTime());
   while ( WiFi.status() == WL_CONNECTED ) {
    delay ( 500 );
    Serial.print("..");
    Serial.print(WiFi.status());
    static float rs=WiFi.RSSI();
    float rssin = WiFi.RSSI();
    //float borderval=rs-50;
    //float atlevel=rs-45;
    //float atlevelhigh=rs-49;

  if(rssin<-90 && rssin>-170)
  {
    //delay(3000);
    if(rssin< -80 && rssin> -94)
    {
    Serial.print("At the border \n");
    }  
  }
  else if(rssin<-95)
  {
    //delay(3000);
    if(rssin<-171)
    {
    Serial.print("Out of boundary \n");
    }
  }
  else
  {
    Serial.print("Dog safe inside boundary");
  }
  
  Serial.print("RSSI:");
  Serial.println(rssin);


  // Write to ThingSpeak. There are up to 8 fields in a channel, allowing you to store up to 8 different
  // pieces of information in a channel.  Here, we write to field 1.
  int x = ThingSpeak.writeField(myChannelNumber, 1, rssin, myWriteAPIKey);
  if(x == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }

  int data;
  data = Serial.read(); //Read the serial data and store it
  Serial.print(data);

  int z = ThingSpeak.writeField(myChannelNumber2, 1, data, myWriteAPIKey2);
  if(z == 200){
    Serial.println("Channel update successful.");
  }
  else{
    Serial.println("Problem updating channel. HTTP error code " + String(x));
  }
  
  }
  if(WiFi.status() != WL_CONNECTED)
  {
    Serial.print("DOG OUT OF BOUNDARY");
  }

  delay(500);
}
