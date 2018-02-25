#include "PointLight.h"

const float PointLight::SHADOW_NEAR_PLANE = 0.01f;

PointLight::PointLight()
{
  m_pointLightShadowDepthBuffer = nullptr;
  m_pointLightShadowDSV = nullptr;
  m_pointLightShadowSRV = nullptr;
}


PointLight::~PointLight()
{
  if (m_pointLightShadowDepthBuffer)
  {
    m_pointLightShadowDepthBuffer->Release();
    m_pointLightShadowDepthBuffer = nullptr;
  }

  if (m_pointLightShadowDSV)
  {
    m_pointLightShadowDSV->Release();
    m_pointLightShadowDSV = nullptr;
  }

  if (m_pointLightShadowSRV)
  {
    m_pointLightShadowSRV->Release();
    m_pointLightShadowSRV = nullptr;
  }
}

void PointLight::Initialize(float linearAttenuation, float quadraticAttenuation, XMFLOAT3 position, XMFLOAT3 color, GameObject* parent, bool castShadows, PointLightShadowDirection shadowDirections)
{
  SetParent(parent);
  SetColor(color);
  SetAttenuation(linearAttenuation, quadraticAttenuation);
  SetPosition(position.x, position.y, position.z);
  this->castShadows = castShadows;
  SetShadowDirections(shadowDirections);
}

void PointLight::InitializeShadowResources(ID3D11Device* device)
{
  bool result;

  D3D11_TEXTURE2D_DESC pointLightShadowDepthBufferDesc;
  ZeroMemory(&pointLightShadowDepthBufferDesc, sizeof(pointLightShadowDepthBufferDesc));
  pointLightShadowDepthBufferDesc.Width = D3DConfigurer::SHADOW_MAP_SIZE;
  pointLightShadowDepthBufferDesc.Height = D3DConfigurer::SHADOW_MAP_SIZE;
  pointLightShadowDepthBufferDesc.MipLevels = 1;
  pointLightShadowDepthBufferDesc.ArraySize = 6;
  pointLightShadowDepthBufferDesc.Format = DXGI_FORMAT_R32_TYPELESS;
  pointLightShadowDepthBufferDesc.SampleDesc.Count = 1;
  pointLightShadowDepthBufferDesc.SampleDesc.Quality = 0;
  pointLightShadowDepthBufferDesc.Usage = D3D11_USAGE_DEFAULT;
  pointLightShadowDepthBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
  pointLightShadowDepthBufferDesc.CPUAccessFlags = 0;
  pointLightShadowDepthBufferDesc.MiscFlags = D3D10_RESOURCE_MISC_TEXTURECUBE;

  result = device->CreateTexture2D(&pointLightShadowDepthBufferDesc, nullptr, &m_pointLightShadowDepthBuffer);
  if (FAILED(result))
  {
    RUNTIME_ERROR("Can't create point light shadow depth buffer");
  }

  D3D11_DEPTH_STENCIL_VIEW_DESC pointLightShadowDSVDesc;
  ZeroMemory(&pointLightShadowDSVDesc, sizeof(pointLightShadowDSVDesc));
  pointLightShadowDSVDesc.Format = DXGI_FORMAT_D32_FLOAT;
  pointLightShadowDSVDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DARRAY;
  pointLightShadowDSVDesc.Flags = 0;
  pointLightShadowDSVDesc.Texture2DArray.MipSlice = 0;
  pointLightShadowDSVDesc.Texture2DArray.FirstArraySlice = 0;
  pointLightShadowDSVDesc.Texture2DArray.ArraySize = 6;

  result = device->CreateDepthStencilView(m_pointLightShadowDepthBuffer, &pointLightShadowDSVDesc, &m_pointLightShadowDSV);
  if (FAILED(result))
  {
    RUNTIME_ERROR("Can't create point light shadow depth stencil view");
  }

  D3D11_SHADER_RESOURCE_VIEW_DESC pointLightShadowSRVDesc;
  pointLightShadowSRVDesc.Format = DXGI_FORMAT_R32_FLOAT;
  pointLightShadowSRVDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURECUBE;
  pointLightShadowSRVDesc.Texture2D.MostDetailedMip = 0;
  pointLightShadowSRVDesc.Texture2D.MipLevels = 1;

  result = device->CreateShaderResourceView(m_pointLightShadowDepthBuffer, &pointLightShadowSRVDesc, &m_pointLightShadowSRV);
  if (FAILED(result))
  {
    RUNTIME_ERROR("Can't create point light shadow shader resource view");
  }
}

void PointLight::PrepareToShadowGeneration(ID3D11DeviceContext* deviceContext)
{
  deviceContext->OMSetRenderTargets(0, nullptr, m_pointLightShadowDSV);
  deviceContext->ClearDepthStencilView(m_pointLightShadowDSV, D3D11_CLEAR_DEPTH, 1.0, 0);
}

void PointLight::SetShadowDirections(PointLightShadowDirection shadowDirections)
{
  if (m_shadowDirections != shadowDirections)
  {
    int shadowDirectionEnumHighBorder = PointLightShadowDirection::MINUS_Z;
    int i = 0;
    for (int shadowDirectionChar = 1, pass = 0; shadowDirectionChar <= shadowDirectionEnumHighBorder; shadowDirectionChar *= 2, ++pass)
    {
      if (shadowDirections & shadowDirectionChar)
      {
        m_shadowDirectionsArr[i] = pass;
        ++i;
      }
    }

    m_shadowDirectionsArrSize = i;
  }

  m_shadowDirections = shadowDirections;
}

const int* const PointLight::GetShaderShadowDirectionsArr() const
{
  return m_shadowDirectionsArr;
}

