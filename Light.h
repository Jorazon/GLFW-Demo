#pragma once

#include "Transform.h"

class Light : public Transform
{
public:
  Light();
  ~Light();
  float m_amount = 1.0f;
};
