#include "BumpSpecMapMaterialCreator.h"
#include "Logger.h"

BumpSpecMapMaterialCreator::~BumpSpecMapMaterialCreator()
{
}

IMaterial* BumpSpecMapMaterialCreator::Get(const std::string& fileInStr, const std::string& fileName)
{
  if (!m_textureFactory)
    RUNTIME_ERROR("Texture factory was not initialized!");

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
    RUNTIME_ERROR("It is not material with texture type");

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

  Texture* texture = m_textureFactory->GetResource(texturePath);
  Texture* normalMap = m_textureFactory->GetResource(normalMapPath);
  Texture* specularMap = m_textureFactory->GetResource(specularMapPath);
  BumpSpecMapMaterial* material = new BumpSpecMapMaterial(fileName, texture, normalMap, specularMap, bumpDepth, XMFLOAT3(rSpec, gSpec, bSpec), specularPower);
  return material;
}
