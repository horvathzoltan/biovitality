#include "filehelper.h"
#include "helpers/logger.h"

#include <QFile>
#include <QFileInfo>

bool FileHelper::_verbose = false;

void FileHelper::SetUtf8Encoding(QTextStream* st)
{
    if(st==nullptr) return;
#if QT_VERSION >= 0x050000 && QT_VERSION < 0x060000
    st->setCodec("UTF-8"); //5.15.2
#elif QT_VERSION >= 0x06
    st->setEncoding(QStringConverter::Utf8);
#endif
}

bool FileHelper::Validate_Load(const QString& filename, FileErrors *err)
{
    bool valid = Validate_Save(filename, err);

    if(!valid) return false;

    QFileInfo fi(filename);

    if(!fi.exists())
    {
        if(_verbose) zInfo(QStringLiteral("file not exist: %1").arg(filename));
        if(err != nullptr) *err= FileErrors::FileNotExists;
        return false;
    }

    return true;
}

bool FileHelper::Validate_Save(const QString& filename, FileErrors *err)
{
    if(filename.isEmpty())
    {
        if(_verbose) zInfo(QStringLiteral("no file name").arg(filename));
        if(err != nullptr) *err= FileErrors::NoFileName;
        return false;
    }

    if(filename.length()>256)
    {
        if(_verbose) zInfo(QStringLiteral("filename too long: %1").arg(filename));
        if(err!=nullptr) *err = FileErrors::FileNameTooLong;
        return false;
    }

    QFileInfo fi(filename);

    if(!fi.isAbsolute())
    {
        if(_verbose) zInfo(QStringLiteral("path is not absolute: %1").arg(filename));
        if(err != nullptr) *err= FileErrors::PathIsNotAbsolute;
        return false;
    }

    return true;
}

FileHelper::TXTLinesModel FileHelper::LoadLines(const QString& filename)
{
    TXTLinesModel m;

    bool valid = Validate_Load(filename, &m.error);
    if(!valid) return m;

    //QFileInfo fi(filename);

    QFile f(filename);
    QStringList e;

    bool ok = f.open(QFile::ReadOnly | QFile::Text);

    if(!ok){
        if(_verbose) zInfo(QStringLiteral("cannot read file (%1): %2").arg(f.errorString(),filename));
        m.error= FileErrors::CannotRead;
        return m;
    }

    if(_verbose) zInfo(QStringLiteral("LoadLines: %1").arg(filename));
    QTextStream st(&f);
    SetUtf8Encoding(&st);

    m.lines = LoadLines_reader(&st);
    f.close();

    m.error= FileErrors::Ok;

    return m;
}

FileHelper::CSVModel FileHelper::LoadCSV(const QString& filename, const QChar& separator){
    CSVModel m;

    bool valid = Validate_Load(filename, &m.error);
    if(!valid) return m;

    //QFileInfo fi(filename);

    QFile f(filename);
    QStringList e;

    bool ok = f.open(QFile::ReadOnly | QFile::Text);

    if(!ok){
        if(_verbose) zInfo(QStringLiteral("cannot read file (%1): %2").arg(f.errorString(),filename));
        m.error= FileErrors::CannotRead;
        return m;
    }

    if(_verbose) zInfo(QStringLiteral("LoadCSV: %1").arg(filename));
    QTextStream st(&f);
    SetUtf8Encoding(&st);

    m.records = LoadCSV_reader(&st, separator);
    f.close();

    m.error= FileErrors::Ok;

    return m;
}


QStringList FileHelper::LoadLines_reader(QTextStream *st){
    QStringList e;
    while (!st->atEnd())
    {
        e << st->readLine();
    }
    return e;
}

QList<QVarLengthArray<QString>> FileHelper::LoadCSV_reader(QTextStream *st, const QChar& separator){
    QList<QVarLengthArray<QString>> rows;
    QVarLengthArray<QString> fields;
    QString s;
    bool inQuote = false;
    while (!st->atEnd())
    {
        QString line = st->readLine();

        int L = line.size();
        for(int i = 0;i<L;i++){
            QChar a = line[i];
            if(a=='"'){
                if(!inQuote){
                    inQuote = true;
                    continue;
                } else{
                    if(i+1<L){// van következő
                        QChar b = line[i+1];
                        if(b=='"'){
                            s+='"';
                            i+=1; continue;
                        } else{
                            inQuote = false;
                            continue;
                        }
                    } else{
                        //s+='"';
                        inQuote = false;
                        continue;
                    }
                }
            }

            if(!inQuote){
                if(a==separator){
                    fields.append(s);
                    s.clear();
                }
                else if(a=='\n'){
                    fields.append(s);
                    int size = fields.size();
                    fields.resize(size);
                    rows.append(fields);
                    fields.clear();
                    s.clear();
                } else{
                    s+=a;
                }
            } else{
                s+=a;
            }
        }
        if(!inQuote){
            fields.append(s);
            int size = fields.size();
            fields.resize(size);
            rows.append(fields);
            fields.clear();
            s.clear();
        }
    }
    return rows;
}



bool FileHelper::Save(const QString& txt, const QString& filename, FileErrors *err, SaveModes saveMode) {
    bool valid = FileHelper::Validate_Save(filename, err);
    if(!valid) return false;

    QFile f(filename);

    auto om = QIODevice::WriteOnly | QIODevice::Text; // openmode
    if(saveMode == SaveModes::Append) om |= QIODevice::Append;

    bool opened = f.open(om);

    if (!opened){
        if(_verbose) zInfo(QStringLiteral("cannot write file (%1): %2").arg(f.errorString(),filename));
        if(err != nullptr) *err= FileErrors::CannotWrite;
        return false;
    }

    if(_verbose) zInfo(QStringLiteral("Save: %1").arg(filename));
    QTextStream out(&f);
    SetUtf8Encoding(&out);
    out << txt;
    f.close();

    if(err != nullptr) *err= FileErrors::Ok;
    return true;
}


/*
QStringList FileHelper::LineReader_CSV(QTextStream *st){
    QStringList e;
    bool inQuote = false;
    //int q = 0;
    while (!st->atEnd())
    {
        QString line = st->readLine();

        QString s;
        QChar p = '\0';
        for(auto &a:line){
            if(a=='"'){
                if(p!='"'){
                    inQuote=!inQuote;
                    if(inQuote) continue;
                }
            }

            if(inQuote){
               if(p=='"'){
                    s+='"';
               }
               s+=a;

            } else{
                if(a=='\n'){
                    e.append(s);
                    s.clear();
                } else if(a!='"'){
                    s+=a;
                }
            }
            p=a;
        }
        if(!inQuote){
            e.append(s);
            s.clear();
        }
    }
    return e;
}





*/
