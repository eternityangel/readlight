#ifdef __cplusplus
extern "C" {
#endif

#define BUTTON_PIN	2

#define RED_PIN		6
#define GREEN_PIN	5

enum LIGHT_STATES {
	LIGHT_FULL_RED,
	LIGHT_HALF_RG,
	LIGHT_FULL_GREEN
};

enum BUTTON_STATE {
	BUTTON_UP = LOW,
	BUTTON_DOWN = HIGH
};

static int		lightstate = LIGHT_FULL_RED;
static int		buttonstate = BUTTON_UP;
static unsigned int	btnpresstart = 0;

void
setup(void)
{
	pinMode(RED_PIN, OUTPUT);
	pinMode(GREEN_PIN, OUTPUT);
	pinMode(BUTTON_PIN, INPUT);
}

void
light_states_transition(void)
{
	switch (lightstate) {
	case LIGHT_FULL_RED:
		analogWrite(RED_PIN, 0xff);
		analogWrite(GREEN_PIN, 0x0);
		lightstate = LIGHT_HALF_RG;
		break;
	case LIGHT_HALF_RG:
		analogWrite(RED_PIN, 0x80);
		analogWrite(GREEN_PIN, 0x80);
		lightstate = LIGHT_FULL_GREEN;
		break;
	case LIGHT_FULL_GREEN:
		analogWrite(RED_PIN, 0x0);
		analogWrite(GREEN_PIN, 0xff);
		lightstate = LIGHT_FULL_RED;
		break;
	}
}

void
loop(void)
{
	buttonstate = digitalRead(BUTTON_PIN);
	switch (buttonstate) {
	case BUTTON_UP:
		//digitalWrite(RED_PIN, LOW);
		//digitalWrite(GREEN_PIN, LOW);
		btnpresstart = 0;
		break;
	case BUTTON_DOWN:
		btnpresstart = 1;
		light_states_transition();
		delay(1000);
		break;
	}
}

#ifdef __cplusplus
}
#endif

