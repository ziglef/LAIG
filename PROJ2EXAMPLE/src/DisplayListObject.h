#ifndef _DISPLAYLIST_OBJECT_H_
#define _DISPLAYLIST_OBJECT_H_


class DisplayListObject
{
	public:
		DisplayListObject(unsigned int nTriangles=1000, int useDL=true);
		~DisplayListObject();
		void draw();
		int usingDL;

	private:
		void generateGeometry();
		unsigned int dl;
		unsigned int nTri;
		
};

#endif
