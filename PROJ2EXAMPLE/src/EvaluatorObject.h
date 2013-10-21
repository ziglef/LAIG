#ifndef _EVALUATOR_OBJECT_H_
#define _EVALUATOR_OBJECT_H_

#include "CGFtexture.h"

class EvaluatorObject
{
	public:
		void draw();
		EvaluatorObject();
		~EvaluatorObject();

	private:
		CGFtexture *myTexture;
};

#endif
