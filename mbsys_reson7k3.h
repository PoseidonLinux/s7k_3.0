/*--------------------------------------------------------------------
 *    The MB-system:	mbsys_reson7k3.h	3/3/2004
 *	$Id: mbsys_reson7k3.h 2308 2017-06-04 19:55:48Z caress $
 *
 *    Copyright (c) 2004-2017 by
 *    David W. Caress (caress@mbari.org)
 *      Monterey Bay Aquarium Research Institute
 *      Moss Landing, CA 95039
 *    and Dale N. Chayes (dale@ldeo.columbia.edu)
 *      Lamont-Doherty Earth Observatory
 *      Palisades, NY 10964
 *
 *    See README file for copying and redistribution conditions.
 *--------------------------------------------------------------------*/
/*
 * mbsys_reson7k3.h defines the MBIO data structures for handling data from
 * Teledyne Reson 7k series, Teledyne Odom MB2, Teledyne BlueView ProScan
 * software, Hydrosweep 3rd generation (HS3) sonars and other applications
 * and sonars using 7k data record formats:
 *      MBF_RESON7K3 : MBIO ID 88 - Teledyne Reson 3rd generation 7K data format
 *
 * Author:	D. W. Caress & C. S. Ferreira
 * Date:	March 3, 2004 & June 6, 2017
 *
 *
 */
/*
 * Notes on the mbsys_reson7k3 data structure:
 *   1. This format is defined by the 7k Data Format Definition (DFD) 
 *      document for Teledyne RESON SeaBat 7k format v3.08.
 *   2. Reson 7k series multibeam sonars output bathymetry, per beam
 *      amplitude, sidescan data and water column.
 *   3. Reson 7k format is used also to log sidescan and subbottom
 *      data from other sonars.
 *   4. The 7k record consists of a data record frame (header and checksum),
 *      a record  type header, an optional record data field and an optional
 *      data field for extra  information. The optional data field typically
 *      holds sensor specific data and third party developer
 *      embedded data.
 *   5. Navigation data may be found in three different record types.
 *      The bathymetry records (kind = MB_DATA_DATA) hold navigation
 *      and attitude data, but these values are not initially set by
 *      the Reson 6046 datalogger. In MB-System these values get set
 *      by running the program mbpreprocess by interpolating the
 *      the values found in either the R7KRECID_Position records
 *      (kind = MB_DATA_NAV1) or the R7KRECID_Bluefin records
 *      (kind = MB_DATA_NAV2). MB-System uses the bathymetry records as
 *      the primary navigation source, so the interpolated values are
 *      accessed by mbnavedit and, by default, mbnavlist. The raw values
 *      of the ancillary navigation records (R7KRECID_Position and
 *      R7KRECID_Bluefin) may be accessed by mbnavlist using the -N1
 *      and -N2 options, respectably.
 *   6. Attitude data may be found in three different record types.
 *      The bathymetry records (kind = MB_DATA_DATA) hold navigation
 *      and attitude data, but these values are not initially set by
 *      the Reson 6046 datalogger. In MB-System these values get set
 *      by running the program mb7kpreprocess by interpolating the
 *      the values found in either the R7KRECID_RollPitchHeave records
 *      (kind = MB_DATA_ATTITUDE) or the R7KRECID_Bluefin records
 *      (kind = MB_DATA_NAV2). MB-System uses the bathymetry records as
 *      the primary attitude source, so the interpolated values are
 *      accessed by mbnavedit and, by default, mbnavlist. The raw values
 *      of the secondary ancillary navigation records (R7KRECID_Bluefin),
 *      including attitude, may be accessed by mbnavlist using the -N2
 *      option.
 *   7. The MB-System code assumes that a Reson 7k data file will include
 *      either R7KRECID_RollPitchHeave and R7KRECID_Position records
 *      or R7KRECID_Bluefin records. Bad things will happen if the
 *      data file contains both the generic records and the bluefin
 *      records.
 *   8. Reserved identifiers or ranges were omitted in the "Devices"
 *      section.
 */

/* include mb_define.h */
#ifndef MB_DEFINE_DEF
#include "mb_define.h"
#endif

/*---------------------------------------------------------------*/
/* Record ID definitions */

/* 0 means no record at all */
#define R7KRECID_None 0

/* 1000-1999 reserved for generic sensor records */
#define R7KRECID_ReferencePoint 1000
#define R7KRECID_UncalibratedSensorOffset 1001
#define R7KRECID_CalibratedSensorOffset 1002
#define R7KRECID_Position 1003
#define R7KRECID_CustomAttitude 1004
#define R7KRECID_Tide 1005
#define R7KRECID_Altitude 1006
#define R7KRECID_MotionOverGround 1007
#define R7KRECID_Depth 1008
#define R7KRECID_SoundVelocityProfile 1009
#define R7KRECID_CTD 1010
#define R7KRECID_Geodesy 1011
#define R7KRECID_RollPitchHeave 1012
#define R7KRECID_Heading 1013
#define R7KRECID_SurveyLine 1014
#define R7KRECID_Navigation 1015
#define R7KRECID_Attitude 1016
#define R7KDEVID_PanTilt 1017
#define R7KDEVID_SonarInstallationIDs 1020

/* 2000-2999 reserved for user defined records */
#define R7KRECID_SonarPipeEnvironment 2004

/* 3000-6999 reserved for extra records */
#define R7KRECID_ContactOutput 3001

/* 7000-7999 reserved for SeaBat 7k records */
#define R7KRECID_7kSonarSettings 7000
#define R7KRECID_7kConfiguration 7001
#define R7KRECID_7kMatchFilter 7002
#define R7KRECID_7kFirmwareHardwareConfiguration 7003
#define R7KRECID_7kBeamGeometry 7004
#define R7KRECID_7kBathymetricData 7006
#define R7KRECID_7kSideScanData 7007
#define R7KRECID_7kWaterColumnData 7008
#define R7KRECID_7kTVG 7010
#define R7KRECID_7kImageData 7011
#define R7KRECID_7kPingMotionData 7012
#define R7KDEVID_7kAdaptiveGate 7014
#define R7KRECID_7kDetectionDataSetup 7017
#define R7KRECID_7kBeamformedData 7018
#define R7KRECID_7kVernierProcessingDataRaw 7019
#define R7KRECID_7kBITEData 7021
#define R7KRECID_7kSonarSourceVersion 7022
#define R7KRECID_7k8kWetEndVersion 7023
#define R7KRECID_7kRawDetectionData 7027
#define R7KRECID_7kSnippetData 7028
#define R7KRECID_7kVernierProcessingDataFiltered 7029
#define R7KRECID_7kInstallationParameters 7030
#define R7KRECID_7kBITESummary 7031
#define R7KRECID_7kCompressedBeamformedMagnitude 7041
#define R7KRECID_7kCompressedWaterColumn 7042
#define R7KRECID_7kSegmentedRawDetection 7047
#define R7KRECID_7kCalibratedBeamData 7048
#define R7KRECID_7kSystemEvents 7050
#define R7KRECID_7kSystemEventMessage 7051
#define R7KRECID_7kRDRRecordingStatus 7052
#define R7KRECID_7kSubscriptions 7053
#define R7KRECID_7kRDRStorageRecording 7054
#define R7KRECID_7kCalibrationStatus 7055
#define R7KRECID_7kCalibratedSideScan 7057
#define R7KRECID_7kSnippetBackscatteringStrength 7058
#define R7KRECID_7kMB2Status 7059
#define R7KRECID_7kFileHeader 7200
#define R7KRECID_7kFileCatalogRecord 7300
#define R7KRECID_7kTimeMessage 7400
#define R7KRECID_7kRemoteControl 7500
#define R7KRECID_7kRemoteControlAcknowledge 7501
#define R7KRECID_7kRemoteControlNotAcknowledge 7502
#define R7KRECID_7kRemoteControlSonarSettings 7503
#define R7KRECID_7kCommonSystemSettings 7504
#define R7KRECID_7kSVFiltering 7510
#define R7KRECID_7kSystemLockStatus 7511
#define R7KRECID_7kSoundVelocity 7610
#define R7KRECID_7kAbsorptionLoss 7611
#define R7KRECID_7kSpreadingLoss 7612

/*---------------------------------------------------------------*/
/* Record size definitions */
#define MBSYS_RESON7K_VERSIONSYNCSIZE 64
#define MBSYS_RESON7K_RECORDHEADER_SIZE 64
#define MBSYS_RESON7K_RECORDTAIL_SIZE 4

/* 0 means no record at all */
#define R7KHDRSIZE_None 0

/* 1000-1999 reserved for generic sensor records */
#define R7KHDRSIZE_ReferencePoint 16
#define R7KHDRSIZE_UncalibratedSensorOffset 24
#define R7KHDRSIZE_CalibratedSensorOffset 24
#define R7KHDRSIZE_Position 37
#define R7KHDRSIZE_CustomAttitude 8
#define R7KRDTSIZE_CustomAttitude 4
#define R7KHDRSIZE_Tide 43
#define R7KHDRSIZE_Altitude 4
#define R7KHDRSIZE_MotionOverGround 8
#define R7KHDRSIZE_Depth 8
#define R7KHDRSIZE_SoundVelocityProfile 24
#define R7KRDTSIZE_SoundVelocityProfile 8
#define R7KHDRSIZE_CTD 36
#define R7KRDTSIZE_CTD 20
#define R7KHDRSIZE_Geodesy 320
#define R7KHDRSIZE_RollPitchHeave 12
#define R7KHDRSIZE_Heading 4
#define R7KHDRSIZE_SurveyLine 72
#define R7KRDTSIZE_SurveyLine 16
#define R7KHDRSIZE_Navigation 41
#define R7KHDRSIZE_Attitude 1
#define R7KRDTSIZE_Attitude 18
#define R7KHDRSIZE_PanTilt 8
#define R7KHDRSIZE_SonarInstallationIDs 164

/* 2000-2999 reserved for user defined records */
#define R7KHDRSIZE_SonarPipeEnvironment 83
#define R7KRDTSIZE_SonarPipeEnvironment 20

/* 3000-6999 reserved for other vendor records */
#define R7KHDRSIZE_ContactOutput 450

/* 7000-7999 reserved for SeaBat 7k records */
#define R7KHDRSIZE_7kSonarSettings 156
#define R7KHDRSIZE_7kConfiguration 12
#define R7KHDRSIZE_7kMatchFilter 88
#define R7KHDRSIZE_7kFirmwareHardwareConfiguration 8
#define R7KHDRSIZE_7kBeamGeometry 12
#define R7KHDRSIZE_7kBathymetricData 24
#define R7KHDRSIZE_7kSideScanData 64
#define R7KHDRSIZE_7kWaterColumnData 30
#define R7KHDRSIZE_7kTVGData 50
#define R7KHDRSIZE_7kImageData 56
#define R7KHDRSIZE_7kPingMotionData 44
#define R7KHDRSIZE_7kAdaptiveGate 
#define R7KHDRSIZE_7kDetectionDataSetup 116
#define R7KRDTSIZE_7kDetectionDataSetup 30
#define R7KHDRSIZE_7kBeamformedData 52
#define R7KHDRSIZE_7kVernierProcessingDataRaw 92
#define R7KHDRSIZE_7kBITEData 2
#define R7KRDTSIZE_7kBITERecordData 130
#define R7KRDTSIZE_7kBITEFieldData 79
#define R7KHDRSIZE_7kSonarSourceVersion 32
#define R7KHDRSIZE_7k8kWetEndVersion 32
#define R7KHDRSIZE_7kRawDetectionData 99
#define R7KRDTSIZE_7kRawDetectionData 34
#define R7KHDRSIZE_7kSnippetData 46
#define R7KRDTSIZE_7kSnippetDataseries 14
#define R7KHDRSIZE_7kVernierProcessingDataFiltered 26
#define R7KRDTSIZE_7kVernierProcessingDataFiltered 16
#define R7KHDRSIZE_7kInstallationParameters 616
#define R7KHDRSIZE_7kBITESummary 36
#define R7KHDRSIZE_7kCompressedBeamformedMagnitude 38
#define R7KHDRSIZE_7kCompressedWaterColumn 44
#define R7KHDRSIZE_7kSegmentedRawDetection 36
#define R7KRDTSIZE_7kSegmentedRawDetection 100
#define R7KHDRSIZE_7kCalibratedBeamData 56
#define R7KHDRSIZE_7kSystemEvents 12
#define R7KHDRSIZE_7kSystemEventMessage 14
#define R7KHDRSIZE_7kRDRRecordingStatus 566
#define R7KHDRSIZE_7kSubscriptions 4
#define R7KRDTSIZE_7kSubscriptions 780
#define R7KHDRSIZE_7kRDRStorageRecording 303
#define R7KHDRSIZE_7kCalibrationStatus 826
#define R7KHDRSIZE_7kCalibratedSideScan 65
#define R7KHDRSIZE_7kSnippetBackscatteringStrength 49
#define R7KHDRSIZE_7kMB2Status 2088
#define R7KHDRSIZE_7kFileHeader 44
#define R7KRDTSIZE_7kFileHeader 272
#define R7KHDRSIZE_7kFileCatalogRecord 14
#define R7KRDTSIZE_7kFileCatalogRecord 48
#define R7KHDRSIZE_7kTimeMessage 16
#define R7KHDRSIZE_7kRemoteControl 24
#define R7KHDRSIZE_7kRemoteControlAcknowledge 20
#define R7KHDRSIZE_7kRemoteControlNotAcknowledge 24
#define R7KHDRSIZE_7kRemoteControlSonarSettings 260
#define R7KHDRSIZE_7kCommonSystemSettings 543
#define R7KHDRSIZE_7kSVFiltering 9
#define R7KHDRSIZE_7kSystemLockStatus 38
#define R7KHDRSIZE_7kSoundVelocity 4
#define R7KHDRSIZE_7kAbsorptionLoss 4
#define R7KHDRSIZE_7kSpreadingLoss 4

/*---------------------------------------------------------------*/

