#include "StaticGameObject.h"


StaticGameObject::StaticGameObject()
{
}


StaticGameObject::~StaticGameObject()
{
}

void StaticGameObject::SetModel(Model* model)
{
  m_model = model;
  m_drawableBoundingBox.Initialize(model->GetBoundingBox());
  RebuildBBInWorldCoord();
}

void StaticGameObject::RebuildBBInWorldCoord()
{
  BoundingBox* modelBB = this->GetModel()->GetBoundingBox();
  XMFLOAT3 modelBBMinPoint = modelBB->GetMinPoint();
  XMFLOAT3 modelBBMaxPoint = modelBB->GetMaxPoint();
  XMMATRIX worldMatrix;
  this->GetWorldMatrix(worldMatrix);

  m_bbInWorldCoord.Initialize(modelBBMinPoint.x, modelBBMinPoint.y, modelBBMinPoint.z, modelBBMaxPoint.x, modelBBMaxPoint.y, modelBBMaxPoint.z, worldMatrix);
}
