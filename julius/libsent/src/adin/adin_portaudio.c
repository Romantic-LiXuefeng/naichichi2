/**
 * @file   adin_portaudio.c
 * 
 * <JA>
 * @brief  �}�C�N���� (portaudio���C�u����)
 *
 * portaudioo���C�u�������g�p�����}�C�N���͂̂��߂̒჌�x���֐��ł��D
 * �g�p����ɂ� configure ���� "--with-mictype=portaudio" ���w�肵�ĉ������D
 * Linux ����� Win32 �Ŏg�p�\�ł��DWin32���[�h�ł͂��ꂪ
 * �f�t�H���g�ƂȂ�܂��D
 *
 * �^���f�o�C�X�� WASAPI -> ASIO -> DirectSound -> MME �̏��őI������܂��B
 * �g�p����f�o�C�X���w�肵�����ꍇ�́A���ϐ� PORTAUDIO_DEV �Ńf�o�C�X��
 * �i�擪���畔���}�b�`�j���w�肷�邩�APORTAUDIO_DEV_NUM �Ńf�o�C�X�ԍ���
 * �w�肵�Ă��������B�g�p�\�ȃf�o�C�X���ƃf�o�C�X�ԍ��͋N�����ɏo�͂���܂��B
 *
 * Julius�̓~�L�T�[�f�o�C�X�̐ݒ����؍s���܂���D�^���f�o�C�X��
 * �I���i�}�C�N/���C���j��^���{�����[���̒��߂�Windows��
 * �u�{�����[���R���g���[���v �� Linux �� xmixer �ȂǁC���̃c�[����
 * �s�Ȃ��ĉ������D
 *
 * portaudio �̓t���[�ŃN���X�v���b�g�z�[���̃I�[�f�B�I���o�̓��C�u����
 * �ł��D�\�[�X�� libsent/src/adin/pa/ �Ɋ܂܂�Ă��܂��D���̃v���O�����ł�
 * �X���b�h�𗘗p����callback �𗘗p���ē��͉����������O�o�b�t�@�Ɏ�荞���
 * ���܂��D
 *
 * @sa http://www.portaudio.com/
 * </JA>
 * <EN>
 * @brief  Microphone input using portaudio library
 *
 * Low level I/O functions for microphone input using portaudio library.
 * To use, please specify "--with-mictype=portaudio" options
 * to configure script.  This function is currently available for Linux and
 * Win32.  On Windows, this is default.
 *
 * The audio API will be chosen in the following order: WASAPI, ASIO,
 * DirectSound and MME.  You can specify which audio capture device to use
 * by setting the name (entire, or just the first part) to the
 * environment variable "PORTAUDIO_DEV", or the ID number to 
 * "PORTAUDIO_DEV_NUM".  The names and ID numbers of available devices will
 * be scanned and listed at the initialization.
 *
 * Julius does not alter any mixer device setting at all.  You should
 * configure the mixer for recording source (mic/line) and recording volume
 * correctly using other audio tool such as xmixer on Linux, or
 * 'Volume Control' on Windows.
 *
 * Portaudio is a free, cross platform, open-source audio I/O library.
 * The sources are included at libsent/src/adin/pa/.  This program uses
 * ring buffer to store captured samples in callback functions with threading.
 *
 * @sa http://www.portaudio.com/
 * </EN>
 *
 * @author Akinobu LEE
 * @date   Mon Feb 14 12:03:48 2005
 *
 * $Revision: 1.18 $
 * 
 */
/*
 * Copyright (c) 2004-2005 Shikano Lab., Nara Institute of Science and Technology
 * Copyright (c) 2005-2011 Julius project team, Nagoya Institute of Technology
 * All rights reserved
 */

#include <sent/stddefs.h>
#include <sent/speech.h>
#include <sent/adin.h>

/* sound header */
#include <portaudio.h>

#ifndef paNonInterleaved
#define OLDVER
#endif

#undef DDEBUG

/**
 * Define this to choose which audio device to open by querying the
 * device API type in the following order in Windows:
 *  
 *  WASAPI -> ASIO -> DirectSound -> MME
 *  
 * This will be effective when using portaudio library with multiple
 * Host API support, in which case Pa_OpenDefaultStream() will open
 * the first found one (not the one with the optimal performance)
 *
 * (not work on OLDVER)
 * 
 */
