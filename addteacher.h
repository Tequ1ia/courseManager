#ifndef ADDTEACHER_H
#define ADDTEACHER_H

#include <QDialog>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QPushButton>
#include <QCheckBox>
#include <QFile>
#include <QTextStream>
#include <QIODevice>

namespace Ui {
class addTeacher;
}

class addTeacher : public QDialog
{
    Q_OBJECT

public:
    explicit addTeacher(QWidget *parent = 0);
    ~addTeacher();
    void clearUserInterface();
    void writeToFile(QString content);

private slots:
    void on_bt_confirm_clicked();
    void on_bt_cancle_clicked();

private:
    Ui::addTeacher *ui;
};

#endif // ADDTEACHER_H
