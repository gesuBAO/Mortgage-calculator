#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calculator.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(tr("Mortgage Calculator"));
    setUpChart();
    setUpControls();
    setUpTable();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setUpChart(void)
{
    QPen pen(Qt::black);
    // set up pie slice 1 and it's properties.
    slice_1 = new QPieSlice(QStringLiteral("本金"), 0.71, this);
    slice_1->setLabelVisible(true);
    slice_1->setPen(pen);
    slice_1->setBrush(QColor(15, 126, 92));
    slice_1->setLabelFont(QFont("Microsoft YaHei", 10));
    // set up pie slice 2 and it's properties.
    slice_2 = new QPieSlice(QStringLiteral("利息"), 0.29, this);
    slice_2->setLabelVisible(true);
    slice_2->setPen(pen);
    slice_2->setBrush(QColor(26, 217, 157));
    slice_2->setLabelFont(QFont("Microsoft YaHei", 10));

    series = new QPieSeries(this);
    series->append(slice_1);
    series->append(slice_2);
    series->setHoleSize(0.4);
    series->setPieSize(0.5);
    chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setBackgroundVisible(false);
    chart->legend()->hide();
    chartview = new QChartView(this);
    ui->verticalLayout1->insertWidget(0, chartview);

    centralLable = new QLabel(this->chartview);
    centralLable->setText("比例");
    centralLable->setFont(QFont("Microsoft YaHei", 15, QFont::Bold));
    centralLable->setStyleSheet("color: rgb(82,85,84)");

    chartview->setRenderHint(QPainter::Antialiasing);
    centralLable->move(258, 245);
    chartview->show();
    chartview->setChart(chart);

    return;
} //set up properties and display for the chart
void MainWindow::refreshChart()
{
    double proportion_interest = 0;
    switch (mortgageCalculator->getLoantype())
    {
    case SINGLE:
        proportion_interest = mortgageCalculator->getProportion_interest1();
        break;
    case MIXED:
        proportion_interest = mortgageCalculator->getProportion_interest2();
        break;
    }

    this->slice_1->setValue(1 - proportion_interest);
    this->slice_2->setValue(proportion_interest);
}
void MainWindow::setUpControls(void)
{

    mortgageCalculator = new calculator;

    //sets loan period controls' (loanPeriodSlider)rage in page ONE and connet sgnals and slots of each other
    ui->loanPeriodSlider->setRange(1, 30);
    ui->loanPeriodSlider->setPageStep(5);
    ui->loanPeriodSpinBox->setRange(1, 30);
    connect(ui->loanPeriodSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            ui->loanPeriodSlider, &QSlider::setValue);
    connect(ui->loanPeriodSlider, &QSlider::valueChanged,
            ui->loanPeriodSpinBox, &QSpinBox::setValue);
    ui->loanPeriodSlider->setValue(25);

    //sets loan period controls' (loanPeriodSlider)rage in page TWO and connet sgnals and slots of each other
    ui->mixedLoanPeriodSlider->setRange(1, 30);
    ui->mixedLoanPeriodSlider->setPageStep(5);
    ui->mixedLoanPeriodSpinBox->setRange(1, 30);
    connect(ui->mixedLoanPeriodSpinBox, QOverload<int>::of(&QSpinBox::valueChanged),
            ui->mixedLoanPeriodSlider, &QSlider::setValue);
    connect(ui->mixedLoanPeriodSlider, &QSlider::valueChanged,
            ui->mixedLoanPeriodSpinBox, &QSpinBox::setValue);
    ui->mixedLoanPeriodSlider->setValue(25);

    //confines ranges and sets tick interval of interest rate controls in PAGE1
    ui->interestRateSlider->setRange(1, 5000);
    ui->interestRateSlider->setPageStep(1000);
    ui->interestRateSpinBox->setRange(0.01, 100);
    ui->interestRateSpinBox->setDecimals(2);
    ui->interestRateSpinBox->setSingleStep(0.01);

    //confines ranges and sets tick interval of interest rate controls in PAGE2
    ui->mixedInterestRateSlider1->setRange(1, 5000);
    ui->mixedInterestRateSlider1->setPageStep(1000);
    ui->interestRateSpinBox_1->setRange(0.01, 100);
    ui->interestRateSpinBox_1->setDecimals(2);
    ui->interestRateSpinBox_1->setSingleStep(0.01);

    ui->mixedInterestRateSlider2->setRange(1, 5000);
    ui->mixedInterestRateSlider2->setPageStep(1000);
    ui->interestRateSpinBox_2->setRange(0.01, 100);
    ui->interestRateSpinBox_2->setDecimals(2);
    ui->interestRateSpinBox_2->setSingleStep(0.01);

    //sets options for two combo  boxes
    ui->repaymentMethodComboBox->addItem(tr("等额本息"));
    ui->repaymentMethodComboBox->addItem(tr("等额本金"));
    ui->loanTypeComboBox->addItem(tr("商业贷款"));
    ui->loanTypeComboBox->addItem(tr("公积金贷款"));
    ui->loanTypeComboBox->addItem(tr("组合贷款"));

    //sets range of total-amount line edit
    ui->totalAmountLineEdit->setValidator(new QIntValidator(0, 100000000, this));
    ui->totalAmountLineEdit->setText("1000000");

    ui->mixedCommercialLineEdit->setValidator(new QIntValidator(0, 100000000, this));
    ui->mixedCommercialLineEdit->setText("500000");

    ui->mixedPublicLineEdit->setValidator(new QIntValidator(0, 100000000, this));
    ui->mixedPublicLineEdit->setText("500000");

    return;
}

