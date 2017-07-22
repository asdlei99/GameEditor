#include "BumpSingleDirLightShaderCreator.h"


BumpSingleDirLightShaderCreator::BumpSingleDirLightShaderCreator()
{
  m_shaderName = "bump";
}


BumpSingleDirLightShaderCreator::~BumpSingleDirLightShaderCreator()
{
}

IShader* BumpSingleDirLightShaderCreator::Get(const std::wstring& vertexShaderName, const std::wstring& pixelShaderName)
{
  if (m_shader)
  {
    return m_shader;
  }

  m_shader = new BumpSingleDirLightShader();
  m_shader->Initialize(m_device, m_hwnd, vertexShaderName, pixelShaderName);

  return m_shader;
}
