/*
 * ?Semtech Corporation, P.O. Box 6097, Camarillo, CA 93011-6097
 * U.S.A. All rights reserved. The copyright of the content of this file
 * is owned by Semtech Corporation (Semtech). This is an unpublished
 * work.  The content of this file must be used only for the purpose for
 * which it was supplied by Semtech or its distributors. The content of
 * this file must not be copied or disclosed unless authorised in
 * writing by Semtech.
 *
 * $File: //topsync/releasesTs2/R2.3.0/utilities/ToPTrace/Interface/Trace.cpp $
 * $Revision: #1 $
 * $Date: 2015/10/27 $
 */

#include "Trace.h"

#include "DerivedTraceHost.h"
#include "Floats.h"
#include "Macros.h"
#include "Main.h"
#include "TraceScaling.h"
#include "../version.h"

#include <wx/dcclient.h>
#include <wx/dcmemory.h>
#include <wx/image.h>
#include <wx/menu.h>
#include <wx/mstream.h>
#include <wx/regex.h>
#include <wx/msw/private.h>

#include <iomanip>
#include <sstream>

extern bool readingFromFile;
extern wxChar localeDecimalPoint;

std::vector<ttTraceWindow*> traces;
wxMutex                     traces_mutex;
std::vector<ttParameter>    parameters;
bool	                    parametersValidated = false;
wxMutex                     parameters_mutex;
std::vector<ttTraceWindow*> parameterListeners;
static std::vector<ttTraceWindow*> recentTraces;

