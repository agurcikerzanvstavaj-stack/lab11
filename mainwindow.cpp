#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <cmath>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // Встановлюємо заголовок вікна
    this->setWindowTitle("Задача 35 – Параметри кола");
}

MainWindow::~MainWindow()
{
    delete ui;
}

// Обробник кнопки "Обчислити"
void MainWindow::on_btn_calculate_clicked()
{
    // Константа π
    const double PI = 3.14;

    // Декларація змінних
    double S, D, L;
    bool ok;

    // Зчитуємо введене значення площі
    S = ui->le_S->text().toDouble(&ok);

    // Перевірка коректності введення
    if (!ok || S <= 0) {
        QMessageBox::warning(this, "Помилка введення",
                             "Будь ласка, введіть коректне додатнє число для площі S!");
        ui->le_S->clear();
        ui->le_S->setFocus();
        // Очищаємо поля результатів
        ui->lbl_D_result->setText("—");
        ui->lbl_L_result->setText("—");
        return;
    }

    // Обчислення діаметра: S = π·D²/4  =>  D = 2·√(S/π)
    D = 2.0 * sqrt(S / PI);

    // Обчислення довжини кола: L = π·D
    L = PI * D;

    // Виведення результатів (6 знаків після коми)
    ui->lbl_D_result->setText(QString::number(D, 'f', 6));
    ui->lbl_L_result->setText(QString::number(L, 'f', 6));
}

// Обробник кнопки "Очистити"
void MainWindow::on_btn_clear_clicked()
{
    // Очищаємо всі поля
    ui->le_S->clear();
    ui->lbl_D_result->setText("—");
    ui->lbl_L_result->setText("—");
    ui->le_S->setFocus();
}

// Завантаження вхідних даних з файлу
void MainWindow::on_actionLoad_from_file_triggered()
{
    // Відкриваємо діалог вибору файлу
    QString filePath = QFileDialog::getOpenFileName(
        this, "Відкрити файл", QDir::currentPath(),
        "Текстові файли (*.txt);;Усі файли (*)");

    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, "Помилка", "Не вдається відкрити файл!");
        } else {
            QTextStream in(&file);
            QString sS;
            in >> sS;                    // зчитуємо значення S
            ui->le_S->setText(sS);
            file.close();
        }
    } else {
        QMessageBox::warning(this, "Помилка", "Файл не обрано!");
    }
}

// Збереження результатів у файл
void MainWindow::on_actionSave_to_file_triggered()
{
    // Перевіряємо, чи є результати для збереження
    if (ui->lbl_D_result->text() == "—" || ui->lbl_L_result->text() == "—") {
        QMessageBox::information(this, "Увага",
                                 "Спочатку виконайте обчислення!");
        return;
    }

    // Відкриваємо діалог збереження файлу
    QString filePath = QFileDialog::getSaveFileName(
        this, "Зберегти файл", QDir::currentPath(),
        "Текстові файли (*.txt);;Усі файли (*)");

    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QMessageBox::critical(this, "Помилка",
                                  "Не вдається зберегти файл:\n" + file.errorString());
        } else {
            QTextStream out(&file);
            // Записуємо вхідні дані та результати
            out << "S = " << ui->le_S->text()         << "\n";
            out << "D = " << ui->lbl_D_result->text() << "\n";
            out << "L = " << ui->lbl_L_result->text() << "\n";
            file.close();
        }
    } else {
        QMessageBox::warning(this, "Помилка", "Файл не обрано!");
    }
}