/* Device identifiers */
#define R7KDEVID_SeaBatT20 20
#define R7KDEVID_SeaBatT20Dual 22
#define R7KDEVID_SeaBatT50 50
#define R7KDEVID_SeaBatT50Dual 52
#define R7KDEVID_GenericPosition 100
#define R7KDEVID_GenericHeading 101
#define R7KDEVID_GenericAttitude 102
#define R7KDEVID_GenericMBES 103
#define R7KDEVID_GenericSideScan 104
#define R7KDEVID_GenericSBP 105
#define R7KDEVID_OdomMB1 1000
#define R7KDEVID_TrueTime 1001
#define R7KDEVID_OdomMB2 1002
#define R7KDEVID_CDCSMCG 2000
#define R7KDEVID_CDCSPG 2001
#define R7KDEVID_EmpireMagnetics 2002
#define R7KDEVID_ResonTC4013 4013
#define R7KDEVID_ResonDiverDat 6000
#define R7KDEVID_Reson7kSonarSource 7000
#define R7KDEVID_Reson7kUserInterface 7001
#define R7KDEVID_ResonPDS 7003
#define R7KDEVID_Reson7kLogger 7004
#define R7KDEVID_BlueViewProScan 7005
#define R7KDEVID_SeaBat7012 7012
#define R7KDEVID_SeaBat7100 7100
#define R7KDEVID_SeaBat7101 7101
#define R7KDEVID_SeaBat7102 7102
#define R7KDEVID_SeaBat7111 7111
#define R7KDEVID_SeaBat7112 7112
#define R7KDEVID_SeaBat7123 7123
#define R7KDEVID_SeaBat7125 7125
#define R7KDEVID_SeaBat7128 7128
#define R7KDEVID_SeaBat7130 7130
#define R7KDEVID_SeaBat7150 7150
#define R7KDEVID_SeaBat7160 7160
#define R7KDEVID_SeaBat8100 8100
#define R7KDEVID_SeaBat8101 8101
#define R7KDEVID_SeaBat8102 8102
#define R7KDEVID_SeaBat8112 8111
#define R7KDEVID_SeaBat8123 8123
#define R7KDEVID_SeaBat8124 8124
#define R7KDEVID_SeaBat8125 8125
#define R7KDEVID_SeaBat8128 8128
#define R7KDEVID_SeaBat8150 8150
#define R7KDEVID_SeaBat8160 8160
#define R7KDEVID_TSSDMS05 10000
#define R7KDEVID_TSS335B 10001
#define R7KDEVID_TSS332B 10002
#define R7KDEVID_SeaBirdSBE37 10010
#define R7KDEVID_Littom200 10200
#define R7KDEVID_EdgetechFSDWSBP 11000
#define R7KDEVID_EdgetechFSDWSSLF 11001
#define R7KDEVID_EdgetechFSDWSSHF 11002
#define R7KDEVID_BlueFin 11100
#define R7KDEVID_IfremerTechsas 11200
#define R7KDEVID_SimradRPT319 12000
#define R7KDEVID_NorbitWBMSFLS400 13002
#define R7KDEVID_NorbitWBMSBathy400 13003
#define R7KDEVID_NorbitiWMBMS 13004
#define R7KDEVID_NorbitBathy400Compact 13005
#define R7KDEVID_NorbitWBMSBathy200 13007
#define R7KDEVID_NorbitBathy400 13008
#define R7KDEVID_NorbitFLSDeepSea400 13009
#define R7KDEVID_NorbitBathyDeepSea400 13010
#define R7KDEVID_NorbitBathyDeepSea200 13011
#define R7KDEVID_NorbitiLidar 13012
#define R7KDEVID_NorbitBathySTX400 13016
#define R7KDEVID_NorbitBathySTX200 13017
#define R7KDEVID_NorbitiWBMSe 13018
#define R7KDEVID_Hydrosweep3DS 14000
#define R7KDEVID_Hydrosweep3MD50 14001
#define R7KDEVID_Hydrosweep3MD30 14002

/*---------------------------------------------------------------*/

/* Structure size definitions */
#define MBSYS_RESON7K_BUFFER_STARTSIZE 32768
#define MBSYS_RESON7K_MAX_DEVICE 71
#define MBSYS_RESON7K_MAX_RECEIVERS 1024
#define MBSYS_RESON7K_MAX_BEAMS 1024
#define MBSYS_RESON7K_MAX_PIXELS 4096

typedef struct s7k_time_struct {
	unsigned short Year; /* Year                 u16 0 - 65535 */
	unsigned short Day;  /* Day                  u16 1 - 366 */

	float Seconds; /* Seconds              f32 0.000000 - 59.000000 */

	mb_u_char Hours;   /* Hours                u8  0 - 23 */
	mb_u_char Minutes; /* Minutes              u8  0 - 59 */
} s7k_time;

typedef struct s7k_header_struct {
	unsigned short Version; /* Version              u16 Version of this frame (e.g.: 1, 2 etc.) */
	unsigned short Offset;  /* Offset               u16 Offset in bytes from the start of the sync
	                                                pattern to the start of the DATA SECTION.
	                                                This allows for expansion of the header
	                                                whilst maintaining backward compatibility. */

	unsigned int SyncPattern;            /* Sync pattern         u32 0x0000FFFF */
	unsigned int Size;                   /* Size                 u32 Size in bytes of this record from the start
	                                                             of the version field to the end of the
	                                                             Checksum. It includes the embedded data size. */
	unsigned int OptionalDataOffset;     /* Data offset          u32 Offset in bytes to optional data field from
	                                                             start of record. Zero implies no optional data. */
	unsigned int OptionalDataIdentifier; /* Data idenfitifer     u32 Identifier for optional data field. Zero for
	                                                             no optional field. This identifier is
	                                                             described with each record type. */
	s7k_time s7kTime;                    /* 7KTIME               u8*10   UTC.*/
	unsigned short RecordVersion;        /* Currently 1 */
	unsigned int RecordType;             /* Record type          u32 Unique identifier of indicating the type of
	                                                             data embedded in this record. */
	unsigned int DeviceId;               /* Device identifier    u32 Identifier of the device to which this datum pertains. */
	unsigned short Reserved;             /* Reserved  */
	unsigned short SystemEnumerator;     /* System enumerator    The enumerator is used to differentiate between devices with the
	                                                             same device identifiers in one installation/system. It is up to
	                                                             each application to decide what number to populate this field with.  */
	unsigned int Reserved2;              /* Reserved  */

	unsigned short Flags;                /* Flags                u16 BIT FIELD:
	                                                             Bit 0 - Checksum
	                                                                 0 - invalid checksum
	                                                                 1 - valid checksum
	                                                             Bit 1 - Reserved
	                                                             Bit 2 - Fragmentation
	                                                                 0 - data unfragmented
	                                                                 1 - fragmented sequence */
	unsigned short Reserved3;     /* Reserved  */
	unsigned int Reserved4;       /* Reserved  */
	unsigned int FragmentedTotal; /* Total Fragmented            Total records in fragmented data record set (if flag is set) - NEW in
	                                                             version 4 header */
	unsigned int FragmentNumber;  /* Fragment number             Fragment number (if flag is set) - NEW in version 4 header */

	/* Following this header is:
	    DATA SECTION                    Dynamic Record type specific data.
	    Checksum                        u32 Sum of bytes in data section
	                                    (optional, depends on bit 1 of Flags field).
	                                    Note: the checksum field  should be computed
	                                    as a 64 bit unsigned integer  with the least
	                                    significant 32 bits used to populate  this field
	                                    thus ensuring a valid checksum and  avoiding
	                                    an explicit overflow.  */
} s7k_header;

/* Reference point information (record 1000) */
/* Note: these offsets should be zero for submersible vehicles */
typedef struct s7kr_reference_struct {
	s7k_header header;
	float offset_x; /* Vehicle's X reference point ot center of gravity (meters) */
	float offset_y; /* Vehicle's Y reference point ot center of gravity (meters) */
	float offset_z; /* Vehicle's Z reference point ot center of gravity (meters) */
	float water_z;  /* Vehicle's water level to center of gravity (meters) */
} s7kr_reference;

/* Sensor uncalibrated offset position information (record 1001) */
typedef struct s7kr_sensoruncal_struct {
	s7k_header header;
	float offset_x;     /* Sensor X offset from vehicle reference point (meters) */
	float offset_y;     /* Sensor Y offset from vehicle reference point (meters) */
	float offset_z;     /* Sensor Z offset from vehicle reference point (meters) */
	float offset_roll;  /* Sensor roll offset (radians - port up is positive) */
	float offset_pitch; /* Sensor pitch offset (radians - bow up is positive) */
	float offset_yaw;   /* Sensor yaw offset (radians - bow right/starboard is positive) */
} s7kr_sensoruncal;

/* Sensor calibrated offset position information (record 1002) */
typedef struct s7kr_sensorcal_struct {
	s7k_header header;
	float offset_x;     /* Sensor X offset from vehicle reference point (meters) */
	float offset_y;     /* Sensor Y offset from vehicle reference point (meters) */
	float offset_z;     /* Sensor Z offset from vehicle reference point (meters) */
	float offset_roll;  /* Sensor roll offset (radians - port up is positive) */
	float offset_pitch; /* Sensor pitch offset (radians - bow up is positive) */
	float offset_yaw;   /* Sensor yaw offset (radians - bow right/starboard is positive) */
} s7kr_sensorcal;

/* Position (record 1003) */
typedef struct s7kr_position_struct {
	s7k_header header;
	unsigned int datum; /* 0=WGS84; others reserved */
	float latency;      /* Position sensor time latency (seconds) */
	double latitude;    /* Latitude (radians) or northing in meters */
	double longitude;   /* Longitude (radians) or easting in meters */
	double height;      /* Height relative to datum (meters) */
	mb_u_char type;     /* Position type flag:
	                       0: Geographical coordinates
	                       1: Grid coordinates */
	mb_u_char utm_zone; /* UTM zone */
	mb_u_char quality;  /* Quality flag
	                       0: Navigation data
	                       1: Dead reckoning */
	mb_u_char method;   /* Positioning method
	                       0: GPS
	                       1: DGPS
	                       2: Start of inertial positioning system from GPS
	                       3: Start of inertial positioning system from DGPS
	                       4: Start of inertial positioning system from bottom correlation
	                       5: Start of inertial positioning system from bottom object
	                       6: Start of inertial positioning system from inertial positioning
	                       7: Start of inertial positioning system from optional data
	                       8: Stop of inertial positioning system from GPS
	                       9: Stop of inertial positioning system from DGPS
	                      10: Stop of inertial positioning system from bottom correlation
	                      11: Stop of inertial positioning system from bottom object
	                      12: Stop of inertial positioning system from inertial positioning
	                      13: Stop of inertial positioning system from optional data
	                      14: User defined
	                      15: RTK Fixed
	                      16: RTK Float */
/*  mb_u_char nsat;     Optional */
} s7kr_position;

/* Custom attitude (record 1004) */
typedef struct s7kr_customattitude_struct {
	s7k_header header;
	mb_u_char fieldmask; /* Boolean bitmask indicating which attitude fields are in data
	                        0: pitch (radians - float)
	                        1: roll (radians - float)
	                        2: heading (radians - float)
	                        3: heave (meters - float)
	                        4: pitch rate (radians per second - float)
	                        5: roll rate (radians per second - float)
	                        6: heading rate (radians per second - float)
	                        7: heave rate (radians per second - float) */
	mb_u_char reserved;  /* reserved field */
	unsigned short n;    /* number of fields */
	float frequency;     /* sample rate (samples/second) */
	int nalloc;          /* number of samples allocated */
	float *pitch;
	float *roll;
	float *heading;
	float *heave;
	float *pitchrate;
	float *rollrate;
	float *headingrate;
	float *heaverate;
} s7kr_customattitude;

/* Tide (record 1005) */
typedef struct s7kr_tide_struct {
	s7k_header header;
	float tide;            /* height correction above mean sea level (meters) */
	unsigned short source; /* tide data source: 0 - unspecified; 1 - table; 2 - gauge */
	mb_u_char flags;       /* Gauge and position validity flags
	                          Bit 0: 0/1 for gauge id valid/invalid
	                          Bit 1: 0/1 for position valid/invalid */
	unsigned short gauge;  /* Optional field to permit discrimination
	                          between different devices */
	unsigned int datum;    /* 0=WGS84; others reserved */
	float latency;         /* Position sensor time latency (seconds) */
	double latitude;       /* Latitude (radians) or northing in meters */
	double longitude;      /* Longitude (radians) or easting in meters */
	double height;         /* Height relative to datum (meters) */
	mb_u_char type;        /* Position type flag:
	                          0: Geographical coordinates
	                          1: Grid coordinates */
	mb_u_char utm_zone;    /* UTM zone */
} s7kr_tide;

/* Altitude (record 1006) */
typedef struct s7kr_altitude_struct {
	s7k_header header;
	float altitude;        /* altitude above seafloor (meters) */
} s7kr_altitude;

/* Motion over ground (record 1007) */
typedef struct s7kr_motion_struct {
	s7k_header header;
	mb_u_char flags;       /* Field mask indicating which motion over ground fields are in data
	                          0: X,Y,Z speed (m/s - 3 X float)
	                          1: X,Y,Z acceleration (m/s**2 - 3 X float)
	                        2-7: reserved */
	mb_u_char reserved;    /* reserved field */
	unsigned short n;      /* number of fields */
	float frequency;       /* sample rate (samples/second) */
	int nalloc;            /* number of samples allocated */
	float *x;
	float *y;
	float *z;
	float *xa;
	float *ya;
	float *za;
} s7kr_motion;

/* Depth (record 1008) */
typedef struct s7kr_depth_struct {
	s7k_header header;
	mb_u_char descriptor;    /* Depth descriptor:
	                            0 = depth to sensor
	                            1 = water depth */
	mb_u_char correction;    /* Correction flag:
	                            0 = raw depth as measured
	                            1 = corrected depth (relative to mean sea level) */
	unsigned short reserved; /* reserved field */
	float depth;             /* depth (meters) */
} s7kr_depth;

/* Sound velocity profile (record 1009) */
typedef struct s7kr_svp_struct {
	s7k_header header;
	mb_u_char position_flag;  /* Position validity flag:
	                             0: invalid position fields
	                             1: valid position field */
	mb_u_char reserved1;      /* reserved field */
	unsigned short reserved2; /* reserved field */
	double latitude;          /* Latitude (radians) */
	double longitude;         /* Longitude (radians) */
	unsigned int n;           /* number of fields */
	int nalloc;               /* number of samples allocated */
	float *depth;             /* depth (meters) */
	float *sound_velocity;    /* sound velocity (meters/second) */
} s7kr_svp;

