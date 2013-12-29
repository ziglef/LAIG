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
			this->movieIndex = 0;
			this->timeElapsed = 0;
		};
		void init();
		void display();
		void update(unsigned long t);
		void YafScene::processGraph( string rootid, vector<Appearence*> &appstack );
		vector<CGFcamera*> *getSceneCameras();
		void activateCamera( int i );
		~YafScene();

	protected:
		SceneGraph *sg;
		int movieIndex;
		int timeElapsed;

	private:
		void initGraph( string rootId, vector<Appearence*> &appstack );

	friend class SceneGraph;
	friend class GraphNode;
};

#endif