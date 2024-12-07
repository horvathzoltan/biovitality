#include "helpers/sqlhelper.h"
#include "networkhelper.h"
#include "helpers/logger.h"
#include <QDirIterator>
#include <QDateTime>
#include <QSqlQuery>
#include <QSqlError>
#include <QDate>
#include <QDateTime>
#include <QTcpSocket>
#include <QRegularExpression>

const QString SQLHelper::_connName = QStringLiteral("conn1");

void SQLHelper::Init(const SQLSettings& v){
    _isInited = false;
    if(!v.isValid()) return;

    _settings = v;
    _isInited = true;
}

bool SQLHelper::Connect()
{
    if(!_isInited) return false;

    bool connected = false;
    if(_settings.driver=="QODBC") connected = Connect_odbc(_connName, 5000);
    else if(_settings.driver=="QMARIADB") connected = Connect_mariadb(_connName, 5000);

    QString msg = "DB["+_settings.driver;
    //if(_host){
    msg+="@"+_settings.ToString_HostPort();
    //}
    msg+="]: "+_settings.dbname+" is "+(connected?"connected":"not connected");

    if(connected)
    {
        zInfo(msg)
    }
    else
    {
        zWarning(msg);
    }

    //zInfo("available host found: "+h->host+":"+QString::number(h->port));
    return connected;
}

bool SQLHelper::TryOpen()
{
    if(!_isInited) return false;
    bool contains = QSqlDatabase::contains(_connName);
    bool connected = false;
    if(contains) {
        //auto db = QSqlDatabase::database(_connName);
        if(_db.isValid())
        {
            if(_db.open())
            {
                zInfo("DB: "+_settings.dbname+" opened successfully");
                connected = true;
                // if(_db.isOpen())
                //     _db.close();
            }
            else
            {
                if (_db.isOpenError())
                {
                    zWarning("Cannot open DB: "+_settings.dbname);
                    zWarning(ErrorString("db", _db.lastError()));
                }
                else
                {
                    zWarning("Unknown error occurred while opening DB: "+_settings.dbname);
                }
            }
        }
    }
    return connected;
}

bool SQLHelper::TryConnect()
{
    bool connected = TryOpen();
    if(!connected)
    {
        bool c = Connect();
        if(c)
        {
            zInfo("DB: "+_settings.dbname+" connected successfully");
            connected = TryOpen();
            // //auto db = QSqlDatabase::database(_connName);
            // if(_db.isValid())
            // {
            //     zInfo("DB: "+_settings.dbname+" connected successfully");
            //     connected = true;
            // }
            // else
            // {
            //     zWarning("DB: "+_settings.dbname+" connecction failed");
            // }
        }
        else
        {
            zWarning("Cannot connect DB: "+_settings.dbname);
        }
    }    

    return connected;
}


auto SQLHelper::GetDriverName() -> QString{
    //opt/microsoft/msodbcsql17/lib64/libmsodbcsql-17.10.so.2.1
    auto driverdir = QStringLiteral("/opt/microsoft/msodbcsql17/lib64");
    auto driverpattern = QStringLiteral("^.*libmsodbcsql-?[0-9.so]*$");
    auto driverfi = GetMostRecent(driverdir, driverpattern);
    if(!driverfi.isFile()) return QString();
    return driverfi.absoluteFilePath();
}

//https://docs.microsoft.com/en-us/sql/linux/sql-server-linux-setup-tools?view=sql-server-ver15#ubuntu
bool SQLHelper::Connect_odbc(const QString& connName, int timeout)
{
    if(!_isInited) return false;
    //auto db = QSqlDatabase::database(_connName);

    bool isAvailable = CheckHostAvailable(timeout);
    if(isAvailable)
    {
        bool contains = QSqlDatabase::contains(connName);
        if(!contains)
        {
            _db = QSqlDatabase::addDatabase(_settings.driver, connName);
            auto driverfn = GetDriverName();
            if(!driverfn.isEmpty())
            {
                auto dbname = QStringLiteral("DRIVER=%1;Server=%2,%3;Database=%4")
                                  .arg(driverfn,_settings.host).arg(_settings.port).arg(_settings.dbname);
                _db.setDatabaseName(dbname);
                _db.setUserName(_settings.user);
                _db.setPassword(_settings.password);
            }
        }
    }

    bool connected = TryOpen();
    return connected;
}

