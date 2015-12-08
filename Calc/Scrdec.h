#ifndef __scrdec_H
#define __scrdec_H

#ifndef __envir_H
#include "envir.h"
#endif
//const	char	scr_meth_general = 0;
/*{scr_meth_general indicates general screen management.}*/

//const	char	scr_meth_borwin = 1;
/*{scr_meth_borwin indicates borland windows screen management.}*/
//char	scr_meth = scr_meth_general;

const char enabled_yes = 0; /*{Indicates that a particular object is enabled.}*/
const char enabled_no = 1; /*{Indicates that a particular object is disabled.}*/

/*{Screen error messages}*/

//const 	unsigned long	scr_err_inv_scr_meth = 2001;
/*{ scr_err_inv_scr_meth means invalid screen method.}*/
#endif