#ifndef OLDVER
#define CHOOSE_HOST_API
#endif

/**
 * Maximum Data fragment Length in msec.  Input can be delayed to this time.
 * You can override this value by specifying environment valuable
 * "LATENCY_MSEC".
 *
 * This is not used in the new V19, it uses default value given by the library.
 * At the new V19, you can force latency by PA_MIN_LATENCY_MSEC instead of LATENCY_MSEC.
 * 
 */
#ifdef OLDVER
#define MAX_FRAGMENT_MSEC 128
#endif

struct adinopt_portaudio {
	/* temporal buffer */
	SP16 *speech;		///< cycle buffer for incoming speech data
	int current;		///< writing point
	int processed;		///< reading point
	boolean buffer_overflowed; ///< TRUE if buffer overflowed
	int cycle_buffer_len;	///< length of cycle buffer based on INPUT_DELAY_SEC

	#ifdef OLDVER
	PortAudioStream *stream;		///< Stream information
	#else
	PaStream *stream;		///< Stream information
	#endif
	int srate;		///< Required sampling rate
};
typedef struct adinopt_portaudio ADINOPT;


/** 
 * PortAudio callback to store the incoming speech data into the cycle
 * buffer.
 * 
 * @param inbuf [in] portaudio input buffer 
 * @param outbuf [in] portaudio output buffer (not used)
 * @param len [in] length of above
 * @param outTime [in] output time (not used)
 * @param userdata [in] user defined data (not used)
 * 
 * @return 0 when no error, or 1 to terminate recording.
 */
static int
#ifdef OLDVER
Callback(void *inbuf, void *outbuf, unsigned long len, PaTimestamp outTime, void *userdata)
#else
Callback(const void *inbuf, void *outbuf, unsigned long len, const PaStreamCallbackTimeInfo *outTime, PaStreamCallbackFlags statusFlags, void *userdata)
#endif
{
#ifdef OLDVER
  SP16 *now;
  int avail;
#else
  const SP16 *now;
  unsigned long avail;
#endif
  int processed_local;
  int written;
  ADINOPT* adinopt = (ADINOPT*)userdata;

  now = inbuf;

  processed_local = adinopt->processed;

#ifdef DDEBUG
  printf("callback-1: processed=%d, current=%d: recordlen=%d\n", processed_local, adinopt->current, len);
#endif

  /* check overflow */
  if (processed_local > adinopt->current) {
    avail = processed_local - adinopt->current;
  } else {
    avail = adinopt->cycle_buffer_len + processed_local - adinopt->current;
  }
  if (len > avail) {
#ifdef DDEBUG
    printf("callback-*: buffer overflow!\n");
#endif
    adinopt->buffer_overflowed = TRUE;
    len = avail;
  }

  /* store to buffer */
  if (adinopt->current + len <= adinopt->cycle_buffer_len) {
    memcpy(&(adinopt->speech[adinopt->current]), now, len * sizeof(SP16));
#ifdef DDEBUG
    printf("callback-2: [%d..%d] %d samples written\n", adinopt->current, adinopt->current+len, len);
#endif
  } else {
    written = adinopt->cycle_buffer_len - adinopt->current;
    memcpy(&(adinopt->speech[adinopt->current]), now, written * sizeof(SP16));
#ifdef DDEBUG
    printf("callback-2-1: [%d..%d] %d samples written\n", adinopt->current, adinopt->current+written, written);
#endif
    memcpy(&(adinopt->speech[0]), &(now[written]), (len - written) * sizeof(SP16));
#ifdef DDEBUG
    printf("callback-2-2: ->[%d..%d] %d samples written (total %d samples)\n", 0, len-written, len-written, len);
#endif
  }
  adinopt->current += len;
  if (adinopt->current >= adinopt->cycle_buffer_len) adinopt->current -= adinopt->cycle_buffer_len;
#ifdef DDEBUG
  printf("callback-3: new current: %d\n", adinopt->current);
#endif

  return(0);
}



#ifdef CHOOSE_HOST_API

