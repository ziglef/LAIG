#ifndef _TEXT_OBJECT_H_
#define _TEXT_OBJECT_H_

class TextObject
{
	public:
		void renderBitmapString(float x, float y, void *font,const char *string);
		void resetPerspectiveProjection();
		void setOrthographicProjection();
		void draw( char * text, int x, int y );
};

#endif
