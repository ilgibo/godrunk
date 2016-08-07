#include <SoftwareSerial.h>
#include <SocketIOClient.h>

byte mac[] = { 0xAA, 0x00, 0xBE, 0xEF, 0xFE, 0xEE };
IPAddress ip_l(192,168,0,12);
IPAddress dns_l(8,8,8,8);
IPAddress gateway_l(192,168,0,1);
IPAddress sub_mask(255,255,255,0);

char servername[] = "godrunk.azurewebsites.net";
int port = 80;

extern String RID;
extern String Rname;
extern String Rcontent;

String msg;
char c;
int counter;

SocketIOClient client;
SoftwareSerial tag(6,7);

void setup() {
  // put your setup code here, to run once
  tag.begin(9600);
  Serial.begin(9600);
  Ethernet.begin(mac, ip_l, dns_l, gateway_l, sub_mask);

  if (!client.connect(servername, port))
    Serial.println(F("Not connected."));
  if (client.connected())
  {
    Serial.println("Connected");
    //client.send("connection", "message", "Connected !!!!");
  }
  else
  {
    Serial.println("Connection Error");
    while(1);
  }
  delay(1000);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(client.monitor())
  {
    Serial.println(RID);
    Serial.println(Rname); 
    Serial.println(Rcontent);
    //client.send("ping","pong","{ciao:0}");
  }
   
 if (tag.available())
{
  if( counter == 13)
  {
     c = tag.read();
     msg += c;
     counter = 0;
     Serial.println(msg);
     client.send("ping", "TAG",msg);
     msg = "\0";
    }
    else
    {
       c = tag.read();
        msg += c;
        counter++;
      }
  
  }
    
}
