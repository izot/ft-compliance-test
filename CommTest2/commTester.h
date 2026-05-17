//////////////////////////////////////////////////////////////////////////////
// File: commTester.h
// Copyright (c) 2001-2026 EnOcean Edge Corporation.  All rights reserved.
//
// EnOcean E MAKES NO REPRESENTATION, WARRANTY, OR CONDITION OF
// ANY KIND, EXPRESS, IMPLIED, STATUTORY, OR OTHERWISE OR IN
// ANY COMMUNICATION WITH YOU, INCLUDING, BUT NOT LIMITED TO,
// ANY IMPLIED WARRANTIES OF MERCHANTABILITY, SATISFACTORY
// QUALITY, FITNESS FOR ANY PARTICULAR PURPOSE,
// NONINFRINGEMENT, AND THEIR EQUIVALENTS.
//
//
// Written By: RTG   
//
// Description: Tests comm performance of FT communication
//
// commTester.h contains the declarations required the implementation
// of commTester. The fblock commTester itself is declared below.
// The member network variables and configuration properties, if any, are also
// declared within this file. 
//
//////////////////////////////////////////////////////////////////////////////

#ifndef _commTester_H_
#define _commTester_H_

#pragma net_buf_in_count 5 
#pragma app_buf_in_count 5
#pragma net_buf_out_priority_count 0
#pragma app_buf_out_priority_count 0
#pragma num_alias_table_entries 	16
#define USE_EXTERNAL_NAME

#   pragma num_addr_table_entries 15
//
//<Fblock CP Family Declarations>
network input cp SCPTdelayTime cpStartDelay;
network input cp SCPTupdateRate cpUpdateRate;
network input cp SCPTmaxRnge cpTestLimit;
//
//<Fblock Input NV Declarations>
network input SNVT_count_32 nviCount;
//
//<Fblock Output NV Declarations>
network output SNVT_count_32 nvoTarget_1;
network output SNVT_count_32 nvoTarget_2;
network output SNVT_count_32 nvoTarget_3;
network output SNVT_count_32 nvoTarget_4;
network output SNVT_count_32 nvoTarget_5;
network output SNVT_count_32 nvoTarget_6;
network output SNVT_count_32 nvoTarget_7;
network output SNVT_count_32 nvoTarget_8;
network output SNVT_count_32 nvoTarget_9;
network output SNVT_count_32 nvoTarget_10;
network output SNVT_count_32 nvoTarget_11;
network output SNVT_count_32 nvoTarget_12;
network output SNVT_count_32 nvoTarget_13;
network output SNVT_count_32 nvoTarget_14;
network output SNVT_count_32 nvoTarget_15;
network output SNVT_count_32 nvoFailCount;
//
//<Fblock Declaration>
fblock UFPTcommTester {
   nviCount    implements nviCount;
   nvoTarget_1    implements nvoTarget_1;
   nvoTarget_2    implements nvoTarget_2;
   nvoTarget_3    implements nvoTarget_3;
   nvoTarget_4    implements nvoTarget_4;
   nvoTarget_5    implements nvoTarget_5;
   nvoTarget_6    implements nvoTarget_6;
   nvoTarget_7    implements nvoTarget_7;
   nvoTarget_8    implements nvoTarget_8;
   nvoTarget_9    implements nvoTarget_9;
   nvoTarget_10    implements nvoTarget_10;
   nvoTarget_11    implements nvoTarget_11;
   nvoTarget_12    implements nvoTarget_12;
   nvoTarget_13    implements nvoTarget_13;
   nvoTarget_14    implements nvoTarget_14;
   nvoTarget_15    implements nvoTarget_15;
   nvoFailCount    implements nvoFailCount;
} commTester
#ifdef USE_EXTERNAL_NAME
   external_name("commTester")
#endif
fb_properties {
   cpStartDelay,
   cpUpdateRate,
   cpTestLimit
};
// IO declaration 
// EVB 6050 LEDs left IO_2, right IO_3
#define LED_ON 0
#define LED_OFF 1
#define NVO_COUNT 15

#ifdef NODEFARM_HW
IO_0 output bit LED1 = LED_OFF;
IO_1 output bit LED2 = LED_OFF;
#else
IO_2 output bit LED1 =  LED_OFF;
IO_3 output bit LED2 = LED_OFF;
#endif

#endif // _commTester_H_