bool SQLHelper::CheckHostAvailable(int timeout){
    bool isAvailable = false;
    if(NetworkHelper::Ping(_settings.host)) {
        zInfo("host found: "+_settings.host);
        QTcpSocket s;
        s.connectToHost(_settings.host, _settings.port);
        auto isok = s.waitForConnected(timeout);
        if(isok){
            s.disconnectFromHost();
            if (s.state() != QAbstractSocket::UnconnectedState) s.waitForDisconnected();
            isAvailable = true;
            zInfo("connection ready on port: "+QString::number(_settings.port));
        }
        else{
            zInfo("cannot connect to port: "+QString::number(_settings.port));
        }
    }
    else{
        zInfo("host not found: "+_settings.host);
    }

    return isAvailable;
}

bool SQLHelper::Connect_mariadb(const QString& connName, int timeout)
{
    if(!_isInited) return false;

    //auto db = QSqlDatabase::database(_connName);
    bool isAvailable = CheckHostAvailable(timeout);
    if(isAvailable)
    {
        bool contains = QSqlDatabase::contains(connName);
        if(!contains)
        {
            _db = QSqlDatabase::addDatabase(_settings.driver, connName);
            //Before using the connection, it must be initialized.
            _db.setHostName(_settings.host);// Tried www.themindspot.com & ip with http:// and https://
            _db.setPort(_settings.port);
            _db.setDatabaseName(_settings.dbname);
            _db.setUserName(_settings.user);
            _db.setPassword(_settings.password);

            zInfo("DB: "+_settings.dbname+" connection added");
        }
    }

   // bool connected = TryOpen();
    bool connected = _db.isValid();
    return connected;
}



// int SQLHelper::GetBuildNum(QSqlDatabase& db, int project)
// {
//     if(!db.isValid()) return -1;
//     int buildnum=-1;

//     QSqlQuery query(db);
//     bool isok = db.open();
//     if(!isok) {goto end; }

//     isok = query.exec(QStringLiteral("SELECT max(buildnum) FROM BuildInfoFlex.dbo.BuildInfo WHERE project=%1;").arg(project));
//     if(!isok) {goto end;}

//     if(query.size())
//     {
//         query.first();
//         auto a  = query.value(0);

//         if(!a.isValid() || a.isNull()) buildnum = 1003; else buildnum = a.toInt()+1;
//     }
//     if(buildnum == -1) buildnum = 1003;

// end:
//     Error(query.lastError());
//     Error(db.lastError());
//     db.close();
//     return buildnum;
// }

// bool SQLHelper::SetBuildNum(QSqlDatabase& db, int project_id, const QString& user, int buildnumber, const QString & project_name)
// {
//     if(!db.isValid()) return -1;

//     QSqlQuery query(db);
//     bool isok = db.open();
//     if(!isok) {goto end; }

//     query.prepare("INSERT INTO BuildInfoFlex.dbo.BuildInfo"
//                   "(version, userinfo, timestamp, product, buildnum, project) VALUES "
//                   "(:version, :userinfo, :timestamp, :product, :buildnum, :project)");

//     query.bindValue(QStringLiteral(":version"), "0.90");
//     query.bindValue(QStringLiteral(":userinfo"), user);
//     query.bindValue(QStringLiteral(":timestamp"), QDateTime::currentDateTimeUtc());
//     query.bindValue(QStringLiteral(":product"), project_name);
//     query.bindValue(QStringLiteral(":buildnum"), buildnumber);
//     query.bindValue(QStringLiteral(":project"), project_id);

//     isok = query.exec();
//     if(!isok) {goto end;}
// end:
//     Error(query.lastError());
//     Error(db.lastError());
//     db.close();
//     return isok;
// }


