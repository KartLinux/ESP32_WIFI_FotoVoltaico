#include <ESP32Servo.h>
#include <Wire.h>                 // Librería para I2C
#include <Adafruit_Sensor.h>      // Librería para sensores
#include <Adafruit_BME280.h>      // Librería específica para el BME280
#include <WiFi.h>          // Librería para conectarse a Wi-Fi
#include <HTTPClient.h>    // Librería para enviar solicitudes HTTP

// Configuración de Wi-Fi
const char* ssid = "XXXX";             // Cambia a tu red Wi-Fi
const char* password = "XXXX";     // Contraseña de tu red Wi-Fi
// Configuración de Supabase
const char* supabaseUrl = "https://XXXX.supabase.co/rest/v1/privietfotonv"; // URL de la tabla de datos de sensores para Supabase
// URL para la tabla casa_doma en Supabase
const String supabaseUrlCasaDoma = "https://XXXX.supabase.co/rest/v1/casa_doma";
const char* supabaseKey = "XXXX";  
//===================================================================================================================

const int Pin34LecturaDivisor = 34;  // GPIO 34 es un pin analógico en el ESP32
float voltajeLeidoDivisor = 0.0;     // Variable para almacenar el voltaje leído
float voltajeRealDivisor = 0.0;
const int Pin32SensorCorriente = 32;
float valorSensorCorriente = 0.1;
float offsetSensorCorriente = 2048;  // Para ADC de 12 bits, el offset típico es 2048
//float sensibilidad = 0.066;          // Sensibilidad del sensor (por ejemplo, 185mV/A para ACS712-5A)
float voltajeSensorCorriente = 0.0;
float corrienteSensor = 0.0;
float corrienteDivisor = 0.0;
const int pinLuz = 33; // Usa GPIO33 (ADC1_CH5) como entrada
float voltajeLeidoSensorLux = 0.0; // Variable para guardar el voltaje leído
float lux = 0.0;         // Variable para almacenar lux calculados
int valorDigital = 0; // Leer el valor digital
int lecturaLux = 0;
float temperatura = 0.0;       
float presion = 0.0;    
float humedad = 0.0;  
// Crear el objeto del sensor
#define I2C_SDA 21  // Cambiar si usas otros pines
#define I2C_SCL 22
Adafruit_BME280 bme;

// Pines y asignación de electrodomésticos
struct Electrodomestico {
  int pin;           // Pin GPIO del ESP32
  String nombreColumna; // Nombre exacto de la columna en Supabase
};

// Definir relación pines-electrodomésticos (ajusta según tu conexión física)
Electrodomestico electrodomesticos[] = {
  {4,  "lavadora"},
  {5,  "secadora"},
  {13, "refrigerador"},
  {14, "microondas"},
  {15, "television_1"},    // Asegurar que coincida con nombres en Supabase
  {16, "television_2"},
  {17, "equipo_de_sonido"},
  {18, "ducha"},
  {19, "focos"}
};

void setup() {
  Serial.begin(115200);      // Iniciar la comunicación serie
  connectToWiFi();
  analogSetPinAttenuation(Pin32SensorCorriente, ADC_11db);
  analogReadResolution(12);  // Resolución de 12 bits (0-4095)
  //Iniciar en ENTRADA para el pin para la corriente con el sensor
  pinMode(Pin32SensorCorriente, INPUT);
  pinMode(Pin34LecturaDivisor, INPUT);
  offsetSensorCorriente = analogRead(Pin32SensorCorriente);  // Leer el offset inicial
  pinMode(pinLuz, INPUT); // Configura el pin como entrada
  // Configurar pines para los LEDS como entradas con resistencia PULLDOWN
  for(int i=0; i<9; i++){
    pinMode(electrodomesticos[i].pin, INPUT_PULLDOWN); 
  }
  // Inicializar I2C
  Wire.begin(21, 22); // SDA=21, SCL=22
  if (bme.begin(0x76)) { // Dirección I2C (0x76 o 0x77 según la conexión)
    Serial.println("\nSensor BME280 detectado correctamente.\n");
    //while (1); // Detener el programa si no se detecta el sensor
  }
  
}

