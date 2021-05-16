#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QUrl>

double num_first;
double p = 6, p1 = 2, p2 = 1, p3 = 0.1;
double course = 74.81;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowOpacity(1);
    setStyleSheet("background-color: #f0f0f0;");
    setWindowIcon(QIcon(":/img/img/icon.png"));

    ui->result_show->setAlignment(Qt::AlignRight);
    ui->result_show_2->setAlignment(Qt::AlignRight);
    ui->spinBox->setAlignment(Qt::AlignRight);
    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));
    connect(ui->pushButton_reverse, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_percent, SIGNAL(clicked()), this, SLOT(operations()));
    connect(ui->pushButton_divide, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(math_operations()));
    connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(math_operations()));

    ui->pushButton_divide->setCheckable(true);
    ui->pushButton_plus->setCheckable(true);
    ui->pushButton_minus->setCheckable(true);
    ui->pushButton_mult->setCheckable(true);

    QString t1, t2, t3, t4;
    t1 = "На год под " + QString::number(p) + " процентов годовых\nс начислением процентов по окончанию года";
    t2 = "На год под " + QString::number(p1) + " процентов\nс начислением процентов ежемесячно";
    t3 = "На год с ежедневным начислением " + QString::number(p2) + " рублей\nна каждую полную тысячу вклада";
    t4 = "На год с ежедневным начислением " + QString::number(p3) + " процентов\nна сумму вклада";
    QStringList terms = {t1, t2, t3, t4};
    ui->terms_of_deposit->addItems(terms);

    ui->horizontalSlider->setMinimum(0);
    ui->horizontalSlider->setMaximum(1 * 1);

    ui->course->setText("1 USD = " + QString::number(course) + " RUB");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digits_numbers()
{
    QPushButton* button = (QPushButton*)sender();
    double all_numbers;
    QString new_label;

    if(ui->result_show->text().contains(".") && button->text() == "0") {
        new_label = ui->result_show->text() + button->text();
    } else {
        all_numbers = (ui->result_show->text() + button->text()).toDouble();
        new_label = QString::number(all_numbers, 'g',  15);
    }
     ui->result_show->setText(new_label);
}

void MainWindow::on_pushButton_dot_clicked()
{
    if(!(ui->result_show->text().contains('.')))
        ui->result_show->setText( ui->result_show->text() + ".");
}

void MainWindow::operations()
{
    QPushButton* button = (QPushButton*)sender();
    double all_numbers;
    QString new_label;
    if(button->text() == "±") {
        all_numbers = (ui->result_show->text()).toDouble();
        all_numbers = all_numbers * (-1);
        new_label = QString::number(all_numbers, 'g',  15);
        ui->result_show->setText(new_label);
    } else if(button->text() == '%') {
        all_numbers = (ui->result_show->text()).toDouble();
        all_numbers = all_numbers * (0.01);
        new_label = QString::number(all_numbers, 'g',  15);
        ui->result_show->setText(new_label);
    }
}

void MainWindow::math_operations()
{
    QPushButton* button = (QPushButton*)sender();
    num_first = ui->result_show->text().toDouble();
    QString status_bar;
    status_bar = ui->result_show->text() + " " + button->text() + "  ";
    ui->result_show_2->setText(status_bar);
    ui->result_show->setText("");
    button->setChecked(true);
}

void MainWindow::on_pushButton_all_clear_clicked()
{
    ui->pushButton_plus->setChecked(false);
    ui->pushButton_minus->setChecked(false);
    ui->pushButton_divide->setChecked(false);
    ui->pushButton_mult->setChecked(false);
    ui->result_show->setText("0");
    ui->result_show_2->setText("");
    ui->result_show_3->setText("0");
    num_first = 0;
}

void MainWindow::on_pushButton_clear_clicked()
{
    if(ui->result_show->text() != "0") {
        QString tmp = ui->result_show->text();
        if(tmp.size() == 1) {
            ui->result_show->setText("0");
        }
        else {
        tmp.chop(1);
        ui->result_show->setText(tmp);
        }
    }
}

void MainWindow::on_pushButton_equal_clicked()
{
    double labelNumber, num_second;
    QString new_label;

    num_second = ui->result_show->text().toDouble();

    if(ui->pushButton_plus->isChecked()) {
        labelNumber = num_first + num_second;
        new_label = QString::number(labelNumber);
        ui->result_show->setText(new_label);
        ui->pushButton_plus->setChecked(false);
    } else if(ui->pushButton_minus->isChecked()) {
        labelNumber = num_first - num_second;
        new_label = QString::number(labelNumber);
        ui->result_show->setText(new_label);
        ui->pushButton_minus->setChecked(false);
    } else if(ui->pushButton_divide->isChecked()) {
        if(num_second == 0) ui->result_show->setText("Ошибка!");
        else {
            labelNumber = num_first / num_second;
            new_label = QString::number(labelNumber);
            ui->result_show->setText(new_label);
        }
        ui->pushButton_divide->setChecked(false);
    } else if(ui->pushButton_mult->isChecked()) {
        labelNumber = num_first * num_second;
        new_label = QString::number(labelNumber);
        ui->result_show->setText(new_label);
        ui->pushButton_mult->setChecked(false);
    }
    ui->result_show_2->setText("");
}
void MainWindow::on_ok_clicked()
{
    bool f = 1;
    double sum = ui->result_show->text().toDouble();
    int duration = ui->spinBox->value();
    int term = ui->terms_of_deposit->currentIndex();
    if (ui->comboBox->currentIndex() == 0 && duration % 12 == 0)
        duration /= 12;
    else
        f = 0;
    if((ui->comboBox->currentIndex() == 1 || f) && sum >= 0) {
        switch(term) {
        case 0:
            for(int i = 0; i < duration; i++)
                sum = sum + 0.01*p*sum;
            break;

        case 1:
            for(int i = 0; i < duration * 12; i++)
                sum = sum + 0.01*p1*sum;
            break;
        case 2:
            for(int i = 0; i < duration * 365; i++)
                sum = sum + (int(0.001*sum))*p2;
            break;
        case 3:
            for(int i = 0; i < duration * 365; i++)
                sum = sum + 0.01*p3*sum;
            break;
        }
        ui->result_show_3->setText(QString::number(sum));
    }
    else
        QMessageBox::critical(this, "Ошибка!", "Неверные срок или сумма вклада");
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    double translate = ui->result_show->text().toDouble(),
           translate1 = ui->result_show_3->text().toDouble();
    if(value == 1) {
        ui->result_show->setText(QString::number(translate / course));
        ui->result_show_3->setText(QString::number(translate1 / course));
    }
    else {
        ui->result_show->setText(QString::number(translate * course));
        ui->result_show_3->setText(QString::number(translate1 * course));
    }
}
