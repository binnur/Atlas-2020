/*******************************************************************************
 * Robot Animations -- Functions to execute the bling "actions"
 ******************************************************************************/

/*
 * Solid colors - remember to add 'delay()' to listen for new commands
 */
void solid(rgbColor c)
{
  setAllPixels(c.color);
  showPixels();
  delay(10);
}

/**
 * Set strip to full brightness and display the solid color
 */
void solidWithFullBrightness(rgbColor c)
{
  setFullBrightness();
  solid(c);
}

/**
 * Set strip to full brightness and display the solid color
 */
void solidWithBrightness(rgbColor c, uint8_t brightness)
{
  pixels.setBrightness(brightness);
  solid(c);
}

/**
 * Display solid color with 'off' in between to give illusion of 'blink'
 */
void solidWithBlink(rgbColor c, uint8_t wait)
{
  solid(c);
  blinkOffWithDelay(wait);
}

/*
 * Turns off the pixels creating a 'blink' animation
 */
void blinkOffWithDelay(uint8_t wait)
{
  // Wait prior to turning off pixels
  delay(wait);
  setAllPixelsOff();
  delay(wait);
}

 void strobe(rgbColor c, uint8_t numFlashes, int8_t flashDelay, int8_t strobePause)
 {
  for (int j = 0; j < numFlashes; j++) 
  {
    setAllPixels(c);
    showPixels();
    
    delay(flashDelay);
    
    setAllPixels(rgbColor_OFF);
    showPixels();
    delay(flashDelay);
  }
 
 delay(strobePause);
}

void fillPixelByPixel(rgbColor c, uint8_t wait)
 {
  // start w/ pixel 0, set color, show color, wait and do it again
  for(uint16_t i=0; i<pixels.numPixels(); i++) 
  {
    // pass the color component of rgbColor 
    setPixel(i, c.color);
    showPixels();

    delay(wait);
  }
}


/** From the middle of the top, start illuminating pixels towards the ends
 * After length pixels have been added to each side, turn old pixels off
 * Pixels continue to scroll off of ends, then the scheme reverses
 */ 
void crawler(uint16_t timeInterval, uint32_t color, uint8_t length)
{
 
  uint8_t tempLength;
  uint8_t headUp;
  uint8_t headDown;
  uint8_t tailUp;
  uint8_t tailDown;

  while (1)
  {
    // Turn off the strip
    setAllPixelsOff();

    tempLength = length;
    headUp = (NUM_LEDS/2);
    headDown = headUp - 1;
    for (uint8_t i=0; i<length; i++)
    {
      setPixel(headUp++, color);
      setPixel(headDown--, color);
      showPixels();
      delay(timeInterval);
    }
    
    tailUp = (NUM_LEDS/2);
    tailDown = tailUp - 1;
    while (headUp < NUM_LEDS)
    {
      setPixel(headUp++, color);
      setPixel(headDown--, color);
      setPixel(tailUp++, OFF);
      setPixel(tailDown--, OFF);
      showPixels();
      delay(timeInterval);
    }
    
    while (tailUp < NUM_LEDS)
    {
      setPixel(tailUp++, OFF);
      setPixel(tailDown--, OFF);
      showPixels();
      delay(timeInterval);
    }

    // Reverse!
    tempLength = length;
    headUp = NUM_LEDS - 1;
    headDown = 0;
    for (uint8_t i=0; i<length; i++)
    {
      setPixel(headUp--, color);
      setPixel(headDown++, color);
      showPixels();
      delay(timeInterval);
    }
    
    tailUp = NUM_LEDS - 1;
    tailDown = 0;
    while (headUp >= (NUM_LEDS/2))
    {
      setPixel(headUp--, color);
      setPixel(headDown++, color);
      setPixel(tailUp--, OFF);
      setPixel(tailDown++, OFF);
      showPixels();
      delay(timeInterval);
    }
    
    while (tailUp >= (NUM_LEDS/2))
    {
      setPixel(tailUp--, OFF);
      setPixel(tailDown++, OFF);
      showPixels();
      delay(timeInterval);
    }
  }
}

// Flash of light for a short period of time, then off (runs once only)
void flash(unsigned long timeInterval, uint32_t color, uint8_t brightness)
{
  pixels.setBrightness(brightness);
  setAllPixels(color);
  delay(timeInterval);
  setAllPixelsOff();
}