void MainWindow::setUpTable()
{
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setRowCount(2);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "月份"
                                                             << "还款额"
                                                             << "本金"
                                                             << "利息");

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionMode(QAbstractItemView::NoSelection);
    ui->tableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->tableWidget->horizontalHeader()->setFont(QFont("Microsoft YaHei", 9, QFont::Bold));

    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setAlternatingRowColors(true);

    ui->tableWidget->setColumnWidth(0, 280);
    ui->tableWidget->setColumnWidth(1, 280);
    ui->tableWidget->setColumnWidth(2, 280);
    ui->tableWidget->setColumnWidth(3, 280);

    ui->tableWidget->verticalScrollBar()->setStyleSheet("QScrollBar:vertical{"
                                                        "background:rgb(244,254,251);"
                                                        "padding-top:0px;"
                                                        "padding-bottom:0px;"
                                                        "padding-left:3px;"
                                                        "padding-right:3px;"
                                                        "border-left:1px solid #d7d7d7;}"
                                                        "QScrollBar::handle:vertical{"
                                                        "background:#dbdbdb;"
                                                        "border-radius:6px;"
                                                        "min-height:80px;}"
                                                        "QScrollBar::handle:vertical:hover{"
                                                        "background:#d0d0d0;}"
                                                        "QScrollBar::add-line:vertical{"
                                                        "background:url(:/images/resource/images/checkout/down.png) center no-repeat;}"
                                                        "QScrollBar::sub-line:vertical{"
                                                        "background:url(:/images/resource/images/checkout/up.png) center no-repeat;}");
    //  ui->tableWidget->setStyleSheet(QString( "QTableWidget QHeaderView::section{background:#2a9ee4;font-weight:bold;}"));
    return;
}
void MainWindow::refreshTable()
{

    mortgageCalculator->calculateTableValue(); // refresh all contents stored in QVector schedule
    int totMonth = 0;

    switch (mortgageCalculator->getLoantype())
    {
    case SINGLE:
        totMonth = mortgageCalculator->getLoanPeriod() * 12;
        break;
    case MIXED:
        totMonth = mortgageCalculator->getLoanPeriod_2() * 12;
        break;
    }

    ui->tableWidget->setRowCount(totMonth + 1); //set row for table

    for (int i = 0; i < totMonth; i++)
    {
        eachMonth cur = mortgageCalculator->getTableValue(i);
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(i + 1, 10)));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(cur.total, 10, 2)));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString::number(cur.principle, 10, 2)));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString::number(cur.intrest, 10, 2)));
        ui->tableWidget->item(i, 0)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->item(i, 1)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->item(i, 2)->setTextAlignment(Qt::AlignCenter);
        ui->tableWidget->item(i, 3)->setTextAlignment(Qt::AlignCenter);
    } //print all data in the table
    return;
}

