#include "dataquery.h"

DataQuery::DataQuery()
{
    this->databaseOnline=false;
}

DataQuery::~DataQuery(){
    db.close();
}

DataQuery* DataQuery::getDataQuery(){
    static DataQuery* dataQuery=nullptr;
    if(dataQuery==nullptr){
        dataQuery=new DataQuery();
    }
    return dataQuery;
}

QString DataQuery::connectToDatabase(QString userName,QString password){
    db=QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("E_Chain_Database");
    db.setUserName(userName);
    db.setHostName("192.168.56.1");
    db.setPassword(password);
    if(!db.open()){
        return "数据库连接失败！";
    }else{
        databaseOnline=true;
        return "";
    }
}

bool DataQuery::canLogInSIMS(QString userName,QString password,int type){
    if(type==1){
        //教师
        if(connectToDatabase("T"+userName,password)==""){
            return true;
        }else{
            return false;
        }
    }else if(type==2){
        //学生
        if(connectToDatabase("S"+userName,password)==""){
            return true;
        }else{
            return false;
        }
    }
    return false;
}

QString DataQuery::init(){
    QFile init_file("SqlCode/CreateTable_New.sql");
    if(init_file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QString sql=init_file.readAll().data();
        this->db.exec(sql);
        if(db.lastError().type()==QSqlError::NoError){
            init_file.close();
            QSqlQuery query;
            QString res;
            QStringList sqls;
            //sqls<<"CREATE TRIGGER Update_CourseInfo ON CourseBasic AFTER UPDATE AS DECLARE @newCno varchar(9), @oldCno varchar(9),  @newClimit SMALLINT, @oldCcur SMALLINT,@newCcur SMALLINT SELECT @newCno=CB2.Cno, @oldCno=CB1.Cno, @newClimit=CB2.Climit,@oldCcur=CB1.Ccur, @newCcur=CB2.Ccur FROM deleted CB1, inserted CB2 IF(@newCno<>@oldCno)OR(@oldCcur<>@newCcur)OR(@newClimit<@oldCcur) BEGIN ROLLBACK TRANSACTION END";
            sqls<<"CREATE TRIGGER UPdate_TeacherInfo ON Teacher AFTER UPDATE AS DECLARE @newTno char(4), @oldTno char(4) SELECT @newTno=T2.Tno, @oldTno=T1.Tno FROM deleted T1, inserted T2 IF(@newTno<>@oldTno) BEGIN ROLLBACK TRANSACTION END";
            sqls<<"CREATE TRIGGER UPdate_StudentInfo ON Student AFTER UPDATE AS DECLARE @newSno char(9), @oldSno char(9) SELECT @newSno=S2.Sno, @oldSno=S1.Sno FROM deleted S1, inserted S2 IF(@newSno<>@oldSno) BEGIN ROLLBACK TRANSACTION END";
            sqls<<"CREATE TRIGGER Delete_Student ON Student AFTER DELETE AS BEGIN DECLARE @delSno char(9) SELECT @delSno=delStu.Sno FROM deleted delStu UPDATE CourseBasic SET Ccur=Ccur-1 WHERE CourseBasic.Cno=(SELECT Cno FROM Stu_Cour, deleted delStu WHERE Stu_Cour.Sno=delStu.Sno) END";
            sqls<<"CREATE TRIGGER Update_sholar_status ON ScholarAppli AFTER UPDATE AS DECLARE @newRes char(1),@oldRes char(1),@money SMALLINT, @sno varchar(10) SELECT @newRes=newSchoAppli.Response, @oldRes=oldSchoAppli.Response,@money=ScholarLst.money, @sno=newSchoAppli.Sno FROM inserted newSchoAppli, deleted oldSchoAppli, ScholarLst WHERE newSchoAppli.Scholarship=ScholarLst.Scholarship IF(@oldRes <>'3') BEGIN ROLLBACK TRANSACTION END ELSE IF(@money>=5000 AND @newRes='1') BEGIN UPDATE ScholarAppli SET Response='2' WHERE Sno=@sno AND Response='3' END";
            sqls<<"CREATE TRIGGER Appli_sholar ON ScholarAppli AFTER INSERT AS DECLARE @newSno varchar(10),@newScholar varchar(20) SELECT @newScholar=A1.Scholarship,@newSno=A1.Sno FROM inserted A1 IF ((SELECT COUNT(ScholarAppli.Scholarship)FROM ScholarLst, ScholarAppli WHERE Sno=@newSno  AND Money>=5000 AND ScholarLst.Scholarship=ScholarAppli.Scholarship AND ScholarAppli.Response='1')>=1) BEGIN ROLLBACK TRANSACTION END";
            //sqls<<"CREATE TRIGGER select_course ON Stu_Cour AFTER INSERT AS DECLARE @newCno varchar(9), @newCterm SMALLINT SELECT @newCno=SC.Cno, @newCterm=SC.Cterm FROM inserted SC IF((SELECT COUNT(CT1.Cno) FROM CTime CT1, CTime CT2 WHERE CT2.Cterm=@newCterm AND CT2.Cno=@newCno AND CT2.Wday=CT1.Wday AND(NOT(CT1.Cbegin>CT2.Cend OR CT2.Cbegin>CT1.Cend)))>=1) BEGIN ROLLBACK TRANSACTION END ELSE BEGIN UPDATE CourseBasic SET Ccur=Ccur+1 WHERE Cno=@newCno END";
            sqls<<"CREATE TRIGGER apply_pro ON ProjectAppli AFTER UPDATE AS DECLARE @newRes varchar(6),@oldRes varchar(6), @sno varchar(10),@NewPro varchar(40)  SELECT @newRes=NPA.Response, @oldRes=OPA.Response, @sno=NPA.Sno, @NewPro=NPA.ProjectName FROM inserted NPA, deleted OPA IF(@oldRes <>'2') BEGIN ROLLBACK TRANSACTION END ELSE IF(@newRes='1' AND (SELECT COUNT(Sno) FROM deleted WHERE deleted.ProjectName=@NewPro AND deleted.Response='1')>=4) BEGIN ROLLBACK TRANSACTION END";
            for(int i=0;i<sqls.size();i++){
                query.exec(sqls.at(i));
                if(query.lastError().type()!=QSqlError::NoError){
                    res+=query.lastError().text();
                }
            }
            if(res==""){
                return "数据库初始化成功！";
            }else{
                return res;
            }

        }else{
            return db.lastError().text();
        }
    }else{
        return "读取CreateTable_New.sql文件读取失败！";
    }
}

QString DataQuery::insertDept(QString dname,QString dintro){
    if(dname==""){
        return "";
    }
    db.exec("insert into Dept values('"+dname+"','"+dintro+"')");
    if(db.lastError().type()==QSqlError::NoError){
        return "";
    }else{
        return db.lastError().text();
    }
}

QString DataQuery::insertLesson(QString cno,QString cname,QString cchar,QString cdept,QString ccredit,QString cgrade){
    //确定选课人数上限
    QString climit = "50";
    QString ccur="0";
    QString sql="insert into CourseBasic values('"+cno+"'";
    if(cchar.size()>0) sql+=",'"+cname+"'";
    else sql+=",NULL";

    sql+=","+climit+","+ccur;

    if(cchar.size()>0) sql+=",'"+cchar+"'";
    else sql+=",NULL";

    if(cdept.size()>0) sql+=",'"+cdept+"'";
    else sql+=",NULL";

    if(ccredit.size()>0) sql+=",'"+ccredit+"'";
    else sql+=",NULL";

    sql+=",'"+cgrade+"')";
    qDebug()<<sql;
    db.exec(sql);
    if(db.lastError().type()==QSqlError::NoError){
        return "";
    }else{
        return db.lastError().text();
    }
}