// Get device list
// If first argument is NULL, return the maximum number of devices
int
get_device_list(int *devidlist, char **namelist, int maxstrlen, int maxnum)
{
  PaDeviceIndex numDevice = Pa_GetDeviceCount(), i;
  const PaDeviceInfo *deviceInfo;
  const PaHostApiInfo *apiInfo;
  static char buf[256];
  int n;

  n = 0;
  for(i=0;i<numDevice;i++) {
    deviceInfo = Pa_GetDeviceInfo(i);
    if (!deviceInfo) continue;
    if (deviceInfo->maxInputChannels <= 0) continue;
    apiInfo = Pa_GetHostApiInfo(deviceInfo->hostApi);
    if (!apiInfo) continue;
    if (devidlist != NULL) {
      if ( n >= maxnum ) break;
      snprintf(buf, 255, "%s: %s", apiInfo->name, deviceInfo->name);
      buf[255] = '\0';
      devidlist[n] = i;
      strncpy(namelist[n], buf, maxstrlen);
    }
    n++;
  }
  
  return n;
}

// Automatically choose a device to open
// 
// 1. if the env value of "PORTAUDIO_DEV" is defined and matches any of 
//    "apiInfo->name: deviceInfo->name" string, use it.
// 2. if the env value "PORTAUDIO_DEV_NUM" is defined, use the (value-1)
//    as device id.
// 3. if not yet, default device will be chosen:
// 3.1. in WIN32 environment, search for supported and available API in
//      the following order: WASAPI, ASIO, DirectSound, MME.
//      Note that only the APIs supported by the linked PortAudio
//      library are available.
// 3.2  in other environment, use the default input device.
//
// store the device id to devId_ret and returns 0.
// if devId_ret is -1, tell caller to use default.
// returns -1 on error.
static int
auto_determine_device(int *devId_ret)
{
  int devId;
  PaDeviceIndex numDevice = Pa_GetDeviceCount(), i;
  const PaDeviceInfo *deviceInfo;
  const PaHostApiInfo *apiInfo;
  char *devname;
  static char buf[256];
#if defined(_WIN32) || defined(__CYGWIN__)
  // at win32, force preference order: iWASAPI > ASIO > DirectSound > MME > Other
  int iMME = -1, iDS = -1, iASIO = -1, iWASAPI = -1;
#endif

  // if PORTAUDIO_DEV is specified, match it against available APIs
  devname = getenv("PORTAUDIO_DEV");
  devId = -1;

  // get list of available capture devices
  jlog("Stat: adin_portaudio: sound capture devices:\n");
  for(i=0;i<numDevice;i++) {
    deviceInfo = Pa_GetDeviceInfo(i);
    if (!deviceInfo) continue;
    if (deviceInfo->maxInputChannels <= 0) continue;
    apiInfo = Pa_GetHostApiInfo(deviceInfo->hostApi);
    if (!apiInfo) continue;
    snprintf(buf, 255, "%s: %s", apiInfo->name, deviceInfo->name);
    buf[255] = '\0';
    jlog("  %d [%s]\n", i+1, buf);
    if (devname && !strncmp(devname, buf, strlen(devname))) {
      // device name (partially) matches PORTAUDIO_DEV
      devId = i;
    }
#if defined(_WIN32) || defined(__CYGWIN__)
    // store the device ID for each API
    switch(apiInfo->type) {
    case paWASAPI: if (iWASAPI < 0) iWASAPI = i; break;
    case paMME:if (iMME   < 0) iMME   = i; break;
    case paDirectSound:if (iDS    < 0) iDS    = i; break;
    case paASIO:if (iASIO  < 0) iASIO  = i; break;
    }
#endif
  }
  if (devname) {
    if (devId == -1) {
      jlog("Error: adin_portaudio: PORTAUDIO_DEV=\"%s\", but no device matches it\n", devname);
      return -1;
    }
    jlog("  --> #%d matches PORTAUDIO_DEV, use it\n", devId + 1);
    *devId_ret = devId;
    return 0;
  }
  if (getenv("PORTAUDIO_DEV_NUM")) {
    devId = atoi(getenv("PORTAUDIO_DEV_NUM")) - 1;
    if (devId < 0 || devId >= numDevice) {
      jlog("Error: PORTAUDIO_DEV_NUM=%d, but device %d not exist\n", devId+1, devId+1);
      return -1;
    }
    jlog("  --> use device %d, specified by PORTAUDIO_DEV_NUM\n", devId + 1);
    *devId_ret = devId;
    return 0;
  }
#if defined(_WIN32) || defined(__CYGWIN__)
  jlog("Stat: adin_portaudio: APIs:");
  if (iWASAPI >= 0) jlog(" WASAPI");
  if (iASIO >= 0) jlog(" ASIO");
  if (iDS >= 0) jlog(" DirectSound");
  if (iMME >= 0) jlog(" MME");
  jlog("\n");
  if (iWASAPI >= 0) {
    jlog("Stat: adin_portaudio: -- WASAPI selected\n");
    devId = iWASAPI;
  } else if (iASIO >= 0) {
    jlog("Stat: adin_portaudio: -- ASIO selected\n");
    devId = iASIO;
  } else if (iDS >= 0) {
    jlog("Stat: adin_portaudio: -- DirectSound selected\n");
    devId = iDS;
  } else if (iMME >= 0) {
    jlog("Stat: adin_portaudio: -- MME selected\n");
    devId = iMME;
  } else {
    jlog("Error: adin_portaudio: no device available, try default\n");
    devId = -1;
  }
  *devId_ret = devId;
#else
  jlog("Stat: adin_portaudio: use default device\n");
  *devId_ret = -1;
#endif
  return 0;
}

