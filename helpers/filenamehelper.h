#ifndef FILENAMEHELPER_H
#define FILENAMEHELPER_H

#include <QString>

class FileNameHelper{
private:
    static bool _inited;
    static QString _projectPath;
    static bool _isTest;
public:
    static bool Init(const char *file = __FILE__);
    static QString GetTestFolderPath();
    static QString GetWorkingFolder();
    static void SetTestMode(bool v){_isTest=v;};

    static QString GetLogFileName();
};

#endif // FILENAMEHELPER_H
