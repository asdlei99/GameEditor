#pragma once

#include <math.h>
#include <QDialog>
#include "ui_AddOrEditPointLightOnMapDialog.h"
#include "PointLightOnMapDbInfo.h"

enum PointLightShadowDirection;

class AddOrEditPointLightOnMapDialog : public QDialog, public Ui::AddOrEditPointLightOnMapDialog
{
    Q_OBJECT
private:
  PointLightOnMapDbInfo m_pointLightOnMap;
protected slots:
  void on_castShadowsCheckBox_clicked(bool checked);
public:
    AddOrEditPointLightOnMapDialog(QWidget *parent = Q_NULLPTR);
    ~AddOrEditPointLightOnMapDialog();
    void SetPointLightOnMap(PointLightOnMapDbInfo pointLight);
    PointLightOnMapDbInfo GetPointLightOnMap();
    void done(int result) override;
};
