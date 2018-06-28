#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addstu.h"
#include "querystu.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete q;
    delete a;
    delete add_teacher;
    delete select_course;
}

void MainWindow::on_addStu_triggered()
{
//    addStu a;
//    a.setModal(false);    // 模态对话框
//    a.show();
//    a.exec();
    this->a = new addStu();
    this->a->show();
}

void MainWindow::on_queryStu_triggered()
{
    this->q = new QueryStu();
    this->q->show();
}

void MainWindow::on_addTeacher_triggered()
{
    this->add_teacher = new addTeacher();
    this->add_teacher->show();
}

void MainWindow::on_actionLogin_triggered()
{
    this->ad_login = new administerLogin();
    this->ad_login->show();
}

void MainWindow::on_action_6_triggered()
{
    this->add_course = new addCourse();
    this->add_course->show();
}

void MainWindow::on_stu_login_triggered()
{
    this->select_course = new selectCourse();
    this->select_course->show();
}

void MainWindow::on_teacher_login_triggered()
{
    this->teacher_login = new teacherLogin();
    teacher_login->show();
}
