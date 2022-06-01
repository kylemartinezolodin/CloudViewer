#include "poissondialog.h"
#include "ui_poissondialog.h"
#include <iostream>

PoissonDialog::PoissonDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PoissonDialog)
{
    ui->setupUi(this);
}

PoissonDialog::~PoissonDialog()
{
    delete ui;
}

void PoissonDialog::on_comboBoxSpacing_currentIndexChanged(int index)
{
    if(index == 0){
        ui->sampleNighbors->setEnabled(true);
        ui->manualSpacing->setEnabled(false);
    }
    else{
        ui->sampleNighbors->setEnabled(false);
        ui->manualSpacing->setEnabled(true);
    }
}


void PoissonDialog::on_checkBox_stateChanged(int arg1)
{
    bool flag = ui->checkBox->isChecked();
    ui->facetAngle->setEnabled(flag);
    ui->radius->setEnabled(flag);
    ui->distance->setEnabled(flag);
    
}

std::vector<double> PoissonDialog::getAllWidgetsValues() {

    std::vector<double> values;
    values.push_back((double)(ui->sampleNighbors->value()));
    values.push_back((ui->manualSpacing->value()));
    values.push_back((ui->facetAngle->value()));
    values.push_back((ui->radius->value()));
    values.push_back((ui->distance->value()));
    //static double a[5] = { ((double)ui->sampleNighbors->value()), ui->manualSpacing->value(), ui->facetAngle->value(), ui->radius->value(), ui->distance->value()};
    return values;
}

void PoissonDialog::uiValues(int& spacingIndx, // 0 for auto, 1 for manual
    int& sampleNeighbors,
    double& manualSpacing,
    double& facetAngle,
    double& radius,
    double& distance
    ) {
    spacingIndx = ui->comboBoxSpacing->currentIndex();
    sampleNeighbors = (double)(ui->sampleNighbors->value());
    manualSpacing = ui->manualSpacing->value();
    facetAngle = ui->facetAngle->value();
    radius = ui->radius->value();
    distance = ui->distance->value();
}