ttParameterDetails          parameterDetails[KNOWN_FIELDS] = {
	// Delay measurement
	{ "MS Time",             "Master-Slave Time",           "s",  NoValue, NoValue, NoValue, true  },
	{ "SM Time",             "Slave-Master Time",           "s",  NoValue, NoValue, NoValue, true  },
	{ "MS Delay",            "Master-Slave Delay",          "s",  NoValue, NoValue, NoValue, true  },
	{ "SM Delay",            "Slave-Master Delay",          "s",  NoValue, NoValue, NoValue, true  },
	{ "MS Corr Delay",       "M-S Corrected Delay",         "s",  NoValue, NoValue, NoValue, true  },
	{ "SM Corr Delay",       "S-M Corrected Delay",         "s",  NoValue, NoValue, NoValue, true  },
	{ "MS Corr Field",       "M-S Correction Field",        "s",  NoValue, NoValue, NoValue, true  },
	{ "SM Corr Field",       "S-M Correction Field",        "s",  NoValue, NoValue, NoValue, true  },
	{ "Phase Error",         "Phase Error",                 "s",  NoValue, NoValue, NoValue, false },
	
	// Everything else											  
	{ "Time",                "ToPSync Time",                "s",  NoValue, NoValue, NoValue, false },
	{ "Curr Time",           "ToPSync Time",                "s",  NoValue, NoValue, NoValue, false }, // Renamed in 5.3.0rc1/1.0.0rc4
	{ "Phase",               "Phase Error",                 "s",  NoValue, NoValue, NoValue, false },
	{ "O/P Filt Ph Err",     "Phase Error",                 "s",  NoValue, NoValue, NoValue, false }, // Renamed in 5.3.0rc1/1.0.0rc4
																  
	{ "MS pkt delay",        "Master-Slave Delay",          "s",  NoValue, NoValue, NoValue, true  },
	{ "SM pkt delay",        "Slave-Master Delay",          "s",  NoValue, NoValue, NoValue, true  },
	{ "MS noise mean",       "Master-Slave Noise (Mean)",   "s",  NoValue, NoValue, NoValue, false },
	{ "SM noise mean",       "Slave-Master Noise (Mean)",   "s",  NoValue, NoValue, NoValue, false },
	{ "MS noise std",        "Master-Slave PDV",            "s",  NoValue, NoValue, NoValue, false },
	{ "MS PDV",              "Master-Slave PDV",            "s",  NoValue, NoValue, NoValue, false }, // Renamed in 5.3.0rc1/1.0.0rc4
	{ "SM noise std",        "Slave-Master PDV",            "s",  NoValue, NoValue, NoValue, false },
	{ "SM PDV",              "Slave-Master PDV",            "s",  NoValue, NoValue, NoValue, false }, // Renamed in 5.3.0rc1/1.0.0rc4
	{ "MS filter",           "Master-Slave Filter",         "",   NoValue, NoValue, NoValue, false },
	{ "SM filter",           "Slave-Master Filter",         "",   NoValue, NoValue, NoValue, false },
																  
	{ "Locked",              "Lock Validity",               "",   1.0,     0.0,     0.1,     false },
	{ "Sys Locked",          "Lock Validity",               "",   1.0,     0.0,     0.1,     false }, // Renamed in 5.3.0rc1/1.0.0rc4
	{ "LD mean gradient",    "Lock Gradient (Mean)",        "",   NoValue, NoValue, NoValue, false },
	{ "LD int phase",        "Lock Integral Phase",         "",   NoValue, NoValue, NoValue, false },
																  
	{ "Ticks to VM timeout", "Ticks to Master Timeout",     "",   NoValue, NoValue, NoValue, false },
	{ "VM timeout",          "Ticks to Master Timeout",     "",   NoValue, NoValue, NoValue, false }, // Renamed in 5.3.0rc1/1.0.0rc4
	{ "Sync Success",        "Successful Syncs",            "",   1.0,     0.0,     0.1,     false },
	{ "Sync Rx",             "Successful Syncs",            "",   1.0,     0.0,     0.1,     false }, // Renamed in 5.3.0rc1/1.0.0rc4
	{ "DReq Success",        "Successful Delay Requests",   "",   1.0,     0.0,     0.1,     false },
	{ "DResp Rx",            "Successful Delay Requests",   "",   1.0,     0.0,     0.1,     false }, // Renamed in 5.3.0rc1/1.0.0rc4
																  
	// Erstweil hidden ones										  
	{ "CmbPh",               "Phase Error: Normal Mode",    "s",  NoValue, NoValue, NoValue, false },
	{ "Norm mode Ph Err",    "Phase Error: Normal Mode",    "s",  NoValue, NoValue, NoValue, false }, // Renamed in 5.3.0rc1/1.0.0rc4
	{ "ClockError",          "Hybrid Clock Freq. Error",    "s",  NoValue, NoValue, NoValue, false },
	{ "Hyb clk Freq err",    "Hybrid Clock Freq. Error",    "s",  NoValue, NoValue, NoValue, false }, // Renamed in 5.3.0rc1/1.0.0rc4
	{ "XO offset",           "Offset from Oscillator",      "Hz", NoValue, NoValue, NoValue, false }, // Added in 5.3.0rc1/1.0.0rc4 (was previously the hidden 'I')
	{ "HTCPhaseLag",         "Phase Error: Hybrid Mode",    "s",  NoValue, NoValue, NoValue, false },
	{ "Hyb mode Ph Err",     "Phase Error: Hybrid Mode",    "s",  NoValue, NoValue, NoValue, false }, // Renamed in 5.3.0rc1/1.0.0rc4
	{ "In H/O",              "In Holdover",                 "",   1.0,     0.0,     1.0,     false }, // Added in 5.3.0rc1/1.0.0rc4 (was previously the hidden 'HoldoverStatus')

	// Hidden ones
	{ "CM actual lag",       "Master Lag: Actual",          "s",  NoValue, NoValue, NoValue, false },
	{ "CM target lag",       "Master Lag: Target",          "s",  NoValue, NoValue, NoValue, false },
	{ "CM lag valid",        "Master Lag Validity",         "",   NoValue, NoValue, NoValue, false },
	{ "CM lag error",        "Master Lag Error",            "s",  NoValue, NoValue, NoValue, false },
	{ "MS minimum filter",   "Master-Slave Minimum Filter", "",   NoValue, NoValue, NoValue, false },
	{ "SM minimum filter",   "Slave-Master Minimum Filter", "",   NoValue, NoValue, NoValue, false },
	{ "RawPh",               "Phase: Raw",                  "s",  NoValue, NoValue, NoValue, false },
	{ "2pathPh",             "Phase: 2nd Path",             "s",  NoValue, NoValue, NoValue, false },
	{ "1pathPh",             "Phase: 1st Path",             "s",  NoValue, NoValue, NoValue, false },
	{ "MSCoef",              "Master-Slave Co-efficient",   "",   NoValue, NoValue, NoValue, false },
	{ "SMCoef",              "Slave-Master Co-efficient",   "",   NoValue, NoValue, NoValue, false },
	{ "LagOffset",           "Lag Offset",                  "s",  NoValue, NoValue, NoValue, false },
	{ "2ndPLag",             "Phase Error: 2nd",            "s",  NoValue, NoValue, NoValue, false },
	{ "Unlocked phase lag",  "Phase Error: Unlocked",       "s",  NoValue, NoValue, NoValue, false },

	// Clock PLL 1 - Basics
	{ "C1Time",              "CLK 1 Current Time",                 "s",  NoValue, NoValue, NoValue, false },
	{ "C1PllState",          "CLK PLL 1 State",                    "",   NoValue, NoValue, NoValue, false },
	{ "C1PhErr",             "CLK 1 Phase Error",                  "s",  NoValue, NoValue, NoValue, false },
	{ "C1HOvr",              "CLK PLL 1 In Holdover",              "",   1.0,     0.0,     1.0,     true  },
	{ "C1Lck",               "CLK 1 Lock Value",                   "",   1.0,     0.0,     0.1,     false },
	{ "CLK 1 Vs OtherCLK",   "CLK 1 Phase Error vs Reference Clk", "s",  NoValue, NoValue, NoValue, false },
	// Clock PLL 1 - Details
	{ "C1FrqDelta",          "CLK 1 Frequency Delta",              "Hz", NoValue, NoValue, NoValue, false },

	// Clock PLL 2 - Basics
	{ "C2Time",              "CLK 2 Current Time",                 "s",  NoValue, NoValue, NoValue, false },
	{ "C2PllState",          "CLK PLL 2 State",                    "",   NoValue, NoValue, NoValue, false },
	{ "C2PhErr",             "CLK 2 Phase Error",                  "s",  NoValue, NoValue, NoValue, false },
	{ "C2HOvr",              "CLK PLL 2 In Holdover",              "",   1.0,     0.0,     1.0,     true  },
	{ "C2Lck",               "CLK 2 Lock Value",                   "",   1.0,     0.0,     0.1,     false },
	{ "CLK 2 Vs OtherCLK",   "CLK 2 Phase Error vs Reference Clk", "s",  NoValue, NoValue, NoValue, false },
	// Clock PLL 2 - Details
	{ "C2FrqDelta",          "CLK 2 Frequency Delta",              "Hz", NoValue, NoValue, NoValue, false },

	// PTP PLL 1 - Basics
	{ "P1Time",              "PTP Slave 1 Current Time",                   "s",    NoValue, NoValue, NoValue, false },
	{ "P1State",             "PTP Slave 1 State",                          "",     NoValue, NoValue, NoValue, false },
	{ "P1PllState",          "PTP PLL 1 State",                            "",     NoValue, NoValue, NoValue, false },
	{ "P1Lck",               "PTP Slave 1 Lock Value",                     "",     1.0,     0.0,     0.1,     false },
	{ "P1PhErr",             "PTP Slave 1 Phase Error",                    "s",    NoValue, NoValue, NoValue, false },
	{ "P1HOvr",              "PTP Slave 1 In Holdover",                    "",     1.0,     0.0,     1.0,     true  },
	// PTP PLL 1 - Details
	{ "P1HyCkFrqDelta",      "Hybrid Clock/PTP Slave 1 Frequency Delta",   "Hz",   NoValue, NoValue, NoValue, false },
	{ "P1LOFrqDelta",        "PTP Slave 1 LO Frequency Delta",             "Hz",   NoValue, NoValue, NoValue, false },		//	76£¬
	{ "P1MSLstDel",          "PTP Slave 1 Last Measured M-S delay",        "s",    NoValue, NoValue, NoValue, true  },
	{ "P1SMLstDel",          "PTP Slave 1 Last Measured S-M delay",        "s",    NoValue, NoValue, NoValue, true  },
    { "P1MSLastCFVal",       "PTP Slave 1 M-S Last CF Value",              "s",    NoValue, NoValue, NoValue, true  },
	{ "P1SMLastCFVal",       "PTP Slave 1 S-M Last CF Value",              "s",    NoValue, NoValue, NoValue, true  },
	{ "P1LstRawPhaLag",      "PTP Slave 1 Last Measured Raw Phase Lag",    "s",    NoValue, NoValue, NoValue, false },
	{ "P1MSFiltPDV",         "PTP Slave 1 M-S Filtered PDV",               "s",    NoValue, NoValue, NoValue, false },
	{ "P1SMFiltPDV",         "PTP Slave 1 S-M Filtered PDV",               "s",    NoValue, NoValue, NoValue, false },
	{ "P1MSNomPkRate",       "PTP Slave 1 M-S Nominal Pk Rate",            "pk/s", NoValue, NoValue, NoValue, false },
	{ "P1SMNomPkRate",       "PTP Slave 1 S-M Nominal Pk Rate",            "pk/s", NoValue, NoValue, NoValue, false },
	{ "P1MSMnDel",           "PTP Slave 1 M-S Minimum Delay",              "s",    NoValue, NoValue, NoValue, false },
	{ "P1SMMnDel",           "PTP Slave 1 S-M Minimum Delay",              "s",    NoValue, NoValue, NoValue, false },
	{ "P1MSMxDel",           "PTP Slave 1 M-S Maximum Delay",              "s",    NoValue, NoValue, NoValue, false },
	{ "P1SMMxDel",           "PTP Slave 1 S-M Maximum Delay",              "s",    NoValue, NoValue, NoValue, false },
	{ "P1PhErrVsRefClk",     "PTP Slave 1 Phase Error vs Reference Clk",   "s",    NoValue, NoValue, NoValue, false },
	{ "P1vsP2PhErr",         "PTP Slave 1 Phase Error vs PTP Slave 2",     "s",    NoValue, NoValue, NoValue, false },
	// PTP PLL 1 - Debug
	{ "P1T1TsRx",            "PTP Slave 1 T1 Timestamps Received",         "",     NoValue, NoValue, NoValue, false },
	{ "P1T1TsMx",            "PTP Slave 1 T1 Timestamps Missing",          "",     NoValue, NoValue, NoValue, false },
	{ "P1T2TsRx",            "PTP Slave 1 T2 Timestamps Received",         "",     NoValue, NoValue, NoValue, false },
	{ "P1T2TsMx",            "PTP Slave 1 T2 Timestamps Missing",          "",     NoValue, NoValue, NoValue, false },
	{ "P1T3TsRx",            "PTP Slave 1 T3 Timestamps Received",         "",     NoValue, NoValue, NoValue, false },
	{ "P1T3TsMx",            "PTP Slave 1 T3 Timestamps Missing",          "",     NoValue, NoValue, NoValue, false },
	{ "P1T4TsRx",            "PTP Slave 1 T4 Timestamps Received",         "",     NoValue, NoValue, NoValue, false },
	{ "P1T4TsMx",            "PTP Slave 1 T4 Timestamps Missing",          "",     NoValue, NoValue, NoValue, false },
	{ "P1MSDlyRx",           "PTP Slave 1 M-S Delay Message Received",     "",     NoValue, NoValue, NoValue, false },
	{ "P1SMDlyRx",           "PTP Slave 1 S-M Delay Message Received",     "",     NoValue, NoValue, NoValue, false },
	{ "P1LstT1Val",          "PTP Slave 1 Last T1 Timestamp Value",        "s",    NoValue, NoValue, NoValue, false },
	{ "P1LstT2Val",          "PTP Slave 1 Last T2 Timestamp Value",        "s",    NoValue, NoValue, NoValue, false },
	{ "P1LstT3Val",          "PTP Slave 1 Last T3 Timestamp Value",        "s",    NoValue, NoValue, NoValue, false },
	{ "P1LstT4Val",          "PTP Slave 1 Last T4 Timestamp Value",        "s",    NoValue, NoValue, NoValue, false },
	{ "P1HldOffTcks",        "PTP Slave 1 Remaining Holdoff Ticks",        "",     NoValue, NoValue, NoValue, false },
	{ "P1MsSlWinSize",       "PTP Slave 1 M-S Sliding Window Size",        "s",    NoValue, NoValue, NoValue, false },
	{ "P1SMSlWinSize",       "PTP Slave 1 S-M Sliding Window Size",        "s",    NoValue, NoValue, NoValue, false },
	{ "P1MSFltPDel",         "PTP Slave 1 M-S Filtered Path Delay",        "s",    NoValue, NoValue, NoValue, false },
	{ "P1SMFltPDel",         "PTP Slave 1 S-M Filtered Path Delay",        "s",    NoValue, NoValue, NoValue, false },
	{ "P1MSFltMinDel",       "PTP Slave 1 M-S Filtered Min Delay",         "s",    NoValue, NoValue, NoValue, false },
	{ "P1SMFltMinDel",       "PTP Slave 1 S-M Filtered Min Delay",         "s",    NoValue, NoValue, NoValue, false },
	{ "P1ModPhErr",          "PTP Slave 1 Modelled Phase Error",           "s",    NoValue, NoValue, NoValue, false },
	{ "P1MSPDelFlr",         "PTP Slave 1 M-S Est Path Delay Above Floor", "s",    NoValue, NoValue, NoValue, false },
	{ "P1SMPDelFlr",         "PTP Slave 1 S-M Est Path Delay Above Floor", "s",    NoValue, NoValue, NoValue, false },
	{ "P1RTDFlr",            "PTP Slave 1 RTD Est Above Floor",            "s",    NoValue, NoValue, NoValue, false },
	{ "P1RawMnDelPhLag",     "PTP Slave 1 Raw Min Delay Phase Lag",        "s",    NoValue, NoValue, NoValue, false },
	{ "P12DirPhLag",         "PTP Slave 1 Processed 2dir Phase Lag",       "s",    NoValue, NoValue, NoValue, false },
	{ "P1UniDirPhLag",       "PTP Slave 1 Processed UniDir Phase Lag",     "s",    NoValue, NoValue, NoValue, false },
	{ "P1GCERx",             "PTP Slave 1 Grand Clock Err Received",       "s",    NoValue, NoValue, NoValue, false },
	{ "P1UniSel",            "PTP Slave 1 Unidirection Selection",         "",     2.0,     0.0,     1.0,     true  },
	{ "P1UseMdFltAlg",       "PTP Slave 1 Use Median Filter Algorithm",    "",     1.0,     0.0,     1.0,     true  },
	{ "P1NseC",              "PTP Slave 1 Noise Compensation",             "s",    NoValue, NoValue, NoValue, false },
	{ "P1RTDC",              "PTP Slave 1 RTD Compensation",               "s",    NoValue, NoValue, NoValue, false },
	{ "P1MdAlgC",            "PTP Slave 1 Median Algorithm Compensation",  "s",    NoValue, NoValue, NoValue, false },
	{ "P1GlbMnRTD",          "PTP Slave 1 Global Minimum RTD",             "s",    NoValue, NoValue, NoValue, false },
	{ "P1UlckPllBW",         "PTP Slave 1 Current Unlocked PLL B/W",       "Hz",   NoValue, NoValue, NoValue, false },
	{ "P1LckPllBW",          "PTP Slave 1 Current Locked PLL B/W",         "Hz",   NoValue, NoValue, NoValue, false },

	// PTP PLL 2 - Basics
	{ "P2Time",              "PTP Slave 2 Current Time",                   "s",    NoValue, NoValue, NoValue, false },
	{ "P2State",             "PTP Slave 2 State",                          "",     NoValue, NoValue, NoValue, false },
	{ "P2PllState",          "PTP PLL 2 State",                            "",     NoValue, NoValue, NoValue, false },
	{ "P2Lck",               "PTP Slave 2 Lock Value",                     "",     1.0,     0.0,     0.1,     false },
	{ "P2PhErr",             "PTP Slave 2 Phase Error",                    "s",    NoValue, NoValue, NoValue, false },
	{ "P2HOvr",              "PTP Slave 2 In Holdover",                    "",     1.0,     0.0,     1.0,     true  },
	// PTP PLL 2 - Details
	{ "P2HyCkFrqDelta",      "Hybrid Clock/PTP Slave 2 Frequency Delta",   "Hz",   NoValue, NoValue, NoValue, false },
	{ "P2LOFrqDelta",        "PTP Slave 2 LO Frequency Delta",             "Hz",   NoValue, NoValue, NoValue, false },
	{ "P2MSLstDel",          "PTP Slave 2 Last Measured M-S delay",        "s",    NoValue, NoValue, NoValue, true  },
	{ "P2SMLstDel",          "PTP Slave 2 Last Measured S-M delay",        "s",    NoValue, NoValue, NoValue, true  },
	{ "P2MSLastCFVal",       "PTP Slave 2 M-S Last CF Value",              "s",    NoValue, NoValue, NoValue, true  },
	{ "P2SMLastCFVal",       "PTP Slave 2 S-M Last CF Value",              "s",    NoValue, NoValue, NoValue, true  },
	{ "P2LstRawPhaLag",      "PTP Slave 2 Last Measured Raw Phase Lag",    "s",    NoValue, NoValue, NoValue, false },	
	{ "P2MSFiltPDV",         "PTP Slave 2 M-S Filtered PDV",               "s",    NoValue, NoValue, NoValue, false },
	{ "P2SMFiltPDV",         "PTP Slave 2 S-M Filtered PDV",               "s",    NoValue, NoValue, NoValue, false },
	{ "P2MSNomPkRate",       "PTP Slave 2 M-S Nominal Pk Rate",            "pk/s", NoValue, NoValue, NoValue, false },
	{ "P2SMNomPkRate",       "PTP Slave 2 S-M Nominal Pk Rate",            "pk/s", NoValue, NoValue, NoValue, false },
	{ "P2MSMnDel",           "PTP Slave 2 M-S Minimum Delay",              "s",    NoValue, NoValue, NoValue, false },
	{ "P2SMMnDel",           "PTP Slave 2 S-M Minimum Delay",              "s",    NoValue, NoValue, NoValue, false },
	{ "P2MSMxDel",           "PTP Slave 2 M-S Maximum Delay",              "s",    NoValue, NoValue, NoValue, false },
	{ "P2SMMxDel",           "PTP Slave 2 S-M Maximum Delay",              "s",    NoValue, NoValue, NoValue, false },
	{ "P2PhErrVsRefClk",     "PTP Slave 2 Phase Error vs Reference Clk",   "s",    NoValue, NoValue, NoValue, false },
	{ "P2vsP1PhErr",         "PTP Slave 2 Phase Error vs PTP Slave 2",     "s",    NoValue, NoValue, NoValue, false },
	// PTP PLL 2 - Debug
	{ "P2T1TsRx",            "PTP Slave 2 T1 Timestamps Received",         "",     NoValue, NoValue, NoValue, false },
	{ "P2T1TsMx",            "PTP Slave 2 T1 Timestamps Missing",          "",     NoValue, NoValue, NoValue, false },
	{ "P2T2TsRx",            "PTP Slave 2 T2 Timestamps Received",         "",     NoValue, NoValue, NoValue, false },
	{ "P2T2TsMx",            "PTP Slave 2 T2 Timestamps Missing",          "",     NoValue, NoValue, NoValue, false },
	{ "P2T3TsRx",            "PTP Slave 2 T3 Timestamps Received",         "",     NoValue, NoValue, NoValue, false },
	{ "P2T3TsMx",            "PTP Slave 2 T3 Timestamps Missing",          "",     NoValue, NoValue, NoValue, false },
	{ "P2T4TsRx",            "PTP Slave 2 T4 Timestamps Received",         "",     NoValue, NoValue, NoValue, false },
	{ "P2T4TsMx",            "PTP Slave 2 T4 Timestamps Missing",          "",     NoValue, NoValue, NoValue, false },
	{ "P2MSDlyRx",           "PTP Slave 2 M-S Delay Message Received",     "",     NoValue, NoValue, NoValue, false },
	{ "P2SMDlyRx",           "PTP Slave 2 S-M Delay Message Received",     "",     NoValue, NoValue, NoValue, false },
	{ "P2LstT1Val",          "PTP Slave 2 Last T1 Timestamp Value",        "s",    NoValue, NoValue, NoValue, false },
	{ "P2LstT2Val",          "PTP Slave 2 Last T2 Timestamp Value",        "s",    NoValue, NoValue, NoValue, false },
	{ "P2LstT3Val",          "PTP Slave 2 Last T3 Timestamp Value",        "s",    NoValue, NoValue, NoValue, false },
	{ "P2LstT4Val",          "PTP Slave 2 Last T4 Timestamp Value",        "s",    NoValue, NoValue, NoValue, false },
	{ "P2HldOffTcks",        "PTP Slave 2 Remaining Holdoff Ticks",        "",     NoValue, NoValue, NoValue, false },
	{ "P2MsSlWinSize",       "PTP Slave 2 M-S Sliding Window Size",        "s",    NoValue, NoValue, NoValue, false },
	{ "P2SMSlWinSize",       "PTP Slave 2 S-M Sliding Window Size",        "s",    NoValue, NoValue, NoValue, false },
	{ "P2MSFltPDel",         "PTP Slave 2 M-S Filtered Path Delay",        "s",    NoValue, NoValue, NoValue, false },
	{ "P2SMFltPDel",         "PTP Slave 2 S-M Filtered Path Delay",        "s",    NoValue, NoValue, NoValue, false },
	{ "P2MSFltMinDel",       "PTP Slave 2 M-S Filtered Min Delay",         "s",    NoValue, NoValue, NoValue, false },
	{ "P2SMFltMinDel",       "PTP Slave 2 S-M Filtered Min Delay",         "s",    NoValue, NoValue, NoValue, false },
	{ "P2ModPhErr",          "PTP Slave 2 Modelled Phase Error",           "s",    NoValue, NoValue, NoValue, false },
	{ "P2MSPDelFlr",         "PTP Slave 2 M-S Est Path Delay Above Floor", "s",    NoValue, NoValue, NoValue, false },
	{ "P2SMPDelFlr",         "PTP Slave 2 S-M Est Path Delay Above Floor", "s",    NoValue, NoValue, NoValue, false },
	{ "P2RTDFlr",            "PTP Slave 2 RTD Est Above Floor",            "s",    NoValue, NoValue, NoValue, false },
	{ "P2RawMnDelPhLag",     "PTP Slave 2 Raw Min Delay Phase Lag",        "s",    NoValue, NoValue, NoValue, false },
	{ "P22DirPhLag",         "PTP Slave 2 Processed 2dir Phase Lag",       "s",    NoValue, NoValue, NoValue, false },
	{ "P2UniDirPhLag",       "PTP Slave 2 Processed UniDir Phase Lag",     "s",    NoValue, NoValue, NoValue, false },
	{ "P2GCERx",             "PTP Slave 2 Grand Clock Err Received",       "s",    NoValue, NoValue, NoValue, false },
	{ "P2UniSel",            "PTP Slave 2 Unidirection Selection",         "",     2.0,     0.0,     1.0,     true  },
	{ "P2UseMdFltAlg",       "PTP Slave 2 Use Median Filter Algorithm",    "",     1.0,     0.0,     1.0,     true  },
	{ "P2NseC",              "PTP Slave 2 Noise Compensation",             "s",    NoValue, NoValue, NoValue, false },
	{ "P2RTDC",              "PTP Slave 2 RTD Compensation",               "s",    NoValue, NoValue, NoValue, false },
	{ "P2MdAlgC",            "PTP Slave 2 Median Algorithm Compensation",  "s",    NoValue, NoValue, NoValue, false },
	{ "P2GlbMnRTD",          "PTP Slave 2 Global Minimum RTD",             "s",    NoValue, NoValue, NoValue, false },
	{ "P2UlckPllBW",         "PTP Slave 2 Current Unlocked PLL B/W",       "Hz",   NoValue, NoValue, NoValue, false },
	{ "P2LckPllBW",          "PTP Slave 2 Current Locked PLL B/W",         "Hz",   NoValue, NoValue, NoValue, false },

	// Node Time 1 - Basics
	{ "N1Time",              "Node Time 1 Current Time",                                 "s", NoValue, NoValue, NoValue, false },
	{ "N1SrcId",             "Node Time 1 Source ID",                                    "",  3.0,     0.0,     1.0,     true  },
	{ "N1Hovr",              "Node Time 1 In Holdover",                                  "",  1.0,     0.0,     1.0,     true  },
	// Node Time 1 - Details
	{ "N1TrckSrcId",         "Node Time 1 Tracked Source ID",                            "",  3.0,     0.0,     1.0,     true  },
	{ "N1PBOState",          "Node Time 1 Current Phase Buildout State",                 "",  2.0,     0.0,     1.0,     true  },
	{ "N1PBOOld",            "Node Time 1 Ref Switch Old Source",                        "",  3.0,     0.0,     1.0,     true  },
	{ "N1PBONew",            "Node Time 1 Ref Switch New Source",                        "",  3.0,     0.0,     1.0,     true  },
	// Node Time 1 - Debug
	{ "N1vsCkCohHyInit",     "Node Time 1 Coh Hybrid Init PTP vs Clock Phase Offset",    "s", NoValue, NoValue, NoValue, false },
	{ "N1vsCkCohHyCurr",     "Node Time 1 Coh Hybrid Current PTP vs Clock Phase Offset", "s", NoValue, NoValue, NoValue, false },
	{ "N1CohHyTcks",         "Node Time 1 Coh Hyb Ticks Remaining to Enter",             "",  NoValue, NoValue, NoValue, false },

	// Node Time 2 - Basics
	{ "N2Time",              "Node Time 2 Current Time",                                 "s", NoValue, NoValue, NoValue, false },
	{ "N2SrcId",             "Node Time 2 Source ID",                                    "",  3.0,     0.0,     1.0,     true  },
	{ "N2Hovr",              "Node Time 2 In Holdover",                                  "",  1.0,     0.0,     1.0,     true  },
	// Node Time 2 - Details
	{ "N2TrckSrcId",         "Node Time 2 Tracked Source ID",                            "",  3.0,     0.0,     1.0,     true  },
	{ "N2PBOState",          "Node Time 2 Current Phase Buildout State",                 "",  2.0,     0.0,     1.0,     true  },
	{ "N2PBOOld",            "Node Time 2 Ref Switch Old Source",                        "",  3.0,     0.0,     1.0,     true  },
	{ "N2PBONew",            "Node Time 2 Ref Switch New Source",                        "",  3.0,     0.0,     1.0,     true  },
	// Node Time 2 - Debug
	{ "N2vsCkCohHyInit",     "Node Time 2 Coh Hybrid Init PTP vs Clock Phase Offset",    "s", NoValue, NoValue, NoValue, false },
	{ "N2vsCkCohHyCurr",     "Node Time 2 Coh Hybrid Current PTP vs Clock Phase Offset", "s", NoValue, NoValue, NoValue, false },
	{ "N2CohHyTcks",         "Node Time 2 Coh Hyb Ticks Remaining to Enter",             "",  NoValue, NoValue, NoValue, false },

	// System - Basics
	{ "M1State",             "PTP Master 1 State",        "", NoValue, NoValue, NoValue },
	{ "M2State",             "PTP Master 2 State",        "", NoValue, NoValue, NoValue },
	// System - Debug
	{ "DACEn",               "DAC Control Enabled",       "", NoValue, NoValue, NoValue },
	{ "DACVal",              "DAC Control Current Value", "", NoValue, NoValue, NoValue },
	{ "DACMin",              "DAC Control Minimum",       "", NoValue, NoValue, NoValue },
	{ "DACMax",              "DAC Control Maximum",       "", NoValue, NoValue, NoValue }

};

