#include "GameEditor.h"

GameEditor::GameEditor(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    BLLDependencyResolver::GetUnitOfWork()->Initialize(m_hostName, m_databaseName, m_connectionName);
    this->configureUI();
}

void GameEditor::configureUI()
{
  m_mapEditorPreferences = std::unique_ptr<MapEditorPreferences>(new MapEditorPreferences);
  this->ui.actionSnap_to_angle->setChecked(m_mapEditorPreferences->GetSnapToAngleState());
  this->ui.actionSnap_to_grid->setChecked(m_mapEditorPreferences->GetSnapToGridState());

  m_SGOTableWidget = std::unique_ptr<SGOTableWidget>(new SGOTableWidget(m_pathToModels, m_pathToMaterials));
  ui.tabWidget->clear();
  ui.tabWidget->addTab(m_SGOTableWidget.get(), "static game objects"); 

  connect(m_SGOTableWidget.get(), SIGNAL(AddToMap(StaticGameObjectDbInfo&)), this, SLOT(AddSGOToMap(StaticGameObjectDbInfo&)));
  

  m_mapEditorData = std::unique_ptr<MapEditorData>(new MapEditorData(this));
  m_mapEditorData->show();

  m_mapEditor = std::unique_ptr<MapEditor>(new MapEditor(m_mapEditorPreferences.get(), m_mapEditorData->GetSGOOnMapTableWidget()->GetTableModel(), m_pathToModels, m_pathToMaterials, this));
  m_mapEditor->show();

  m_mapEditorData->GetSGOOnMapTableWidget()->SetMapEditor(m_mapEditor.get());

  connect(m_mapEditorData->GetSGOOnMapTableWidget(), SIGNAL(SGOCountChanged()), m_SGOTableWidget.get(), SLOT(UpdateTable()));
  connect(m_SGOTableWidget.get(), SIGNAL(SGODeleted(int)), m_mapEditorData->GetSGOOnMapTableWidget(), SLOT(SGODeleted(int)));
  connect(m_SGOTableWidget.get(), SIGNAL(SGODeleted(int)), m_mapEditor.get(), SLOT(SGODbInfoDeleted(int)));
  connect(m_SGOTableWidget.get(), SIGNAL(SGOEdited(StaticGameObjectDbInfo&)), m_mapEditor.get(), SLOT(SGODbInfoEdited(StaticGameObjectDbInfo&)));
}

void GameEditor::on_actionObjConverter_triggered()
{
  ObjConverterDialog objConverterDialog;
  objConverterDialog.SetPathToGEModels(m_pathToModels);
  objConverterDialog.SetPathToObjModels(m_pathToObjModels);
  objConverterDialog.SetPathToGEMaterials(m_pathToMaterials.toStdString());

  objConverterDialog.exec();
}

void GameEditor::AddSGOToMap(StaticGameObjectDbInfo& gameObject)
{
  m_mapEditorData->GetSGOOnMapTableWidget()->AddSGOToMap(gameObject);
}

void GameEditor::show()
{
  QMainWindow::show();
}

void GameEditor::on_editPreferencesAction_triggered()
{
  MapEditorPreferencesDialog dialog;
  dialog.SetMapEditorPreferences(m_mapEditorPreferences.get());
  dialog.exec();
  this->ui.actionSnap_to_angle->setChecked(m_mapEditorPreferences->GetSnapToAngleState());
  this->ui.actionSnap_to_grid->setChecked(m_mapEditorPreferences->GetSnapToGridState());
}

void GameEditor::on_actionSnap_to_angle_toggled(bool checked)
{
  m_mapEditorPreferences->SetSnapToAngleState(checked);
}

void GameEditor::on_actionSnap_to_grid_toggled(bool checked)
{
  m_mapEditorPreferences->SetSnapToGridState(checked);
}