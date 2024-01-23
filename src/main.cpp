#include <M5AtomS3.h>
#include "USB.h"
#include "USBHIDMouse.h"

#define GPIO_BUTTON 41
USBHIDMouse Mouse;

struct TimerConf {
  int interval_ms;
  CRGB color;

  TimerConf(int interval_ms, CRGB color) :
    interval_ms(interval_ms),
    color(color)
  {
  }
};

std::vector<TimerConf> modes = {
  TimerConf(-1, CRGB::Black),
  TimerConf(10000, CRGB::Blue),
  TimerConf(30000, CRGB::Green),
  TimerConf(60000, CRGB::Red)
};

volatile bool g_irq0 = false;
void setIRQ0() {
  g_irq0 = true;
}

void setLED(CRGB color, const int rest_ms = 0){
  const int flash_ms = 5000;

  if(0 < rest_ms && rest_ms <= flash_ms){
    color = (rest_ms / 500) % 2 == 0 ? color : CRGB::Black;
  }

  AtomS3.dis.drawpix(color);
  AtomS3.dis.show();
  return;
}

void setup() {
  AtomS3.begin(true);
  Mouse.begin();
  USB.begin();
  
  pinMode(GPIO_BUTTON, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(GPIO_BUTTON), setIRQ0, FALLING);
  AtomS3.dis.drawpix(CRGB::Black);
  AtomS3.dis.show();
}

void loop() {
  static int mode_idx = 0;
  static int prev_ms = 0;

  if(g_irq0){
    g_irq0 = false;
    mode_idx = (mode_idx + 1) % modes.size();
    prev_ms = millis();
  }

  const auto mode = modes[mode_idx];

  const int curr_ms = millis();
  const int spent_ms = curr_ms >= prev_ms ? curr_ms - prev_ms : INT_MAX - prev_ms + curr_ms;
  const int rest_ms = mode.interval_ms - spent_ms;

  setLED(mode.color, rest_ms);

  if(mode.interval_ms <= 0){
    return;
  }

  if(rest_ms <= 0){
    Mouse.click();
    prev_ms = curr_ms;
    return;
  }
}
