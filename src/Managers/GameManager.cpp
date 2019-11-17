#include "GameManager.h"

//ASSETS ARE CREATED

void GameManager::setup_managers() {
	shader_manager	= new ShaderManager();
	texture_manager	= new TextureManager();
	text_manager	= new TextManager();
	model_manager	= new ModelManager();
	settings_manager= new SettingsManager();
}

void GameManager::deconstruct_managers() {
	delete 	shader_manager;
	delete 	texture_manager;
	delete 	text_manager;
	delete 	model_manager;
	delete 	settings_manager;
}

void GameManager::setup_manager_shader() {
	shader_manager->create_shader("Debug", "src/GLSL/Shaders/Fragment/debug.fragment", "src/GLSL/Shaders/Vertex/debug.vertex");
	shader_manager->create_shader("WorldObj", "src/GLSL/Shaders/Fragment/world_obj.fragment", "src/GLSL/Shaders/Vertex/world_obj.vertex");
	shader_manager->create_shader("Tile", "src/GLSL/Shaders/Fragment/tile.fragment", "src/GLSL/Shaders/Vertex/tile.vertex");
	shader_manager->create_shader("Text", "src/GLSL/Shaders/Fragment/text.fragment", "src/GLSL/Shaders/Vertex/text.vertex");
}

void GameManager::setup_manager_texture() {

}

void GameManager::setup_manager_text() {

}


void GameManager::setup_manager_model() {

}

void GameManager::setup_manager_settings() {

}


