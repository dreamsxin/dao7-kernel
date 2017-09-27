#ifndef EXTNAME_VERSION_H
#define EXTNAME_VERSION_H

#include "php_extname.h"

#define EXTNAME_VERSION_ALPHA      1
#define EXTNAME_VERSION_BETA       2
#define EXTNAME_VERSION_RC         3
#define EXTNAME_VERSION_STABLE     4

extern zend_class_entry *extname_version_ce;

PHALCON_INIT_CLASS(Extname_Version);

#endif /* EXTNAME_VERSION_H */
