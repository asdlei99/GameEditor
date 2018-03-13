#pragma once

#include <QWidget>
#include <memory>
#include "ui_MapEditor.h"
#include "QtDirectXWidget.h"
#include "MapEditorViewModel.h"
#include "MapEditorControl.h"

class PointLightVolumeGridObject;
class UnfrozenDrawableBBFactory;
class FrozenDrawableBBFactory;
class GridObject;

class MapEditor : public QtDirectXWidget, public Ui::MapEditor
{
    Q_OBJECT
protected:
  std::shared_ptr<MapEditorControl> m_mapEditorControl;
  std::unique_ptr<MapEditorViewModel> m_mapEditorViewModel;
  std::vector<StaticGameObject*> m_visibleSgos;
  std::vector<StaticGameObject*> m_selectedSgos;
  bool m_testLightiningEnabled = true;
  
  bool m_radiusOfAddingLightSourcesToRenderChanged = true;

  std::unique_ptr<PointLightVolumeGridObject> m_pointLightVolumeGridObject;

  std::unique_ptr<UnfrozenDrawableBBFactory> m_unfrozedDrawableBBFactory;
  std::unique_ptr<FrozenDrawableBBFactory> m_frozedDrawableBBFactory;
protected:
  virtual void paintEvent(QPaintEvent* pEvent) override;
  GridObject* GetSGODrawableBB(const std::string& modelName, bool isFrozen);
public:
  MapEditor(MapEditorPreferences* mapEditorPreferences, QString pathToModels, QString pathToMaterials, QWidget *parent = Q_NULLPTR);
  ~MapEditor();
  MapEditorControl* GetMapEditorControl() { return m_mapEditorControl.get(); }
  void EnableTestLightining(bool testLightining);
  void SetAmbientLight(float red, float green, float blue);
  void RadiusOfAddingLightSourcesToRenderChanged() { m_radiusOfAddingLightSourcesToRenderChanged = true; }
};
