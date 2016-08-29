#include "../../h/Window/WindowSFML.h"
#include "../../h/Math/SimpMath.h"
#include "../../h/Graphics/TextLineFont.h"
#include "../../h/Graphics/Image.h"

namespace widap
{

bool WindowSFML::firstInstance=true;
//sf::Font WindowSFML::font;
char WindowSFML::key2char[127];


WindowSFML::WindowSFML()
{
	//constructor
	
	textInit();
	
	err.setPrefix("widap::WindowSFML: ");
	
	drawClr=clr(0, 0, 0);
	drawAlpha=1;
	data=0;
	
	if (firstInstance)
	{
		/*if
		(
			!font.loadFromFile("/usr/share/fonts/truetype/ubuntu-font-family/UbuntuMono-R.ttf") &&
			!font.loadFromFile("/usr/share/fonts/truetype/freefont/FreeMono.ttf") &&
			!font.loadFromFile("/usr/share/fonts/TTF/DejaVuSans.ttf")
		)
		{
			err << "font failed to load" << err;
		}*/
		
		int i;
		
		for (i=0; i<127; ++i)
		{
			key2char[i]=1;
		}
		
		for (i=sf::Keyboard::A; i<=sf::Keyboard::Z; ++i) //letters
			key2char[i]=i-sf::Keyboard::A+int('A');
			
		for (i=sf::Keyboard::Num0; i<=sf::Keyboard::Num9; ++i) //number row
			key2char[i]=i-sf::Keyboard::Num0+int('0');
			
		for (i=sf::Keyboard::Numpad0; i<=sf::Keyboard::Numpad9; ++i) //number pad
			key2char[i]=i-sf::Keyboard::Numpad0+int('0');
			
		key2char[int(sf::Keyboard::Space)]=' ';
		key2char[int(sf::Keyboard::Period)]='.';
		key2char[int(sf::Keyboard::Comma)]=',';
		key2char[int(sf::Keyboard::BackSlash)]='\\';
		key2char[int(sf::Keyboard::Slash)]='/';
		key2char[int(sf::Keyboard::LBracket)]='[';
		key2char[int(sf::Keyboard::RBracket)]=']';
		key2char[int(sf::Keyboard::Quote)]='\'';
		key2char[int(sf::Keyboard::SemiColon)]=';';
		key2char[int(sf::Keyboard::Delete)]=127;
		key2char[int(sf::Keyboard::BackSpace)]='\b';
		key2char[int(sf::Keyboard::Return)]='\n';
		key2char[int(sf::Keyboard::Tab)]='\t';
		key2char[int(sf::Keyboard::Equal)]='=';
		key2char[int(sf::Keyboard::Dash)]='-';
		key2char[int(sf::Keyboard::Left)]='a'; //I use lower key2char[int(wasd for arrow keys)]
		key2char[int(sf::Keyboard::Right)]='d';
		key2char[int(sf::Keyboard::Up)]='w';
		key2char[int(sf::Keyboard::Down)]='s';
		
		firstInstance=0;
	}
}

void WindowSFML::textInit()
{
	textPtr=new TextLineFont(this);
}

WindowSFML::~WindowSFML()
{
	close();
	
	if (data)
		delete[] data;
}


///from WindowBase

//open the window with the given dimensions and name
void WindowSFML::open(V2u dimIn, string nameIn)
{
	name=nameIn;
	
	if (dimIn.x)
		windowObj.create(sf::VideoMode(dimIn.x, dimIn.y), name);
	else
	{
		if (dimIn.y==0)
			windowObj.create(sf::VideoMode::getDesktopMode(), name, sf::Style::Fullscreen);
		else if (dimIn.y==1)
		{
			err << "requested maximized window, but SFML doesn't support that so making it a bit smaller then the screen" << err;
			sf::VideoMode mode=sf::VideoMode::getDesktopMode();
			double wo=0.02, ho=0.12;
			windowObj.create(sf::VideoMode(mode.width*(1-wo), mode.height*(1-ho)), name);
			windowObj.setPosition(sf::Vector2i(mode.width*wo*0.5, mode.height*ho*0.2));
		}
	}
	
	hasBeenResized();
	
	windowIsOpen=windowObj.isOpen();
	
	windowHasFocus=windowIsOpen;
	
	refreshDisplay();
	updateInput();
}

//close the window
void WindowSFML::close()
{
	/** ||| **/
	/** VVV **/ windowObj.close();
	/// If you get an error here, probably you've not linked to the sfml libraries
	//you must put the following lines into linker options to use sfml window
	/*

-lsfml-graphics
-lsfml-window
-lsfml-system

	*/
}

//repaint the window
void WindowSFML::refreshDisplay()
{
	if (!windowObj.isOpen())
	{
		windowIsOpen=0;
		return;
	}
	else if (!windowIsOpen)
	{
		//std::cout << ">> update called while window closed <<\n";
		return;
	}
	
	windowObj.display();
}

//get any new input
void WindowSFML::updateInput()
{
	if (!windowIsOpen)
	{
		return;
	}
	else if (!windowObj.isOpen())
	{
		windowIsOpen=0;
		return;
	}
	
	sf::Event event;
	
	keyPressListPos=0;
	keyPressNum=0;
	
	mouseLClick=0;
	mouseRClick=0;
	mouseMClick=0;
	
	mouseScroll=0;
	
	while (windowObj.pollEvent(event))
	{
		switch (event.type)
		{
		// window closed
		case sf::Event::Closed:
			windowObj.close();
			break;
		
		// key pressed
		case sf::Event::KeyPressed:
			if (keyPressNum<MAX_KEY_PRESSES)
			{
				keyPresses[keyPressNum]=key2char[event.key.code];
				++keyPressNum;
			}
			else
			{
				err << "key press overflow" << err;
			}
			break;
		
		case sf::Event::MouseButtonPressed:
			switch (event.mouseButton.button)
			{
			case sf::Mouse::Left:
				mouseLClick=1;
				break;
				
			case sf::Mouse::Right:
				mouseRClick=1;
				break;
				
			case sf::Mouse::Middle:
				mouseMClick=1;
				break;
			
			default:
				break;
			}
			break;
		
		case sf::Event::MouseWheelMoved:
			mouseScroll+=event.mouseWheel.delta;
			break;
			
		case sf::Event::Resized:
			hasBeenResized();
			break;
			
		case sf::Event::GainedFocus:
			windowHasFocus=1;
			break;
		
		case sf::Event::LostFocus:
			windowHasFocus=0;
			break;
		
		// we don't process other types of events
		default:
			break;
		}
	}
	
	sf::Vector2i mouseVctr=sf::Mouse::getPosition(windowObj);
	
	shiftDwnBool=sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift);
	ctrlDwnBool=sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) || sf::Keyboard::isKeyPressed(sf::Keyboard::RControl);
	altDwnBool=sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) || sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt);
	superDwnBool=sf::Keyboard::isKeyPressed(sf::Keyboard::RSystem) || sf::Keyboard::isKeyPressed(sf::Keyboard::RSystem);
	
	mouseLDwn=sf::Mouse::isButtonPressed(sf::Mouse::Left);
	mouseRDwn=sf::Mouse::isButtonPressed(sf::Mouse::Right);
	mouseMDwn=sf::Mouse::isButtonPressed(sf::Mouse::Middle);
	
	mouseLocDlta.x=mouseVctr.x-mouseLocation.x;
	mouseLocDlta.y=dim.y-mouseVctr.y-mouseLocation.y;
	
	mouseLocation.x=mouseVctr.x;
	mouseLocation.y=dim.y-mouseVctr.y;
}

