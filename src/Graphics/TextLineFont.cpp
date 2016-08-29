#include "../../h/Graphics/TextLineFont.h"
#include "../../h/Math/SimpMath.h"
#include "../../h/Mscl/Error.h"

namespace widap
{

TextLineFont::Glyph TextLineFont::fontData[];
bool TextLineFont::hasInited=0;

void TextLineFont::init()
{
	int i, j;
	
	const double Y[9]={0.0, 0.25, 0.375, 0.625, 0.75, 1.0, 0.5, -0.2, -0.4};
	const double X[5]={0.0, 0.5, 1.0, 0.25, 0.75}; //normal x and y positions
	
	for (int i=0; i<256; ++i)
	{ //set all glyphs to skull and cross bones (unknown glyph)
		fontData[i].lineNum=13;
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[1];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[1];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[5];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[4];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[4];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[2];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[2];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[1];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[1];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[2];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[2];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[4];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[4];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=0.6;
		fontData[i].lines[0][j].y=Y[3];
		fontData[i].lines[1][j].x=0.8;
		fontData[i].lines[1][j].y=Y[4];
		++j;
		fontData[i].lines[0][j].x=0.8;
		fontData[i].lines[0][j].y=Y[3];
		fontData[i].lines[1][j].x=0.6;
		fontData[i].lines[1][j].y=Y[4];
		++j;
		fontData[i].lines[0][j].x=0.2;
		fontData[i].lines[0][j].y=Y[3];
		fontData[i].lines[1][j].x=0.4;
		fontData[i].lines[1][j].y=Y[4];
		++j;
		fontData[i].lines[0][j].x=0.4;
		fontData[i].lines[0][j].y=Y[3];
		fontData[i].lines[1][j].x=0.2;
		fontData[i].lines[1][j].y=Y[4];
		++j;
		fontData[i].lines[0][j].x=0.3;
		fontData[i].lines[0][j].y=Y[2];
		fontData[i].lines[1][j].x=0.7;
		fontData[i].lines[1][j].y=Y[2];
	}
	
	
	///special chars
	
	{ ///[space]
		i=32; fontData[i].lineNum=0; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
	}
	
	{ ///!
		i=33; fontData[i].lineNum=5; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[5];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[2];
		++j;
		fontData[i].lines[0][j].x=0.4;
		fontData[i].lines[0][j].y=0.05;
		fontData[i].lines[1][j].x=0.5;
		fontData[i].lines[1][j].y=0.1;
		++j;
		fontData[i].lines[0][j].x=0.5;
		fontData[i].lines[0][j].y=0.1;
		fontData[i].lines[1][j].x=0.6;
		fontData[i].lines[1][j].y=0.05;
		++j;
		fontData[i].lines[0][j].x=0.6;
		fontData[i].lines[0][j].y=0.05;
		fontData[i].lines[1][j].x=0.5;
		fontData[i].lines[1][j].y=0;
		++j;
		fontData[i].lines[0][j].x=0.5;
		fontData[i].lines[0][j].y=0;
		fontData[i].lines[1][j].x=0.4;
		fontData[i].lines[1][j].y=0.05;
	}
	
	{ ///"
		i=34; fontData[i].lineNum=2; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[3];
		fontData[i].lines[0][j].y=Y[4];
		fontData[i].lines[1][j].x=X[3];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[4];
		fontData[i].lines[0][j].y=Y[4];
		fontData[i].lines[1][j].x=X[4];
		fontData[i].lines[1][j].y=Y[5];
	}
	
	{ ///#
		i=35; fontData[i].lineNum=4; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=0.3;
		fontData[i].lines[0][j].y=0;
		fontData[i].lines[1][j].x=0.3;
		fontData[i].lines[1][j].y=1;
		++j;
		fontData[i].lines[0][j].x=0.7;
		fontData[i].lines[0][j].y=0;
		fontData[i].lines[1][j].x=0.7;
		fontData[i].lines[1][j].y=1;
		++j;
		fontData[i].lines[0][j].x=0;
		fontData[i].lines[0][j].y=0.3;
		fontData[i].lines[1][j].x=1;
		fontData[i].lines[1][j].y=0.3;
		++j;
		fontData[i].lines[0][j].x=0;
		fontData[i].lines[0][j].y=0.7;
		fontData[i].lines[1][j].x=1;
		fontData[i].lines[1][j].y=0.7;
	}
	
	{ ///%
		i=37; fontData[i].lineNum=9; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=0;
		fontData[i].lines[0][j].y=0;
		fontData[i].lines[1][j].x=1;
		fontData[i].lines[1][j].y=1;
		++j;
		fontData[i].lines[0][j].x=0.6;
		fontData[i].lines[0][j].y=0.1;
		fontData[i].lines[1][j].x=0.8;
		fontData[i].lines[1][j].y=0.2;
		++j;
		fontData[i].lines[0][j].x=0.8;
		fontData[i].lines[0][j].y=0.2;
		fontData[i].lines[1][j].x=1.0;
		fontData[i].lines[1][j].y=0.1;
		++j;
		fontData[i].lines[0][j].x=1.0;
		fontData[i].lines[0][j].y=0.1;
		fontData[i].lines[1][j].x=0.8;
		fontData[i].lines[1][j].y=0.0;
		++j;
		fontData[i].lines[0][j].x=0.8;
		fontData[i].lines[0][j].y=0.0;
		fontData[i].lines[1][j].x=0.6;
		fontData[i].lines[1][j].y=0.1;
		++j;
		fontData[i].lines[0][j].x=0.0;
		fontData[i].lines[0][j].y=0.9;
		fontData[i].lines[1][j].x=0.2;
		fontData[i].lines[1][j].y=1.0;
		++j;
		fontData[i].lines[0][j].x=0.2;
		fontData[i].lines[0][j].y=1.0;
		fontData[i].lines[1][j].x=0.4;
		fontData[i].lines[1][j].y=0.9;
		++j;
		fontData[i].lines[0][j].x=0.4;
		fontData[i].lines[0][j].y=0.9;
		fontData[i].lines[1][j].x=0.2;
		fontData[i].lines[1][j].y=0.8;
		++j;
		fontData[i].lines[0][j].x=0.2;
		fontData[i].lines[0][j].y=0.8;
		fontData[i].lines[1][j].x=0.0;
		fontData[i].lines[1][j].y=0.9;
	}
	
	{ ///'
		i=39; fontData[i].lineNum=1; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[4];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[5];
	}
	
	{ ///(
		i=40; fontData[i].lineNum=3; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[2];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[2];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[3];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[3];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[5];
	}
	
	{ ///)
		i=41; fontData[i].lineNum=3; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[2];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[2];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[3];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[3];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[5];
	}
	
	{ ///*
		i=42; fontData[i].lineNum=3; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=0.5;
		fontData[i].lines[0][j].y=0.3;
		fontData[i].lines[1][j].x=0.5;
		fontData[i].lines[1][j].y=0.7;
		++j;
		fontData[i].lines[0][j].x=0.1;
		fontData[i].lines[0][j].y=0.4;
		fontData[i].lines[1][j].x=0.9;
		fontData[i].lines[1][j].y=0.6;
		++j;
		fontData[i].lines[0][j].x=0.9;
		fontData[i].lines[0][j].y=0.4;
		fontData[i].lines[1][j].x=0.1;
		fontData[i].lines[1][j].y=0.6;
	}
	
	{ ///+
		i=43; fontData[i].lineNum=2; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=0.1;
		fontData[i].lines[0][j].y=0.5;
		fontData[i].lines[1][j].x=0.9;
		fontData[i].lines[1][j].y=0.5;
		++j;
		fontData[i].lines[0][j].x=0.5;
		fontData[i].lines[0][j].y=0.3;
		fontData[i].lines[1][j].x=0.5;
		fontData[i].lines[1][j].y=0.7;
	}
	
	{ ///,
		i=44; fontData[i].lineNum=1; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=0.5;
		fontData[i].lines[0][j].y=0.1;
		fontData[i].lines[1][j].x=0.3;
		fontData[i].lines[1][j].y=-0.1;
	}
	
	{ ///-
		i=45; fontData[i].lineNum=1; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=0.1;
		fontData[i].lines[0][j].y=0.5;
		fontData[i].lines[1][j].x=0.9;
		fontData[i].lines[1][j].y=0.5;
	}
	
	{ ///.
		i=46; fontData[i].lineNum=4; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=0.3;
		fontData[i].lines[0][j].y=0.05;
		fontData[i].lines[1][j].x=0.4;
		fontData[i].lines[1][j].y=0.1;
		++j;
		fontData[i].lines[0][j].x=0.4;
		fontData[i].lines[0][j].y=0.1;
		fontData[i].lines[1][j].x=0.5;
		fontData[i].lines[1][j].y=0.05;
		++j;
		fontData[i].lines[0][j].x=0.5;
		fontData[i].lines[0][j].y=0.05;
		fontData[i].lines[1][j].x=0.4;
		fontData[i].lines[1][j].y=0;
		++j;
		fontData[i].lines[0][j].x=0.4;
		fontData[i].lines[0][j].y=0;
		fontData[i].lines[1][j].x=0.3;
		fontData[i].lines[1][j].y=0.05;
	}
	
	{ /// /
		i=47; fontData[i].lineNum=1; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[5];
	}
	
	
	///numbers
	
	{ ///0
		i=48; fontData[i].lineNum=7; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[5];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[4];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[4];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[1];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[1];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[0];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[1];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[1];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[4];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[4];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[4];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[1];
	}
	
	{ ///1
		i++; fontData[i].lineNum=3; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[0];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[5];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[4];
	}
	
	{ ///2
		i++; fontData[i].lineNum=6; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[4];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[5];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[4];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[4];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[3];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[3];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[1];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[1];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[0];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[0];
	}
	
	{ ///3
		i++; fontData[i].lineNum=9; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[4];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[5];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[4];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[4];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[3];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[3];
		fontData[i].lines[1][j].x=0.75;
		fontData[i].lines[1][j].y=0.5;
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=0.5;
		fontData[i].lines[1][j].x=0.75;
		fontData[i].lines[1][j].y=0.5;
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[2];
		fontData[i].lines[1][j].x=0.75;
		fontData[i].lines[1][j].y=0.5;
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[2];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[1];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[1];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[0];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[1];
	}
	
	{ ///4
		i++; fontData[i].lineNum=3; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[6];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[6];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[6];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[5];
	}
	
	{ ///5
		i++; fontData[i].lineNum=7; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[5];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[5];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[3];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[3];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[3];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[3];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[2];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[2];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[1];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[1];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[0];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[0];
	}
	
	{ ///6
		i++; fontData[i].lineNum=7; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[2];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[2];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[1];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[2];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[3];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[3];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[2];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[2];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[1];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[1];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[0];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[1];
	}
	
	{ ///7
		i++; fontData[i].lineNum=4; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[5];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[5];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[4];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[4];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[2];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[2];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[0];
	}
	
	{ ///8
		i++; fontData[i].lineNum=10; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[5];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[4];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[4];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[3];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[3];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[4];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[4];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[2];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[1];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[2];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[3];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[3];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[2];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[2];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[1];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[1];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[0];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[1];
	}
	
	{ ///9
		i++; fontData[i].lineNum=7; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[3];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[0];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[3];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[4];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[3];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[2];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[2];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[3];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[3];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[4];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[4];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[5];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[4];
	}
	
	
	///special chars
	
	{ ///:
		i=58; fontData[i].lineNum=8; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=0.3;
		fontData[i].lines[0][j].y=0.25;
		fontData[i].lines[1][j].x=0.4;
		fontData[i].lines[1][j].y=0.3;
		++j;
		fontData[i].lines[0][j].x=0.4;
		fontData[i].lines[0][j].y=0.3;
		fontData[i].lines[1][j].x=0.5;
		fontData[i].lines[1][j].y=0.25;
		++j;
		fontData[i].lines[0][j].x=0.5;
		fontData[i].lines[0][j].y=0.25;
		fontData[i].lines[1][j].x=0.4;
		fontData[i].lines[1][j].y=0.2;
		++j;
		fontData[i].lines[0][j].x=0.4;
		fontData[i].lines[0][j].y=0.2;
		fontData[i].lines[1][j].x=0.3;
		fontData[i].lines[1][j].y=0.25;
		++j;
		fontData[i].lines[0][j].x=0.3;
		fontData[i].lines[0][j].y=0.65;
		fontData[i].lines[1][j].x=0.4;
		fontData[i].lines[1][j].y=0.7;
		++j;
		fontData[i].lines[0][j].x=0.4;
		fontData[i].lines[0][j].y=0.7;
		fontData[i].lines[1][j].x=0.5;
		fontData[i].lines[1][j].y=0.65;
		++j;
		fontData[i].lines[0][j].x=0.5;
		fontData[i].lines[0][j].y=0.65;
		fontData[i].lines[1][j].x=0.4;
		fontData[i].lines[1][j].y=0.6;
		++j;
		fontData[i].lines[0][j].x=0.4;
		fontData[i].lines[0][j].y=0.6;
		fontData[i].lines[1][j].x=0.3;
		fontData[i].lines[1][j].y=0.65;
	}
	
	{ ///;
		i=59; fontData[i].lineNum=5; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=0.3;
		fontData[i].lines[0][j].y=0.65;
		fontData[i].lines[1][j].x=0.4;
		fontData[i].lines[1][j].y=0.7;
		++j;
		fontData[i].lines[0][j].x=0.4;
		fontData[i].lines[0][j].y=0.7;
		fontData[i].lines[1][j].x=0.5;
		fontData[i].lines[1][j].y=0.65;
		++j;
		fontData[i].lines[0][j].x=0.5;
		fontData[i].lines[0][j].y=0.65;
		fontData[i].lines[1][j].x=0.4;
		fontData[i].lines[1][j].y=0.6;
		++j;
		fontData[i].lines[0][j].x=0.4;
		fontData[i].lines[0][j].y=0.6;
		fontData[i].lines[1][j].x=0.3;
		fontData[i].lines[1][j].y=0.65;
		++j;
		fontData[i].lines[0][j].x=0.5;
		fontData[i].lines[0][j].y=0.3;
		fontData[i].lines[1][j].x=0.3;
		fontData[i].lines[1][j].y=0.1;
	}
	
	{ ///<
		i=60; fontData[i].lineNum=2; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[6];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[1];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[6];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[4];
	}
	
	{ ///=
		i=61; fontData[i].lineNum=2; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[2];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[2];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[3];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[3];
	}
	
	{ ///>
		i=62; fontData[i].lineNum=2; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[6];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[1];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[6];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[4];
	}
	
	
	///Capital letters
	
	{ ///A
		i=65; fontData[i].lineNum=3; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=lerp(Y[2], Y[0], Y[4], X[0], X[1]);
		fontData[i].lines[0][j].y=Y[2];
		fontData[i].lines[1][j].x=lerp(Y[2], Y[0], Y[4], X[2], X[1]);
		fontData[i].lines[1][j].y=Y[2];
	}
	
	{ ///B
		i++; fontData[i].lineNum=9;  delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[5];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[5];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[4];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[4];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[3];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[3];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[3];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[3];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[2];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[2];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[1];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[1];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[0];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[0];
	}
	
	{ ///C
		i++; fontData[i].lineNum=5; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[1];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[0];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[1];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[1];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[4];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[4];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[5];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[4];
	}
	
	{ ///D
		i++; fontData[i].lineNum=6; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[5];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[5];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[3];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[3];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[2];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[2];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[0];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[0];
	}
	
	{ ///E
		i++; fontData[i].lineNum=4; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[5];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[6];
		fontData[i].lines[1][j].x=0.75;
		fontData[i].lines[1][j].y=Y[6];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[0];
	}
	
	{ ///F
		i++; fontData[i].lineNum=3; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[5];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[6];
		fontData[i].lines[1][j].x=0.75;
		fontData[i].lines[1][j].y=Y[6];
	}
	
	{ ///G
		i++; fontData[i].lineNum=7; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[1];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[0];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[1];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[1];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[4];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[4];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[5];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[4];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[6];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[6];
		fontData[i].lines[1][j].x=X[4];
		fontData[i].lines[1][j].y=Y[6];
	}
	
	{ ///H
		i++; fontData[i].lineNum=3; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=0.5;
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=0.5;
	}
	
	{ ///I
		i++; fontData[i].lineNum=3; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[5];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[0];
	}
	
	{ ///J
		i++; fontData[i].lineNum=4; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[1];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[5];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[1];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[0];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[1];
	}
	
	{ ///K
		i++; fontData[i].lineNum=4; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[3];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[3];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[3];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[3];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[0];
	}
	
	{ ///L
		i++; fontData[i].lineNum=2; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[0];
	}
	
	{ ///M
		i++; fontData[i].lineNum=4; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[5];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[2];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[5];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[2];
	}
	
	{ ///N
		i++; fontData[i].lineNum=3; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[5];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[0];
	}
	
	{ ///O
		i++; fontData[i].lineNum=6; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[1];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[0];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[1];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[1];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[4];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[4];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[5];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[4];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[1];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[4];
	}
	
	{ ///P
		i++; fontData[i].lineNum=6; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[5];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[5];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[4];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[4];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[3];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[3];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[2];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[2];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[2];
	}
	
	{ ///Q
		i++; fontData[i].lineNum=7; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[1];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[0];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[1];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[1];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[4];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[4];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[5];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[4];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[1];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[4];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[1];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[0];
	}
	
	{ ///R
		i++; fontData[i].lineNum=7; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[5];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[5];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[4];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[4];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[3];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[3];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[2];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[2];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[2];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[2];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[0];
	}
	
	{ ///S
		i++; fontData[i].lineNum=7; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[4];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[5];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[4];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[4];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[3];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[3];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[2];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[2];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[1];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[1];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[0];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[1];
	}
	
	{ ///T
		i++; fontData[i].lineNum=2; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[5];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[5];
	}
	
	{ ///U
		i++; fontData[i].lineNum=4; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[1];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[0];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[1];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[1];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[1];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[5];
	}
	
	{ ///V
		i++; fontData[i].lineNum=2; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[5];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[0];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[5];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[0];
	}
	
	{ ///W
		i++; fontData[i].lineNum=4; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[3];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[3];
	}
	
	{ ///X
		i++; fontData[i].lineNum=2; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[5];
	}
	
	{ ///Y
		i++; fontData[i].lineNum=5; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[2];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[2];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[3];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[2];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[3];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[3];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[3];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[5];
	}
	
	{ ///Z
		i++; fontData[i].lineNum=4; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[5];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[5];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[0];
		++j;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[0];
		++j;
		fontData[i].lines[0][j].x=X[3];
		fontData[i].lines[0][j].y=Y[6];
		fontData[i].lines[1][j].x=X[4];
		fontData[i].lines[1][j].y=Y[6];
	}
	
	
	///special chars
	
	{ ///?
		i=63; fontData[i].lineNum=9; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[0];
		fontData[i].lines[0][j].y=Y[4];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[5];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[5];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[4];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[4];
		fontData[i].lines[1][j].x=X[2];
		fontData[i].lines[1][j].y=Y[3];
		++j;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[3];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[2];
		++j;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[2];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[1];
		++j;
		fontData[i].lines[0][j].x=0.4;
		fontData[i].lines[0][j].y=0.05;
		fontData[i].lines[1][j].x=0.5;
		fontData[i].lines[1][j].y=0.1;
		++j;
		fontData[i].lines[0][j].x=0.5;
		fontData[i].lines[0][j].y=0.1;
		fontData[i].lines[1][j].x=0.6;
		fontData[i].lines[1][j].y=0.05;
		++j;
		fontData[i].lines[0][j].x=0.6;
		fontData[i].lines[0][j].y=0.05;
		fontData[i].lines[1][j].x=0.5;
		fontData[i].lines[1][j].y=0;
		++j;
		fontData[i].lines[0][j].x=0.5;
		fontData[i].lines[0][j].y=0;
		fontData[i].lines[1][j].x=0.4;
		fontData[i].lines[1][j].y=0.05;
	}
	
	{ /// [backslash]
		i=92; fontData[i].lineNum=1; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[2];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[0];
		fontData[i].lines[1][j].y=Y[5];
	}
	
	{ ///_
		i=95; fontData[i].lineNum=1; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=0;
		fontData[i].lines[0][j].y=-0.1;
		fontData[i].lines[1][j].x=1;
		fontData[i].lines[1][j].y=-0.1;
	}
	
	for (i=0; i<26; ++i)
	{ //make smalls the same as capitals
		delete[] fontData[i].lines[0];
		delete[] fontData[i].lines[1];
		fontData[i+97].lineNum=fontData[i+65].lineNum;
		fontData[i+97].lines[0]=fontData[i+65].lines[0];
		fontData[i+97].lines[1]=fontData[i+65].lines[1];
	}
	
	///special chars
	
	{ ///|
		i=124; fontData[i].lineNum=1; delete[] fontData[i].lines[0]; delete[] fontData[i].lines[1];
		fontData[i].lines[0]=new V2d[fontData[i].lineNum];
		fontData[i].lines[1]=new V2d[fontData[i].lineNum];
		j=0;
		fontData[i].lines[0][j].x=X[1];
		fontData[i].lines[0][j].y=Y[0];
		fontData[i].lines[1][j].x=X[1];
		fontData[i].lines[1][j].y=Y[5];
	}
	
}

TextLineFont::TextLineFont(Surface * surfaceIn): TextBase(surfaceIn)
{
	if (!hasInited)
	{
		init();
		hasInited=1;
	}
	
	widthRateo=0.5;
}

void TextLineFont::renderGlyph(char c)
{
	if (bkndAlpha>0.0)
	{
		bkndClr->setDrawClr(surface);
		if (bkndAlpha!=1)
			surface->setDrawAlpha(bkndAlpha);
		
		surface->rect(V2d(pos.x, pos.y-cDim.y), V2d(pos.x+cDim.x, pos.y));
	}
	
	double lineThick;
	V2d loc, glyphDim;
	
	glyphDim.x=cDim.x*GLYPH_DIM_RATIO_X;
	glyphDim.y=cDim.y*GLYPH_DIM_RATIO_Y;
	
	loc.x=pos.x+GLYPH_OFFSET_X*cDim.x;
	loc.y=pos.y-cDim.y+GLYPH_OFFSET_Y*cDim.y;
	
	if (drawBold)
		lineThick=max(cDim.y*BOLD_THICKNESS_RATEO, 1.0);
	else
		lineThick=max(cDim.y*LINE_THICKNESS_RATEO, 1.0);
	
	drawClr->setDrawClr(surface);
	if (drawAlpha!=1)
		surface->setDrawAlpha(drawAlpha);
	
	for (int j=0; j<fontData[(int)c].lineNum; ++j)
		surface->line(floor(fontData[(int)c].lines[0][j]*glyphDim+loc), floor(fontData[(int)c].lines[1][j]*glyphDim+loc), lineThick);
	
	//surface->rect(loc, loc+glyphDim);
}

}

