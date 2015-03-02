#pragma once

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/params/Params.h"

#include "ciSONDevice.h"
#include "ciSONFemto.h"
#include "ciSONUE.h"


using namespace ci;
using namespace ci::app;
using namespace std;

class cinder_testApp : public AppNative {
public:
  void setup();
  void prepareSettings(Settings *settings);
  void update();
  void draw();

  void mouseDown(MouseEvent event);
  void mouseUp(MouseEvent event);
  void mouseDrag(MouseEvent event);
  void mouseMove(MouseEvent event);

  void backgroundWorking();

  float mObjSize;
  Quatf mObjOrientation;
  Vec3f mLightDirection;
  ColorA mColor;

  shared_ptr<ciSONDevice> mObject;

  //shared_ptr<boost::thread> _thread;

  list<ciSONFemto> mFemtoList;
  list<ciSONUE> mUEList;

  gl::Texture mBgImage;

  params::InterfaceGl mParams;
};