/* CTD (record 1010) */
typedef struct s7kr_ctd_struct {
	s7k_header header;
	float frequency;                /* Sample rate */
	mb_u_char velocity_source_flag; /* Velocity source flag:
	                                   0: not computed
	                                   1: CTD
	                                   2: user computed */
	mb_u_char velocity_algorithm;   /* Velocity algorithm flag:
	                                   0: not computed
	                                   1: Chen Millero
	                                   2: Delgrosso */
	mb_u_char conductivity_flag;    /* Conductivity flag:
	                                   0: conductivity
	                                   1: salinity */
	mb_u_char pressure_flag;        /* Pressure flag:
	                                   0: pressure
	                                   1: depth */
	mb_u_char position_flag;        /* Position validity flag:
	                                   0: invalid position fields
	                                   1: valid position field */
	mb_u_char validity;             /* Sample content validity:
	                                   Bit 0: conductivity/salinity
	                                   Bit 1: water temperature
	                                   Bit 2: pressure/depth
	                                   Bit 3: sound velocity
	                                   Bit 4: absorption */
	unsigned short reserved;        /* Reserved field */
	double latitude;                /* Latitude (radians) */
	double longitude;               /* Longitude (radians) */
	float sample_rate;              /* Sample rate */
	unsigned int n;                 /* Number of fields */
	int nalloc;                     /* Number of samples allocated */
	float *conductivity_salinity;   /* Conductivity (s/m) or salinity (ppt) */
	float *temperature;             /* Temperature (degrees celcius) */
	float *pressure_depth;          /* Pressure (pascals) or depth (meters) */
	float *sound_velocity;          /* Sound velocity (meters/second) */
	float *absorption;              /* Sound velocity absorption (dB/second) */
} s7kr_ctd;

/* Geodesy (record 1011) */
typedef struct s7kr_geodesy_struct {
	s7k_header header;
	char spheroid[32];               /* Text description of the spheroid name (e.g. "WGS84") */
	double semimajoraxis;            /* Semi-major axis in meters (e.g. 6378137.0 for WGS84) */
	double flattening;               /* Inverse flattening in meters (e.g. 298.257223563 for WGS84) */
	char reserved1[16];              /* Reserved space */
	char datum[32];                  /* Datum name (e.g. "WGS84") */
	unsigned int calculation_method; /* Data calculation method:
	                                    0 - Molodensky
	                                    1 - Bursa / Wolfe
	                                    2 - DMA MRE
	                                    3 - NADCON
	                                    4 - HPGN
	                                    5 - Canadian National Transformation V2 */
	unsigned int number_parameters;  /* Seven parameter transformation supported */
	double dx;                       /* X shift (meters) */
	double dy;                       /* Y shift (meters) */
	double dz;                       /* Z shift (meters) */
	double rx;                       /* X rotation (radians) */
	double ry;                       /* Y rotation (radians) */
	double rz;                       /* Z rotation (radians) */
	double scale;                    /* Scale */
	char reserved2[35];              /* Reserved for implementation of 9 parameter transformation */
	char grid_name[32];              /* Name of grid system in use: (e.g. "UTM") */
	mb_u_char distance_units;        /* Grid distance units:
	                                    0 - meters
	                                    1 - feet
	                                    2 - yards
	                                    3 - US survey feet
	                                    4 - km
	                                    5 - miles
	                                    6 - US survey miles
	                                    7 - nautical miles
	                                    8 - chains
	                                    9 - links */
	mb_u_char angular_units;         /* Grid angulat units:
	                                    0 - radians
	                                    1 - degrees
	                                    2 - degrees, minutes, seconds
	                                    3 - gradians
	                                    4 - arc-seconds */
	double latitude_origin;          /* Latitude of origin */
	double central_meriidan;         /* Central meridian */
	double false_easting;            /* False easting (meters) */
	double false_northing;           /* False northing (meters) */
	double central_scale_factor;     /* Central scale factor */
	int custom_identifier;           /* Identifier for optional field definition in 7k record.
	                                    Used to define projection specific parameters.
	                                    -2 - custom
	                                    -1 - not used */
	char reserved3[50];              /* Reserved field */
} s7kr_geodesy;

/* Roll pitch heave (record 1012) */
typedef struct s7kr_rollpitchheave_struct {
	s7k_header header;
	float roll;  /* Roll (radians) */
	float pitch; /* Pitch (radians) */
	float heave; /* Heave (m) */
} s7kr_rollpitchheave;

/* Heading (record 1013) */
typedef struct s7kr_heading_struct {
	s7k_header header;
	float heading; /* Heading (radians) */
} s7kr_heading;

/* Survey Line (record 1014) */
typedef struct s7kr_surveyline_struct {
	s7k_header header;
	unsigned short n;    /* Number of points */
	unsigned short type; /* Position type flag:
	                        0: Geographical coordinates
	                        1: Grid coordinates */
	float turnradius;    /* Turn radius between line segments
	                        (meters, 0 = no curvature in turns) */
	char name[64];       /* Line name */
	int nalloc;          /* Number of points allocated */
	double *latitude;    /* Latitude (radians, -pi/2 to pi/2) */
	double *longitude;   /* Longitude (radians -pi to pi) */
} s7kr_surveyline;

/* Navigation (record 1015) */
typedef struct s7kr_navigation_struct {
	s7k_header header;
	mb_u_char vertical_reference; /* Vertical reference:
	                                 1 = Ellipsoid
	                                 2 = Geoid
	                                 3 = Chart datum */
	double latitude;              /* Latitude (radians, -pi/2 to pi/2) */
	double longitude;             /* Longitude (radians -pi to pi) */
	float position_accuracy;      /* Horizontal position accuracy (meters) */
	float height;                 /* Height of vessel reference point above
	                                 vertical reference (meters) */
	float height_accuracy;        /* Height accuracy (meters) */
	float speed;                  /* Speed over ground (meters/sec) */
	float course;                 /* Course over ground (radians) */
	float heading;                /* Heading (radians) */
} s7kr_navigation;

/* Attitude (record 1016) */
typedef struct s7kr_attitude_struct {
	s7k_header header;
	mb_u_char n;                /* number of datasets */
	int nalloc;                 /* number of samples allocated */
	unsigned short *delta_time; /* Time difference with record timestamp (msec) */
	float *roll;                /* Roll (radians) */
	float *pitch;               /* Pitch (radians) */
	float *heave;               /* Heave (m) */
	float *heading;             /* Heading (radians) */
} s7kr_attitude;

/* Pan Tilt (record 1017) */
typedef struct s7kr_pantilt_struct {
	s7k_header header;
	float pan;  /* Angle (radians) */
	float tilt; /* Angle (radians) */
} s7kr_pantilt;

/* Sonar Installation Identifiers (record 1020) */
typedef struct s7kr_sonarinstallationids_struct {
	s7k_header header;
	unsigned int system_id;     /* Sonar ID */
	unsigned int tx_id;         /* Tx Unid ID */
	unsigned int rx_id;         /* Rx Unid ID */
	unsigned int std_id;        /* 0=Custom, otherwise all parameters */
	                            /* bellow are ignored */
	unsigned int conf_pars;     /* Defines configuration defined parameters */
	                            /* Bit field, 1 = fixed
	                               Bit 0-2: Tx to Rx XYZ Linear Offsets
	                               Bit 3-5: Tx to Reference XYZ Linear Offsets
	                               Bit 6-8: Tx to Rx Angular Offsets
	                               Bit 9-15: Reserved */
	float tx_length;            /* Y measured value of Tx hardware (meters) */
	float tx_width;             /* X measured value of Tx hardware (meters) */
	float tx_height;            /* Z measured value of Tx hardware (meters) */
	float tx_radius;            /* Flat arrays set to 0 */
	float offset_srp2tx_x;      /* X linear offset from SRP to center of Tx (meters) */
	float offset_srp2tx_y;      /* Y linear offset from SRP to center of Tx (meters) */
	float offset_srp2tx_z;      /* Z linear offset from SRP to center of Tx (meters) */
	float offset_tx_roll;       /* Angular offsets from array main axis to */
	float offset_tx_pitch;      /*   motion axes in Lagrange coordinates (radians) */
	float offset_tx_yaw;        /*  */
	float rx_length;            /* Y measured value of Rx hardware (meters) */
	float rx_width;             /* X measured value of Rx hardware (meters) */
	float rx_height;            /* Z measured value of Rx hardware (meters) */
	float rx_radius;            /* Flat arrays set to 0 */
	float offset_srp2rx_x;      /* X linear offset from SRP to center of Rx (meters) */
	float offset_srp2rx_y;      /* Y linear offset from SRP to center of Rx (meters) */
	float offset_srp2rx_z;      /* Z linear offset from SRP to center of Rx (meters) */
	float offset_rx_roll;       /* Angular offsets from array main axis to */
	float offset_rx_pitch;      /*   motion axes in Lagrange coordinates (radians) */
	float offset_rx_yaw;        /*  */
	float frequency;            /* System frequency */
	float offset_vrp2srp_x;     /* X linear offset from VRP to SRP (meters) */
	float offset_vrp2srp_y;     /* Y linear offset from VRP to SRP (meters) */
	float offset_vrp2srp_z;     /* Z linear offset from VRP to SRP (meters) */
	unsigned int cable_length;  /* Cable length (meters) for DMPA systems, 0 when no set */
	char reserved[44];          /* Reserved field */
} s7kr_sonarinstallationids;

/* Sonar Pipe Environment (record 2004) */
typedef struct s7kr_sonarpipeenvironment_struct {
	s7k_header header;
	unsigned int pipe_number;       /* Pipe identifier */
	s7k_time s7kTime;               /* 7KTIME               u8*10   UTC.*/
	unsigned int ping_number;       /* Sequential number */
	unsigned int multiping_number;  /* Sub number */
	float pipe_diameter;            /* Diameter of pipe (meters) */
	float sound_velocity;           /* Sound velocity (m/s) */
	float sample_rate;              /* Sonar's sampling frequency (Hertz) */
	mb_u_char finished;             /* 0 = Pipe is still growing, otherwise is finished */
	unsigned int points_number;     /* Number of point sub records, always 5 (five) */
	unsigned int n;                 /* Size of sub record */
	unsigned int reserved[10];      /* Reserved field */
	int nalloc;                     /* number of samples allocated */
	float *x;                       /* X coordinate in sonar space (meters) */
	float *y;                       /* Y coordinate in sonar space (meters) */
	float *z;                       /* Z coordinate in sonar space (meters) */
	float *angle;                   /* Point angle (radians) */
	float *sample_number;           /* Sample number */
} s7kr_sonarpipeenvironment;

/* Contact Output (record 3001) */
typedef struct s7kr_contactoutput_struct {
	s7k_header header;
	unsigned int target_id;      /* Contact unique ID */
	unsigned int ping_number;    /* Sequential number */
	s7k_time s7kTime;            /* 7KTIME               u8*10   UTC.*/
	char operator[128];          /* Optional textual name of the operator */
	unsigned int contact_state;  /* 0 = created; 1 = modified; 2 = deleted */
	float range;                 /* Range from sonar to contact (meters) */
	float bearing;               /* Bearing from sonar to contact (meters) */
	unsigned int info_flags;     /* Bit field
	                                Bit 0: Set to 1 if latitude and longitude fields
	                                  contain valid values
	                                Bit 1: Set to 1 if azimuth field contains a valid
	                                  value
	                                Bit 2: Set to 1 if contact length field contains
	                                  a valid value
	                                Bit 3: Set to 1 if latitude and longitude fields
	                                  contain valid values */
	double latitude;             /* Latitude of contact in radians (-pi/2 to pi/2),
	                                south negative */
	double longitude;            /* Latitude of contact in radians (-pi/2 to pi/2),
	                                west negative */
	float azimuth;               /* Optional azimuth of contact (radians) */
	float contact_length;        /* Optional length of contact (radians) */
	float contact_width;         /* Optional azimuth of contact (radians) */
	char classification[128];    /* Optional textual classification given by the operator */
	char description[128];       /* Optional textual description given by the operator */
} s7kr_contactoutput;

/* Processed sidescan - MB-System extension to 7k format (record 3199) */
typedef struct s7kr_processedsidescan_struct {
	s7k_header header;
	mb_u_long serial_number;                    /* Sonar serial number */
	unsigned int ping_number;                   /* Sequential number */
	unsigned short multi_ping;                  /* Flag to indicate multi-ping mode
	                                    0 = no multi-ping
	                                    >0 = sequence number of ping
	                                        in the multi-ping
	                                        sequence */
	unsigned short recordversion;               /* allows for progression of versions of this data record
	                                                version = 1: initial version as of 8 October 2012 */
	unsigned int ss_source;                     /* Source of raw backscatter for this sidescan that has
	                                                been laid out on the seafloor:
	                                                    ss_source = 0:     None
	                                                    ss_source = 1:     Non-Reson sidescan
	                                                    ss_source = 7007:  7kBackscatterImageData
	                                                    ss_source = 7008:  7kBeamData
	                                                    ss_source = 7028:  7kV2SnippetData
	                                                    ss_source = 7058:  7kCalibratedSnippetData */
	unsigned int number_pixels;                 /* Number of sidescan pixels across the entire swath */
	unsigned int ss_type;                       /* indicates if sidescan values are logarithmic or linear
	                                                            ss_type = 0: logarithmic (dB)
	                                                            ss_type = 1: linear (voltage) */
	float pixelwidth;                           /* Pixel acrosstrack width in m
	                                                                Acrosstrack distance of each pixel given by
	                                                                    acrosstrack = (ipixel - number_pixels / 2) * pixelwidth
	                                                                where i = pixel number and N is the total number
	                                                                of pixels, counting from port to starboard starting at 0 */
	double sonardepth;                          /* Sonar depth in m */
	double altitude;                            /* Sonar nadir altitude in m */
	float sidescan[MBSYS_RESON7K_MAX_PIXELS];   /* Depth releative to chart datum in meters */
	float alongtrack[MBSYS_RESON7K_MAX_PIXELS]; /* Alongtrack distance in meters */
} s7kr_processedsidescan;

