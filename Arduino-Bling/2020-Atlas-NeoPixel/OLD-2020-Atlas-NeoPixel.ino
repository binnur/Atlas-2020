
// Fill the strip with a single color
void fillStrip(uint32_t c)
{
   for (unsigned i=0; i<pixels.numPixels(); i++)
   {
      pixels.setPixelColor(i, c);
   }
   pixels.show();
}


/*******************************************************************************
 * Functions to execute the bling "actions"
 ******************************************************************************/


// Blink a single color on and off at the given time interval
void blink(unsigned long timeInterval, uint32_t color, uint8_t brightness)
{
  pixels.setBrightness(brightness);
  while (1)
  {
    fillStrip(color);
    delay(timeInterval);
    setAllPixelsOff();
    delay(timeInterval);
  }
}

// Fade a color in and out
void fade(unsigned long timeInterval, uint32_t color, uint8_t maxBrightness)
{
  bool brightening = true;
  int brightness = 0;

  // Set the strip to the desired color to begin with
  fillStrip(color);

  while (1)
  {
    pixels.setBrightness(brightness);
    pixels.show();
    if (brightening)
    {
      if (brightness >= maxBrightness)  // At maximum brightness?
      {
        brightening = false;    // Time to switch to dimming
      }
      else
      {
        brightness++;           // Increase the brightness for next time
      }
    }
    else // dimming
    {
      if (brightness <= 0)      // At minimum brightness?
      {
        brightening = true;     // Time to switch to brightening
      }
      else
      {
        brightness--;           // Reduce the brightness for next time
      }
    }
    delay(timeInterval);
  }
}

// Fade between two alternating colors
void spartronics_fade(unsigned long timeInterval, uint32_t color1, uint32_t color2, uint8_t maxBrightness)
{
  bool brightening = true;
  int brightness = 0;
  bool color1_is_current = true;;

  // Set the strip to the desired color to begin with
  fillStrip(color1);

  while (1)
  {
    pixels.setBrightness(brightness);
    pixels.show();
    if (brightening)
    {
      if (brightness >= maxBrightness)  // At maximum brightness?
      {
        brightening = false;    // Time to switch to dimming
      }
      else
      {
        brightness++;           // Increase the brightness for next time
      }
    }
    else // dimming
    {
      if (brightness <= 0)      // At minimum brightness?
      {
        // Switch to the alternate color
        if (color1_is_current)
        {
          fillStrip(color2);
          color1_is_current = false;
        }
        else
        {
          fillStrip(color1);
          color1_is_current = true;
        }

        brightening = true;     // Time to switch to brightening
      }
      else
      {
        brightness--;           // Reduce the brightness for next time
      }
    }
    delay(timeInterval);
  }
}

