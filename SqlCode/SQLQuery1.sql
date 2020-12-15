/*A teacher's view*/

/*
1. 自己教授的课的列表???
2. 教授的某一门课的具体学生选课情况
3. 自己申请一些事项的视图
4. 承接的大创的项目，可以批准或者拒绝
*/

CREATE VIEW TC_Tno /*e.g. TC_1*/
AS 
SELECT Tcourse.Cterm, CourseBasic.Cno, Cname, Wday, Cbegin, Cend
FROM CourseBasic, CTime, Tcourse
WHERE Tcourse.Tno='x' AND Tcourse.Cno=CourseBasic.Cno
AND Tcourse.Cno=CTime.Cno AND Tcourse.Cterm=CTime.Cterm

/*一个老师教授的一门课的具体学生信息，用于后续登录成绩*/
CREATE VIEW TCS_Tno__Cno_Cterm 
AS
SELECT Sno, Grade
FROM Stu_Cour
WHERE Stu_Cour.Cno='x' AND Stu_Cour.Cterm='y'

CREATE VIEW T2A_Tno
AS
SELECT Rcontent, Response
FROM T2A
WHERE T2A.Tno='x'

CREATE VIEW TP_Tno
AS
SELECT Sno, ProjectName, Reason, Response
FROM ProjectAppli, ProjectLst
WHERE ProjectLst.Tno='x' AND ProjectAppli.ProjectName=ProjectLst.ProgramName

CREATE ROLE Teacher_Tno

GRANT SELECT
ON TC_Tno
TO Teacher_Tno

GRANT SELECT, UPDATE(Grade)
ON TCS_Tno__Cno_Cterm 
TO Teacher_Tno

GRANT SELECT, UPDATE(Rcontent)
ON T2A_Tno
TO Teacher_Tno

GRANT SELECT, UPDATE(Response)
ON TP_Tno
TO TP_Tno