/* Reson 7k volatile sonar settings (record 7000) */
typedef struct s7kr_volatilesettings_struct {
	s7k_header header;
	unsigned double serial_number;    /* Sonar serial number */
	unsigned int ping_number;         /* Ping number */
	unsigned short multi_ping;        /* Flag to indicate multi-ping mode.
	                                     0 = no multi-ping
	                                    >0 = sequence number of the ping in the multi-ping sequence. */
	float frequency;                  /* Transmit frequency (Hertz) */
	float sample_rate;                /* Sample rate (Hertz) */
	float receiver_bandwidth;         /* Receiver bandwidth (Hertz) */
	float tx_pulse_width;             /* Transmit pulse length (seconds) */
	unsigned int tx_pulse_type;       /* Pulse type identifier:
	                                     0 - CW
	                                     1 - linear chirp */
	unsigned int tx_pulse_envelope;   /* Pulse envelope identifier:
	                                     0 - tapered rectangular
	                                     1 - Tukey
	                                     2 - Hamming
	                                     3 - Han
	                                     4 - Rectangular */
	float tx_pulse_envelope_par;      /* Some envelopes don't use this parameter */
	unsigned int tx_pulse_mode;       /* 1 - Single ping
	                                     2 - Multi-ping 2
	                                     3 - Multi-ping 3
	                                     4 - Multi-ping 4 */
	float max_ping_rate;              /* Maximum ping rate (pings/second) */
	float ping_period;                /* Time since last ping (seconds) */
	float range_selection;            /* Range selection (meters) */
	float power_selection;            /* Power selection (dB/uPa) */
	float gain_selection;             /* Gain selection (dB) */
	unsigned int control_flags;       /* Control flags bit field:
	                                     Bit 0-3: Auto range method
	                                     Bit 4-7: Auto bottom detect filter method
	                                     Bit   8: Bottom detection range filter enabled
	                                     Bit   9: Bottom detect depth filter enabled
	                                     Bit  10: Receiver gain method Auto Gain
	                                     Bit  11: Receiver gain method Fixed Gain
	                                     Bit  12: Receiver gain method Reserved
	                                     Bit  13: Reserved
	                                     Bit  14: Trigger out High for entire RX duration
	                                              0 - disabled
	                                              1 - enabled
	                                     Bit  15: 
	                                              0 - system inactive
	                                              1 - active
	                                     Bit16-19: Reserved for bottom detection
	                                     Bit   20: Pipe gating filter
	                                               0 - Disabled
	                                               1 - Enabled
	                                     Bit   21: Adaptive gate depth filter fixed
	                                               0 - Follow seafloor
	                                               1 - Fix depth
	                                     Bit   22: Adaptive gate
	                                               0 - Disabled
	                                               1 - Enabled
	                                     Bit   23: Adaptive gate depth filter
	                                               0 - Disabled
	                                               1 - Enabled
	                                     Bit   24: Trigger out
	                                               0 - Disabled
	                                               1 - Enabled
	                                     Bit   25: Trigger in edge
	                                               0 - Positive
	                                               1 - Negative
	                                     Bit   26: PPS edge
	                                               0 - Positive
	                                               1 - Negative
	                                     Bit27-28: Timestamp State
	                                               0 - Timestamp not applicable
	                                               1 - Timestamp error/not valid
	                                               2 - Timestamp warning/use caution
	                                               3 - Timestamp ok/valid
	                                     Bit   29: Depth filter follows seafloor
	                                               0 - Fix depth
	                                               1 - Follow seafloor
	                                     Bit   30: Reduced coverage for constant spacing
	                                               0 - Always maintain swath coverage
	                                               1 - Allow swath coverage to be reduced
	                                     Bit   31: 
	                                               0 - 7K
	                                               1 - Simulator */
	unsigned int projector_magic_no;  /* Projector selection */
	float steering_vertical;          /* Projector steering angle vertical (radians) */
	float steering_horizontal;        /* Projector steering angle horizontal (radians) */
	float beamwidth_vertical;         /* Projector -3 dB beamwidth vertical (radians) */
	float beamwidth_horizontal;       /* Projector -3 dB beamwidth horizontal (radians) */
	float focal_point;                /* Projector focal point (meters) */
	unsigned int projector_weighting; /* Projector beam weighting window type:
	                                     0 - rectangular
	                                     1 - Chebyshev
	                                     2 - Gauss */
	float projector_weighting_par;    /* Projector beam weighting window parameter */
	unsigned int transmit_flags;      /* Transmit flags bitfield:
	                                     Bit 0-3: Pitch stabilization method
	                                     Bit 4-7: Yaw stabilization method
	                                     Bit8-31: Reserved */
	unsigned int hydrophone_magic_no; /* Hydrophone selection (magic number) */
	unsigned int receive_weighting;   /* Receiver beam weighting window type:
	                                     0 - Chebyshev
	                                     1 - Kaiser */
	float receive_weighting_par;      /* Receiver beam weighting window parameter */
	unsigned int receive_flags;       /* Receive flags bit field:
	                                     Bit    0: Roll compensation indicator
	                                     Bit    1: Reserved
	                                     Bit    2: Heave compensation indicator
	                                     Bit    3: Reserved
	                                     Bit  4-7: Dynamic focusing method
	                                     Bit 8-11: Doppler compensation method
	                                     Bit12-15: Match filtering method
	                                     Bit16-19: TVG method
	                                     Bit20-23: Multi-ping mode
	                                               0 - No multi-ping
	                                               If non-zero, this represents the sequence
	                                               number of the ping in the multi-ping
	                                               sequence.
	                                     Bit24-31: Reserved */
	float receive_width;         /* Receive beam width (radians) */
	float range_minimum;         /* Bottom detection minimum range (meters) */
	float range_maximum;         /* Bottom detection maximum range (meters) */
	float depth_minimum;         /* Bottom detection minimum depth (meters) */
	float depth_maximum;         /* Bottom detection maximum depth (meters) */
	float absorption;            /* Absorption (dB/km) */
	float sound_velocity;        /* Sound velocity (meters/second) */
	float spreading;             /* Spreading loss (dB) */
	unsigned short reserved;     /* reserved for future pulse shape description */
} s7kr_volatilesettings;

/* Reson 7k device configuration structure */
typedef struct s7k_device_struct {
	unsigned int magic_number;      /* Unique identifier number */
	char description[60];           /* Device description string */
	unsigned int alphadata_card;    /* Data card definition:
	                                   0x0400 - Virtex 2 card
	                                   0x0800 - Virtex 5 card
	                                   0x1000 - Virtex 6 card */
	unsigned double serial_number;  /* Device serial number */
	unsigned int info_length;       /* Length of device specific data (bytes) */
	unsigned int info_alloc;        /* Memory allocated for data (bytes) */
	char *info;                     /* Device specific data */
} s7k_device;

/* Reson 7k configuration (record 7001) */
typedef struct s7kr_configuration_struct {
	s7k_header header;
	unsigned double serial_number;               /* Sonar serial number */
	unsigned int number_devices;                 /* Number of devices */
	s7k_device device[MBSYS_RESON7K_MAX_DEVICE]; /* Device configuration information */
} s7kr_configuration;

/* Reson 7k match filter (record 7002) */
typedef struct s7kr_matchfilter_struct {
	s7k_header header;
	unsigned double serial_number;  /* Sonar serial number */
	unsigned int ping_number;       /* Sequential number */
	unsigned int operation;         /* Operation
	                                   0 = off
	                                   1 = on */
	float start_frequency;          /* Start frequency (Hz) */
	float end_frequency;            /* End frequency (Hz) */
	unsigned int window_type        /* 0 - Rectangular
	                                   1 - Kaiser
	                                   2 - Hamming
	                                   3 - Blackmann
	                                   4 - Triangular
	                                   5 - X (Taylor) */
	float shading;                  /* Shading value */
	float pulse_width;              /* Effective pulse width after FM compression */
	unsigned int reserved[13]       /* Filled with 0xFB */
} s7kr_matchfilter;

/* Reson 7k firmware and hardware configuration (record 7003) */
typedef struct s7kr_firmwarehardwareconfiguration_struct {
	s7k_header header;
	unsigned int device_count; /* Hardware device count */
	unsigned int info_length;  /* Info length (bytes) */
	unsigned int info_alloc;   /* Memory allocated for data (bytes) */
	char *info;                /* Device specific data */
} s7kr_firmwarehardwareconfiguration;

/* Reson 7k beam geometry (record 7004) */
typedef struct s7kr_beamgeometry_struct {
	s7k_header header;
	unsigned double serial_number;                        /* Sonar serial number */
	unsigned int number_beams;                            /* Number of receiver beams */
	float angle_alongtrack[MBSYS_RESON7K_MAX_BEAMS];      /* Receiver beam X direction angle (radians) */
	float angle_acrosstrack[MBSYS_RESON7K_MAX_BEAMS];     /* Receiver beam Y direction angle (radians) */
	float beamwidth_alongtrack[MBSYS_RESON7K_MAX_BEAMS];  /* Receiver beamwidth X (radians) */
	float beamwidth_acrosstrack[MBSYS_RESON7K_MAX_BEAMS]; /* Receiver beamwidth Y (radians) */
	float tx_delay;                                       /* Tx delay for the beam in fractional samples,
	                                                         zero when not applicable.
	                                                         Up to now Tx Delay is only supported for the
	                                                         Hydrosweep sonars.
	                                                         When the sonar does not has Tx Delay the item
	                                                         will not be in the Record Data, check record
	                                                         length in the Data Record Frame. */
} s7kr_beamgeometry;

/* Reson 7k bathymetry (record 7006) */
typedef struct s7kr_bathymetrydata_struct {
	s7k_header header;
	unsigned double serial_number;  /* Sonar serial number */
	unsigned int ping_number;       /* Sequential number */
	unsigned short multi_ping;      /* Flag to indicate multi-ping mode
	                                   0 = no multi-ping
	                                  >0 = sequence number of ping in the multi-ping sequence */
	unsigned int number_beams;      /* Number of receiver beams */
	mb_u_char layer_comp_flag;      /* Bit field:
	                                   Bit   0: Layer compensation
	                                   0 = off
	                                   1 = on
	                                   Bit   1: XYZ compensation
	                                   0 = off
	                                   1 = on
	                                   Bit 2-7: Reserved (always 0) */
	mb_u_char sound_vel_flag;       /* Flag indicating if sound velocity is measured or manually entered
	                                   0 = measured
	                                   1 = manually entered */
	float sound_velocity;           /* Sound veocity at the sonar (m/sec) */
	float range[MBSYS_RESON7K_MAX_BEAMS]; /* Two way travel time (seconds) */
	mb_u_char quality[MBSYS_RESON7K_MAX_BEAMS]; /* Beam quality bitfield:
	                                               Bit 0: Brightness test
	                                               1 - Pass
	                                               0 - Fail
	                                               Bit 1: Colinearity test
	                                               1 - Pass
	                                               0 - Fail
	                                               Bit 2: Bottom detection process (magnitude)
	                                               1 - Used
	                                               0 - Not used
	                                               Bit 3: Bottom detection process (phase)
	                                               1 - Used
	                                               0 - Not used
	                                               Bit 4: Used internally
	                                               Bit 5: PDS nadir filter
	                                               1 - Fail
	                                               0 - Pass
	                                               Bit 6-7: Reserved */
	float intensity[MBSYS_RESON7K_MAX_BEAMS];   /* Intensity: Bottom reflectivity. This is a relative
	                                               value (not calibrated) */
	float min_depth_gate[MBSYS_RESON7K_MAX_BEAMS];  /* Minimum two-way travel time to filter point
	                                                   for each beam (minimum depth gate) */
	float max_depth_gate[MBSYS_RESON7K_MAX_BEAMS];  /* Maximum two-way travel time to filter point
	                                                for each beam (maximum depth gate) */
	unsigned int optionaldata;                  /* Flag indicating if bathymetry calculated and
	                                               values below filled in
	                                               0 = No
	                                               1 = Yes
	                                               This is an internal MB-System flag, not
	                                               a value in the data format */
	float frequency;                            /* Ping frequency in Hz */
	double latitude;                            /* Latitude of vessel reference point
	                                               in radians, -pi/2 to +pi/2, south negative */
	double longitude;                           /* Longitude of vessel reference point
	                                               in radians, -pi to +pi, west negative */
	float heading;                              /* Heading of vessel at transmit time
	                                               in radians */
	unsigned char height_source;                /* Method used to correct to chart datum.
	                                               0 = None
	                                               1 = RTK (implies tide = 0.0)
	                                               2 = Tide */
	float tide;                                 /* Tide in meters */
	float roll;                                 /* Roll at transmit time */
	float pitch;                                /* Pitch at transmit time */
	float heave;                                /* Heave at transmit time in m*/
	float vehicle_height;                       /* Vehicle height at transmit time in m */
	float depth[MBSYS_RESON7K_MAX_BEAMS];       /* Depth releative to chart datum in meters */
	float alongtrack[MBSYS_RESON7K_MAX_BEAMS];  /* Alongtrack distance in meters */
	float acrosstrack[MBSYS_RESON7K_MAX_BEAMS];    /* Acrosstrack distance in meters */
	float pointing_angle[MBSYS_RESON7K_MAX_BEAMS]; /* Pointing angle from vertical in radians */
	float azimuth_angle[MBSYS_RESON7K_MAX_BEAMS];  /* Azimuth angle in radians */

	int acrossalongerror;     /* MB-System flipped the order of the alongtrack
	                           * and acrosstrack distance values through 4.3.2003
	                           * - if acrossalongerror == MB_MAYBE check max values of
	                           *       the acrosstrack and alongtrack arrays and treat the larger
	                           *       as acrosstrack - if this is found to be the case ten
	                           *       times then set acrossalongerro = MB_YES and always flip
	                           *       the values - if this is found to not be the case ten
	                           *       times then set acrossalongerror = MB_NO and never flip
	                           *       the values. */
	int nacrossalongerroryes; /* counter for times acrosstrack and alongtrack values flipped */
	int nacrossalongerrorno;  /* counter for times acrosstrack and alongtrack values not flipped */
} s7kr_bathymetrydata;

