#include "bspt.h"

using namespace ci;
using namespace ci::app;
using namespace std;

smallCellPT::smallCellPT(const Rectf& rect)
{
  this->rect = rect;
  pressedColor = Color(1, 0, 0);
  idleColor = Color(0.7, 0.7, 0.7);
  overColor = Color(1, 1, 1);
  strokeColor = Color(0, 0, 0);
  mPressed = false;
  mOver = false;
}

smallCellPT::~smallCellPT()
{

}

void smallCellPT::draw()
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

void smallCellPT::pressed()
{
  console() << "pressed" << endl;
}

void smallCellPT::pressedOutside()
{
  console() << "pressed outside" << endl;
}
void smallCellPT::released()
{
  console() << "released" << endl;
}
void smallCellPT::releasedOutside()
{
  console() << "released outside" << endl;
}
void smallCellPT::rolledOver()
{
  console() << "rolled over" << endl;
}
void smallCellPT::rolledOut()
{
  console() << "rolled out" << endl;
}
void smallCellPT::dragged()
{
  console() << "dragged" << endl;
}
void smallCellPT::mouseDown(MouseEvent& event)
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
void smallCellPT::mouseUp(MouseEvent& event)
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
void smallCellPT::mouseDrag(MouseEvent& event)
{
  if (mPressed && rect.contains(event.getPos()))
  {
    mPressed = true;
    mOver = false;
    dragged();
  }
}
void smallCellPT::mouseMove(MouseEvent& event)
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
