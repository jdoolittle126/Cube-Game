#pragma once

#include "Manager.h"

class TextManager : Manager {
private:
	FT_Library ft;
	std::map<std::string, FT_Face> fonts;
	std::string current_font;

	FT_Face build_font(std::string font_loc);

public:
	TextManager() {
		if(FT_Init_FreeType(&ft)) log_error(ERROR_FREETYPE_INIT_FAIL);
	}

	~TextManager() {

	}

	void create_font(std::string reference_name, std::string font_loc);
	void use_font();
	void set_font_size(int size);


	//GLuint use_font();
	std::map<std::string, GLuint> get_fonts();

};
