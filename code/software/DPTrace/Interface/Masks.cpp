/*
 * ?Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $File: //topsync/releasesTs2/R2.3.0/utilities/ToPTrace/Interface/Masks.cpp $
 * $Revision: #1 $
 * $Date: 2015/10/27 $
 */

#include "Masks.h"

#include <chartdir.h>

/************
  G.823 PDH
************/

#define G823_PDH_MTIE 21
static double g823_pdh_mtie_x[G823_PDH_MTIE] = {
	1,
	7.3,
	10,
	20,
	100,
	1000,
	2000,
	5000,
	10000,
	20000,
	50000,
	100000,
	200000,
	500000,
	1000000,
	2000000,
	5000000,
	10000000,
	20000000,
	50000000,
	100000000
};
static double g823_pdh_mtie_y[G823_PDH_MTIE] = {
	732E-9,
	732E-9,
	1000E-9,
	2000E-9,
	2000E-9,
	2000E-9,
	2000E-9,
	2428.384E-9,
	2832.045E-9,
	3338.296E-9,
	4269.484E-9,
	5330E-9,
	6973.864E-9,
	10974.229E-9,
	16862.588E-9,
	27883.043E-9,
	59468.516E-9,
	110876.468E-9,
	212493.781E-9,
	515006.586E-9,
	1017238.04E-9
};
#define G823_PDH_TDEV 16
static double g823_pdh_tdev_x[G823_PDH_TDEV] = {
	1,
	10,
	48,
	100,
	200,
	500,
	1000,
	2000,
	5000,
	10000,
	20000,
	50000,
	100000,
	200000,
	500000,
	1000000
};
static double g823_pdh_tdev_y[G823_PDH_TDEV] = {
	34E-9,
	34E-9,
	34E-9,
	70E-9,
	75.031E-9,
	84.983E-9,
	96.247E-9,
	112.266E-9,
	144.353E-9,
	181E-9,
	233.706E-9,
	341.328E-9,
	467.473E-9,
	654.656E-9,
	1056.528E-9,
	1558E-9
};

MetricMask g823_pdh = {
	"G.823 PDH",
	{G823_PDH_MTIE,g823_pdh_mtie_x,g823_pdh_mtie_y},
	{G823_PDH_TDEV,g823_pdh_tdev_x,g823_pdh_tdev_y},
	Chart::SquareShape+7
};

/************
  G.823 PRC
************/

#define G823_PRC_MTIE 25
static double g823_prc_mtie_x[G823_PRC_MTIE] = {
	1,
	2,
	5,
	10,
	20,
	50,
	100,
	200,
	500,
	1000,
	2000,
	5000,
	10000,
	20000,
	50000,
	100000,
	200000,
	500000,
	1000000,
	2000000,
	5000000,
	10000000,
	20000000,
	50000000,
	100000000
};
static double g823_prc_mtie_y[G823_PRC_MTIE] = {
	25.275E-9,
	25.55E-9,
	26.375E-9,
	27.75E-9,
	30.5E-9,
	38.75E-9,
	52.5E-9,
	80E-9,
	162.5E-9,
	300E-9,
	310E-9,
	340E-9,
	390E-9,
	490E-9,
	790E-9,
	1290E-9,
	2290E-9,
	5290E-9,
	10290E-9,
	20290E-9,
	50290E-9,
	100290E-9,
	200290E-9,
	500290E-9,
	1000290E-9
};
#define G823_PRC_TDEV 11
static double g823_prc_tdev_x[G823_PRC_TDEV] = {
	1,
	10,
	100,
	1000,
	10000,
	20000,
	50000,
	100000,
	200000,
	500000,
	1000000
};
static double g823_prc_tdev_y[G823_PRC_TDEV] = {
	3E-9,
	3E-9,
	3E-9,
	30E-9,
	30E-9,
	33E-9,
	42E-9,
	57E-9,
	87E-9,
	177E-9,
	327E-9
};

MetricMask g823_prc = {
	"G.823 PRC",
	{G823_PRC_MTIE,g823_prc_mtie_x,g823_prc_mtie_y},
	{G823_PRC_TDEV,g823_prc_tdev_x,g823_prc_tdev_y},
	Chart::DiamondShape+7
};

