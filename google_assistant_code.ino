#include <ESP8266WiFi.h> 
#include <Servo.h>
const char* ssid = "name of your wifi"; //need name of wifi ********** 
const char* password = "password of your wifi";//need password of wifi ********** 
const char* host ="api.thingspeak.com";
Servo servomove1;//hand
Servo servomove2;//updown
bool flag=1;
void setup () {
Serial.begin (115200);
Serial.println ();
Serial.printf("Connecting to %s ", ssid);
WiFi.begin (ssid, password);
while (WiFi.status () != WL_CONNECTED)
{
  delay (500);
  Serial.print (".");
}
Serial.println (" connected");
servomove1.attach (7); //servo hand pin 
servomove2.attach (11); //servo updown pin 
}
void loop () 
{
  Serial.println("ok");
  WiFiClient client;
  String line;
  Serial.printf("\n[Connecting to %s ... ", host);
  if (client.connect (host, 80))
  {
  Serial.println ("connected]");
  Serial.println ("[Sending a request]");
  client.print (String ("GET /") + "the api from thingspeak" + 
  "HTTP/1.1\n" +   
  "Host: " + host + "\r\n" +
  "Connection: close\r\n" + "\r\n" ) ;
  Serial.println (" [Response:]");
  while (client.connected () || client.available ())
  {
  if (client.available ())
  {
  line = client.readString (); 
  Serial.println (line);
  int x = line.length();
  String y= line.substring(x-5);
  if (y[0] == '0'&&flag==1){ // hand open 
    servomove1.write (15) ;
    delay(5);
    servomove1.write (35) ;
    delay(5);
    servomove1.write (50) ;
    delay(5);
   Serial.println("Hand is Open");
     flag=0;
  // y[0]='1'; //  we can't change the value of field
  }
    /*else if( y[0]=='0'&& flag==0){ // hand close
     servomove1.write (35) ;
    delay(5);
    servomove1.write (15) ;
    delay(5);
    servomove1.write (0) ;
    delay(5);
   Serial.println("Hand is close");
   flag=1;
   //y[0]='0'; //   we can't change the value of field
  }*/
  /*else if (y [0] == '2'&&flag==0){    //servo2 down                                     //field1=0,2
    servomove2.write (0) ;
    delay(5);
    servomove2.write (45) ;
    delay(5);
    servomove2.write (90) ;
    delay(5);                                                       // 0 open hand     
    Serial.println("Updown is down") ;                              // 2 down servo  
    flag=1;
     // y[0]='3'; //  we can't change the value of field                                   
     }
     else if (y [0] == '2'&&flag==1){    //servo2 up                                     
    servomove2.write (45) ;
    delay(5);
    servomove2.write (0) ;
    delay(5);                                     
    Serial.println("Updown is up") ;  
    flag=0;                            
     // y[0]='2'; //  we can't change the value of field                                                     
     }*/
  }
}
  client.stop (); 
  Serial.println ("\n[Disconnected] ");
  }
  else
  {
  Serial.println ("connection failed!] "); 
  client.stop ();
  }

}//void loop
