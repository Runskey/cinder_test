#include "cinder/ImageIo.h"
#include "cinder/Rand.h"
//#include "boost/thread.hpp"

#include "cinder_testApp.h"

void cinder_testApp::prepareSettings(Settings *settings)
{
  settings->setResizable(false);
  settings->setWindowSize(800, 600);
  settings->setTitle("Cinder demo app");

  settings->setFrameRate(30);
}

void cinder_testApp::setup()
{
  // Setup background image
  //mBgImage = gl::Texture(loadImage(loadAsset("l89_resize.jpg")));
  //setWindowSize(mBgImage.getWidth(), mBgImage.getHeight());

  // Setup parameters dialog
  //mParams = params::InterfaceGl("Parameters", Vec2i(200, 300));
  //mParams.addParam("Cube Size", &mObjSize, "min=0.1 max=20.5 step=0.5 keyIncr=z keyDecr=Z");
  //mParams.addParam("Cube Rotation", &mObjOrientation);
  //mParams.addParam("Cube Color", &mColor, "");
  //mParams.addSeparator();

  //mParams.addParam("Light Direction", &mLightDirection, "");

  mDegree = 0.0f;

  // Setup 3D perspective camera
  CameraPersp camera = mMayaCam.getCamera();
  camera.setPerspective(75.0f, getWindowAspectRatio(), 1.0f, 1000.0f);
  camera.setWorldUp(Vec3f::zAxis());

  mMayaCam.setCurrentCam(camera);

  Rectf rect(200, 200, 210, 210);
  mObject = shared_ptr<ciSONDevice>(new ciSONDevice(rect));

  mFemtoList.push_back(ciSONFemto(Vec2f(200, 490)));
  mFemtoList.push_back(ciSONFemto(Vec2f(460, 200)));

  Rand::randSeed((unsigned long)time(0));
  mUEList.push_back(ciSONUE(Vec2f(500, 500)));
  mUEList.push_back(ciSONUE(Vec2f(500, 500)));

  bGraph = false;

  // Setup multiple-window
  mDefaultWin = getWindow();
  mDefaultWin->connectDraw(&cinder_testApp::drawDefault, this);
  mDefaultWin->connectMouseDown(&cinder_testApp::mouseDownDefault, this);
  mDefaultWin->connectMouseUp(&cinder_testApp::mouseUpDefault, this);
  mDefaultWin->connectMouseDrag(&cinder_testApp::mouseDragDefault, this);
  mDefaultWin->connectMouseMove(&cinder_testApp::mouseMoveDefault, this);
  mDefaultWin->connectKeyDown(&cinder_testApp::keyDownDefault, this);

}


void cinder_testApp::drawDefault()
{
  mDegree += 0.05f;
  // Update the 3D camera
  gl::setMatrices(mMayaCam.getCamera());

  // clear out the window
  gl::clear(Color::black(), true);

  gl::enableDepthRead();
  gl::enableDepthWrite();

  Vec3f currPos = Vec3f::zAxis();
  gl::rotate(mDegree*currPos);

  // reset color to white before tinting the background image
  //gl::color(Color::white());
  //mBgImage.enableAndBind();
  //gl::draw(mBgImage, getWindowBounds());
  //mBgImage.disable();


  //gl::setViewport(getWindowBounds());
  //gl::setMatricesWindow(getWindowSize());

  drawGrid();

  gl::enableWireframe();
  //gl::drawColorCube(Vec3f::zero(), Vec3f(4.0f, 4.0f, 4.0f));
  gl::drawSphere(Vec3f::zero(), 10.0f);
  gl::disableWireframe();


  //mParams.draw();
  //mObject->draw();

  for (list<ciSONFemto>::iterator p = mFemtoList.begin(); p != mFemtoList.end(); p++)
  {
    p->draw();
  }
  for (list<ciSONUE>::iterator p = mUEList.begin(); p != mUEList.end(); p++)
  {
    p->draw();
  }

  gl::disableDepthRead();
  gl::disableDepthWrite();
}

