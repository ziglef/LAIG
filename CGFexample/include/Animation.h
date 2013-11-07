#ifndef _ANIMATION_H_
#define _ANIMATION_H_

class Animation{
	public:
		Animation();
		~Animation();
		void reset();
		void update( unsigned long t );
		void draw();

	private:
		void init( unsigned long t );
		double  obj_radius, obj_rotate, radius_speed_ms, rotate_speed_ms;
		unsigned long startTime;
		unsigned char doReset;
};

#endif