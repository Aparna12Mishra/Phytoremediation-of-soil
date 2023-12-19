/*Simple first build of plant soil moisture indicator. 
Red transtions from brightest to off as it approaches the dry threshold indicating low moisture. 
Green transitions from off to brightest at the center between the wet and dry threshold and then back to off at the wet threshold to indicate the ideal zone. 
Blue transitions to on starting from the wet threshold indicating very wet conditions*/

#include <Adafruit_NeoPixel.h>

#define PIN 2	 // pin Neopixel is attached to
#define SENSOR A0		//input pin for Potentiometer
#define NUMPIXELS 1 // number of neopixels in strip

/*THese values adjust what is considered wet or dry*/
#define dryThreshold 50 //below this value, begin alerting dry, turn red;
#define wetThreshold 200 //above this value, begin alerting wet,turn blue;
#define thresholdCenter (dryThreshold + wetThreshold)/2 //Brightest Green point
#define crossFade 20 //how much blue and red should fade in to green

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int delayval = 100; // timing delay in milliseconds

int redColor = 0;
int greenColor = 0;
int blueColor = 0;

//Sensor reading and the value converted from 1024 to 255 for output
int sensorValue  = 0;
int transitionValue = 0;


void setup() {
  // Initialize the NeoPixel library.
  pixels.begin();
  pinMode(SENSOR,INPUT);
}

void loop() {
	sensorValue = analogRead(SENSOR);
	transitionValue = map(sensorValue,0,1023,0,255);
	setColor();
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(0,redColor,greenColor,blueColor);
	
    // This sends the updated pixel color to the hardware.
    pixels.show();

    // Delay for a period of time (in milliseconds).
    delay(delayval); 
}

void setColor(){

  
    //red value greater towards higher resistance/drier
redColor = ((transitionValue <= dryThreshold + crossFade) && (transitionValue >= 0 ))? map(transitionValue,0,dryThreshold + crossFade,255,0) : 0;
  //blue value greater towards lower resistance/wetter
blueColor = (transitionValue >= wetThreshold - crossFade && transitionValue <= 255)? map(transitionValue,wetThreshold - crossFade,255,0,255):0; 
  
  //green value towrds middle resistance
  if(transitionValue >= dryThreshold && transitionValue <= thresholdCenter)
  {
  greenColor = map(transitionValue,dryThreshold,thresholdCenter,0,255);
  }
  else if(transitionValue > thresholdCenter && transitionValue < wetThreshold)
  {
    greenColor = map(transitionValue,dryThreshold,thresholdCenter,255,0);
  }
  else{
    greenColor = 0;
  }
                   
}



