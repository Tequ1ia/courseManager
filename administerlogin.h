#ifndef ADMINISTERLOGIN_H
#define ADMINISTERLOGIN_H

#include <QDialog>
#include <QMessageBox>
#include "addstu.h"
#include "addteacher.h"
#include "addcourse.h"

namespace Ui {
class administerLogin;
}

class administerLogin : public QDialog
{
    Q_OBJECT

public:
    explicit administerLogin(QWidget *parent = 0);
    ~administerLogin();

private slots:
    void on_btn_login_clicked();

    void on_btn_cancel_clicked();

private:
    Ui::administerLogin *ui;
    addStu *add_stu;
    addTeacher * add_teacher;
    addCourse *add_course;
};


#endif // ADMINISTERLOGIN_H
