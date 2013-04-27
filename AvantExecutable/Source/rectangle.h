#ifndef _RECTANGLE_
#define _RECTANGLE_

namespace Avant
{
	class Rectangle
	{
	public:
		Rectangle();
		Rectangle(int x, int y, int w, int h);
		~Rectangle();

		bool contains(int x, int y);

		void shape(int x,int y,int w,int h);
		
		void resize(int w, int h);


	private:

		int x;
		int y;
		int width;
		int height;

	};
};

#endif