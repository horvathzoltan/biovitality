#include "dowork.h"

//DoWork::DoWork()
//{

//}

auto DoWork::Work1(MainViewModel::DoWorkModel m) -> MainViewModel::StringModel
{
    return {QString::number(m.i+1)};
}
