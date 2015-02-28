#include "bspt.h"

using namespace ci;
using namespace ci::app;
using namespace std;

ciSONDevice::ciSONDevice(const Rectf& rect)
{
  this->rect = rect;
  pressedColor = Color(1, 0, 0);
  idleColor = Color(0.7, 0.7, 0.7);
  overColor = Color(1, 1, 1);
  strokeColor = Color(0, 0, 0);
  mPressed = false;
  mOver = false;
}

ciSONDevice::~ciSONDevice()
{

}

void ciSONDevice::draw()
{
  if (mPressed)
  {
    gl::color(pressedColor);
  }
  else if (mOver)
  {
    gl::color(overColor);
  }
  else
  {
    gl::color(idleColor);
  }

  gl::drawSolidRect(rect);
  gl::color(strokeColor);
  gl::drawStrokedRect(rect);
}

void ciSONDevice::pressed()
{
  console() << "pressed" << endl;
}

void ciSONDevice::pressedOutside()
{
  console() << "pressed outside" << endl;
}
void ciSONDevice::released()
{
  console() << "released" << endl;
}
void ciSONDevice::releasedOutside()
{
  console() << "released outside" << endl;
}
void ciSONDevice::rolledOver()
{
  console() << "rolled over" << endl;
}
void ciSONDevice::rolledOut()
{
  console() << "rolled out" << endl;
}
void ciSONDevice::dragged()
{
  console() << "dragged" << endl;
}
void ciSONDevice::mouseDown(MouseEvent& event)
{
  if (rect.contains(event.getPos()))
  {
    mPressed = true;
    mOver = false;
    pressed();
  }
  else
  {
    pressedOutside();
  }
}
void ciSONDevice::mouseUp(MouseEvent& event)
{
  if (rect.contains(event.getPos()))
  {
    if (mPressed)
    {
      mPressed = false;
      mOver = true;
      released();
    }
  }
  else
  {
    mPressed = false;
    mOver = false;
    releasedOutside();
  }
}
void ciSONDevice::mouseDrag(MouseEvent& event)
{
  if (mPressed && rect.contains(event.getPos()))
  {
    mPressed = true;
    mOver = false;
    dragged();
  }
}
void ciSONDevice::mouseMove(MouseEvent& event)
{
  if (rect.contains(event.getPos()))
  {
    if (mOver == false)
    {
      mPressed = false;
      mOver = true;
      rolledOver();
    }
  }
  else
  {
    if (mOver)
    {
      mPressed = false;
      mOver = false;
      rolledOut();
    }
  }
}