/* ChartDirector licensing info */
static const char* cdlk = "RDST-25QJ-3LME-NN5H-CBF2-81F3";
static bool cdlkUsed = false;
static inline void InitialiseChartDirector()
{
	if (!cdlkUsed && !Version::DEVELOPMENT)
	{
		Chart::setLicenseCode(cdlk);
		cdlkUsed = true;
	}
}

#if defined(_MSC_VER) && _MSC_VER > 1310
// Visual C++ 2005 and later require the source files in UTF-8, and all strings 
// to be encoded as wchar_t otherwise the strings will be converted into the 
// local multibyte encoding and cause errors. To use a wchar_t as UTF-8, these 
// strings then need to be convert back to UTF-8. This function is just a rough 
// example of how to do this.
# define utf8(str)  ConvertToUTF8(L##str)
const char * ConvertToUTF8(const wchar_t * pStr)
{
	static char szBuf[1024];
	WideCharToMultiByte(CP_UTF8, 0, pStr, -1, szBuf, sizeof(szBuf), NULL, NULL);
	return szBuf;
}
#else
// Visual C++ 2003 and gcc will use the string literals as is, so the files 
// should be saved as UTF-8. gcc requires the files to not have a UTF-8 BOM.
# define utf8(str)  str
#endif

static void RemoveRecentTrace(ttTraceWindow* trace)
{
	for (std::vector<ttTraceWindow*>::iterator i=recentTraces.begin(); i!=recentTraces.end(); ++i)
	{
		if (*i==trace)
		{ // Already in list, so remove from here
			recentTraces.erase(i);
			break;
		}
	}
}

static void AddRecentTrace(ttTraceWindow* trace)
{
	RemoveRecentTrace(trace);
	recentTraces.insert(recentTraces.begin(),trace);
}

static void GetRecentTrace(ttTraceWindow* &trace)
{
	ttTraceWindow* result = NULL;
	for (std::vector<ttTraceWindow*>::iterator i=recentTraces.begin(); i!=recentTraces.end(); ++i)
	{
		if (trace==NULL || *i!=trace)
		{ // Either we're not picky or this is the first trace that isn't the one passed to us
			result = *i;
			break;
		}
	}
	trace = result;
}

/****************
  ttTraceWindow
****************/

const double ttTraceWindow::m_auto_x_min = 0.0;
//const double ttTraceWindow::m_auto_x_max = 0.0;
//const double ttTraceWindow::m_auto_y_min = 0.0;
//const double ttTraceWindow::m_auto_y_max = 0.0;
const long ttTraceWindow::ID_MENU_CONFIGURE = wxNewId();
const long ttTraceWindow::ID_MENU_AUTO      = wxNewId();
const long ttTraceWindow::ID_MENU_LOCKY     = wxNewId();
const long ttTraceWindow::ID_MENU_DERIVE    = wxNewId();
const long ttTraceWindow::ID_MENU_ADOPT     = wxNewId();

BEGIN_EVENT_TABLE(ttTraceWindow, wxWindow)
	EVT_ERASE_BACKGROUND ( ttTraceWindow::OnErase )
	EVT_PAINT            ( ttTraceWindow::OnPaint )
	EVT_SIZE             ( ttTraceWindow::OnSize  )
	EVT_LEFT_DCLICK      ( ttTraceWindow::OnMouse )
	EVT_RIGHT_DOWN       ( ttTraceWindow::OnMouse )
	EVT_MENU             ( wxID_ANY, ttTraceWindow::OnCommand )
END_EVENT_TABLE()

ttTraceWindow::ttTraceWindow(wxWindow* parent, const std::vector<ttParameter>::iterator &parameter)
	: wxWindow( parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SUNKEN|wxFULL_REPAINT_ON_RESIZE, "ttTraceWindow-"+parameter->name),
	m_menu(NULL),
	m_rendered_w(0),
	m_rendered_h(0),
	m_bitmap(NULL),
	m_plotter(NULL),
	m_rendering_thread(NULL),
	m_derived(NULL)
{
	CommonConstructor(parameter->name, parameter->columnOffset, parameter->detailsIndex);
}

ttTraceWindow::ttTraceWindow(wxWindow* parent, const wxString &name, const unsigned int &columnOffset, const int &detailsIndex)
	: wxWindow( parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SUNKEN|wxFULL_REPAINT_ON_RESIZE, "ttTraceWindow-"+name),
	m_menu(NULL),
	m_rendered_w(0),
	m_rendered_h(0),
	m_bitmap(NULL),
	m_plotter(NULL),
	m_rendering_thread(NULL),
	m_derived(NULL)
{
	CommonConstructor(name, columnOffset, detailsIndex);
}

void ttTraceWindow::CommonConstructor(const wxString &name, const unsigned int &columnOffset, const int &detailsIndex)
{
	m_data_initialised = false;
	m_plot_x_initialised = false;
	m_plot_y_initialised = false;
	m_waitingForData = true;
	m_bitmapValid = false;

	m_user_styleMargins = true;
	m_user_x_autoScale = true;
	m_user_x_div_number = 12;
	m_user_x_div_method = ttTrace_Divisions_Auto;
	m_user_x_initialised_extents = false;
	m_user_x_initialised_divs = false;
	m_user_y_autoScale = true;
	m_user_y_div_number = 10;
	m_user_y_div_method = ttTrace_Divisions_Auto;
	m_user_y_align = ttTrace_Align_Auto;
	m_user_y_initialised_extents = false;
	m_user_y_initialised_divs = false;

	// Start out assuming there is no scaling information provided
	m_auto_pointer_x_min = const_cast<double*>(&m_auto_x_min);
	m_auto_pointer_x_max = const_cast<double*>(&m_data_x_max);
	m_auto_pointer_x_div = NULL;
	m_auto_pointer_y_min = const_cast<double*>(&m_data_y_min);
	m_auto_pointer_y_max = const_cast<double*>(&m_data_y_max);
	m_auto_pointer_y_div = NULL;

	m_crop_x_min_index = 0;
	m_crop_x_min_valid = ttTrace_Extent_Lower;
	m_crop_x_max_index = 0;
	m_crop_x_max_valid = ttTrace_Extent_Lower;
	m_crop_y_min_index = 0;
	m_crop_y_min_valid = false;
	m_crop_y_max_index = 0;
	m_crop_y_max_valid = false;

	m_columnOffset = columnOffset;
	if (detailsIndex==-1)
	{ // Make do with what we got from the column
		m_details = NULL;
		m_name = name;
	}
	else
	{ // Use the built-in details we have on the parameter
		m_details = &parameterDetails[detailsIndex];
		m_name = m_details->nameFriendly;
		if (m_details->min!=NoValue) m_auto_pointer_y_min = &m_details->min;
		if (m_details->max!=NoValue) m_auto_pointer_y_max = &m_details->max;
		if (m_details->div!=NoValue) m_auto_pointer_y_div = &m_details->div;
	}

	// Reserve an hour's worth of space in the storage vectors
	m_points_store_x.reserve(3600);
	m_points_store_y.reserve(3600);
	// Reserve a couple of minutes' worth of space in the buffer vectors
	m_points_buffer_x.reserve(120);
	m_points_buffer_y.reserve(120);

	// Inform traces deriving from this column that this trace exists and can be used as a data source
	derivedListeners_mutex.Lock();
	for (std::vector<ttDerivedTraceHost*>::iterator i=derivedListeners.begin(); i!=derivedListeners.end(); ++i)
	{
		if ((*i)->GetColumnOffset()==columnOffset)
		{
			m_derived = (*i);
			m_derived->SetSource(this);
		}
	}
	derivedListeners_mutex.Unlock();
}

