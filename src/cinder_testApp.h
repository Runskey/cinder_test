#pragma once

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/params/Params.h"
#include "cinder/Camera.h"
#include "cinder/MayaCamUI.h"

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
  void drawDefault();

  void drawGrid(float size = 100.f, float step = 10.0f);

  void mouseDown(MouseEvent event);
  void mouseUp(MouseEvent event);
  void mouseDrag(MouseEvent event);
  void mouseMove(MouseEvent event);

  void mouseDownW1(MouseEvent event);

  void keyDown(KeyEvent event);

  void createScrollingGraph();
  void drawScrollingGraph();
  void destroyScrollingGraph();

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

protected:

  // 3D camera controller
  MayaCamUI mMayaCam;
  CameraPersp mCamera;

  float mDegree;

  app::WindowRef mGraph;
  bool bGraph;

};