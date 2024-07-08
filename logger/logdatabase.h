#ifndef LOGDATABASE_H
#define LOGDATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlTableModel>
#include <QThread>



class LogDatabase : public QThread
{
public:
    LogDatabase();
    void run();
private:
    void logDataBaseInit();


private:




};

#endif // LOGDATABASE_H
