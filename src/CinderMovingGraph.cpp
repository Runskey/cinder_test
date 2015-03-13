#include "CinderMovingGraph.h"

#include "cinder/gl/gl.h"

CinderMovingGraph::CinderMovingGraph(shared_ptr<AppNative> app, int history, float maxValue, float minValue):
  mApp(app), mHistory(history), mMaxValue(maxValue), mMinValue(minValue)
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
  if (bOpened) return;
  
  Window::Format format;
  format.setSize(300, 200);
  format.setResizable(false);
  mGraphWindow = mApp->createWindow(format);
}

app::WindowRef CinderMovingGraph::getWindow()
{
  return mGraphWindow;
}

void CinderMovingGraph::draw()
{
  gl::clear(Color::black(), true);
  gl::pushModelView();
  gl::enableAlphaBlending();

  gl::enableWireframe();
  gl::setMatricesWindow(getWindowSize());
  gl::color(Colorf(1.0f, 1.0f, 0.0f));
  
  glBegin(GL_POLYGON);
  
  gl::vertex(Vec2f(0,0));
  
  list<float>::iterator it = mDataList.begin();
  for (int i=0; i<mHistory; i++, it++)
  {
    gl::vertex(Vec2f(i, *it));
  }
  gl::vertex(Vec2f(mHistory,0));
  glEnd();
  
  //gl::drawSolidCircle(Vec2f(20.0f, 20.0f), 10);
  gl::disableWireframe();
  
  gl::disableAlphaBlending();
  gl::popModelView();
}

void CinderMovingGraph::close()
{
  mGraphWindow.reset();
  bOpened = false;
}

void CinderMovingGraph::mouseDown(MouseEvent event) {}
void CinderMovingGraph::mouseUp(MouseEvent event) {}
void CinderMovingGraph::mouseDrag(MouseEvent event) {}
void CinderMovingGraph::mouseMove(MouseEvent event) {}
void CinderMovingGraph::keyDown(KeyEvent event) {}