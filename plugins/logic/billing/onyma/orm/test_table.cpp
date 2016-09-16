#include "test_table.h"
#include <QxMemLeak.h>
//#include "precompiled.h"

QX_REGISTER_CPP_KASHIER(test_table)

namespace qx {
template <> void register_class(QxClass<test_table> & t)
{
  t.setName("test_table");

  t.id(& test_table::m_id, "id");
  t.data(& test_table::m_dogid, "dogid");
  t.data(& test_table::m_name, "name");
}}

test_table::test_table()
{
}
