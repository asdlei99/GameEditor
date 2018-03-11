#pragma once

#include "BumpSpecSingleLightSh.h"
#include "BumpSpecMapMaterial.h"

class BumpSpecMapShader
  : public BumpSpecSingleLightSh
{
public:
  BumpSpecMapShader();
  virtual ~BumpSpecMapShader();
  virtual void Render(ID3D11DeviceContext* deviceContext, int indexCount, XMMATRIX worldMatrix, XMMATRIX viewMatrix,
    XMMATRIX projectionMatrix, const IMaterial* material, LightininigSystem* lightining, const XMFLOAT3& cameraPosition) override;
};