ttTraceWindow::~ttTraceWindow()
{
	if (m_rendering_thread!=NULL) m_rendering_thread->Terminate();
	if (m_rendering_thread!=NULL) m_rendering_thread->WaitForTermination(5000);
	PrepareForDestruction();
	Obliterate(m_bitmap)
	Obliterate(m_plotter)
	Obliterate(m_menu);
	if (m_derived!=NULL) m_derived->SourceLost();
}

void ttTraceWindow::PrepareForDestruction()
{ // Disassociate from other items, such that it can be safely destroyed asynchronously
	if (m_columnOffset<parameterListeners.size() && parameterListeners[m_columnOffset]==this) parameterListeners[m_columnOffset] = NULL;
	RemoveRecentTrace(this);
}

unsigned int ttTraceWindow::GetColumnOffset() const
{
	return m_columnOffset;
}

wxString ttTraceWindow::GetName() const
{
	return m_name;
}

wxString ttTraceWindow::GetUnits() const
{
	return m_details==NULL ? wxEmptyString : m_details->unit;
}

void ttTraceWindow::GetCurrentYScale(double* max, double* min, double* div) const
{
	*max = m_plot_y_max;
	*min = m_plot_y_min;
	*div = m_plot_y_div;
}

bool ttTraceWindow::GetUserXAutoScaling() const
{
	return m_user_x_autoScale;
}

double ttTraceWindow::GetUserXMaximum() const
{
	if (m_user_x_initialised_extents)
	{ // Return the user's current setting
		return m_user_x_max;
	}
	else
	{ // Derive a value from what the graph's currently doing
		return ceil(m_plot_x_max); // ceil() it, as in the early stages the max value is the latest data acquisition time, which is too rough
	}
}

double ttTraceWindow::GetUserXMinimum() const
{
	if (m_user_x_initialised_extents)
	{ // Return the user's current setting
		return m_user_x_min;
	}
	else
	{ // Derive a value from what the graph's currently doing
		return m_plot_x_min;
	}
}

ttTrace_Divisions ttTraceWindow::GetUserXDivisions(unsigned short* number, double* value) const
{
	if (m_user_x_initialised_divs)
	{ // Return the user's current setting
		*value = m_user_x_div_value;
	}
	else
	{ // Derive a value from what the graph's currently doing
		*value = m_plot_x_div;
	}
	*number = m_user_x_div_number;
	if (m_user_x_autoScale)
	{ // Return whatever the graph's effectively using (unless user's value is used)
		if (m_auto_pointer_x_div==NULL || m_user_x_initialised_divs)
		{
			return ttTrace_Divisions_Auto;
		}
		else
		{
			return ttTrace_Divisions_Value;
		}
	}
	else
	{ // Return user's choice
		return m_user_x_div_method;
	}
}

bool ttTraceWindow::GetUserYAutoScaling() const
{
	return m_user_y_autoScale;
}

double ttTraceWindow::GetUserYMaximum() const
{
	if (m_user_y_initialised_extents)
	{ // Return the user's current setting
		return m_user_y_max;
	}
	else
	{ // Derive a value from what the graph's currently doing
		return m_plot_y_max;
	}
}

double ttTraceWindow::GetUserYMinimum() const
{
	if (m_user_y_initialised_extents)
	{ // Return the user's current setting
		return m_user_y_min;
	}
	else
	{ // Derive a value from what the graph's currently doing
		return m_plot_y_min;
	}
}

ttTrace_Divisions ttTraceWindow::GetUserYDivisions(unsigned short* number, double* value) const
{
	if (m_user_y_initialised_divs)
	{ // Return the user's current setting
		*value = m_user_y_div_value;
	}
	else
	{ // Derive a value from what the graph's currently doing
		*value = m_plot_y_div;
	}
	*number = m_user_y_div_number;
	if (m_user_y_autoScale)
	{ // Return whatever the graph's effectively using (unless user's value is used)
		if (m_auto_pointer_y_div==NULL || m_user_y_initialised_divs)
		{
			return ttTrace_Divisions_Auto;
		}
		else
		{
			return ttTrace_Divisions_Value;
		}
	}
	else
	{ // Return user's choice
		return m_user_y_div_method;
	}
}

ttTrace_Align ttTraceWindow::GetUserYAlignment() const
{
	return m_user_y_align;
}

bool ttTraceWindow::GetUserMargins() const
{
	return m_user_styleMargins;
}

void ttTraceWindow::SetUserXAutoScaling(const bool &value)
{
	m_user_x_autoScale = value;
	// Switch the extents used by the automatic Y-scaling
	BeginUserYUpdate();
	if (m_details==NULL || m_details->min==NoValue) m_auto_pointer_y_min = const_cast<double*>(value ? &m_data_y_min : &m_crop_y_min_value);
	if (m_details==NULL || m_details->max==NoValue) m_auto_pointer_y_max = const_cast<double*>(value ? &m_data_y_max : &m_crop_y_max_value);
	if (m_user_y_autoScale)
	{ // Invalidate Y-axis. Must be done manually as it won't be done by EndUserYUpdate in this case
		m_plot_y_initialised = false;
	}
	EndUserYUpdate(true);
}

void ttTraceWindow::SetUserXMaximum(const double &value)
{
	if (m_crop_x_max_valid==ttTrace_Extent_Valid)
	{ // See if it needs invalidating
		if (value<m_user_x_max)
		{
			m_crop_x_max_valid = ttTrace_Extent_Lower;
		}
		else if (value>m_crop_x_max_value)
		{
			m_crop_x_max_valid = ttTrace_Extent_Higher;
		}
	}
	m_user_x_max = value;
	m_user_x_initialised_extents = true;
}

void ttTraceWindow::SetUserXMinimum(const double &value)
{
	if (m_crop_x_min_valid==ttTrace_Extent_Valid)
	{ // See if it needs invalidating
		if (value<m_crop_x_min_value)
		{
			m_crop_x_min_valid = ttTrace_Extent_Lower;
		}
		else if (value>m_user_x_min)
		{
			m_crop_x_min_valid = ttTrace_Extent_Higher;
		}
	}
	m_user_x_min = value;
	m_user_x_initialised_extents = true;
}

void ttTraceWindow::SetUserXDivisions(const ttTrace_Divisions &method, const unsigned short &number, const double &value)
{
	switch (method)
	{
		case ttTrace_Divisions_Value:
			m_user_x_div_method = ttTrace_Divisions_Value;
			m_user_x_div_value = value;
			m_user_x_initialised_divs = true;
			break;
		case ttTrace_Divisions_Number:
			m_user_x_div_method = ttTrace_Divisions_Number;
			m_user_x_div_number = number;
			break;
		default:
			m_user_x_div_method = ttTrace_Divisions_Auto;
			break;
	}
}

void ttTraceWindow::BeginUserXUpdate()
{
	m_user_x_mutex.Lock();
}

void ttTraceWindow::EndUserXUpdate(const bool &readonly)
{
	if (!readonly)
	{
		m_plot_x_initialised = false;
		AddRecentTrace(this);
	}
	m_user_x_mutex.Unlock();
}

void ttTraceWindow::SetUserYAutoScaling(const bool &value)
{
	m_user_y_autoScale = value;
}

void ttTraceWindow::SetUserYMaximum(const double &value)
{
	m_user_y_max = value;
	m_user_y_initialised_extents = true;
}

void ttTraceWindow::SetUserYMinimum(const double &value)
{
	m_user_y_min = value;
	m_user_y_initialised_extents = true;
}

void ttTraceWindow::SetUserYDivisions(const ttTrace_Divisions &method, const unsigned short &number, const double &value)
{
	switch (method)
	{
		case ttTrace_Divisions_Value:
			m_user_y_div_method = ttTrace_Divisions_Value;
			m_user_y_div_value = value;
			m_user_y_initialised_divs = true;
			break;
		case ttTrace_Divisions_Number:
			m_user_y_div_method = ttTrace_Divisions_Number;
			m_user_y_div_number = number;
			break;
		default:
			m_user_y_div_method = ttTrace_Divisions_Auto;
			break;
	}
}

void ttTraceWindow::SetUserYAlignment(const ttTrace_Align &value)
{
	switch (value)
	{
		case ttTrace_Align_Max:
			m_user_y_align = ttTrace_Align_Max;
			break;
		case ttTrace_Align_Min:
			m_user_y_align = ttTrace_Align_Min;
			break;
		default:
			m_user_y_align = ttTrace_Align_Auto;
			break;
	}
}

void ttTraceWindow::BeginUserYUpdate()
{
	m_user_y_mutex.Lock();
}

void ttTraceWindow::EndUserYUpdate(const bool &readonly)
{
	if (!readonly)
	{
		m_plot_y_initialised = false;
		AddRecentTrace(this);
	}
	m_user_y_mutex.Unlock();
}

void ttTraceWindow::SetUserMargins(const bool &value)
{
	m_user_styleMargins = value;
}

void ttTraceWindow::OnErase(wxEraseEvent &event)
{
}

void ttTraceWindow::OnPaint(wxPaintEvent &event)
{
	wxPaintDC dc(this);

	dc.SetBackground(*wxWHITE_BRUSH);

	int w,h;
	GetClientSize(&w,&h);

	m_bitmap_mutex.Lock();
	if (m_bitmapValid && m_bitmap)
	{
		wxMemoryDC bdc(*m_bitmap);
		dc.Blit(
			0, 0,                                              // Bitmap's offset from window (if bitmap<window)
			m_bitmap->GetWidth(), m_bitmap->GetHeight(), &bdc, // Bitmap dimensions & DC
			0, 0                                               // Window's offset from bitmap (if window<bitmap)
		);
		bdc.SelectObjectAsSource(wxNullBitmap);
	}
	else
	{
		dc.Clear();
		wxString message = m_waitingForData ? "Reading data..." : (m_points_store_x.size()<2 ? "Insufficient data" : "Rendering...");
		int tw,th;
		dc.GetTextExtent(message,&tw,&th);
		dc.DrawText(
			message,
			(w-tw)/2,
			(h-th)/2
		);
	}
	m_bitmap_mutex.Unlock();
}

void ttTraceWindow::OnSize(wxSizeEvent &event)
{
	if (m_bitmapValid && (m_rendered_w!=event.GetSize().x || m_rendered_h!=event.GetSize().y)) 
	{ // Invalidate the bitmap
		m_bitmapValid = false;
		Render(true);
	}
}

void ttTraceWindow::OnMouse(wxMouseEvent &event)
{
	if (event.LeftDClick())
	{

		ttTraceScalingDialog* dialog = new ttTraceScalingDialog(this);
		dialog->ShowModal();
		dialog->Destroy();

	}
	else
	{

		Obliterate(m_menu);

		m_menu = new wxMenu();

		m_menu->Append(ID_MENU_CONFIGURE,"Configure Scaling...");
		SetMenuDefaultItem(GetHmenuOf(m_menu),ID_MENU_CONFIGURE,FALSE);
		if (!m_user_x_autoScale || !m_user_y_autoScale)
		{
			m_menu->Append(ID_MENU_AUTO,"Scale Automatically");
		}
		if (m_user_y_autoScale)
		{
			m_menu->Append(ID_MENU_LOCKY,"Lock Y-axis");
		}

		if (traces.size()>1)
		{
			wxMenu* graphs = new wxMenu();
			unsigned int columnOffset;
			for (std::vector<ttParameter>::iterator trace=parameters.begin(); trace!=parameters.end(); ++trace)
			{
				columnOffset = trace->columnOffset;
				if (columnOffset!=m_columnOffset && columnOffset<parameterListeners.size() && parameterListeners[columnOffset]!=NULL)
				{
					graphs->Append(
						ID_MENU_ADOPT+columnOffset,
						parameterListeners[columnOffset]->GetName()
					);
				}
			}

			if (traces.size()>2)
			{
				ttTraceWindow* recent = this;
				GetRecentTrace(recent);
				if (recent!=NULL)
				{
					graphs->PrependSeparator();
					graphs->Prepend(ID_MENU_ADOPT+recent->GetColumnOffset(), recent->GetName());
				}
			}

			m_menu->Append(wxID_ANY,"Adopt Scaling from",graphs);
		}

		m_menu->Append(ID_MENU_DERIVE,"Calculate MTIE && TDEV");

		PopupMenu(m_menu);

	}
}

