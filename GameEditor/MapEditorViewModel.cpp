#include "MapEditorViewModel.h"


MapEditorViewModel::MapEditorViewModel()
{
  connect(&m_sgoOnMapTM, SIGNAL(FreezeSgoSignal(int)), this, SLOT(FreezeSgo(int)));
  connect(&m_sgoOnMapTM, SIGNAL(UnfreezeSgoSignal(int)), this, SLOT(UnfreezeSgo(int)));
  connect(&m_sgoOnMapTM, SIGNAL(SelectionChanged(std::vector<int>)), this, SLOT(SelectionChanged(std::vector<int>)));
}

void MapEditorViewModel::Initialize(const std::string& pathToModels, ModelFactory* modelFactory, MapEditorPreferences* mapEditorPreferences)
{
  m_pathToModels = pathToModels;
  m_modelFactory = modelFactory;
  m_mapEditorPreferences = mapEditorPreferences;

  InitializeSgos();
}

MapEditorViewModel::~MapEditorViewModel()
{
}


void MapEditorViewModel::InitializeSgos()
{
  for (auto& sgo : m_sgoOnMapTM.GetAll())
  {
    AddSgoToMap(sgo);
  }

  std::map<int, StaticGameObject*> temporarySgoMap;
  for (auto& sgo : m_staticGameObjectMap)
  {
    temporarySgoMap[sgo.first] = &(sgo.second);
  }
  m_octoTree.Initialize(&temporarySgoMap, XMFLOAT3(0.0f, 0.0f, 0.0f), OCT_TREE_CELL_HALF_SIZE);
}

void MapEditorViewModel::AddSgoToMap(SGOOnMapDbInfo& sgoOnMap)
{
  StaticGameObject sgo;
  sgo.SetModel(GetModel(sgoOnMap.staticGameObjectDbInfo.modelFileName.toStdString()));
  sgo.SetPosition(sgoOnMap.xPos, sgoOnMap.yPos, sgoOnMap.zPos);
  sgo.SetRotation(sgoOnMap.xRotate, sgoOnMap.yRotate, sgoOnMap.zRotate);
  sgo.modelId = sgoOnMap.staticGameObjectDbInfo.id;
  sgo.isFrozen = sgoOnMap.isFrozen;
  sgo.uniqueId = sgoOnMap.id;
  m_staticGameObjectMap[sgoOnMap.id] = sgo;
}

Model* MapEditorViewModel::GetModel(const std::string& modelName)
{
  return m_modelFactory->GetResource(m_pathToModels + FileProcessor::FILE_SEPARATOR + modelName);
}

void MapEditorViewModel::AddSgo(SGOOnMapDbInfo& sgoOnMapDbInfo)
{
  m_sgoOnMapTM.append(sgoOnMapDbInfo);
  AddSgoToMap(sgoOnMapDbInfo);
  m_octoTree.AddSgo(sgoOnMapDbInfo.id, &m_staticGameObjectMap[sgoOnMapDbInfo.id]);
}

void MapEditorViewModel::DeleteSgo(int id)
{
  m_sgoOnMapTM.remove(id);
  DeleteSgoFromMap(id);
}

void MapEditorViewModel::DeleteSgoFromMap(int id)
{
  m_octoTree.DeleteSgo(id, &m_staticGameObjectMap[id]);
  m_selectedObjectIds.erase(id);
  m_staticGameObjectMap.erase(id);
}

void MapEditorViewModel::SGODbInfoDeleted(int sgoDbInfoId)
{
  for (auto it = m_staticGameObjectMap.begin(), itEnd = m_staticGameObjectMap.end(); it != itEnd;)
  {
    if (it->second.modelId == sgoDbInfoId)
    {
      m_octoTree.DeleteSgo(it->first, &m_staticGameObjectMap[it->first]);
      m_selectedObjectIds.erase(it->first);
      it = m_staticGameObjectMap.erase(it);
    }
    else
    {
      ++it;
    }
  }

  m_sgoOnMapTM.UpdateData();
}

void MapEditorViewModel::SGODbInfoEdited(StaticGameObjectDbInfo& staticGameObjectDbInfo)
{
  for (auto& sgo : m_staticGameObjectMap)
  {
    if (sgo.second.modelId == staticGameObjectDbInfo.id)
    {
      sgo.second.SetModel(GetModel(staticGameObjectDbInfo.modelFileName.toStdString()));
    }
  }
}

void MapEditorViewModel::EditSgo(SGOOnMapDbInfo& editedGameObject)
{
  m_sgoOnMapTM.edit(editedGameObject);
  EditSgoOnMap(editedGameObject);
}

void MapEditorViewModel::EditSgoOnMap(SGOOnMapDbInfo& editedGameObject)
{
  AddSgoToMap(editedGameObject);
  m_octoTree.ObjectChangedPosition(editedGameObject.id, &m_staticGameObjectMap[editedGameObject.id]);
}

void MapEditorViewModel::FreezeSgo(int id)
{
  m_sgoOnMapTM.FreezeSgo(id);
  m_staticGameObjectMap[id].isFrozen = true;
}

void MapEditorViewModel::UnfreezeSgo(int id)
{
  m_sgoOnMapTM.UnfreezeSgo(id);
  m_staticGameObjectMap[id].isFrozen = false;
}

void MapEditorViewModel::FreezeAll()
{
  for (auto& sgo : m_staticGameObjectMap) 
  {
    sgo.second.isFrozen = true;
  }

  m_sgoOnMapTM.FreezeAll();
}

void MapEditorViewModel::UnfreezeAll()
{
  for (auto& sgo : m_staticGameObjectMap)
  {
    sgo.second.isFrozen = false;
  }

  m_sgoOnMapTM.UnfreezeAll();
}

void MapEditorViewModel::FreezeSelected()
{
  for (int id : m_selectedObjectIds)
  {
    auto sgoInDb = m_sgoOnMapTM.GetEntityByKey(id);
    sgoInDb.isFrozen = true;
    EditSgo(sgoInDb);
  }
}

void MapEditorViewModel::UnfreezeSelected()
{
  for (int id : m_selectedObjectIds)
  {
    auto sgoInDb = m_sgoOnMapTM.GetEntityByKey(id);
    sgoInDb.isFrozen = false;
    EditSgo(sgoInDb);
  }
}

void MapEditorViewModel::SelectionChanged(std::vector<int> selectedSgoIds)
{
  SetSelectedObjectIds(selectedSgoIds);
}

void MapEditorViewModel::GetVisibleSgo(CameraFrustrum* cameraFrustrum, std::vector<StaticGameObject*>* sgosToRender)
{
  sgosToRender->clear();
  m_octoTree.GetVisibleSgo(cameraFrustrum, sgosToRender);
}

void MapEditorViewModel::GetSelectedSgos(std::vector<StaticGameObject*>* selectedSgos)
{
  selectedSgos->clear();
  selectedSgos->reserve(m_selectedObjectIds.size());

  for (int selectedId : m_selectedObjectIds)
  {
    selectedSgos->push_back(&m_staticGameObjectMap[selectedId]);
  }
}