void cinder_testApp::update()
{
  console() << getElapsedFrames() << std::endl;
  
  for (list<ciSONFemto>::iterator p = mFemtoList.begin(); p != mFemtoList.end(); p++)
  {
    p->update();
  }
  
  for (list<ciSONUE>::iterator p = mUEList.begin(); p != mUEList.end(); p++)
  {
    p->update();
  }
}


void cinder_testApp::drawGrid(float size, float step)
{
  gl::color(Colorf(0.2f, 0.2f, 0.2f));
  for (float i = -size; i <= size; i += step) 
  {
    gl::drawLine(Vec3f(i, -size, 0.0f), Vec3f(i, size, 0.0f));
    gl::drawLine(Vec3f(-size, i, 0.0f), Vec3f(size, i, 0.0f));
  }
  gl::color(Colorf(1.0f, 0.0f, 0.0f));
  gl::drawVector(Vec3f::zero(), Vec3f(0.0f, 0.0f, 20.0f), 2, 0.5);
  gl::color(Colorf(0.0f, 1.0f, 0.0f));
  gl::drawVector(Vec3f::zero(), Vec3f(0.0f, 20.0f, 0.0f), 2, 0.5);
  gl::color(Colorf(0.0f, 0.0f, 1.0f));
  gl::drawVector(Vec3f::zero(), Vec3f(20.0f, 0.0f, 0.0f), 2, 0.5);
}

void cinder_testApp::mouseDownDefault(MouseEvent event)
{
  // Update 3D camera
  mMayaCam.mouseDown(event.getPos());

  for (list<ciSONFemto>::iterator p = mFemtoList.begin(); p != mFemtoList.end(); p++)
  {
    p->mouseDown(event);
  }
}

void cinder_testApp::mouseUpDefault(MouseEvent event)
{
  mObject->mouseUp(event);
}

void cinder_testApp::mouseDragDefault(MouseEvent event)
{
  // Update 3D camera
  mMayaCam.mouseDrag(event.getPos(), event.isLeftDown(), event.isMiddleDown(), event.isRightDown());

  mObject->mouseDrag(event);
}

void cinder_testApp::mouseMoveDefault(MouseEvent event)
{
  mObject->mouseMove(event);
}

void cinder_testApp::keyDownDefault(KeyEvent event)
{
  switch (event.getCode()) {
  case KeyEvent::KEY_ESCAPE:
    quit();
    break;
  case KeyEvent::KEY_d:
    //CameraPersp camera = mMayaCam.getCamera();
    //Vec3f eye = camera.getEyePoint();
    //Vec3f center = camera.getCenterOfInterestPoint();
    //Vec3f up = camera.getWorldUp();
    break;
  case KeyEvent::KEY_w:
    createScrollingGraph();
    break;
  }

}

void cinder_testApp::createScrollingGraph()
{
  
  if (!bGraph)
  {
    mGraph = shared_ptr<CinderMovingGraph>(new CinderMovingGraph(static_cast<shared_ptr<AppNative>>(this)));
    mGraph->openWindow();
    app::WindowRef graphWin = mGraph->getWindow();
    graphWin->connectDraw(&cinder_testApp::drawScrollingGraph, this);
    //(mGraph->getWindow())->connectDraw(&CinderMovingGraph::draw, mGraph);
    
    //mGraph->setTitle("Throughput Performance window");

    //mGraph->connectDraw(&cinder_testApp::drawScrollingGraph, this);
    //mGraph->connectClose(&cinder_testApp::destroyScrollingGraph, this);
    
    bGraph = true;
  }  
  
}

void cinder_testApp::drawScrollingGraph()
{
  if (bGraph)
  {
    mGraph->draw();
  }
}

void cinder_testApp::destroyScrollingGraph()
{
  bGraph = false;
}


void cinder_testApp::backgroundWorking()
{
  console() << "Hello world, I am a thread!" << endl;
}

CINDER_APP_NATIVE( cinder_testApp, RendererGl )
