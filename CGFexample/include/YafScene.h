#ifndef YAFSCENE_H
#define YAFSCENE_H

#include "CGF\CGFscene.h"
#include "SceneGraph.h"

class YafScene : public CGFscene{
	public:
		YafScene(SceneGraph *sg):CGFscene(){
			this->sg = sg;
		};
		void init();
		void display();
		~YafScene();

	protected:
		SceneGraph *sg;

};

#endif