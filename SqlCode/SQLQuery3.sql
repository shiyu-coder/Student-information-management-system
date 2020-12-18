select CourseBasic.Cno,Cname,Cchar,Climit,Ccur,Cdept,Ccredit,Cgrade,Cterm from CourseBasic,Tcourse where CourseBasic.Cno=Tcourse.Cno and Tcourse.Tno='0111' 

select Wday,Cbegin,Cend from CTime where Cno='' and Cterm=''

select CourseBasic.Cno,Cname,Cchar,Climit,Ccur,Cdept,Ccredit,Cgrade,Cterm from CourseBasic,Tcourse where CourseBasic.Cno=Tcourse.Cno and Tcourse.Tno='0111'

select CourseBasic.Cno,Cname,Ssex,Sdept,Sgrade from Student,Stu_Cour,CourseBasic where CourseBasic.Cno=Stu_Cour.Cno and Stu_Cour.Sno=Student.Sno and Cname=''

select Cname from Tcourse,CourseBasic where Tcourse.Cno=CourseBasic.Cno and Tno='0111'

insert into Stu_Cour values('0000012','00201010','1',2020); update CourseBasic set Ccur=Ccur+1 where Cno='00201060'

select * from CourseBasic where Cno='00201010'

select CourseBasic.Cno,Cname,Cchar,Climit,Ccur,Cdept,Ccredit,Cgrade,Stu_Cour.Cterm from CourseBasic,Stu_Cour,Tcourse,Teacher where Teacher.Tno=Tcourse.Tno and Tcourse.Cno=CourseBasic.Cno and CourseBasic.Cno=Stu_Cour.Cno and Stu_Cour.Sno='0000012'

select Tname from CourseBasic,Tcourse,Teacher where CourseBasic.Cno=Tcourse.Cno and Tcourse.Tno=Teacher.Tno and CourseBasic.Cno=''

insert into ProjectAppli values('','','','3')

select Rcontent,Response from T2A where Tno='0111'

insert into T2A values('','','')

update S2A set Response='' where Rcontent=''

delete from Stu_Cour where Cno='00201010' and Sno='0000012' update CourseBasic set Ccur=Ccur-1 where Cno='00201010'