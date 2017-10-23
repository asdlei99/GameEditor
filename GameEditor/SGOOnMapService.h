#pragma once

#include "ISGOOnMapService.h"
#include "IUnitOfWork.h"
#include "BLLDependencyResolver.h"
#include "Utils.h"
#include "SGOMetadata.h"

class SGOOnMapService : public ISGOOnMapService
{
protected:
  IUnitOfWork* m_unitOfWork;
  SGOMetadata m_SGOMetadata;
protected:
  void IncrementSGOCount(int id);
  void DecrementSGOCount(int id);
public:
  SGOOnMapService();
  virtual ~SGOOnMapService();
  virtual SGOOnMapDbInfo Get(int id) override;
  virtual QList<SGOOnMapDbInfo> GetAll() override;
  virtual int Create(SGOOnMapDbInfo& gameObject) override;
  virtual void Update(SGOOnMapDbInfo& gameObject) override;
  virtual void Delete(int id) override;
  virtual QList<SGOOnMapDbInfo> GetFiltered(GetParameters& parameters, PagingInfo& pagingInfo, std::string SGOName = "", std::string instanceName = "") override;
};

