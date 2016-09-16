#include "api_dog_list.h"
#include <QxMemLeak.h>
//#include "precompiled.h"

QX_REGISTER_CPP_KASHIER(API_DOG_LIST)

namespace qx {
template <> void register_class(QxClass<API_DOG_LIST> & t)
{
  t.setName("API_DOG_LIST");

  t.id(& API_DOG_LIST::id, "DOGID");
  t.data(& API_DOG_LIST::dogcode, "DOGCODE");
  t.data(& API_DOG_LIST::dognum, "DOGNUM");
  t.data(& API_DOG_LIST::startdate, "STARTDATE");
  t.data(& API_DOG_LIST::enddate, "ENDDATE");
}}

API_DOG_LIST::API_DOG_LIST()
{
}
