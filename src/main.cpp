#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// credenciais da rede wifi
const char* ssid = "Bematech_SPO";
const char* password = "bematech";

ESP8266WebServer server(80);

String webPage;

int gpio4_pin = 4;

void setup(void) {
  webPage =
      "<html>"
      "<head>"
      "  <title>Hello ESP12 - ESP8266</title>"
      "  <link rel=\"stylesheet\" href=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css\" integrity=\"sha384-BVYiiSIFeK1dGmJRAkycuHAHRg32OmUcww7on3RYdg4Va+PmSTsz/K68vbdEjh4u\" crossorigin=\"anonymous\">"
      "  <script src=\"https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js\" integrity=\"sha384-Tc5IQib027qvyjSMfHjOMaLkfuWVxZxUPnCJA7l2mCWNIpG9mGCD8wGNIcPD7Txa\" crossorigin=\"anonymous\"></script>"
      "</head>"
      "<body>"
      "<div class=\"jumbotron\">"
      "  <div class=\"container\">"
      "    <h1>Hello ESP8266!</h1>"
      "    <img src=\"https://s30.postimg.org/6w1onoa1t/esp12e.png\">"
      "    <p>Pressione os bot&otilde;es para ligar e desligar o LED</p>"
      "    <p>"
      "      <a class=\"btn btn-danger btn-lg\" href=\"io4_ligar\" role=\"button\">Ligar &raquo;</a>"
      "      <a class=\"btn btn-primary btn-lg\" href=\"io4_desligar\" role=\"button\">Desligar &raquo;</a>"
      "    </p>"
      "  </div>"
      "</div>"
      "<div class=\"container\">"
      "</div>"
      "</body>"
      "</html>";

  Serial.begin(115200);

  // preparando GPIOs
  pinMode(gpio4_pin, OUTPUT);
  digitalWrite(gpio4_pin, LOW);

  delay(1000);

  WiFi.begin(ssid, password);

  Serial.println("\nConectando com wifi...");
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
