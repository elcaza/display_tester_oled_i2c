// Código para probar la pantalla OLED I2C (SSD1306)
// ESP32 - 38 pines

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ****************************************************
// VARIABLES DE PANTALLA (I2C)
// ****************************************************

// SDA va al GPIO 21 || también puede ser 32
// SCL va al GPIO 22 || también puede ser 33
#define SDA_PIN 32
#define SCL_PIN 33
// Tamaño de pantalla
#define SCREEN_WIDTH 128    // Ancho de la pantalla OLED, en píxeles
#define SCREEN_HEIGHT 64   // Alto de la pantalla OLED, en píxeles
// Dirección I2C del OLED. Los valores comunes son 0x3C o 0x3D.
#define OLED_ADDR 0x3C

const long SERIAL_BAUD = 9600;

// Usamos -1 para el pin de RESET, ya que la mayoría de los módulos I2C no lo usan
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

bool checkI2cAddress(uint8_t address) {
	// Intenta contactar la dirección I2C.
	Wire.beginTransmission(address);
	// endTransmission() devuelve 0 si el dispositivo responde con un ACK.
	// Devuelve un valor diferente de 0 si falla (NACK).
	return Wire.endTransmission() == 0;
}

void display_message(){
	delay(50);
	display.clearDisplay();

	display.setTextSize(1);
	display.setTextColor(WHITE);

	display.setCursor(0, 0);
	display.println("Test OLED ESP32 OK!");

	display.setTextSize(2);
	display.setCursor(0, 15);
	display.println("TEST I2C");

	display.setCursor(0, 50);
	display.println("uwur");

	display.display();
}

void setup() {
	Serial.begin(SERIAL_BAUD);
	delay(200);

	// Inicializa la comunicación I2C en los pines definidos
	Wire.begin(SDA_PIN, SCL_PIN);
	// Reducir la velocidad del BUS a 100 kHz
	Wire.setClock(100000);

	// bool screen_found = false;
	uint8_t final_addr = 0x00;

	// 1. Verifica si la pantalla está conectada (evita el falso positivo de display.begin())
	if (checkI2cAddress(OLED_ADDR)) {
		final_addr = OLED_ADDR;
	} else if (checkI2cAddress(0x3D)) {
		final_addr = 0x3D;
	}

	// 2. Detiene el programa
	if (final_addr == 0x00) {
		Serial.println(F("ERROR: La pantalla no fue encontrada en 0x3C ni 0x3D. Posibles errores, cableado o modulo. Tus pines del ESP32 también podrían estar quemados."));
		for(;;);
	}

	// 3. Inicialización. Solo si el hardware respondió
	if (!display.begin(SSD1306_SWITCHCAPVCC, final_addr)) {
		Serial.println(F("ERROR: Inicializacion de la librería falló en la direccion encontrada."));
		for(;;);
	} else {
		Serial.print(F("INFO: Pantalla inicializada correctamente en 0x"));
		Serial.println(final_addr, HEX);

		if (final_addr == 0x3D) {
			Serial.println(F("INFO: Se usó la direccion 0x3D. Ajusta tu codigo principal"));
		}
	}

	display_message();
}

void loop() {

}