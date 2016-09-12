#include "precompiled.h"

#ifndef API_DOG_LIST_H
#define API_DOG_LIST_H

class API_DOG_LIST
{
public:
    long id;
    QString dogcode;
    long dognum;
    QDateTime startdate;
    QDateTime enddate;
    long bill;
    int status;
    int csid;
    int tsid;
    int utid;
    int gid;
    API_DOG_LIST();
};

QX_REGISTER_HPP_KASHIER(API_DOG_LIST, qx::trait::no_base_class_defined, 0)

#endif // API_DOG_LIST_H
