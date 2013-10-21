#ifndef _ANIMATED_OBJECT_H_
#define _ANIMATED_OBJECT_H_


class AnimatedObject
{
	public:
		AnimatedObject();
		void update(unsigned long t);
		void draw();
		void reset();

	private:
		double  obj_radius, obj_rotate, radius_speed_ms, rotate_speed_ms;
		unsigned long startTime;
		unsigned char doReset;
		void init(unsigned long t);

};

#endif