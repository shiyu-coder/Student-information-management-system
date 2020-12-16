#include "weblogwidget.h"
#include "ui_weblogwidget.h"

WebLogWidget::WebLogWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WebLogWidget)
{
    ui->setupUi(this);
    //加载登录界面
    logView=new QWebEngineView(this);
    logView->load(QUrl("http://elite.nju.edu.cn/jiaowu/index.jsp"));
    logView->resize(this->size());

    logView->show();

    logCookie.insert("CNZZDATA2416398","cnzz_eid%3D492131341-1567131453-http%253A%252F%252Fauthserver.nju.edu.cn%252F%26ntime%3D1569392997");

    //关联槽函数
    connect(logView->page()->profile()->cookieStore(), &QWebEngineCookieStore::cookieAdded,this,&WebLogWidget::getCookie);

    QApplication::setQuitOnLastWindowClosed(true);
}

void WebLogWidget::getCookie(const QNetworkCookie &cookie){
    logCookie.insert(cookie.name(),cookie.value());
    qDebug()<<"Cookie Added-->"<< cookie.domain()<<cookie.name()<<cookie.value()<< endl;
    if(cookie.name()=="user_id"){
        saveCookieInData();
    }
}

void WebLogWidget::saveCookieInData(){
    Data* data=Data::getData();
    QString content;
    content+="JSESSIONID="+logCookie["JSESSIONID"]+"; ";
    content+="ARRAffinity="+logCookie["ARRAffinity"]+"; ";
    content+="CNZZDATA2416398="+logCookie["CNZZDATA2416398"]+"; ";
    content+="user_id="+logCookie["user_id"]+"; ";
    data->cookie=content;
    this->destroy();
}

WebLogWidget::~WebLogWidget()
{
    delete ui;
}
