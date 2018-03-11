#pragma once

#include "BumpSpecDefferedShader.h"
#include "BumpSpecMapMaterial.h"

class BumpSpecMapDefferedShader :
  public BumpSpecDefferedShader
{
public:
  BumpSpecMapDefferedShader();
  virtual ~BumpSpecMapDefferedShader();
  virtual void Render(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
    XMMATRIX projectionMatrix, const IMaterial* material, LightininigSystem* lightining, const XMFLOAT3& cameraPosition) override;
};

