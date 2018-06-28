#include "administerlogin.h"
#include "ui_administerlogin.h"

administerLogin::administerLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::administerLogin)
{
    ui->setupUi(this);
}

administerLogin::~administerLogin()
{
    delete ui;
}

void administerLogin::on_btn_login_clicked()
{
    if(this->ui->le_account->text() == "admin" && this->ui->le_pwd->text() == "admin"){
        int ret = QMessageBox::question(this, "提示", "Login successfull!", "学生管理", "教师管理", "添加课程");
        if(ret == 0){
            this->add_stu = new addStu();
            this->add_stu->show();
        } else if(ret == 1) {
            this->add_teacher = new addTeacher();
            this->add_teacher->show();
        } else {
            this->add_course = new addCourse();
            this->add_course->show();
        }
    }
    else
        QMessageBox::critical(this, "错误", "账号或者密码错误!", "确定");
}

void administerLogin::on_btn_cancel_clicked()
{
    this->close();
}
