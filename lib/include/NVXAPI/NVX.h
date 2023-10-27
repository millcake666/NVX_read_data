/*----------------------------------------------------------------------------*/
/*
  NVX DLL header file
*/
/*----------------------------------------------------------------------------*/
#ifndef ModID_NVX_H
#define ModID_NVX_H
#include <Windows.h>
/*----------------------------------------------------------------------------*/
/* Defines */

#ifdef __cplusplus
extern "C" {
#endif
#ifdef NVX_EXPORTS
/*! NVX_API functions as being exported from a DLL */
#define NVX_API __declspec(dllexport)
#else
/*! NVX_API functions as being imported from a DLL */
#define NVX_API __declspec(dllimport)
#endif

/*! Error codes */
#define NVX_ERR_OK			(0)		/*!< Success (no errors) */
#define NVX_ERR_ID			(-1)	/*!< Invalid ID (such ID not present now) */
#define NVX_ERR_FAIL		(-2)	/*!< Function fail (internal error) */
#define NVX_ERR_PARAM		(-3)	/*!< Invalid function parameter(s) */

/*! Invalid device ID */
#define NVX_ID_INVALID (0)

/* NVX models */
#define NVX_MODEL_24  (4003)	/* 24 main channels */
#define NVX_MODEL_36  (4004)	/* 32 main and 4 auxiliary channels */
#define NVX_MODEL_52  (4005)	/* 48 main and 4 auxiliary channels */
#define NVX_MODEL_16  (4009)    /* 10 main and 6 auxiliary channels */
#define NVX_MODEL_24T (4010)	/* 24 main channels + TET */
#define NVX_MODEL_36T (4011)	/* 32 main and 4 auxiliary channels + TET */

/*! NVX channels count in normal mode */
#define NVX_MODEL_24_CHANNELS_MAIN	(24) /* 24 (EEG) channels */
#define NVX_MODEL_24_CHANNELS_AUX	(0)	 /* 0 auxiliary channels */

#define NVX_MODEL_36_CHANNELS_MAIN	(32) /* 32 (EEG) channels */
#define NVX_MODEL_36_CHANNELS_AUX	(4)  /* 4 auxiliary channels */

#define NVX_MODEL_52_CHANNELS_MAIN	(48) /* 48 (EEG) channels */
#define NVX_MODEL_52_CHANNELS_AUX	(4)	 /* 4 auxiliary channels */

#define NVX_MODEL_16_CHANNELS_MAIN	(10) /* 10 (EEG) channels */
#define NVX_MODEL_16_CHANNELS_AUX	(6)	 /* 6 auxiliary channels */

/*! NVX select channels count in 10 kHz or 50 kHz mode */
#define NVX_SELECT_CHANNELS_COUNT	(24)

/*! NVX channels count in 50 kHz mode */
#define NVX_MODE_50_KHZ_CHANNELS_MAIN (4) /* 4 (EEG) channels */

/*! NVX data mode */
#define NVX_DM_NORMAL	(0) /* normal mode */
#define NVX_DM_50_KHZ	(1) /* fast mode(50 kHz), 4 Channels, no auxiliary */

/*! NVX test mode */
#define NVX_TM_FIXED	(0) /* all channels connected */
#define NVX_TM_CYCLE	(1) /* cyclical channels connection */

/*! NVX triggers mode */
#define NVX_TRG_NORMAL	(0) /* normal mode */
#define NVX_TRG_FRONT	(1) /* front detection */
#define NVX_TRG_REAR	(2) /* rear detection */

#define NVX_DISPLAY_MODE_INT	(0) /* internal display mode */
#define NVX_DISPLAY_MODE_EXT	(1) /* external display mode */

#define NVX_STM_SPR_MAX	(8000)	/* max sample rate of stimulus */

/*----------------------------------------------------------------------------*/
/* Data Types */

/*! 
  Device information structure 
  Note:
  If serial number = 0, it's means that device has not production information.
  In such case - production date also invalid (= 0) and can not be used.
  Model for this situation - always NVX_MODEL_24.
*/
typedef struct {
  unsigned int Model;			/*!< Device model ID */
  unsigned int SerialNumber;	/*!< Device serial number */
  SYSTEMTIME ProductionDate;	/*!< Device production date and time */
} t_NVXInformation;

/*! Device property structure */
typedef struct {
 float RateEeg;					/*!< EEG sampling rate, Hz */
 float RateAux;					/*!< AUX sampling rate, Hz */
 float ResolutionEeg;			/*!< EEG amplitude scale coefficients, V/bit */
 float ResolutionAux;			/*!< AUX amplitude scale coefficients, V/bit */
 float RangeEeg;				/*!< EEG input range, V */
 float RangeAux;				/*!< AUX input range, V */
} t_NVXProperty;

#pragma pack(push, 1) /* override default packing for structures */

/*! Device data type for NVX-24 model */
typedef struct {
  signed int Main[NVX_MODEL_24_CHANNELS_MAIN]; /*!< main channels data, 24 channels */
  unsigned int Status;	/*!< Digital inputs (bits 0 - 9) + output (bit 10) state + 21 MSB reserved bits */
  unsigned int Counter; /*!< 32-bit data sequencing cyclic counter */
} t_NVXDataModel24;

/*! Device data type for NVX-36 model */
typedef struct {
  signed int Main[NVX_MODEL_36_CHANNELS_MAIN]; /*!< main channels data, 32 channels */
  signed int  Aux[NVX_MODEL_36_CHANNELS_AUX];  /*!< auxiliary channels data, 4 channels */
  unsigned int Status;  /*!< Digital inputs (bits 0 - 9) + output (bit 10) state + 21 MSB reserved bits */
  unsigned int Counter; /*!< 32-bit data sequencing cyclic counter */
} t_NVXDataModel36;

/*! Device data type for NVX-52 model */
typedef struct {
  signed int Main[NVX_MODEL_52_CHANNELS_MAIN]; /*!< main channels data, 48 channels */
  signed int  Aux[NVX_MODEL_52_CHANNELS_AUX];  /*!< auxiliary channels data, 4 channels */
  unsigned int Status;  /*!< Digital inputs (bits 0 - 9) + output (bit 10) state + 21 MSB reserved bits */
  unsigned int Counter; /*!< 32-bit data sequencing cyclic counter */
} t_NVXDataModel52;

/*! Device data type for NVX-16 model */
typedef struct {
  signed int Main[NVX_MODEL_16_CHANNELS_MAIN]; /*!< main channels data, 10 channels */
  signed int  Aux[NVX_MODEL_16_CHANNELS_AUX];  /*!< auxiliary channels data, 6 channels */
  unsigned int Status;  /*!< Digital inputs (bits 0, 1) + output (bits 10, 11) state + 20 MSB reserved bits */
  unsigned int Counter; /*!< 32-bit data sequencing cyclic counter */
} t_NVXDataModel16;

/*! Device data type for acquisition mode 50 kHz */
typedef struct {
  signed int Main[NVX_MODE_50_KHZ_CHANNELS_MAIN];	/*!< main channels data, 4 channels */
  unsigned int Status; /*!< Digital inputs (bits 0 - 9) + output (bit 10) state + 21 MSB reserved bits */
  unsigned int Counter; /*!< 32-bit data sequencing cyclic counter */
} t_NVXDataMode50kHz;

/*! 
  Data acquisition modes settings.

  Note:
	- in 50 kHz mode device can acquisition  4 channels, monopolar or differential
	  (choice of the first 8 channels);
	- in 10 kHz mode device can acquisition 24 channels, monopolar or differential;
    - device channels numbers starting from 0, i.e. at label channel 1 = internal 0;
    - for monopolar set Main's channel to wishful, and Diff's to 255.

  Examples:
   - example for differential (channel 1 - channel 2)
       NVXChannelsSelect.MainChannels[0] = 0;
       NVXChannelsSelect.DiffChannels[0] = 1;
   - example for monopolar (channel 1)
       NVXChannelsSelect.MainChannels[0] = 0;
       NVXChannelsSelect.DiffChannels[0] = 255;
*/

/* Channels selector for 10 kHz or 50 kHz mode */
typedef struct {
    unsigned short MainChannels[NVX_SELECT_CHANNELS_COUNT]; /* numbers of main channels */
    unsigned short DiffChannels[NVX_SELECT_CHANNELS_COUNT]; /* numbers of diff channels */
} t_NVXChannelsSelect;

/*
  if DataRate = 0 then   24 channels at 10 kHz
  if DataRate = 1 then	all channels at  5 kHz
  if DataRate = 2 then	all channels at  2 kHz
  if DataRate = 3 then	all channels at  1 kHz
  if DataRate = 4 then	all channels at  0.5 kHz
  if DataRate = 5 then	all channels at  0.250 kHz
  if DataRate = 6 then	all channels at  0.125 kHz
*/
typedef struct { 
  unsigned short DataRate;
  t_NVXChannelsSelect NVXChannelsSelect;
} t_NVXDataSettings;

/*!  Possibility */
typedef struct {
  unsigned int EegChannelsCount;	/* numbers of Eeg channels */
  unsigned int AuxChannelsCount;	/* numbers of Aux channels */
  unsigned int InTriggersCount;		/* numbers of input triggers */
  unsigned int OutTriggersCount;	/* numbers of output triggers */
  unsigned int XDisplayResolution;	/* display resolution horizontal */
  unsigned int YDisplayResolution;	/* display resolution vertical */
  unsigned int UserMemorySize;		/* size of memory for user data */
} t_NVXPossibility;

/* Version info about NVX */
typedef struct {
  unsigned long long Dll;
  unsigned long long Driver;
  unsigned long long Firmware;
} t_NVXVersion;

typedef struct {
	unsigned long long Dll;
	unsigned long long Driver;
	unsigned long long Dsp;
	unsigned long long Fpga;
} t_NVXVersionExt;

/*! Samples rate (physical) enum */
typedef enum {
	NVX_RATE_10KHZ = 0,
	NVX_RATE_50KHZ = 1,
} t_NVXRate;

/*!  ADC data decimation */
typedef enum {
	NVX_DECIMATION_0 = 0, /* no decimation */
	NVX_DECIMATION_2 = 2, /* decimation by 2 */
	NVX_DECIMATION_5 = 5, /* decimation by 5 */
	NVX_DECIMATION_10 = 10, /* decimation by 10 */
	NVX_DECIMATION_20 = 20, /* decimation by 20 */
	NVX_DECIMATION_40 = 40, /* decimation by 40 */
	NVX_DECIMATION_80 = 80, /* decimation by 80 */
} t_NVXDecimation;


/*! Frequency bandwidth structure */
typedef struct {
	unsigned int SampleRate; /*!<  Sample rate of device, mHz */
	unsigned int CutoffFreq; /*!< Cutoff frequency of the -3 dB, mHz */
	t_NVXRate DecimFromRate; /*!< Decimation from rate */
	t_NVXDecimation Decimation; /*!< Decimation value */
} t_NVXFrequencyBandwidth;

/* Stimulus info for NVX-T */
typedef struct {
	int SampleRate; /* Hz */
} t_NVXStimulusInfo;

/*!  TET current mode */
typedef enum {
	NVXT_CM_DC = 0, /* DC */
	NVXT_CM_AC = 1, /* AC */
} t_NVXCurrentMode;

/*!  Stimulation mode */
typedef enum {
	NVXT_STM_NORMAL = 0, /* Normal mode */
	NVXT_STM_DB = 1, /* Double blind mode */
} t_NVXStimulationMode;

/* TET switchers for NVX-T */
typedef struct {
	unsigned int PosChannels;
	unsigned int NegChannels;
	unsigned int Ground;
} t_NVXSwitchers;

/* TET stimulus sync settings */
typedef struct {
	unsigned int InputRemote;
	unsigned int OutputEnable;
} t_NVXStimulusSync;

/* TET stream parameters */
typedef struct {
	unsigned int SampleRate;
	unsigned int Size;
} t_NVXStreamParameters;

/*!  TET stream state */
typedef enum {
	NVXT_STREAM_STOPPED = 0, /* Stream started */
	NVXT_STREAM_STARTED = 1, /* Stream stopped */
} t_NVXStreamState;

/*!  TET stream result */
typedef enum {
	NVXT_STREAM_ERROR_OK = 0, /* Success (no errors) */
	NVXT_STREAM_ERROR_FAIL = 1, /* Fail (stream error) */
} t_NVXStreamError;

/* TET stimulus stream status */
typedef struct {
	unsigned int Position;
	t_NVXStreamState State;
	t_NVXStreamError Error;
} t_NVXStreamStatus;

#pragma pack(pop) /* restore default packing for structures */

/*----------------------------------------------------------------------------*/
/* NVX Functions */
/*!
  Function to get version info about NVX
  Note:
  - if hDevice = NULL, only Dll version is valid.
\param hDevice - device handle
\param Version - pointer to structure with version
\return - error code
*/
NVX_API int WINAPI NVXGetVersion(int Id, t_NVXVersion *Version);

/*!
Function to get extended version info about NVX
Note:
- if hDevice = NULL, only Dll version is valid.
\param hDevice - device handle
\param VersionExt - pointer to structure with extended version
\return - error code
*/
NVX_API int WINAPI NVXGetVersionExt(int Id, t_NVXVersionExt *VersionExt);

/*----------------------------------------------------------------------------*/
/*!
  Function return count of device currently connected to system
\return - device count
*/
NVX_API unsigned int WINAPI NVXGetCount(void);

/*----------------------------------------------------------------------------*/
/*!
  Function return device ID on order number (from 0 to NVXGetCount() - 1)
\param Number - order number of device
\return - device ID
*/
NVX_API int WINAPI NVXGetId(unsigned int Number);

/*----------------------------------------------------------------------------*/
/*!
  Function to open device for work
\param Id - device ID
\return - error code
*/
NVX_API int WINAPI NVXOpen(int Id);

/*----------------------------------------------------------------------------*/
/*!
  Function to close device for work
\param Id - device ID
\return - error code
*/
NVX_API int WINAPI NVXClose(int Id);

/*----------------------------------------------------------------------------*/
/*!  
  Function to start data acquisition
\param Id - device ID
\return - error code
*/
NVX_API int WINAPI NVXStart(int Id);

/*----------------------------------------------------------------------------*/
/*!  
  Function to stop data acquisition
\param Id - device ID
\return - error code
*/
NVX_API int WINAPI NVXStop(int Id);

/*----------------------------------------------------------------------------*/
/*!  
  Function return acquisition data from internal buffer.
  If some channels is not connect, data values are equals to INT_MAX for its.
  Data return in format t_NVXDataModel16 or t_NVXDataModel24 or t_NVXDataModel36 or t_NVXDataModel52 or
  t_NVXDataMode50kHz, depends from model and acquisition mode.
\param Id - device ID
\param Buffer - pointer to buffer for device data.
\param Size - size of buffer for device data, bytes.
\return
  if > 0 - count of bytes copied to buffer
  if = 0 - no more data in internal buffer
  if < 0 - error code  
*/
NVX_API int WINAPI NVXGetData(int Id, void *Buffer, unsigned int Size);

/*----------------------------------------------------------------------------*/
/*!  
  Function return device information
  Note:
  - if device has not this information in EEPROM (for example not programming or
    data corruption) than serial number in t_NVXInformation structure set to 0 
    and device information structure return as for unprogramming device.
    See note for t_NVXInformation structure.
\param Id - device ID
\param Information - address of t_NVXInformation structure for return data
\return - error code
*/
NVX_API int WINAPI NVXGetInformation(int Id, t_NVXInformation *Information);

/*----------------------------------------------------------------------------*/
/*!  
  Function return device property
\param Id - device ID
\param Property - address of t_NVXProperty structure for return data
\return - error code
*/
NVX_API int WINAPI NVXGetProperty(int Id, t_NVXProperty *Property);

/*----------------------------------------------------------------------------*/
/*!  
  Function return device possibility
\param Id - device ID
\param Possibility - address of t_NVXPossibility structure for return data
\return - error code
*/
NVX_API int WINAPI NVXGetPossibility(int Id, t_NVXPossibility *Possibility);

/*----------------------------------------------------------------------------*/
/*!  
  Function to start impedance measure.
  Note:
    - for correct work of impedance measure (NVXGetImpedance()) needs to start 
      data acquisition (NVXStart()) before start of impedance measure (NVXStartImpedance()).
\param Id - device ID
\return - error code
*/
NVX_API int WINAPI NVXStartImpedance(int Id);

/*----------------------------------------------------------------------------*/
/*!
  Function to stop impedance measure.
  Note:
    - this function only stop impedance measure, but not stop data acquisition.
\param Id - device ID
\return - error code
*/
NVX_API int WINAPI NVXStopImpedance(int Id);

/*----------------------------------------------------------------------------*/
/*!
  Function return impedance values for all channels in Ohm.
  Remarks (notes):
  - if electrode not connect, value equal to INT_MAX (from <limits.h>)
\param Id - device ID
\param Buffer - pointer to destination buffer for N (channels)
\param Size - size of destination buffer, bytes
\return - error code  
*/
NVX_API int WINAPI NVXGetImpedance(int Id, unsigned int *Buffer, unsigned int Size);

/*----------------------------------------------------------------------------*/
/*!  
  Function to start of test signal on EEG channels
  Note:
  - test signal is square signal with period 1 sec with amplitude 200 uV,
    (on-off time ratio 1 : 1)
  - amplitude correct only on unconnected channels.
  - on connected electrodes amplitude of test signal uncorrect (devided 
    between electrode impedance and channel output impedance )
\param Id - device ID
\param Mode - test mode (NVX_TM_FIXED or NVX_TM_CYCLE)
\return - error code
*/
NVX_API int WINAPI NVXStartTest(int Id, unsigned int Mode);

/*----------------------------------------------------------------------------*/
/*!
  Function to stop of test signal on EEG channels
\param Id - device ID
\return - error code
*/
NVX_API int WINAPI NVXStopTest(int Id);

/*----------------------------------------------------------------------------*/
/*!
Function to set triggers mode
Note: only for NVX24, NVX36, NVX52 models
\param Id - device ID
\param Mode - triggers mode (NVX_TRG_NORMAL, NVX_TRG_FRONT or NVX_TRG_REAR)
\return - error code
*/
NVX_API int WINAPI NVXSetTriggersMode(int Id, unsigned int Mode);

/*----------------------------------------------------------------------------*/
/*!
Function to get triggers mode
Note: only for NVX24, NVX36, NVX52 models
\param Id - device ID
\param Mode - pointer to triggers mode variable
\return - error code
*/
NVX_API int WINAPI NVXGetTriggersMode(int Id, unsigned int *Mode);

/*----------------------------------------------------------------------------*/
/*!
  Function to set state of output trigger
\param Id - device ID
\param State - state of output trigger (bits 0, 1)
\return - error code
*/
NVX_API int WINAPI NVXSetOut(int Id, unsigned char State);

/*----------------------------------------------------------------------------*/
/*!
Function to get BUS voltage
\param Id - device ID
\param Voltage - voltage, V
\return - error code
*/
NVX_API int WINAPI NVXGetVoltage(int Id, double *Voltage);

/*----------------------------------------------------------------------------*/
/*!
  Function to set display mode
\param Id - device ID
\param Mode - display mode NVX_DISPLAY_MODE_INT or NVX_DISPLAY_MODE_EXT
\return - error code
*/
NVX_API int WINAPI NVXSetDisplayMode(int Id, unsigned int Mode);

/*----------------------------------------------------------------------------*/
/*!
Function to set text on display
\param Id - device ID
\param PStr - text string
\return - error code
*/
NVX_API int WINAPI NVXSetLCDText(int ID, char* PStr);

/*----------------------------------------------------------------------------*/
/*!
  Function to show Windows bitmap on device display
  Note:
  - device display have 256 pixels x 64 pixels x 1 bit color
  - if Bitmap == NULL then device LCD fill the area with black
\param Id - device ID
\param Bitmap - handle to monochrome Windows bitmap
\return - error code
*/
NVX_API int WINAPI NVXSetBitmap(int Id, HBITMAP Bitmap);

/*----------------------------------------------------------------------------*/
/*!
  Function to set Windows bitmap as welcome screen on device
\param Id - device ID
\param Bitmap - handle to monochrome Windows bitmap 256 pixels x 64 pixels
\return - error code
*/
NVX_API int WINAPI NVXSaveBitmap(int Id, HBITMAP Bitmap);

/*----------------------------------------------------------------------------*/
/*!
  Function to get contrast of display
\param Id - device ID
\param Contrast - contrast(0-255)
\return - error code
*/
NVX_API int WINAPI NVXGetContrast(int Id, unsigned int *Contrast);

/*----------------------------------------------------------------------------*/
/*!
  Function to set contrast of LCD display
\param Id - device ID
\param Contrast - contrast(0-255)
\return - error code
*/
NVX_API int WINAPI NVXSetContrast(int Id, unsigned int Contrast);

/*----------------------------------------------------------------------------*/
/*!
  Function to read user (application software) data from device nonvolatile memory.
  Note:
  - max size of user data equal to NVX_USER_DATA_SIZE(1024 bytes)
  - device internal protect user data integrity with CRC code
\param Id - device ID
\param Buffer - pointer to buffer for data
\param Size - size of buffer for data, bytes
\param Count - pointer to count of reading data, bytes
\return - error code
*/
NVX_API int WINAPI NVXGetUserData(int Id, void *Buffer, unsigned int Size, 
  unsigned int *Count);

/*----------------------------------------------------------------------------*/
/*!
  Function to write user (application software) data to device nonvolatile memory.
  Note:
  - max size of user data equal to NVX_USER_DATA_SIZE(1024 bytes)
  - device internal protect user data integrity with CRC code
\param Id - device ID
\param Buffer - pointer to buffer for data
\param Size - size of buffer for data, bytes
\param Count - pointer to count of writing data, bytes
\return - error code
*/
NVX_API int WINAPI NVXSetUserData(int Id, void *Buffer, unsigned int Size, 
  unsigned int *Count);

/*----------------------------------------------------------------------------*/
/*!
  Function to get data acquisition mode
\param Id - device ID
\param Mode - pointer to data acquisition mode variable
\return - error code
*/
NVX_API int WINAPI NVXGetDataMode(int Id, unsigned int *Mode);

/*----------------------------------------------------------------------------*/
/*!
  Function to set data acquisition mode.
  Warning:
    - do not change mode during acquisition, previous stop.
    - impedance measure in 50 kHz mode not working, needs set normal mode
  Note:    
    - for set normal mode call NVXSetDataMode(Id, NVX_DM_NORMAL, &settings)
    - for set 50 kHz mode call NVXSetDataMode(Id, NVX_DM_50_KHZ, &settings)
\param Id - device ID
\param Mode - data acquisition mode
\param Settings - data acquisition mode settings
\return - error code
*/
NVX_API int WINAPI NVXSetDataMode(int Id, unsigned int Mode, t_NVXDataSettings *Settings);

typedef struct {
	unsigned version;
	char PnPThreadEnabled;
} t_NVXConfiguration;

/*----------------------------------------------------------------------------*/
/*!
Function to get polarization of the electrodes
\param Id - device ID
\param Buffer -  pointer to buffer for polarization data
\param Size - size of buffer for polarization data, bytes
\return - error code
*/
NVX_API int WINAPI NVXGetPolarization(int Id, double *Buffer, unsigned int Size);

/*----------------------------------------------------------------------------*/
/*!
Function to get device sample rate count
\param Count - pointer to 32-bit variable
\return - error code
*/
NVX_API int WINAPI NVXGetSampleRateCount(unsigned int *Count);

/*----------------------------------------------------------------------------*/
/*!
Function to get frequency bandwidth
\param FrequencyBandwidth -  pointer to array of t_NVXFrequencyBandwidth
\param Size - size of array of t_NVXFrequencyBandwidth for bandwidth data, bytes
\return - error code
*/
NVX_API int WINAPI NVXGetFrequencyBandwidth(t_NVXFrequencyBandwidth *FrequencyBandwidth, unsigned int Size);

/*----------------------------------------------------------------------------*/
/*!
Function to load stimulus
\param Id - device ID
\param Buffer - pointer to buffer
\param Size - size of buffer, bytes
\return - error code
*/
NVX_API int WINAPI NVXLoadStimulus(int Id, t_NVXStimulusInfo *StimulusInfo, void *Buffer, unsigned int Size);

/*----------------------------------------------------------------------------*/
NVX_API int WINAPI NVXSetStimulationMode(int Id, t_NVXStimulationMode StimulationMode);
NVX_API int WINAPI NVXSetSwitchers(int Id, t_NVXSwitchers *Switchers);
NVX_API int WINAPI NVXSetCurrentMode(int Id, int CurrentMode);
NVX_API int WINAPI NVXSetCurrentLimit(int Id, int CurrentLimit);
NVX_API int WINAPI NVXSetStimulusAmplitude(int Id, int Amplitude);
NVX_API int WINAPI NVXSetStimulusOffset(int Id, int Offset);
NVX_API int WINAPI NVXSetStimulusTimeLimit(int Id, int TimeLimit);
NVX_API int WINAPI NVXSetStimulusTimeCorr(int Id, int TimeCorr);
NVX_API int WINAPI NVXGetResolutionCtrl(int Id, double *ResolutionCtrl);

/*----------------------------------------------------------------------------*/
/*!
Function return current values for all channels in uA.
Remarks (notes):
- if electrode not connect, value equal to INT_MAX - 1 (from <limits.h>)
\param Id - device ID
\param Buffer - pointer to destination buffer for N (channels)
\param Size - size of destination buffer, bytes
\return - error code
*/
NVX_API int WINAPI NVXGetCurrent(int Id, unsigned int *Buffer, unsigned int Size);

NVX_API int WINAPI NVXGetCurrentRms(int Id, unsigned int *Buffer, unsigned int Size);

/*----------------------------------------------------------------------------*/
/*!
Function to start TET on EEG channels
\return - error code
*/
NVX_API int WINAPI NVXStartStimulus(int Id, unsigned int Period, unsigned int CycleCount, int Sweep);

/*----------------------------------------------------------------------------*/
/*!
Function to start TET on EEG channels with additional parameters
\return - error code
*/
NVX_API int WINAPI NVXStartStimulusExt(int Id, unsigned int Period, unsigned int CycleCount, unsigned int Blocks, unsigned int Pause, int Sweep);

/*----------------------------------------------------------------------------*/
/*!
Function to stop TET on EEG channels
\param Id - device ID
\return - error code
*/
NVX_API int WINAPI NVXStopStimulus(int Id);
NVX_API int WINAPI NVXOpenStream(int Id, void *Buffer, t_NVXStreamParameters *StreamParameters);
NVX_API int WINAPI NVXStartStream(int Id);
NVX_API int WINAPI NVXStopStream(int Id);
NVX_API int WINAPI NVXGetStreamStatus(int Id, t_NVXStreamStatus *StreamStatus);

/*----------------------------------------------------------------------------*/
/*!
Function to set stimulus warning
\param Id - device ID
\param Warning - if warning = 0, then disabled
\return - error code
*/
NVX_API int WINAPI NVXSetStimulusWarning(int Id, int Warning);
NVX_API int WINAPI NVXSetStimulusSync(int Id, t_NVXStimulusSync *StimulusSync);

/*----------------------------------------------------------------------------*/
/*!
Function to init NVX API
\param configuration -  pointer to configuration string
\return - error code
*/
NVX_API int WINAPI NVXAPIInit(const char* configuration);

/*----------------------------------------------------------------------------*/
/*!
Function to stop NVX API
\return - error code
*/
NVX_API int WINAPI NVXAPIStop();

/*----------------------------------------------------------------------------*/
#ifdef __cplusplus
} // extern "C"
#endif

#ifdef __cplusplus
#include <ostream>
NVX_API std::ostream& operator <<(std::ostream&, const t_NVXConfiguration&);
#endif

#endif /* ModID_XXX_H */
