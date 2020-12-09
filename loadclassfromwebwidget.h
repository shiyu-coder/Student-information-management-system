#ifndef LOADCLASSFROMWEBWIDGET_H
#define LOADCLASSFROMWEBWIDGET_H

#include <QWidget>
#include<QProcess>
#include<QNetworkAccessManager>
#include<QNetworkRequest>
#include<QList>
#include<lesson.h>
#include<QPainter>
#include<QDate>
#include<QDebug>
#include<QMessageBox>
#include<QList>
#include<QNetworkCookie>
#include<QUrl>
#include<QNetworkReply>
#include<QFile>
#include<QRegExp>
#include<QRegularExpression>
#include<QRegularExpressionMatch>
#include<QListWidget>
#include<QListWidgetItem>
#include<weblogwidget.h>
#include<data.h>
#include<Windows.h>
#include<QTextCodec>

namespace Ui {
class LoadClassFromWebWidget;
}

class LoadClassFromWebWidget : public QWidget
{
    Q_OBJECT

public:
    //利用正则表达式提取课程信息
    void getLessonMsgFromHtml();

    explicit LoadClassFromWebWidget(QWidget *parent = nullptr);
    ~LoadClassFromWebWidget();

private slots:
    void on_getLessonButton_clicked();

    void ReplyFinished(QNetworkReply *reply);

private:
    Ui::LoadClassFromWebWidget *ui;
    //获取课程信息的网址
    QString leUrl;
    //Cookie信息
    QString leCookie;
    //调用负责登录的程序的进程
    QProcess *process;
    //负责网络请求
    QNetworkAccessManager *manager;
    //获取的课程信息(html)
    QString ori_lesson;
    //网络请求
    QNetworkRequest request;
    //暂存的课程信息（QString)
    QStringList lessonList;
};

#endif // LOADCLASSFROMWEBWIDGET_H
