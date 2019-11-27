#pragma once

#include "FontManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "ModelManager.h"
#include "SettingsManager.h"

class GameManager {
private:
	ShaderManager 	* shader_manager;
	TextureManager 	* texture_manager;
	FontManager  	* font_manager;
	ModelManager	* model_manager;
	SettingsManager	* settings_manager;

	void setup_managers();
	void deconstruct_managers();
	void setup_manager_shader();
	void setup_manager_texture();
	void setup_manager_font();
	void setup_manager_model();
	void setup_manager_settings();

public:
	GameManager() {
		setup_managers();
		setup_manager_shader();
		setup_manager_texture();
		setup_manager_font();
		setup_manager_model();
		setup_manager_settings();
	}

	~GameManager() {
		deconstruct_managers();
	}

	ShaderManager 	* getShaderManager() 	{ return shader_manager;	}
	TextureManager	* getTextureManager() 	{ return texture_manager;	}
	FontManager 	* getFontManager() 		{ return font_manager;		}
	ModelManager	* getModelManager()		{ return model_manager;		}
	SettingsManager	* getSettingsManager()	{ return settings_manager;	}

};
