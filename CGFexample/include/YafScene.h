#ifndef YAFSCENE_H
#define YAFSCENE_H

#include "CGF\CGFscene.h"

class YafScene : public CGFscene{
	public:
		void init();
		void display();
		~YafScene();

};

#endif