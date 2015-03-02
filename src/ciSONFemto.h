#pragma once

#include "cinder/app/App.h"

using namespace std;
using namespace ci;
using namespace ci::app;

class ciSONFemto {
public:
  ciSONFemto(Vec2f location);
  virtual ~ciSONFemto();

  virtual void draw();
  virtual void update();
  //virtual void pressed();
  //virtual void pressedOutside();
  //virtual void released();
  //virtual void releasedOutside();
  //virtual void rolledOver();
  //virtual void rolledOut();
  //virtual void dragged();

  void mouseDown(ci::app::MouseEvent& event);
  
//  void mouseDrag(ci::app::MouseEvent& event);
//  void mouseMove(ci::app::MouseEvent& event);

  ci::Color pressedColor, idleColor, overColor, strokeColor;

protected:
  Vec2f mLoc;
  float mRadius;
  Color mColor;
  bool mPressed, mOver;

};