/************
  G.823 SEC
************/

#define G823_SEC_MTIE 21
static double g823_sec_mtie_x[G823_SEC_MTIE] = {
	1,
	2.5,
	10,
	20,
	100,
	1000,
	2000,
	5000,
	10000,
	20000,
	50000,
	100000,
	200000,
	500000,
	1000000,
	2000000,
	5000000,
	10000000,
	20000000,
	50000000,
	100000000
};
static double g823_sec_mtie_y[G823_SEC_MTIE] = {
	250E-9,
	250E-9,
	1000E-9,
	2000E-9,
	2000E-9,
	2000E-9,
	2000E-9,
	2428.384E-9,
	2832.045E-9,
	3338.296E-9,
	4269.484E-9,
	5330E-9,
	6973.864E-9,
	10974.229E-9,
	16862.588E-9,
	27883.043E-9,
	59468.516E-9,
	110876.468E-9,
	212493.781E-9,
	515006.586E-9,
	1017238.04E-9
};
#define G823_SEC_TDEV 16
static double g823_sec_tdev_x[G823_SEC_TDEV] = {
	1,
	10,
	17.14,
	100,
	200,
	500,
	1000,
	2000,
	5000,
	10000,
	20000,
	50000,
	100000,
	200000,
	500000,
	1000000
};
static double g823_sec_tdev_y[G823_SEC_TDEV] = {
	12E-9,
	12E-9,
	12E-9,
	70E-9,
	75.031E-9,
	84.983E-9,
	96.247E-9,
	112.266E-9,
	144.353E-9,
	181E-9,
	233.706E-9,
	341.328E-9,
	467.473E-9,
	654.656E-9,
	1056.528E-9,
	1558E-9
};

MetricMask g823_sec = {
	"G.823 SEC",
	{G823_SEC_MTIE,g823_sec_mtie_x,g823_sec_mtie_y},
	{G823_SEC_TDEV,g823_sec_tdev_x,g823_sec_tdev_y},
	Chart::TriangleShape+7
};

/************
  G.823 SSU
************/

#define G823_SSU_MTIE 21
static double g823_ssu_mtie_x[G823_SSU_MTIE] = {
	1,
	2.5,
	10,
	100,
	200,
	1000,
	2000,
	5000,
	10000,
	20000,
	50000,
	100000,
	200000,
	500000,
	1000000,
	2000000,
	5000000,
	10000000,
	20000000,
	50000000,
	100000000
};
static double g823_ssu_mtie_y[G823_SSU_MTIE] = {
	25E-9,
	25E-9,
	100E-9,
	1000E-9,
	2000E-9,
	2000E-9,
	2000E-9,
	2428.384E-9,
	2832.045E-9,
	3338.296E-9,
	4269.484E-9,
	5330E-9,
	6973.864E-9,
	10974.229E-9,
	16862.588E-9,
	27883.043E-9,
	59468.516E-9,
	110876.468E-9,
	212493.781E-9,
	515006.586E-9,
	1017238.04E-9
};
#define G823_SSU_TDEV 16
static double g823_ssu_tdev_x[G823_SSU_TDEV] = {
	1,
	4.3,
	10,
	100,
	200,
	500,
	1000,
	2000,
	5000,
	10000,
	20000,
	50000,
	100000,
	200000,
	500000,
	1000000
};
static double g823_ssu_tdev_y[G823_SSU_TDEV] = {
	3E-9,
	3E-9,
	7E-9,
	70E-9,
	75.031E-9,
	84.983E-9,
	96.247E-9,
	112.266E-9,
	144.353E-9,
	181E-9,
	233.706E-9,
	341.328E-9,
	467.473E-9,
	654.656E-9,
	1056.528E-9,
	1558E-9
};

MetricMask g823_ssu = {
	"G.823 SSU",
	{G823_SSU_MTIE,g823_ssu_mtie_x,g823_ssu_mtie_y},
	{G823_SSU_TDEV,g823_ssu_tdev_x,g823_ssu_tdev_y},
	Chart::CircleShape+7
};

/************
  G.824 DS1
************/

