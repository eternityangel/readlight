#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include <Adafruit_NeoPixel.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

#define NEOPIXEL_COUNT		1
#define NEOPIXEL_CTL_PIN	2
#define POTENTIOMETER_PIN	A3
#define PUSH_BUTTON_PIN		5

#define TIME_SPAN_MS		100

enum button_state {
	BUTTON_UP = LOW,
	BUTTON_DOWN = HIGH
};

enum rgb_colors {
	RED = 0xff0000,
	GREEN = 0x00ff00,
	BLUE = 0x0000ff
};

struct rgb_t {
	uint32_t red;
	uint32_t green;
	uint32_t blue;
};

uint32_t	potentiometer_val = 0;
unsigned long	prev_time = 0;
enum rgb_colors chosen_color = RED;
struct rgb_t	cur_color;

Adafruit_NeoPixel pixel = Adafruit_NeoPixel(
				NEOPIXEL_COUNT,
				NEOPIXEL_CTL_PIN,
				NEO_GRB + NEO_KHZ800);

void
setup(void)
{
	//Serial.begin(9600);
	cur_color.red = 128;

	pixel.begin();
	pixel.show(); // Lights off
}

void
loop(void)
{
	int anal4read = analogRead(POTENTIOMETER_PIN);
	int buttonstate = digitalRead(PUSH_BUTTON_PIN);

	potentiometer_val = map(anal4read, 0, 1023, 0, 255);

	if (buttonstate == BUTTON_DOWN
	    && (millis() - prev_time) >= TIME_SPAN_MS) {

		int blaa = millis() - prev_time;

		switch (chosen_color) {
		case RED:
			chosen_color = GREEN;
			break;
		case GREEN:
			chosen_color = BLUE;
			break;
		case BLUE:
			chosen_color = RED;
			break;
		}
		prev_time = millis();
	} else {
		switch (chosen_color) {
		case RED:
			cur_color.red = potentiometer_val;
			break;
		case GREEN:
			cur_color.green = potentiometer_val;
			break;
		case BLUE:
			cur_color.blue = potentiometer_val;
			break;
		}
	}

	pixel.setPixelColor(0, cur_color.red, cur_color.green, cur_color.blue);
	pixel.show();
}

#ifdef __cplusplus
}
#endif
