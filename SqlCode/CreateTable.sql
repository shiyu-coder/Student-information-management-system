create table Systbl(
    adminNotice SMALLINT,/*0-no 1-yes，管理员一上线系统就对这个量进行检查，如果是1，说明有人向管理员提交申请待处理，提醒管理员处理表S2A & T2A中的内容*/
    stuNum SMALLINT,/*学生总人数*/
)

create table Dept(
    Dname varchar(30) PRIMARY KEY,
    Dintro varchar(200),/*introduction*/
)

create table Student(
    Sno char(9) PRIMARY KEY,/*学号，每位都是数字字符*/
    Sname varchar(10),
    Ssex char(2),/*约束：男or女*/
    Sdept varchar(30),/**/
    Sgrade smallint,/*入学年级*/
    FOREIGN KEY(Sdept) REFERENCES Dept(Dname),
)

create table Teacher(
    Tno char(9) PRIMARY KEY,/*工号，每位都是数字字符*/
    Tname varchar(10),
    Tprof varchar(10),/*教师职称*/
    Tdept varchar(30),
    Tnotice SMALLINT,/*0-no 1-yes，教师一上线系统就对这个量进行检查，如果是1，说明有人向教师提交申请待处理*/
    FOREIGN KEY(Tdept) REFERENCES Dept(Dname),
)

/*
*ATTENTION，假设条件
*一学期中，一门课只由一个老师教授，只开一次，即不存在1班2班的情况
*每门课的开课周数一样，每门课只有一个上课地点
*/
create table CourseBasic(
    Cno varchar(9)PRIMARY KEY,
    Cname varchar(30),
    Climit SMALLINT,/*选课人数上限*/
    Ccur SMALLINT,/*当前选课人数，每选课成功一个人，就要用Trigger更新*/
    Cdept varchar(30),
    Cgrade SMALLINT,/*开课年级*/
    FOREIGN KEY(Cdept) REFERENCES Dept(Dname),

)

create table CTime(
    Cno varchar(9),
    Cterm SMALLINT, /*限制1，2*/
    Weekday SMALLINT,
    Cbegin SMALLINT,
    Cend SMALLINT,
    FOREIGN KEY(Cno) REFERENCES CourseBasic(Cno),
    PRIMARY KEY(Cno, Cterm, Weekday, Cbegin, Cend)
)
/*选课操作考虑的因素*/

create table Tcourse(/*教师教课表*/
    Cno varchar(9),
    Tno char(9),
    Cterm SMALLINT, /*限制1，2*/
    FOREIGN KEY(Cno) REFERENCES CourseBasic(Cno),
    FOREIGN KEY(Tno) REFERENCES Teacher(Tno),
    PRIMARY KEY(Cno, Tno, Cterm)
    /*在当前学期的语境下，不需要指明学期*/
)

create table Stu_Cour(
    Sno char(9),
    Cno varchar(9), 
    Cterm SMALLINT, /*限制1，2*/
    Grade SMALLINT,
    PRIMARY KEY(Sno, Cno, Cterm),
    FOREIGN KEY(Cno) REFERENCES CourseBasic(Cno),
    FOREIGN KEY(Sno) REFERENCES Student(Sno),
)

/*教师和学生都会进行一些申请操作，这里的表是向管理员申请，即需要在学生界面有“退课，请假一个窗口”，教师界面都有一个“修改课程信息”的窗口，输入的内容其实最终填写到这张表中。在填写完毕之后，是Sys表中的AdminNotice变成1*/
/*！！！一个表不可以，一个列好像不能绑两个外键...*/
create table T2A(
    Tno char(9) NOT NULL,/*申请老师工号*/
    Rcontent varchar(200) NOT NULL,/*申请内容：请假，退课，修改课程人数上限之类的*/
    Response varchar(50),/*Admin反馈*/
    FOREIGN KEY(Tno) REFERENCES Teacher(Tno),
    PRIMARY KEY(Tno, Rcontent),
)

create table S2A(
    Sno char(9) NOT NULL,/*申请学生学号*/
    Rcontent varchar(200) NOT NULL,/*申请内容：请假，退课，修改课程人数上限之类的*/
    Response varchar(50),/*Admin反馈*/
    FOREIGN KEY(Sno) REFERENCES Student(Sno),
    PRIMARY KEY(Sno, Rcontent),
)


/*学生还会向老师申请报名大创项目
申请报名大创项目成功为“通过”*/
create table ProjectLst(
    ProgramName varchar(40) PRIMARY KEY,
    Tno char(9) NOT NULL,
    ProIntro varchar(400),
    FOREIGN KEY(Tno) REFERENCES Teacher(Tno),
)

/*有一个想法不知道行不行，大创每个项目限4人，这里申请的人可以不止四个
最终老师只能同意四个
然后学生视角可以看到自己是否通过
大创最终项目名单只要select Response='通过'就好了

一旦有人申请，就提醒老师*/
create table ProjectAppli(
    Sno char(9), 
    ProjectName varchar(40),
    Reason varchar(400),
    Response varchar(6),/*通过或者不通过*/
    FOREIGN KEY(Sno) REFERENCES Student(Sno),
    FOREIGN KEY(ProjectName) REFERENCES ProjectLst(ProgramName),
)



/*申请奖学金之后Admin会收到提醒*/
/*奖学金展示表*/
create table ScholarLst(
    Scholarship varchar(20) PRIMARY KEY,
    SchoIntro varchar(200),/*奖学金介绍，包括评选要求*/
    Money SMALLINT,/* 与5k比较看是否高额，一个人若已经得到高额，则其余高额奖学金和低额奖学金不可以申请*/
)

/*奖学金申请表
还是和上面一样的思路，学生视角可以看到自己是否通过
最终项目名单只要select Response='通过'就好了
用Trigger实现如果已经有一项通过的高额申请，则不给申请*/
create table ScholarAppli(
    Sno char(9),
    Scholarship varchar(20),
    Reason varchar(200),
    Response varchar(6),/*通过或者不通过*/
    FOREIGN KEY(Sno) REFERENCES Student(Sno),
    FOREIGN KEY(Scholarship) REFERENCES ScholarLst(Scholarship)
)



