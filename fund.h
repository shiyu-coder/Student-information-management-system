#ifndef FUND_H
#define FUND_H
#include<QString>
#include<QVector>

/**
 * @brief The Fund class
 * 存储有关单个基金的基本信息
 */
class Fund
{
public:
    /**
     * @brief code
     * 基金代码
     */
    QString code;
    /**
     * @brief name
     * 基金名称
     */
    QString name;
    /**
     * @brief netWorth
     * 当前基金单位净值
     */
    int netWorth;
    /**
     * @brief expectWorth
     * 当前基金单位净值估算
     */
    int expectWorth;
    /**
     * @brief expectGrowth
     * 当前基金单位净值估算日涨幅,单位为百分比
     */
    QString expectGrowth;
    /**
     * @brief dayGrowth
     * 单位净值日涨幅,单位为百分比
     */
    QString dayGrowth;
    /**
     * @brief lastWeekGrowth
     * 单位净值周涨幅,单位为百分比
     */
    QString lastWeekGrowth;
    /**
     * @brief lastMonthGrowth
     * 单位净值月涨幅,单位为百分比
     */
    QString lastMonthGrowth;
    /**
     * @brief lastThreeMonthsGrowth
     * 单位净值三月涨幅,单位为百分比
     */
    QString lastThreeMonthsGrowth;
    /**
     * @brief lastSixMonthsGrowth
     * 单位净值六月涨幅,单位为百分比
     */
    QString lastSixMonthsGrowth;
    /**
     * @brief lastYearGrowth
     * 单位净值年涨幅,单位为百分比
     */
    QString lastYearGrowth;
    /**
     * @brief netWorthDate
     * 净值更新日期,日期格式为yy-MM-dd HH:mm.2019-06-27 15:00代表当天下午3点
     */
    QString netWorthDate;
    /**
     * @brief expectWotrhDate
     * 净值估算更新日期,,日期格式为yy-MM-dd HH:mm.2019-06-27 15:00代表当天下午3点
     */
    QString expectWotrhDate;

    Fund();

};

#endif // FUND_H
