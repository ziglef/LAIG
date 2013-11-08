#ifndef _ANIMATIONPOINT_H_
#define _ANIMATIONPOINT_H_

class AnimationPoint{
	public:
		AnimationPoint( float x, float y, float z );
		~AnimationPoint();
		void setDistance( float distance );
		float getDistance();
		void setDuration( float duration );
		float getDuration();
		float getX();
		float getY();
		float getZ();
		void setIterations( int iterations );
		int getIterations();
		void setMaxIterations( int maxIterations );
		int getMaxIterations();
    private:
		float distance;
		float duration;
		int iterations;
		int maxIterations;
		float x, y, z;
};

#endif