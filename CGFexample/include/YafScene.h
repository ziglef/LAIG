#ifndef YAFSCENE_H
#define YAFSCENE_H

#include "CGF\CGFscene.h"
#include "CGF\CGFcamera.h"
#include "CGF\CGFapplication.h"
#include "SceneGraph.h"

class YafScene : public CGFscene{
	public:
		YafScene(SceneGraph *sg):CGFscene(){
			this->sg = sg;
		};
		void init();
		void display();
		void processGraph( string rootId );
		vector<CGFcamera*> *getSceneCameras();
		void activateCamera( int i );
		~YafScene();

	protected:
		SceneGraph *sg;

	private:
		void initGraph( string rootId );

	friend class SceneGraph;
	friend class GraphNode;
};

#endif