/* Reson 7k Side Scan Data (record 7007) */
typedef struct s7kr_sidescandata_struct {
	s7k_header header;
	unsigned double serial_number;  /* Sonar serial number */
	unsigned int ping_number;       /* Sequential number */
	unsigned short multi_ping;      /* Flag to indicate multi-ping mode
	                                   0 = no multi-ping
	                                  >0 = sequence number of ping in the multi-ping sequence */
	float beam_position;            /* Beam position forward from position of beam 0 (meters) */
	unsigned int control_flags;     /* Control flags bitfield
	                                   Bit 0: Nadir depth record field used
	                                   Bit 1-31: Reserved */
	unsigned int number_samples;    /* number of samples */
	unsigned int nadir_depth;       /* Nadir depth in samples */n
	float port_beamwidth_x;         /* Port -3 dB X beamwidth (radians - typically a large angle) */
	float port_beamwidth_y;         /* Port -3 dB Y beamwidth (radians - typically a small angle) */
	float stbd_beamwidth_x;         /* Starboard -3 dB X beamwidth
	                                   (radians - typically a large angle) */
	float stbd_beamwidth_y;         /* Starboard -3 dB Y beamwidth
	                                   (radians - typically a small angle) */
	float port_steering_x;          /* Port -3 dB X steering angle
	                                   (radians - typically slightly positive) */
	float port_steering_y;          /* Port -3 dB Y steering angle
	                                   (radians - typically pi) */
	float stbd_steering_x;          /* Starboard -3 dB X steering angle
	                                   (radians - typically slightly positive) */
	float stbd_steering_y;          /* Starboard -3 dB Y steering angle
	                                   (radians - typically zero) */
	unsigned short number_beams;    /* Number of sidescan beams per side (usually only one) */
	unsigned short current_beam;    /* Beam number of this record (0 to number_beams - 1) */
	mb_u_char sample_size;          /* Number of bytes per sample, 1, 2 or 4 */
	mb_u_char data_type;            /* Data type bitfield:
	                                   Bit 0: Reserved (always 0)
	                                   Bit 1-7: Phase */
	unsigned int nalloc;            /* Memory allocated in each array (bytes) */
	char *port_data;
	char *stbd_data;
	unsigned int optionaldata;      /* Flag indicating if values below filled in
	                                   0 = No
	                                   1 = Yes
	                                   This is an internal MB-System flag, not
	                                   a value in the data format */
	float frequency;                /* Ping frequency in Hz */
	double latitude;                /* Latitude of vessel reference point
	                                   in radians, -pi/2 to +pi/2 */
	double longitude;               /* Longitude of vessel reference point
	                                   in radians, -pi to +pi */
	float heading;                  /* Heading of vessel at transmit time
	                                   in radians */
	float altitude;                 /* Altitude in meters for slant range correction */
	float depth;                    /* Nadir depth for slant range correction in meters */
} s7kr_sidescandata;

/* Reson 7k Generic Water Column data (record 7008) */
typedef struct s7kr_watercolumndata_struct {
	s7k_header header;
	unsigned double serial_number;  /* Sonar serial number */
	unsigned int ping_number;       /* Sequential number */
	unsigned short multi_ping;      /* Flag to indicate multi-ping mode
	                                   0 = no multi-ping
	                                  >0 = sequence number of ping in the multi-ping sequence */
	unsigned int number_beams;      /* Number of receiver beams */
	unsigned short reserved;        /* Reserved record */
	unsigned int samples;           /* Samples per ping */
	mb_u_char subset_flag;          /* Bit field: 
	                                   Bit 0:
	                                   0 - all beams and samples in ping
	                                   1 - beam and/or sample ping subset
	                                   Bit 1: 
	                                   0 - aample ping subset
	                                   1 - beam ping subset */
	mb_u_char subset_flag;          /* 0 - All samples for a beam, followed by all 
	                                   samples for the next beam
	                                   1 - Sample 1 for all beams, followed by Sample 2
	                                   for all beams, etc */
	unsigned short reserved2;       /* Reserved record */
	unsigned int sample_type;       /* Bit field:
	                                   Least significant bit corresponds to Bit 0. Each grouping
	                                   of bits is to be treated as an unsigned integer of the
	                                   specified width. E.g. magnitude is u4 with possible
	                                   values in the range 0 to 16
	                                   Bit   0-3: Magnitude
	                                   0 - no magnitude
	                                   1 - reserved
	                                   2 - magnitude (16 bits)
	                                   3 - magnitude (32 bits)
	                                   Bit   4-7: Phase
	                                   0 - no phase
	                                   1 - reserved
	                                   2 - phase (16 bits)
	                                   3 - phase (32 bits)
	                                   Bit  8-11: I and Q
	                                   0 - no I and Q
	                                   1 - signed 16 bit and signed 16 bit Q
	                                   2 - signed 32 bit and signed 32 bit Q
	                                   Bit 12-14: Beamforming flag
	                                   0 - Beam formed data
	                                   1 - Element data*/
	/* 
	to be continued...
	*/
} s7kr_watercolumndata;

/* Reson 7k tvg data (record 7010) */
typedef struct s7kr_tvg_struct {
	s7k_header header;
	unsigned double serial_number;  /* Sonar serial number */
	unsigned int ping_number;       /* Sequential number */
	unsigned short multi_ping;      /* Flag to indicate multi-ping mode
	                                   0 = no multi-ping
	                                  >0 = sequence number of ping in the multi-ping sequence */
	unsigned int n;                 /* number of samples */
	unsigned int reserved[8];       /* Reserved records */
	unsigned int nalloc;            /* Number of bytes allocated to tvg array */
	void *tvg;                      /* Array of tvg data */
} s7kr_tvg;

/* Reson 7k image data (record 7011) */
typedef struct s7kr_imagedata_struct {
	s7k_header header;
	unsigned int ping_number;         /* Sequential number */
	unsigned short multi_ping;        /* Flag to indicate multi-ping mode
	                                     0 = no multi-ping
	                                    >0 = sequence number of ping in the multi-ping sequence */
	unsigned int width;               /* Image width in pixels */
	unsigned int height;              /* Image height in pixels */
	unsigned short color_depth;       /* Color depth per pixel in bytes */
	unsigned short reserved;          /* Reserved record */
	unsigned short compression;       /* Reserved for future use */
	unsigned int n;                   /* Original samples prior to compression */
	unsigned int flag;                /* Bit field:
	                                     Bit 0: dB visualization
	                                     Bit 1: Un-stabilized beams */
	float rx_delay;                   /* Rx delay in fractional samples, zero when not applicable. */
	unsigned int reserved[6];         /* Reserved record */
	unsigned int nalloc;              /* Number of bytes allocated to image array */
	void *image;                      /* Array of image data */
} s7kr_imagedata;

/* Reson 7k Ping Motion (record 7012) */
typedef struct s7kr_pingmotiondata_struct {
	s7k_header header;
	mb_u_long serial_number;    /* Sonar serial number */
	unsigned int ping_number;   /* Sequential number */
	unsigned short multi_ping;  /* Flag to indicate multi-ping mode
	                               0 = no multi-ping
	                              >0 = sequence number of ping in the multi-ping sequence */
	unsigned int n;            /* number of samples */
	unsigned short flags;      /* Bit field:
	                              Bit 0: Pitch stabilization applied / pitch field present
	                              Bit 1: Roll stabilization applied / roll field present
	                              Bit 2: Yaw stabilization applied / yaw field present
	                              Bit 3: Heave stabilization applied / heave field present
	                              Bit 4-15: Reserved */
	unsigned int error_flags;  /* Bit field:
	                              Bit 0: PHINS reference 0 = invalid, 1 = valid
	                              Bit 1-3: Reserved for PHINS
	                              Bit 4: Roll angle > 15 degrees
	                              Bit 5: Pitch angle > 35 degrees
	                              Bit 6: Roll rate > 10 degrees
	                              Bit 7: 1 = External motion data not received (roll
	                              angle and rate are not reported)
	                              Bit 8-15: Reserved */
	float frequency;           /* sampling frequency (Hz) */
	float pitch;               /* Pitch value at the ping time (radians) */
	int nalloc;                /* number of samples allocated */
	float *roll;               /* Roll (radians) */
	float *heading;            /* Heading (radians) */
	float *heave;              /* Heave (m) */
} s7kr_pingmotiondata;

/* Reson 7k Adaptive Gate (record 7014) */
typedef struct s7kr_adaptivegate_struct {
	s7k_header header;
	unsigned int record_size;       /* Size of record header in bytes */
	unsigned double serial_number;  /* Sonar serial number */
	unsigned int ping_number;       /* Sequential number */
	unsigned short multi_ping;      /* Flag to indicate multi-ping mode
	                                   0 = no multi-ping
	                                  >0 = sequence number of ping in the multi-ping sequence */
	unsigned int n;                 /* Number of gate descriptors */
	unsigned short gate_size;       /* Size of gate descriptor information block in bytes */
	unsigned int nalloc;            /* Memory allocated for data (bytes) */
	float *angle;                   /* Gate angle (radians) */
	float *min_limit;               /* Minimum sample number of gate limit */
	float *max_limit;               /* Maximum sample number of gate limit*/
} s7kr_adaptivegate;

/* Reson 7k Detection Setup (record 7017) */
typedef struct s7kr_detectiondatasetup_struct {
	s7k_header header;
	unsigned double serial_number;     /* Sonar serial number */
	unsigned int ping_number;          /* Sequential number */
	unsigned short multi_ping;         /* Flag to indicate multi-ping mode 0 = no multi-ping
	                                      >0 = sequence number of ping in the multi-ping sequence */
	unsigned int number_beams;         /* Number of detection points */
	unsigned int data_block_size;      /* Size of detection information block in bytes */
	mb_u_char detection_algorithm;     /* Detection algorithm:
	                                      0 = G1_Simple
	                                      1 = G1_BlendFilt
	                                      2 = G2
	                                      3 = G3
	                                      4 = IF1
	                                      5 = PS1 (beam detection)
	                                      6 = HS1 (beam detection)
	                                      7 = HS2 (pseudo beam detection)
	                                      8-255 = Reserved for future use */
	unsigned int detection_flags;      /* Bit field:
	                                      Bit 0: 1 = User-defined depth filter enabled
	                                      Bit 1: 1 = User-defined range filter enabled
	                                      Bit 2: 1 = Automatic filter enabled
	                                      Bit 3: 1 = Nadir search limits enabled
	                                      Bit 4: 1 = Automatic window limits enabled
	                                      Bit 5: 1 = Quality filter enabled
	                                      Bit 6: 1 = Multi detection enabled
	                                      Bits 7-31: Reserved for future use */
	float minimum_depth;               /* Minimum depth for user-defined filter (meters) */
	float maximum_depth;               /* Maximum depth for user-defined filter (meters) */
	float minimum_range;               /* Minimum range for user-defined filter (meters) */
	float maximum_range;               /* Maximum range for user-defined filter (meters) */
	float minimum_nadir_search;        /* Minimum depth for automatic filter nadir search (meters) */
	float maximum_nadir_search;        /* Maximum depth for automatic filter nadir search (meters) */
	mb_u_char automatic_filter_window; /* Automatic filter window size (percent depth) */
	float applied_roll;                /* Roll value (in radians) applied to gates; 
	                                      zero if roll stabilization is on */
	float depth_gate_tilt;             /* Angle in radians (positive to starboard) */
	float nadir_depth;                 /* Nadir depth used mb MB2 */
	float reserved[13];                /* Reserved for future use */
	unsigned short beam_descriptor[MBSYS_RESON7K_MAX_BEAMS];
	                                   /* Beam number the detection is taken from */
	float detection_point[MBSYS_RESON7K_MAX_BEAMS];
	                                   /* Non-corrected fractional sample number with
	                                      the reference to the receiver's acoustic center 
	                                      with the zero sample at the transmit time */
	unsigned int flags[MBSYS_RESON7K_MAX_BEAMS];
	                                   /* Bit field:
	                                      Bit 0: 1 = automatic limits valid
	                                      Bit 1: 1 = User-defined limits valid
	                                      Bit 2-8: Quality type, defines the type of the quality field
	                                      Bit 9: 1 = Quality passes user-defined criteria
	                                      or no user-defined criteria was specified
	                                      Bit 10-12: Detection type (1 or more of the following)
	                                        Bit 10: Magnitude based detection
	                                        Bit 11: Phase based detection
	                                        Bit 12: Reserved
	                                      Bit 13-15: Reserved for future use
	                                      Bit 16-19: Detection priority number for detections
	                                      within the same beam (Multi-detect only). Value zero is
	                                      highest priority */
	unsigned int auto_limits_min_sample[MBSYS_RESON7K_MAX_BEAMS];
	                                   /* Minimum sample number for automatic limits */
	unsigned int auto_limits_max_sample[MBSYS_RESON7K_MAX_BEAMS];
	                                   /* Maximum sample number for automatic limits */
	unsigned int user_limits_min_sample[MBSYS_RESON7K_MAX_BEAMS];
	                                   /* Minimum sample number for user-defined limits */
	unsigned int user_limits_max_sample[MBSYS_RESON7K_MAX_BEAMS];
	                                   /* Maximum sample number for user-defined limits */
	unsigned int quality[MBSYS_RESON7K_MAX_BEAMS]; /* Bit field:
	                                                  Bit 0: 1 = Brightness filter passed
	                                                  Bit 1: 1 = Colinearity filter passed
	                                                  Bit 2-31: Reserved for future use */
	float uncertainty[MBSYS_RESON7K_MAX_BEAMS];
	                                   /* Detection uncertainty represented as an error 
	                                   normalized to the detection point */
} s7kr_detectiondatasetup;

/* Reson 7k amplitude and phase data (part of record 7018) */
typedef struct s7kr_amplitudephase_struct {
	unsigned short beam_number;  /* Beam or element number */
	unsigned int number_samples; /* Number of samples */
	unsigned int nalloc;         /* Number of samples allocated */
	unsigned short *amplitude;   /* Amplitude time series  */
	short *phase;                /* Phase time series (radians scaled by 10430) */
} s7kr_amplitudephase;

/* Reson 7k Beamformed Data (record 7018) */
typedef struct s7kr_beamformeddata_struct {
	s7k_header header;
	unsigned double serial_number;  /* Sonar serial number */
	unsigned int ping_number;       /* Sequential number */
	unsigned short multi_ping;      /* Flag to indicate multi-ping mode
	                                   0 = no multi-ping
	                                  >0 = sequence number of ping in the multi-ping sequence */
	unsigned short number_beams;    /* Total number of beams or elements in record */
	unsigned int number_samples;    /* Number of samples in each beam in this record */
	unsigned int reserved[8];       /* Reserved for future use */
	s7kr_amplitudephase amplitudephase[MBSYS_RESON7K_MAX_BEAMS];
	                                /* amplitude and phase data for each beam */
} s7kr_beamformeddata;

