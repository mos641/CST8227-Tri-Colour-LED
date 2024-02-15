//
// 2 x PBS control tri-colour LED--- Debounce PBSs
//
// Include the Bounce2 library found here :
// https://github.com/thomasfredericks/Bounce2
//
#include <Bounce2.h>

int redPin =   15;    //12;
int greenPin = 19;    //15;
int bluePin =  18;    //14;

int pbsMode0 = 6;
int pbsMode1 = 4;

Bounce debouncerMode0 = Bounce(); // Instantiate a Bounce object
Bounce debouncerMode1 = Bounce();


void setup()   {
  Serial.begin(38400);
  pinMode(pbsMode0, INPUT);
  pinMode(pbsMode1, INPUT_PULLUP);

  debouncerMode0.attach(pbsMode0,INPUT);
  debouncerMode0.interval(25);

  debouncerMode1.attach(pbsMode1,INPUT_PULLUP); // Attach the debouncer to a pin with INPUT_PULLUP mode
  debouncerMode1.interval(25); // Use a debounce interval of 25 milliseconds

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

int redIntensity = 0;
int mode = 0;

void loop()                     
{
  // set all 3 pins to the desired intensity
  analogWrite(redPin, redIntensity);
  if (mode == 0) {
    // in mode zero, fade from red to green
    analogWrite(greenPin, 255 - redIntensity);
    analogWrite(bluePin, 0);
  } else {
    // in mode one, fade from red to blue
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 255 - redIntensity);
  }

   debouncerMode0.update(); // Update the Bounce instance

   if ( debouncerMode0.fell() ) {  // Call code if button transitions from HIGH to LOW
    // use mode zero when the first button is pressed
    mode = 0;
    Serial.println("mode 0");
   }

   debouncerMode1.update();

   if ( debouncerMode1.fell() ) {
    // use mode one when the second button is pressed
    mode = 1;
    Serial.println("mode 1");
  }
  
  // remain at this color, but not for very long
  delay(10);
  
  // increase the red
  redIntensity = redIntensity + 1;
  
  // since 255 is the maximum, set it back to 0
  // when it increments beyond 255
  if (redIntensity > 255) {
    redIntensity = 0;
  }
}
