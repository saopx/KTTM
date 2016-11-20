/*
 *  This sketch sends a message to a TCP server
 *
 */

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>





// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Mang&TT";
char pass[] = "mangtt!@#$";

int h = 1000*60*60;

ESP8266WiFiMulti WiFiMulti;

void setup() {
    pinMode(16, OUTPUT);
    pinMode(5,OUTPUT);
    pinMode(0,OUTPUT);

    digitalWrite(16,HIGH);
    digitalWrite(5,HIGH);
    digitalWrite(0,HIGH);
    
    Serial.begin(115200);
    delay(10);

    // We start by connecting to a WiFi network
    //WiFiMulti.addAP("Mang&TT", "mangtt!@#$");
    WiFiMulti.addAP("hellokitty", "xommatmang");

    Serial.println();
    Serial.println();
    Serial.print("Wait for WiFi... ");

    while(WiFiMulti.run() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    delay(500);

}


void loop() {
      
    const uint16_t port = 80;
    const char * host = "68.65.122.56"; // ip or dns vinasoft.com.vn
    
    Serial.print("connecting to ");
    Serial.println(host);

    // Use WiFiClient class to create TCP connections
    WiFiClient client;

    if (!client.connect(host, 80)) {
        Serial.println("connection failed");
        Serial.println("wait 5 sec...");
        delay(5000);
        return;
    }
    else
    {
      Serial.println("connected");
    // Make a HTTP request:
    
    client.println("GET /test.php HTTP/1.1");
    client.println("Host: www.vinatopup.com");
    
    client.println("Connection: close");
    client.println();
    //digitalWrite(16,HIGH);
   }

    // This will send the request to the server
    client.print("Send this data to server");

    //read back one line from server
    String line = client.readStringUntil('#');//\r
    int b = line.indexOf("@") + 1;
    int c = line.lastIndexOf("@");
    line = line.substring(b,c);
    client.println(line);

    Serial.println(line);
    if(line == "1"){              //Rainy
      digitalWrite(16,LOW);
      digitalWrite(5,HIGH);
      digitalWrite(0,HIGH);
    }
    if(line == "2"){              //Cloudy
      digitalWrite(16,HIGH);
      digitalWrite(5,HIGH);
      digitalWrite(0,LOW);
    }
    if(line == "3"){            //Sunny
      digitalWrite(16,HIGH);
      digitalWrite(5,LOW);
      digitalWrite(0,HIGH);
    }
    

    Serial.println("closing connection");
    client.stop();
    
    Serial.println("wait 20 sec...");
    delay(3*h);
}

