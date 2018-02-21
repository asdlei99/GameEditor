#include "PointLightOnMapRepository.h"


PointLightOnMapRepository::PointLightOnMapRepository()
{
}


PointLightOnMapRepository::~PointLightOnMapRepository()
{
}

IRepository<PointLightOnMapDbInfo>* PointLightOnMapRepository::Initialize(std::string connectionName)
{
  m_tableMetadata = std::unique_ptr<PointLightOnMapMetadata>(new PointLightOnMapMetadata());
  m_defaultOrderField = m_tableMetadata->GetDefaultOrderString();

  QtRepository<PointLightOnMapDbInfo>::Initialize(connectionName);
  QSqlQuery query(GetDatabase());

  PointLightMetadata pointLightMetadata;
  SGOOnMapMetadata m_SGOOnMapMetadata;

  QString createTableString = QString("CREATE TABLE IF NOT EXISTS %1 (%2 INTEGER PRIMARY KEY AUTOINCREMENT, %3 INTEGER NOT NULL, %4 INTEGER NOT NULL, %5 REAL NOT NULL, %6 REAL NOT NULL, %7 REAL NOT NULL, %8 REAL NOT NULL, %9 REAL NOT NULL,").arg(m_tableMetadata->GetTableName(), m_tableMetadata->GetKeyColumnName(), m_tableMetadata->GetColumnNames()[0], m_tableMetadata->GetColumnNames()[1], m_tableMetadata->GetColumnNames()[2], m_tableMetadata->GetColumnNames()[3], m_tableMetadata->GetColumnNames()[4], m_tableMetadata->GetColumnNames()[5], m_tableMetadata->GetColumnNames()[6]);

  createTableString = QString("%1 %2 INTEGER NOT NULL, FOREIGN KEY(%3) REFERENCES %4(%5) ON DELETE CASCADE ON UPDATE CASCADE, FOREIGN KEY(%6) REFERENCES %7(%8) ON DELETE CASCADE ON UPDATE CASCADE)").arg(
    createTableString,
    m_tableMetadata->GetColumnNames()[7],
    m_tableMetadata->GetColumnNames()[0], 
    pointLightMetadata.GetTableName(),
    m_tableMetadata->GetRelationShips()[pointLightMetadata.GetTableName()].OtherTablePrimaryKeyName, 
    m_tableMetadata->GetColumnNames()[1],
    m_SGOOnMapMetadata.GetTableName(),
    m_tableMetadata->GetRelationShips()[m_SGOOnMapMetadata.GetTableName()].OtherTablePrimaryKeyName
    );

  query.prepare(createTableString);

  if (!query.exec())
    throw std::runtime_error(Logger::get().GetErrorTraceMessage(query.lastError().text().toStdString(), __FILE__, __LINE__));

  return this;
}