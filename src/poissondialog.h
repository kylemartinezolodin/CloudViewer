#ifndef POISSONDIALOG_H
#define POISSONDIALOG_H

#include <QDialog>
//#inlude <>
namespace Ui {
class PoissonDialog;
}

class PoissonDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PoissonDialog(QWidget *parent = nullptr);
    ~PoissonDialog();
    Ui::PoissonDialog* ui;

    std::vector<double> getAllWidgetsValues();

    void uiValues(int &spacingIndx, // 0 for auto, 1 for manual
        int &sampleNeighbors,
        double &manualSpacing,
        double &facetAngle,
        double &radius,
        double &distance
        );


private slots:
    void on_comboBoxSpacing_currentIndexChanged(int index);

    void on_checkBox_stateChanged(int arg1);

private:
    //Ui::PoissonDialog* ui;
};

#endif // POISSONDIALOG_H