QFileInfo SQLHelper::GetMostRecent(const QString& path, const QString& pattern)
{
    QFileInfo most_recent;
    static const QDate d1 = QDate(1980,1,1);
#if QT_VERSION > QT_VERSION_CHECK(5, 14, 0)
    QDateTime tstamp = d1.startOfDay(Qt::UTC);// ::currentDateTimeUtc().addYears(-1);//f1.lastModified();
#else

    QDateTime tstamp(d1, QTime(0,0));  //d1.startOfDay(Qt::UTC);// ::currentDateTimeUtc().addYears(-1);//f1.lastModified();
#endif
    QRegularExpression re(pattern);

    QDirIterator it(path);
    while (it.hasNext()) {
        auto fn = it.next();
        QFileInfo fi(fn);
        if(!fi.isFile()) continue;
        auto m = re.match(fn);
        if(!m.hasMatch()) continue;

        auto ts = fi.lastModified();
        if(ts>tstamp){ tstamp=ts; most_recent = fi;}
    }
    return most_recent;
}

// QVariant SQLHelper::GetProjId(QSqlDatabase &db, const QString &project_name)
// {
//     if(!db.isValid()) return -1;
//     QVariant project_id;

//     QSqlQuery query(db);
//     bool isok = db.open();
//     if(!isok) {goto end; }

//     isok = query.exec(QStringLiteral("SELECT id FROM BuildInfoFlex.dbo.Projects WHERE Name='%1';").arg(project_name));
//     if(!isok) {goto end;}

//     if(query.size())
//     {
//         query.first();
//         project_id= query.value(0);
//     }
//     else
//         project_id = QVariant();

// end:
//     Error(query.lastError());
//     Error(db.lastError());
//     db.close();
//     return project_id;
// }
// bool isok = _db.open();
// QSqlQuery SQLHelper::GetQuery()
// {
//     //if(!_db.isValid()) return QSqlQuery();
//     QSqlQuery query(_db);
//     return query;
// }

// QSqlQuery SQLHelper::GetQuery(const QString& cmd)
// {
//     //if(!_db.isValid()) return QSqlQuery();
//     QSqlQuery query(_db);
//     //bool isok = _db.open();
//     query.prepare(cmd);
//     return query;
// }

// ROWID=:rowid
SQLHelper::DoQueryRModel SQLHelper::DoQuery(const QString& cmd, const QList<SQLHelper::SQLParam>& params)
{
    if(!_isInited) return {};

    zInfo("cmd:"+cmd);

    DoQueryRModel m;    
    bool opened = TryOpen();
    bool queryOk = false;
    if(opened) {
        //auto db = QSqlDatabase::database(_connName);
        QSqlQuery query(_db);

        query.prepare(cmd);
        if(!params.isEmpty()){
            //QStringList names = params.keys();
            for(auto&n:params){
                //QVariant v = params.value(n);
                if(n.fieldValue.isValid()){
                    query.bindValue(":"+n.paramName,n.fieldValue);
                }
                QString fieldValue = GetFieldValue(n.fieldValue);
                zInfo(n.paramName+":"+n.fieldName+"="+fieldValue
                      +" "+(n.fieldValue.isValid()?"valid":"invalid") +
                      " "+n.fieldValue.metaType().name());
            }
        }

        queryOk = query.exec();

        if(queryOk){
            if(query.isSelect()){
                m.rowsAffected = query.size();
            } else{
                m.rowsAffected = query.numRowsAffected();
            }

            if(query.isSelect() && m.rowsAffected>0){
                while (query.next()) {
                    QSqlRecord rec = query.record();
                    m.records.append(rec);
                }
            }
        }
        else
        {
            zWarning("Cannot execute query");
            //zWarning(ErrorString("db", _db.lastError()));
            zWarning(ErrorString("query", query.lastError()));
        }
        _db.close();
    }

    //m.dbError = _db.lastError();
    //m.queryError = query.lastError();
    m.isOk = opened && queryOk;

    zInfo(QStringLiteral("Query ")+(m.isOk?"succeed":"failed"));
    return m;
}

