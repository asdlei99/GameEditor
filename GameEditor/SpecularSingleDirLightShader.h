#pragma once

#include "TextureShader.h"
#include "SpecularMaterial.h"

class SpecularSingleDirLightShader
  : public TextureShader
{
protected:
  struct CameraBufferType
  {
    XMFLOAT3 cameraPosition;
    float padding;
  };
  struct LightBufferSpecularType 
  {
    XMVECTOR ambientColor;
    XMVECTOR diffuseColor;
    XMFLOAT3 lightDirection;
    float specularPower;
    XMVECTOR specularColor;
  };
protected:
  ID3D11Buffer* m_cameraBuffer;
  ID3D11Buffer* m_lightBuffer;
protected:
  virtual void ShutdownShader() override;
  virtual void InitializeShader(ID3D11Device* device, HWND hwnd, const std::wstring& vsFilename, const std::wstring& gsFilename, const std::wstring& hlFilename, const std::wstring& dmShaderFileName, const std::wstring& psFilename) override;
  void SetShaderParameters(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
    XMMATRIX projectionMatrix, XMFLOAT3 lightDirection, XMVECTOR ambientColor,
    XMVECTOR diffuseColor, XMVECTOR specularColor, float specularPower, XMFLOAT3 cameraPosition);
public:
  SpecularSingleDirLightShader();
  virtual ~SpecularSingleDirLightShader();
  virtual void Render(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
    XMMATRIX projectionMatrix, const IMaterial* material, LightininigSystem* lightining, const XMFLOAT3& cameraPosition) override;
};