void ttTraceWindow::OnCommand(wxCommandEvent &event)
{
	int command = event.GetId();

	if (command==ID_MENU_CONFIGURE)
	{ // Open the scaling dialog
		ttTraceScalingDialog* dialog = new ttTraceScalingDialog(this);
		dialog->ShowModal();
		dialog->Destroy();
	}

	else if (command==ID_MENU_AUTO)
	{ // Automatically scale the graph
		if (!m_user_y_autoScale)
		{
			BeginUserYUpdate();
			SetUserYAutoScaling(true);
			EndUserYUpdate();
		}
		if (!m_user_x_autoScale)
		{
			BeginUserXUpdate();
			SetUserXAutoScaling(true);
			EndUserXUpdate();
		}
		Render(true);
	}

	else if (command==ID_MENU_LOCKY)
	{ // Lock the Y-axis (set its manual extents to the current automatic ones)
		if (m_user_y_autoScale)
		{
			BeginUserYUpdate();
			SetUserYMaximum(m_plot_y_max);
			SetUserYMinimum(m_plot_y_min);
			SetUserYDivisions(ttTrace_Divisions_Value, m_user_y_div_number, m_plot_y_div);
			SetUserYAlignment(ttTrace_Align_Auto);
			SetUserYAutoScaling(false);
			EndUserYUpdate();
		}
		// No need to re-render, as there should be no visual change
	}

	else if (command>=ID_MENU_ADOPT)
	{ // Adopt extents from another graph
		unsigned int columnOffset = command-ID_MENU_ADOPT;
		if (columnOffset==m_columnOffset || columnOffset>=parameterListeners.size()) return;

		ttTraceWindow* remote = parameterListeners[columnOffset];
		if (remote!=NULL)
		{
			double min,max,divValue;
			unsigned short divNumber;
			ttTrace_Divisions divMethod;

			BeginUserXUpdate();
			remote->BeginUserXUpdate();
			if (remote->GetUserXAutoScaling())
			{
				remote->EndUserXUpdate(true);
				SetUserXAutoScaling(true);
			}
			else
			{
				max = remote->GetUserXMaximum();
				min = remote->GetUserXMinimum();
				divMethod = remote->GetUserXDivisions(&divNumber,&divValue);
				remote->EndUserXUpdate(true);
				SetUserXMaximum(max);
				SetUserXMinimum(min);
				SetUserXDivisions(divMethod,divNumber,divValue);
				SetUserXAutoScaling(false);
			}
			EndUserXUpdate();

			BeginUserYUpdate();
			remote->BeginUserYUpdate();
			SetUserMargins(remote->GetUserMargins());
			if (remote->GetUserYAutoScaling())
			{
				remote->GetCurrentYScale(&max,&min,&divValue);
				remote->EndUserYUpdate(true);
				SetUserYMaximum(max);
				SetUserYMinimum(min);
				SetUserYDivisions(ttTrace_Divisions_Value,m_user_y_div_number,divValue);
			}
			else
			{
				ttTrace_Align alignment = remote->GetUserYAlignment();
				max = remote->GetUserYMaximum();
				min = remote->GetUserYMinimum();
				divMethod = remote->GetUserYDivisions(&divNumber,&divValue);
				remote->EndUserYUpdate(true);
				SetUserYMaximum(max);
				SetUserYMinimum(min);
				SetUserYDivisions(divMethod,divNumber,divValue);
				SetUserYAlignment(alignment);
			}
			SetUserYAutoScaling(false);
			EndUserYUpdate();

			Render(true);
		}
	}

	else if (command==ID_MENU_DERIVE)
	{ // Calculate MTIE & TDEV
		if (m_derived==NULL)
		{
			m_derived = new ttDerivedTraceHost(ToPTraceFrame::GetInstance(),this,"MTIE & TDEV");
			m_derived->Show();
		}
		else
		{ // Show & refresh existing graphs
			m_derived->Raise();
			m_derived->RefreshGraphs();
		}
	}
}

void ttTraceWindow::Render(const bool &force)
{
	if (m_waitingForData) return;

	if (m_rendering_thread!=NULL)
	{ // Tell existing thread to do it again, if necessary
		if (force) m_rendering_rerender = true;
	}
	else
	{ // Spawn a new thread to render
		#ifdef __WXDEBUG__
			m_rendering_thread = new ttTraceThread(m_name,this);
		#else
			m_rendering_thread = new ttTraceThread(this);
		#endif
		m_rendering_thread->Run();
	}
}

void ttTraceWindow::DoRender()
{
	if (m_rendering_thread==NULL || GetCurrentThreadId()!=m_rendering_thread->GetId()) return;
	ttThread* thisThread = m_rendering_thread;
	m_rendering_thread->EnterWorkingZone();

	int w,h;
	bool recreateGraph;
	bool newData;
	bool newIncluded;

	for (;;)
	{

		recreateGraph = false;
		newData = false;
		newIncluded = false;

		// Last point at which this routine will produce a quaranteed valid image
		// Reset the flag so if it's set by the end we know we legitimately should rerender the graph
		m_rendering_rerender = false;

		GetClientSize(&w,&h);
		// Prevent invalid bitmap & image errors
		if (w==0) w = 1;
		if (h==0) h = 1;
		if (!m_bitmapValid)
		{ // Recreate graph if physical size has changed
			recreateGraph = true;
			m_rendered_w = w;
			m_rendered_h = h;
		}

		unsigned long vectorStart_cropped = 0;
		unsigned long vectorCount_cropped = m_points_store_x.size();
		unsigned long vectorStart_new = m_points_store_x.size()-1; // So it picks the point before the newest, to create a continuous line
		unsigned long vectorCount_new = m_points_buffer_x.size()+1; // So it draw all new points plus the repeated one at the start

		m_points_store_mutex.Lock();
		m_points_buffer_mutex.Lock();

		if (!m_points_buffer_x.empty())
		{ // Prepare 'new' and main vectors
			unsigned long currentCapacity = m_points_store_x.capacity();
			if (m_points_store_x.size()+m_points_buffer_x.size() > currentCapacity)
			{ // Re-allocate main vectors
				m_points_store_x.reserve(currentCapacity*2);
				m_points_store_y.reserve(currentCapacity*2);
			}
			// Copy contents of 'new' into main
			m_points_store_x.insert(m_points_store_x.end(), m_points_buffer_x.begin(), m_points_buffer_x.end());
			m_points_store_y.insert(m_points_store_y.end(), m_points_buffer_y.begin(), m_points_buffer_y.end());
			m_points_buffer_x.clear();
			m_points_buffer_y.clear();
			vectorCount_cropped = m_points_store_x.size();
			newData = true;
		}

		m_points_buffer_mutex.Unlock();

		if (m_points_store_x.size()<2)
		{ // Can't plot one point - it creates a problem
			m_points_store_mutex.Unlock();
			m_rendering_thread = NULL; // Disassociate so it thinks the thread's gone
			return;
		}

		// Calculate scales
		if (CalculateScaleX(&newIncluded,&vectorStart_cropped,&vectorCount_cropped,&vectorStart_new,&vectorCount_new)) recreateGraph = true;
		if (CalculateScaleY()) recreateGraph = true;

		if (recreateGraph)
		{ // Update graph from scratch
			Obliterate(m_plotter)
		}

		if (!recreateGraph && !(newData && newIncluded) && !m_rendering_rerender)
		{ // Nothing new to plot
			m_points_store_mutex.Unlock();
			m_rendering_thread = NULL; // Disassociate so it thinks the thread's gone
			m_bitmapValid = true;
			Refresh();
			break;
		}
		
		if (m_plotter==NULL)
		{ // Create plotter

			InitialiseChartDirector();
			m_plotter = new XYChart(w,h);
			m_plotter->setPlotArea(5,20,w-18,h-25);
			m_plotter->setClipping();
			m_plotter->addTitle(m_name.c_str(),"tahomabd.ttf",10);

			LineLayer* line = m_plotter->addLineLayer(
				DoubleArray((double*)&m_points_store_y[vectorStart_cropped],vectorCount_cropped)
			);
			line->setXData(
				DoubleArray((double*)&m_points_store_x[vectorStart_cropped],vectorCount_cropped)
			);
			m_points_store_mutex.Unlock();
			if (m_details!=NULL && m_details->scatter)
			{
				line->setLineWidth(0);
				line->getDataSet(0)->setDataSymbol(Chart::CircleShape,2,0xff0000,0xff0000);
			}
			else
			{
				line->setLineWidth(1);
			}
		
			m_plotter->yAxis()->setWidth(0);
			m_plotter->yAxis()->setLinearScale(
				m_plot_y_styled_min,
				m_plot_y_styled_max,
				NoValue
			);
			m_plotter->yAxis()->setLabelFormat("");
			Mark** yMarks = new Mark*[m_plot_y_axisLabels.size()];
			for (int i=0; i<m_plot_y_axisLabels.size(); ++i)
			{
				yMarks[i] = m_plotter->yAxis()->addMark(
					m_plot_y_axisLabelPoints[i],
					0x000000,
					m_plot_y_axisLabels[i].c_str(),
					i==m_plot_y_baseTick ? "tahomabd.ttf" : "tahoma.ttf"
				);
				yMarks[i]->setDrawOnTop(false);
				if (i!=m_plot_y_baseTick) yMarks[i]->setMarkColor(Chart::metalColor(0xcccccc,45),0x000000,0x000000);
			}
			if (!m_plot_axisLabel.empty())
			{
				m_plotter->yAxis()->setTitle(m_plot_axisLabel.c_str(),"tahomabd.ttf",8);
				m_plotter->yAxis()->setTitlePos(Chart::Top,-5);
			}

			m_plotter->xAxis()->setWidth(0);
			Mark** xMarks = NULL;
			if (m_plot_x_axisLabels.empty())
			{ // Use automatic X-ticking
				m_plotter->xAxis()->setLinearScale(
					m_plot_x_min,
					m_plot_x_max,
					m_plot_x_div
				);
				wxString format;
				if (m_plot_x_max>=86400.0)
				{ // Days & hours
					format = "{={value|d}-1}d {={value}%86400/3600}h";
				}
				else if (m_plot_x_max>=3600.0)
				{ // Hours & minutes
					format = "{value|h'h'nn}";
				}
				else
				{ // Minutes & seconds
					format = "{value|n:ss}";
				}
				m_plotter->xAxis()->setLabelFormat(format);
			}
			else
			{ // Use the X-ticking we defined ourselves
				m_plotter->xAxis()->setLinearScale(
					m_plot_x_min,
					m_plot_x_max,
					NoValue
				);
				m_plotter->xAxis()->setLabelFormat("");
				xMarks = new Mark*[m_plot_x_axisLabels.size()];
				for (int i=0; i<m_plot_x_axisLabels.size(); ++i)
				{
					xMarks[i] = m_plotter->xAxis()->addMark(
						m_plot_x_axisLabelPoints[i],
						0x000000,
						m_plot_x_axisLabels[i].c_str(),
						"tahoma.ttf"
					);
					xMarks[i]->setDrawOnTop(false);
					xMarks[i]->setMarkColor(Chart::metalColor(0xcccccc,45),0x000000,0x000000);
				}
			}

			m_plotter->packPlotArea(5,20,w-18,h);
			// Decimate if text is too dense
			{
				double tickSpacing = m_plotter->getPlotArea()->getHeight() / double(m_plot_y_axisLabels.size()); // The spacing
				int tickDecimation = (tickSpacing<10.0) ? (int)floor(10.0/tickSpacing)+1 : 1; // How many ticks should be represented by 1, i.e. 'show every [tickDecimation] ticks'
				int tickModulus = (m_plot_y_baseTick==-1) ? 0 : (m_plot_y_baseTick % tickDecimation); // Which of the [tickDecimation] ticks should be shown, i.e. 'show every [tickModulus]th out of [tickDecimation] ticks'
				for (int i=0; i<m_plot_y_axisLabels.size(); ++i)
				{
					if ((i % tickDecimation)!=tickModulus) yMarks[i]->setMarkColor(Chart::metalColor(0xcccccc,45),Transparent,0x000000);
				}
				delete[] yMarks;
			}
			if (xMarks!=NULL)
			{
				double tickSpacing = m_plotter->getPlotArea()->getWidth() / double(m_plot_x_axisLabels.size()); // The spacing
				int tickDecimation = (tickSpacing<35.0) ? (int)floor(35.0/tickSpacing)+1 : 1; // How many ticks should be represented by 1, i.e. 'show every [tickDecimation] ticks'
				for (int i=0; i<m_plot_x_axisLabels.size(); ++i)
				{
					if ((i % tickDecimation)!=0) xMarks[i]->setMarkColor(Chart::metalColor(0xcccccc,45),Transparent,0x000000);
				}
				delete[] xMarks;
			}


			m_plotter->getPlotArea()->setGridColor(Transparent,Chart::metalColor(0xcccccc,45));

		}
		else
		{ // Add to existing graph

			// Create the replacement plotter
			InitialiseChartDirector();
			XYChart* plotter = new XYChart(w,h,0xffffff,Transparent);
			plotter->setPlotArea(
				m_plotter->getPlotArea()->getLeftX(),
				m_plotter->getPlotArea()->getTopY(),
				m_plotter->getPlotArea()->getWidth(),
				m_plotter->getPlotArea()->getHeight()
			);
			plotter->setClipping();
			if (m_plot_x_axisLabels.empty())
			{ // Use automatic X-ticking
				plotter->xAxis()->setLinearScale(
					m_plot_x_min,
					m_plot_x_max,
					m_plot_x_div
				);
			}
			else
			{ // Use the X-ticking we defined ourselves
				plotter->xAxis()->setLinearScale(
					m_plot_x_min,
					m_plot_x_max,
					NoValue
				);
			}
			plotter->yAxis()->setLinearScale(
				m_plot_y_styled_min,
				m_plot_y_styled_max,
				NoValue
			);

			// Hide as much as possible, so it's just the data being drawn
			plotter->xAxis()->setLabelFormat("");
			plotter->xAxis()->setWidth(0);
			plotter->yAxis()->setLabelFormat("");
			plotter->yAxis()->setWidth(0);
			plotter->getPlotArea()->setBackground(Transparent,Transparent,Transparent);

			// Import the previous plotter's... plot as a background
			plotter->getDrawArea()->merge(m_plotter->getDrawArea(),0,0,TopLeft,0);

			LineLayer* line = plotter->addLineLayer(
				DoubleArray((double*)&m_points_store_y[vectorStart_new],vectorCount_new)
			);
			line->setXData(
				DoubleArray((double*)&m_points_store_x[vectorStart_new],vectorCount_new)
			);
			m_points_store_mutex.Unlock();
			if (m_details!=NULL && m_details->scatter)
			{
				line->setLineWidth(0);
				line->getDataSet(0)->setDataSymbol(Chart::CircleShape,2,0xff0000,0xff0000);
			}
			else
			{
				line->setLineWidth(1);
			}

			// Swap around the plotters
			Obliterate(m_plotter)
			m_plotter = plotter;

		}

		MemBlock inMemory = m_plotter->makeChart(BMP);

		wxMemoryInputStream stream(inMemory.data,inMemory.len);
		wxImage img(stream,wxBITMAP_TYPE_BMP);
		wxBitmap* newBitmap = new wxBitmap(img);
		m_bitmap_mutex.Lock();
		if (m_bitmap) delete m_bitmap;
		m_bitmap = newBitmap;
		m_bitmap_mutex.Unlock();

		if (!m_rendering_rerender)
		{ // Not been asked to render it again in the mean time
			m_rendering_thread = NULL; // Disassociate so it thinks the thread's gone
			m_bitmapValid = true;
			Refresh();
			break;
		}
		else
		{
			int erm=0;
		}
		// Otherwise we start again as during the previous routine we were asked to render again
	}

	thisThread->LeaveWorkingZone();
}

