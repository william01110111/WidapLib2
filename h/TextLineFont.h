#pragma once

#include "TextBase.h"
#include "Drawable.h"

namespace widap
{

class TextLineFont : public TextBase
{
public:
	TextLineFont(Drawable * drwblIn);
	
	static constexpr double LINE_THICKNESS_RATEO=0.03; // the thickness of the lines that make up the glyphs relative to the height
	static constexpr double BOLD_THICKNESS_RATEO=0.1;
	
protected:
	Drawable * drwbl; // the drawable that the text will be drawn to
	void renderGlyph(char c);
	
private:
	
	// populate the Glyph array
	static void init();
	
	// the actual data for the font is stored in this struct
	struct Glyph
	{
		int lineNum;
		
		V2d* lines[2]; // the actual data; the array is for the start and end points of each line
	};
	
	// where the data is stored
	static Glyph fontData[256];
	
	static constexpr double GLYPH_DIM_RATIO_X=0.5;
	static constexpr double GLYPH_DIM_RATIO_Y=0.5;
	static constexpr double GLYPH_OFFSET_X=0.25;
	static constexpr double GLYPH_OFFSET_Y=0.25;
	
	static bool hasInited;
	
};

}

