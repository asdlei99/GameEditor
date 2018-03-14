#pragma once

#include <memory>
#include <string>
#include "IRepository.h"
#include "StaticGameObjectDbInfo.h"
#include "SGOOnMapDbInfo.h"
#include "PointLightDbInfo.h"
#include "PointLightOnMapDbInfo.h"
#include <QSqlDatabase.h>

class IUnitOfWork 
{
public:
  IUnitOfWork() {}
  virtual ~IUnitOfWork() {}
  virtual void Initialize(std::string hostName, std::string databaseName, std::string connectionName) = 0;
  virtual std::shared_ptr<IRepository<StaticGameObjectDbInfo> > GetStaticGORepository() = 0;
  virtual std::shared_ptr<IRepository<SGOOnMapDbInfo> > GetSGOOnMapRepository() = 0;
  virtual  std::shared_ptr<IRepository<PointLightDbInfo> > GetPointLightRepository() = 0;
  virtual std::shared_ptr<IRepository<PointLightOnMapDbInfo> > GetPointLightOnMapRepository() = 0;
  virtual QSqlDatabase GetDatabase() = 0; //TODO FHolod: ���������� �������� �� �� ����� ������������ �� Qt � ���� ������
};