void ttTraceWindow::WriteToBuffer(const double &x, const double &y)
{
	m_points_buffer_mutex.Lock();
	StoreDataExtremities(x,y);
	m_points_buffer_x.push_back(x);
	m_points_buffer_y.push_back(y);
	m_points_buffer_mutex.Unlock();
}

void ttTraceWindow::WriteToStore(const double &x, const double &y)
{
	m_points_store_mutex.Lock();
	StoreDataExtremities(x,y);
	m_points_store_x.push_back(x);
	m_points_store_y.push_back(y);
	m_points_store_mutex.Unlock();
}

void ttTraceWindow::StoreDataExtremities(const double &x, const double &y)
{
	if (m_data_initialised)
	{
		if (x>m_data_x_max)
		{
			m_data_x_max = x;
		}
		else if (x<m_data_x_min)
		{
			m_data_x_min = x;
		}
		if (y>m_data_y_max)
		{
			m_data_y_max = y;
			m_data_y_invalidated = true;
		}
		else if (y<m_data_y_min)
		{
			m_data_y_min = y;
			m_data_y_invalidated = true;
		}
	}
	else
	{ // Store no matter what
		m_data_x_max = m_data_x_min = x;
		m_data_y_max = m_data_y_min = y;
		m_data_y_invalidated = true;
		// Also initialise the plotting range
		m_plot_x_min = floor(x);
		m_plot_x_max = x + 10.0;
		m_plot_y_max = m_plot_y_min = y;
		m_data_initialised = true;
	}
}

bool ttTraceWindow::CalculateScaleX(bool* newIncluded, unsigned long* all_start, unsigned long* all_count, unsigned long* new_start, unsigned long* new_count)
{
	wxMutexLocker userMutex(m_user_x_mutex);

	if (m_user_x_autoScale && ToPTraceFrame::GetInstance()->IsLogging() && *m_auto_pointer_x_max>m_plot_x_max)
	{ // We're plotting automatically and the data range changed, so need to rescale
		m_plot_x_initialised = false;
	}

	if (m_plot_x_initialised)
	{ // Axis is fine

		if (m_user_x_autoScale)
		{
			*newIncluded = true; // Ensure new points are plotted
		}
		else if (m_crop_x_min_valid==ttTrace_Extent_Valid && m_crop_x_max_valid==ttTrace_Extent_Valid)
		{ // Cropping bounds are set and being used, so see if the new data falls within them
			double n_min_value = m_points_store_x[*new_start];
			double n_max_value = m_points_store_x[m_points_store_x.size()-1];
			if (*new_count==0 || n_min_value>m_user_x_max || n_max_value<m_user_x_min)
			{ // No new data to analyse or it's out of our range, so just return the current extents
				*newIncluded = false;
			}
			else
			{ // Will need to analyse new data
				unsigned long n_first_index = *new_start;
				if (n_min_value<m_user_x_min)
				{ // New data enters our range from the bottom - find the first valid point
					for (std::vector<double>::iterator i=m_points_store_x.begin()+n_first_index; i!=m_points_store_x.end() && *i<m_user_x_min; ++i)
					{
						++n_first_index;
					}
					if (n_first_index!=0) --n_first_index;
					// We consequently now have an index for cropping
					m_crop_x_min_index = n_first_index;
					m_crop_x_min_value = m_points_store_x[m_crop_x_min_index];
					m_crop_x_min_valid = ttTrace_Extent_Valid;
				}
				// Look for last valid point
				unsigned long n_last_index = n_first_index;
				unsigned long y_min_index = n_first_index;
				double        y_min_value = m_points_store_y[y_min_index];
				unsigned long y_max_index = n_first_index;
				double        y_max_value = y_min_value;
				double        y;
				for (std::vector<double>::iterator i=m_points_store_x.begin()+n_first_index; i!=m_points_store_x.end() && *i<=m_user_x_max; ++i)
				{
					y = m_points_store_y[n_last_index];
					if (y>y_max_value)
					{
						y_max_index = n_last_index;
						y_max_value = y;
					}
					else if (y<y_min_value)
					{
						y_min_index = n_last_index;
						y_min_value = y;
					}
					++n_last_index;
				}
				if (n_last_index==m_points_store_x.size()) --n_last_index;
				m_crop_x_max_index = n_last_index;
				m_crop_x_max_value = m_points_store_x[m_crop_x_max_index];
				m_crop_x_max_valid = ttTrace_Extent_Valid;
				if (!m_crop_y_min_valid || y_min_value<m_crop_y_min_value)
				{
					m_crop_y_min_value = y_min_value;
					m_crop_y_min_index = y_min_index;
				}
				if (!m_crop_y_max_valid || y_max_value>m_crop_y_max_value)
				{
					m_crop_y_max_value = y_max_value;
					m_crop_y_max_index = y_max_index;
				}
				*new_start = n_first_index;
				*new_count = n_last_index-n_first_index + 1;
				*newIncluded = true;
			}
			*all_start = m_crop_x_min_index;
			*all_count = m_crop_x_max_index-m_crop_x_min_index + 1;
		}

		return false; // Axis was not rescaled
	}

	else
	{ // Axis needs to be recalculated

		if (m_user_x_autoScale)
		{ // Scaling automatically

			// New data, if there is any, will fall within our range
			*newIncluded = true;

			/*if (m_auto_pointer_x_div==NULL)
			{ // No ideal division has been provided*/
				CalculateScaleX(*m_auto_pointer_x_min,*m_auto_pointer_x_max);
			/*}
			else
			{ // An ideal division has been provided
				CalculateScaleX(*m_auto_pointer_x_min,*m_auto_pointer_x_max,*m_auto_pointer_x_div);
			}*/

		}
		else
		{ // User-defined

			if (m_crop_x_min_valid!=ttTrace_Extent_Valid || m_crop_x_max_valid!=ttTrace_Extent_Valid)
			{ // One or both cropping bounds have been invalidated, so re-analyse the range
				bool rescanForY = (!m_crop_y_min_valid || !m_crop_y_max_valid);

				if (m_crop_x_min_valid!=ttTrace_Extent_Valid)
				{ // Look for new minimum x-point
					if (m_crop_x_min_valid==ttTrace_Extent_Lower)
					{ // New x-min will be below existing one
						m_crop_x_min_index = 0; // Begin scanning upwards from the start
						rescanForY = true; // The range will have increased, so look for Y-extents
					} // Otherwise we will scan from the existing point, and we don't yet know if we should look for Y

					for (std::vector<double>::iterator i=m_points_store_x.begin()+m_crop_x_min_index; i!=m_points_store_x.end() && *i<m_user_x_min; ++i)
					{
						++m_crop_x_min_index;
					}
					if (m_crop_x_min_index!=0) --m_crop_x_min_index;

					if (m_crop_x_min_index>m_crop_y_min_index || m_crop_x_min_index>m_crop_y_max_index)
					{ // We've lost one or both of the Y-extents
						rescanForY = true;
					}

					m_crop_x_min_value = m_points_store_x[m_crop_x_min_index];
					m_crop_x_min_valid = ttTrace_Extent_Valid;
				}

				if (m_crop_x_max_valid!=ttTrace_Extent_Valid || rescanForY)
				{ // Look for new maximum X-point and/or scan for Y-extents
					if (m_crop_x_max_valid==ttTrace_Extent_Lower || rescanForY)
					{ // New x-max will be below existing one, or we need to rescan the entire range
						m_crop_x_max_index = m_crop_x_min_index; // Begin scanning upwards from the start of the range
						rescanForY = true; // We may lose the Y-extents by shortening the range
					} // Otherwise we will scan from the existing point
					
					double y;
					if (rescanForY)
					{ // Invalidate all Y-extents, starting the search from scratch
						m_crop_y_min_index = m_crop_x_min_index;
						m_crop_y_min_value = m_points_store_y[m_crop_y_min_index];
						m_crop_y_max_index = m_crop_x_min_index;
						m_crop_y_max_value = m_points_store_y[m_crop_y_max_index];
					}
					for (std::vector<double>::iterator i=m_points_store_x.begin()+m_crop_x_max_index; i!=m_points_store_x.end() && *i<=m_user_x_max; ++i)
					{
						y = m_points_store_y[m_crop_x_max_index];
						if (y>m_crop_y_max_value)
						{
							m_crop_y_max_index = m_crop_x_max_index;
							m_crop_y_max_value = y;
						}
						else if (y<m_crop_y_min_value)
						{
							m_crop_y_min_index = m_crop_x_max_index;
							m_crop_y_min_value = y;
						}
						++m_crop_x_max_index;
					}
					if (m_crop_x_max_index==m_points_store_x.size()) --m_crop_x_max_index;
					
					if (rescanForY)
					{
						m_crop_y_min_valid = true;
						m_crop_y_max_valid = true;
					}
					if (m_crop_x_max_valid!=ttTrace_Extent_Valid)
					{
						m_crop_x_max_value = m_points_store_x[m_crop_x_max_index];
						m_crop_x_max_valid = ttTrace_Extent_Valid;
					}
				}
			}
			
			*all_start = m_crop_x_min_index;
			*all_count = m_crop_x_max_index-m_crop_x_min_index + 1;

			switch (m_user_x_div_method)
			{
				case ttTrace_Divisions_Number: // Divisions specified by number
					CalculateScaleX(m_user_x_min,m_user_x_max,m_user_x_div_number);
					break;
				case ttTrace_Divisions_Value: // Divisions specified exactly
					CalculateScaleX(m_user_x_min,m_user_x_max,m_user_x_div_value);
					break;
				default: // Divisions not specified
					CalculateScaleX(m_user_x_min,m_user_x_max);
					break;
			}

		}

		m_plot_x_initialised = true;
		return true; // Axis was rescaled

	}
}

/* Automatically calculated divisions:

   Determine the magnitude (seconds, minutes, hours, days), then apply these
   limits to the value in those terms.

            ||     Minimum    ||     Maximum    ||
   divFinal || Number | Range || Number | Range ||
   ===============================================
       1    ||      6 |    6  ||     12 |   12  || => split at 12
       2    ||      6 |   12  ||     12 |   24  || => split at 24
       4    ||      6 |   24  ||     10 |   40  || => split at 40
       5    ||      8 |   40  ||     12 |   60  || => split at 60
      10    ||      6 |   60  ||     12 |  120  || => split at 120
      20    ||      6 |  120  ||     12 |  240  || => split at 210
      30    ||      6 |  180  ||     12 |  360  || => split at 360 (actually done earlier by detecting it's a higher magnitude)
   [next magnitude]
*/
void ttTraceWindow::CalculateScaleX(double min, double max)
{
	double range = max-min;
	double div;
	double rangeScaled;

	if (range>6.0)
	{ // Seconds and greater
		double factor;

		if (range > 864000) // 9.6 * 20 hours OR 8 * 1 day
		{ // Day scaling
			factor = 86400.0;
		}
		else if (range > 21600.0) // 12 * 30 minutes OR 6 * 1 hour
		{ // Hour scaling
			factor = 3600.0;
		}
		else if (range > 360.0) // 12 * 30 seconds OR 6 * 1 minute
		{ // Minute scaling
			factor = 60.0;
		}
		else
		{ // Second scaling
			factor = 1.0;
		}
		rangeScaled = range / factor;

		if (rangeScaled < 12.0)
		{
			div = 1.0;
		}
		else if (rangeScaled < 24.0)
		{
			div = 2.0;
		}
		else if (rangeScaled < 40.0)
		{
			div = 4.0;
		}
		else if (rangeScaled < 60.0)
		{
			div = 5.0;
		}
		else if (rangeScaled < 120.0)
		{
			div = 10.0;
		}
		else if (rangeScaled < 210.0)
		{
			div = 20.0;
		}
		else // if (range Scaled <= 360.0)
		{
			div = 30.0;
		}
		div *= factor;
	}

	else
	{ // Sub-second resolution
		double rangeMagnitude = floor( log10(abs( range )) );
		rangeScaled = range / pow(10.0, rangeMagnitude);
		if (rangeScaled < 1.4)
		{
			div = 0.1;
		}
		else if (rangeScaled < 2.2)
		{
			div = 0.2;
		}
		else if (rangeScaled < 3.125)
		{
			div = 0.25;
		}
		else if (rangeScaled < 4.4)
		{
			div = 0.4;
		}
		else if (rangeScaled < 7.0)
		{
			div = 0.5;
		}
		else // if (rangeScaled <= 10.0)
		{
			div = 1.0;
		}
		div *= pow(10.0,rangeMagnitude);
	}

	CalculateScaleX(min,max,div);
}

