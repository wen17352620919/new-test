#include"test_data.h"

void analog_init(cmtr_cfg_analog analog[])
{
      //---------------------------------------------------------------- 模拟量  
        //cmtr_cfg_analog analog[10]; 
        analog[0].index = 0;
        strcpy((char*)analog[0].name,"Ua (母段二)");
        strcpy((char*)analog[0].phase," ");
        strcpy((char*)analog[0].element," ");
        strcpy((char*)analog[0].unit,"V ");
        analog[0].factor_a = 0.863037;
        analog[0].factor_b = 0;
        analog[0].offset_time = 0;
        analog[0].smp_min = -32767;
        analog[0].smp_max = 32768;
        analog[0].ct1 = 10000;
        analog[0].ct2 = 100;
        strcpy((char*)analog[0].flag,"P");
        //-------------------------------
        analog[1].index = 1;
        strcpy((char*)analog[1].name,"Ub (母段二)");
        strcpy((char*)analog[1].phase," ");
        strcpy((char*)analog[1].element," ");
        strcpy((char*)analog[1].unit,"V ");
        analog[1].factor_a = 0.863037;
        analog[1].factor_b = 0;
        analog[1].offset_time = 0;
        analog[1].smp_min = -32767;
        analog[1].smp_max = 32768;
        analog[1].ct1 = 10000;
        analog[1].ct2 = 100;
        strcpy((char*)analog[1].flag,"P");
        //------------------------------
        analog[2].index = 2;
        strcpy((char*)analog[2].name,"Uc (母段二)");
        strcpy((char*)analog[2].phase," ");
        strcpy((char*)analog[2].element," ");
        strcpy((char*)analog[2].unit,"V ");
        analog[2].factor_a = 0.863037;
        analog[2].factor_b = 0;
        analog[2].offset_time = 0;
        analog[2].smp_min = -32767;
        analog[2].smp_max = 32768;
        analog[2].ct1 = 10000;
        analog[2].ct2 = 100;
        strcpy((char*)analog[2].flag,"P");
        //-----------------------------
        analog[3].index = 3;
        strcpy((char*)analog[3].name,"U0 (母段二)");
        strcpy((char*)analog[3].phase," ");
        strcpy((char*)analog[3].element," ");
        strcpy((char*)analog[3].unit,"V ");
        analog[3].factor_a = 0.863037;
        analog[3].factor_b = 0;
        analog[3].offset_time = 0;
        analog[3].smp_min = -32767;
        analog[3].smp_max = 32768;
        analog[3].ct1 = 5770;
        analog[3].ct2 = 100;
        strcpy((char*)analog[3].flag,"P");
        //-----------------------------
        analog[4].index = 4;
        strcpy((char*)analog[4].name,"线路一");
        strcpy((char*)analog[4].phase," ");
        strcpy((char*)analog[4].element," ");
        strcpy((char*)analog[4].unit,"A ");
        analog[4].factor_a = 0.010788;
        analog[4].factor_b = 0;
        analog[4].offset_time = 0;
        analog[4].smp_min = -32767;
        analog[4].smp_max = 32768;
        analog[4].ct1 = 50;
        analog[4].ct2 = 1;
        strcpy((char*)analog[4].flag,"P");
        //-----------------------------
        analog[5].index = 5;
        strcpy((char*)analog[5].name,"线路二");
        strcpy((char*)analog[5].phase," ");
        strcpy((char*)analog[5].element," ");
        strcpy((char*)analog[5].unit,"A ");
        analog[5].factor_a = 0.010788;
        analog[5].factor_b = 0;
        analog[5].offset_time = 0;
        analog[5].smp_min = -32767;
        analog[5].smp_max = 32768;
        analog[5].ct1 = 50;
        analog[5].ct2 = 1;
        strcpy((char*)analog[5].flag,"P");
        //-----------------------------
        analog[6].index = 6;
         strcpy((char*)analog[6].name,"线路三");
        strcpy((char*)analog[6].phase," ");
        strcpy((char*)analog[6].element," ");
        strcpy((char*)analog[6].unit,"A ");
        analog[6].factor_a = 0.010788;
        analog[6].factor_b = 0;
        analog[6].offset_time = 0;
        analog[6].smp_min = -32767;
        analog[6].smp_max = 32768;
        analog[6].ct1 = 50;
        analog[6].ct2 = 1;
        strcpy((char*)analog[6].flag,"P");
        //-----------------------------
        analog[7].index = 7;
        strcpy((char*)analog[7].name,"线路四");
        strcpy((char*)analog[7].phase," ");
        strcpy((char*)analog[7].element," ");
        strcpy((char*)analog[7].unit,"A ");
        analog[7].factor_a = 0.010788;
        analog[7].factor_b = 0;
        analog[7].offset_time = 0;
        analog[7].smp_min = -32767;
        analog[7].smp_max = 32768;
        analog[7].ct1 = 50;
        analog[7].ct2 = 1;
        strcpy((char*)analog[7].flag,"P");
        //-----------------------------
        analog[8].index = 8;
        strcpy((char*)analog[8].name,"线路五");
        strcpy((char*)analog[8].phase," ");
        strcpy((char*)analog[8].element," ");
        strcpy((char*)analog[8].unit,"A ");
        analog[8].factor_a = 0.010788;
        analog[8].factor_b = 0;
        analog[8].offset_time = 0;
        analog[8].smp_min = -32767;
        analog[8].smp_max = 32768;
        analog[8].ct1 = 50;
        analog[8].ct2 = 1;
        strcpy((char*)analog[8].flag,"P");
        //-----------------------------
        analog[9].index = 9;
        strcpy((char*)analog[9].name,"线路六 ");
        strcpy((char*)analog[9].phase," ");
        strcpy((char*)analog[9].element," ");
        strcpy((char*)analog[9].unit,"A ");
        analog[9].factor_a = 0.010788;
        analog[9].factor_b = 0;
        analog[9].offset_time = 0;
        analog[9].smp_min = -32767;
        analog[9].smp_max = 32768;
        analog[9].ct1 = 50;
        analog[9].ct2 = 1;
        strcpy((char*)analog[9].flag,"P");
}

void digit_int()
{
        //-----------------------------------------------------------------
        cmtr_cfg_digit digit;
        digit.index = 1;
        digit.state = 0;
        strcpy((char*)digit.name,"digit");
}
//数据文件数据初始化
void dat_init()
{
          //------------------------------------------------------------------
        cmtr_dat_smpdot dot[10];
}



//模拟配置信息初始化
void cfg_init(cmtr_cfg_info* cfg)
{
        //---------------------------------------------------------------       
        strcpy((char*)cfg->station_name,"抚州钟岭变");
        strcpy((char*)cfg->kymograph_id,"1");
        cfg->analog_count = 10;
        cfg->digit_count = 0;
        //------------------------------------------------------------------采样率和采样点
        cfg->rate = 12800;
        cfg->point = 2564;
        //------------------------------------------------------------------
        analog_init(cfg->analogs);
        cfg->frequency = 50;
        cfg->smprate_count = 1;
        strcpy((char*)cfg->begin_time,"26/03/2016,10:49:35.0000");
        strcpy((char*)cfg->end_time,"26/03/2016,11:07:55.0000");
        strcpy((char*)cfg->file_type,"ASCALL");
}
