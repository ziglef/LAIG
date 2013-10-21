#ifndef DEMOSCENE_H
#define DEMOSCENE_H

#include "CGFscene.h"
#include "DemoInterface.h"
#include "CGFshader.h"

#include "AnimatedObject.h"
#include "IncrementAnimatedObject.h"

#include "DisplayListObject.h"
#include "EvaluatorObject.h"
#include "TextObject.h"


class DemoScene : public CGFscene
{
	friend DemoInterface;
public:
	void init();
	void display();
	void update(unsigned long t);
	~DemoScene();


protected:
	CGFlight* light0;
	CGFshader* demoshader;

	int wireframe;

	IncrementAnimatedObject *myIncAnimObj;
	AnimatedObject *myTimeAnimObj;

	TextObject *myTextObj;

	DisplayListObject *myDLObj;

	EvaluatorObject *myEvalObj;

};

#endif