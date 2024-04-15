#include "Monitor.h"

Monitor::Monitor(){};
Monitor::~Monitor(){};

void Monitor::drawMessage(SH1107Wire& display, String M1, String M2) {
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 5, M1);
  display.setFont(ArialMT_Plain_24);
  display.drawString(0, 25, M2);
  display.display();
}