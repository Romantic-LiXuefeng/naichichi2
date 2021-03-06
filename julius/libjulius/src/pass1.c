/**
 * @file   pass1.c
 * 
 * <JA>
 * @brief  ﾂ・パス：フ･・璽狷唄・咫璽狠戯・ *
 * 静的木構造辞書を用いて，入力特徴量ベクト･・鵑紡个靴董､Juliusの第１パス
 * であ､・侫・璽狷唄・咫璽狠戯�を行いま�ｹ. 
 *
 * 入力データ全体があらかじめ得ら､・討い・・腓蓮ぐ・腓之彁擦・ * 行う関ｿ・get_back_trellis() がメインから呼ば､・泙ｹ. オンライン認識
 * のｾ・腓ﾏ realtime_1stpass.c から，初ｴ・宗ぅ侫・璽爐瓦箸侶彁察､
 * 終了処理のそ､・召・�入力の進行にあぁ�擦童鎚未妨討个・泙ｹ. 
 *
 * 実際の個々の認識処理インスタンスごとの処理は beam.c に記述さ､・討い泙ｹ. 
 *
 * </JA>
 * 
 * <EN>
 * @brief  The first pass: frame-synchronous beam search
 *
 * These functions perform a frame-synchronous beam search using a static
 * lexicon tree, as the first pass of Julius/Julian.
 *
 * When the whole input is already obtained, get_back_trellis() simply
 * does all the processing of the 1st pass.  When performing online
 * real-time recognition with concurrent speech input, each function
 * will be called separately from realtime_1stpass.c according on the
 * basis of input processing.
 *
 * The core recognition processing functions for each recognition
 * process instances are written in beam.c.
 *
 * </EN>
 * 
 * @author Akinobu Lee
 * @date   Fri Oct 12 23:14:13 2007
 *
 * $Revision: 1.8 $
 * 
 */
/*
 * Copyright (c) 1991-2011 Kawahara Lab., Kyoto University
 * Copyright (c) 2000-2005 Shikano Lab., Nara Institute of Science and Technology
 * Copyright (c) 2005-2011 Julius project team, Nagoya Institute of Technology
 * All rights reserved
 */

#include <julius/julius.h>

/********************************************************************/
/* 第１パスを実行す､・瓮ぅ鶸愎・                                    */
/* 入力をパイプライン処理す､・・腓ﾏ realtime_1stpass.c を参照のこと */
/* main function to execute 1st pass                                */
/* the pipeline processing is not here: see realtime_1stpass.c      */
/********************************************************************/

/** 
 * <EN>
 * @brief  Process one input frame for all recognition process instance.
 *
 * This function proceeds the recognition for one frame.  All
 * recognition process instance will be processed synchronously.
 * The input frame for each instance is stored in mfcc->f, where mfcc
 * is the MFCC calculation instance assigned to each process instance.
 *
 * If an instance's mfcc->invalid is set to TRUE, its processing will
 * be skipped.
 *
 * When using GMM, GMM computation will also be executed here.
 * If GMM_VAD is defined, GMM-based voice detection will be performed
 * inside this function, by using a scheme of short-pause segmentation.
 *
 * This function also handles segmentation of recognition process.  A
 * segmentation will occur when end of speech is detected by level-based
 * sound detection or GMM-based / decoder-based VAD, or by request from
 * application.  When segmented, it stores current frame and return with
 * that status.
 *
 * The frame-wise callbacks will be executed inside this function,
 * when at least one valid recognition process instances exists.
 * 
 * </EN>
 * <JA>
 * @brief  全ての認識処理インスタンス処理､・フ･・璽猜�進めぁ�
 *
 * 全ての認識処理インスタンスについて，割､・佞韻蕕・討い・FCC計算インスタンス
 * の mfcc->f をカ･・鵐肇侫・璽爐箸靴峠萢�ぁΕ�･・璽狄覆瓩・ 
 *
 * なお，mfcc->invalid が TRUE となってい､・萢�インスタンスの処理はスキッ�ﾗ
 * さ､・・ 
 *
 * GMMの計算もここで呼び出さ､・・ GMM_VAD ﾄ・岨�は�､GMM によ､・ * 発話区間開始・終了の検出がここで行､・・・ また，GMMの計算ｷ・漫､
 * あ､・い惑Ъ噂萢�内のショートポーズセグメンテーション判定やデバイス・外鼻� * からの要求によ､・札哀瓮鵐董璽轡腑鵑�要求さぁ�燭�どうかの判定も行�ｦ. 
 *
 * フ･・璽狠碓未埜討喀个気・・魁璽・丱奪�が登録さぁζいぁΑ�腓蓮い修・蕕ﾎ
 * 呼出しも行う. 
 * </JA>
 * 
 * @param recog [in] engine instance
 * 
 * @return 0 on success, -1 on error, or 1 when an input segmentation
 * occured/requested inside this function.
 *
 * @callgraph
 * @callergraph
 * 
 */
