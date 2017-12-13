#include "StaticGOService.h"


StaticGOService::StaticGOService()
{
  m_unitOfWork = BLLDependencyResolver::GetUnitOfWork();
}


StaticGOService::~StaticGOService()
{
}

StaticGameObjectDbInfo StaticGOService::GetStaticGameObject(int id)
{
  return m_unitOfWork->GetStaticGORepository()->Get(id);
}

QList<StaticGameObjectDbInfo> StaticGOService::GetStaticGameObjects()
{
  std::vector<StaticGameObjectDbInfo> gameObjects = m_unitOfWork->GetStaticGORepository()->GetAll();

  QList<StaticGameObjectDbInfo> qListGameObjects;
  qListGameObjects.reserve(gameObjects.size());

  std::copy(gameObjects.begin(), gameObjects.end(), std::back_inserter(qListGameObjects));

  return qListGameObjects;
}

int StaticGOService::CreateStaticGameObject(StaticGameObjectDbInfo& gameObject)
{
  int entityId = m_unitOfWork->GetStaticGORepository()->Create(gameObject);
  gameObject.id = entityId;
  return entityId;
}

void StaticGOService::UpdateStaticGameObject(StaticGameObjectDbInfo& gameObject)
{
  m_unitOfWork->GetStaticGORepository()->Update(gameObject);
}

void StaticGOService::DeleteStaticGameObject(int id)
{
  m_unitOfWork->GetStaticGORepository()->Delete(id);
}

QList<StaticGameObjectDbInfo> StaticGOService::GetFiltered(GetParameters& parameters, PagingInfo& pagingInfo, std::string name, std::string model)
{
  std::vector<std::string> whereParams;
  std::string whereParamsGlue = " AND ";
  parameters.whereCondition = "";
  bool filteringIsEnabled = false;
  std::vector<StaticGameObjectDbInfo> gameObjects;
  QList<StaticGameObjectDbInfo> qListGameObjects;

  if (!name.empty()) {
    whereParams.push_back(" " + m_metadata.GetAlias(0).toStdString() + " LIKE '%" + name + "%' ");
    filteringIsEnabled = true;
  }

  if (!model.empty()) {
    whereParams.push_back(" " + m_metadata.GetAlias(1).toStdString() + " LIKE '%" + model + "%' ");
    filteringIsEnabled = true;
  }

  if (filteringIsEnabled)
    parameters.whereCondition = Utils::Join(whereParams, whereParamsGlue);

  else
    parameters.whereCondition = "1";

  gameObjects = m_unitOfWork->GetStaticGORepository()->GetAll(parameters, pagingInfo);
  qListGameObjects.reserve(gameObjects.size());
  std::copy(gameObjects.begin(), gameObjects.end(), std::back_inserter(qListGameObjects));

  return qListGameObjects;
}