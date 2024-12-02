#ifndef SQLHELPER_H
#define SQLHELPER_H

#include <QVector>
#include <QList>
#include <QString>
#include <QFileInfo>
#include <QSqlDatabase>
#include <QVariant>
#include <QSqlRecord>
#include <QSqlError>

class SQLHelper
{
public:
    struct DBE{
    private:
        DBE(){};
        QString _error;

    public:
        DBE(const QString& error){
            _error = error;
        }
        QString ToString(){return _error;}
    };

    struct DbErr
    {
    private:
        QList<DBE> _errors;
    public:
        QString _dbName="";

        DbErr(const QString& dbName)
        {
            _dbName = dbName;
        }
     private:
         DbErr(){};
     public:
         void AddError(const QString& v){_errors.append(DBE(v));}
         void AddError(const QString& p, const QSqlError& v)
         {
             if(v.type()!=QSqlError::ErrorType::NoError)
             {
                 QString msg = DoQueryRModel::ErrorString(p, v);
                 _errors.append(msg);
             }

         }

         void AddError_dbIsInvalid(){
             _errors.append(DBE("database "+_dbName+" is invalid"));
         }

         void AddError_TableNotExists(const QString& tableName){
             _errors.append(DBE("table "+tableName+" is not exists"));
         }

         bool isValid(){return _errors.isEmpty();}

         QString ToString(){
             if(_errors.isEmpty()) return _dbName+": ok";
             QString e;
             for(auto&error:_errors){
                 if(!e.isEmpty()) e+="\n";
                 e.append(error.ToString());
             }
             return e;
         }
    };

    struct DoQueryRModel{
        QList<QSqlRecord> records;
        int rowsAffected = -1;
        bool isOk = false;
        QSqlError dbError;
        QSqlError queryError;

        bool hasRecords(){
            if(!isOk) return false;
            if(records.isEmpty()) return false;
            return true;
        }

        int recordCount(){
            return records.count();
        }

        static QString ErrorString(const QString& p, const QSqlError& err)
        {
            if(err.isValid() && err.type()!= QSqlError::ErrorType::NoError)
            {
                auto n = err.nativeErrorCode();
                auto d = err.driverText();
                auto db = err.databaseText();
                QString t = ErrorType_ToString(err.type());

                QString msg2 = p+": "+t+ "("+n+") "+d+", "+db;
                return msg2;
            }
            return QStringLiteral("%1: no error").arg(p);
        };

        static QString ErrorType_ToString(QSqlError::ErrorType t){
            switch(t){
            case QSqlError::ErrorType::NoError: return "NoError";
            case QSqlError::ErrorType::ConnectionError: return "ConnectionError";
            case QSqlError::ErrorType::StatementError: return "StatementError";
            case QSqlError::ErrorType::TransactionError: return "TransactionError";
            default: return "UnknownError";
            }
        }

        QString ToString(){
            if(!isOk){
                QString msg1 = ErrorString("db", dbError);
                QString msg2 = ErrorString("query", queryError);

                return msg1+"\n"+msg2;
            }

            if(rowsAffected>0){
                return "Rows affected:"+QString::number(rowsAffected);
            }
            return "No rows affected";
        }

        QString ToString_RowsAffected(){
            if(rowsAffected>0)
            {
                return "Rows affected:"+QString::number(rowsAffected);
            }
            return "No rows affected";
        }
    };

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
    QString GetCallSelect(const QString& call);
public:    
    void Init(const SQLSettings& v);

    bool dbIsValid() const { return _isInited ? _db.isValid() : false; }
    QString dbName() const { return _isInited ? _db.databaseName() : ""; }
    //void SetSettings(const SQLSettings& v){_settings = v;}

    SQLHelper(){}

    bool Connect();

    static QFileInfo GetMostRecent(const QString &path, const QString &pattern);

    // QVariant GetProjId(QSqlDatabase &db, const QString& project_name);
    // int GetBuildNum(QSqlDatabase &db, int project);
    // bool SetBuildNum(QSqlDatabase &db, int project, const QString &user, int buildnumber, const QString &project_name);

    static QString GetDriverName();

    DoQueryRModel DoQuery(const QString& cmd, const QList<SQLParam>& params = {});

    static QString GetFieldNames_UPDATE(const QList<SQLHelper::SQLParam>& params);
    static QString GetFieldNames_INSERT(const QList<SQLHelper::SQLParam>& params);
    static QString GetParamList_INSERT(const QList<SQLHelper::SQLParam>& params);
    //QSqlQuery GetQuery();
    //QSqlQuery GetQuery(const QString& cmd);
    DoQueryRModel Call(const QString& cmd);

    static QString GetFieldValue(const QVariant& v);
    DbErr dbErr(){
        DbErr e = DbErr(dbName());
        if(!dbIsValid()){
            e.AddError_dbIsInvalid();
        }
        e.AddError("db", _db.lastError());
        return e;
    }
};

#endif // SQLHELPER_H
