#include "precompiled.h"

#ifndef TEST_TABLE_H
#define TEST_TABLE_H

class test_table
{
public:
    long m_id;
    QString m_name;
    int m_dogid;
    test_table();
};

QX_REGISTER_HPP_KASHIER(test_table, qx::trait::no_base_class_defined, 0)

typedef boost::shared_ptr<test_table> test_table_ptr;
typedef qx::QxCollection<QString, test_table_ptr> list_test_table;

#endif // TEST_TABLE_H
