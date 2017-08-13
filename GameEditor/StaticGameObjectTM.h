#pragma once

#include <map>
#include <string>
#include <QAbstractTableModel>
#include "DependencyResolver.h"
#include "IStaticGOService.h"
#include "QtUtils.h"
#include "GetParameters.h"
#include "PagingInfo.h"

class StaticGameObjectTM 
  : public QAbstractTableModel
{
protected:
  IStaticGOService* m_staticGOService;
  QList<StaticGameObject> m_data;
  GetParameters m_getParameters;
  PagingInfo m_pagingInfo;

  std::string m_SGONameFilter = "";
  std::string m_modelFileNameFilter = "";
  std::string m_materialFileNameFilter = "";
protected:
  void UpdateData();
public:
  StaticGameObjectTM(QObject * parent = {});
  virtual ~StaticGameObjectTM();
  int rowCount(const QModelIndex &) const override { return m_data.count(); }
  int columnCount(const QModelIndex &) const override { return 4; }
  QVariant data(const QModelIndex &index, int role) const override;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
  void append(StaticGameObject& gameObject);
  void edit(StaticGameObject& gameObject);
  void remove(int id);
  StaticGameObject GetStaticGameObject(int rowNumber);
  PagingInfo GetPagingInfo() { return m_pagingInfo; }
  void UpdateTable(int pageNumber, int onPage, QString OrderFieldName, QString orderDirection, QString SGONameFilter = "", QString SGOModelFilenameFilter = "", QString SGOMaterialFilenameFilter = "");
};

