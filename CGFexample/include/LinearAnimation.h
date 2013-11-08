#ifndef _LINEARANIMATION_H_
#define _LINEARANIMATION_H_

#include "Animation.h"
#include "AnimationPoint.h"
#include "math.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

class LinearAnimation{
	public:
		LinearAnimation( int animationCp, float **originalMatrix, float totalDuration );
		~LinearAnimation();
		void reset();
		void draw();
		void update( unsigned long t );  
	private:
		void init( unsigned long t );
		vector<AnimationPoint*> ctrlPoints;
		unsigned long startTime;
		unsigned char doReset;
		int pointNumber;
		float x, y, z;
};

#endif