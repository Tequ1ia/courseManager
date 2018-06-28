#ifndef TEACHERLOGIN_H
#define TEACHERLOGIN_H

#include <QDialog>
#include <QFile>
#include <QList>
#include <QString>
#include <QDebug>
#include <QTextStream>
#include <QMessageBox>
#include <QStringList>
#include <QStandardItem>
#include <QStandardItemModel>

namespace Ui {
class teacherLogin;
}

class teacherLogin : public QDialog
{
    Q_OBJECT

public:
    explicit teacherLogin(QWidget *parent = 0);
    ~teacherLogin();
    int readFromFile(QString file_name);

private slots:
    void on_btn_login_clicked();

    void on_cbb_course_currentIndexChanged(int index);

    void on_btn_submit_clicked();

    void on_btn_save_clicked();

private:
    Ui::teacherLogin *ui;
    QList<QString> teacher_info;
    QList<QString> course_info;
    QList<QString> student_info;
};

#endif // TEACHERLOGIN_H