int
decode_proceed(Recog *recog)
{
  MFCCCalc *mfcc;
  boolean break_flag;
  boolean break_decode;
  RecogProcess *p;
  boolean ok_p;
#ifdef GMM_VAD
  GMMCalc *gmm;
  boolean break_gmm;
#endif
  
  break_decode = FALSE;

  for(p = recog->process_list; p; p = p->next) {
    p->have_interim = FALSE;
  }
  for (mfcc = recog->mfcclist; mfcc; mfcc = mfcc->next) {
    mfcc->segmented = FALSE;
  }

  for(p = recog->process_list; p; p = p->next) {
    if (!p->live) continue;
    mfcc = p->am->mfcc;
    if (!mfcc->valid) {
      /* このフ･・璽爐僚萢�をスキッ�ﾗ */
      /* skip processing the frame */
      continue;
    }

    /* mfcc-f のフ･・璽爐砲弔い毒Ъ噂萢��(フ･・璽狷唄・咫璽狠戯・を進め､・*/
    /* proceed beam search for mfcc->f */
    if (mfcc->f == 0) {
      /* 最初のフ･・璽・ 探索処理を初ｴ・ｽ */
      /* initial frame: initialize search process */
      if (get_back_trellis_init(mfcc->param, p) == FALSE) {
	jlog("ERROR: %02d %s: failed to initialize the 1st pass\n", p->config->id, p->config->name);
	return -1;
      }
    }
    if (mfcc->f > 0 || p->am->hmminfo->multipath) {
      /* 1フ･・璽狠戯�を進めぁ�*/
      /* proceed search for 1 frame */
      if (get_back_trellis_proceed(mfcc->f, mfcc->param, p, FALSE) == FALSE) {
	mfcc->segmented = TRUE;
	break_decode = TRUE;
      }
      if (p->config->successive.enabled) {
	if (detect_end_of_segment(p, mfcc->f - 1)) {
	  /* セグメント終了検知: 第１パスここで中断 */
	  mfcc->segmented = TRUE;
	  break_decode = TRUE;
	}
      }
    }
  }

  /* セグメントすべきかどうか最終的な判定を行う．
     デコーダベースVADあ､・いﾏ spsegment のｾ・隋な�数インスタンス間�ﾇ OR
     を取､・イ泙拭､GMMなど複数基準があ､・・腓牢霆犂屬ﾇ AND を取､・･*/
  /* determine whether to segment at here
     If multiple segmenter exists, take their AND */
  break_flag = FALSE;
  if (break_decode
      ) {
    break_flag = TRUE;
  }

  if (break_flag) {
    /* 探索処理の終了が発生したのでここで認識を終え､・ 
       最初のフ･・璽爐�ぁ�[f-1] 番目までが認識さ､・燭海箸砲覆・    */
    /* the recognition process tells us to stop recognition, so
       recognition should be terminated here.
       the recognized data are [0..f-1] */

    /* 最終フ･・璽爐・last_time にセット */
    /* set the last frame to last_time */
    for (mfcc = recog->mfcclist; mfcc; mfcc = mfcc->next) {
      mfcc->last_time = mfcc->f - 1;
    }

    if (! recog->jconf->decodeopt.segment) {
      /* ショートポーズ以外で切､・疹・隋せ弔蠅離汽鵐廛・惑Ъ韻擦困房里討・*/
      /* drop rest inputs if segmented by error */
      for (mfcc = recog->mfcclist; mfcc; mfcc = mfcc->next) {
	mfcc->param->header.samplenum = mfcc->f;
	mfcc->param->samplenum = mfcc->f;
      }
    }

    return 1;
  }

  return 0;
}

