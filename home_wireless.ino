
#include<ESP8266WiFi.h>
const char* ssid = "YOUR WIFI NAME";
const char* password = "YOUR ID PASSWORD";

int ledPin = D1;
WiFiServer server(80);

void setup() {
      Serial.begin(115200);
      delay(10);

      pinMode(ledPin,OUTPUT);
      digitalWrite(ledPin,LOW);

      Serial.println();
      Serial.println();
      Serial.print("Connecting to...");
      Serial.println(ssid);

      WiFi.begin(ssid, password);
      
      while(WiFi.status()!=WL_CONNECTED);{
      delay(500);
      Serial.print(".");
      }
      Serial.println("");
      Serial.println("WiFi connected");

      //starting the server
      server.begin();
      Serial.println("server started");

      //printing ip address
      Serial.print("use this url to connect: ");
      Serial.print("http://");
      Serial.print(WiFi.localIP());
      Serial.println("/");
      
      }

void loop() {
  WiFiClient client=server.available();
  if(!client)
  return;

  Serial.println("New client");
  while(!client.available()){
    delay(5);
  }

//reading:
String request = client.readStringUntil('\r');
Serial.println(request);
client.flush();

int value = LOW;
if(request.indexOf("/LED=ON") != -1){
  digitalWrite(ledPin,HIGH);
  value= HIGH;
  
  }
 if(request.indexOf("/LED=OFF") != -1){
  digitalWrite(ledPin,LOW);
  value= LOW;
  
  } 

    client.println("HTTP/1.1 200 OK");
    client.println("Connect type text/html");
    client.println("");
    client.println("<!DOCTYPE HTML>");
    client.println("html");
    
     

   client.println("the Buzzer is currently");
   if(value==HIGH){
     client.print(" ON");
   }else{
     client.print(" OFF");
   }
    client.println("<br><br>");
    client.println("<a href=\"/LED=ON\"\"><button>Turn ON</button></a><br>");
    client.println("<a href=\"/LED=OFF\"\"><button>Turn OFF</button></a><br>");
    client.println("</html>");
    delay(5);
    
    Serial.println("client disconnected");
    Serial.println("");
   
   
}