/* Reson 7k Vernier Processing Data Raw (record 7019) */
typedef struct s7kr_vernierprocessingdataraw_struct {
	s7k_header header;

	CONTINUE HERE <---

} s7kr_vernierprocessingdataraw;

/* Reson 7k BITE field (part of record 7021) */
typedef struct s7kr_v2bitefield_struct {
	unsigned short reserved; /* Reserved */
	char name[64];           /* Name - null terminated ASCII string */
	mb_u_char device_type;   /* Device type:
	                 1 = Error count
	                 2 = FPGA die temperature
	                 3 = Humidity
	                 4 = Serial 8-channel ADC
	                 5 = Firmware version
	                 6 = Head Temp,_8K WetEnd
	                 7 = Leak V,_8K WetEnd
	                 8 = 5 Volt,_8K WetEnd
	                 9 = 12 Volt,_8K WetEnd
	                 10 = DipSwitch,_8K WetEnd */
	float minimum;           /* Minimum value */
	float maximum;           /* Maximum value */
	float value;             /* Current value */
} s7kr_v2bitefield;

/* Reson 7k BITE (part of record 7021) */
typedef struct s7kr_v2bitereport_struct {
	char source_name[64];            /* source name - null terminated string */
	mb_u_char source_address;        /* source address */
	float frequency;                 /* frequency for transmitter or 0 */
	unsigned short enumerator;       /* Enumerator for transmitter or 0 */
	s7k_time downlink_time;          /* Downlink time sent */
	s7k_time uplink_time;            /* Uplink time received */
	s7k_time bite_time;              /* BITE time received */
	mb_u_char status;                /* Bit field:
	                             Bit 0:
	                                 0 = Uplink ok
	                                 1 = Uplink error
	                             Bit 1:
	                                 0 = Downlink ok
	                                 1 = Downlink error
	                             Bit 2:
	                                 0 = BITE ok
	                                 1 = BITE error */
	unsigned short number_bite;      /* Number of valid BITE fields for this board */
	mb_u_char bite_status[32];       /* Each bit delineates status of one BITE channel up to 256:
	                     0 = BITE field within range
	                     1 = BITE field out of range */
	s7kr_v2bitefield bitefield[256]; /* Array of BITE field data */
} s7kr_v2bitereport;

/* Reson 7k BITE (record 7021) */
typedef struct s7kr_v2bite_struct {
	s7k_header header;
	unsigned short number_reports; /* Number of Built In Test Environment reports */
	unsigned int nalloc;
	s7kr_v2bitereport *reports;
} s7kr_v2bite;

/* Reson 7k center version (record 7022) */
typedef struct s7kr_v27kcenterversion_struct {
	s7k_header header;
	char version[32]; /* Null terminated ASCII string */
} s7kr_v27kcenterversion;

/* Reson 7k 8k wet end version (record 7023) */
typedef struct s7kr_v28kwetendversion_struct {
	s7k_header header;
	char version[32]; /* Null terminated ASCII string */
} s7kr_v28kwetendversion;

/* Reson 7k version 2 detection (record 7026) */
typedef struct s7kr_v2detection_struct {
	s7k_header header;
	mb_u_long serial_number;       /* Sonar serial number */
	unsigned int ping_number;      /* Sequential number */
	unsigned short multi_ping;     /* Flag to indicate multi-ping mode
	                       0 = no multi-ping
	                       >0 = sequence number of ping
	                           in the multi-ping
	                           sequence */
	unsigned int number_beams;     /* Number of detection points */
	unsigned int data_field_size;  /* Size of detection information block in bytes */
	mb_u_long corrections;         /* Corrections/Methods bit field:
	                       Bit 0:
	                           1 = Geometrical corrections for
	                               cylindrical arrays applied
	                       Bit 1-2:
	                           0 = Manually entered surface sound velocity used
	                           1 = Measured surface sound velocity used
	                           2,3 = reserved for future use
	                       Bit 3:
	                           1 = Roll stabilization applied
	                       Bit 4:
	                           1 = Pitch stablization applied
	                       Bits 5-63:
	                           Reserved for future use */
	mb_u_char detection_algorithm; /* Detection algorithm:
	                   0 = G1_Simple
	                   1 = G1_BlendFilt
	                   2 = G2
	                   3-255: Reserved for future use */
	unsigned int flags;            /* Bit field:
	                       Bit 0:
	                           1 = Quality filter applied. Only detections
	                               that pass user-defined criteria
	                               are generated.
	                       Bit 1:
	                           1 = Motion error(s) detected. Data may not
	                               be accurate
	                       Bit 2-3: Reference frame
	                           0 = Sonar
	                           1 = Vessel
	                           2-3 = Reserved */
	mb_u_char reserved[64];        /* Reserved for future use */

	float range[MBSYS_RESON7K_MAX_BEAMS];
	/* Two-way travel time to the bottom/target (seconds) */
	float angle_x[MBSYS_RESON7K_MAX_BEAMS];
	/* Across-track angle to detection point (radians) */
	float angle_y[MBSYS_RESON7K_MAX_BEAMS];
	/* Along-track angle to detection point (radians) */
	float range_error[MBSYS_RESON7K_MAX_BEAMS];
	/* Measurement error (seconds) */
	float angle_x_error[MBSYS_RESON7K_MAX_BEAMS];
	/* Measurement error (radians) */
	float angle_y_error[MBSYS_RESON7K_MAX_BEAMS];
	/* Measurement error (radians) */
} s7kr_v2detection;

/* Reson 7k version 2 raw detection (record 7027) */
typedef struct s7kr_v2rawdetection_struct {
	s7k_header header;
	mb_u_long serial_number;       /* Sonar serial number */
	unsigned int ping_number;      /* Sequential number */
	unsigned short multi_ping;     /* Flag to indicate multi-ping mode
	                       0 = no multi-ping
	                       >0 = sequence number of ping
	                           in the multi-ping
	                           sequence */
	unsigned int number_beams;     /* Number of detection points */
	unsigned int data_field_size;  /* Size of detection information block in bytes */
	mb_u_char detection_algorithm; /* Detection algorithm:
	                   0 = G1_Simple
	                   1 = G1_BlendFilt
	                   2 = G2
	                   3-255: Reserved for future use */
	unsigned int detection_flags;  /* Bit field: Bits 0-31: Reserved for future use */
	float sampling_rate;           /* Sonar's sampling frequency in Hz */
	float tx_angle;                /* Applied transmitter steering angle, in radians */
	mb_u_char reserved[64];        /* Reserved for future use */

	unsigned short beam_descriptor[MBSYS_RESON7K_MAX_BEAMS];
	/* Beam number the detection is taken from */
	float detection_point[MBSYS_RESON7K_MAX_BEAMS];
	/* Non-corrected fractional sample number with
	    the reference to the receiver's
	    acoustic center with the zero sample
	    at the transmit time */
	float rx_angle[MBSYS_RESON7K_MAX_BEAMS];
	/* Beam steering angle with reference to
	    receiver's acoustic center in the
	    sonar reference frame, at the detection
	    point, in radians */
	unsigned int flags[MBSYS_RESON7K_MAX_BEAMS];
	/* Bit fields:
	    Bit 0: 1 = Magnitude based detection
	    Bit 1: 1 = Phase based detection
	    Bits 2-8: Quality type, defines the type
	        of the quality field below
	        0: Quality not available / not used
	        1: Quality available
	        2-31: Reserved for future use
	    Bit 9: Uncertainty information is available
	    Bits 10-31: Reserved for future use */
	unsigned int quality[MBSYS_RESON7K_MAX_BEAMS];
	/* Detection quality:
	    Bit 0: 1 = Brightness filter passed
	    Bit 1: 1 = Co-linearity filter passed */
	float uncertainty[MBSYS_RESON7K_MAX_BEAMS];
	/* Detection uncertainty represented as an error
	    normalized to the detection point */
} s7kr_v2rawdetection;

/* Reson 7k version 2 snippet data (part of record 7028) */
typedef struct s7kr_v2snippettimeseries_struct {
	unsigned short beam_number; /* Beam or element number */
	unsigned int begin_sample;  /* First sample included in snippet */
	unsigned int detect_sample; /* Detection point */
	unsigned int end_sample;    /* Last sample included in snippet */
	unsigned int nalloc;        /* Bytes allocated to hold amplitude time series */
	unsigned short *amplitude;  /* Amplitude time series */
} s7kr_v2snippettimeseries;

/* Reson 7k version 2 snippet (record 7028) */
typedef struct s7kr_v2snippet_struct {
	s7k_header header;
	mb_u_long serial_number;     /* Sonar serial number */
	unsigned int ping_number;    /* Sequential number */
	unsigned short multi_ping;   /* Flag to indicate multi-ping mode
	                     0 = no multi-ping
	                     >0 = sequence number of ping
	                         in the multi-ping
	                         sequence */
	unsigned short number_beams; /* Number of detection points */
	mb_u_char error_flag;        /* If set, record will not contain any data
	                         Flag itself will indicate an error:
	                         0 = Ok
	                         6 = Bottom detection failed
	                         Other = reserved */
	mb_u_char control_flags;     /* Control settings from RC 1118 command:
	                     Bit 0: Automatic snippet window is used
	                     Bit 1: Quality filter enabled
	                     Bit 2: Minimum window size is required
	                     Bit 3: Maximum window size is required
	                     Bit 4-7: Reserved */
	mb_u_char reserved[28];      /* Reserved for future use */
	s7kr_v2snippettimeseries snippettimeseries[MBSYS_RESON7K_MAX_BEAMS];
	/* Snippet time series for each beam */
} s7kr_v2snippet;

/* Reson 7k sonar installation parameters (record 7030) */
typedef struct s7kr_installation_struct {
	s7k_header header;
	float frequency;                     /* Sonar frequency (Hz) */
	unsigned short firmware_version_len; /* Length of firmware version info in bytes */
	char firmware_version[128];          /* Firmware version info */
	unsigned short software_version_len; /* Length of software version info in bytes */
	char software_version[128];          /* Software version info */
	unsigned short s7k_version_len;      /* Length of 7k software version info in bytes */
	char s7k_version[128];               /* 7k software version info */
	unsigned short protocal_version_len; /* Length of protocal version info in bytes */
	char protocal_version[128];          /* Protocal version info */
	float transmit_x;                    /* Sonar transmit array X offset (m) */
	float transmit_y;                    /* Sonar transmit array Y offset (m) */
	float transmit_z;                    /* Sonar transmit array Z offset (m) */
	float transmit_roll;                 /* Sonar transmit array roll offset radiansm) */
	float transmit_pitch;                /* Sonar transmit array pitch offset (radians) */
	float transmit_heading;              /* Sonar transmit array heading offset (radians) */
	float receive_x;                     /* Sonar receive array X offset (m) */
	float receive_y;                     /* Sonar receive array Y offset (m) */
	float receive_z;                     /* Sonar receive array Z offset (m) */
	float receive_roll;                  /* Sonar receive array roll offset (radians) */
	float receive_pitch;                 /* Sonar receive array pitch offset (radians) */
	float receive_heading;               /* Sonar receive array heading offset (radians) */
	float motion_x;                      /* Motion sensor X offset (m) */
	float motion_y;                      /* Motion sensor Y offset (m) */
	float motion_z;                      /* Motion sensor Z offset (m) */
	float motion_roll;                   /* Motion sensor roll offset (radians) */
	float motion_pitch;                  /* Motion sensor pitch offset (radians) */
	float motion_heading;                /* Motion sensor heading offset (radians) */
	unsigned short motion_time_delay;    /* Motion sensor time delay (msec) */
	float position_x;                    /* Position sensor X offset (m) */
	float position_y;                    /* Position sensor Y offset (m) */
	float position_z;                    /* Position sensor Z offset (m) */
	unsigned short position_time_delay;  /* Position sensor time delay (msec) */
	float waterline_z;                   /* Vertical offset from reference
	                             point to waterline (m) */
} s7kr_installation;

/* Reson 7k system event (record 7051) */
typedef struct s7kr_systemeventmessage_struct {
	s7k_header header;
	mb_u_long serial_number;         /* Sonar serial number */
	unsigned short event_id;         /* Event id:
	                         0: success
	                         1: information (used for MB-System comment record)
	                         2: warning
	                         3: error */
	unsigned short message_length;   /* Message length in bytes */
	unsigned short event_identifier; /* Undefined */
	unsigned int message_alloc;      /* Number of bytes allocated for message */
	char *message;                   /* Message string (null terminated) */
} s7kr_systemeventmessage;

/* Reson 7k calibrated snippet data (part of record 7058) */
typedef struct s7kr_calibratedsnippettimeseries_struct {
	unsigned short beam_number; /* Beam or element number */
	unsigned int begin_sample;  /* First sample included in snippet */
	unsigned int detect_sample; /* Detection point */
	unsigned int end_sample;    /* Last sample included in snippet */
	unsigned int nalloc;        /* Bytes allocated to hold amplitude time series */
	float *amplitude;           /* Amplitude time series */
} s7kr_calibratedsnippettimeseries;

/* Reson 7k calibrated snippet (record 7058) */
typedef struct s7kr_calibratedsnippet_struct {
	s7k_header header;
	mb_u_long serial_number;     /* Sonar serial number */
	unsigned int ping_number;    /* Sequential number */
	unsigned short multi_ping;   /* Flag to indicate multi-ping mode
	                     0 = no multi-ping
	                     >0 = sequence number of ping
	                         in the multi-ping
	                         sequence */
	unsigned short number_beams; /* Number of detection points */
	mb_u_char error_flag;        /* If set, record will not contain any data
	                         Flag itself will indicate an error:
	                         0 = Ok
	                         1 = No calibration
	                         2 = TVG read error (R7010)
	                         3 = CTD not available (R1010)
	                         4 = Invalid or not available geometry (R7004)
	                         5 = Invalid sonar specifications (XML)
	                         6 = Bottom detection failed (R7006)
	                         7 = No power (Power is set to zero)
	                         8 = No gain (Gain is too low)
	                         255 = System cannot be calibrated (c7k file missing)
	                         Other = reserved */
	unsigned int control_flags;  /* Control settings from RC 1113 command:
	                   Bit 0: Brightness is required to pass
	                   Bit 1: Colinearity is required to pass
	                   Bit 2: Bottom detection results are used for snippet
	                   Bit 3: Snippets display min requirements are used
	                   Bit 4: Minimum window size is required
	                   Bit 5: Maximum window size is required
	                   6-31: reserved */
	mb_u_char reserved[28];      /* Reserved for future use */
	s7kr_calibratedsnippettimeseries calibratedsnippettimeseries[MBSYS_RESON7K_MAX_BEAMS];
	/* Snippet time series for each beam */
} s7kr_calibratedsnippet;

