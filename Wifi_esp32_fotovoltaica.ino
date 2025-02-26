#include <WiFi.h>          // Librería para conectarse a Wi-Fi
#include <HTTPClient.h>    // Librería para enviar solicitudes HTTP
//=============================================================================================================0¡
// Configuración de Wi-Fi
const char* ssid = "XXXX";             // Cambia a tu red Wi-Fi
const char* password = "XXXX";     // Contraseña de tu red Wi-Fi

// Configuración de Supabase
const char* supabaseUrl = "https://XXXX.supabase.co/rest/v1/TablaPruebas"; // Cambia a tu URL de Supabase
const char* supabaseKey = "XXXX";  
//===================================================================================================================
// Variables globales para almacenar los valores de los servos y la hora
int servo1Angle = 0; // Ángulo del Servo 1
int servo2Angle = 0; // Ángulo del Servo 2
String currentTime = "00:00:00"; // Hora actual
//================================================
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("\nHola Viejo");
  // Llama a esta función al inicio de setup()
  connectToWiFi();
}

void loop() {
  // put your main code here, to run repeatedly:
  // Actualiza valores globales de servo1, servo2 y tiempo...
  sendDataToSupabase(servo1Angle, servo2Angle, currentTime);
  delay(3000);
}

// Función para conectar a Wi-Fi
void connectToWiFi() {
  Serial.print("Conectando a Wi-Fi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nConectado a Wi-Fi.");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

// Función para enviar datos a Supabase
void sendDataToSupabase(int servo1Angle, int servo2Angle, String currentTime) {
  if (WiFi.status() == WL_CONNECTED) { // Verifica conexión Wi-Fi
    HTTPClient http;
    http.begin(supabaseUrl);           // URL de la API
    http.addHeader("Content-Type", "application/json"); // Cabecera para JSON
    http.addHeader("apikey", supabaseKey);              // Clave de API

    // Construir el cuerpo del JSON
    String payload = "{";
    payload += "\"servo1_angle\":" + String(servo1Angle) + ",";
    payload += "\"servo2_angle\":" + String(servo2Angle) + ",";
    payload += "\"time\":\"" + currentTime + "\"";
    payload += "}";
    Serial.println(payload);
    // Enviar solicitud POST
    int httpResponseCode = http.POST(payload);

    // Verificar respuesta
    if (httpResponseCode > 0) {
      Serial.print("Datos enviados, código de respuesta: ");
      Serial.println(httpResponseCode);
    } else {
      Serial.print("Error al enviar datos: ");
      Serial.println(http.errorToString(httpResponseCode));
    }

    http.end(); // Finalizar conexión
  } else {
    Serial.println("No conectado a Wi-Fi.");
  }
}
