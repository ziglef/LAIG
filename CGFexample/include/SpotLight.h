#ifndef _SPOTLIGHT_H
#define _SPOTLIGHT_H

#include "Lighting.h"

class SpotLight : public Lighting{
	public:
		SpotLight(	string ref,
					bool enabled,
					float *locationValues,
					float *diffuseValues,
					float *ambientValues,
					float *specularValues,
					float angle,
					float exponent,
					float *directionValues
				) : Lighting( ref, enabled, locationValues, diffuseValues, ambientValues, specularValues, direction ){
					this->exponent = exponent;

					this->setAngle( angle );
		};
		~SpotLight();
		string getType();
		string getID();

	protected:
		float exponent;
};

#endif