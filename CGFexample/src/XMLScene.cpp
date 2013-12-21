#include "../include/XMLScene.h"
#include "../include/SceneGraph.h"

#include <iostream>

XMLScene::XMLScene(char *filename, bool debug) {

	// Read XML from file //
	doc = new TiXmlDocument( filename );
	// Get loaded state //
	bool loadOkay = doc->LoadFile();

	// Check if it loaded okay //
	if ( ( !loadOkay ) && debug ) {
		printf( "Could not load file '%s'. Error='%s'. Exiting.\n", filename, doc->ErrorDesc() );
		exit( 1 );
	}

	// Gets the main child //
	yafElement = doc->FirstChildElement( "yaf" );

	// Checks if it was read //
	if ( ( yafElement == NULL ) && debug ) {
		printf("Main yaf block element not found! Exiting!\n");
		exit(1);
	}

	// Loads all the other major tags //
	globals = yafElement->FirstChildElement( "globals" );
	cameras = yafElement->FirstChildElement( "cameras" );
	lighting =  yafElement->FirstChildElement( "lighting" );
	textures =  yafElement->FirstChildElement( "textures" );
	appearances =  yafElement->FirstChildElement( "appearances" );
	animations = yafElement->FirstChildElement( "animations" );
	sceneGraph =  yafElement->FirstChildElement( "graph" );

	// Globals //
	if ( ( globals == NULL ) && debug )
		printf("Globals block not found!\n");
	else {
		if( debug ) printf("\nProcessing globals:\n");

		// Background //
		char *background;
		float backgroundX, backgroundY, backgroundZ, backgroundA;

		// Config Values //
		char *drawmode;
		char *shading;
		char *cullface;
		char *cullorder;

		// Process Background //
		background = (char *)globals->Attribute( "background" );

		if(background && sscanf(background,"%f %f %f %f",&backgroundX, &backgroundY, &backgroundZ, &backgroundA) == 4) {
			if( debug ) printf("\tBackground: %f %f %f %f\n", backgroundX, backgroundY, backgroundZ, backgroundA);
		} else
			if( debug ) printf("\t!! Error parsing Background values !!\n");

		// Process Config Values //
		drawmode = (char *)globals->Attribute( "drawmode" );
		shading = (char *)globals->Attribute( "shading" );
		cullface = (char *)globals->Attribute( "cullface" );
		cullorder = (char *)globals->Attribute( "cullorder" );

		if( drawmode  && debug )
			printf("\tDrawmode: %s\n", drawmode);
		else 
			if( debug ) printf("\t!! Error parsing Drawmode values !!\n");

		if( shading  && debug )
			printf("\tShading: %s\n", shading);
		else 
			if( debug ) printf("\t!! Error parsing Shading values !!\n");

		if( cullface  && debug )
			printf("\tCullface: %s\n", cullface);
		else 
			if( debug ) printf("\t!! Error parsing Cullface values !!\n");

		if( cullorder  && debug )
			printf("\tCullorder: %s\n", cullorder);
		else 
			if( debug ) printf("\t!! Error parsing Cullorder values !!\n");
	
		this->sg = new SceneGraph( backgroundX, backgroundY, backgroundZ, backgroundA, drawmode, shading, cullface, cullorder );
	}

	// Cameras //
	if( ( cameras == NULL ) && debug )
		printf("Cameras block not found!\n");
	else{
		if( debug )printf("\nProcessing cameras:\n");

		// Initial Camera ID //
		char* initialCamera;

		// Pespective and Othogonal Shared Fields //
		char *id;
		float near;
		float far;

		// Perspective Camera Values //
		float angle;
		char *pos;
		float posV[3];
		char *target;
		float targetV[3];

		// Orthogonal Camera Values //
		float left;
		float right;
		float top;
		float bottom;

		// Inicial Camera Info //
		initialCamera = (char*)cameras->Attribute( "initial" );
		if( initialCamera && debug )
			printf("\tInitial camera: %s\n", initialCamera);
		else
			if( debug ) printf("\t!! Error parsing ID of the initial camera !!\n");

		// Sets the initial camera info on the scene graph //
		this->sg->setInitialCamera( initialCamera );
		
		// Process Perspective Camera Values //
		cameraChilds = cameras->FirstChildElement(  );

		while( cameraChilds ){
				if( strcmp( cameraChilds->Value(), "perspective" )==0 ){
					// ID //
					id = (char *)cameraChilds->Attribute( "id" );
					if( id && debug )
						printf("\tPerspective Camera id: %s\n", id);
					else
						if( debug ) printf("\t!! Error parsing perspective camera id !!\n");
			
					// Near //
					if( cameraChilds->QueryFloatAttribute( "near", &near )==TIXML_SUCCESS && debug )
						printf("\tNear: %f\n", near);
					else
						if( debug ) printf("\t!! Error parsing Near value !!\n");

					// Far //
					if( cameraChilds->QueryFloatAttribute( "far", &far )==TIXML_SUCCESS && debug )
						printf("\tFar: %f\n", far);
					else
						if( debug ) printf("\t!! Error parsing Far value !!\n");

					// Angle //
					if( cameraChilds->QueryFloatAttribute( "angle", &angle )==TIXML_SUCCESS && debug )
						printf("\tAngle: %f\n", angle);
					else
						if( debug ) printf("\t!! Error parsing Angle value !!\n");

					// Position //
					pos = (char *)cameraChilds->Attribute( "pos" );

					if( pos && sscanf(pos, "%f %f %f", &posV[0], &posV[1], &posV[2] )==3 && debug )
						printf("\tPos: %f %f %f\n", posV[0], posV[1], posV[2]);
					else
						if( debug ) printf("\t!! Error parsing Pos values !!\n");

					// Target //
					target = (char *)cameraChilds->Attribute( "target" );

					if( pos && sscanf(target, "%f %f %f", &targetV[0], &targetV[1], &targetV[2] )==3 && debug )
						printf("\tTarget: %f %f %f\n", targetV[0], targetV[1], targetV[2]);
					else
						if( debug ) printf("\t!! Error parsing Target value !!\n");

					// Adds new perspective camera
					this->sg->addCamera( new PerspectiveCamera( id, near, far, angle, posV, targetV ) );
					if( debug ) printf("\n");
				}
		

			// Process Orthogonal Camera Values //
				if( strcmp( cameraChilds->Value(), "ortho")==0 ){
			
					// ID //
					id = (char *)cameraChilds->Attribute( "id" );
					if( id && debug )
						printf("\tOrthogonal camera id: %s\n", id);
					else
						if( debug ) printf("\t!! Error parsing orthogonal camera id !!\n");

					// Near //
					if( cameraChilds->QueryFloatAttribute( "near", &near )==TIXML_SUCCESS && debug )
						printf("\tNear: %f\n", near);
					else
						if( debug ) printf("\tError parsing near value !!\n");

					// Far //
					if( cameraChilds->QueryFloatAttribute( "far", &far )==TIXML_SUCCESS && debug )
						printf("\tFar: %f\n", far);
					else
						if( debug ) printf("\tError parsing far value !!\n");

					// Left //
					if( cameraChilds->QueryFloatAttribute( "left", &left )==TIXML_SUCCESS && debug )
						printf("\tLeft: %f\n", left);
					else
						if( debug ) printf("\tError parsing left value !!\n");

					// Right //
					if( cameraChilds->QueryFloatAttribute( "right", &right )==TIXML_SUCCESS && debug )
						printf("\tRight: %f\n", right);
					else
						if( debug ) printf("\tError parsing right value !!\n");

					// Top //
					if( cameraChilds->QueryFloatAttribute( "top", &top )==TIXML_SUCCESS && debug )
						printf("\tTop: %f\n", top);
					else
						if( debug ) printf("\tError parsing top value !!\n");

					// Bottom //
					if( cameraChilds->QueryFloatAttribute( "bottom", &bottom )==TIXML_SUCCESS && debug )
						printf("\tBottom: %f\n", bottom);
					else
						if( debug ) printf("\tError parsing bottom value !!\n");

					// Adds a new orthogonal camera
					this->sg->addCamera( new OrthogonalCamera( id, near, far, left, right, top, bottom ) );
					if( debug ) printf("\n");
				}
				cameraChilds = cameraChilds->NextSiblingElement( );
			}
		}

		// Lighting Block //
		if( ( lighting == NULL ) && debug )
			printf("Lighting block not found\n");
		else{
			if( debug ) printf("Processing Lights:\n");

			// Omni and Spot Lights Shared Fields //
			char *id;
			char *enabled;
			bool enabledBool;
			char *location;
			float locationV[3];
			char *diffuse;
			float diffuseV[4];
			char *ambient;
			float ambientV[4];
			char *specular;
			float specularV[4];
			
			// Lighting values //
			char *doublesided;
			char *local;
			char *LightingEnabled;
			char *LightingAmbient;
			float LightingAmbientV[4];

			// Spot Lights values //
			float angle;
			float exponent;
			char *direction;
			float directionV[4];

			// Process Lighting values //
			doublesided = (char *)lighting->Attribute( "doublesided" );
			local = (char *)lighting->Attribute( "local" );
			LightingEnabled = (char *)lighting->Attribute( "enabled" );
			LightingAmbient = (char *)lighting->Attribute( "ambient" );

			// Doublesided //
			if( doublesided && debug )
				printf("\tDoublesided: %s\n", doublesided);
			else
				if( debug ) printf("\t!! Error parsing doublesided value !!\n");

			// Local //
			if( local && debug )
				printf("\tLocal: %s\n", local);
			else
				if( debug ) printf("\t!! Error parsing local value !!\n");

			// Enabled //
			if( LightingEnabled  && debug )
				printf("\tEnabled: %s\n", LightingEnabled);
			else
				if( debug ) printf("\t!! Error parsing enabled value !!\n");

			// Ambient //
			if( sscanf(LightingAmbient, "%f %f %f %f", &LightingAmbientV[0], &LightingAmbientV[1], &LightingAmbientV[2], &LightingAmbientV[3] )==4 && debug )
					printf("\tAmbient: %f %f %f %f\n\n", LightingAmbientV[0], LightingAmbientV[1], LightingAmbientV[2], LightingAmbientV[3] );
				else
					if( debug ) printf("\t!! Error parsing ambient values !!\n");

			// Save the Lighting values in the sceneGraph //
			sg->addLightingValues( doublesided, local, LightingEnabled, LightingAmbientV );

			// Process Omni Lighting Values //
			lights = lighting->FirstChildElement();
			while( lights ){
					if( strcmp( lights->Value(), "omni") == 0 ){

						id = (char *)lights->Attribute( "id" );
						enabled = (char *)lights->Attribute( "enabled" );
						location = (char *)lights->Attribute( "location" );
						ambient = (char *)lights->Attribute( "ambient" );
						diffuse = (char *)lights->Attribute( "diffuse" );
						specular = (char *)lights->Attribute( "specular" );

						// ID //
						if( id && debug )
							printf("\tOmni Light id: %s\n", id);
						else
							if( debug ) printf("\t!! Error parsing omni light id !!\n");

						// Enabled //
						if( enabled && debug )
							printf("\tEnabled: %s\n", enabled);
						else
							if( debug ) printf("\t!! Error parsing enabled value !!\n");

						// Location //
						if( sscanf(location, "%f %f %f", &locationV[0], &locationV[1], &locationV[2] )==3 && debug )
							printf("\tLocation: %f %f %f\n", locationV[0], locationV[1], locationV[2] );
						else
							if( debug ) printf("\t!! Error parsing location values !!\n");

						// Ambient //
						if( sscanf(ambient, "%f %f %f %f", &ambientV[0], &ambientV[1], &ambientV[2], &ambientV[3] )==4 && debug )
							printf("\tAmbient: %f %f %f %f\n", ambientV[0], ambientV[1], ambientV[2], ambientV[3]);
						else
							if( debug ) printf("\t!! Error parsing ambient values !!\n");

						// Diffuse //
						if( sscanf(diffuse, "%f %f %f %f", &diffuseV[0], &diffuseV[1], &diffuseV[2], &diffuseV[3] )==4 && debug )
							printf("\tDiffuse: %f %f %f %f\n", diffuseV[0], diffuseV[1], diffuseV[2], diffuseV[3]);
						else
							if( debug ) printf("\t!! Error parsing diffuse values !!\n");

						// Specular //
						if( sscanf(specular,"%f %f %f %f", &specularV[0], &specularV[1], &specularV[2], &specularV[3] )==4 && debug )
							printf("\tSpecular: %f %f %f %f\n\n", specularV[1], specularV[1], specularV[2], specularV[3]);
						else
							if( debug ) printf("\t!! Error parsing specular values !!\n");

						if(strcmp(enabled, "true") == 0)
							enabledBool = true;
						else
							enabledBool = false;

						// Adds the omni light to the omni lights map //
						this->sg->addLight( new OmniLight( id, enabledBool, locationV, diffuseV,  ambientV, specularV ) );
						if( debug ) printf("\n");
					}

				// Process spot Lighting values //
					if( strcmp( lights->Value(), "spot" ) == 0 ){
				
						id = (char *)lights->Attribute( "id" );
						enabled = (char *)lights->Attribute( "enabled" );
						location = (char *)lights->Attribute( "location" );
						ambient = (char *)lights->Attribute( "ambient" );
						diffuse = (char *)lights->Attribute( "diffuse" );
						specular = (char *)lights->Attribute( "specular" );
						direction = (char *)lights->Attribute( "direction" );

						// ID //
						if( id && debug )
							printf("\tSpot Light id: %s\n", id);
						else
							if( debug ) printf("\t!! Error parsing spot light id !!\n");

						// Enabled //
						if( enabled && debug )
							printf("\tEnabled: %s\n", enabled);
						else
							if( debug ) printf("\t!! Error parsing enabled value !!\n");

						// Location //
						if( sscanf(location, "%f %f %f", &locationV[0], &locationV[1], &locationV[2] )==3 && debug )
							printf("\tLocation: %f %f %f\n", locationV[0], locationV[1], locationV[2] );
						else
							if( debug ) printf("\t!! Error parsing location values !!\n");

						// Ambient //
						if( sscanf(ambient, "%f %f %f %f", &ambientV[0], &ambientV[1], &ambientV[2], &ambientV[3] )==4 && debug )
							printf("\tAmbient: %f %f %f %f\n", ambientV[0], ambientV[1], ambientV[2], ambientV[3]);
						else
							if( debug ) printf("\t!! Error parsing ambient values !!\n");

						// Diffuse //
						if( sscanf(diffuse, "%f %f %f %f", &diffuseV[0], &diffuseV[1], &diffuseV[2], &diffuseV[3] )==4 && debug )
							printf("\tDiffuse: %f %f %f %f\n", diffuseV[0], diffuseV[1], diffuseV[2], diffuseV[3]);
						else
							if( debug ) printf("\t!! Error parsing diffuse values !!\n");

						// Specular //
						if( sscanf(specular,"%f %f %f %f", &specularV[0], &specularV[1], &specularV[2], &specularV[3] )==4 && debug )
							printf("\tSpecular: %f %f %f %f\n", specularV[1], specularV[1], specularV[2], specularV[3]);
						else
							if( debug ) printf("\t!! Error parsing specular values !!\n");

						// Angle //
						if( lights->QueryFloatAttribute( "angle", &angle )==TIXML_SUCCESS && debug )
							printf("\tAngle: %f\n", angle);
						else
							if( debug ) printf("\t!! Error parsing angle value !!\n");

						// Exponent //
						if( lights->QueryFloatAttribute( "exponent", &exponent )==TIXML_SUCCESS && debug )
							printf("\tExponent: %f\n", exponent);
						else
							if( debug ) printf("\t!! Error parsing exponent value !!\n");

						// Direction //
						if( sscanf(direction, "%f %f %f %f", &directionV[0], &directionV[1], &directionV[2] )==3 && debug )
							printf("\tDirection: %f %f %f\n", directionV[0], directionV[1], directionV[2]);
						else
							if( debug ) printf("\t!! Error parsing direction values !!\n");

						if(strcmp(enabled, "true") == 0)
							enabledBool = true;
						else
							enabledBool = false;

						// Adds the spot light to the spot lights map //
						this->sg->addLight( new SpotLight( id, enabledBool, locationV, diffuseV, ambientV, specularV, angle, exponent, directionV) );
						if( debug ) printf("\n");
					}
					lights = lights->NextSiblingElement();
				  }
			}

		// Textures block //
		if( textures == NULL && debug )
			printf("Textures block not found");
		else{
			if( debug ) printf("Processing Textures:\n");

			// Texture values //
			char *id;
			char *file;

			// Textures vector //
			vector<Texture> texturesVector;

			// Process Textures values //
			textureTextures = textures->FirstChildElement( "texture" );

			if( textureTextures ){
				do{
					id = (char *)textureTextures->Attribute( "id" );
					file = (char *)textureTextures->Attribute( "file" );

					// ID //
					if( id && debug )
						printf("\tTexture id: %s\n", id);
					else
						if( debug ) printf("\t!! Error parsing texture id !!\n");

					// File Location //
					if( file && debug )
						printf("\tTexture file location: %s\n", file);
					else
						if( debug ) printf("\t!! Error parsing texture file location !!\n");

					//Saves the textures vector in the scene graph //
					this->sg->addTexture( new Texture( id, file ) );

					// Parses the next texture //
					textureTextures = textureTextures->NextSiblingElement( "texture" );
					if( debug ) printf("\n");
				}while( textureTextures );
			}
		}

		// Appearences Block //
		if( appearances == NULL && debug )
			printf("Appearences block not found\n");
		else{
			if( debug ) printf("Processing Appearences:\n");

			// Appearences Values //
			char *id;
			char *emissive;
			float emissiveValues[4];
			char *diffuse;
			float diffuseValues[4];
			char *ambient;
			float ambientValues[4];
			char *specular;
			float specularValues[4];
			float shininess;
			char *textureref;
			float texlength_s;
			int sWrap;
			float texlength_t;
			int tWrap;

			// Appearences vector //
			vector<Appearence> appearencesVector;

			// Process Appearance values //
			appearanceAppearances = appearances->FirstChildElement( "appearance" );
			if( appearanceAppearances ){
				do{
					id = (char*)appearanceAppearances->Attribute( "id" );
					emissive = (char*)appearanceAppearances->Attribute( "emissive" );
					ambient = (char*)appearanceAppearances->Attribute( "ambient" );
					diffuse = (char*)appearanceAppearances->Attribute( "diffuse" );
					specular = (char*)appearanceAppearances->Attribute( "specular" );
					textureref = (char*)appearanceAppearances->Attribute( "textureref" );

					// ID //
					if( id && debug )
						printf("\tAppearance id: %s\n", id);
					else
						if( debug ) printf("\t!! Error parsing appearance id !!\n");

					// Emissive //
					if( sscanf(emissive, "%f %f %f %f", &emissiveValues[0], &emissiveValues[1], &emissiveValues[2], &emissiveValues[3] )==4 && debug )
						printf("\tEmissive: %f %f %f %f\n", emissiveValues[0], emissiveValues[1], emissiveValues[2], emissiveValues[3]);
					else
						if( debug ) printf("\t!! Error parsing Emissive values !!\n");

					// Ambient //
					if( sscanf(ambient, "%f %f %f %f", &ambientValues[0], &ambientValues[1], &ambientValues[2], &ambientValues[3] )==4 && debug )
						printf("\tAmbient: %f %f %f %f\n", ambientValues[0], ambientValues[1], ambientValues[2], ambientValues[3]);
					else
						if( debug ) printf("\t!! Error parsing ambient values !!\n");

					// Diffuse //
					if( sscanf(diffuse, "%f %f %f %f", &diffuseValues[0], &diffuseValues[1], &diffuseValues[2], &diffuseValues[3] )==4 && debug )
						printf("\tDiffuse: %f %f %f %f\n", diffuseValues[0], diffuseValues[1], diffuseValues[2], diffuseValues[3]);
					else
						if( debug ) printf("\t!! Error parsing diffuse values !!\n");

					// Specular //
					if( sscanf(specular, "%f %f %f %f", &specularValues[0], &specularValues[1], &specularValues[2], &specularValues[3] )==4 && debug )
						printf("\tSpecular: %f %f %f %f\n", specularValues[0], specularValues[1], specularValues[2], specularValues[3]);
					else
						if( debug ) printf("\t!! Error parsing specular values !!\n");

					// Shininess //
					if( appearanceAppearances->QueryFloatAttribute( "shininess", &shininess )==TIXML_SUCCESS && debug )
						printf("\tShininess: %f\n", shininess);
					else
						if( debug ) printf("\t!! Error parsing shininess value !!\n");

					// TextureRef //
					if( textureref && debug )
						printf("\ttextureref: %s\n", textureref);
					else
						if( debug ) printf("\t!! Error parsing textureref !!\n");

					// TexLength_s //
					if( appearanceAppearances->QueryFloatAttribute( "texlength_s", &texlength_s )==TIXML_SUCCESS && debug )
						printf("\tTexlength_s: %f\n", texlength_s);
					else
						if( debug ) printf("\t!! Error parsing texlength_s value !!\n");

					// TexLength_t //
					if( appearanceAppearances->QueryFloatAttribute( "texlength_t", &texlength_t )==TIXML_SUCCESS && debug )
						printf("\tTexlength_t: %f\n", texlength_t);
					else
						if( debug ) printf("\t!! Error parsing texlength_t value !!\n");

					// Adds the appearence to the appearences vector //
					if( texlength_s != NULL ){
						sWrap = (int)texlength_s;
						tWrap = (int)texlength_t;
					}

					CGFtexture *textureRef;

					if( textureref != NULL && strcmp(textureref, "") != 0)
						textureRef = this->sg->getTextures()->at(textureref);
					else
						textureRef = NULL;


					if( textureRef == NULL ){
							 this->sg->addAppearence( new Appearence( id, emissiveValues, diffuseValues, ambientValues, specularValues, shininess ) );
					  } else {
						  this->sg->addAppearence( new Appearence( id, emissiveValues, diffuseValues, ambientValues, specularValues, shininess, textureRef, sWrap, tWrap ) );
						 textureref = NULL;
					  }					

					appearanceAppearances = appearanceAppearances->NextSiblingElement( "appearance" );
					if( debug ) printf("\n");
				}while( appearanceAppearances );
			}
		}

		// Animations Block //
		if( animations == NULL && debug )
			printf("Animations block not found!\n");
		else{
			if( debug ) printf("Processing animations:\n");

			// Animation values //
			char *id;
			char *type = "linear";
			float span;

			GLfloat **cpAnimationMatrix = NULL;
			int controlAnimationPoints = 0;

			vector<LinearAnimation> animationsVector;

			// Control point values //
			float x, y, z;

			animationsAnimation = animations->FirstChildElement( "animation" );
			controlpointAnimation = animationsAnimation->FirstChildElement( "controlpoint" );


			if( animationsAnimation ){
				do{
					 id = (char *)animationsAnimation->Attribute( "id" );
					 if( id && debug )
						  printf("\tAnimation ID: %s\n\n", id);
					  else
						  if( debug ) printf("\t!! Error parsing Animation ID !!\n");

					 if( animationsAnimation->QueryFloatAttribute( "span", &span )==TIXML_SUCCESS && debug )
						 printf("\tSpan Value : %f\n", span);
					 else
						 if( debug ) printf("\t!! Error parsing span value !!\n");

					 if( controlpointAnimation ){
						 do{
							 if( controlpointAnimation->QueryFloatAttribute( "xx", &x )==TIXML_SUCCESS && debug )
								 printf("\tAnimation control point X:%f\n", x);
							 else
								 if( debug ) printf("\t!! Error parsing Animation control point X !!\n");

							 if( controlpointAnimation->QueryFloatAttribute( "yy", &y )==TIXML_SUCCESS && debug )
								 printf("\tAnimation control point Y:%f\n", y);
							 else
								 if( debug ) printf("\t!! Error parsing Animation control point Y !!\n");

							 if( controlpointAnimation->QueryFloatAttribute( "zz", &z )==TIXML_SUCCESS && debug )
								 printf("\tAnimation control point Z:%f\n", z);
							 else
								 if( debug ) printf("\t!! Error parsing Animation control point Z !!\n");

							controlAnimationPoints++;
							cpAnimationMatrix = (GLfloat **)realloc(cpAnimationMatrix, sizeof(GLfloat *) * controlAnimationPoints);
							cpAnimationMatrix[controlAnimationPoints-1] = (GLfloat *)malloc(sizeof(GLfloat) * 3);
							cpAnimationMatrix[controlAnimationPoints-1][0] = x;
							cpAnimationMatrix[controlAnimationPoints-1][1] = y;
							cpAnimationMatrix[controlAnimationPoints-1][2] = z;

							 controlpointAnimation = controlpointAnimation->NextSiblingElement( "controlpoint" );
							 if( debug ) printf("\n");
						 }while( controlpointAnimation );
					 }

					 this->sg->addAnimation( new LinearAnimation( id, controlAnimationPoints, cpAnimationMatrix, span ) );
					 animationsAnimation = animationsAnimation->NextSiblingElement( "animation" );
					 if( debug ) printf("\n");
				}while( animationsAnimation );
			 }
		}

		// Graph Block //
		if( sceneGraph == NULL && debug )
			printf("Graph block not found!\n");
		else{
			  if( debug ) printf("Processing Graph:\n");

			  // Graph values //
			  char *rootid;

			  // Nodes Vector //
			  GraphNode *node;

			  // Node values //
			  char *id;
			  char *displayList;
			  bool hasDL = false;

			  // AppearanceRef Values //
			  char *appRefId = NULL;

			  // Animationref Values //
			  char *animRefId = NULL;

			  // Plane Values //
			  int parts;

			  // Patch Values //
			  int order, partsU, partsV;
			  char *compute;
			  GLfloat **cpPatchMatrix = NULL;
			  int controlPatchPoints = 0;
			 
			  // Control Point Values //
			  float cpx, cpy, cpz;

			  // Tranformation Values //
			  char *translate;
			  float translateX, translateY, translateZ;
			  char *scale;
			  float scaleX, scaleY, scaleZ;
			  char *rotateAxis;
			  float rotateAngle;

			  // Children Values //
			  char *nodeRefId;

			  // Primitive Values //

			  // Rectangle Values //
			  char *xy1;
			  char *xy2;
			  float rx1, ry1, rx2, ry2;

			  // Triangle Values //
			  char *xyz1;
			  char *xyz2;
			  char *xyz3;
			  float tx1, ty1, tz1;
			  float tx2, ty2, tz2;
			  float tx3, ty3, tz3;

			  // Cylinder Values //
			  float cbase;
			  float ctop;
			  float cheight;
			  int cslices;
			  int cstacks;

			  // Sphere Values //
			  float sradius;
		      int sslices;
		      int sstacks;

			  // Torus Values //
			  float tinner;
			  float touter;
			  int tslices;
			  int tloops;

			   // Waterline Values //
			  char *heightmap;
			  char *texturemap;
			  char *fragmentshader;
			  char *vertexshader;

			  // Process the Graph ID //
			  rootid = (char*)sceneGraph->Attribute( "rootid" );
			  if( rootid && debug )
				  printf("\tGraph root ID: %s\n\n", rootid);
			  else
				  if( debug ) printf("\t!! Error parsing Graph root ID !!\n");

			  sg->setRootId( rootid );

			  glMatrixMode( GL_MODELVIEW_MATRIX );

			  // Process Nodes of the Graph //
			  nodeGraph = sceneGraph->FirstChildElement( "node" );
			  if( nodeGraph ){
				  do{
					  vector<string> nodeRefIdVector;	
					  // Primitives Vector //
					  vector<CGFobject*> primitives;
					  id = (char *)nodeGraph->Attribute( "id" );
					  displayList = (char *)nodeGraph->Attribute( "displaylist" );
					  transformsNodeGraph = nodeGraph->FirstChildElement( "transforms" );
					  transformsChildNodeGraph = transformsNodeGraph->FirstChildElement();
					  appearanceRefNodeGraph = nodeGraph->FirstChildElement( "appearanceref" );
					  animationRefNodeGraph = nodeGraph->FirstChildElement( "animationref" );
					  planePartsNodeGraph = nodeGraph->FirstChildElement( "plane" );
					  childrenNodeGraph = nodeGraph->FirstChildElement( "children" );
					  patchNodeGraph = childrenNodeGraph->FirstChildElement( "patch" );
					  vehicleNodeGraph = childrenNodeGraph->FirstChildElement( "vehicle" );
					  boardNodeGraph = childrenNodeGraph->FirstChildElement( "board" );
					  noderefChildrenNodeGraph = childrenNodeGraph->FirstChildElement( "noderef" );
					  rectangleChildrenNodeGraph = childrenNodeGraph->FirstChildElement( "rectangle" );
					  triangleChildrenNodeGraph = childrenNodeGraph->FirstChildElement( "triangle" );
					  cylinderChildrenNodeGraph = childrenNodeGraph->FirstChildElement( "cylinder" );
					  sphereChildrenNodeGraph = childrenNodeGraph->FirstChildElement( "sphere" );
					  torusChildrenNodeGraph = childrenNodeGraph->FirstChildElement( "torus" );
					  waterlineNodeGraph = childrenNodeGraph->FirstChildElement( "waterline" );

					  // Node ID //
					  if( id && debug )
						  printf("\tNode ID: %s\n", id);
					  else
						  if( debug ) printf("\t!! Error parsing node ID !!\n");

					  // Dispay List //
					  if( displayList ){
						  if( strcmp( "true", displayList )== 0 )
							  hasDL = true;
						  else
							  hasDL = false;
					  }

					  if( displayList && debug )
						  printf("\tDislplay list : %s", displayList);
					  else
						  if( debug ) printf("\t!! Error parsing display list element !!\n");

					  // Tranformations //

					  // Initialize the translation matrix //
					  glLoadIdentity();

					while( transformsChildNodeGraph ){
						// Translate //
						if( strcmp(transformsChildNodeGraph->Value(), "translate") == 0 ){
							translate = (char *)transformsChildNodeGraph->Attribute( "to" );
							if( sscanf(translate, "%f %f %f", &translateX, &translateY, &translateZ )==3 && debug )
								printf("\tTranslate: %f %f %f\n", translateX, translateY, translateZ);
							else
								if( debug ) printf("\t!! Error parsing Translate values !!\n");
							glTranslatef( translateX, translateY, translateZ );
						}

					   // Scale //
						if( strcmp(transformsChildNodeGraph->Value(), "scale") == 0 ){
							scale = (char *)transformsChildNodeGraph->Attribute( "factor" );
							if( sscanf(scale, "%f %f %f", &scaleX, &scaleY, &scaleZ )==3 && debug )
							printf("\tScale: %f %f %f\n", scaleX, scaleY, scaleZ);
							else
							if( debug ) printf("\t!! Error parsing scale values !!\n");
							glScalef( scaleX, scaleY, scaleZ );
						}

						// Rotate //
						if( strcmp(transformsChildNodeGraph->Value(), "rotate") == 0 ){
							// Axis //
							rotateAxis = (char *)transformsChildNodeGraph->Attribute( "axis" );
							if( rotateAxis && debug )
								printf("\tRotation Axis: %s ", rotateAxis);
							else
								if( debug ) printf("\t!! Error parsing rotation angle !!\n");

							// Angle //
							if( transformsChildNodeGraph->QueryFloatAttribute( "angle", &rotateAngle )==TIXML_SUCCESS && debug )
								printf("\tRotation Angle: %f\n",rotateAngle);
							else
								if( debug ) printf("\t!! Error parsing rotation angle !!\n");

							// Axis Parsing //
							if(strcmp( rotateAxis, "x" )==0 )
								glRotatef( rotateAngle, 1, 0, 0 );
							else
								if(strcmp( rotateAxis, "y" )==0 )
									glRotatef( rotateAngle, 0, 1, 0 );
								else
									glRotatef( rotateAngle, 0, 0, 1 );
						}
						transformsChildNodeGraph = transformsChildNodeGraph->NextSiblingElement();
					}

					  // Appearance Reference //
					  if( appearanceRefNodeGraph ){
						appRefId = (char *)appearanceRefNodeGraph->Attribute( "id" );
						if( appRefId && debug )
							printf("\tAppearance Reference: %s\n", appRefId);
						else {
							if( debug ) printf("\t!! Error parsing appearance reference !!\n");
						}

						if( !appRefId )
							appRefId = NULL;
					  }

					  // Animation Reference //
					  if( animationRefNodeGraph ){
						  animRefId = (char *)animationRefNodeGraph->Attribute( "id" );
						  if( animRefId && debug )
							  printf("\tAnimation Reference: %s\n", animRefId);
						  else
							  if( debug ) printf("\t!! Error parsing animation reference !!\n");

						  if( !animRefId )
							  animRefId = NULL;
					  }
					  
					  // Plane //
					  if( planePartsNodeGraph ){
						  if( planePartsNodeGraph->QueryIntAttribute( "parts", &parts )==TIXML_SUCCESS && debug )
							  printf("\tParts: %d\n", parts);
						  else
							  if( debug ) printf("\t!! Error parsing Parts !!\n");
					  }

					  // Children //

					  // Node ref //
					  if( noderefChildrenNodeGraph ){
						  do{
							  // Reference ID //
							  nodeRefId = (char *)noderefChildrenNodeGraph->Attribute( "id" );
							  if( nodeRefId && debug )
								  printf("\tNode reference ID: %s\n", nodeRefId);
							  else
								  if( debug ) printf("\t!! Error parsing node reference ID !!\n");
							  noderefChildrenNodeGraph = noderefChildrenNodeGraph->NextSiblingElement( "noderef" );

							  nodeRefIdVector.push_back( nodeRefId );
						  }while( noderefChildrenNodeGraph );
					  }

					  // Primitives //

					  // Patch //
					  if( patchNodeGraph ){
						  if( patchNodeGraph->QueryIntAttribute( "order", &order )==TIXML_SUCCESS && debug )
							  printf("\tOrder: %d\n", order);
						  else
							  if( debug ) printf("\t!! Error parsing Order !!\n");

						  if( patchNodeGraph->QueryIntAttribute( "partsU", &partsU )==TIXML_SUCCESS && debug )
							  printf("\tPartsU: %d\n", partsU);
						  else
							  if( debug ) printf("\t!! Error parsing PartsU !!\n");

						  if( patchNodeGraph->QueryIntAttribute( "partsV", &partsV )==TIXML_SUCCESS && debug )
							  printf("\tPartsV: %d\n", partsV);
						  else
							  if( debug ) printf("\t!! Error parsing PartsU !!\n");

						  compute = (char *)patchNodeGraph->Attribute( "compute" );
						  if( compute && debug )
							  printf("\tCompute: %s\n", compute );
						  else
							  if( debug ) printf("\t!! Error parsing compute value !!\n");

						  controlpointNodeGraph = patchNodeGraph->FirstChildElement( "controlpoint" );
						  if( controlpointNodeGraph ){
							  do{
								if( controlpointNodeGraph->QueryFloatAttribute( "x", &cpx )==TIXML_SUCCESS && debug )
									printf("\tControl Point X: %f\n", cpx);
								else
									if( debug ) printf("\t!! Error parsing Control Point X !!\n");

								if( controlpointNodeGraph->QueryFloatAttribute( "y", &cpy )==TIXML_SUCCESS && debug )
									printf("\tControl Point y: %f\n", cpy);
								else
									if( debug ) printf("\t!! Error parsing Control Point y !!\n");

								if( controlpointNodeGraph->QueryFloatAttribute( "z", &cpz )==TIXML_SUCCESS && debug )
									printf("\tControl Point Z: %f\n", cpz);
								else
									if( debug ) printf("\t!! Error parsing Control Point Z !!\n");

								controlPatchPoints++;
								cpPatchMatrix = (GLfloat **)realloc(cpPatchMatrix, sizeof(GLfloat *) * controlPatchPoints);
								cpPatchMatrix[controlPatchPoints-1] = (GLfloat *)malloc(sizeof(GLfloat) * 3);
								cpPatchMatrix[controlPatchPoints-1][0] = cpx;
								cpPatchMatrix[controlPatchPoints-1][1] = cpy;
								cpPatchMatrix[controlPatchPoints-1][2] = cpz;
								
								controlpointNodeGraph = controlpointNodeGraph->NextSiblingElement( "controlpoint" );
							  }while( controlpointNodeGraph );
							  primitives.push_back( new Patch( order, partsU, partsV, compute, controlPatchPoints, cpPatchMatrix ) );
						  }
					  }

					  // Vehicle //
					  if( vehicleNodeGraph ){
						 primitives.push_back( new Vehicle());
					  }

					  // Board //
					if( boardNodeGraph ){
						primitives.push_back( new Board());
					}

					  // Rectangle //
					  if( rectangleChildrenNodeGraph ){
						  do{
							  xy1 = (char *)rectangleChildrenNodeGraph->Attribute( "xy1" );
							  if( sscanf(xy1, "%f %f", &rx1, &ry1 )==2 && debug )
								printf("\tRectangle : x1:%f y1:%f", rx1, ry1 );
							  else
								if( debug ) printf("\t!! Error parsing xy1 rectangle values !!\n");

							  xy2 = (char *)rectangleChildrenNodeGraph->Attribute( "xy2" );
							  if( sscanf(xy2, "%f %f", &rx2, &ry2 )==2 && debug )
								printf(" x2:%f y2:%f\n", rx2, ry2 );
							  else
								if( debug ) printf("\t!! Error parsing xy2 rectangle values !!\n");

							  primitives.push_back( new Rectangle( rx1, ry1, rx2, ry2 ) );
							  rectangleChildrenNodeGraph = rectangleChildrenNodeGraph->NextSiblingElement( "rectangle" );
							  if( debug ) printf("\n");
						  }while( rectangleChildrenNodeGraph );
					  }

					  // Triangle //
					  if( triangleChildrenNodeGraph ){
						  do{
							  xyz1 = (char *)triangleChildrenNodeGraph->Attribute( "xyz1" );
							  if( sscanf(xyz1, "%f %f %f", &tx1, &ty1, &tz1 )==3 && debug )
								printf("\tTriangle xyz1: x1:%f y1:%f z1:%f\n" , tx1, ty1, tz1 );
							  else
								if( debug ) printf("\t!! Error parsing xyz1 triangle values !!\n");

							  xyz2 = (char *)triangleChildrenNodeGraph->Attribute( "xyz2" );
							  if( sscanf(xyz2, "%f %f %f", &tx2, &ty2, &tz2 )==3 && debug )
								printf("\tTriangle xyz1: x1:%f y1:%f z1:%f\n" , tx2, ty2, tz2 );
							  else
								if( debug ) printf("\t!! Error parsing xyz2 triangle values !!\n");

							  xyz3 = (char *)triangleChildrenNodeGraph->Attribute( "xyz3" );
							  if( sscanf(xyz3, "%f %f %f", &tx3, &ty3, &tz3 )==3 && debug )
								printf("\tTriangle xyz1: x1:%f y1:%f z1:%f\n" , tx3, ty3, tz3 );
							  else
								if( debug ) printf("\t!! Error parsing xyz3 triangle values !!\n");

							  primitives.push_back( new Triangle( tx1, ty1, tz1, tx2, ty2, tz2, tx3, ty3, tz3 ) );
							  triangleChildrenNodeGraph = triangleChildrenNodeGraph->NextSiblingElement( "triangle" );
							  if( debug ) printf("\n");
						  }while( triangleChildrenNodeGraph );
					  }

					  // Cylinder //
					  if( cylinderChildrenNodeGraph ){
						  do{
							  if( cylinderChildrenNodeGraph->QueryFloatAttribute( "base", &cbase )==TIXML_SUCCESS && debug )
								printf("\tCylinder Base: %f\n", cbase);
							  else
								if( debug ) printf("\t!! Error parsing base value !!\n");

							   if( cylinderChildrenNodeGraph->QueryFloatAttribute( "top", &ctop )==TIXML_SUCCESS && debug )
								printf("\tCylinder Top: %f\n", ctop);
							  else
								if( debug ) printf("\t!! Error parsing top value !!\n");

							  if( cylinderChildrenNodeGraph->QueryFloatAttribute( "height", &cheight )==TIXML_SUCCESS && debug )
								printf("\tCylinder Height: %f\n", cheight);
							  else
								if( debug ) printf("\t!! Error parsing height value !!\n");

							  if( cylinderChildrenNodeGraph->QueryIntAttribute( "slices", &cslices )==TIXML_SUCCESS && debug )
								printf("\tCylinder Slices: %d\n", cslices);
							  else
								if( debug ) printf("\t!! Error parsing slices value !!\n");

							  if( cylinderChildrenNodeGraph->QueryIntAttribute( "stacks", &cstacks )==TIXML_SUCCESS && debug )
								  printf("\tCylinder Stacks: %d\n", cstacks);
							  else
								if( debug ) printf("\t!! Error parsing stacks value !!\n");

							  primitives.push_back( new Cylinder( cbase, ctop, cheight, cslices, cstacks ) );
							  cylinderChildrenNodeGraph = cylinderChildrenNodeGraph->NextSiblingElement( "cylinder" );
							  if( debug ) printf("\n");
						  }while( cylinderChildrenNodeGraph );
					  }

					  // Sphere //
					  if( sphereChildrenNodeGraph ){
						  do{
							  if( sphereChildrenNodeGraph->QueryFloatAttribute( "radius", &sradius )==TIXML_SUCCESS && debug )
								printf("\tSphere radius: %f\n", sradius);
							  else
								if( debug ) printf("\t!! Error parsing radius value !!\n");

							  if( sphereChildrenNodeGraph->QueryIntAttribute( "slices", &sslices )==TIXML_SUCCESS && debug )
								printf("\tSphere slices: %d\n", sslices);
							  else
								if( debug ) printf("\t!! Error parsing radius value !!\n");

							   if( sphereChildrenNodeGraph->QueryIntAttribute( "stacks", &sstacks )==TIXML_SUCCESS && debug )
								printf("\tSphere stacks: %d\n", sstacks);
							  else
								if( debug ) printf("\t!! Error parsing stacks value !!\n");

							   primitives.push_back( new Sphere( sradius, sslices, sstacks ) );
							  sphereChildrenNodeGraph = sphereChildrenNodeGraph->NextSiblingElement( "sphere" );
							  if( debug ) printf("\n");
						  }while( sphereChildrenNodeGraph );
					  }

					  // Torus //
					  if( torusChildrenNodeGraph ){
						  do{
							  if(torusChildrenNodeGraph->QueryFloatAttribute( "inner", &tinner )==TIXML_SUCCESS && debug )
								printf("\tTorus inner: %f\n", tinner);
							  else
								if( debug ) printf("\t!! Error parsing inner value !!\n");

							  if( torusChildrenNodeGraph->QueryFloatAttribute( "outer", &touter )==TIXML_SUCCESS && debug )
								printf("\tTorus outers: %f\n", touter);
							  else
								if( debug ) printf("\t!! Error parsing stacks value !!\n");

							  if( torusChildrenNodeGraph->QueryIntAttribute( "slices", &tslices )==TIXML_SUCCESS && debug )
								printf("\tTorus slices: %d\n", tslices);
							  else
								if( debug ) printf("\t!! Error parsing slices value !!\n");

							  if( torusChildrenNodeGraph->QueryIntAttribute( "loops", &tloops )==TIXML_SUCCESS && debug )
								printf("\tTorus loops: %d\n", tloops);
							  else
								if( debug ) printf("\t!! Error parsing loops value !!\n");

							  primitives.push_back( new Torus( tinner, touter, tslices, tloops ) );
							  torusChildrenNodeGraph = torusChildrenNodeGraph->NextSiblingElement( "torus" );
							  if( debug )printf("\n");
						  }while( torusChildrenNodeGraph );
					  }

					  // Waterline //
					  if( waterlineNodeGraph ){
						  heightmap = (char *)waterlineNodeGraph->Attribute( "heightmap" );
						  if( heightmap && debug )
							  printf("\tHeightmap: %s\n", heightmap);
						  else
							  if( debug ) printf("\t!! Error parsing heightmap \n");

						  texturemap = (char *)waterlineNodeGraph->Attribute( "texturemap" );
						  if( texturemap && debug )
							  printf("\tTexturemap: %s\n", texturemap);
						  else
							  if( debug ) printf("\t!! Error parsing Texturemap \n");

						  fragmentshader = (char *)waterlineNodeGraph->Attribute( "fragmentshader" );
						  if( fragmentshader && debug )
							  printf("\tFragmentshader: %s\n", fragmentshader);
						  else
							  if( debug ) printf("\t!! Error parsing Fragmentshader \n");

						  vertexshader = (char *)waterlineNodeGraph->Attribute( "vertexshader" );
						  if( vertexshader && debug )
							  printf("\tVertexshader: %s\n", vertexshader);
						  else
							  if( debug ) printf("\t!! Error parsing Vertexshader \n");

						   primitives.push_back(new Shader( heightmap, texturemap, fragmentshader, vertexshader ));
					  }

					  if( animRefId == NULL && appRefId == NULL ){
						  node = new GraphNode( id, nodeRefIdVector, hasDL );
					  }else
						  if( animRefId == NULL && appRefId != NULL ){
							 node = new GraphNode( id, appRefId, nodeRefIdVector, hasDL );
							 appRefId = NULL;
						  }else
							  if( animRefId != NULL && appRefId == NULL ){
								  node = new GraphNode( id, nodeRefIdVector, hasDL, animRefId );
								  animRefId = NULL;
							  }else
								  if( animRefId != NULL && appRefId != NULL ){
									 node = new GraphNode( id, appRefId, nodeRefIdVector, hasDL, animRefId );
									 appRefId = NULL;
									 animRefId = NULL;
								  }

					  glGetFloatv( GL_MODELVIEW_MATRIX, node->getTransformationMatrix() );
					  node->setPrimitives( primitives );
					  sg->addGraphNode( node );
					  nodeGraph = nodeGraph->NextSiblingElement( "node" );
					  if( debug ) printf("\n");
				  }while( nodeGraph );
			  }
		}	
}

XMLScene::~XMLScene()
{
	delete( doc );
}

//-------------------------------------------------------

TiXmlElement *XMLScene::findChildByAttribute( TiXmlElement *parent,const char * attr, const char *val )
// Searches within descendants of a parent for a node that has an attribute _attr_ (e.g. an id) with the value _val_
// A more elaborate version of this would rely on XPath expressions
{
	TiXmlElement *child=parent->FirstChildElement();
	int found=0;

	while ( child && !found )
		if ( child->Attribute( attr ) && strcmp( child->Attribute( attr ), val )==0 )
			found=1;
		else
			child=child->NextSiblingElement();

	return child;
}

SceneGraph *XMLScene::getSG(){
	return this->sg;
}