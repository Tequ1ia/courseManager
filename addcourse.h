#ifndef ADDCOURSE_H
#define ADDCOURSE_H

#include <QDialog>
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QPushButton>
#include <QCheckBox>
#include <QFile>
#include <QTextStream>
#include <QIODevice>
#include <QList>

namespace Ui {
class addCourse;
}

class addCourse : public QDialog
{
    Q_OBJECT

public:
    explicit addCourse(QWidget *parent = 0);
    ~addCourse();
    bool writeToFile(QString content);
    void clearUserInterface();
    int get_primary_key();

private slots:
    void on_btn_confirm_clicked();
    void on_btn_cancel_clicked();

private:
    Ui::addCourse *ui;
};

#endif // ADDCOURSE_H