/* Reson 7k subsystem structure */
typedef struct s7kr_subsystem_struct {
	unsigned int device_identifier;   /* Identifier for record type of embedded data */
	unsigned short system_enumerator; /* Identifier for the device subsystem */
} s7kr_subsystem;

/* Reson 7k file header (record 7200) */
typedef struct s7kr_fileheader_struct {
	s7k_header header;
	char file_identifier[16];    /* File identifier:
	                 0xF3302F43CFB04D6FA93E2AEC33DF577D */
	unsigned short version;      /* File format version number */
	unsigned short reserved;     /* Reserved */
	char session_identifier[16]; /* Session identifier - used to associate multiple
	                 files for a given session */
	unsigned int record_data_size;  /* Size of record data - 0 if not set */
	unsigned int number_subsystems; /* Number of subsystems - 0 if not set */
	char recording_name[64];        /* Recording program name - null terminated string */
	char recording_version[16];     /* Recording program version number - null terminated string */
	char user_defined_name[64];     /* User defined name - null terminated string */
	char notes[128];                /* Notes - null terminated string */
	s7kr_subsystem subsystem[MBSYS_RESON7K_MAX_DEVICE];
} s7kr_fileheader;

/* Reson 7k remote control sonar settings (record 7503) */
typedef struct s7kr_remotecontrolsettings_struct {
	s7k_header header;
	mb_u_long serial_number;  /* Sonar serial number */
	unsigned int ping_number; /* Ping number */
	float frequency;          /* Transmit frequency (Hertz) */
	float sample_rate;        /* Sample rate (Hertz) */
	float receiver_bandwidth; /* Receiver bandwidth (Hertz) */
	float pulse_width;        /* Transmit pulse length (seconds) */
	unsigned int pulse_type;  /* Pulse type identifier:
	                  0 - CW
	                  1 - linear chirp */
	unsigned int pulse_envelope; /* Pulse envelope identifier:
	                 0 - tapered rectangular
	                 1 - Tukey */
	float pulse_envelope_par;        /* Pulse envelope parameter */
	unsigned int pulse_reserved;     /* Reserved pulse information */
	float max_ping_rate;             /* Maximum ping rate (pings/second) */
	float ping_period;               /* Time since last ping (seconds) */
	float range_selection;           /* Range selection (meters) */
	float power_selection;           /* Power selection (dB/uPa) */
	float gain_selection;            /* Gain selection (dB) */
	unsigned int control_flags;      /* Control flags bitfield:
	                     0-3: auto range method
	                     4-7: auto bottom detect filter method
	                     8: bottom detect range filter
	                     9: bottom detect depth filter
	                     10-14: auto receiver gain method
	                     15-31: reserved	*/
	unsigned int projector_magic_no; /* Projector selection */
	float steering_vertical;         /* Projector steering angle vertical (radians) */
	float steering_horizontal;       /* Projector steering angle horizontal (radians) */
	float beamwidth_vertical;        /* Projector -3 dB beamwidth vertical (radians) */
	float beamwidth_horizontal;      /* Projector -3 dB beamwidth horizontal (radians) */
	float focal_point;               /* Projector focal point (meters) */
	unsigned int projector_weighting; /* Projector beam weighting window type:
	                  0 - rectangular
	                  1 - Chebyshev */
	float projector_weighting_par;    /* Projector beam weighting window parameter */
	unsigned int transmit_flags;      /* Transmit flags bitfield:
	                      0-3: pitch stabilization method
	                      4-7: yaw stabilization method
	                      8-31: reserved */
	unsigned int hydrophone_magic_no; /* Hydrophone selection (magic number) */
	unsigned int receive_weighting; /* Receiver beam weighting window type:
	                    0 - Chebyshev
	                    1 - Kaiser */
	float receive_weighting_par; /* Receiver beam weighting window parameter */
	unsigned int receive_flags;  /* Receive flags bitfield:
	                 0-3: roll stabilization method
	                 4-7: dynamic focusing method
	                 8-11: doppler compensation method
	                 12-15: match filtering method
	                 16-19: TVG method
	                 20-23: Multi-ping mode
	                     0 = no multi-ping
	                     >0 = sequence number of the ping
	                         in the multi-ping
	                         sequence.
	                 24-31: Reserved */
	float range_minimum;         /* Bottom detection minimum range (meters) */
	float range_maximum;         /* Bottom detection maximum range (meters) */
	float depth_minimum;         /* Bottom detection minimum depth (meters) */
	float depth_maximum;         /* Bottom detection maximum depth (meters) */
	float absorption;            /* Absorption (dB/km) */
	float sound_velocity;        /* Sound velocity (meters/second) */
	float spreading;             /* Spreading loss (dB) */
	unsigned short reserved;     /* reserved for future pulse shape description */

	/* parameters added by version 1.0 */
	float tx_offset_x;          /* Offset of the transducer array in m, relative
	                    to the receiver array on the x axis, positive
	                    value is to the right, if the receiver faces
	                    forward. */
	float tx_offset_y;          /* Offset of the transducer array in m, relative
	                    to the receiver array on the y axis, positive
	                    value is forward, if the receiver faces
	                    forward. */
	float tx_offset_z;          /* Offset of the transducer array in m, relative
	                    to the receiver array on the z axis, positive
	                    value is up, if the receiver faces forward. */
	float head_tilt_x;          /* Head tilt x (radians) */
	float head_tilt_y;          /* Head tilt y (radians) */
	float head_tilt_z;          /* Head tilt z (radians) */
	unsigned short ping_on_off; /* Ping on/off state:
	                0 = pinging disabled
	                1 = pinging enabled */
	mb_u_char data_sample_types;     /* */
	mb_u_char projector_orientation; /* Projector orientation:
	                     0: down
	                     1: up */
	unsigned short beam_angle_mode; /* Beam angle spacing mode:
	                    1: equiangle
	                    2: eqidistant */
	unsigned short r7kcenter_mode; /* 7kCenter mode:
	                   0: normal
	                   1: autopilot
	                   2: calibration (IQ)
	                   3+: reserved */
	float gate_depth_min;          /* Adaptive gate minimum depth */
	float gate_depth_max;          /* Adaptive gate maximum depth */
	unsigned short reserved2[35];
} s7kr_remotecontrolsettings;

/* Reson 7k Reserved (well, unknown really...) (record 7504) */
typedef struct s7kr_reserved_struct {
	s7k_header header;
	mb_u_char reserved[R7KHDRSIZE_7kReserved]; /* raw bytes of unknown record */
} s7kr_reserved;

/* Reson 7k Roll (record 7600) */
typedef struct s7kr_roll_struct {
	s7k_header header;
	float roll; /* Roll (radians) */
} s7kr_roll;

/* Reson 7k Pitch (record 7601) */
typedef struct s7kr_pitch_struct {
	s7k_header header;
	float pitch; /* Pitch (radians) */
} s7kr_pitch;

/* Reson 7k Sound Velocity (record 7610) */
typedef struct s7kr_soundvelocity_struct {
	s7k_header header;
	float soundvelocity; /* Water sound speed (m/s) */
} s7kr_soundvelocity;

/* Reson 7k Absorption Loss (record 7611) */
typedef struct s7kr_absorptionloss_struct {
	s7k_header header;
	float absorptionloss; /* Absorption loss (dB/km) */
} s7kr_absorptionloss;

/* Reson 7k Spreading Loss (record 7612) */
typedef struct s7kr_spreadingloss_struct {
	s7k_header header;
	float spreadingloss; /* dB (0 - 60) */
} s7kr_spreadingloss;

/* internal data structure */
struct mbsys_reson7k_struct {
	/* Type of data record */
	int kind;   /* MB-System record ID */
	int type;   /* Reson record ID */
	int sstype; /* If type == R7KRECID_FSDWsidescan
	            sstype: 0 = low frequency sidescan
	                1 = high frequency sidescan */

	/* ping record id's */
	int current_ping_number;
	int read_volatilesettings;
	int read_matchfilter;
	int read_beamgeometry;
	int read_remotecontrolsettings;
	int read_bathymetry;
	int read_backscatter;
	int read_beam;
	int read_verticaldepth;
	int read_tvg;
	int read_image;
	int read_v2pingmotion;
	int read_v2detectionsetup;
	int read_v2beamformed;
	int read_v2detection;
	int read_v2rawdetection;
	int read_v2snippet;
	int read_calibratedsnippet;
	int read_processedsidescan;

	/* MB-System time stamp */
	double time_d;
	int time_i[7];

	/* Reference point information (record 1000) */
	/*  Note: these offsets should be zero for submersible vehicles */
	s7kr_reference reference;

	/* Sensor uncalibrated offset position information (record 1001) */
	s7kr_sensoruncal sensoruncal;

	/* Sensor calibrated offset position information (record 1002) */
	s7kr_sensorcal sensorcal;

	/* Position (record 1003) */
	s7kr_position position;

	/* Custom attitude (record 1004) */
	s7kr_customattitude customattitude;

	/* Tide (record 1005) */
	s7kr_tide tide;

	/* Altitude (record 1006) */
	s7kr_altitude altitude;

	/* Motion over ground (record 1007) */
	s7kr_motion motion;

	/* Depth (record 1008) */
	s7kr_depth depth;

	/* Sound velocity profile (record 1009) */
	s7kr_svp svp;

	/* CTD (record 1010) */
	s7kr_ctd ctd;

	/* Geodesy (record 1011) */
	s7kr_geodesy geodesy;

	/* Roll pitch heave (record 1012) */
	s7kr_rollpitchheave rollpitchheave;

	/* Heading (record 1013) */
	s7kr_heading heading;

	/* Survey line (record 1014) */
	s7kr_surveyline surveyline;

	/* Navigation (record 1015) */
	s7kr_navigation navigation;

	/* Attitude (record 1016) */
	s7kr_attitude attitude;

	/* Unknown record 1022 (record 1022) */
	s7kr_rec1022 rec1022;

	/* Edgetech FS-DW low frequency sidescan (record 3000) */
	s7kr_fsdwss fsdwsslo;

	/* Edgetech FS-DW high frequency sidescan (record 3000) */
	s7kr_fsdwss fsdwsshi;

	/* Edgetech FS-DW subbottom (record 3001) */
	s7kr_fsdwsb fsdwsb;

	/* Bluefin data frames (record 3100) */
	s7kr_bluefin bluefin;

	/* Processed sidescan - MB-System extension to 7k format (record 3199) */
	s7kr_processedsidescan processedsidescan;

	/* Reson 7k volatile sonar settings (record 7000) */
	s7kr_volatilesettings volatilesettings;

	/* Reson 7k configuration (record 7001) */
	s7kr_configuration configuration;

	/* Reson 7k match filter (record 7002) */
	s7kr_matchfilter matchfilter;

	/* Reson 7k firmware and hardware configuration (record 7003) */
	s7kr_v2firmwarehardwareconfiguration v2firmwarehardwareconfiguration;

	/* Reson 7k beam geometry (record 7004) */
	s7kr_beamgeometry beamgeometry;

	/* Reson 7k calibration (record 7005) */
	s7kr_calibration calibration;

	/* Reson 7k bathymetry (record 7006) */
	s7kr_bathymetry bathymetry;

	/* Reson 7k backscatter imagery data (record 7007) */
	s7kr_backscatter backscatter;

	/* Reson 7k beam data (record 7008) */
	s7kr_beam beam;

	/* Reson 7k vertical depth (record 7009) */
	s7kr_verticaldepth verticaldepth;

	/* Reson 7k tvg data (record 7011) */
	s7kr_tvg tvg;

	/* Reson 7k image data (record 7011) */
	s7kr_image image;

	/* Ping motion (record 7012) */
	s7kr_v2pingmotion v2pingmotion;

	/* Detection setup (record 7017) */
	s7kr_v2detectionsetup v2detectionsetup;

	/* Reson 7k beamformed magnitude and phase data (record 7018) */
	s7kr_v2beamformed v2beamformed;

	/* Reson 7k BITE (record 7021) */
	s7kr_v2bite v2bite;

	/* Reson 7k center version (record 7022) */
	s7kr_v27kcenterversion v27kcenterversion;

	/* Reson 7k 8k wet end version (record 7023) */
	s7kr_v28kwetendversion v28kwetendversion;

	/* Reson 7k version 2 detection (record 7026) */
	s7kr_v2detection v2detection;

	/* Reson 7k version 2 raw detection (record 7027) */
	s7kr_v2rawdetection v2rawdetection;

	/* Reson 7k version 2 snippet (record 7028) */
	s7kr_v2snippet v2snippet;

	/* Reson 7k sonar installation parameters (record 7030) */
	s7kr_installation installation;

	/* Reson 7k system event (record 7051) */
	s7kr_systemeventmessage systemeventmessage;

	/* Reson 7k calibrated snippet (record 7058) */
	s7kr_calibratedsnippet calibratedsnippet;

	/* Reson 7k file header (record 7200) */
	s7kr_fileheader fileheader;

	/* Reson 7k remote control sonar settings (record 7503) */
	s7kr_remotecontrolsettings remotecontrolsettings;

	/* Reson 7k Reserved (well, unknown really...) (record 7504) */
	s7kr_reserved reserved;

	/* Reson 7k Roll (record 7600) */
	s7kr_roll roll;

	/* Reson 7k Pitch (record 7601) */
	s7kr_pitch pitch;

	/* Reson 7k Sound Velocity (record 7610) */
	s7kr_soundvelocity soundvelocity;

	/* Reson 7k Absorption Loss (record 7611) */
	s7kr_absorptionloss absorptionloss;

	/* Reson 7k Spreading Loss (record 7612) */
	s7kr_spreadingloss spreadingloss;

