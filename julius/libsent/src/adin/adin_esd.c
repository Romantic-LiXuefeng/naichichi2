/**
 * @file   adin_esd.c
 *
 * <JA>
 * @brief  ネットワーク入力：Enlightened Sound Daemon (EsounD) からの音声入力
 *
 * 入力ソースとして Enlightened Sound Daemon (EsounD, 以下 esd) を
 * 使用する低レベル関数です．
 * 使用には esd が動作していることが必要です．
 * 使用するには configure 時に "--with-mictype=esd" を指定して下さい．
 * </JA>
 * <EN>
 * @brief  Audio input from Englightened Sound Daemon (EsounD)
 *
 * Low level I/O functions for audio input via the Enlightened Sound
 * Daemon (EsounD, or esd in short).  If you want to use this API,
 * please specify "--with-mictype=esd" options at compilation time
 * to configure script.
 * </EN>
 *
 * @author Akinobu LEE
 * @date   Sun Feb 13 16:18:26 2005
 *
 * $Revision: 1.6 $
 * 
 */
/*
 * Copyright (c) 2004-2005 Shikano Lab., Nara Institute of Science and Technology
 * Copyright (c) 2005-2011 Julius project team, Nagoya Institute of Technology
 * All rights reserved
 */

#include <sent/stddefs.h>
#include <sent/adin.h>

#ifdef HAS_ESD

#include <esd.h>

struct adinopt_esd {
	static int sock;		///< Audio socket
	static char name_buf[ESD_NAME_MAX]; ///< Unique identifier of this process that will be passed to EsounD
	static int latency;	///< Lantency time in msec
};
typedef struct adinopt_esd ADINOPT;

#endif

/** 
 * Connection initialization: check connectivity and open for recording.
 * 
 * @param sfreq [in] required sampling frequency
 * @param dummy [in] a dummy data
 * 
 * @return TRUE on success, FALSE on failure.
 */
void*
adin_esd_standby(int sfreq, void *dummy)
{
#ifndef HAS_ESD
  jlog("Error: esd not compiled in\n");
  return NULL;
#else
  esd_format_t format = ESD_BITS16 | ESD_MONO | ESD_STREAM | ESD_RECORD;
  ADINOPT * adinopt = (ADINOPT*) mymalloc(sizeof(ADINOPT));
  memset(adinopt,0,sizeof(ADINOPT));

  adinopt->latency = 50;

  /* generate uniq ID */
  snprintf(adinopt->name_buf, ESD_NAME_MAX, "julius%d", getpid());

  /* open stream */
  jlog("adin_esd: opening socket, format = 0x%08x at %d Hz id=%s\n", format, sfreq, adinopt->name_buf);
  adinopt->sock = esd_record_stream_fallback(format, sfreq, NULL, adinopt->name_buf);
  if (adinopt->sock <= 0) {
    jlog("Error: adin_esd: failed to connect to esd\n");
    free(adinopt);
    return NULL;
  }

  return adinopt;
#endif
}
 
/** 
 * Start recording.
 * @a pathname is dummy.
 *
 * @param pathname [in] path name to open or NULL for default
 * 
 * @return TRUE on success, FALSE on failure.
 */
boolean
adin_esd_begin(void * adinoptTHIS,char *pathname)
{
  return(TRUE);
}

/** 
 * Stop recording.
 * 
 * @return TRUE on success, FALSE on failure.
 */
boolean
adin_esd_end(void * adinoptTHIS)
{
  return TRUE;
}

/**
 * @brief  Read samples from the daemon.
 * 
 * Try to read @a sampnum samples and returns actual number of recorded
 * samples currently available.  This function will block until
 * at least one sample can be obtained.
 * 
 * @param buf [out] samples obtained in this function
 * @param sampnum [in] wanted number of samples to be read
 * 
 * @return actural number of read samples, -2 if an error occured.
 */
int
adin_esd_read(void * adinoptTHIS,SP16 *buf, int sampnum)
{
  ADINOPT* adinopt = (ADINOPT*)adinoptTHIS;
#ifndef HAS_ESD
  return -2;
#else
  int size, cnt;

  size = sampnum;
  if (size > ESD_BUF_SIZE) size = ESD_BUF_SIZE;
  size *= sizeof(SP16);

  while((cnt = read(adinopt->sock, buf, size)) <= 0) {
    if (cnt < 0) {
      perror("adin_esd_read: read error\n");
      return ( -2 );
    }
    usleep(adinopt->latency * 1000);
  }
  cnt /= sizeof(SP16);
  return(cnt);
#endif
}

/** 
 * 
 * Function to return current input source device name
 * 
 * @return string of current input device name.
 * 
 */
char *
adin_esd_input_name(void * adinoptTHIS)
{
  ADINOPT* adinopt = (ADINOPT*)adinoptTHIS;
#ifndef HAS_ESD
  return NULL;
#else
  return(adinopt->name_buf);
#endif
}
