#ifndef _OMNILIGHT_H
#define _OMNILIGHT_H

#include "Lighting.h"

class OmniLight : public Lighting{
	public:
		OmniLight(	string ref,
					bool enabled,
					float *locationValues,
					float *diffuseValues,
					float *ambientValues,
					float *specularValues
				) : Lighting( ref, enabled, locationValues, diffuseValues, ambientValues, specularValues ){
		};
		~OmniLight();
		string getType();
		string getID();
};

#endif