#include "vector2d.h"
#include "local.h"

using namespace Resource;

void Vector2d::setLength( int Lin )
{
   length = Lin;
   x = costable[angle]*length;
   y = sintable[angle]*length;
}

void Vector2d::setAngle( int Ain )
{
   angle = Ain;
   x = costable[angle]*length;
   y = sintable[angle]*length;
}

int Vector2d::getAngle()
{
	return angle;
}

int Vector2d::getLength()
{
	return length;
}

int Vector2d::getX()
{
	return x;
}

int Vector2d::getY()
{
	return y;
}

void Vector2d::setX(int xd)
{
	x = xd;
}

void Vector2d::setY(int yd)
{
	y = yd;
}

void Vector2d::operator =(Vector2d aVector)
{
	x = aVector.getX();
	y = aVector.getY();
}

void Vector2d::initTables()
{
   if(!tableInit)
   {
		float temp;
		for( int i = 0; i<360; i++ )
		{
			 temp = ((float)(360-i)/180);

			 temp *= PI;

			 costable[i] = (float)cos( temp );
			 sintable[i] = (float)sin( temp );     
		}
		tableInit = true;
   }
}
