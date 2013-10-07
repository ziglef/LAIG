#include "../include/XMLScene.h"
#include "../include/SceneGraph.h"

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
		float posX,posY,posZ;
		char *target;
		float targetX,targetY,targetZ;

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
		perspectiveCamera = cameras->FirstChildElement( "perspective" );

		if( perspectiveCamera ){
			do{
				// ID //
				id = (char *)perspectiveCamera->Attribute( "id" );
				if( id && debug )
					printf("\tPerspective Camera id: %s\n", id);
				else
					if( debug ) printf("\t!! Error parsing perspective camera id !!\n");
			
				// Near //
				if( perspectiveCamera->QueryFloatAttribute( "near", &near )==TIXML_SUCCESS && debug )
					printf("\tNear: %f\n", near);
				else
					if( debug ) printf("\t!! Error parsing Near value !!\n");

				// Far //
				if( perspectiveCamera->QueryFloatAttribute( "far", &far )==TIXML_SUCCESS && debug )
					printf("\tFar: %f\n", far);
				else
					if( debug ) printf("\t!! Error parsing Far value !!\n");

				// Angle //
				if( perspectiveCamera->QueryFloatAttribute( "angle", &angle )==TIXML_SUCCESS && debug )
					printf("\tAngle: %f\n", angle);
				else
					if( debug ) printf("\t!! Error parsing Angle value !!\n");

				// Position //
				pos = (char *)perspectiveCamera->Attribute( "pos" );

				if( pos && sscanf(pos, "%f %f %f", &posX, &posY, &posZ )==3 && debug )
					printf("\tPos: %f %f %f\n", posX, posY, posZ);
				else
					if( debug ) printf("\t!! Error parsing Pos values !!\n");

				// Target //
				target = (char *)perspectiveCamera->Attribute( "target" );

				if( pos && sscanf(target, "%f %f %f", &targetX, &targetY, &targetZ )==3 && debug )
					printf("\tTarget: %f %f %f\n", targetX, targetY, targetZ);
				else
					if( debug ) printf("\t!! Error parsing Target value !!\n");

				// Adds new perspective camera
				this->sg->addCamera( new PerspectiveCamera( id, near, far,angle, pos, posX, posY, posZ, target, targetX, targetY, targetZ ) );

				// Parses the next perspective camera //
				perspectiveCamera = perspectiveCamera->NextSiblingElement( "perspective" );
				if( debug ) printf("\n");
			}while( perspectiveCamera );
		}

		// Process Orthogonal Camera Values //
		orthogonalCamera = cameras->FirstChildElement( "ortho" );

		if( orthogonalCamera ){
			do{
				// ID //
				id = (char *)orthogonalCamera->Attribute( "id" );
				if( id && debug )
					printf("\tOrthogonal camera id: %s\n", id);
				else
					if( debug ) printf("\t!! Error parsing orthogonal camera id !!\n");

				// Near //
				if( orthogonalCamera->QueryFloatAttribute( "near", &near )==TIXML_SUCCESS && debug )
					printf("\tNear: %f\n", near);
				else
					if( debug ) printf("\tError parsing near value !!\n");

				// Far //
				if( orthogonalCamera->QueryFloatAttribute( "far", &far )==TIXML_SUCCESS && debug )
					printf("\tFar: %f\n", far);
				else
					if( debug ) printf("\tError parsing far value !!\n");

				// Left //
				if( orthogonalCamera->QueryFloatAttribute( "left", &left )==TIXML_SUCCESS && debug )
					printf("\tLeft: %f\n", left);
				else
					if( debug ) printf("\tError parsing left value !!\n");

				// Right //
				if( orthogonalCamera->QueryFloatAttribute( "right", &right )==TIXML_SUCCESS && debug )
					printf("\tRight: %f\n", right);
				else
					if( debug ) printf("\tError parsing right value !!\n");

				// Top //
				if( orthogonalCamera->QueryFloatAttribute( "top", &top )==TIXML_SUCCESS && debug )
					printf("\tTop: %f\n", top);
				else
					if( debug ) printf("\tError parsing top value !!\n");

				// Bottom //
				if( orthogonalCamera->QueryFloatAttribute( "bottom", &bottom )==TIXML_SUCCESS && debug )
					printf("\tBottom: %f\n", bottom);
				else
					if( debug ) printf("\tError parsing bottom value !!\n");

				// Adds a new orthogonal camera
				this->sg->addCamera( new OrthogonalCamera( id, near, far, left, right, top, bottom ) );

				// Parses the next orthogonal camera //
				orthogonalCamera = orthogonalCamera->NextSiblingElement( "ortho" );
				if( debug ) printf("\n");
			}while( orthogonalCamera );
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
			char *location;
			char *diffuse;
			float diffuseX, diffuseY, diffuseZ, diffuseAlfa;
			char *ambient;
			float ambientX, ambientY, ambientZ, ambientAlfa;
			char *specular;
			float specularX, specularY, specularZ, specularAlfa;

			// Lighting values //
			char *doublesided;
			char *local;
			char *LightingEnabled;
			char *LightingAmbient;
			float LightingAmbientX, LightingAmbientY, LightingAmbientZ, LightingAmbientAlfa;

			// Spot Lights values //
			float angle;
			float exponent;
			char *direction;
			float directionX, directionY, directionZ;

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
			if( sscanf(LightingAmbient, "%f %f %f %f", &LightingAmbientX, &LightingAmbientY, &LightingAmbientZ, &LightingAmbientAlfa )==4 && debug )
					printf("\tAmbient: %f %f %f %f\n\n", LightingAmbientX, LightingAmbientY, LightingAmbientZ, LightingAmbientAlfa );
				else
					if( debug ) printf("\t!! Error parsing ambient values !!\n");

			// Save the Lighting values in the sceneGraph //
			sg->addLightingValues( doublesided, local, LightingEnabled, LightingAmbient, LightingAmbientX, LightingAmbientY, LightingAmbientZ, LightingAmbientAlfa );

			// Process Omni Lighting Values //
			omniLighting = lighting->FirstChildElement( "omni" );
			if( omniLighting ){
				do{
					id = (char *)omniLighting->Attribute( "id" );
					enabled = (char *)omniLighting->Attribute( "enabled" );
					location = (char *)omniLighting->Attribute( "location" );
					ambient = (char *)omniLighting->Attribute( "ambient" );
					diffuse = (char *)omniLighting->Attribute( "diffuse" );
					specular = (char *)omniLighting->Attribute( "specular" );

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
					if( location && debug )
						printf("\tLocal: %s\n",location);
					else
						if( debug ) printf("\t!! Error parsing location value !!\n");

					// Ambient //
					if( sscanf(ambient, "%f %f %f %f", &ambientX, &ambientY, &ambientZ, &ambientAlfa )==4 && debug )
						printf("\tAmbient: %f %f %f %f\n", ambientX, ambientY, ambientZ, ambientAlfa);
					else
						if( debug ) printf("\t!! Error parsing ambient values !!\n");

					// Diffuse //
					if( sscanf(diffuse, "%f %f %f %f", &diffuseX, &diffuseY, &diffuseZ, &diffuseAlfa )==4 && debug )
						printf("\tDiffuse: %f %f %f %f\n", diffuseX, diffuseY, diffuseZ, diffuseAlfa);
					else
						if( debug ) printf("\t!! Error parsing diffuse values !!\n");

					// Specular //
					if( sscanf(specular,"%f %f %f %f", &specularX, &specularY, &specularZ, &specularAlfa )==4 && debug )
						printf("\tSpecular: %f %f %f %f\n\n", specularX, specularY, specularZ, specularAlfa);
					else
						if( debug ) printf("\t!! Error parsing specular values !!\n");

					// Adds the omni light to the omni lights map //
					this->sg->addLight( new OmniLight( id, enabled, location, diffuse, diffuseX, diffuseY, diffuseZ, diffuseAlfa,  ambient, ambientX, ambientY, ambientZ, ambientAlfa, specular, specularX, specularY, specularZ, specularAlfa ) );

					// Parses the next omni light //
					omniLighting = omniLighting->NextSiblingElement( "omni" );
					if( debug ) printf("\n");
				}while( omniLighting );
			}

			// Process spot Lighting values //
			spotLighting = lighting->FirstChildElement( "spot" );
			if( spotLighting ){
				do{
					id = (char *)spotLighting->Attribute( "id" );
					enabled = (char *)spotLighting->Attribute( "enabled" );
					location = (char *)spotLighting->Attribute( "location" );
					ambient = (char *)spotLighting->Attribute( "ambient" );
					diffuse = (char *)spotLighting->Attribute( "diffuse" );
					specular = (char *)spotLighting->Attribute( "specular" );
					direction = (char *)spotLighting->Attribute( "direction" );

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
					if( location && debug )
						printf("\tLocal: %s\n", location);
					else
						if( debug ) printf("\t!! Error parsing location value !!\n");

					// Ambient //
					if( sscanf(ambient, "%f %f %f %f", &ambientX, &ambientY, &ambientZ, &ambientAlfa )==4 && debug )
						printf("\tAmbient: %f %f %f %f\n", ambientX, ambientY, ambientZ, ambientAlfa);
					else
						if( debug ) printf("\t!! Error parsing ambient values !!\n");

					// Diffuse //
					if( sscanf(diffuse, "%f %f %f %f", &diffuseX, &diffuseY, &diffuseZ, &diffuseAlfa )==4 && debug )
						printf("\tDiffuse: %f %f %f %f\n", diffuseX, diffuseY, diffuseZ, diffuseAlfa);
					else
						if( debug ) printf("\t!! Error parsing diffuse values !!\n");

					// Specular //
					if( sscanf(specular, "%f %f %f %f", &specularX, &specularY, &specularZ, &specularAlfa )==4 && debug )
						printf("\tSpecular: %f %f %f %f\n",specularX,specularY,specularZ,specularAlfa);
					else
						if( debug ) printf("\t!! Error parsing specular values !!\n");

					// Angle //
					if( spotLighting->QueryFloatAttribute( "angle", &angle )==TIXML_SUCCESS && debug )
						printf("\tAngle: %f\n", angle);
					else
						if( debug ) printf("\t!! Error parsing angle value !!\n");

					// Exponent //
					if( spotLighting->QueryFloatAttribute( "exponent", &exponent )==TIXML_SUCCESS && debug )
						printf("\tExponent: %f\n", exponent);
					else
						if( debug ) printf("\t!! Error parsing exponent value !!\n");

					// Direction //
					if( sscanf(direction, "%f %f %f %f", &directionX, &directionY, &directionZ )==3 && debug )
						printf("\tDirection: %f %f %f\n", directionX, directionY, directionZ);
					else
						if( debug ) printf("\t!! Error parsing direction values !!\n");

					// Adds the spot light to the spot lights map //
					this->sg->addLight( new SpotLight( id, enabled, location, diffuse, diffuseX, diffuseY, diffuseZ, diffuseAlfa,  ambient, ambientX, ambientY, ambientZ, ambientAlfa, specular, specularX, specularY, specularZ, specularAlfa, angle, exponent, direction, directionX, directionY, directionZ ) );

					// Parses the next spot light //
					spotLighting = spotLighting->NextSiblingElement( "spot" );
					if( debug ) printf("\n");
				}while( spotLighting );
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

					// Adds the texture to the textures vector //
					texturesVector.push_back( *( new Texture( id, file ) ));

					// Parses the next texture //
					textureTextures = textureTextures->NextSiblingElement( "texture" );
					if( debug ) printf("\n");
				}while( textureTextures );
				//Saves the textures vector in the scene graph //
				this->sg->addTextures( texturesVector );
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
			float emissiveX, emissiveY, emissiveZ, emissiveAlfa;
			char *diffuse;
			float diffuseX, diffuseY, diffuseZ, diffuseAlfa;
			char *ambient;
			float ambientX, ambientY, ambientZ, ambientAlfa;
			char *specular;
			float specularX, specularY, specularZ, specularAlfa;
			float shininess;
			char *textureref;
			float texlength_s;
			float texlength_t;

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
					if( sscanf(emissive, "%f %f %f %f", &emissiveX, &emissiveY, &emissiveZ, &emissiveAlfa )==4 && debug )
						printf("\tEmissive: %f %f %f %f\n", emissiveX, emissiveY, emissiveZ, emissiveAlfa);
					else
						if( debug ) printf("\t!! Error parsing Emissive values !!\n");

					// Ambient //
					if( sscanf(ambient, "%f %f %f %f", &ambientX, &ambientY, &ambientZ, &ambientAlfa )==4 && debug )
						printf("\tAmbient: %f %f %f %f\n", ambientX, ambientY, ambientZ, ambientAlfa);
					else
						if( debug ) printf("\t!! Error parsing ambient values !!\n");

					// Diffuse //
					if( sscanf(diffuse, "%f %f %f %f", &diffuseX, &diffuseY, &diffuseZ, &diffuseAlfa )==4 && debug )
						printf("\tDiffuse: %f %f %f %f\n", diffuseX, diffuseY, diffuseZ, diffuseAlfa);
					else
						if( debug ) printf("\t!! Error parsing diffuse values !!\n");

					// Specular //
					if( sscanf(specular, "%f %f %f %f", &specularX, &specularY, &specularZ, &specularAlfa )==4 && debug )
						printf("\tSpecular: %f %f %f %f\n", specularX, specularY, specularZ, specularAlfa);
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
					appearencesVector.push_back( *( new Appearence( id, emissive, emissiveX, emissiveY, emissiveZ, emissiveAlfa, diffuse, diffuseX, diffuseY, diffuseZ, diffuseAlfa, ambient, ambientX, ambientY, ambientZ, ambientAlfa, specular, specularX, specularY, specularZ, specularAlfa, shininess, textureref, texlength_s, texlength_t ) ));

					appearanceAppearances = appearanceAppearances->NextSiblingElement( "appearance" );
					if( debug ) printf("\n");
				}while( appearanceAppearances );
				//Saves the appearance vector in the scene graph //
				this->sg->addAppearences( appearencesVector );
			}
		}

		// Graph Block //
		if( sceneGraph == NULL && debug )
			printf("Graph block not found!\n");
		else{
			  if( debug ) printf("Processing Graph:\n");

			  // Graph values //
			  char *rootid;

			  // Node values //
			  char *id;

			  // AppearanceRef Values //
			  char *appRefId;

			  // Tranformation Values //
			  char *translate;
			  float translateX, translateY, translateZ;
			  char *scale;
			  float scaleX, scaleY, scaleZ;
			  char *rotateAxis;
			  float rotateAngle;

			  // Children Values //
			  char *nodeRefId;

			  // Process the Graph ID //
			  rootid = (char*)sceneGraph->Attribute( "rootid" );
			  if( rootid && debug )
				  printf("\tGraph root ID: %s\n\n", rootid);
			  else
				  if( debug ) printf("\t!! Error parsing Graph root ID !!\n");

			  // Process Nodes of the Graph //
			  nodeGraph = sceneGraph->FirstChildElement( "node" );
			  if( nodeGraph ){
				  do{
					  id = (char *)nodeGraph->Attribute( "id" );
					  transformsNodeGraph = nodeGraph->FirstChildElement( "transforms" );
					  translateTransformsNodeGraph = transformsNodeGraph->FirstChildElement( "translate" );
					  scaleTransformsNodeGraph = transformsNodeGraph->FirstChildElement( "scale" );
					  rotateTransformsNodeGraph = transformsNodeGraph->FirstChildElement( "rotate" );
					  appearanceRefNodeGraph = nodeGraph->FirstChildElement( "appearanceref" );
					  childrenNodeGraph = nodeGraph->FirstChildElement( "children" );
					  noderefChildrenNodeGraph = childrenNodeGraph->FirstChildElement( "noderef" );

					  // Node ID //
					  if( id && debug )
						  printf("\tNode ID: %s\n", id);
					  else
						  if( debug ) printf("\t!! Error parsing node ID !!\n");

					  // Tranformations //

					  // Translate //
					  if( translateTransformsNodeGraph ){
						  translate = (char *)translateTransformsNodeGraph->Attribute( "to" );
						if( sscanf(translate, "%f %f %f %f", &translateX, &translateY, &translateZ )==3 && debug )
							printf("\tTranslate: %f %f %f\n", translateX, translateY, translateZ);
						else
							if( debug ) printf("\t!! Error parsing Translate values !!\n");
					  }

					  // Scale //
					  if( scaleTransformsNodeGraph ){
						  scale = (char *)scaleTransformsNodeGraph->Attribute( "factor" );
						if( sscanf(scale, "%f %f %f %f", &scaleX, &scaleY, &scaleZ )==3 && debug )
							printf("\tScale: %f %f %f\n", scaleX, scaleY, scaleZ);
						else
							if( debug ) printf("\t!! Error parsing scale values !!\n");
					  }

					  // Rotate //
					  if( rotateTransformsNodeGraph ){
						  // Axis //
						  rotateAxis = (char *)rotateTransformsNodeGraph->Attribute( "axis" );
						  if( rotateAxis && debug )
							  printf("\tRotation Axis: %s ", rotateAxis);
						  else
							  if( debug ) printf("\t!! Error parsing rotation angle !!\n");

						  // Angle //
						  if( rotateTransformsNodeGraph->QueryFloatAttribute( "angle", &rotateAngle )==TIXML_SUCCESS && debug )
							  printf("\tRotation Angle: %f\n",rotateAngle);
						  else
							  if( debug ) printf("\t!! Error parsing rotation angle !!\n");
					  }

					  // Appearance Reference //
					  if( appearanceRefNodeGraph ){
						  appRefId = (char *)appearanceRefNodeGraph->Attribute( "id" );
						  if( appRefId && debug )
							  printf("\tAppearance Reference: %s\n", appRefId);
						  else
							  if( debug ) printf("\t!! Error parsing appearance reference !!\n");
					  }

					  // Children //
					  if( noderefChildrenNodeGraph ){
						  do{
							  // Reference ID //
							  nodeRefId = (char *)noderefChildrenNodeGraph->Attribute( "id" );
							  if( nodeRefId && debug )
								  printf("\tNode reference ID: %s\n", nodeRefId);
							  else
								  if( debug ) printf("\t!! Error parsing node reference ID !!\n");
							  noderefChildrenNodeGraph = noderefChildrenNodeGraph->NextSiblingElement( "noderef" );
						  }while( noderefChildrenNodeGraph );
					  }
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