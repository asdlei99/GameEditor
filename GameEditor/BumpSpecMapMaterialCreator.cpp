#include "BumpSpecMapMaterialCreator.h"

BumpSpecMapMaterialCreator::~BumpSpecMapMaterialCreator()
{
}

IMaterial* BumpSpecMapMaterialCreator::Get(const std::string& fileInStr, const std::string& fileName)
{
  char input;
  std::string type;
  std::string texturePath;
  std::string normalMapPath;
  std::string specularMapPath;
  std::stringstream fileStrStream(fileInStr);
  float bumpDepth;
  float rSpec, gSpec, bSpec, aSpec;
  float specularPower;

  fileStrStream.get(input);
  while (input != ':')
  {
    fileStrStream.get(input);
  }
  fileStrStream >> type;

  if (type != m_type)
    throw std::runtime_error(Logger::get().GetErrorTraceMessage("It is not material with texture type", __FILE__, __LINE__));

  fileStrStream.get(input);
  while (input != ':')
  {
    fileStrStream.get(input);
  }
  fileStrStream >> texturePath;

  fileStrStream.get(input);
  while (input != ':')
  {
    fileStrStream.get(input);
  }
  fileStrStream >> normalMapPath;

  fileStrStream.get(input);
  while (input != ':')
  {
    fileStrStream.get(input);
  }
  fileStrStream >> specularMapPath;

  fileStrStream.get(input);
  while (input != ':')
  {
    fileStrStream.get(input);
  }
  fileStrStream >> bumpDepth;

  fileStrStream.get(input);
  while (input != ':')
  {
    fileStrStream.get(input);
  }
  fileStrStream >> rSpec >> gSpec >> bSpec >> aSpec;

  fileStrStream.get(input);
  while (input != ':')
  {
    fileStrStream.get(input);
  }
  fileStrStream >> specularPower;

  Texture* texture = TextureFactory::get().GetResource(texturePath);
  Texture* normalMap = TextureFactory::get().GetResource(normalMapPath);
  Texture* specularMap = TextureFactory::get().GetResource(specularMapPath);
  BumpSpecMapMaterial* material = new BumpSpecMapMaterial(fileName, texture, normalMap, specularMap, bumpDepth, XMVectorSet(rSpec, gSpec, bSpec, aSpec), specularPower);
  return material;
}
