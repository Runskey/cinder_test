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
  mBorderOff = 15.0f;
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

  mOrtCam.setOrtho(0, getWindowWidth(), 0, getWindowHeight(), 1, -1);
  gl::setMatrices(mOrtCam);
  //gl::setMatricesWindow(getWindowSize());

  drawCoordinate();

  float boardOffset = 10.0f;
  list<float>::iterator it;
  gl::disableAlphaBlending();
  gl::translate(Vec3f(boardOffset, boardOffset, 0.0f));

  gl::enableAdditiveBlending();
  gl::color(ColorA8u(153, 153, 0, 128));
  glBegin(GL_TRIANGLE_STRIP);
  glVertex2f(Vec2f(0.0f, 0.0f));
  it = mDataList.begin();
  for (int i = 0; i < mHistory; i++) {
    glVertex2f(Vec2f(i, 0.0f));
    glVertex2f(Vec2f(i, *(it++)));
  }
  glVertex2f(Vec2f(mHistory - 1, 0.0f));
  glEnd();
  gl::disableAlphaBlending();
  
  gl::color(Color8u(153, 153, 0));
  glBegin(GL_LINE_STRIP);
  it = mDataList.begin();
  for (int i = 0; i < mHistory; i++) {
    glVertex2f(Vec2f(i, *(it++)));
  }
  glEnd();
  
  gl::translate(-1 * Vec3f(boardOffset, boardOffset, 0.0f));  
  
  gl::popModelView();
}

void CinderMovingGraph::mouseDown(MouseEvent event) {}
void CinderMovingGraph::mouseUp(MouseEvent event) {}
void CinderMovingGraph::mouseDrag(MouseEvent event) {}
void CinderMovingGraph::mouseMove(MouseEvent event) {}
void CinderMovingGraph::keyDown(KeyEvent event) {}

void CinderMovingGraph::drawCoordinate()
{
  gl::translate(Vec3f(mBorderOff, mBorderOff, 0.0f));

  /*
  // Draw grid
  gl::color(Color8u(160, 160, 160));
  for (int x = 0; x < getWindowWidth() - 2 * mBorderOff; x += 20) {
    gl::drawLine(Vec3f(x, 0, 0), Vec3f(x, getWindowHeight() - 2 * mBorderOff, 0));
  }
  for (int y = 0; y < getWindowHeight() - 2 * mBorderOff; y += 20) {
    gl::drawLine(Vec3f(0, y, 0), Vec3f(getWindowWidth() - 2 * mBorderOff, y, 0));
  }
  */
  // Draw border
  gl::color(Color8u(224, 224, 224));
  gl::drawLine(Vec3f(0, getWindowHeight() - 2 * mBorderOff, 0.0f), Vec3f(getWindowWidth() - 2 * mBorderOff, getWindowHeight() - 2 * mBorderOff, 0.0f));
  gl::drawLine(Vec3f(getWindowWidth() - 2 * mBorderOff, 0, 0.0f), Vec3f(getWindowWidth() - 2 * mBorderOff, getWindowHeight() - 2 * mBorderOff, 0.0f));
  // Draw X- and Y- axis
  gl::color(Color8u(255, 51, 51));
  gl::drawVector(Vec3f(0, 0, 0.0f), Vec3f(0, getWindowHeight() - 2 * mBorderOff, 0.0f), 10.0f, 4.0f);
  gl::drawVector(Vec3f(0, 0, 0.0f), Vec3f(getWindowWidth() - 2 * mBorderOff, 0, 0.0f), 10.0f, 4.0f);

  gl::translate(-1 * Vec3f(mBorderOff, mBorderOff, 0.0f));

}