#ifndef HSMANAGER_H
#define HSMANAGER_H

#include <Arduino.h>

class HsManager {

  int hsPin_;
  
  HsManager(int hsPin);
  static HsManager* hsFWA;
  static HsManager* hsGWA;
  
 public:
  bool connected = false;

  int firstHSRead;
  int lastHSRead;
  
  static HsManager* instanceHsFWA();
  static HsManager* instanceHsGWA();

  int hsRead();
  
};


#endif
