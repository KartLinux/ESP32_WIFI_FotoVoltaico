<!DOCTYPE html>
<html lang="es">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">

</head>
<body style="background-color: #121212; color: #e0e0e0; font-family: Arial, sans-serif; line-height: 1.6;">

  <!-- Título principal -->
  <h1 style="font-size: 36px; font-weight: bold; color: #00ff00; text-align: center; text-transform: uppercase; letter-spacing: 2px;">
    🌞 PROYECTO ESP32: MONITOREO DE ENERGÍA SOLAR Y ALMACENAMIENTO EN LA NUBE ⚡
  </h1>

  <!-- Descripción del proyecto -->
  <div style="background-color: #282c34; color: #abb2bf; padding: 20px; border-radius: 10px; margin: 20px 0;">
    <p style="font-size: 18px; text-align: center;">
      Este proyecto utiliza un <strong>ESP32</strong> para monitorear la generación de electricidad mediante un panel solar, el estado de carga de una batería y otros sensores ambientales. Los datos se envían a una base de datos en la nube (<a href="https://supabase.com/" style="color: #00ff00;">Supabase</a>) para su análisis y visualización en tiempo real.
    </p>
  </div>

  <!-- Imágenes en una tabla -->
  <div style="text-align: center; margin: 20px 0;">
    <table style="margin: 0 auto; border-collapse: collapse;">
      <tr>
        <td><img src="https://github.com/user-attachments/assets/b745448b-dcaa-4256-81ae-a12884e3f188" width="300" style="border: 2px solid #ccc; border-radius: 10px;" /></td>
        <td><img src="https://github.com/user-attachments/assets/373fc36d-bf7c-4839-aa34-a2634c50b857" width="300" style="border: 2px solid #ccc; border-radius: 10px;" /></td>
        <td><img src="https://github.com/user-attachments/assets/0421ec15-fbd3-4a2f-9cdc-9281cd9553a5" width="300" style="border: 2px solid #ccc; border-radius: 10px;" /></td>
        <td><img src="https://github.com/user-attachments/assets/c4c5db78-82b9-42a5-917f-f0d0fe197b2c" width="300" style="border: 2px solid #ccc; border-radius: 10px;" /></td>
      </tr>
      <tr>
        <td style="text-align: center; color: #00ff00; font-size: 14px;">Programacion en Arduino</td>
        <td style="text-align: center; color: #00ff00; font-size: 14px;">Placa ESP32</td>
        <td style="text-align: center; color: #00ff00; font-size: 14px;">WIFI (Wireless)</td>
        <td style="text-align: center; color: #00ff00; font-size: 14px;">Base de datos (Nube)</td>
      </tr>
    </table>
  </div>

  <!-- Sección de características -->
  <h2 style="font-size: 24px; font-weight: bold; color: #ff4500; text-align: center; margin-top: 30px;">
    🛠️ CARACTERÍSTICAS PRINCIPALES
  </h2>
  <div style="background-color: #282c34; color: #abb2bf; padding: 20px; border-radius: 10px; margin: 20px 0;">
    <ul style="list-style-type: none; padding: 0;">
      <li><span style="color: #00ff00;">🔋 Monitoreo de batería:</span> Voltaje, corriente y estado de carga.</li>
      <li><span style="color: #00ff00;">🌞 Panel solar:</span> Voltaje y corriente generada.</li>
      <li><span style="color: #00ff00;">🌡️ Sensores ambientales:</span> Temperatura, presión y humedad.</li>
      <li><span style="color: #00ff00;">☁️ Almacenamiento en la nube:</span> Datos enviados a Supabase para análisis.</li>
      <li><span style="color: #00ff00;">⚡ Control de electrodomésticos:</span> Estado de dispositivos conectados.</li>
    </ul>
  </div>

  <!-- Configuración inicial -->
  <h2 style="font-size: 24px; font-weight: bold; color: #ff4500; text-align: center; margin-top: 30px;">
    🔧 CONFIGURACIÓN INICIAL
  </h2>
  <div style="background-color: #282c34; color: #abb2bf; padding: 20px; border-radius: 10px; margin: 20px 0;">
    <p style="font-size: 16px;">
      Antes de usar este proyecto, asegúrate de configurar las siguientes variables con tus propias credenciales:
    </p>
    <pre style="background-color: #21252b; color: #d4d4d4; padding: 10px; border-radius: 5px; font-family: 'Courier New', monospace;">
