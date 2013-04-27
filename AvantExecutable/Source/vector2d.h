#ifndef _VECTOR_2D_
#define _VECTOR_2D_

namespace Resource
{

class Vector2d
{
private:
   int x,y;     
   int angle;    
   int length;  
public:
   void setX( int Xin );     
   void setY( int Yin );      
   void setLength( int Lin ); 
   void setAngle( int Ain );

   int getX();      
   int getY();      
   int getLength(); 
   int getAngle();   

public:
   void operator=(Vector2d aVector); 
   
   static void initTables();

   Vector2d() { initTables(); }                      
   Vector2d( int Xin, int Yin ) { x = Xin; y = Yin; initTables(); } 
   ~Vector2d() { }
};

};

#endif