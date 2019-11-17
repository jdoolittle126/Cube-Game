#include "TextManager.h"

FT_Face TextManager::build_font(std::string font_loc) {
	FT_Face face;
	if(FT_New_Face(ft, font_loc.c_str(), 0, &face)) log_error(ERROR_FREETYPE_FONT_OPEN);
	return face;
}

void TextManager::create_font(std::string reference_name, std::string font_loc) {
	fonts.insert(std::pair<std::string, FT_Face>(reference_name, build_font(font_loc)));
}

void TextManager::set_font_size(int size) {

	//FT_Set_Pixel_Sizes(face, 0, 48);
}
