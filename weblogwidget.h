#ifndef WEBLOGWIDGET_H
#define WEBLOGWIDGET_H

#include <QWidget>
#include<QNetworkCookie>
#include<QMap>
#include<QWebEngineView>
#include<QUrl>
#include<QWebEngineCookieStore>
#include<QWebEngineProfile>
#include<QtWebView/QtWebView>
#include<QTextStream>
#include<iostream>
#include<data.h>
namespace Ui {
class WebLogWidget;
}

class WebLogWidget : public QWidget
{
    Q_OBJECT

public:
    explicit WebLogWidget(QWidget *parent = nullptr);
    ~WebLogWidget();

    void getCookie(const QNetworkCookie &cookie);

    void saveCookieInData();

private:
    Ui::WebLogWidget *ui;
    QMap<QString,QString> logCookie;
    QWebEngineView *logView;
};

#endif // WEBLOGWIDGET_H
