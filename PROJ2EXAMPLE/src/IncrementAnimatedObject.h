#ifndef _INCREMENTANIMATED_OBJECT_H_
#define _INCREMENTANIMATED_OBJECT_H_


class IncrementAnimatedObject
{
	public:
		IncrementAnimatedObject(unsigned long milli_secs);
		void update(unsigned long t);
		void draw();
		void reset();

	private:
		double  obj_radius, obj_rotate, delta_radius, delta_rotate;
		unsigned char doReset;
		void init();

};

#endif