#ifdef POWER_REJECT
boolean
power_reject(Recog *recog)
{
  MFCCCalc *mfcc;

  for (mfcc = recog->mfcclist; mfcc; mfcc = mfcc->next) {
    /* skip if not realtime and raw file processing */
    if (mfcc->avg_power == 0.0) continue;
    if (debug2_flag) jlog("STAT: power_reject: MFCC%02d: avg_power = %f\n", mfcc->id, mfcc->avg_power / mfcc->param->samplenum);
    if (mfcc->avg_power / mfcc->param->samplenum < recog->jconf->reject.powerthres) return TRUE;
  }
  return FALSE;
}
#endif

/** 
 * <EN>
 * @brief  End procedure of the first pass (when segmented)
 *
 * This function do things for ending the first pass and prepare for
 * the next recognition, when the input was segmented at the middle of
 * recognition by some reason.
 *
 * First, the best path at each recognition process instance will be parsed
 * and stored.  In case of recognition error or input rejection, the error
 * status will be set.
 *
 * Then, the last pause segment of the processed input will be cut and saved
 * to be processed at first in the recognition of the next or remaining input.
 * 
 * </EN>
 * <JA>
 * @brief  ﾂ・パスの終了処理（セグメント時）
 * 
 * 入力が何らかの事由によって途中でセグメントさ､・浸�に，臓Ε僖垢稜Ъ噂萢�､・ * 終了して次回再開す､・燭瓩僚萢�を行�ｦ. 
 *
 * まず，各認識処理インスタンスに対して，最尤単ｸ・藁鵑鮓�付け，臓Ε僖垢�
 * 認識ｷ・未箸靴導頁爾垢・ また，認識失敗・入力棄却の時はエラーステータスをそ
 * ､・召・札奪箸垢・
 * 
 * そして，次回の認識で，次のセグメントの認識を，検出さ､・針�尾雑�ｻ
 * 区間から再開す､・燭瓩法い修遼�尾雑音区間を切ぁπしておく処理を呼�ﾖ. 
 * 
 * </JA>
 * 
 * @param recog [in] engine instance
 * 
 * @callgraph
 * @callergraph
 */
void
decode_end_segmented(Recog *recog)
{
  boolean ok_p;
  int mseclen;
  RecogProcess *p;
  int last_status;

  /* rejectshort 指ﾄ・��, 入力が短け､・个海海蚤・パスｷ・未鮟侘呂靴覆､ */
  /* suppress 1st pass output if -rejectshort and input shorter than specified */
  ok_p = TRUE;
  if (recog->jconf->reject.rejectshortlen > 0) {
    mseclen = (float)recog->mfcclist->last_time * (float)recog->jconf->input.period * (float)recog->jconf->input.frameshift / 10000.0;
    if (mseclen < recog->jconf->reject.rejectshortlen) {
      last_status = J_RESULT_STATUS_REJECT_SHORT;
      ok_p = FALSE;
    }
  }

#ifdef POWER_REJECT
  if (ok_p) {
    if (power_reject(recog)) {
      last_status = J_RESULT_STATUS_REJECT_POWER;
      ok_p = FALSE;
    }
  }
#endif

  if (ok_p) {
    for(p=recog->process_list;p;p=p->next) {
      if (!p->live) continue;
      finalize_1st_pass(p, p->am->mfcc->last_time);
    }
  } else {
    for(p=recog->process_list;p;p=p->next) {
      if (!p->live) continue;
      p->result.status = last_status;
    }
  }
  if (recog->jconf->decodeopt.segment) {
    finalize_segment(recog);
  }

  if (recog->gmm != NULL) {
    /* GMM 計算の終了 */
    gmm_end(recog);
  }
}

/** 
 * <EN>
 * @brief  End procedure of the first pass
 *
 * This function finish the first pass, when the input was fully
 * processed to the end.
 *
 * The best path at each recognition process instance will be parsed
 * and stored.  In case of recognition error or input rejection, the
 * error status will be set.
 *
 * </EN>
 * <JA>
 * @brief  ﾂ・パスの終了処理
 * 
 * 入力が最後まで処理さ､・峠�了したときに，臓Ε僖垢稜Ъ噂萢�､・ * 終了させ､・ 
 *
 * 各認識処理インスタンスに対して，その時点でのﾂ・パスの最尤単ｸ・ * 系列を格納す､・ また，認識失敗・入力棄却の時はエラーステータスをそ
 * ､・召・札奪箸垢・
 * 
 * </JA>
 * 
 * @param recog [in] engine instance
 * 
 * @callgraph
 * @callergraph
 */
