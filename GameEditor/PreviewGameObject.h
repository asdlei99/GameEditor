#pragma once

#include <cstdlib>
#include <math.h>
#include "InputListener.h"
#include "Camera.h"
#include "Logger.h"
#include "Model.h"

class PreviewGameObject :
  public InputListener
{
protected:
  const float m_scaleCoef = 0.05f;
  const float m_rotateCoef = 0.01f;
  const float rotateYAngle = 0.1f;
  Camera* m_camera;
  Model* m_model;
  bool m_rotateSwicher;
  bool spacePressed;
public:
  PreviewGameObject();
  virtual ~PreviewGameObject();
  void SetCamera(Camera* camera) { m_camera = camera; }
  void SetModel(Model* model) { m_model = model; }
  virtual void ProcessUserInput(InputState* inputState) override;
};

