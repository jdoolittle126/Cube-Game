#pragma once

#include "Manager.h"

class TextManager : Manager {
private:
	FT_Library ft;
	std::map<std::string, GLuint> fonts;
	GLuint build_shader(std::string fragment_loc, std::string vertex_loc);

public:
	TextManager() {
		if(FT_Init_FreeType(&ft)) log_error(ERROR_FREETYPE_INIT_FAIL);
	}

	~TextManager() {

	}

	void create_font();
	GLuint use_font();
	std::map<std::string, GLuint> get_fonts();

};
