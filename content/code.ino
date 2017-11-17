/*
 * androidauto.ino
 *
 * Created: 14-Aug-16 2:04:31 PM
 * Author :NASEEFMK
 */ 

/* Create a WiFi access point and provide a web server on it. */

//#include <ESP8266WiFi.h>
//#include <WiFiClient.h> 
//#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
/* Set these to your desired credentials. */
const char *ssid = "MACHINSER";
const char *password = "123456789";

//ESP8266WebServer server(80);
WiFiServer server(80);



//void handleRoot() {
	//server.send(200, "text/html", "<h1>You are connected</h1>");
//}

void setup() {
	delay(1000);
	Serial.begin(115200);
	Serial.println();
	Serial.print("Configuring access point...");
	/* You can remove the password parameter if you want the AP to be open. */
	WiFi.softAP(ssid, password);

	IPAddress myIP = WiFi.softAPIP();
	Serial.print("AP IP address: ");
	Serial.println(myIP);
  pinMode(13, OUTPUT);
  digitalWrite(13, 0);
  pinMode(12, OUTPUT);
  digitalWrite(12, 0);
  pinMode(14, OUTPUT);
  digitalWrite(14, 0);
  pinMode(16, OUTPUT);
  digitalWrite(16, 0);
  pinMode(5, OUTPUT);
  digitalWrite(5, 0);
  pinMode(4, OUTPUT);
  digitalWrite(4, 0);

	
	//server.on("/", handleRoot);
	server.begin();
	Serial.println("HTTP server started");
  
}

void loop() {
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  // Match the request
  char val;
  if (req.indexOf("/gpio/0") != -1)
    val = 0;
  else if (req.indexOf("/gpio/1") != -1)
    val = 1;
  else if (req.indexOf("/gpio/2") != -1)
    val=2;
  else if (req.indexOf("/gpio/3") != -1)
    val=3;
  else if (req.indexOf("/gpio/4") != -1)
    val=4;
  else if (req.indexOf("/gpio/5") != -1)
    val=5;
  else if (req.indexOf("/gpio/6") != -1)
    val=6;
  else if (req.indexOf("/gpio/7") != -1)
    val=7;
  else if (req.indexOf("/gpio/8") != -1)
    val=8;
  else if (req.indexOf("/gpio/9") != -1)
    val=9;
  else if (req.indexOf("/gpio/a") != -1)
    val=10;
  else if (req.indexOf("/gpio/b") != -1)
    val=11;
  //else if (req.indexOf("/gpio/12") != -1)
    //val=12;
  
  else {
    Serial.println("invalid request");
    client.stop();
    return;
  }


  switch(val)
  {
    case 0:
     digitalWrite(13,0);
     break;
    case 1:
    digitalWrite(13,1);
    break;
    case 2:
    digitalWrite(12,0);
    break;
    case 3:
    digitalWrite(12,1);
    break;
    case 4:
    digitalWrite(14,0);
    break;
    case 5:
    digitalWrite(14,1);
    break;
    case 6:
    digitalWrite(16,0);
    break;
    case 7:
    digitalWrite(16,1);
    break;
    case 8:
    digitalWrite(5,0);
    break;
    case 9:
    digitalWrite(5,1);
    break;
    case 10:
    digitalWrite(4,0);
    break;
    case 11:
    digitalWrite(4,1);
    
  }
  

  // Set GPIO2 according to the request
  //digitalWrite(13, val);
  
  client.flush();

  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO is now ";
  s += (val)?"high":"low";
  s += "</html>\n";

  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");
	//server.handleClient();
} 
