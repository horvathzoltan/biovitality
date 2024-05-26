#ifndef FILEHELPER_H
#define FILEHELPER_H

#include <QStringList>
#include <QTextStream>


class FileHelper
{
    static bool _verbose;
public:
    enum FileErrors:int{
        Ok = 0,
        NoFileName,
        PathIsNotAbsolute,
        FileNotExists,
        CannotRead,
        CannotWrite, FileNameTooLong
    };



    class CSVModel{
    public:
        FileErrors error;
        QList<QVarLengthArray<QString>> records;
    };

    class TXTLinesModel{
    public:
        FileErrors error;
        QStringList lines;
    };

    static TXTLinesModel LoadLines(const QString& filename);
    static CSVModel LoadCSV(const QString& filename);
private:
    static void SetUtf8Encoding(QTextStream* st);
    static bool Validate_Load(const QString& filename, FileErrors *err);
    static bool Validate_Save(const QString& filename, FileErrors *err);

    static QStringList LoadLines_reader(QTextStream *st);
    static QList<QVarLengthArray<QString>> LoadCSV_reader(QTextStream *st);
};

#endif // FILEHELPER_H
