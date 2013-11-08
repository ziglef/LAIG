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
    private:
		float distance;
		float duration;
		float x, y, z;
};

#endif