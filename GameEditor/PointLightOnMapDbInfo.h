#pragma once

#include <qstring.h>
#include "PointLightDbInfo.h"
#include "SGOOnMapDbInfo.h"

class PointLightOnMapDbInfo
{
public:
  int id;
  int pointLightId;
  int sgoOnMapId;

  float red = 1.0f;
  float green = 1.0f;
  float blue = 1.0f;
  float linearAttenuation;
  float quadraticAttenuation;
  bool castShadows = false;
  int shadowDirections = 63;

  PointLightDbInfo pointLightDbInfo;
  SGOOnMapDbInfo sgoOnMapDbInfo;
};

