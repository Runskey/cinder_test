#pragma once

#include "cinder/app/App.h"
#include "cinder/Perlin.h"


using namespace std;
using namespace ci;
using namespace ci::app;

class ciSONUE {
public:
  ciSONUE(Vec2f location);
  virtual ~ciSONUE();

  virtual void draw();

  virtual void update();

protected:
  Vec2f mLoc, mDir;
  float mRadius, mVel;
  
  Perlin mPerlin;
};