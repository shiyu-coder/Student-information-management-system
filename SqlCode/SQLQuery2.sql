SELECT CONCAT('drop view ', view_name, ';')
  FROM sysobjects
 WHERE (xtype = 'v')and A.name like 'T_%'
 
 

select identity(int,1,1) flag,[name] names into #tmp
from sysobjects where crdate>'2020-12-18'



declare @tb varchar(1000) ,@a int,@b int,@sql varchar(8000)
select @a=min(flag),@b=max(flag) from #tmp
while @a<=@b
    begin
        select @tb=names from #tmp where flag=@a
        set @sql='drop view '+@tb
        exec(@sql)
        set @a=@a+1
    end

    DROP TABLE #tmp
select *   from sysobjects
where crdate>'2020-12-18'


select identity(int,1,1) flag,[name] names into #tmp
from sysobjects where crdate>'2020-12-18'

declare @tb varchar(1000) ,@a int,@b int,@sql varchar(8000)
select @a=min(flag),@b=max(flag) from #tmp
while @a<=@b
    begin
        select @tb=names from #tmp where flag=@a
        set @sql='drop user '+@tb
        exec(@sql)
        set @a=@a+1
    end

    DROP TABLE #tmp
select *   from sysobjects
where crdate>'2020-12-18'