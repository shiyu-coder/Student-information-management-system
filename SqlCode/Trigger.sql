/*修改课程信息时，
课程编号不可修改，课程名称可修改
课程最大选修人数可修改，修改完的值大于当前已选就行了*/

CREATE TRIGGER Update_CourseInfo ON CourseBasic AFTER UPDATE AS DECLARE @newCno varchar(9), @oldCno varchar(9),  @newClimit SMALLINT, @oldCcur SMALLINT,@newCcur SMALLINT SELECT @newCno=CB2.Cno, @oldCno=CB1.Cno, @newClimit=CB2.Climit,@oldCcur=CB1.Ccur, @newCcur=CB2.Ccur FROM deleted CB1, inserted CB2 IF(@newCno<>@oldCno)OR(@oldCcur<>@newCcur)OR(@newClimit<@oldCcur) BEGIN ROLLBACK TRANSACTION END

/*删除课程*/

/*新增数据*/


/*修改教师
教师编号不可修改*//*话说修改的时候如果不符合外键是直接会报错吧?*/
CREATE TRIGGER UPdate_TeacherInfo ON Teacher AFTER UPDATE AS DECLARE @newTno char(4), @oldTno char(4) SELECT @newTno=T2.Tno, @oldTno=T1.Tno FROM deleted T1, inserted T2 IF(@newTno<>@oldTno) BEGIN ROLLBACK TRANSACTION END

/*新增教师*/

/*删除教师*/


/*修改学生信息*/
CREATE TRIGGER UPdate_StudentInfo ON Student AFTER UPDATE AS DECLARE @newSno char(9), @oldSno char(9) SELECT @newSno=S2.Sno, @oldSno=S1.Sno FROM deleted S1, inserted S2 IF(@newSno<>@oldSno) BEGIN ROLLBACK TRANSACTION END

/*删除所有视图*/
Declare @SQLText varchar(8000),@viewNames varchar(8000)
set @viewNames=''
select @viewNames=@viewNames+A.Name+',' from sysobjects A WHERE (xtype = 'v')and A.name like 'T_%'
if @viewNames <> ''
set @SQLText='drop view '+left(@viewNames,len(@viewNames)-1)
Exec(@SQLText)
/*删除所有trigger*/
Declare @SQLText Varchar(1000),@viewNames varchar(1000)
set @viewNames=''
select @viewNames=@viewNames+A.Name+',' from sysobjects A WHERE (xtype = 'tr')and A.name like '%'
if @viewNames <> ''
set @SQLText='drop  trigger '+left(@viewNames,len(@viewNames)-1)
Exec(@SQLText)

select * from sysobjects where (xtype = 'v')

Declare @SQLText Varchar(1000),@loginNames varchar(1000)
set @loginNames=''
select @loginNames FROM Sysusers WHERE status='2' and islogin='1'
if @loginNames <> ''
set @SQLText='sp_droplogin '+left(@loginNames,len(@loginNames)-1)
Exec(@SQLText)

/*
select 'drop Trigger '+name from sys.objects where name like '%' and type = 'TR'
*/


/*删除学生*/
CREATE TRIGGER Delete_Student ON Student AFTER DELETE AS BEGIN DECLARE @delSno char(9) SELECT @delSno=delStu.Sno FROM deleted delStu UPDATE CourseBasic SET Ccur=Ccur-1 WHERE CourseBasic.Cno=(SELECT Cno FROM Stu_Cour, deleted delStu WHERE Stu_Cour.Sno=delStu.Sno) END

/*管理员处理退课*/
DELETE FROM Stu_Cour
WHERE Sno='申请退课同学' AND Cno='申请的课' AND Cterm='申请退课的学期'

UPDATE CourseBasic
SET Ccur=Ccur-1
WHERE CourseBasic.Cno='申请的课'

/*1-同意授予，2-不可兼得，0-拒绝授予，3-等待处理，*/
/*奖学金：仿照学校，先只能申请高额奖学金，高额可以申请多个，但是最终只能拿一个
高额评完之后开始评低额，拿过高额的直接不能申请 */
CREATE TRIGGER Update_sholar_status ON ScholarAppli AFTER UPDATE AS DECLARE @newRes char(1),@oldRes char(1),@money SMALLINT, @sno varchar(10) SELECT @newRes=newSchoAppli.Response, @oldRes=oldSchoAppli.Response,@money=ScholarLst.money, @sno=newSchoAppli.Sno FROM inserted newSchoAppli, deleted oldSchoAppli, ScholarLst WHERE newSchoAppli.Scholarship=ScholarLst.Scholarship IF(@oldRes <>'3') BEGIN ROLLBACK TRANSACTION END ELSE IF(@money>=5000 AND @newRes='1') BEGIN UPDATE ScholarAppli SET Response='2' WHERE Sno=@sno AND Response='3' END
/*
drop trigger Update_sholar_status
*/
/*在开始申请奖学金的时候，如果一个学生已经获得了高额，那么申请直接驳回*/
CREATE TRIGGER Appli_sholar ON ScholarAppli AFTER INSERT AS DECLARE @newSno varchar(10),@newScholar varchar(20) SELECT @newScholar=A1.Scholarship,@newSno=A1.Sno FROM inserted A1 IF ((SELECT COUNT(ScholarAppli.Scholarship)FROM ScholarLst, ScholarAppli WHERE Sno=@newSno  AND Money>=5000 AND ScholarLst.Scholarship=ScholarAppli.Scholarship AND ScholarAppli.Response='1')>=1) BEGIN ROLLBACK TRANSACTION END


	
	
/*学生选课
时间冲突就不能选，能选就要+1*/

CREATE TRIGGER select_course ON Stu_Cour AFTER INSERT AS DECLARE @newCno varchar(9), @newCterm SMALLINT SELECT @newCno=SC.Cno, @newCterm=SC.Cterm FROM inserted SC IF((SELECT COUNT(CT1.Cno) FROM CTime CT1, CTime CT2 WHERE CT2.Cterm=@newCterm AND CT2.Cno=@newCno AND CT2.Wday=CT1.Wday AND(NOT(CT1.Cbegin>CT2.Cend OR CT2.Cbegin>CT1.Cend)))>=1) BEGIN ROLLBACK TRANSACTION END ELSE BEGIN UPDATE CourseBasic SET Ccur=Ccur+1 WHERE Cno=@newCno END


/*0-不同意 1-同意 2-待处理*/
/*大创一个组不能多于4个人, 一个学生可以报名多个组也可以加入多个组*/
CREATE TRIGGER apply_pro ON ProjectAppli AFTER UPDATE AS DECLARE @newRes varchar(6),@oldRes varchar(6), @sno varchar(10),@NewPro varchar(40)  SELECT @newRes=NPA.Response, @oldRes=OPA.Response, @sno=NPA.Sno, @NewPro=NPA.ProjectName FROM inserted NPA, deleted OPA IF(@oldRes <>'2') BEGIN ROLLBACK TRANSACTION END ELSE IF(@newRes='1' AND (SELECT COUNT(Sno) FROM deleted WHERE deleted.ProjectName=@NewPro AND deleted.Response='1')>=4) BEGIN ROLLBACK TRANSACTION END

