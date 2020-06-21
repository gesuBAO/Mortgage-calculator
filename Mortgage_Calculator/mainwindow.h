#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>
#include <QtCharts/QPieSeries>
#include <Qtcharts/QPieSlice>
#include <QHeaderView>
#include <QTableWidget>
#include <QTableWidgetItem>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class calculator;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_interestRateSlider_valueChanged(int value);

    void on_interestRateSpinBox_valueChanged(double arg1);

    void on_loanTypeComboBox_currentIndexChanged(int index);

    void on_totalAmountLineEdit_textEdited(const QString &arg1);

    void on_loanPeriodSpinBox_valueChanged(int arg1);

    void on_repaymentMethodComboBox_currentIndexChanged(int index);

    void on_mixedInterestRateSlider1_valueChanged(int value);

    void on_interestRateSpinBox_1_valueChanged(double arg1);

    void on_interestRateSpinBox_2_valueChanged(double arg1);

    void on_mixedInterestRateSlider2_valueChanged(int value);

    void on_mixedLoanPeriodSpinBox_valueChanged(int arg1);

    void on_pushButton_released();

    void on_mixedCommercialLineEdit_textEdited(const QString &arg1);

    void on_mixedPublicLineEdit_textEdited(const QString &arg1);

    void on_pushButton_2_released();

private:
    Ui::MainWindow *ui;
    calculator *mortgageCalculator;
    QPieSlice *slice_1;
    QPieSlice *slice_2;
    QPieSeries *series;
    QChart *chart;
    QChartView *chartview;
    QLabel* centralLable;
    QTableWidget *table;

    void setUpControls();
    void setUpChart();
    void refreshChart();
    void refreshTable();
    void setUpTable();
};



#endif // MAINWINDOW_H