QString SQLHelper::GetFieldNames_UPDATE(const QList<SQLHelper::SQLParam>& params){
    if(params.isEmpty()) return {};
    QString e;
    //int i = 0;
    for(auto&a:params){
        if(a.fieldName.toLower()=="id") continue;
        if(!e.isEmpty()) e+=",";
        e+=a.fieldName+"=:"+a.paramName;
    }
    return e;
}



QString SQLHelper::GetFieldNames_INSERT(const QList<SQLHelper::SQLParam>& params){
    if(params.isEmpty()) return {};
    QString e;
    //int i = 0;
    for(auto&a:params){
        if(a.fieldName.toLower()=="id") continue;
        if(!e.isEmpty()) e+=",";
        e+=a.fieldName;
    }
    return e;
}

QString SQLHelper::GetParamList_INSERT(const QList<SQLHelper::SQLParam>& params){
    if(params.isEmpty()) return {};
    QString e;
    //int i = 0;
    for(auto&a:params){
        if(a.fieldName.toLower()=="id") continue;
        if(!e.isEmpty()) e+=",";
        e+=':'+a.paramName;
    }
    return e;
}

SQLHelper::DoQueryRModel SQLHelper::Call(const QString& cmd)//, const QList<SQLHelper::SQLParam>& params){
{
    if(!_isInited) return {};

    QString select = GetCallSelect(cmd);
    if(select.isEmpty()) return {};
    QString call = "call "+cmd;

    zInfo("cmd:"+call);
    zInfo("cmd:"+select);

    DoQueryRModel m;    
    bool opened = TryOpen();

    bool queryOk = false;
    if(opened) {
        //auto db = QSqlDatabase::database(_connName);
        QSqlQuery query(_db);

        query.prepare(call);

        queryOk= query.exec();

        if(queryOk)
        {
            query.prepare(select);

            query.exec();
            if(query.isSelect()){
                m.rowsAffected = query.size();
            } else{
                m.rowsAffected = query.numRowsAffected();
            }
            if(query.isSelect() && m.rowsAffected>0){
                while (query.next()) {
                    QSqlRecord rec = query.record();
                    m.records.append(rec);
                }
            }
        }
        else
        {
            zWarning("Cannot execute query");
            zWarning(ErrorString("query", query.lastError()));
        }
        _db.close();
    }

    m.isOk = opened && queryOk;

    zInfo(QStringLiteral("Call ")+(m.isOk?"succeed":"failed"));
    return m;
}

QString SQLHelper::GetFieldValue(const QVariant &v)
{
    if(v.isNull()) return "NULL";
    if(v.userType() == QMetaType::Type::QString){
        return "\""+v.toString()+"\"";
    }
    if(v.userType() == QMetaType::Type::QChar){
        return "\'"+v.toString()+"\'";
    }
    return v.toString();
}

QString SQLHelper::ErrorType_ToString(QSqlError::ErrorType t){
    switch(t){
    case QSqlError::ErrorType::NoError: return "NoError";
    case QSqlError::ErrorType::ConnectionError: return "ConnectionError";
    case QSqlError::ErrorType::StatementError: return "StatementError";
    case QSqlError::ErrorType::TransactionError: return "TransactionError";
    default: return "UnknownError";
    }
}

QString SQLHelper::ErrorString(const QString &p, const QSqlError &err)
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
}

QString SQLHelper::GetCallSelect(const QString &call)
{
    //QString s = "SELECT";
    QRegularExpression r(R"(\s*(@\w*))");

    QStringList t;
    QRegularExpressionMatchIterator a = r.globalMatch(call);
    while(a.hasNext()){
        QRegularExpressionMatch m = a.next();
        int capturedLength = m.lastCapturedIndex();
        bool hasValidCapture = capturedLength>=1;
        if(hasValidCapture){
            QString c0 = m.captured(1);
            t.append(c0);
        }
    }
    if(t.isEmpty()) return {};

    QString s = "SELECT "+t.join(", ")+';';
    return s;
}
