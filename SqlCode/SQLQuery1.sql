/*A teacher's view*/

/*
1. 自己教授的课的列表???
2. 教授的某一门课的具体学生选课情况
3. 自己申请一些事项的视图
4. 承接的大创的项目，可以批准或者拒绝
*/

CREATE ROLE Teacher_Tno

create login T0000001 with password='123456', default_database=E_Chain;
create user T0000001 for login T0000001 with default_schema=dbo

create view T0000003_Course as select Cno,Cterm from Tcourse
CREATE VIEW T0000003_Course AS SELECT Sno, Grade, Stu_Cour.Cno, Stu_Cour.Cterm FROM Stu_Cour, Tcourse WHERE Tcourse.Tno='x' AND Tcourse.Cterm=Stu_Cour.Cterm AND Tcourse.Cno=Stu_Cour.Cno
GRANT SELECT ON CourseBasic TO T0000001
GRANT SELECT ON CTime TO T0000001
GRANT SELECT ON Tcourse TO T0000001
GRANT SELECT ON Stu_Cour TO T0000001
GRANT SELECT ON Teacher TO T0000001
GRANT SELECT ON Student TO T0111
GRANT SELECT,INSERT ON T2A TO T0111
GRANT SELECT,INSERT,DELETE ON ScholarAppli TO T0111
GRANT SELECT,INSERT,DELETE ON ScholarLst TO T0111
GRANT SELECT,INSERT,DELETE ON ProjectAppli TO T0111
GRANT SELECT,INSERT,DELETE ON ProjectLst TO T0111

GRANT SELECT, UPDATE(Grade) ON T0000001_Course  TO T0000001

CREATE VIEW T0000001_T2A AS SELECT Rcontent, Response FROM T2A WHERE T2A.Tno='T0000001'

GRANT SELECT, UPDATE(Rcontent),INSERT  ON T0000001_T2A TO T0000001

CREATE VIEW T0000001_TP AS SELECT Sno, ProjectName, Reason, Response FROM ProjectAppli, ProjectLst WHERE ProjectLst.Tno='T0000001' AND ProjectAppli.ProjectName=ProjectLst.ProgramName

GRANT SELECT, UPDATE(Response) ON T0000001_TP TO T0000001

use master
go
Declare @SQLText Varchar(1000),@loginNames varchar(1000)
set @loginNames=''
select @loginNames=@loginNames+A.name+',' FROM syslogins A WHERE  (name<>'sa' AND name like 's%')
if @loginNames <> ''
set @SQLText='sp_droplogin '+left(@loginNames,len(@loginNames)-1)
Exec(@SQLText)
use E_Chain
go


/*
学生的视图
1. 所有学生都有的，可以查看所有课程的信息
2. 自己所有选课信息（退课要申请，这里不能退）
3. 只能查看自己的成绩表
4. 学生查看自己的基本信息
5. 自己的一般申请
6. 自己的奖学金申请
7. 自己的大创申请
*/

CREATE ROLE Student_Sno


create login S0000001 with password='123456', default_database=E_Chain;
create user 施宇 for login 施宇 with default_schema=dbo

CREATE VIEW Sno_Info_0000001 AS SELECT Sno , Sname, Ssex, Sdept, Sgrade FROM Student WHERE Sno='0000001'

GRANT SELECT ON Sno_Info_0000001 TO 施宇
/*学生查看自己所有选课*/


CREATE VIEW Sno_Course_0000001 AS SELECT DISTINCT Stu_Cour.Cno, Stu_Cour.Cterm FROM Stu_Cour WHERE Stu_Cour.Sno='x'
/*insert是选课的时候插入的*/
GRANT SELECT, INSERT ON Sno_Course TO 施宇

/*与这个视图一起可以查看这位同学的选课课表*/
/*SELECT Sno_Course.Cno, Cname, Tname, Sno_Course.Cterm, Wday, Cbegin, Cend FROM Sno_Course, CourseBasic, CTime, Tcourse, Teacher WHERE Sno_Course.Cno=CourseBasic.Cno AND Sno_Course.Cno=Tcourse.Cno AND Sno_Course.Cterm=Tcourse.Cterm AND Sno_Course.Cno=CTime.Cno AND Sno_Course.Cterm=CTime.Cterm
*/

GRANT SELECT,UPDATE ON CourseBasic TO S0000012
GRANT SELECT ON CTime TO S0000006
GRANT SELECT ON Tcourse TO S0000006
GRANT SELECT ON Teacher TO S0000006
GRANT SELECT,INSERT ON ScholarAppli TO S0000006
GRANT SELECT ON ScholarLst TO S0000006
GRANT SELECT,INSERT ON ProjectAppli TO S0000009
GRANT SELECT ON ProjectLst TO S0000009
GRANT SELECT,INSERT,DELETE ON Stu_Cour TO S0000012
GRANT SELECT,INSERT ON S2A TO S0000012

CREATE VIEW Sno_Grade AS SELECT DISTINCT Stu_Cour.Cno, Cname, Cchar, Ccredit, Grade,Cterm FROM Stu_Cour, CourseBasicWHERE Stu_Cour.Sno='x' AND Stu_Cour.Cno=CourseBasic.Cno 

GRANT SELECT ON Sno_Grade TO Student_Sno



CREATE VIEW Sno_S2A AS SELECT Rcontent, Response FROM S2A WHERE Sno='x'
/*但是学生和老师不能写response，这个有点难顶*/
GRANT SELECT, UPDATE(Rcontent),INSERT  ON Sno_S2A TO Student_Sno



CREATE VIEW Sno_Pro AS SELECT ProjectName, Reason, Response FROM ProjectAppli WHERE Sno='x'
 /*但是学生不能写response?*/
GRANT SELECT, UPDATE(ProjectName, Reason),INSERT ON Sno_Pro TO Student_Sno



CREATE VIEW Sno_Scho AS SELECT Scholarship, Reason, Response FROM ScholarAppli WHERE Sno='x'
/*但是学生不能写response?*/ 
GRANT SELECT, UPDATE(Scholarship, Reason),INSERT ON Sno_Scho TO Student_Sno