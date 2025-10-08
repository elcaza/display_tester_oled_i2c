# Display Tester for ESP32
Un código para probar el funcionamiento correcto del ESP32 y una pantalla OLED I2C.

Este proyecto considera:
+ ¿La pantalla no está conectada?
    + Quizá no la has conectado
    + Quizá te equivocaste de pines
    + Quizá los puertos de tu ESP32 están quemados, no sirven (Prueba con puertos alternativos)
    + Quizá tu pantalla no funciona
+ ¿Hay problemas con la inicialización de la librería?
+ La dirección I2C del OLED se encuentra en 0x3C o 0x3D
    + Verifica que tu código real use la dirección correcta

# Componentes
+ OLED I2C (SSD1306)
+ ESP32 

# Instrucciones de uso
1. Ajusta los siguientes valores en el código `display_tester.ino`
    + `#define SDA_PIN 32`
        + // SDA va al GPIO 21 || también puede ser 32
    + `#define SCL_PIN 33`
        + // SCL va al GPIO 22 || también puede ser 33

2. Opcional: Ancho y alto de la pantalla
    + `#define SCREEN_WIDTH 128`
    + `#define SCREEN_HEIGHT 64`
3. Compila y carga el código en el ESP32

# Conexiones
<img src="https://raw.githubusercontent.com/elcaza/display_tester_oled_i2c/refs/heads/main/images/display_connections.png">

# Teoría

## ¿Qué es el protocolo I2C?
Es un protocolo de comunicación serial síncrono de corto alcance diseñado para permitir que múltiples dispositivos maestros (como el ESP32) y múltiples dispositivos esclavos (como la pantalla OLED) se comuniquen entre sí usando solo dos cables.

## ¿Cuántos puertos I2C tiene el ESP32?
Dos controladores I2C dedicados, sin embargo el ESP32 te permite asignar estos dos puertos a casi cualquier par de pines GPIO disponibles.

Convenciones comunes utilizadas por el firmware de Arduino:

I2C Port 0:
+ Pines convencionales (por defecto): `GPIO 21 (SDA)` y `GPIO 22 (SCL)`	
+ Pines alternativos (por ejemplo): `GPIO 32 (SDA)` y `GPIO 33 (SCL)`

I2C Port 1:
+ No tiene pines por defecto
+ Puedes usar cualquier otro par de pines libres, como GPIO 18/19 o 25/26, etcétera.

## ¿Cómo funciona el programa?
1. Verifica si la pantalla está conectada para evitar el falso positivo de display.begin()
1. Verifica si el hardware inicia correctamente
1. En caso de algún error, el programa lo informa lo informa a través del serial port