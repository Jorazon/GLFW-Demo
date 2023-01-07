#pragma once
#include "Texture.h"

class RAW : virtual public Texture
{
public:
  RAW(std::string file, GLsizei width, GLsizei height) : Texture() {
    m_file = file;
    m_width = width;
    m_height = height;

    load();
  };
protected:
  void load() {
    unsigned char* data;

    FILE* image;
    image = fopen(m_file.c_str(), "rb");

    unsigned int imageSize = m_width * m_height * 3;

    data = new unsigned char[imageSize];

    if (!image)
    {
      printf("Error creating texture %s. %s\n", m_file.c_str(), strerror(errno));
      return;
    }

    // read file contents
    fread(data, 1, imageSize, image);
    
    fclose(image);

    // bind texture into texture unit
    Activate();

    // set sampling to GL_NEAREST to make integer texture work
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // make data into texture
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, (void*)data);

    glGenerateMipmap(GL_TEXTURE_2D);

    // free data
    delete[] data;
  }
private:
  std::string m_file;
  GLsizei m_width;
  GLsizei m_height;
};