#define G824_DS1_MTIE 26
static double g824_ds1_mtie_x[G824_DS1_MTIE] = {
	1,
	2,
	5,
	10,
	20,
	50,
	100,
	200,
	280,
	500,
	1000,
	2000,
	5000,
	10000,
	20000,
	50000,
	100000,
	200000,
	500000,
	1000000,
	2000000,
	5000000,
	10000000,
	20000000,
	50000000,
	100000000
};
static double g824_ds1_mtie_y[G824_DS1_MTIE] = {
	302.5E-9,
	305E-9,
	312.5E-9,
	325E-9,
	350E-9,
	425E-9,
	550E-9,
	800E-9,
	1000E-9,
	1002E-9,
	1007E-9,
	1017E-9,
	1047E-9,
	1097E-9,
	1197E-9,
	1497E-9,
	1997E-9,
	2997E-9,
	5997E-9,
	10997E-9,
	20997E-9,
	50997E-9,
	100997E-9,
	200997E-9,
	500997E-9,
	1000997E-9
};
#define G824_DS1_TDEV 4
static double g824_ds1_tdev_x[G824_DS1_TDEV] = {
	1,
	10,
	100,
	1000
};
static double g824_ds1_tdev_y[G824_DS1_TDEV] = {
	100E-9,
	100E-9,
	316.23E-9,
	1000.007E-9
};

MetricMask g824_ds1 = {
	"G.824 DS1",
	{G824_DS1_MTIE,g824_ds1_mtie_x,g824_ds1_mtie_y},
	{G824_DS1_TDEV,g824_ds1_tdev_x,g824_ds1_tdev_y},
	Chart::InvertedTriangleShape+7
};

/************
  ETSI PDH
************/

MetricMask etsi_pdh = {
	"ETSI PDH",
	{G823_PDH_MTIE,g823_pdh_mtie_x,g823_pdh_mtie_y},
	{G823_PDH_TDEV,g823_pdh_tdev_x,g823_pdh_tdev_y},
	Chart::SquareShape
};

/************
  ETSI PRC
************/

#define ETSI_PRC_MTIE 11
static double etsi_prc_mtie_x[ETSI_PRC_MTIE] = {
	1,
	10,
	83,
	100,
	1000,
	10000,
	30000,
	100000,
	1000000,
	10000000,
	100000000
};
static double etsi_prc_mtie_y[ETSI_PRC_MTIE] = {
	25E-9,
	25E-9,
	25E-9,
	30E-9,
	300E-9,
	300E-9,
	300E-9,
	1000E-9,
	10000E-9,
	100000E-9,
	1000000E-9
};
#define ETSI_PRC_TDEV 13
static double etsi_prc_tdev_x[ETSI_PRC_TDEV] = {
	1,
	10,
	100,
	1000,
	2000,
	5000,
	10000,
	20000,
	50000,
	100000,
	200000,
	500000,
	1000000
};
static double etsi_prc_tdev_y[ETSI_PRC_TDEV] = {
	3E-9,
	3E-9,
	3E-9,
	30E-9,
	30.3E-9,
	31.2E-9,
	32.7E-9,
	35.7E-9,
	44.7E-9,
	59.7E-9,
	89.7E-9,
	179.7E-9,
	329.7E-9
};

MetricMask etsi_prc = {
	"ETSI PRC",
	{ETSI_PRC_MTIE,etsi_prc_mtie_x,etsi_prc_mtie_y},
	{ETSI_PRC_TDEV,etsi_prc_tdev_x,etsi_prc_tdev_y},
	Chart::DiamondShape
};

/************
  ETSI SEC
************/

MetricMask etsi_sec = {
	"ETSI SEC",
	{G823_SEC_MTIE,g823_sec_mtie_x,g823_sec_mtie_y},
	{G823_SEC_TDEV,g823_sec_tdev_x,g823_sec_tdev_y},
	Chart::TriangleShape
};

/************
  ETSI SSU
************/

MetricMask etsi_ssu = {
	"ETSI SSU",
	{G823_SSU_MTIE,g823_ssu_mtie_x,g823_ssu_mtie_y},
	{G823_SSU_TDEV,g823_ssu_tdev_x,g823_ssu_tdev_y},
	Chart::CircleShape
};