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
#include "CinderMovingGraph.h"


using namespace ci;
using namespace ci::app;
using namespace std;

class cinder_testApp : public AppNative {
public:
  void prepareSettings(Settings *settings);
  void setup();
  void update();
  
  void drawDefault();
  void closeDefault();
  void mouseDownDefault(MouseEvent event);
  void mouseUpDefault(MouseEvent event);
  void mouseDragDefault(MouseEvent event);
  void mouseMoveDefault(MouseEvent event);
  void keyDownDefault(KeyEvent event);

  void drawGrid(float size = 100.f, float step = 10.0f);

  void openMovingGraph();
  void closeMovingGraph();
  void drawMovingGraph();

  void backgroundWorking();

  ColorA mColor;

  shared_ptr<ciSONDevice> mObject;


  list<ciSONFemto> mFemtoList;
  list<ciSONUE> mUEList;

  gl::Texture mBgImage;


protected:

  // 3D camera controller
  MayaCamUI mMayaCam;

  
  app::WindowRef mDefaultWin;

  // Graph
  shared_ptr<CinderMovingGraph> mGraph;
  app::WindowRef mGraphWindow;

  float mDegree;
  params::InterfaceGl mParams;

  bool mGraphOpened;

  bool mPressed;

};
