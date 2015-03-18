#ifndef __CINDER_MOVING_GRAPH__
#define __CINDER_MOVING_GRAPH__

#include "cinder/app/AppNative.h"
#include "cinder/Camera.h"

using namespace std;
using namespace ci;
using namespace ci::app;

class CinderMovingGraph {
public:
  CinderMovingGraph(int history=300, float maxValue=100, float minValue=0);
  virtual ~CinderMovingGraph();
  
  void draw();
  void mouseDown(MouseEvent event);
  void mouseUp(MouseEvent event);
  void mouseDrag(MouseEvent event);
  void mouseMove(MouseEvent event);
  void keyDown(KeyEvent event);
  
  void openWindow();
  void closeWindow();
  void feedIn(float newData);
  void drawCoordinate();
  
protected:
  float mMaxValue, mMinValue;
  float mBorderOff;
  int mHistory;
  CameraOrtho mOrtCam;
  
  bool bOpened;
  
  list<float> mDataList;
};

#endif