const int PointLight::GetShaderShadowDirectionsArrSize() const
{
  return m_shadowDirectionsArrSize;
}

void PointLight::SetAttenuation(float linearAttenuation, float quadraticAttenuation)
{
  m_linerarAttenuation = linearAttenuation;
  m_quadraticAttenuation = quadraticAttenuation;

  float maxColorPart = (std::max)({ m_color.x, m_color.y, m_color.z });
  float D = pow(m_linerarAttenuation, 2) - 4 * m_quadraticAttenuation * (1 - 256.0f * maxColorPart);

  if (D < 0)
  {
    this->SetScale(0.0f);
    return;
  }

  if (D == 0)
  {
    m_radius = -m_linerarAttenuation / (2 * m_quadraticAttenuation);
  }
  else if (D > 0)
  {
    float x1 = (-m_linerarAttenuation + sqrtf(D)) / (2 * m_quadraticAttenuation);
    float x2 = (-m_linerarAttenuation - sqrtf(D)) / (2 * m_quadraticAttenuation);
    m_radius = max(x1, x2);
  }
  m_radius *= 100.0f;
  this->SetScale(m_radius);

  RebuildPerspectiveValues();
}

void PointLight::SetPosition(float x, float y, float z)
{
  GameObject::SetPosition(x, y, z);
  XMFLOAT3 worldPosition = this->GetWorldPosition();
  RebuildCubeViewProjection(worldPosition);
}

void PointLight::RebuildCubeViewProjection(XMFLOAT3 worldPosition)
{
  XMMATRIX lightProjection, positionMatrix, spotView, toShadow;

  positionMatrix = XMMatrixTranslation(-worldPosition.x, -worldPosition.y, -worldPosition.z);
  lightProjection = XMMatrixPerspectiveFovLH(XM_PIDIV2, 1.0f, SHADOW_NEAR_PLANE, m_radius * 1000);

  // Cube +X
  spotView = XMMatrixRotationY(XM_PI + XM_PIDIV2);
  toShadow = positionMatrix * spotView * lightProjection;
  m_cubeViewProjection[0] = XMMatrixTranspose(toShadow);

  // Cube -X
  spotView = XMMatrixRotationY(XM_PIDIV2);
  toShadow = positionMatrix * spotView * lightProjection;
  m_cubeViewProjection[1] = XMMatrixTranspose(toShadow);

  // Cube +Y
  spotView = XMMatrixRotationX(XM_PIDIV2);
  toShadow = positionMatrix * spotView * lightProjection;
  m_cubeViewProjection[2] = XMMatrixTranspose(toShadow);

  // Cube -Y
  spotView = XMMatrixRotationX(XM_PI + XM_PIDIV2);
  toShadow = positionMatrix * spotView * lightProjection;
  m_cubeViewProjection[3] = XMMatrixTranspose(toShadow);

  // Cube +Z
  toShadow = positionMatrix * lightProjection;
  m_cubeViewProjection[4] = XMMatrixTranspose(toShadow);

  // Cube -Z
  spotView = XMMatrixRotationY(XM_PI);
  toShadow = positionMatrix * spotView * lightProjection;
  m_cubeViewProjection[5] = XMMatrixTranspose(toShadow);

  m_oldWorldPosition = worldPosition;
}

XMMATRIX* PointLight::GetCubeViewProjection()
{
  XMFLOAT3 worldPosition = this->GetWorldPosition();

  float precision = 0.001;

  if (abs(m_oldWorldPosition.x - worldPosition.x) > precision || abs(m_oldWorldPosition.y - worldPosition.y) > precision != abs(m_oldWorldPosition.z - worldPosition.z) > precision)
  {
    RebuildCubeViewProjection(worldPosition);
  }

  return m_cubeViewProjection;
}

void PointLight::RebuildPerspectiveValues()
{
  XMMATRIX lightProjection = XMMatrixPerspectiveFovLH(XM_PIDIV2, 1.0f, SHADOW_NEAR_PLANE, m_radius);
  XMFLOAT4X4 lightProjectionReadable;

  XMStoreFloat4x4(&lightProjectionReadable, lightProjection);
  m_lightPerspectiveValues = XMFLOAT2(lightProjectionReadable._33, lightProjectionReadable._43);
}

XMFLOAT2 PointLight::GetLightPerspectiveValues()
{
  return m_lightPerspectiveValues;
}

void PointLight::RebuildBBInWorldCoord()
{
  float radius50Percent = m_radius * 0.5;
  XMFLOAT3 worldPosition = this->GetWorldPosition();

  m_bbInWorldCoord.Initialize(
    worldPosition.x - radius50Percent,
    worldPosition.y - radius50Percent,
    worldPosition.z - radius50Percent,
    worldPosition.x + radius50Percent,
    worldPosition.y + radius50Percent,
    worldPosition.z + radius50Percent
    );
}

BoundingBox* PointLight::GetAABBBoundingBox()
{
  return this->GetBBInWorldCoords();
}

void PointLight::RebuildWorldMatrix()
{
  GameObject::RebuildWorldMatrix();

  float radius20Percent = m_radius * 0.2f;
  m_20percentLightVolumeMatrix = XMMatrixScaling(radius20Percent, radius20Percent, radius20Percent) * m_translationMatrix;
}

void PointLight::Get20PercentLightVolumeMatrix(XMMATRIX& lightVolume)
{
  if (NeedRebuildWorldMatrix())
  {
    RebuildWorldMatrix();
  }

  if (m_parent)
  {
    XMMATRIX parentMatrix;
    GetParentMatrix(parentMatrix);
    lightVolume = m_20percentLightVolumeMatrix * parentMatrix;
  }
  else
  {
    lightVolume = m_20percentLightVolumeMatrix;
  }
}