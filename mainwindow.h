#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Слот для кнопки "Обчислити"
    void on_btn_calculate_clicked();

    // Слот для кнопки "Очистити"
    void on_btn_clear_clicked();

    // Слот для завантаження з файлу
    void on_actionLoad_from_file_triggered();

    // Слот для збереження у файл
    void on_actionSave_to_file_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