#endif

/** 
 * Device initialization: check device capability and open for recording.
 * 
 * @param sfreq [in] required sampling frequency.
 * @param dummy [in] a dummy data
 * 
 * @return TRUE on success, FALSE on failure.
 */
void*
adin_mic_standby(int sfreq, void *dummy)
{
  ADINOPT * adinopt = (ADINOPT*) mymalloc(sizeof(ADINOPT));
  memset(adinopt,0,sizeof(ADINOPT));
  /* store required sampling rate for checking after opening device */
  adinopt->srate = sfreq;
  return adinopt;
}

/** 
 * Open the portaudio device and check capability of the opening device.
 *
 * @param arg [in] argument: if number, use it as device ID
 * 
 * @return TRUE on success, FALSE on failure.
 */
static boolean
adin_mic_open(ADINOPT* adinopt,char *arg)
{
  int sfreq = adinopt->srate;
  PaError err;
#ifdef OLDVER
  int frames_per_buffer;
  int num_buffer;
#endif
  int latency;
  char *p;
  int devId;

  /* set cycle buffer length */
  adinopt->cycle_buffer_len = INPUT_DELAY_SEC * sfreq;
  //jlog("Stat: adin_portaudio: INPUT_DELAY_SEC = %d\n", INPUT_DELAY_SEC);
  jlog("Stat: adin_portaudio: audio cycle buffer length = %d bytes\n", adinopt->cycle_buffer_len * sizeof(SP16));

#ifdef OLDVER
  /* for safety... */
  if (sizeof(SP16) != paInt16) {
    jlog("Error: adin_portaudio: SP16 != paInt16 !!\n");
    return FALSE;
  }
  /* set buffer parameter*/
  frames_per_buffer = 256;
#endif

  /* allocate and init */
  adinopt->current = adinopt->processed = 0;
  adinopt->speech = (SP16 *)mymalloc(sizeof(SP16) * adinopt->cycle_buffer_len);
  adinopt->buffer_overflowed = FALSE;


  /* get user-specified latency parameter */
  latency = 0;
  if ((p = getenv("LATENCY_MSEC")) != NULL) {
    latency = atoi(p);
    jlog("Stat: adin_portaudio: setting latency to %d msec (obtained from LATENCY_MSEC)\n", latency);
  }
#ifdef OLDVER
  if (latency == 0) {
    latency = MAX_FRAGMENT_MSEC;
    jlog("Stat: adin_portaudio: setting latency to %d msec\n", latency);
  }
  num_buffer = sfreq * latency / (frames_per_buffer * 1000);
  jlog("Stat: adin_portaudio: framesPerBuffer=%d, NumBuffers(guess)=%d\n",
       frames_per_buffer, num_buffer);
  jlog("Stat: adin_portaudio: audio I/O Latency = %d msec (data fragment = %d frames)\n",
	   (frames_per_buffer * num_buffer) * 1000 / sfreq, 
	   (frames_per_buffer * num_buffer));
#endif

  /* initialize device */
  err = Pa_Initialize();
  if (err != paNoError) {
    jlog("Error: adin_portaudio: failed to initialize: %s\n", Pa_GetErrorText(err));
    return(FALSE);
  }

#ifdef CHOOSE_HOST_API

  if (arg == NULL) {
    // first try to determine the best device
    if (auto_determine_device(&devId) == -1) {
      jlog("Error: adin_portaudio: failed to choose the specified device\n");
      return(FALSE);
    }
    if (devId == -1) {
      // No device has been determined, use the default input device
      devId = Pa_GetDefaultInputDevice();
      if (devId == paNoDevice) {
	jlog("Error: adin_portaudio: no default input device is available or an error was encountered\n");
	return FALSE;
      }
    }
  } else {
    // use the given number as device id
    devId = atoi(arg);
  }
  // output device information to use
  {
    const PaDeviceInfo *deviceInfo;
    const PaHostApiInfo *apiInfo;
    static char buf[256];
    deviceInfo = Pa_GetDeviceInfo(devId);
    if (deviceInfo == NULL) {
      jlog("Error: adin_portaudio: failed to get info for device id %d\n", devId);
      return FALSE;
    }
    apiInfo = Pa_GetHostApiInfo(deviceInfo->hostApi);
    if (apiInfo == NULL) {
      jlog("Error: adin_portaudio: failed to get API info for device id %d\n", devId);
      return FALSE;
    }
    snprintf(buf, 255, "%s: %s", apiInfo->name, deviceInfo->name);
    buf[255] = '\0';
    jlog("Stat: adin_portaudio: [%s]\n", buf);
    jlog("Stat: adin_portaudio: (you can specify device by \"PORTAUDIO_DEV_NUM=number\"\n");
  }
  
  // open the device
  {
    PaStreamParameters param;
    memset( &param, 0, sizeof(param));
    param.channelCount = 1;
    param.device = devId;
    param.sampleFormat = paInt16;
    if (latency == 0) {
      param.suggestedLatency = Pa_GetDeviceInfo(devId)->defaultLowInputLatency;
      jlog("Stat: adin_portaudio: try to set default low latency from portaudio: %d msec\n", param.suggestedLatency * 1000.0);
    } else {
      param.suggestedLatency = latency / 1000.0;
      jlog("Stat: adin_portaudio: try to set latency to %d msec\n", param.suggestedLatency * 1000.0);
    }
    err = Pa_OpenStream(&adinopt->stream, &param, NULL, sfreq, 
			0, paNoFlag,
			Callback, adinopt);
    if (err != paNoError) {
      jlog("Error: adin_portaudio: error in opening stream: %s\n", Pa_GetErrorText(err));
      return(FALSE);
    }
  }
  {
    const PaStreamInfo *stinfo;
    stinfo = Pa_GetStreamInfo(adinopt->stream);
    jlog("Stat: adin_portaudio: latency was set to %f msec\n", stinfo->inputLatency * 1000.0);
  }

#else

  // Just open the default stream
  err = Pa_OpenDefaultStream(&adinopt->stream, 1, 0, paInt16, sfreq, 
#ifdef OLDVER
			     frames_per_buffer,
			     num_buffer, 
#else
				 0,
#endif
			     Callback, adinopt);
  if (err != paNoError) {
    jlog("Error: adin_portaudio: error in opening stream: %s\n", Pa_GetErrorText(err));
    return(FALSE);
  }

#endif /* CHOOSE_HOST_API */

  return(TRUE);
}

