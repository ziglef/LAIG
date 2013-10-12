#ifndef _LIGHTING_H
#define _LIGHTING_H

#include "CGF\CGFlight.h"
#include <string>
using std::string;

class Lighting : public CGFlight{
	private:
		static size_t count;

	public:
		Lighting(	string ref,
					bool enabled,
					float *locationValues,
					float *diffuseValues,
					float *ambientValues,
					float *specularValues
				) : CGFlight( count,  locationValues, NULL){
					this->ref = ref;
					this->enabled = enabled;
					
					this->setAmbient( ambientValues );
					this->setDiffuse( diffuseValues );
					this->setSpecular( specularValues );
					++count;			
		};

		Lighting(	string ref,
					bool enabled,
					float *locationValues,
					float *diffuseValues,
					float *ambientValues,
					float *specularValues,
					float *direction
				) : CGFlight( count,  locationValues, direction){
					this->ref = ref;
					this->enabled = enabled;
					
					this->setAmbient( ambientValues );
					this->setDiffuse( diffuseValues );
					this->setSpecular( specularValues );
					++count;
		};
		~Lighting();
		virtual string getType();
		virtual string getID();
		int *getToogled();
		void setToogled( int toogled );
		bool getEnabled();

	protected:
		string ref;
		int toogled;
};

#endif