#pragma once

#include "cinder\Rect.h"
#include "cinder\Color.h"
#include "cinder\app\MouseEvent.h"
#include "cinder\gl\gl.h"
#include "cinder\app\App.h"

using namespace std;
using namespace ci;
using namespace ci::app;

class ciSONDevice {
public:
  ciSONDevice(const ci::Rectf& rect);
  virtual ~ciSONDevice();
  virtual void draw();
  virtual void pressed();
  virtual void pressedOutside();
  virtual void released();
  virtual void releasedOutside();
  virtual void rolledOver();
  virtual void rolledOut();
  virtual void dragged();
  void mouseDown(ci::app::MouseEvent& event);
  void mouseUp(ci::app::MouseEvent& event);
  void mouseDrag(ci::app::MouseEvent& event);
  void mouseMove(ci::app::MouseEvent& event);

  //void backgroundWorking();

  ci::Rectf rect;
  ci::Color pressedColor, idleColor, overColor, strokeColor;

protected:
  bool mPressed, mOver;
};