void MainWindow::on_totalAmountLineEdit_textEdited(const QString &totalPrice)
{

    double amount = totalPrice.toDouble();
    mortgageCalculator->setTotalAmount(amount);
    if (amount == 0)
        return;
    double display = mortgageCalculator->refreshDisplay_line();
    ui->MonthlyPaymentlabel->setText(QString::number(display, 10, 2));
    this->refreshChart();
}

void MainWindow::on_interestRateSlider_valueChanged(int value)
{
    ui->interestRateSpinBox->setValue(value / 1000.0);
}

void MainWindow::on_interestRateSpinBox_valueChanged(double arg1)
{
    ui->interestRateSlider->setValue((int)(arg1 * 1000));

    mortgageCalculator->setInterestRate(arg1);

    double display = mortgageCalculator->refreshDisplay_line();
    ui->MonthlyPaymentlabel->setText(QString::number(display, 10, 2));

    this->refreshChart();
}
void MainWindow::on_loanPeriodSpinBox_valueChanged(int arg1)
{

    mortgageCalculator->setLoanPeriod(arg1);
    double display = mortgageCalculator->refreshDisplay_line();
    ui->MonthlyPaymentlabel->setText(QString::number(display, 10, 2));
    QString x = ui->totalAmountLineEdit->text();

    this->refreshChart();
}

void MainWindow::on_mixedCommercialLineEdit_textEdited(const QString &arg1)
{
    double amount = arg1.toDouble();
    mortgageCalculator->setHomePrice_CM(amount);
    double display = mortgageCalculator->refreshDisplay_line2();
    ui->MonthlyPaymentlabel->setText(QString::number(display, 10, 2));
    if (amount == 0)
        return;
    this->refreshChart();
}
void MainWindow::on_mixedPublicLineEdit_textEdited(const QString &arg1)
{
    double amount = arg1.toDouble();
    mortgageCalculator->setHomePrice_PF(amount);
    double display = mortgageCalculator->refreshDisplay_line2();
    ui->MonthlyPaymentlabel->setText(QString::number(display, 10, 2));
    if (amount == 0)
        return;
    this->refreshChart();
}

void MainWindow::on_interestRateSpinBox_1_valueChanged(double arg1)
{
    ui->mixedInterestRateSlider1->setValue((int)(arg1 * 1000));
    mortgageCalculator->setInterestRate_CM(arg1);
    double display = mortgageCalculator->refreshDisplay_line2();
    ui->MonthlyPaymentlabel->setText(QString::number(display, 10, 2));
    if (arg1 == 0)
        return;
    this->refreshChart();
}

void MainWindow::on_mixedInterestRateSlider1_valueChanged(int value)
{
    ui->interestRateSpinBox_1->setValue(value / 1000.0);
}

void MainWindow::on_interestRateSpinBox_2_valueChanged(double arg1)
{
    ui->mixedInterestRateSlider2->setValue((int)(arg1 * 1000));
    mortgageCalculator->setInterestRate_PF(arg1);
    double display = mortgageCalculator->refreshDisplay_line2();
    ui->MonthlyPaymentlabel->setText(QString::number(display, 10, 2));
    if (arg1 == 0)
        return;
    this->refreshChart();
}

