#pragma once

#include <algorithm>
#include "IConverter.h"
#include "BumpMaterial.h"
#include "ColorMaterial.h"
#include "SpecularMaterial.h"
#include "Utils.h"

class Logger;

class MtlMatLibConverter : public IConverter
{
public:

  struct MtlColor {
    float r;
    float g;
    float b;
  };

  struct MtlMaterial {
    float Ns;
    float Ni;
    float d;
    float Tr;
    MtlColor Tf;
    int illum;
    MtlColor Ka;
    MtlColor Kd;
    MtlColor Ks;
    MtlColor Ke;
    std::string map_Ka;
    std::string map_Kd;
    float bumpPower;
    std::string map_bump;
  };
protected:
  static const char MTL_FILE_SEPARATOR = '\\';
  static const std::string NEW_MAT_DESCRIPTOR;
  std::string m_pathToMaterials;
  std::string m_space; //Place for reading string from buffer
protected:
  bool HasSpecularData(const MtlMaterial& material) { return (material.Ks.r > 0 || material.Ks.g > 0 || material.Ks.b > 0) && material.Ns > 0; }

  void readMtlMaterial(std::stringstream& strStream, MtlMaterial& material);
  void saveMaterial(const std::string& materialName, const MtlMaterial& material, bool needReplaceIfExists);
  std::string defineMaterialType(const MtlMaterial& material);
  void saveBumpMaterial(std::ofstream& ofstream, const MtlMaterial& material);
  void saveColorMaterial(std::ofstream& ofstream, const MtlMaterial& material);
  void saveTextureMaterial(std::ofstream& ofstream, const MtlMaterial& material);
  void saveSpecularMaterialType(std::ofstream& ofstream, const MtlMaterial& material);
public:
  static const std::string GE_MAT_EXT;
  static const std::string MTL_MAT_EXT;
public:
  MtlMatLibConverter(std::string pathToMaterials) { m_fileExtension = MTL_MAT_EXT.substr(1); m_pathToMaterials = pathToMaterials; }
  virtual ~MtlMatLibConverter();
  void ConvertMtlMaterials(std::string& sourceFileName, bool needReplaceIfExists = false);
 
};

