#include <dht11.h>
#include <Ethernet.h>
#define DHT11PIN 4
#define PIN_MQ2 A1
#define LED 13

float value;

dht11 DHT11;
EthernetClient client;
int port="443";
String method= "GET";
char host="192.168.220.109";
String path="/testarduino.php";
String temp="?temperature=";
String hum="&humidite=";
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
void  setup()
{
  Serial.begin(9600);
  Ethernet.begin(mac,host);
  pinMode(LED,OUTPUT);
  pinMode(PIN_MQ2,INPUT);
 
}

void loop()
{
  
  Serial.println();

  value=analogRead(PIN_MQ2);  
  int chk = DHT11.read(DHT11PIN);

  Serial.print("Humidity (%): ");

  Serial.println((float)DHT11.humidity, 2);

  Serial.print("Temperature(C): ");
  Serial.println((float)DHT11.temperature, 2);

  Serial.print("Concentration de Gaz (%): ");
  Serial.print((float)value);
  
    if(value>200){digitalWrite(LED,HIGH);}
    else{digitalWrite(LED,LOW);}
  myadmin();
  delay(2000);

}
void myadmin(){
    if(client.connect(host,port)){
      Serial.println("Connected to DB");
    
    Serial.print("GET /testarduino.php?humidity=");
    client.print("GET /testarduino.php?humidity=");     //YOUR URL
    Serial.println(DHT11.humidity);
    client.print(DHT11.humidity);
    client.print("&temperature=");
    Serial.println("&temperature=");
    client.print(DHT11.temperature);
    Serial.println(DHT11.temperature);
    client.print("&particule=");
    Serial.println("&particule=");
    client.print(value);
    Serial.println(value);
    client.print(" HTTP/1.1");
    }else{
      Serial.println();
      Serial.println("nope");
    }

}