void WindowSFML::hasBeenResized()
{
	V2u newDim(windowObj.getSize().x, windowObj.getSize().y);
	
	if (newDim==dim)
		return;
	
	dim=newDim;
	
	//stop view from scaling with the window
	
	windowObj.setView(sf::View(sf::FloatRect(0, 0, dim.x, dim.y)));
}


///from Surface

//sets the value of a single pixel to the predefined drawing color
void WindowSFML::set(int x, int y)
{
	err << "tried to draw a single pixel to a SFML window, this is not implemented because it would be to slow" << err;
	/*if (drawAlpha>=1)
		data[y*dim.x+x]=drawClr;
	else if (drawAlpha>0)
	{
		ClrBGR * ptr=data+y*dim.x+x;
		ptr->r=ptr->r*(1-drawAlpha)+drawClr.r*drawAlpha;
		ptr->g=ptr->g*(1-drawAlpha)+drawClr.g*drawAlpha;
		ptr->b=ptr->b*(1-drawAlpha)+drawClr.b*drawAlpha;
	}*/
}

//set the draw color with an bool
void WindowSFML::setDrawClr(bool clrIn)
{
	if (clrIn)
		drawClr=clr(255, 255, 255);
	else
		drawClr=clr(0, 0, 0);
	
	drawAlpha=1;
}

//set the draw color with an int (usually the lowest few numbers will be standard template colors, and anything higher will be the same as 0)
void WindowSFML::setDrawClr(int clrIn)
{
	switch (clrIn)
	{
	case 1:
		drawClr=clr(255, 255, 255);
		break;
		
	case 2:
		drawClr=clr(0, 16, 32);
		break;
		
	case 3:
		drawClr=clr(192, 255, 0);
		break;
		
	case 4:
		drawClr=clr(255, 0, 128);
		break;
		
	default:
		drawClr=clr(0, 0, 0);
		break;
	}
	
	drawAlpha=1;
}

//set the draw color with a ClrRGBA value
void WindowSFML::setDrawClr(ClrRGBA clrIn)
{
	drawClr.r=clrIn.r;
	drawClr.g=clrIn.g;
	drawClr.b=clrIn.b;
	drawAlpha=clrIn.a/255.0;
}

//set the draw color with a ClrBGR value
void WindowSFML::setDrawClr(ClrBGR clrIn)
{
	drawClr=clrIn;
	
	drawAlpha=1;
}