/** 
 * Start recording.
 * 
 * @param pathname [in] path name to open or NULL for default
 * 
 * @return TRUE on success, FALSE on failure.
 */
boolean
adin_mic_begin(void * adinoptTHIS,char *arg)
{
  ADINOPT* adinopt = (ADINOPT*)adinoptTHIS;
  PaError err;

  /* initialize device and open stream */
  if (adin_mic_open(adinopt,arg) == FALSE) {
    adinopt->stream = NULL;
    return(FALSE);
  }
  /* start stream */
  err = Pa_StartStream(adinopt->stream);
  if (err != paNoError) {
    jlog("Error: adin_portaudio: failed to begin stream: %s\n", Pa_GetErrorText(err));
    adinopt->stream = NULL;
    return(FALSE);
  }
  
  return(TRUE);
}

/** 
 * Stop recording.
 * 
 * @return TRUE on success, FALSE on failure.
 */
boolean
adin_mic_end(void * adinoptTHIS)
{
  ADINOPT* adinopt = (ADINOPT*)adinoptTHIS;
  PaError err;

  if (adinopt->stream == NULL) return(TRUE);

  /* stop stream (do not wait callback and buffer flush, stop immediately) */
  err = Pa_AbortStream(adinopt->stream);
  if (err != paNoError) {
    jlog("Error: adin_portaudio: failed to stop stream: %s\n", Pa_GetErrorText(err));
    return(FALSE);
  }
  /* close stream */
  err = Pa_CloseStream(adinopt->stream);
  if (err != paNoError) {
    jlog("Error: adin_portaudio: failed to close stream: %s\n", Pa_GetErrorText(err));
    return(FALSE);
  }
  /* terminate library */
  err = Pa_Terminate();
  if (err != paNoError) {
    jlog("Error: adin_portaudio: failed to terminate library: %s\n", Pa_GetErrorText(err));
    return(FALSE);
  }
  
  adinopt->stream = NULL;

  return TRUE;
}