void
decode_end(Recog *recog)
{
  MFCCCalc *mfcc;
  int mseclen;
  boolean ok_p;
  RecogProcess *p;
  int last_status;

  for (mfcc = recog->mfcclist; mfcc; mfcc = mfcc->next) {
    mfcc->segmented = FALSE;
  }

  if (recog->gmm != NULL) {
    /* GMM 計算の終了 */
    gmm_end(recog);
  }

#ifdef GMM_VAD
  /* もしト･・�がかからないまま入力終了に達したのなら，そのままエラー終�ｻ */
  if (recog->jconf->decodeopt.segment) {
    if (recog->gmm) {
      if (recog->gc->after_trigger == FALSE) {
	for(p=recog->process_list;p;p=p->next) {
	  p->result.status = J_RESULT_STATUS_ONLY_SILENCE;	/* reject by decoding */
	}
	/* ショートポーズセグメンテーションのｾ・・
	   入力パラメータ分割などの最終処理も行なう */
	/* When short-pause segmentation enabled */
	finalize_segment(recog);
	return;
      }
    }
  }
#endif

  /* 第１パスの最後のフ･・璽爐稜Ъ噂萢�を行�ｦ */
  /* finalize 1st pass */
  for(p=recog->process_list;p;p=p->next) {
    if (!p->live) continue;
#ifdef SPSEGMENT_NAIST
    if (recog->jconf->decodeopt.segment) {
      if (p->pass1.after_trigger == FALSE) continue;
    }
#endif
    mfcc = p->am->mfcc;
    if (mfcc->f > 0) {
      get_back_trellis_end(mfcc->param, p);
    }
  }

  /* 終了処理 */
  for(p=recog->process_list;p;p=p->next) {
    if (!p->live) continue;

    ok_p = TRUE;

    /* check rejection by no input */
    if (ok_p) {
      mfcc = p->am->mfcc;
      /* 入力長がデ･・燭侶彁擦暴淑�でない勝�隋て�力無しとすぁ�･ */
      /* if input is short for compute all the delta coeff., terminate here */
      if (mfcc->f == 0) {
//	jlog("STAT: no input frame\n");
	last_status = J_RESULT_STATUS_FAIL;
	ok_p = FALSE;
      }
    }

    /* check rejection by input length */
    if (ok_p) {
      if (recog->jconf->reject.rejectshortlen > 0) {
	mseclen = (float)mfcc->param->samplenum * (float)recog->jconf->input.period * (float)recog->jconf->input.frameshift / 10000.0;
	if (mseclen < recog->jconf->reject.rejectshortlen) {
	  last_status = J_RESULT_STATUS_REJECT_SHORT;
	  ok_p = FALSE;
	}
      }
    }

#ifdef POWER_REJECT
    /* check rejection by average power */
    if (ok_p) {
      if (power_reject(recog)) {
	last_status = J_RESULT_STATUS_REJECT_POWER;
	ok_p = FALSE;
      }
    }
#endif

#ifdef SPSEGMENT_NAIST
    /* check rejection non-triggered input segment */
    if (ok_p) {
      if (recog->jconf->decodeopt.segment) {
	if (p->pass1.after_trigger == FALSE) {
	  last_status = J_RESULT_STATUS_ONLY_SILENCE;	/* reject by decoding */
	  ok_p = FALSE;
	}
      }
    }
#endif

    if (ok_p) {
      /* valid input segment, finalize it */
      finalize_1st_pass(p, mfcc->param->samplenum);
    } else {
      /* invalid input segment */
      p->result.status = last_status;
    }
  }
  if (recog->jconf->decodeopt.segment) {
    /* ショートポーズセグメンテーションのｾ・・
       入力パラメータ分割などの最終処理も行なう */
    /* When short-pause segmentation enabled */
    finalize_segment(recog);
  }
}