//fills the entire window with a single color

void WindowSFML::clear()
{
	if (drawAlpha==1)
		windowObj.clear(sf::Color(drawClr.r, drawClr.g, drawClr.b, 255)); //this function ignores alpha value
	else
		rect(V2d(), dim);
}

//draws a filled rectangle
void WindowSFML::rect(V2d low, V2d hgh)
{
	sf::RectangleShape rectangle(sf::Vector2f(hgh.x-low.x, hgh.y-low.y));
	rectangle.setFillColor(sfmlDrawClr());
	rectangle.setPosition(low.x, dim.y-hgh.y);
	
	windowObj.draw(rectangle);
}

//draws a filled circle
void WindowSFML::circle(V2d pos, double radius)
{
	
	sf::CircleShape shape(radius);
	shape.setFillColor(sfmlDrawClr());
	shape.setPosition(pos.x-radius, dim.y-pos.y-radius);
	
	windowObj.draw(shape);
}

//draw a triangle
void WindowSFML::tri(V2d * virtsIn)
{
	sf::ConvexShape shape(3); //3 is the number of verts
	
	shape.setFillColor(sfmlDrawClr());
	
	shape.setPoint(0, sf::Vector2f(virtsIn[0].x, dim.y-virtsIn[0].y));
	shape.setPoint(1, sf::Vector2f(virtsIn[1].x, dim.y-virtsIn[1].y));
	shape.setPoint(2, sf::Vector2f(virtsIn[2].x, dim.y-virtsIn[2].y));
	
	windowObj.draw(shape);
}

//draw a line
void WindowSFML::line(V2d a, V2d b, double thickness)
{
	double rot=-atan2(b.y-a.y, b.x-a.x);
	sf::RectangleShape rectangle(sf::Vector2f(dst(a, b), thickness));
	rectangle.setFillColor(sfmlDrawClr());
	rectangle.setPosition(a.x+sin(rot)*thickness/2, dim.y-a.y-cos(rot)*thickness/2);
	rectangle.setRotation(rad2deg(rot));
	
	windowObj.draw(rectangle);
	
	//circle(a, thickness/2);
	//circle(b, thickness/2);
	
	//circle(a, drawThick/2, ::clr(0, 0, 0), 0.5);
	//circle(b, drawThick/2, ::clr(0, 0, 0), 0.5);
}

//draw a surface
void WindowSFML::surfaceWithAlphaSet(Surface * other, V2d pos)
{
	switch (other->getType())
	{
	case IMAGE_BGR:
		image((Image *)other, pos, drawAlpha);
		break;
		
	default:
		Surface::surfaceWithAlphaSet(other, pos);
	}
}


///other

//draws an image, the pointer must be to an image type
void WindowSFML::image(Surface * imgIn, V2d pos, double alphaIn)
{
	unsigned char alpha=alphaIn*255;
	
	if (imgIn->getType()!=IMAGE_BGR)
	{
		err << "image() was called with a surface pointer not of type Image" << err;
		return;
	}
	
	Image * img=(Image *)imgIn;
	
	if (img->isEmpty())
		return;
	
	V2u imgDim=img->getDim();
	
	if (!data || imgDim.x>texture.getSize().x || imgDim.y>texture.getSize().y)
	{
		if (data)
			delete[] data;
		
		try
		{
			data=new ClrRGBA[img->getDim().area()];
		}
		catch (std::bad_alloc)
		{
			err << "bad mem alloc while creating RGBA data, attempted size was " << dim.area()*sizeof(ClrRGBA)/1048576.0 << "MB" << err;
			data=0;
			return;
		}
		
		if (!texture.create(imgDim.x, imgDim.y))
		{
			err << "error creating texture for image transfer" << err;
			
			if (data)
				delete[] data;
			
			data=0;
			
			return;
		}
	}
	
	unsigned int x, y, yo0, yo1; //y-offset
	Clr color;
	ClrBGR * dataBGR=img->getData();
	
	for (y=0; y<imgDim.y; ++y)
	{
		yo0=y*imgDim.x;
		yo1=(imgDim.y-y-1)*imgDim.x;
		for (x=0; x<imgDim.x; ++x)
		{
			color=dataBGR[x+yo0];
			
			data[yo1+x].r=color.r;
			data[yo1+x].g=color.g;
			data[yo1+x].b=color.b;
			data[yo1+x].a=alpha;
		}
	}
	
	texture.update((sf::Uint8*)data, imgDim.x, imgDim.y, 0, 0);
	
	sf::Sprite sprite(texture);
	
	sprite.setPosition(sf::Vector2f(pos.x, dim.y-pos.y-imgDim.y));
	
	windowObj.draw(sprite);
}


///private

//return the draw color and alpha as a sfml color
sf::Color WindowSFML::sfmlDrawClr()
{
	return sf::Color(drawClr.r, drawClr.g, drawClr.b, drawAlpha*255);
}

}