void loop() {
  //=======================================================================
  //Codigo para calcular la corriente,voltaje de los datos del Sensor de Corriente
  //Estos datos deberian llegar de la bateria
    valorSensorCorriente = analogRead(Pin32SensorCorriente);
    Serial.print(">>(Bateria) Offset inicial del sensor: ");
    Serial.print(offsetSensorCorriente);
    Serial.print("\tValor sensor de Corriente: ");
    Serial.print(valorSensorCorriente);
    voltajeSensorCorriente = (valorSensorCorriente * 3.3) / 4095.0;  // Convertir a voltaje
    //corriente = (voltajeCorriente - (offsetSensorCorriente / 4095.0) * 3.3) / sensibilidad;
    Serial.print("\tVoltaje medida: (V)");
    Serial.print(voltajeSensorCorriente, 5);
    corrienteSensor = ((voltajeSensorCorriente - 2.25) / 0.185) * 1000;
    Serial.print("\tCorriente medida: (mA)");
    Serial.println(corrienteSensor, 3);  // Mostrar en amperios con 3 decimales
  //==============================================================
  //Codigo para leer el voltaje del panel Solar con el DIVISOR de Voltaje
  Serial.print(">>(Panel Solar) Lectura pin Divisor de Voltaje: ");
  Serial.print(analogRead(Pin34LecturaDivisor));
  voltajeLeidoDivisor = (float(analogRead(Pin34LecturaDivisor)) * 3.3 / 4095);  // Convertir la lectura analógica en voltaje
  Serial.print("\tVoltaje del Divisor: (V)");
  Serial.print(voltajeLeidoDivisor);
  voltajeRealDivisor = voltajeLeidoDivisor * (14.3 + 3.2) / 3.2;  // Ajuste basado en el divisor de tensión
  Serial.print("\tVoltaje real con la relación: (V)");
  Serial.print(voltajeRealDivisor);
  Serial.print("\tcorriente: (A)");
  corrienteDivisor = (voltajeLeidoDivisor * (13.0 / 5.0)) / 3.2;
  Serial.println(corrienteDivisor);
  //
  // Leer y mostrar los datos
  Serial.print("Temperatura =  (grados Celsius)");
  Serial.print(bme.readTemperature()); // Lee la temperatura en °C
  Serial.println(" °C");
  temperatura = bme.readTemperature();

  Serial.print("Presión = (hectopascales)");
  Serial.print(bme.readPressure() / 100.0F); // Presión en hPa
  Serial.println(" hPa");
  presion = (bme.readPressure() / 100.0F);

  Serial.print("Humedad = ");
  Serial.print(bme.readHumidity()); // Humedad relativa en %
  Serial.println(" %");
  humedad = bme.readHumidity();

  lecturaLux = analogRead(pinLuz); // Lee el valor analógico
  voltajeLeidoSensorLux = (lecturaLux * 3.3) / 4095.0; // Convierte la lectura a voltaje
  // Ejemplo: Conversión de voltaje a lux (fórmula aproximada)
  lux = 500/voltajeLeidoSensorLux; // Ajuste para escala específica del sensor
  // Imprime los resultados
  Serial.print("Voltaje medido del Sensor de Luz: ");
  Serial.print(voltajeLeidoSensorLux, 2);
  Serial.print(" V\tLuz: ");
  Serial.print(lux);
  Serial.println(" lux (lumen/m²)");

  // Enviar datos a Supabase
    sendDataToSupabase(valorSensorCorriente, voltajeSensorCorriente, corrienteSensor, voltajeLeidoDivisor, voltajeRealDivisor,corrienteDivisor,temperatura, presion, humedad, lux);
    sendEstadosElectrodomesticos(); //envío a casa_doma
    delay(5000);
}
// ==================== FUNCIONES ==========================
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
void sendDataToSupabase(float valorSensorCorriente, float voltajeSensorCorriente, float corrienteSensor,
                        float voltajeLeidoDivisor, float voltajeRealDivisor, float corrienteDivisor,
                        float temperatura, float presion, float humedad, float lux) {
  // Verificar si estamos conectados a Wi-Fi
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http; // Crear objeto HTTPClient

    // Iniciar la conexión HTTP con la URL de Supabase
    http.begin(supabaseUrl);

    // Configurar las cabeceras necesarias para la solicitud HTTP
    http.addHeader("Content-Type", "application/json"); // Indica que el cuerpo es JSON
    http.addHeader("apikey", supabaseKey);              // Incluye la clave API

    // Construir el cuerpo JSON con todos los datos
    String payload = "{";
    payload += "\"valorsensorcorriente_analogo_bateria\": " + String(valorSensorCorriente) + ",";
    payload += "\"voltaje_sensorcorriente_bateria_v\": " + String(voltajeSensorCorriente) + ",";
    payload += "\"corriente_sensor_bateria_ma\": " + String(corrienteSensor) + ",";
    payload += "\"voltaje_leido_divisor_panel_v\": " + String(voltajeLeidoDivisor) + ",";
    payload += "\"voltaje_real_panel_v\": " + String(voltajeRealDivisor) + ",";
    payload += "\"corriente_divisor_panel_a\": " + String(corrienteDivisor) + ",";
    payload += "\"temperatura_celcius\": " + String(temperatura) + ",";
    payload += "\"presion_hectopascales\": " + String(presion) + ",";
    payload += "\"humedad_percent\": " + String(humedad) + ",";
    payload += "\"lux_lumen_m2\": " + String(lux);
    payload += "}";

    // Imprimir el JSON para depuración
    Serial.println("Enviando los siguientes datos a Supabase:");
    Serial.println(payload);

    // Enviar la solicitud POST con el cuerpo JSON
    int httpResponseCode = http.POST(payload);

    // Verificar el código de respuesta del servidor
    // Verificar el código de respuesta del servidor
  if (httpResponseCode > 0) {
    Serial.print("Código de respuesta: ");
    Serial.println(httpResponseCode);
  } else {
    Serial.print("Error al enviar los datos. Código de error: ");
    Serial.println(httpResponseCode);
    // Imprimir detalles del error
    String errorString = http.errorToString(httpResponseCode);
    Serial.println("Descripción del error: " + errorString);
  }
    // Finalizar la conexión HTTP
    http.end();

  } else {
    // Si no estamos conectados a Wi-Fi, mostrar un mensaje de error
    Serial.println("Error: No conectado a Wi-Fi.");
  }
}
// =============== FUNCIÓN PARA LEER Y ENVIAR ESTADOS ================
void sendEstadosElectrodomesticos() {
  if(WiFi.status() != WL_CONNECTED){
    Serial.println("Error WiFi en electrodomésticos");
    return;
  }

  HTTPClient http;
  http.begin(supabaseUrlCasaDoma);
  http.addHeader("Content-Type", "application/json");
  http.addHeader("apikey", supabaseKey);

  // Construir JSON con estados
  String payload = "{";
  for(int i=0; i<9; i++){
    int estado = digitalRead(electrodomesticos[i].pin);
    payload += "\"" + electrodomesticos[i].nombreColumna + "\":" + String(estado);
    if(i < 8) payload += ",";
  }
  payload += "}";

  Serial.print("Enviando estados a DOMA: ");
  Serial.println(payload);

  int codigoRespuesta = http.POST(payload);
  
  if(codigoRespuesta > 0){
    Serial.print("Éxito casa_doma: ");
    Serial.println(codigoRespuesta);
  } else {
    Serial.print("Fallo casa_doma: ");
    Serial.println(http.errorToString(codigoRespuesta));
  }
  
  http.end();
}
