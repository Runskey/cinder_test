#ifndef __CINDER_MOVING_GRAPH__
#define __CINDER_MOVING_GRAPH__

#include "cinder/app/AppNative.h"

using namespace std;
using namespace ci;
using namespace ci::app;

class CinderMovingGraph {
public:
  CinderMovingGraph(shared_ptr<AppNative> app, int history=100, float maxValue=100, float minValue=0);
  virtual ~CinderMovingGraph();
  
  void draw();
  void close();
  void mouseDown(MouseEvent event);
  void mouseUp(MouseEvent event);
  void mouseDrag(MouseEvent event);
  void mouseMove(MouseEvent event);
  void keyDown(KeyEvent event);
  
  void openWindow();
  app::WindowRef getWindow();
  void feedIn(float newData);
  
protected:
  float mMaxValue, mMinValue;
  int mHistory;
  
  shared_ptr<AppNative> mApp;
  app::WindowRef mGraphWindow;
  bool bOpened;
  
  list<float> mDataList;
};

#endif