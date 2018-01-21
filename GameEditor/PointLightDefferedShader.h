#pragma once

#include "TextureShader.h"
#include "Mesh.h"
#include "PointLightDefferedParameters.h"

class PointLightDefferedShader :
  public TextureShader
{
protected:
  struct PointLightBuffer
  {
    XMFLOAT3 color;
    float linearAttenuation;
    XMFLOAT3 position;
    float quadraticAttenuation;
    float screenWidth;
    float screenHeight;
    float padding[2];
  };
protected:
  ID3D11Buffer* m_pointLightBuffer;
protected:
  virtual void InitializeShader(ID3D11Device* device, HWND hwnd, const std::wstring& vsFilename, const std::wstring& psFilename) override;
  virtual void ShutdownShader() override;
  void SetShaderParameters(ID3D11DeviceContext* deviceContext, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
    XMMATRIX projectionMatrix, XMFLOAT3 pointLightColor, XMFLOAT3 pointLightPosition, float linearAttenuation, float quadraticAttenuation, float screenWidth, float screenHeight);
public:
  PointLightDefferedShader();
  virtual ~PointLightDefferedShader();
  virtual void Render(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
    XMMATRIX projectionMatrix, IMaterial* material, LightininigSystem* lightining, XMFLOAT3& cameraPosition) override;
};