/** 
 * <JA>
 * @brief  フ･・璽狷唄・咫璽狠戯�メイン関数（バッチ処理用�ﾋ
 *
 * 与えら､・親�力ベクトァ�鵑紡个靴涜茖吋僖ｹ(フ･・璽狷唄・咫璽狠戯・､・ * 行い，そのｷ・未鮟侘呂垢・ また全フ･・璽爐謀呂・姥・�端を，第２パ�ｹ
 * のために単ｸ・肇・・更渋ぢ里乏頁爾垢・ 
 * 
 * この関数は入力ベクト･・鵑�あらかじめ得らぁζいぁΑ�腓僕僂い蕕・・ 
 * 第１パスが入力と並列して実行さ､・・�ンライン認識の勝�隋､
 * この関数は用いら､・此ぢ紊・蠅砲海離侫．ぅ・把・舛気・討い・謄汽峇愎瑤ｬ
 * 直接 realtime-1stpass.c 内から呼ば､・・ 
 * 
 * @param recog [in] エンジンインスタンス
 * </JA>
 * <EN>
 * @brief  Frame synchronous beam search: the main (for batch mode)
 *
 * This function perform the 1st recognition pass of frame-synchronous beam
 * search and output the result.  It also stores all the word ends in every
 * input frame to word trellis structure.
 *
 * This function will be called if the whole input vector is already given
 * to the end.  When online recognition, where the 1st pass will be
 * processed in parallel with input, this function will not be used.
 * In that case, functions defined in this file will be directly called
 * from functions in realtime-1stpass.c.
 * 
 * @param recog [in] engine instance
 * </EN>
 * @callgraph
 * @callergraph
 */
boolean
get_back_trellis(Recog *recog)
{
  boolean ok_p;
  MFCCCalc *mfcc;
  int rewind_frame;
  PROCESS_AM *am;
  boolean reprocess;

  /* initialize mfcc instances */
  for(mfcc=recog->mfcclist;mfcc;mfcc=mfcc->next) {
    /* mark all as valid, since all frames are fully prepared beforehand */
    if (mfcc->param->samplenum == 0) mfcc->valid = FALSE;
    else mfcc->valid = TRUE;
    /* set frame pointers to 0 */
    mfcc->f = 0;
  }

  recog->triggered = TRUE;

  while(1) {
    ok_p = TRUE;
    for (mfcc = recog->mfcclist; mfcc; mfcc = mfcc->next) {
      if (! mfcc->valid) continue;
      if (mfcc->f < mfcc->param->samplenum) {
	mfcc->valid = TRUE;
	ok_p = FALSE;
      } else {
	mfcc->valid = FALSE;
      }
    }
    if (ok_p) {
      /* すべての MFCC が終､・蠅肪�したのでァ�璽彌��ｻ */
      /* all MFCC has been processed, end of loop  */
      break;
    }

    switch (decode_proceed(recog)) {
    case -1: /* error */
      return FALSE;
      break;
    case 0:			/* success */
      break;
    case 1:			/* segmented */
      /* 探索中断: 処理さ､・親�力�ﾏ 0 か､・t-2 まで */
      /* search terminated: processed input = [0..t-2] */
      /* この時点でﾂ・パスを終了す､・*/
      /* end the 1st pass at this point */
      decode_end_segmented(recog);
      /* terminate 1st pass here */
      return TRUE;
    }


//    if (spsegment_need_restart(recog, &rewind_frame, &reprocess) == TRUE) {
//      /* do rewind for all mfcc here */
//      spsegment_restart_mfccs(recog, rewind_frame, reprocess);
//      /* reset outprob cache for all AM */
//      for(am=recog->amlist;am;am=am->next) {
//	outprob_prepare(&(am->hmmwrk), am->mfcc->param->samplenum);
//      }
//    }
    /* call frame-wise callback */
//    callback_exec(CALLBACK_EVENT_PASS1_FRAME, recog);

    /* 1フ･・璽狃萢�が進んだのでポインタを進めぁ�*/
    /* proceed frame pointer */
    for (mfcc = recog->mfcclist; mfcc; mfcc = mfcc->next) {
      if (!mfcc->valid) continue;
      mfcc->f++;
    }

  }

  /* 最終フ･・璽狃萢�を行い，認識の掘μ出力と終了処理を行�ｦ */
  decode_end(recog);

  return TRUE;
}

/* end of file */
