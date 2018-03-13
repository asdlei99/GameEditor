#include "QtDirectXWidget.h"
#include "LightininigSystem.h"
#include "Camera.h"
#include "PathesToShaderSet.h"
#include "ShaderConfiguration.h"

QtDirectXWidget::QtDirectXWidget(
  const std::string& pathToModels,
  const std::string& pathToMaterials, 
  const PathesToShaderSet& pathesToShaderSet,
  QWidget *parent)
  : QWidget(parent),
  m_pathToModels(pathToModels), 
  m_pathToMaterials(pathToMaterials),
  m_inputSystem(nullptr),
  m_Camera(nullptr),
  m_shaderConfiguration(new ShaderConfiguration(pathesToShaderSet)),
  m_lightininigSystem(nullptr),
  m_graphicSystem(nullptr)
{
  m_screenDepth = 10000.0f;

  setupUi(this);

  this->setWindowFlags(Qt::Window);

  setMinimumSize(m_minWidth, m_minHeight);
  setAttribute(Qt::WA_OpaquePaintEvent, true);
  setAttribute(Qt::WA_PaintOnScreen, true);
  setAttribute(Qt::WA_NativeWindow, true);

  bool result = Initialize(width(), height(), (HWND)winId());
  if (!result) {
    QMessageBox::critical(this,
      "ERROR",
      "Faild initialize QD3Dwidget",
      QMessageBox::Ok);
  }
}

QtDirectXWidget::~QtDirectXWidget()
{
  
}

bool QtDirectXWidget::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
  bool result;

  m_shaderConfiguration->ConfigureForwardRenderer();

  m_graphicSystem = std::unique_ptr<GraphicSystem>(new GraphicSystem);
  if (!m_graphicSystem)
    return false;

  m_graphicSystem->Initialize(screenWidth, screenHeight, m_vsyncEnabled, hwnd, m_fullScreen, m_shaderConfiguration.get(), m_pathToMaterials, m_pathToModels);

  // Create the camera object.
  m_Camera = std::unique_ptr<Camera>(new Camera());
  m_Camera->Initialize(screenWidth, screenHeight, m_screenNear, m_screenDepth);
  if (!m_Camera)
  {
    return false;
  }

  m_Camera->SetPosition(0.0f, 0.0f, -100.0f);

  m_lightininigSystem = std::unique_ptr<LightininigSystem>(new LightininigSystem());
  if (!m_lightininigSystem)
  {
    return false;
  }
  m_lightininigSystem->SetDirectLightDirection(1.0f, 0.0f, 1.0f);
  m_lightininigSystem->SetDirectLightColor(1.0f, 1.0f, 1.0f, 1.0f);
  m_lightininigSystem->SetAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);

  m_inputSystem = std::unique_ptr<InputSystem>(new InputSystem());
  m_inputSystem->Initialize(GetModuleHandle(NULL), hwnd);
  
  return true;
}

void QtDirectXWidget::paintEvent(QPaintEvent* evt) {
  m_inputSystem->Frame();
  m_graphicSystem->Render(m_Camera.get(), m_lightininigSystem.get());
  // trigger another update as soon as possible 
  update();
}

void QtDirectXWidget::resizeEvent(QResizeEvent* evt)
{
  //TODO FHolod: update resource which depends on aspect ration
  float width = this->width();
  float height = this->height();
  m_Camera->Initialize(width, height, m_screenNear, m_screenDepth);
}

Model* QtDirectXWidget::GetModel(const std::string& modelName)
{
  return m_graphicSystem->GetModelFactory()->GetResource(m_pathToModels + FileProcessor::FILE_SEPARATOR + modelName);
}