const char* ssid = "XXXX";             // Cambia a tu red Wi-Fi (El nombre de tu red wirless)
const char* password = "XXXX";         // Contraseña de tu red Wi-Fi
const char* supabaseUrl = "https://XXXX.supabase.co/rest/v1/privietfotonv"; //Url de la tabla a donde se van a guardar los datos
const char* supabaseKey = "XXXX";     // Clave de acceso a Supabase (La base de datos)
    </pre>
    <p style="font-size: 16px;">
      Reemplaza los valores <code>XXXX</code> con tus datos personales.
    </p>
  </div>

  <!-- Librerías utilizadas -->
  <h2 style="font-size: 24px; font-weight: bold; color: #ff4500; text-align: center; margin-top: 30px;">
    📚 LIBRERÍAS UTILIZADAS
  </h2>
  <div style="background-color: #282c34; color: #abb2bf; padding: 20px; border-radius: 10px; margin: 20px 0;">
    <ul style="list-style-type: none; padding: 0;">
      <li><span style="color: #00ff00;">WiFi.h:</span> Para conexión inalámbrica.</li>
      <li><span style="color: #00ff00;">HTTPClient.h:</span> Para enviar solicitudes HTTP a Supabase.</li>
      <li><span style="color: #00ff00;">Adafruit_BME280.h:</span> Para sensores ambientales (temperatura, presión, humedad).</li>
      <li><span style="color: #00ff00;">Wire.h:</span> Para comunicación I2C.</li>
    </ul>
  </div>
  <!-- Imágenes en una tabla -->
  <div style="text-align: center; margin: 20px 0;">
    <table style="margin: 0 auto; border-collapse: collapse;">
      <tr>
        <td><img src="https://github.com/user-attachments/assets/d63cd13b-9b9d-46bb-9cdc-72a50afa2a6d" width="300" style="border: 2px solid #ccc; border-radius: 10px;" /></td>
        <td><img src="https://github.com/user-attachments/assets/39332114-50ff-4254-b8af-8d1af0433b12" width="300" style="border: 2px solid #ccc; border-radius: 10px;" /></td>
        <td><img src="https://github.com/user-attachments/assets/89675999-7504-435c-a387-70a6ef2af9de" width="300" style="border: 2px solid #ccc; border-radius: 10px;" /></td>
      </tr>
      <tr>
        <td style="text-align: center; color: #00ff00; font-size: 14px;">Panel Solar</td>
        <td style="text-align: center; color: #00ff00; font-size: 14px;">Batería</td>
        <td style="text-align: center; color: #00ff00; font-size: 14px;">Sensores Ambientales</td>
      </tr>
    </table>
  </div>
  <!-- Contribuciones -->
  <h2 style="font-size: 24px; font-weight: bold; color: #ff4500; text-align: center; margin-top: 30px;">
    🤝 CONTRIBUCIONES
  </h2>
  <div style="background-color: #282c34; color: #abb2bf; padding: 20px; border-radius: 10px; margin: 20px 0;">
    <p style="font-size: 16px;">
      ¡Las contribuciones son bienvenidas! Si encuentras errores o tienes ideas para mejorar este proyecto, sigue estos pasos:
    </p>
    <ol style="list-style-type: decimal; padding-left: 20px;">
      <li>Haz un fork del repositorio.</li>
      <li>Crea una nueva rama (<code>git checkout -b feature/nueva-funcionalidad</code>).</li>
      <li>Haz commit de tus cambios (<code>git commit -m "Agrega nueva funcionalidad"</code>).</li>
      <li>Sube tus cambios (<code>git push origin feature/nueva-funcionalidad</code>).</li>
      <li>Abre un pull request.</li>
    </ol>
  </div>

  <!-- Licencia -->
  <h2 style="font-size: 24px; font-weight: bold; color: #ff4500; text-align: center; margin-top: 30px;">
    📜 LICENCIA
  </h2>
  <div style="background-color: #282c34; color: #abb2bf; padding: 20px; border-radius: 10px; margin: 20px 0;">
    <p style="font-size: 16px; text-align: center;">
      Este proyecto está bajo la licencia <a href="LICENSE" style="color: #00ff00;">MIT</a>. ¡Usa y modifica el código como quieras!
    </p>
  </div>

</body>
</html>
