/*********
  Adaptado do projeto de Rui Santos
  Complete project details at http://randomnerdtutorials.com
*********/

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// credenciais da rede wifi
const char* ssid = "Bematech_SPO";
const char* password = "bematech";

ESP8266WebServer server(80);

String webPage;

int gpio4_pin = 4;

void setup(void){
  webPage =
      "<h1>Ola ESP8266</h1>"
      "<p>"
      "    LED - IO4"
      "    <a href=\"io4_ligar\">"
      "        <button>Ligar</button>"
      "    </a>&nbsp;"
      "    <a href=\"io4_desligar\">"
      "        <button>Desligar</button></a>"
      "</p>";;

  Serial.begin(115200);
  Serial.println("");

  // preparando GPIOs
  pinMode(gpio4_pin, OUTPUT);
  digitalWrite(gpio4_pin, LOW);

  delay(1000);

  WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(200);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", []() {
    server.send(200, "text/html", webPage);
  });

  server.on("/io4_ligar", []() {
    server.send(200, "text/html", webPage);
    digitalWrite(gpio4_pin, HIGH);
  });

  server.on("/io4_desligar", []() {
    server.send(200, "text/html", webPage);
    digitalWrite(gpio4_pin, LOW);
  });

  server.begin();
  Serial.println("servidor HTTP iniciado!");
}

void loop(void){
  server.handleClient();
}
