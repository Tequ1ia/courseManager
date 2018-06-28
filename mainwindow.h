#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "addstu.h"
#include "querystu.h"
#include "addteacher.h"
#include "administerlogin.h"
#include "addcourse.h"
#include "selectcourse.h"
#include "teacherlogin.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_addStu_triggered();
    void on_queryStu_triggered();

    void on_addTeacher_triggered();

    void on_actionLogin_triggered();

    void on_action_6_triggered();

    void on_stu_login_triggered();

    void on_teacher_login_triggered();

private:
    Ui::MainWindow *ui;
    QueryStu *q;
    addStu *a;
    addTeacher *add_teacher;
    administerLogin *ad_login;
    addCourse *add_course;
    selectCourse *select_course;
    teacherLogin *teacher_login;
};

#endif // MAINWINDOW_H
