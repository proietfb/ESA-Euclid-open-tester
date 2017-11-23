#include "HsManager.h"

HsManager* HsManager::hsFWA = nullptr;
HsManager* HsManager::hsGWA = nullptr;

HsManager::HsManager(int hsPin): hsPin_(hsPin){

  pinMode(hsPin_, INPUT);
}

HsManager* HsManager::instanceHsFWA(){
  if(!hsFWA){
    hsFWA = new HsManager(A4);
  }
  return hsFWA;
}


HsManager* HsManager::instanceHsGWA(){
  if(!hsGWA){
    hsGWA = new HsManager(A9);
  }
  return hsGWA;
}


int HsManager::hsRead(){
  return analogRead(hsPin_);
}
