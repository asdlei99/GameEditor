
#include "Camera.h"


Camera::Camera(float screenWidth, float screenHeight, float screenNear, float screenDepth, float fieldOfView)
{
  m_screenWidth = screenWidth;
  m_screenHeight = screenHeight;
  m_screenDepth = screenDepth;
  m_screenNear = screenNear;
  m_fieldOfView = fieldOfView;

  float screenAspect = screenWidth / screenHeight;
  m_projectionMatrix = XMMatrixPerspectiveFovLH(m_fieldOfView, screenAspect, screenNear, screenDepth);
  m_orthoMatrix = XMMatrixOrthographicLH(screenWidth, screenHeight, screenNear, screenDepth);
}


Camera::~Camera()
{
}

void Camera::GetViewMatrix(XMMATRIX& viewMatrix)
{
  GetWorldMatrix(viewMatrix);
  viewMatrix = XMMatrixInverse(nullptr, viewMatrix);
}

void Camera::GetOrthoMatrix(XMMATRIX& orthoMatrix)
{
  orthoMatrix = m_orthoMatrix;
}

void Camera::GetProjectionMatrix(XMMATRIX& projectionMatrix)
{
  projectionMatrix = m_projectionMatrix;
}