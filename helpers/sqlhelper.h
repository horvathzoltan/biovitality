#ifndef SQLHELPER_H
#define SQLHELPER_H

#include "networkhelper.h"

#include <QVector>
#include <QList>
#include <QString>
#include <QFileInfo>
#include <QSqlDatabase>
#include <QVariant>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlQuery>

class SQLHelper
{
private:
    class DatabaseManager{
    private:
        QSqlDatabase _db;

    public:
        bool isValid(){return _db.isValid();}
        QString databaseName(){return _db.databaseName();}
        bool open(){return _db.open();}
        void close(){_db.close();}
        bool isOpenError(){return _db.isOpenError();}
        QSqlError lastError(){return _db.lastError();}
        QSqlDatabase addDatabase(const QString& d,
                                 const QString& c,
                                 const QString& dName){
            _db = QSqlDatabase::addDatabase(d,c);
            _db.setDatabaseName(dName);
            return _db;
        };

        void setUserNamePassword(const QString& u,
                                 const QString& p){
            _db.setUserName(u);
            _db.setPassword(p);
        };

        void setHostNamePort(const QString& h, int p){
            _db.setHostName(h);
            _db.setPort(p);
        };

        QSqlQuery query(){return QSqlQuery(_db);}

        //void setDatabaseName(const QString& v){_db.setDatabaseName();}
    };
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

    // struct DbErr
    // {
    // private:
    //     QList<DBE> _errors;
    // public:
    //     QString _dbName="";

    //     DbErr(const QString& dbName)
    //     {
    //         _dbName = dbName;
    //     }
    //  private:
    //      DbErr(){};
    //  public:
    //      void AddError(const QString& v){_errors.append(DBE(v));}
    //      void AddError(const QString& p, const QSqlError& v)
    //      {
    //          if(v.type()!=QSqlError::ErrorType::NoError)
    //          {
    //              QString msg = ErrorString(p, v);
    //              _errors.append(msg);
    //          }
    //      }

    //      void AddError_dbIsInvalid(){
    //          _errors.append(DBE("database "+_dbName+" is invalid"));
    //      }

    //      void AddError_TableNotExists(const QString& tableName){
    //          _errors.append(DBE("table "+tableName+" is not exists"));
    //      }

    //      bool isValid(){return _errors.isEmpty();}

    //      QString ToString(){
    //          if(_errors.isEmpty()) return _dbName+": ok";
    //          QString e;
    //          for(auto&error:_errors){
    //              if(!e.isEmpty()) e+="\n";
    //              e.append(error.ToString());
    //          }
    //          return e;
    //      }
    // };

    struct DoQueryRModel{
        QList<QSqlRecord> records;
        int rowsAffected = -1;
        bool isOk = false;
   //     QSqlError dbError;
   //     QSqlError queryError;

        bool hasRecords(){
            if(!isOk) return false;
            if(records.isEmpty()) return false;
            return true;
        }

        // int recordCount(){
        //     return records.count();
        // }

       //  QString ToString(){
       //      if(!isOk){
       // //         QString msg1 = ErrorString("db", dbError);
       // //         QString msg2 = ErrorString("query", queryError);

       // //         return msg1+"\n"+msg2;
       //          return "error";
       //      }

       //      if(rowsAffected>0){
       //          return "Rows affected: "+QString::number(rowsAffected);
       //      }
       //      return "No rows affected";
       //  }

        // QString ToString_RowsAffected(){
        //     if(rowsAffected>0)
        //     {
        //         return "Rows affected: "+QString::number(rowsAffected);
        //     }
        //     return "No rows affected";
        // }
    };

public:
    struct SQLParam{
        QString paramName;
        QString fieldName;
        QVariant fieldValue;

        QString ToString_Value() const{
            QString v = GetFieldValue(fieldValue);

            QString m = paramName+":"+fieldName+"="+v
                  +" "+(fieldValue.isValid()?"valid":"invalid") +
                  " "+fieldValue.metaType().name();
            return m;
        }

        QString ToString() const{
            QString m = fieldName+" "+fieldValue.metaType().name();
            return m;
        }

    };

    // struct HostPort
    // {
    //     QString host;// = "172.16.1.5";
    //     int port;
    // };

    struct SQLSettings : public ClientSettings
    {    
    public:
        SQLSettings():ClientSettings(){};
        SQLSettings(const QString& d,
                    const QString& b,
                    const QString& h,
                    int port,
                    const QString& u,
                    const QString& p);
    private:
        QString _driver;// = "QODBC";
        QString _dbname;// = "BuildInfoFlex";
        QString _user;// = "sa";
        QString _password;//= "Gtr7jv8fh2";
    public:
        QString dbname(){return _dbname;}
        QString driver(){return _driver;}
        QString user(){return _user;}
        QString password(){return _password;}

        QString ToString()
        {
            return _driver+'@'+ToString_HostPort();
        }

        bool isValid() const{
            if(_dbname.isEmpty()) return false;
            if(_driver.isEmpty()) return false;
            if(_host.isEmpty()) return false;
            if(_port < 1) return false;
            if(_port > 65535) return false;
            if(_user.isEmpty()) return false;
            if(_password.isEmpty()) return false;
            return true;
        }
    };

private:   
    SQLSettings _settings;
    bool _isInited = false;

    DatabaseManager *_db = nullptr;
    //QSqlDatabase *_db = nullptr;
    static const QString _connName;
    //HostPort* _host = nullptr;

    bool CheckHostAvailable(int timeout);
    bool Connect_odbc(const QString &name, int timeout);
    bool Connect_mariadb(const QString &name, int timeout);

    void Error(const QString& p, const QSqlError& err);
    QString GetCallSelect(const QString& call);
public:    
    void Init(const SQLSettings& v);
    void UnInit();
    //void DeleteDatabase();

    bool dbIsValid() const { return _isInited ? _db->isValid() : false; }
    QString dbName() const { return _isInited ? _db->databaseName() : ""; }
    //void SetSettings(const SQLSettings& v){_settings = v;}

    SQLHelper(){
        _db = new DatabaseManager();//QSqlDatabase();
    }

    ~SQLHelper()
    {        
        delete _db;
    }

private:
    bool Connect();
public:
    bool TryConnect();
    bool TryOpen();

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

    // DbErr dbErr(){
    //     DbErr e = DbErr(dbName());
    //     if(!dbIsValid()){
    //         e.AddError_dbIsInvalid();
    //     }
    //     QSqlError lastError = _db.lastError();
    //     bool isValid = lastError.isValid();
    //     e.AddError("db", lastError);
    //     return e;
    // }

    static QString ErrorType_ToString(QSqlError::ErrorType t);

    static QString ErrorString(const QString& p, const QSqlError& err);

private:
    QString DbMsg();
};

#endif // SQLHELPER_H