/**
 * @brief  Read samples from device
 * 
 * Try to read @a sampnum samples and returns actual number of recorded
 * samples currently available.  This function will block until
 * at least some samples are obtained.
 * 
 * @param buf [out] samples obtained in this function
 * @param sampnum [in] wanted number of samples to be read
 * 
 * @return actural number of read samples, -2 if an error occured.
 */
int
adin_mic_read(void * adinoptTHIS,SP16 *buf, int sampnum)
{
  ADINOPT* adinopt = (ADINOPT*)adinoptTHIS;
  int current_local;
  int avail;
  int len;

  if (adinopt->buffer_overflowed) {
    jlog("Error: adin_portaudio: input buffer OVERFLOW, increase INPUT_DELAY_SEC in sent/speech.h\n");
    adinopt->buffer_overflowed = FALSE;
  }

  while (adinopt->current == adinopt->processed) {
#ifdef DDEBUG
    printf("process  : current == processed: %d: wait\n", adinopt->current);
#endif
    Pa_Sleep(20); /* wait till some input comes */
    if (adinopt->stream == NULL) return(-1);
  }

  current_local = adinopt->current;

#ifdef DDEBUG
  printf("process-1: processed=%d, current=%d\n", adinopt->processed, current_local);
#endif

  if (adinopt->processed < current_local) {
    avail = current_local - adinopt->processed;
    if (avail > sampnum) avail = sampnum;
    memcpy(buf, &(adinopt->speech[adinopt->processed]), avail * sizeof(SP16));
#ifdef DDEBUG
    printf("process-2: [%d..%d] %d samples read\n", adinopt->processed, adinopt->processed+avail, avail);
#endif
    len = avail;
    adinopt->processed += avail;
  } else {
    avail = adinopt->cycle_buffer_len - adinopt->processed;
    if (avail > sampnum) avail = sampnum;
    memcpy(buf, &(adinopt->speech[adinopt->processed]), avail * sizeof(SP16));
#ifdef DDEBUG
    printf("process-2-1: [%d..%d] %d samples read\n", adinopt->processed, adinopt->processed+avail, avail);
#endif
    len = avail;
    adinopt->processed += avail;
    if (adinopt->processed >= adinopt->cycle_buffer_len) adinopt->processed -= adinopt->cycle_buffer_len;
    if (sampnum - avail > 0) {
      if (sampnum - avail < current_local) {
	avail = sampnum - avail;
      } else {
	avail = current_local;
      }
      if (avail > 0) {
	memcpy(&(buf[len]), &(adinopt->speech[0]), avail * sizeof(SP16));
#ifdef DDEBUG
	printf("process-2-2: [%d..%d] %d samples read (total %d)\n", 0, avail, avail, len + avail);
#endif
	len += avail;
	adinopt->processed += avail;
	if (adinopt->processed >= adinopt->cycle_buffer_len) adinopt->processed -= adinopt->cycle_buffer_len;
      }
    }
  }
#ifdef DDEBUG
  printf("process-3: new processed: %d\n", adinopt->processed);
#endif
  return len;
}

/** 
 * 
 * Function to return current input source device name
 * 
 * @return string of current input device name.
 * 
 */
char *
adin_mic_input_name(void * adinoptTHIS)
{
  return("Portaudio default device");
}
