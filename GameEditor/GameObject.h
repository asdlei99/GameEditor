#pragma once

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <d3d11.h>
#include <directxmath.h>

using namespace DirectX;

class GameObject
{
private:
  XMMATRIX m_translationMatrix;
  XMMATRIX m_rotationMatrix;
  XMMATRIX m_worldMatrix;
  bool m_needRebuildTranslationMatrix;
  bool m_needRebuildRotationMatrix;
  float m_positionX, m_positionY, m_positionZ;
  float m_rotationX, m_rotationY, m_rotationZ;

  GameObject* m_parent;
public :
  bool needRebuildDependOnWorldMatrix = true; // ��� ����������� ��� ����� ����������� ������� � ����������� ��������� �� ��������� ������� ������� ���������, �������� bounding box
public:
  GameObject();
  virtual ~GameObject();

  void SetPosition(float x, float y, float z);
  void SetRotation(float x, float y, float z);
  XMFLOAT3 GetPosition();
  XMFLOAT3 GetRotation();
  void ChangeXRotation(float angle);
  void ChangeYRotation(float angle);
  void ChangeZRotation(float angle);

  void virtual GetWorldMatrix(XMMATRIX& worldMatrix);
  void SetWorldMatrix(XMMATRIX worldMatrix);

  XMVECTOR GetRight();
  XMVECTOR GetUp();
  XMVECTOR GetForward();

  void MoveRight(float distance);
  void MoveUp(float distance);
  void MoveForward(float distance);

  inline bool NeedRebuildWorldMatrix() { return m_needRebuildTranslationMatrix || m_needRebuildRotationMatrix; }

  void SetParent(GameObject* gameObject) { m_parent = gameObject; }
  void GetParentMatrix(XMMATRIX& parentMatrix) const;
};

