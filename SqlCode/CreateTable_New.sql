create table Systbl(
    stuNum SMALLINT,/*学生总人数*/
)

create table Dept(
    Dname varchar(50) PRIMARY KEY,
    Dintro varchar(200),/*introduction*/
)


create table Student(
    Sno varchar(10) PRIMARY KEY,/*学号，每位都是数字字符*/
    Sname varchar(10),
    Ssex char(2),/*约束：男or女*/
    Sdept varchar(50),/**/ 
    Sgrade char(4),/*入学年级*/
    FOREIGN KEY(Sdept) REFERENCES Dept(Dname),
)

create table Teacher(
    Tno varchar(4) PRIMARY KEY,/*工号，每位都是数字字符*/
    Tname varchar(10),
    Tdept varchar(50),
    FOREIGN KEY(Tdept) REFERENCES Dept(Dname),
)

/*
*ATTENTION，假设条件
*一学期中，一门课只由一个老师教授，只开一次，即不存在1班2班的情况
*每门课的开课周数一样，每门课只有一个上课地点
*/
create table CourseBasic(
    Cno varchar(9)PRIMARY KEY,
    Cname varchar(50),
    Climit SMALLINT,/*选课人数上限*/
    Ccur SMALLINT,/*当前选课人数，每选课成功一个人，就要用Trigger更新*/
    Cchar varchar(30),/*选课性质*/
    Cdept varchar(50),
    Ccredit SMALLINT,
    Cgrade char(4),/*开课年级*/
    FOREIGN KEY(Cdept) REFERENCES Dept(Dname) ,

)




create table CTime(
    Cno varchar(9),
    Cterm SMALLINT , /*限制1，2*/
    Wday SMALLINT,
    Cbegin SMALLINT,
    Cend SMALLINT,
    FOREIGN KEY(Cno) REFERENCES CourseBasic(Cno)  ON DELETE CASCADE,
)
/*选课操作考虑的因素*/

create table Tcourse(/*教师教课表*/
    Cno varchar(9),
    Tno varchar(4),
    Cterm SMALLINT, /*限制1，2*/
    FOREIGN KEY(Cno) REFERENCES CourseBasic(Cno) ON DELETE CASCADE,
    FOREIGN KEY(Tno) REFERENCES Teacher(Tno)ON DELETE CASCADE
    /*在当前学期的语境下，不需要指明学期*/
)

create table Stu_Cour(
    Sno varchar(10),
    Cno varchar(9), 
    Cterm SMALLINT, /*限制1，2*/
    Grade SMALLINT,
    PRIMARY KEY(Sno, Cno, Cterm),
    FOREIGN KEY(Cno) REFERENCES CourseBasic(Cno) ON DELETE CASCADE ,
    FOREIGN KEY(Sno) REFERENCES Student(Sno) ON DELETE CASCADE ,
)

/*教师和学生都会进行一些申请操作，这里的表是向管理员申请，即需要在学生界面有“退课，请假一个窗口”，教师界面都有一个“修改课程信息”的窗口，输入的内容其实最终填写到这张表中。在填写完毕之后，是Sys表中的AdminNotice变成1*/
/*！！！一个表不可以，一个列好像不能绑两个外键...*/
create table T2A(
    Tno varchar(4) NOT NULL,/*申请老师工号*/
    Rcontent varchar(200) NOT NULL,/*申请内容：请假，退课，修改课程人数上限之类的*/
    Response varchar(50),/*Admin反馈*/
    FOREIGN KEY(Tno) REFERENCES Teacher(Tno) ON DELETE CASCADE,
    PRIMARY KEY(Tno, Rcontent),
)

create table S2A(
    Sno varchar(10) NOT NULL,/*申请学生学号*/
    Rcontent varchar(200) NOT NULL,/*申请内容：请假，退课，修改课程人数上限之类的*/
    Response varchar(50),/*Admin反馈*/
    FOREIGN KEY(Sno) REFERENCES Student(Sno)  ON DELETE CASCADE,
    PRIMARY KEY(Sno, Rcontent),
)


/*学生还会向老师申请报名大创项目
申请报名大创项目成功为“通过”*/
create table ProjectLst(
    ProgramName varchar(40) PRIMARY KEY,
    Tno varchar(4) NOT NULL,
    ProIntro varchar(400),
    FOREIGN KEY(Tno) REFERENCES Teacher(Tno)  ON DELETE CASCADE,
)

/*有一个想法不知道行不行，大创每个项目限4人，这里申请的人可以不止四个
最终老师只能同意四个
然后学生视角可以看到自己是否通过
大创最终项目名单只要select Response='通过'就好了

一旦有人申请，就提醒老师*/
create table ProjectAppli(
    Sno varchar(10), 
    ProjectName varchar(40),
    Reason varchar(400),
    Response varchar(6),/*通过或者不通过*/
    FOREIGN KEY(Sno) REFERENCES Student(Sno) ON DELETE CASCADE ,
    FOREIGN KEY(ProjectName) REFERENCES ProjectLst(ProgramName) ON DELETE CASCADE ,
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
用Trigger实现如果已经有一项通过的高额申请，则不给申请

一个学生可以申请一个高额，若干低额
先从高额开始评奖，一个学生获得高额奖学金之后，他的其他申请状态变成不可兼得*/
create table ScholarAppli(
    Sno varchar(10),
    Scholarship varchar(20),
    Reason varchar(200),
    Response char(1) CHECK(Response IN ('0','1','2','3')),/*1-通过, 0-不通过, 2-不可兼得，3-未审核*/
    FOREIGN KEY(Sno) REFERENCES Student(Sno) ON DELETE CASCADE,
    FOREIGN KEY(Scholarship) REFERENCES ScholarLst(Scholarship) ON DELETE CASCADE 
)


