#pragma once

#include "InputListener.h"
#include "MapEditorPreferences.h"
#include "GEMath.h"

class ConfigurePLRelativePosWidget;
class Logger;
class Camera;
class StaticGameObject;

class ConfigurePLRelPosControl :
  public InputListener
{
protected:
  MapEditorPreferences* m_preferences;
  Camera* m_camera;
  StaticGameObject* m_pointLightSgo;
  ConfigurePLRelativePosWidget* m_configurePLRelativePosWidget;
  float m_timeInSecondsBetweenFrames;
protected:
  void RotateCameraAroundSGO(InputState* inputState);
  void MovePointLight(InputState* inputState);
  void ZoomCamera(InputState* inputState);
public:
  ConfigurePLRelPosControl(ConfigurePLRelativePosWidget* configurePLRelativePosWidget, Camera* camera, StaticGameObject* pointLightSgo, MapEditorPreferences* preferences);
  virtual ~ConfigurePLRelPosControl();
  virtual void ProcessUserInput(InputState* inputState) override;
};

