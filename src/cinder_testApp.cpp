#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/params/Params.h"

#include "bspt.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class cinder_testApp : public AppNative {
  public:
	void setup();
  void prepareSettings(Settings *settings);
  void update();
	void draw();

  void mouseDown(MouseEvent event);
  void mouseUp(MouseEvent event);
  void mouseDrag(MouseEvent event);
  void mouseMove(MouseEvent event);

  float mObjSize;
  Quatf mObjOrientation;
  Vec3f mLightDirection;
  ColorA mColor;

  shared_ptr<smallCellPT> mObject;


  params::InterfaceGl mParams;
};

void cinder_testApp::prepareSettings(Settings *settings)
{
  settings->setResizable(false);
  settings->setWindowSize(800, 600);
  settings->setTitle("Cinder demo app");

  settings->setFrameRate(30);
}

void cinder_testApp::setup()
{
  mParams = params::InterfaceGl("Parameters", Vec2i(200, 400));
  mParams.addParam("Cube Size", &mObjSize, "min=0.1 max=20.5 step=0.5 keyIncr=z keyDecr=Z");
  mParams.addParam("Cube Rotation", &mObjOrientation);
  mParams.addParam("Cube Color", &mColor, "");
  mParams.addSeparator();

  mParams.addParam("Light Direction", &mLightDirection, "");

  Rectf rect(10, 10, 200, 200);
  mObject = shared_ptr<smallCellPT>(new smallCellPT(rect));

}

void cinder_testApp::update()
{
  console() << getElapsedFrames() << std::endl;
}

void cinder_testApp::draw()
{
  gl::enableAlphaBlending();
	// clear out the window with black
	gl::clear( Color( 0, 0, 0.5 ) ); 

  gl::setViewport(getWindowBounds());
  gl::setMatricesWindow(getWindowSize());

//  gl::color(Color(1, 0, 0));
//  gl::drawSolidCircle(Vec2f(100, 100), 20, 6);

  mParams.draw();

  mObject->draw();
}

void cinder_testApp::mouseDown(MouseEvent event)
{
  mObject->mouseDown(event);
}
void cinder_testApp::mouseUp(MouseEvent event)
{
  mObject->mouseUp(event);
}
void cinder_testApp::mouseDrag(MouseEvent event)
{
  mObject->mouseDrag(event);
}
void cinder_testApp::mouseMove(MouseEvent event)
{
  mObject->mouseMove(event);
}



CINDER_APP_NATIVE( cinder_testApp, RendererGl )