	/* record counting variables */
	int nrec_read;
	int nrec_write;
	int nrec_reference;
	int nrec_sensoruncal;
	int nrec_sensorcal;
	int nrec_position;
	int nrec_customattitude;
	int nrec_tide;
	int nrec_altitude;
	int nrec_motion;
	int nrec_depth;
	int nrec_svp;
	int nrec_ctd;
	int nrec_geodesy;
	int nrec_rollpitchheave;
	int nrec_heading;
	int nrec_surveyline;
	int nrec_navigation;
	int nrec_attitude;
	int nrec_rec1022;
	int nrec_fsdwsslo;
	int nrec_fsdwsshi;
	int nrec_fsdwsb;
	int nrec_bluefinnav;
	int nrec_bluefinenv;
	int nrec_multibeam;
	int nrec_volatilesonarsettings;
	int nrec_configuration;
	int nrec_matchfilter;
	int nrec_beamgeometry;
	int nrec_v2firmwarehardwareconfiguration;
	int nrec_calibration;
	int nrec_bathymetry;
	int nrec_backscatter;
	int nrec_beam;
	int nrec_verticaldepth;
	int nrec_tvg;
	int nrec_image;
	int nrec_v2pingmotion;
	int nrec_v2detectionsetup;
	int nrec_v2beamformed;
	int nrec_v2bite;
	int nrec_v27kcenterversion;
	int nrec_v28kwetendversion;
	int nrec_v2detection;
	int nrec_v2rawdetection;
	int nrec_v2snippet;
	int nrec_calibratedsnippet;
	int nrec_processedsidescan;
	int nrec_installation;
	int nrec_systemeventmessage;
	int nrec_fileheader;
	int nrec_remotecontrolsettings;
	int nrec_reserved;
	int nrec_roll;
	int nrec_pitch;
	int nrec_soundvelocity;
	int nrec_absorptionloss;
	int nrec_spreadingloss;
	int nrec_other;
};

/* 7K Macros */
int mbsys_reson7k_checkheader(s7k_header header);

/* system specific function prototypes */
int mbsys_reson7k_zero7kheader(int verbose, s7k_header *header, int *error);
int mbsys_reson7k_alloc(int verbose, void *mbio_ptr, void **store_ptr, int *error);
int mbsys_reson7k_survey_alloc(int verbose, void *mbio_ptr, void *store_ptr, int *error);
int mbsys_reson7k_attitude_alloc(int verbose, void *mbio_ptr, void *store_ptr, int *error);
int mbsys_reson7k_heading_alloc(int verbose, void *mbio_ptr, void *store_ptr, int *error);
int mbsys_reson7k_ssv_alloc(int verbose, void *mbio_ptr, void *store_ptr, int *error);
int mbsys_reson7k_tlt_alloc(int verbose, void *mbio_ptr, void *store_ptr, int *error);
int mbsys_reson7k_deall(int verbose, void *mbio_ptr, void **store_ptr, int *error);
int mbsys_reson7k_zero_ss(int verbose, void *store_ptr, int *error);
int mbsys_reson7k_dimensions(int verbose, void *mbio_ptr, void *store_ptr, int *kind, int *nbath, int *namp, int *nss,
                             int *error);
int mbsys_reson7k_pingnumber(int verbose, void *mbio_ptr, int *pingnumber, int *error);
int mbsys_reson7k_sonartype(int verbose, void *mbio_ptr, void *store_ptr, int *sonartype, int *error);
int mbsys_reson7k_sidescantype(int verbose, void *mbio_ptr, void *store_ptr, int *ss_type, int *error);
int mbsys_reson7k_preprocess(int verbose, void *mbio_ptr, void *store_ptr, void *platform_ptr, void *preprocess_pars_ptr,
                             int *error);
int mbsys_reson7k_extract_platform(int verbose, void *mbio_ptr, void *store_ptr, int *kind, void **platform_ptr, int *error);
int mbsys_reson7k_extract(int verbose, void *mbio_ptr, void *store_ptr, int *kind, int time_i[7], double *time_d, double *navlon,
                          double *navlat, double *speed, double *heading, int *nbath, int *namp, int *nss, char *beamflag,
                          double *bath, double *amp, double *bathacrosstrack, double *bathalongtrack, double *ss,
                          double *ssacrosstrack, double *ssalongtrack, char *comment, int *error);
int mbsys_reson7k_insert(int verbose, void *mbio_ptr, void *store_ptr, int kind, int time_i[7], double time_d, double navlon,
                         double navlat, double speed, double heading, int nbath, int namp, int nss, char *beamflag, double *bath,
                         double *amp, double *bathacrosstrack, double *bathalongtrack, double *ss, double *ssacrosstrack,
                         double *ssalongtrack, char *comment, int *error);
int mbsys_reson7k_ttimes(int verbose, void *mbio_ptr, void *store_ptr, int *kind, int *nbeams, double *ttimes, double *angles,
                         double *angles_forward, double *angles_null, double *heave, double *alongtrack_offset, double *draft,
                         double *ssv, int *error);
int mbsys_reson7k_detects(int verbose, void *mbio_ptr, void *store_ptr, int *kind, int *nbeams, int *detects, int *error);
int mbsys_reson7k_gains(int verbose, void *mbio_ptr, void *store_ptr, int *kind, double *transmit_gain, double *pulse_length,
                        double *receive_gain, int *error);
int mbsys_reson7k_extract_altitude(int verbose, void *mbio_ptr, void *store_ptr, int *kind, double *transducer_depth,
                                   double *altitude, int *error);
int mbsys_reson7k_extract_nav(int verbose, void *mbio_ptr, void *store_ptr, int *kind, int time_i[7], double *time_d,
                              double *navlon, double *navlat, double *speed, double *heading, double *draft, double *roll,
                              double *pitch, double *heave, int *error);
int mbsys_reson7k_extract_nnav(int verbose, void *mbio_ptr, void *store_ptr, int nmax, int *kind, int *n, int *time_i,
                               double *time_d, double *navlon, double *navlat, double *speed, double *heading, double *draft,
                               double *roll, double *pitch, double *heave, int *error);
int mbsys_reson7k_insert_nav(int verbose, void *mbio_ptr, void *store_ptr, int time_i[7], double time_d, double navlon,
                             double navlat, double speed, double heading, double draft, double roll, double pitch, double heave,
                             int *error);
int mbsys_reson7k_extract_svp(int verbose, void *mbio_ptr, void *store_ptr, int *kind, int *nsvp, double *depth, double *velocity,
                              int *error);
int mbsys_reson7k_insert_svp(int verbose, void *mbio_ptr, void *store_ptr, int nsvp, double *depth, double *velocity, int *error);
int mbsys_reson7k_extract_segytraceheader(int verbose, void *mbio_ptr, void *store_ptr, int *kind, void *segyheader_ptr,
                                          int *error);
int mbsys_reson7k_extract_segy(int verbose, void *mbio_ptr, void *store_ptr, int *sampleformat, int *kind, void *segyheader_ptr,
                               float *segydata, int *error);
int mbsys_reson7k_insert_segy(int verbose, void *mbio_ptr, void *store_ptr, int kind, void *segyheader_ptr, float *segydata,
                              int *error);
int mbsys_reson7k_ctd(int verbose, void *mbio_ptr, void *store_ptr, int *kind, int *nctd, double *time_d, double *conductivity,
                      double *temperature, double *depth, double *salinity, double *soundspeed, int *error);
int mbsys_reson7k_ancilliarysensor(int verbose, void *mbio_ptr, void *store_ptr, int *kind, int *nsamples, double *time_d,
                                   double *sensor1, double *sensor2, double *sensor3, double *sensor4, double *sensor5,
                                   double *sensor6, double *sensor7, double *sensor8, int *error);
int mbsys_reson7k_copy(int verbose, void *mbio_ptr, void *store_ptr, void *copy_ptr, int *error);
int mbsys_reson7k_checkheader(s7k_header header);
int mbsys_reson7k_makess(int verbose, void *mbio_ptr, void *store_ptr, int source, int pixel_size_set, double *pixel_size,
                         int swath_width_set, double *swath_width, int pixel_int, int *error);
int mbsys_reson7k_print_header(int verbose, s7k_header *header, int *error);
int mbsys_reson7k_print_reference(int verbose, s7kr_reference *reference, int *error);
int mbsys_reson7k_print_sensoruncal(int verbose, s7kr_sensoruncal *sensoruncal, int *error);
int mbsys_reson7k_print_sensorcal(int verbose, s7kr_sensorcal *sensorcal, int *error);
int mbsys_reson7k_print_position(int verbose, s7kr_position *position, int *error);
int mbsys_reson7k_print_customattitude(int verbose, s7kr_customattitude *customattitude, int *error);
int mbsys_reson7k_print_tide(int verbose, s7kr_tide *tide, int *error);
int mbsys_reson7k_print_altitude(int verbose, s7kr_altitude *altitude, int *error);
int mbsys_reson7k_print_motion(int verbose, s7kr_motion *motion, int *error);
int mbsys_reson7k_print_depth(int verbose, s7kr_depth *depth, int *error);
int mbsys_reson7k_print_svp(int verbose, s7kr_svp *svp, int *error);
int mbsys_reson7k_print_ctd(int verbose, s7kr_ctd *ctd, int *error);
int mbsys_reson7k_print_geodesy(int verbose, s7kr_geodesy *geodesy, int *error);
int mbsys_reson7k_print_rollpitchheave(int verbose, s7kr_rollpitchheave *rollpitchheave, int *error);
int mbsys_reson7k_print_heading(int verbose, s7kr_heading *heading, int *error);
int mbsys_reson7k_print_surveyline(int verbose, s7kr_surveyline *surveyline, int *error);
int mbsys_reson7k_print_navigation(int verbose, s7kr_navigation *navigation, int *error);
int mbsys_reson7k_print_attitude(int verbose, s7kr_attitude *attitude, int *error);
int mbsys_reson7k_print_rec1022(int verbose, s7kr_rec1022 *rec1022, int *error);
int mbsys_reson7k_print_fsdwchannel(int verbose, int data_format, s7k_fsdwchannel *fsdwchannel, int *error);
int mbsys_reson7k_print_fsdwssheader(int verbose, s7k_fsdwssheader *fsdwssheader, int *error);
int mbsys_reson7k_print_fsdwsegyheader(int verbose, s7k_fsdwsegyheader *fsdwsegyheader, int *error);
int mbsys_reson7k_print_fsdwss(int verbose, s7kr_fsdwss *fsdwss, int *error);
int mbsys_reson7k_print_fsdwsb(int verbose, s7kr_fsdwsb *fsdwsb, int *error);
int mbsys_reson7k_print_bluefin(int verbose, s7kr_bluefin *bluefin, int *error);
int mbsys_reson7k_print_processedsidescan(int verbose, s7kr_processedsidescan *processedsidescan, int *error);
int mbsys_reson7k_print_volatilesettings(int verbose, s7kr_volatilesettings *volatilesettings, int *error);
int mbsys_reson7k_print_device(int verbose, s7k_device *device, int *error);
int mbsys_reson7k_print_configuration(int verbose, s7kr_configuration *configuration, int *error);
int mbsys_reson7k_print_matchfilter(int verbose, s7kr_matchfilter *matchfilter, int *error);
int mbsys_reson7k_print_v2firmwarehardwareconfiguration(int verbose,
                                                        s7kr_v2firmwarehardwareconfiguration *v2firmwarehardwareconfiguration,
                                                        int *error);
int mbsys_reson7k_print_beamgeometry(int verbose, s7kr_beamgeometry *beamgeometry, int *error);
int mbsys_reson7k_print_calibration(int verbose, s7kr_calibration *calibration, int *error);
int mbsys_reson7k_print_bathymetry(int verbose, s7kr_bathymetry *bathymetry, int *error);
int mbsys_reson7k_print_backscatter(int verbose, s7kr_backscatter *backscatter, int *error);
int mbsys_reson7k_print_beam(int verbose, s7kr_beam *beam, int *error);
int mbsys_reson7k_print_verticaldepth(int verbose, s7kr_verticaldepth *verticaldepth, int *error);
int mbsys_reson7k_print_tvg(int verbose, s7kr_tvg *tvg, int *error);
int mbsys_reson7k_print_image(int verbose, s7kr_image *image, int *error);
int mbsys_reson7k_print_v2pingmotion(int verbose, s7kr_v2pingmotion *v2pingmotion, int *error);
int mbsys_reson7k_print_v2detectionsetup(int verbose, s7kr_v2detectionsetup *v2detectionsetup, int *error);
int mbsys_reson7k_print_v2beamformed(int verbose, s7kr_v2beamformed *v2beamformed, int *error);
int mbsys_reson7k_print_v2bite(int verbose, s7kr_v2bite *v2bite, int *error);
int mbsys_reson7k_print_v27kcenterversion(int verbose, s7kr_v27kcenterversion *v27kcenterversion, int *error);
int mbsys_reson7k_print_v28kwetendversion(int verbose, s7kr_v28kwetendversion *v28kwetendversion, int *error);
int mbsys_reson7k_print_v2detection(int verbose, s7kr_v2detection *v2detection, int *error);
int mbsys_reson7k_print_v2rawdetection(int verbose, s7kr_v2rawdetection *v2rawdetection, int *error);
int mbsys_reson7k_print_v2snippet(int verbose, s7kr_v2snippet *v2snippet, int *error);
int mbsys_reson7k_print_calibratedsnippet(int verbose, s7kr_calibratedsnippet *calsnippet, int *error);
int mbsys_reson7k_print_installation(int verbose, s7kr_installation *installation, int *error);
int mbsys_reson7k_print_systemeventmessage(int verbose, s7kr_systemeventmessage *systemeventmessage, int *error);
int mbsys_reson7k_print_subsystem(int verbose, s7kr_subsystem *subsystem, int *error);
int mbsys_reson7k_print_fileheader(int verbose, s7kr_fileheader *fileheader, int *error);
int mbsys_reson7k_print_remotecontrolsettings(int verbose, s7kr_remotecontrolsettings *remotecontrolsettings, int *error);
int mbsys_reson7k_print_reserved(int verbose, s7kr_reserved *reserved, int *error);
int mbsys_reson7k_print_roll(int verbose, s7kr_roll *roll, int *error);
int mbsys_reson7k_print_pitch(int verbose, s7kr_pitch *pitch, int *error);
int mbsys_reson7k_print_soundvelocity(int verbose, s7kr_soundvelocity *soundvelocity, int *error);
int mbsys_reson7k_print_absorptionloss(int verbose, s7kr_absorptionloss *absorptionloss, int *error);
int mbsys_reson7k_print_spreadingloss(int verbose, s7kr_spreadingloss *spreadingloss, int *error);
