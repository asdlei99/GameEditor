#include "GraphicSystem.h"

const std::string GraphicSystem::GRID_SHADER_NAME = "grid";
const std::string GraphicSystem::DEPTH_BUFFER_SHADER_NAME = "depthBuffer";
const std::string GraphicSystem::AMBIENT_DEFFERED_SHADER_NAME = "ambientDeffered";
const std::string GraphicSystem::POINT_LIGHT_DEFFERED_SHADER_NAME = "pointLightDeffered";
const std::string GraphicSystem::POINT_LIGHT_MODEL_NAME = "sphere1cm.txt";

GraphicSystem::GraphicSystem()
{
}


GraphicSystem::~GraphicSystem()
{
  
}

void GraphicSystem::Initialize(int screenWidth, int screenHeight, bool vsyncEnabled, HWND hwnd, bool fullScreen, ShaderConfiguration* shaderConfiguration, std::string pathToMaterials, std::string pathToModels)
{
  bool result;
  m_direct3D = std::unique_ptr<D3DConfigurer>(new D3DConfigurer);
  result = m_direct3D->Initialize(screenWidth, screenHeight, vsyncEnabled, hwnd, fullScreen);
  if (!result)
    throw std::runtime_error(Logger::get().GetErrorTraceMessage("cant initialize direct 3D", __FILE__, __LINE__));

  m_pathToModels = pathToModels;

  //factory initializing
  m_textureFactory = std::unique_ptr<TextureFactory>((new TextureFactory())->Initialize(m_direct3D->GetDevice(), m_direct3D->GetDeviceContext(), pathToMaterials));
  m_shaderFactory = std::unique_ptr<ShaderFactory>((new ShaderFactory())->Initialize(m_direct3D->GetDevice(), hwnd, shaderConfiguration));
  m_materialFactory = std::unique_ptr<MaterialFactory>((new MaterialFactory())->Initialize(m_textureFactory.get(), pathToMaterials));
  m_modelFactory = std::unique_ptr<ModelFactory>((new ModelFactory())->Initialize(m_direct3D->GetDevice(), m_materialFactory.get()));

  m_pointLightMesh = m_modelFactory->GetResource(m_pathToModels + FileProcessor::FILE_SEPARATOR + POINT_LIGHT_MODEL_NAME)->GetMesh(0);
}

ModelFactory* GraphicSystem::GetModelFactory()
{
  return m_modelFactory.get();
}
TextureFactory* GraphicSystem::GetTextureFactory()
{
  return m_textureFactory.get();
}
ShaderFactory* GraphicSystem::GetShaderFactory()
{
  return m_shaderFactory.get();
}
MaterialFactory* GraphicSystem::GetMaterialFactory()
{
  return m_materialFactory.get();
}

void GraphicSystem::AddModelToRenderList(Model* model, XMMATRIX& worldMatrix)
{
  for (int i = 0; i < model->GetMeshCount(); ++i)
  {
    Mesh* mesh = model->GetMesh(i);
    std::pair<XMMATRIX, Mesh*> renderInfo(worldMatrix, mesh);
    m_modelRenderList[mesh->GetMaterialType()][mesh->GetMaterialName()].push_back(renderInfo);
  }
}

void GraphicSystem::Render(Camera* camera, LightininigSystem* lightiningSystem)
{
  XMMATRIX viewMatrix, projectionMatrix;

  m_direct3D->SetBackBufferRenderTarget();
  // Clear the buffers to begin the scene.
  m_direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

  // Generate the view matrix based on the camera's position.
  camera->GetViewMatrix(viewMatrix);
  camera->GetProjectionMatrix(projectionMatrix);

  DrawModels(viewMatrix, projectionMatrix, lightiningSystem, camera->GetPosition());
  DrawGrids(viewMatrix, projectionMatrix);
  m_direct3D->EndScene();
}

void GraphicSystem::DrawModels(XMMATRIX& viewMatrix, XMMATRIX& projectionMatrix, LightininigSystem* lightiningSystem, XMFLOAT3 cameraPosition)
{
  ID3D11DeviceContext* deviceContext = m_direct3D->GetDeviceContext();

  deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

  for (auto shaderInfo : m_modelRenderList)
  {
    IShader* shader = m_shaderFactory->Get(shaderInfo.first);
    shader->EnableShader(deviceContext);

    for (auto materialInfo : shaderInfo.second)
    {
      IMaterial* material = materialInfo.second[0].second->GetMaterial();
      if (material->GetTexturesCount() > 0)
        shader->SetTextures(deviceContext, material->GetTextures(), material->GetTexturesCount());

      bool needEnableTransparancy = material->GetType() == ColorMaterial::colorMaterialType && (int)(((ColorMaterial*)material)->m_subType & ColorMaterialSubType::COLOR_TRANSPARENT) > 0;

      if (needEnableTransparancy)
        m_direct3D->EnableTransparencyBlending();

      for (auto meshInfo : materialInfo.second)
      {
        meshInfo.second->PrepareToRender(deviceContext);
        shader->Render(deviceContext, meshInfo.second->GetIndexCount(), meshInfo.first, viewMatrix, projectionMatrix, material, lightiningSystem, cameraPosition);
      }

      if (needEnableTransparancy)
        m_direct3D->DisableBlending();
    }
  }
  m_modelRenderList.clear();
}

