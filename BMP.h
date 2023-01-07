// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-5-a-textured-cube/#loading-bmp-images-yourself
#pragma once
#include "Texture.h"

class BMP : virtual public Texture
{
public:
  BMP(std::string file) : Texture() {
    m_file = file;
    load();
  };
protected:
  void load() {
    unsigned char header[54]; // Each BMP file begins by a 54-bytes header
    unsigned int dataPos;     // Position in the file where the actual data begins
    unsigned int width, height;
    unsigned int imageSize;   // = width*height*3
    // Actual RGB data
    unsigned char* data;

    FILE* image;
    image = fopen(m_file.c_str(), "rb");


    if (!image)
    {
      printf("Error creating texture %s. %s\n", m_file.c_str(), strerror(errno));
      return;
    }

    size_t headerSize = fread(header, 1, 54, image);

    if (headerSize != sizeof(header) || header[0] != 'B' || header[1] != 'M') {
      printf("Not a correct BMP file\n");
      return;
    }
      
    dataPos = *(int*)&(header[0x0A]);
    imageSize = *(int*)&(header[0x22]);
    width = *(int*)&(header[0x12]);
    height = *(int*)&(header[0x16]);
    
    if (imageSize == 0)    imageSize = width * height * 3; // 3 : one byte for each Red, Green and Blue component
    if (dataPos == 0)      dataPos = 54; // The BMP header is done that way

    data = new unsigned char[imageSize];

    // read file contents
    fread(data, 1, imageSize, image);
    
    fclose(image);

    // bind texture into texture unit
    Activate();

    // set sampling to GL_NEAREST to make integer texture work
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // make data into texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, (void*)data);

    glGenerateMipmap(GL_TEXTURE_2D);

    // free data
    delete[] data;
  }
private:
  std::string m_file;
};