void ttTraceWindow::CalculateScaleX(double min, double max, unsigned short divs)
{
	if (divs>255) divs = 255;

	double range = max-min;
	double divFinal = range / double(divs);

	CalculateScaleX(min,max,divFinal);
}

void ttTraceWindow::CalculateScaleX(double min, double max, double div)
{
	short magnitudePosition;
	{
		short upper = GetTimeMagnitude(max);
		short lower = GetTimeMagnitude(min);
		magnitudePosition = wxMax(upper,lower);
	}
	short magnitudeMovement = GetTimeMagnitude(div);

	if
	(
		EffectivelyEqual(div,round(div),9)
		&& (unsigned long)div > 0
		&& ( (unsigned long)min % (unsigned long)div ) == 0
		&& (magnitudePosition-magnitudeMovement) < 2
	)
	{ // Divisions line up nicely with the minimum value, so use ChartDirector's own ticking
		m_plot_x_axisLabels.clear();
		m_plot_x_axisLabelPoints.clear();
		m_plot_x_min = min;
		if (m_user_x_autoScale)
		{
			m_plot_x_max = ceil(*m_auto_pointer_x_max / div) * div;
		}
		else
		{
			m_plot_x_max = max;
		}
		m_plot_x_div = div;
	}
	else
	{ // Divisions don't line up nicely with the minimum value, so generate the ticks manually

		double range = max-min;
		double bottomTick;
		double topTick;
		unsigned int numberOfTicks;

		if (div>range)
		{ // Special case: division won't fit in range, so tick min and max only
			bottomTick = min;
			topTick = max;
			numberOfTicks = 2;
		
			m_plot_x_min = min;
			m_plot_x_max = max;
			m_plot_x_div = m_plot_x_max - m_plot_x_min;
		}

		else
		{ // Determine ticks
			bottomTick = min;
			topTick = ( floor(range / div) * div ) + bottomTick;

			m_plot_x_div = div;
			m_plot_x_min = min;
			m_plot_x_max = max;

			numberOfTicks = (unsigned int)round((topTick-bottomTick) / div) + 1;

			if (numberOfTicks>256)
			{ // Need to rescale div width to allow for only 256 ticks (255 divs)
				numberOfTicks = 256;
				m_plot_x_div = (m_plot_x_max-m_plot_x_min) / 255.0;
			}
		}

		{ // Determine magnitudes of position & movement
			short upper = GetTimeMagnitude(m_plot_x_max);
			short lower = GetTimeMagnitude(m_plot_x_min);
			magnitudePosition = wxMax(upper,lower);

			magnitudeMovement = GetTimeMagnitude(m_plot_x_div);
		}
	
		{ // Generate ticks
			double labelValue;
			int tickIndex = 0;

			m_plot_x_axisLabels.resize(numberOfTicks);
			m_plot_x_axisLabelPoints.resize(numberOfTicks);

			if ((magnitudePosition-magnitudeMovement) > 1)
			{ // Option 3 if we lose detail in the position by representing movement accurately

				for (std::vector<wxString>::iterator i=m_plot_x_axisLabels.begin(); i!=m_plot_x_axisLabels.end(); ++i, ++tickIndex)
				{
					m_plot_x_axisLabelPoints[tickIndex] = bottomTick + double(tickIndex)*m_plot_x_div;
					// Label value is relative to the baseline (an addition or subtraction)
					if (tickIndex==0)
					{ // It is the baseline value, so print that
						*i = "<*font=tahomabd.ttf*>" + FormatTime(m_plot_x_axisLabelPoints[tickIndex]);
					}
					else
					{ // Addition to baseline value, so must be prepended with a plus sign
						labelValue = double(tickIndex) * m_plot_x_div;
						*i = "+" + FormatTime(labelValue,magnitudeMovement);
					}
				}

			}

			else
			{ // Option 1 or 2

				for (std::vector<wxString>::iterator i=m_plot_x_axisLabels.begin(); i!=m_plot_x_axisLabels.end(); ++i, ++tickIndex)
				{
					labelValue = bottomTick + (double)(tickIndex)*m_plot_x_div;
					m_plot_x_axisLabelPoints[tickIndex] = labelValue;
					*i = FormatTime(labelValue);
				}

			} // End modes 1 & 2

		} // End of tick generation

	} // End of entire block
}

bool ttTraceWindow::CalculateScaleY()
{
	wxMutexLocker userMutex(m_user_y_mutex);

	if (m_user_y_autoScale && ToPTraceFrame::GetInstance()->IsLogging() && m_data_y_invalidated && (*m_auto_pointer_y_max>m_plot_y_max || *m_auto_pointer_y_min<m_plot_y_min))
	{ // We're plotting automatically and the data range changed, so need to rescale
		m_plot_y_initialised = false;
	}

	if (!m_plot_y_initialised)
	{

		if (m_user_y_autoScale)
		{ // Scaling automatically

			if (*m_auto_pointer_y_min==*m_auto_pointer_y_max)
			{ // Range has not yet been defined
				if (*m_auto_pointer_y_min==0.0)
				{ // Range from -5 to +5
					CalculateScaleY(-5.0, 5.0, 1.0);
				}
				else
				{ // Create a range based on the magnitude & precision
					long tempValue;
					double magnitude = floor( log10(abs( *m_auto_pointer_y_min )) );
					for (unsigned int i=4; i>1; --i) // 4,3,2
					{ // Hunt for the best magnitude to represent the number without losing too much precision
						tempValue = long(round( *m_auto_pointer_y_min / pow(10.0,magnitude-i) ));
						if ((tempValue % 10) != 0)
						{ // There's a digit we'd lose if we chopped here, so set this as the minimum magnitude
							magnitude -= i; // Adjust it
							break;
						}
					}
					double div = pow(10.0, magnitude);
					CalculateScaleY(*m_auto_pointer_y_min-5.0*div, *m_auto_pointer_y_min+5.0*div, div);
				}
			}
			else
			{ // Range exists, so use it
				if (m_auto_pointer_y_div==NULL)
				{ // No ideal division has been provided
					CalculateScaleY(*m_auto_pointer_y_min,*m_auto_pointer_y_max);
				}
				else
				{ // An ideal division has been provided
					CalculateScaleY(*m_auto_pointer_y_min,*m_auto_pointer_y_max,*m_auto_pointer_y_div);
				}
				m_plot_y_initialised = true; // Flag that range has been initialised
			}

		}
		else
		{ // User-defined

			switch (m_user_y_div_method)
			{
				case ttTrace_Divisions_Number: // Divisions specified by number
					CalculateScaleY(m_user_y_min,m_user_y_max,m_user_y_div_number);
					break;
				case ttTrace_Divisions_Value: // Divisions specified exactly
					CalculateScaleY(m_user_y_min,m_user_y_max,m_user_y_div_value,m_user_y_align);
					break;
				default: // Divisions not specified
					CalculateScaleY(m_user_y_min,m_user_y_max);
					break;
			}
			m_plot_y_initialised = true; // Flag that range has been initialised

		}

		return true; // Axis was rescaled

	}
	else
	{

		return false; // Axis wasn't rescaled

	}
}

/* Automatically calculated divisions:

            ||     Minimum    ||     Maximum    ||
   divFinal || Number | Range || Number | Range ||
   ===============================================
     0.1    ||     10 |  1.0  ||     14 |  1.4  || => split at 1.4
     0.2    ||      7 |  1.4  ||     12 |  2.4  || => split at 2.2
     0.25   ||      8 |  2.0  ||     13 |  3.25 || => split at 3.125
     0.4    ||      8 |  3.2  ||     12 |  4.8  || => split at 4.4
     0.5    ||      8 |  4.0  ||     14 |  7.0  || => split at 7.0
     1.0    ||      7 |  7.0  ||     10 | 10.0  ||
*/
void ttTraceWindow::CalculateScaleY(double min, double max)
{
	double range = max-min;
	double rangeMagnitude = floor( log10(abs( range )) );
	double rangeScaled = range / pow(10.0, rangeMagnitude);
	double div;
	if (rangeScaled < 1.4)
	{
		div = 0.1;
	}
	else if (rangeScaled < 2.2)
	{
		div = 0.2;
	}
	else if (rangeScaled < 3.125)
	{
		div = 0.25;
	}
	else if (rangeScaled < 4.4)
	{
		div = 0.4;
	}
	else if (rangeScaled < 7.0)
	{
		div = 0.5;
	}
	else // if (rangeScaled <= 10.0)
	{
		div = 1.0;
	}
	div *= pow(10.0,rangeMagnitude);

	CalculateScaleY(min,max,div,ttTrace_Align_Auto);
}

void ttTraceWindow::CalculateScaleY(double min, double max, unsigned short divs)
{
	if (divs>255) divs = 255;

	double range = max-min;
	double divFinal = range / double(divs);

	CalculateScaleY(min,max,divFinal,ttTrace_Align_Auto);
}

