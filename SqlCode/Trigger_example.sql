create trigger T on ScholarAppli
after update
as
declare @newRes char(1),@money smallint,@sno varchar(10)
select @newRes=(select Response from inserted)
    ,@money=(select money from inserted,ScholarLst where inserted.Scholarship=ScholarLst.Scholarship)
    ,@sno=(select Sno from inserted)
if(@money>=5000 and @newRes='1')
begin
	update ScholarAppli
	set Response='2'
	where Sno=@sno and Scholarship!=@newRes and Response='3' 
end


update ScholarAppli
set Response='1'
where Scholarship='Ê©Óî½±Ñ§½ð'