#ifndef __CINDER_MOVING_GRAPH__
#define __CINDER_MOVING_GRAPH__

#include "cinder/app/AppNative.h"

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
  
protected:
  float mMaxValue, mMinValue;
  int mHistory;
  
  bool bOpened;
  
  list<float> mDataList;
};

#endif