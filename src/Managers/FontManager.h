#pragma once

#include "Manager.h"

class FontManager : Manager {
private:
	FT_Library ft;
	std::map<std::string, FT_Face> fonts;
	std::string current_font;

	FT_Face build_font(std::string font_loc);

public:
	FontManager() {
		if(FT_Init_FreeType(&ft)) log_error(ERROR_FREETYPE_INIT_FAIL);
	}

	~FontManager() {

	}

	void create_font(std::string reference_name, std::string font_loc);
	void use_font(std::string reference_name);
	void set_font_size(int size);



	//GLuint use_font();
	std::map<std::string, GLuint> get_fonts();

};
