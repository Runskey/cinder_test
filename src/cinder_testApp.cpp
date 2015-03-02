#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/params/Params.h"
#include "cinder/ImageIo.h"
#include "cinder/gl/Texture.h"
#include "cinder/Rand.h"
#include "boost/thread.hpp"

#include "ciSONDevice.h"
#include "ciSONFemto.h"
#include "ciSONUE.h"

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

  void backgroundWorking();

  float mObjSize;
  Quatf mObjOrientation;
  Vec3f mLightDirection;
  ColorA mColor;

  shared_ptr<ciSONDevice> mObject;

  //shared_ptr<boost::thread> _thread;

  list<ciSONFemto> mFemtoList;
  list<ciSONUE> mUEList;

  gl::Texture mBgImage;

  params::InterfaceGl mParams;
};

void cinder_testApp::prepareSettings(Settings *settings)
{
  settings->setResizable(false);
  //settings->setWindowSize(800, 600);
  settings->setTitle("Cinder demo app");

  settings->setFrameRate(60);
}

void cinder_testApp::setup()
{
  // Setup background image
  mBgImage = gl::Texture(loadImage(loadAsset("l89_resize.jpg")));
  setWindowSize(mBgImage.getWidth(), mBgImage.getHeight());

  // Setup parameters dialog
  mParams = params::InterfaceGl("Parameters", Vec2i(200, 300));
  mParams.addParam("Cube Size", &mObjSize, "min=0.1 max=20.5 step=0.5 keyIncr=z keyDecr=Z");
  mParams.addParam("Cube Rotation", &mObjOrientation);
  mParams.addParam("Cube Color", &mColor, "");
  mParams.addSeparator();

  mParams.addParam("Light Direction", &mLightDirection, "");

  Rectf rect(200, 200, 210, 210);
  mObject = shared_ptr<ciSONDevice>(new ciSONDevice(rect));

  mFemtoList.push_back(ciSONFemto(Vec2f(200, 490)));
  mFemtoList.push_back(ciSONFemto(Vec2f(460, 200)));

  Rand::randSeed(time(0));
  mUEList.push_back(ciSONUE(Vec2f(500, 500)));
  mUEList.push_back(ciSONUE(Vec2f(500, 500)));

  //_thread = shared_ptr<boost::thread>(new boost::thread(&cinder_testApp::backgroundWorking, this));
  //_thread->join();
}

void cinder_testApp::update()
{
  //console() << getElapsedFrames() << std::endl;
  for (list<ciSONFemto>::iterator p = mFemtoList.begin(); p != mFemtoList.end(); p++)
  {
    p->update();
  }
  for (list<ciSONUE>::iterator p = mUEList.begin(); p != mUEList.end(); p++)
  {
    p->update();
  }
}

void cinder_testApp::draw()
{

  // clear out the window
  gl::clear(Color::black(), true);

  // reset color to white before tinting the background image
  gl::color(Color::white());
  mBgImage.enableAndBind();
  gl::draw(mBgImage, getWindowBounds());
  mBgImage.disable();

  //gl::setViewport(getWindowBounds());
  //gl::setMatricesWindow(getWindowSize());

  mParams.draw();
  //mObject->draw();

  for (list<ciSONFemto>::iterator p = mFemtoList.begin(); p != mFemtoList.end(); p++)
  {
    p->draw();
  }
  for (list<ciSONUE>::iterator p = mUEList.begin(); p != mUEList.end(); p++)
  {
    p->draw();
  }
}

void cinder_testApp::mouseDown(MouseEvent event)
{
  for (list<ciSONFemto>::iterator p = mFemtoList.begin(); p != mFemtoList.end(); p++)
  {
    p->mouseDown(event);
  }
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

void cinder_testApp::backgroundWorking()
{
  console() << "Hello world, I am a thread!" << endl;
}

CINDER_APP_NATIVE( cinder_testApp, RendererGl )
