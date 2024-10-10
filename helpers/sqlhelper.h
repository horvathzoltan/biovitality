#ifndef SQLHELPER_H
#define SQLHELPER_H

#include <QVector>
#include <QList>
#include <QString>
#include <QFileInfo>
#include <QSqlDatabase>
#include <QVariant>
#include <QSqlRecord>

class SQLHelper
{
public:
    struct SQLParam{
        QString paramName;
        QString fieldName;
        QVariant fieldValue;
    };

    struct HostPort
    {
        QString host;// = "172.16.1.5";
        int port;
    };

    struct SQLSettings
    {
        QString driver;// = "QODBC";
        QString dbname;// = "BuildInfoFlex";
        QVector<HostPort> hosts;
        QString user;// = "sa";
        QString password;//= "Gtr7jv8fh2";
    };

private:
    SQLSettings _settings;
    bool _isInited = false;
    QSqlDatabase _db;
    static const QString _connName;
    HostPort* _host = nullptr;

    bool Connect_odbc(const QString &name, int timeout);
    bool Connect_mariadb(const QString &name, int timeout);

    void Error(const QString& p, const QSqlError& err);

public:    
    void Init(const SQLSettings& v);

    bool dbIsValid(){ return _isInited ? _db.isValid() : false; }
    QString dbName(){ return _isInited ? _db.databaseName() : ""; }
    //void SetSettings(const SQLSettings& v){_settings = v;}

    SQLHelper(){}

    bool Connect();

    static QFileInfo GetMostRecent(const QString &path, const QString &pattern);

    // QVariant GetProjId(QSqlDatabase &db, const QString& project_name);
    // int GetBuildNum(QSqlDatabase &db, int project);
    // bool SetBuildNum(QSqlDatabase &db, int project, const QString &user, int buildnumber, const QString &project_name);

    static QString GetDriverName();

    QList<QSqlRecord> DoQuery(const QString& cmd, const QList<SQLParam>& params = {});

    static QString GetFieldList_UPDATE(const QList<SQLHelper::SQLParam>& params);
    static QString GetFieldList_INSERT(const QList<SQLHelper::SQLParam>& params);
    static QString GetParamList_INSERT(const QList<SQLHelper::SQLParam>& params);
    //QSqlQuery GetQuery();
    //QSqlQuery GetQuery(const QString& cmd);
};

#endif // SQLHELPER_H
