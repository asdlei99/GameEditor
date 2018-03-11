#pragma once

#include <QWidget>
#include <QDialog>
#include "ui_QtDirectXWidget.h"
#include <QMessageBox>
#include <string>
#include <memory>
#include "InputSystem.h"
#include "ShaderConfiguration.h"
#include "GraphicSystem.h"

class LightininigSystem;
class Camera;

class QtDirectXWidget : public QWidget, public Ui::QtDirectXWidget
{
    Q_OBJECT
protected:
  const std::string m_pathToModels;
  const std::string m_pathToMaterials;

  bool m_fullScreen = false;
  bool m_vsyncEnabled = false;
  float m_screenDepth = 20000.0f;
  float m_screenNear = 0.1f;

  int m_minWidth = 800;
  int m_minHeight = 600;

  std::unique_ptr<InputSystem> m_inputSystem;
  std::unique_ptr<Camera> m_Camera;

  std::unique_ptr<ShaderConfiguration> m_shaderConfiguration;
  std::unique_ptr<LightininigSystem> m_lightininigSystem;
  std::unique_ptr<GraphicSystem> m_graphicSystem;

protected:
  /** Destroys the D3D environment */
  void Shutdown();

  /** paints the scene */
  virtual void paintEvent(QPaintEvent* pEvent);
  Model* GetModel(const std::string& modelName);
public:
  QtDirectXWidget(QString pathToModels, QString pathToMaterials, QWidget *parent = Q_NULLPTR);
  ~QtDirectXWidget();

  /** Initialized the D3D environment */
  bool Initialize(int screenWidth, int screenHeight, HWND hwnd);

  ModelFactory* GetModelFactory() { m_graphicSystem->GetModelFactory(); }

  /** a hint to Qt to give the widget as much space as possible */
  QSizePolicy sizePolicy() const { return QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); }

  /** a hint to Qt that we take care of the drawing for ourselves, thankyouverymuch */
  QPaintEngine *paintEngine() const { return NULL; }

  virtual void resizeEvent(QResizeEvent* evt);
};
