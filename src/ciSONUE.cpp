#include "ciSONUE.h"
#include "cinder/Rand.h"

ciSONUE::ciSONUE(Vec2f location)
{
  mRadius = 5;
  mLoc = location;
  mDir = Rand::randVec2f();
  mVel = Rand::randFloat(1.0f);

  mPerlin = Perlin();
}

ciSONUE::~ciSONUE()
{
  
}

void ciSONUE::draw()
{
  gl::color(Color(1, 0, 1));
  gl::drawSolidCircle(mLoc, mRadius);
}

void ciSONUE::update()
{
  //Vec2f diroffset = Rand::randVec2f()*Rand::randFloat(1.0f, 3.0f);
  //float decay = Rand::randFloat(0.95f, 0.99f);
  //mLoc += (mDir+diroffset)*(mVel+decay);

  float nX = mLoc.x * 0.005f;
  float nY = mLoc.y * 0.005f;
  float nZ = app::getElapsedSeconds() * 0.1f;
  float noise = mPerlin.fBm(Vec3f(nX, nY, nZ));

  float angle = noise * 15.0f;
  Vec2f dirOffset = Vec2f(cos(angle), sin(angle));
  mLoc += (mDir+dirOffset)*0.1;

}