#include "ciSONFemto.h"

ciSONFemto::ciSONFemto(Vec2f location)
{
  mRadius = 10;
  mLoc = location;
  mPressed = false;
}

ciSONFemto::~ciSONFemto()
{

}

void ciSONFemto::draw()
{
  if (mPressed)
  {
    gl::color(Color(0, 1, 0));
  }
  else
  {
    float currColor = sin(4 * getElapsedSeconds())*0.5f + 0.5f;
    gl::color(Color(0, currColor, 0));
  }
  gl::drawSolidCircle(mLoc, mRadius);
}

void ciSONFemto::update()
{

}

void ciSONFemto::mouseDown(ci::app::MouseEvent& event)
{
  Vec2f dir = event.getPos() - mLoc;
  if (dir.length() < mRadius)
  {
    mPressed = !mPressed;
  }
  if (mPressed)
  {
    mRadius = 20;
  }
  else
  {
    mRadius = 10;
  }
}
