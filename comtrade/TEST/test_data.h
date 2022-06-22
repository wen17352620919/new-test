#ifndef __TEST_DATA_H
#define __TEST_DATA_H
#include "../comtrade/my_comtrade.h"
#include  "../FileOperation/file.h"

#ifdef __cplusplus
extern "C" {
#endif

void analog_init();
void digit_int();
void dat_init();
void cfg_init(cmtr_cfg_info* cfg);


#ifdef __cplusplus
}
#endif
#endif // !__TEST_DATA_H
