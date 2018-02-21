#pragma once

#include "TextureShader.h"
#include "TextureMaterial.h"

class TextureDefferedShader :
  public TextureShader
{
protected:
  virtual void InitializeShader(ID3D11Device* device, HWND hwnd, const std::wstring& vsFilename, const std::wstring& gsFilename, const std::wstring& hlFilename, const std::wstring& dmShaderFileName, const std::wstring& psFilename) override;
public:
  TextureDefferedShader();
  virtual ~TextureDefferedShader();
};