void MainWindow::on_mixedInterestRateSlider2_valueChanged(int value)
{
    ui->interestRateSpinBox_2->setValue(value / 1000.0);
}

void MainWindow::on_mixedLoanPeriodSpinBox_valueChanged(int arg1)
{
    mortgageCalculator->setLoanPeriod_2(arg1);
    double display = mortgageCalculator->refreshDisplay_line2();
    ui->MonthlyPaymentlabel->setText(QString::number(display, 10, 2));
    if (arg1 == 0)
        return;
    this->refreshChart();
}

void MainWindow::on_loanTypeComboBox_currentIndexChanged(int index)
{
    double display;
    switch (index)
    {
    case 0:
        ui->loanTypeStackedWidget->setCurrentIndex(0);
        ui->totalAmountLineEdit->setText("1000000");
        mortgageCalculator->setTotalAmount(1000000);
        ui->interestRateSpinBox->setValue(4.75);
        ui->loanPeriodSlider->setValue(25);
        mortgageCalculator->setloanType(SINGLE);
        display = mortgageCalculator->refreshDisplay_line();
        ui->MonthlyPaymentlabel->setText(QString::number(display, 10, 2)); //set all parameters to default value and refresh display
        break;
    case 1:
        ui->loanTypeStackedWidget->setCurrentIndex(0);
        ui->totalAmountLineEdit->setText("1000000");
        mortgageCalculator->setTotalAmount(1000000);
        ui->interestRateSpinBox->setValue(3.75);
        ui->loanPeriodSlider->setValue(25);
        mortgageCalculator->setloanType(SINGLE);
        display = mortgageCalculator->refreshDisplay_line();
        ui->MonthlyPaymentlabel->setText(QString::number(display, 10, 2)); //set all parameters to default value and refresh display
        break;
    case 2:
        ui->loanTypeStackedWidget->setCurrentIndex(1);
        ui->mixedCommercialLineEdit->setText("500000");
        ui->mixedPublicLineEdit->setText("500000");
        mortgageCalculator->setHomePrice_CM(500000);
        mortgageCalculator->setHomePrice_PF(500000);
        ui->interestRateSpinBox_1->setValue(3.75);
        ui->interestRateSpinBox_2->setValue(3.75);
        ui->mixedLoanPeriodSlider->setValue(25);
        mortgageCalculator->setloanType(MIXED);
        display = mortgageCalculator->refreshDisplay_line2();
        ui->MonthlyPaymentlabel->setText(QString::number(display, 10, 2)); //set all parameters to default value and refresh display
        break;
    }
    this->refreshChart();
}

void MainWindow::on_repaymentMethodComboBox_currentIndexChanged(int index)
{
    switch (index)
    {
    case 0:
        ui->resultDisplayPage->setCurrentIndex(0);
        mortgageCalculator->setRepaymentMethod(FIXED_PAYMENT);
        break;
    case 1:
        ui->resultDisplayPage->setCurrentIndex(1);
        mortgageCalculator->setRepaymentMethod(FIXED_BASIS);
        break;
    }
    double display = 0;
    switch (mortgageCalculator->getLoantype())
    {
    case SINGLE:
        display = mortgageCalculator->refreshDisplay_line();
        break;
    case MIXED:
        display = mortgageCalculator->refreshDisplay_line2();
        break;
    }
    ui->MonthlyPaymentlabel->setText(QString::number(display, 10, 2));
    this->refreshChart();
} //when the index of repaymentMethodComboBox changes, switch repaymentmethod and refresh display

void MainWindow::on_pushButton_released()
{
    this->refreshTable();
    ui->centralStackedWidget->setCurrentIndex(1);
} // when button released, switch into full schedule page

void MainWindow::on_pushButton_2_released()
{
    ui->centralStackedWidget->setCurrentIndex(0);

} // when button released, back to previous page
