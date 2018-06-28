#ifndef SELECTCOURSE_H
#define SELECTCOURSE_H

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
class selectCourse;
}

class selectCourse : public QDialog
{
    Q_OBJECT

public:
    explicit selectCourse(QWidget *parent = 0);
    ~selectCourse();
    int readFromFile(QString file_name);
    void setHeaderItem();
    void display();

private slots:
    void on_btn_login_clicked();

    void on_cbb_course_type_currentIndexChanged(int index);

    void on_btn_add_course_clicked();

    void on_btn_delete_course_clicked();

    void on_btn_submit_clicked();

    void on_btn_query_clicked();

//    void on_btn_display_courses_clicked();

    void on_btn_query_scores_clicked();

private:
    Ui::selectCourse *ui;
    QList<QString> stu_info;
    QList<QString> course_info;
    QStandardItemModel *model;
    QStandardItemModel *model_courses;
    QStandardItemModel *model_scores;
    QList<QString> selected_courses;
    QSet<QString> total_selected_courses;
};

#endif // SELECTCOURSE_H
