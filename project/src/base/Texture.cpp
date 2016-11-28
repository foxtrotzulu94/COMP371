#include "base\Texture.h"
#include "..\..\soil\SOIL.h"

GLTexture::GLTexture()
{
	ImageData = NULL;
	width = 0;
	height = 0;
	glTexture = NULL;
}

GLTexture::~GLTexture()
{
}

bool GLTexture::isInRenderingContext()
{
	return glTexture!=NULL;
}


uchar* GLTexture::readImageData()
{
	return ImageData;
}

int GLTexture::getWidth()
{
	return width;
}

int GLTexture::getHeight()
{
	return height;
}

void GLTexture::setContextTexture(uint glTex)
{
	glTexture = glTex;
	SOIL_free_image_data(ImageData);
	ImageData = NULL;
}

void GLTexture::loadImageData(std::string filename)
{
	ImageData = SOIL_load_image(filename.c_str(), &width, &height, NULL, SOIL_LOAD_RGB);
}