void ttTraceWindow::CalculateScaleY(double min, double max, double div, ttTrace_Align align)
{
	double range = max-min;
	double bottomTick;
	double topTick;
	unsigned int numberOfTicks;
	double maxPrecision = floor( log10(abs(range)) ) - 3;
	double magnitudePosition = 0.0;
	double magnitudeMovement = 0.0;

	if (div>range)
	{ // Special case: division won't fit in range, so tick min and max only
		bottomTick = min;
		topTick = max;
		numberOfTicks = 2;
		
		m_plot_y_min = min;
		m_plot_y_max = max;
		m_plot_y_div = m_plot_y_max - m_plot_y_min;
		m_plot_y_baseTick = 0;
	}

	else
	{ // Determine ticks
		switch (align)
		{
			default:
				{ // Align the ticks automatically
					double divsIntoBound = min / div;
					if (EffectivelyEqual(divsIntoBound,round(divsIntoBound),3))
					{ // Ticks divide into the minimum nicely, so use the exact value
						bottomTick = min;
					}
					else
					{ // Otherwise take the first tick after the minimum
						bottomTick = ceil(divsIntoBound) * div;
					}
					divsIntoBound = max / div;
					if (EffectivelyEqual(divsIntoBound,round(divsIntoBound),3))
					{ // Ticks divide into the maximum nicely, so use the exact value
						topTick = max;
					}
					else
					{ // Otherwise take the first tick after the minimum
						topTick = floor(max / div) * div;
					}
					double mainTick;
					if (min<=0.0 && max>=0.0)
					{
						mainTick = 0.0;
					}
					else
					{
						mainTick = ceil(min / div) * div;
					}
					m_plot_y_baseTick = (int)floor((topTick-bottomTick) / div / 2.0);
				}
				break;
			case ttTrace_Align_Min:
				{ // Align the ticks with the minimum
					bottomTick = min;
					topTick = ( floor(range / div) * div ) + bottomTick;
					m_plot_y_baseTick = 0;
				}
				break;
			case ttTrace_Align_Max:
				{ // Align the ticks with the maximum
					topTick = max;
					double numberOfDivisions = floor(range / div);
					bottomTick = topTick - ( numberOfDivisions * div );
					m_plot_y_baseTick = int(numberOfDivisions);
				}
				break;
		}

		m_plot_y_div = div;

		if (m_user_y_autoScale)
		{
			if (min<bottomTick)
			{ // Change range to encompass min with an entire division
				bottomTick -= div;
				m_plot_y_min = bottomTick;
				++m_plot_y_baseTick;
			}
			else
			{
				m_plot_y_min = min;
			}

			if (max>topTick)
			{ // Change range to encompass max with an entire division
				topTick += div;
				m_plot_y_max = topTick;
			}
			else
			{
				m_plot_y_max = max;
			}
		}
		else
		{
			m_plot_y_min = min;
			m_plot_y_max = max;
		}

		numberOfTicks = (unsigned int)round((topTick-bottomTick) / div) + 1;

		if (numberOfTicks>256)
		{ // Need to rescale div width to allow for only 256 ticks (255 divs)
			numberOfTicks = 256;
			m_plot_x_div = (topTick-bottomTick) / 255.0;
		}
	}

	if (m_user_styleMargins)
	{
		double range = m_plot_y_max - m_plot_y_min;
		m_plot_y_styled_min = m_plot_y_min - 0.05*range;
		m_plot_y_styled_max = m_plot_y_max + 0.05*range;
	}
	else
	{
		m_plot_y_styled_min = m_plot_y_min;
		m_plot_y_styled_max = m_plot_y_max;
	}

	{ // Determine magnitudes of position & movement
		double upper = floor( log10(abs( m_plot_y_max )) );
		double lower = floor( log10(abs( m_plot_y_min )) );
		magnitudePosition = wxMax(upper,lower);

		magnitudeMovement = floor( log10(abs( m_plot_y_div )) );
	}
	
	{ // Generate ticks
		int unitMagnitude;
		double labelValue;
		wxString unit = m_details==NULL ? wxEmptyString : m_details->unit;
		int tickIndex = 0;

		m_plot_y_axisLabels.resize(numberOfTicks);
		m_plot_y_axisLabelPoints.resize(numberOfTicks);

		if (
			(m_plot_y_min>0.0 || m_plot_y_max<0.0)
			&& (magnitudePosition-magnitudeMovement) > 3.0
		)
		{ // Option 3 if a) zero is not visible, and b) we lose detail in the position by representing movement accurately

			for (std::vector<wxString>::iterator i=m_plot_y_axisLabels.begin(); i!=m_plot_y_axisLabels.end(); ++i, ++tickIndex)
			{
				m_plot_y_axisLabelPoints[tickIndex] = bottomTick + double(tickIndex)*m_plot_y_div;
				// Label value is relative to the baseline (an addition or subtraction)
				labelValue = double((tickIndex-m_plot_y_baseTick)) * m_plot_y_div;
				if (tickIndex > m_plot_y_baseTick)
				{ // Addition to baseline value, so must be prepended with a plus sign
					*i = "+" + FormatPreciseNumber(labelValue,unit);
				}
				else if (tickIndex < m_plot_y_baseTick)
				{ // Subtraction from baseline value, so already has a minus sign
					*i = FormatPreciseNumber(labelValue,unit);
				}
				else
				{ // It is the baseline value, so print that
					*i = FormatPreciseNumber(m_plot_y_axisLabelPoints[tickIndex],unit,3);
				}
			}
			m_plot_axisLabel.Clear();

		}

		else
		{ // Option 1 or 2

			if (unit.empty())
			{ // Print as X.XXX with an axis label of E+X
			
				// Base derived from the minimum magnitude. E.g. a range of 200ns to 1.2us is represented as 2-12 e-7 (instead of 0.2-1.2 e-6)
				double magnitudeSource = min(abs(m_plot_y_max),abs(m_plot_y_min));
				unitMagnitude =
					(int)floor(
						DecimalMagnitude(magnitudeSource)
					);
				m_plot_axisLabel =
					(unitMagnitude<-2 || unitMagnitude>2)
					? wxString::Format("e%+i",unitMagnitude)
					: wxEmptyString;

			}
			else
			{ // Print as X.XXX, XX.XX or XXX.X with an axis label in units

				// Base derived from the maximum magnitude. E.g. a range of 200ns to 1.2us is represented as 0.2-1.2 us (instead of 200-1200 ns)
				double magnitudeSource = max(abs(m_plot_y_max),abs(m_plot_y_min));
				unitMagnitude =
					(int)floor(
						DecimalMagnitude(magnitudeSource)
						/
						3.0
					)
					*
					3;
				m_plot_axisLabel = GetScaledUnits(unitMagnitude,unit);

			}

			bool tickedZero = false;
			for (std::vector<wxString>::iterator i=m_plot_y_axisLabels.begin(); i!=m_plot_y_axisLabels.end(); ++i, ++tickIndex)
			{
				labelValue = bottomTick + (double)(tickIndex)*m_plot_y_div;
				m_plot_y_axisLabelPoints[tickIndex] = labelValue;
				if (EffectivelyZero(labelValue,int(maxPrecision)))
				{ // Print 0 directly, as rounding errors would otherwise print it as something stupid
					*i = "0";
					m_plot_y_baseTick = tickIndex;
					tickedZero = true;
				}
				else
				{ // Label value is absolute
					if (unitMagnitude<-2 || unitMagnitude>2) labelValue /= pow(10.0, unitMagnitude);
					*i = FormatPreciseNumber(labelValue);
				}
			}

			if (!tickedZero) m_plot_y_baseTick = -1; // Prevent plot from boldening any tick

		} // End modes 1 & 2

	} // End of tick determination
}

bool ttTraceWindow::WaitingForData()
{
	return m_waitingForData;
}

void ttTraceWindow::DataReady()
{
	if (!m_waitingForData) return;
	m_waitingForData = false;
	Render(true);
}

short ttTraceWindow::GetTimeMagnitude(const double &value, bool* losingPrecision)
{
	unsigned long theTime = (unsigned long)value;
	unsigned short magnitude = 0;

	if (theTime>84599) // Greater than 23:29:59 rounds up to 1 day because both seconds and minutes will be lost
	{ // We have days
		magnitude = 3;
		// Check for two magnitudes down: minutes & seconds
		if (losingPrecision!=NULL) *losingPrecision = ((theTime%3600)>0);
	}
	else if (value<1.0)
	{ // Sub-second resolution
		double realMagnitude = floor( log10(abs( value )) );
		magnitude = short(floor( realMagnitude/3.0 ));
	}
	else
	{
		if ( ( theTime=(theTime % 86400) ) > 0 )
		{ // We have smaller units
			if (theTime>3569) // Greater than 0:59:29 rounds up to 1 hour
			{ // Have hours
				magnitude = 2;
				// Check for two magnitudes down: seconds
				if (losingPrecision!=NULL) *losingPrecision = ((theTime%60)>0);
			}
			else
			{
				if (theTime % 3600 > 59)
				{ // Have minutes
					magnitude = 1;
				}
				// Can't be losing precision at this point
				if (losingPrecision!=NULL) *losingPrecision = false;
			}
		}
	}

	return magnitude;
}

wxString ttTraceWindow::FormatTime(const double &value, short magnitude)
{
	if (magnitude==10) magnitude = GetTimeMagnitude(value);
	unsigned long theTime = (unsigned long)value;
	wxString output = wxEmptyString;

	switch (magnitude)
	{
		case 3: // Days & hours
			{
				unsigned long minutesAndSeconds = theTime % 3600;
				if (minutesAndSeconds>1799)
				{ // Round up to the nearest hour
					theTime += 3600-minutesAndSeconds;
				}
				unsigned long days = theTime / 86400;
				unsigned long hours = (theTime % 86400) / 3600;
				output << days << "d";
				if (hours>0) output << " " << hours << "h";
			}
			break;
		case 2: // Hours & minutes
			{
				unsigned long seconds = theTime % 60;
				if (seconds>29)
				{ // Round up to the nearest minute
					theTime += 60-seconds;
				}
				unsigned long hours = theTime / 3600;
				unsigned long minutes = (theTime % 3600) / 60;
				output = wxString::Format("%luh%02lu",hours,minutes);
			}
			break;
		default: // Minutes & seconds (or seconds & sub-seconds)
			{
				unsigned long minutes = theTime / 60;
				unsigned long seconds = theTime % 60;
				if (minutes>0)
				{
					output = wxString::Format("%lu:%02lu",minutes,seconds);
				}
				else
				{
					output << FormatPreciseNumber(value,"s");
				}
			}
			break;
	}

	return output;
}

wxString ttTraceWindow::FormatPreciseNumber(const double &number, const wxString &unit, const int &precisionMagnitude)
{
	wxString output = wxEmptyString;
	double numberMagnitude = (number==0.0) ? 0.0 : floor(log10(abs(number)));

	if (precisionMagnitude!=-1)
	{ // Check precision and represent equality as appropriate
		output << (LosingPrecision(number,precisionMagnitude) ? utf8("\u2248") : "=") << " ";
	}

	wxString numberString = wxEmptyString;
	/// Format number
	if (unit.empty())
	{ // Format as X.XXXE+X
		std::locale myLocale("");
		std::ostringstream outputStream;
		outputStream.imbue(myLocale);
		outputStream << std::setprecision(4) << number;
		numberString = outputStream.str();
	}
	else
	{ // Format with units, e.g. X.XXXns, XX.XX mHz or X.XXXppm
		double shownNumber;
		int unitMagnitude = (int)(floor(numberMagnitude/3.0) * 3.0);
		int unitMagnitudeOffset = 3 + unitMagnitude - (int)floor(numberMagnitude);
		if (unit.IsSameAs("pp") && unitMagnitude==-12)
		{ // Must divide the number up by an extra 10^3, so it's represented as ppbill instead of... pptrill
			shownNumber = number / pow(10.0,unitMagnitude+3);
		}
		else
		{
			shownNumber = number / pow(10.0,unitMagnitude);
		}
		numberString = wxString::Format("%.*lf",unitMagnitudeOffset,shownNumber);
		
		// Make sure the number hasn't been rounded into a different magnitude, e.g. 999.99999ps -> 1000ps, which should instead appear as 1ns
		if (numberString.Length()>=4 && ( (shownNumber<0.0 && numberString.First("000")==2) || numberString.First("000")==1 ) )
		{
			unitMagnitude += 3;
			unitMagnitudeOffset -= 1;
			shownNumber /= pow(10.0, 3);
			numberString = wxString::Format("%.*lf",unitMagnitudeOffset,shownNumber);
		}

		numberString << GetScaledUnits(unitMagnitude,unit);
	}
	if (numberString.Contains(localeDecimalPoint)) {
		wxString regexScratch;
		regexScratch << "\\" << localeDecimalPoint << "?0+(?=[^" << localeDecimalPoint << "0-9]|$)";
		wxRegEx decimals(regexScratch,wxRE_ADVANCED);
		decimals.ReplaceFirst(&numberString,"");
	}
	wxRegEx zeroes("[Ee]([-+])0+",wxRE_ADVANCED);
	zeroes.ReplaceAll(&numberString,"e\\1");
	if (numberString.Last()=='+' || numberString.Last()=='-') numberString.Append("0");
	output << numberString;
	
	return output;
}

wxString ttTraceWindow::GetScaledUnits(const int &magnitude, const wxString &unit)
{
	if (unit.IsSameAs("pp"))
	{
		switch (magnitude)
		{
			case 24:
				return "YHz/Hz";
			case 21:
				return "ZHz/Hz";
			case 18:
				return "EHz/Hz";
			case 15:
				return "PHz/Hz";
			case 12:
				return "THz/Hz";
			case 9:
				return "GHz/Hz";
			case 6:
				return "MHz/Hz";
			case 3:
				return "kHz/Hz";
			case 2:
				return "hHz/Hz";
			case 0:
				return "Hz/Hz";
			case -1:
				return "daHz/Hz"; // deci (d)
			case -2:
				return "cHz/Hz";
			case -3:
				return "mHz/Hz";
			case -6:
				return "ppm";
			case -9:
				return "ppb";
			case -12: // Also represent as ppb. It is up to the calling function to alter the magnitude of the number it's formatting
				return "ppb";
			case -15:
				return "fHz/Hz";
			case -18:
				return "aHz/Hz";
			case -21:
				return "zHz/Hz";
			case -24:
				return "yHz/Hz";
			default:
				return "?Hz/Hz";
		}
	}
	else
	{
		switch (magnitude)
		{
			case 24:
				return "Y"+unit;
			case 21:
				return "Z"+unit;
			case 18:
				return "E"+unit;
			case 15:
				return "P"+unit;
			case 12:
				return "T"+unit;
			case 9:
				return "G"+unit;
			case 6:
				return "M"+unit;
			case 3:
				return "k"+unit;
			case 2:
				return "h"+unit;
			case 0:
				return unit;
			case -1:
				return "da"+unit; // deci (d)
			case -2:
				return "c"+unit;
			case -3:
				return "m"+unit;
			case -6:
				return utf8("\u00b5")+unit;
			case -9:
				return "n"+unit;
			case -12:
				return "p"+unit;
			case -15:
				return "f"+unit;
			case -18:
				return "a"+unit;
			case -21:
				return "z"+unit;
			case -24:
				return "y"+unit;
			default:
				return "?"+unit;
		}
	}
}

void ttTraceWindow::AcquireData(const std::vector<double>* &x, const std::vector<double>* &y)
{
	m_points_store_mutex.Lock();
	x = &m_points_store_x;
	y = &m_points_store_y;
}

void ttTraceWindow::ReleaseData()
{
	m_points_store_mutex.Unlock();
}

void ttTraceWindow::DerivedLost()
{
	m_derived = NULL;
}

/****************
  ttTraceThread
****************/

#ifdef __WXDEBUG__

	ttTraceThread::ttTraceThread(const wxString &name, ttTraceWindow* window)
		: ttThread(threadPlotting,NULL),
		m_window(window)
	{
		m_name << " (" << name << ")";
	}

#else

	ttTraceThread::ttTraceThread(ttTraceWindow* window)
		: ttThread(NULL),
		m_window(window)
	{
	}

#endif

ttTraceThread::~ttTraceThread()
{
}

/** First thread-specific function called by the new thread. Leads on to the appropriate routine in the ttTraceWindow */
UINT ttTraceThread::StartThisThread() {
	m_window->DoRender();
	return 0;
}