#include "CinderMovingGraph.h"

#include "cinder/gl/gl.h"

CinderMovingGraph::CinderMovingGraph(int history, float maxValue, float minValue):
  mHistory(history), mMaxValue(maxValue), mMinValue(minValue)
{
  mDataList.clear();
  
  for (int i=0; i<mHistory; i++)
  {
    mDataList.push_back(i);
  }
  
  bOpened = false;
}

CinderMovingGraph::~CinderMovingGraph()
{
}

void CinderMovingGraph::feedIn(float newData)
{
  mDataList.pop_front();
  mDataList.push_back(newData);
}

void CinderMovingGraph::openWindow()
{
  if (!bOpened) bOpened = true;
}

void CinderMovingGraph::closeWindow()
{
  if (bOpened) bOpened = false;
}

void CinderMovingGraph::draw()
{
  if (!bOpened) return;

  gl::clear(Color::black(), true);
  gl::pushModelView();
  gl::enableAlphaBlending();

  //gl::enableWireframe();
  gl::setMatricesWindow(getWindowSize());
//  gl::color(Colorf(1.0f, 1.0f, 0.0f));
  
  glBegin(GL_TRIANGLE_STRIP);
  
  list<float>::iterator it = mDataList.begin();
  for (int i=0; i<mHistory; i++, it++)
  {
    gl::color(((float)i/mHistory) * Color::white());
    gl::vertex(Vec2f(i, 0));
    gl::vertex(Vec2f(i, *it));
  }
  glEnd();
  
  //gl::drawSolidCircle(Vec2f(20.0f, 20.0f), 10);
  //gl::disableWireframe();
  
  gl::disableAlphaBlending();
  gl::popModelView();
}

void CinderMovingGraph::mouseDown(MouseEvent event) {}
void CinderMovingGraph::mouseUp(MouseEvent event) {}
void CinderMovingGraph::mouseDrag(MouseEvent event) {}
void CinderMovingGraph::mouseMove(MouseEvent event) {}
void CinderMovingGraph::keyDown(KeyEvent event) {}