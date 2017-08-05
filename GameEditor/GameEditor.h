#pragma once

#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include "ui_GameEditor.h"
#include "QtUtils.h"
#include "StaticGameObjectTM.h"
#include "BLLDependencyResolver.h"
#include "AddStaticGameObjectDialog.h"
#include "StaticGameObject.h"
#include "PreviewStaticGOWidget.h"

class GameEditor : public QMainWindow
{
    Q_OBJECT
private:
  Ui::GameEditorClass ui;
  std::unique_ptr<StaticGameObjectTM>  m_gameObjectTableModel;
  std::string m_hostName = "hostName";
  std::string m_databaseName = "../GameEditor/database/gameEditor.db";
  std::string m_connectionName = "gameEditorDBConnection";
  QString m_pathToModels = "../GameEditor/models";
  QString m_pathToMaterials = "../GameEditor/materials";
private:
  void createUI();
  void StaticGameObjectBtnsStateConfigure();
private slots:
  void on_addStaticGOBtn_clicked();
  void on_editStaticGOBtn_clicked();
  void on_deleteStaticGOBtn_clicked();
  void on_previewStaticGOBtn_clicked();
  void staticGameObjectTableRowSelected(const QItemSelection& selected, const QItemSelection& deselected);
public:
    GameEditor(QWidget *parent = Q_NULLPTR);
    ~GameEditor() { }
};