void GraphicSystem::DrawModelsInDepthBuffer(XMMATRIX& viewMatrix, XMMATRIX& projectionMatrix)
{
  ID3D11DeviceContext* deviceContext = m_direct3D->GetDeviceContext();
  XMFLOAT3 space;

  deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

  auto depthBufferShader = m_shaderFactory->Get(DEPTH_BUFFER_SHADER_NAME);
  depthBufferShader->EnableShader(deviceContext);
  for (auto shaderInfo : m_modelRenderList)
  {
    for (auto materialInfo : shaderInfo.second)
    {
      for (auto meshInfo : materialInfo.second)
      {
        meshInfo.second->PrepareToRender(deviceContext);
        depthBufferShader->Render(deviceContext, meshInfo.second->GetIndexCount(), meshInfo.first, viewMatrix, projectionMatrix, nullptr, nullptr, space);
      }
    }
  }
}

void GraphicSystem::DrawGrids(XMMATRIX& viewMatrix, XMMATRIX& projectionMatrix)
{
  XMFLOAT3 nothing;
  auto deviceContext = m_direct3D->GetDeviceContext();
  deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

  IShader* shader = GetShaderFactory()->Get(GRID_SHADER_NAME);
  shader->EnableShader(deviceContext);
  for (auto& gridAndWorldMatrix : m_gridObjectRenderList)
  {
    gridAndWorldMatrix.second->PrepareToRender(deviceContext);
    shader->Render(deviceContext, gridAndWorldMatrix.second->GetIndexCount(), gridAndWorldMatrix.first, viewMatrix, projectionMatrix, nullptr, nullptr, nothing);
  }
  m_gridObjectRenderList.clear();
}

void GraphicSystem::AddGridToRenderList(GridObject* gridObject, XMMATRIX& worldMatrix)
{
  m_gridObjectRenderList.push_back(std::pair<XMMATRIX, GridObject*>(worldMatrix, gridObject));
}

void GraphicSystem::RenderDeffered(Camera* camera, LightininigSystem* lightiningSystem)
{
  XMMATRIX viewMatrix, projectionMatrix, orthoMatrix, worldMatrix;
  XMMATRIX spaceMatrix;
  XMFLOAT3 spaceFloat3;

 
  m_direct3D->ClearGBufferRenderTargets();
  m_direct3D->DisableBlending();

  camera->GetViewMatrix(viewMatrix);
  camera->GetProjectionMatrix(projectionMatrix);
  camera->GetOrthoMatrix(orthoMatrix);

  m_direct3D->SetGBufferRenderTargets();
  DrawModels(viewMatrix, projectionMatrix, nullptr, camera->GetPosition());

  m_direct3D->SetBackBufferRenderTarget();
  m_direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);
  m_direct3D->DisableDepthTest();
  m_direct3D->SetNullAsDepthBuffer();
    m_direct3D->PrepareToFullScreenDefferedEffect();

  auto ambientDefferedShader = m_shaderFactory->Get(AMBIENT_DEFFERED_SHADER_NAME);
  ambientDefferedShader->EnableShader(m_direct3D->GetDeviceContext());
  ambientDefferedShader->SetTextures(m_direct3D->GetDeviceContext(), m_direct3D->GetGBufferShaderResourceViewes(), GBuffer::SHADER_RESOURCE_VIEW_COUNT);
  ambientDefferedShader->Render(m_direct3D->GetDeviceContext(), 0, spaceMatrix, spaceMatrix, spaceMatrix, nullptr, lightiningSystem, spaceFloat3);
  
  m_direct3D->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
  m_direct3D->EnableAditiveBlending();

  auto depthBufferShader = m_shaderFactory->Get(DEPTH_BUFFER_SHADER_NAME);
  auto pointLightDefferedShader = m_shaderFactory->Get(POINT_LIGHT_DEFFERED_SHADER_NAME);

  camera->GetWorldMatrix(worldMatrix);
  m_pointLightDefferedParemeters.SetViewMatrixInverse(worldMatrix);
  m_pointLightDefferedParemeters.SetPerspectiveValues(projectionMatrix);

  for (auto pointLight : *lightiningSystem->GetPointLights())
  {
    LightininigSystem onePointLightLS;
    onePointLightLS.AddPointLight(pointLight);
    pointLight->GetWorldMatrix(worldMatrix);

    m_direct3D->SetGBufferOnlyWriteableDepthBufferToRenderTargets();
    m_direct3D->ClearGBufferStencil();
    m_direct3D->EnableDepthStencilLightVolumeState();
    m_direct3D->SetCullNoneRasterState();
    depthBufferShader->EnableShader(m_direct3D->GetDeviceContext());
    m_pointLightMesh->PrepareToRender(m_direct3D->GetDeviceContext());
    depthBufferShader->Render(m_direct3D->GetDeviceContext(), m_pointLightMesh->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, nullptr, &onePointLightLS, camera->GetPosition());

    m_direct3D->SetGBufferReadonlyDepthBufferToRenderTargets();
    m_direct3D->EnableDepthStencilDefferedLightState();
    m_direct3D->SetCullFrontRasterState();
    pointLightDefferedShader->SetTextures(m_direct3D->GetDeviceContext(), m_direct3D->GetGBufferShaderResourceViewes(), GBuffer::SHADER_RESOURCE_VIEW_COUNT);
    pointLightDefferedShader->EnableShader(m_direct3D->GetDeviceContext());
    m_pointLightMesh->PrepareToRender(m_direct3D->GetDeviceContext());
    pointLightDefferedShader->Render(m_direct3D->GetDeviceContext(), m_pointLightMesh->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, &m_pointLightDefferedParemeters, &onePointLightLS, camera->GetPosition());
  }

  m_direct3D->SetCullBackRasterState();
  m_direct3D->EnableDepthTest();
  m_direct3D->DisableBlending();

  DrawGrids(viewMatrix, projectionMatrix);

  m_direct3D->EndScene();
}