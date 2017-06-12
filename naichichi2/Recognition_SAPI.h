﻿// Recognition_SAPI.h: Recognition_SAPI クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_Recognition_SAPI_H__1477FE93_D7A8_4F29_A369_60E33C71B2B7__INCLUDED_)
#define AFX_Recognition_SAPI_H__1477FE93_D7A8_4F29_A369_60E33C71B2B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <atlbase.h>
#include <sapi.h>
#include <sphelper.h>

class Recognition_SAPI  : public ISpeechRecognitionInterface
{
public:
	Recognition_SAPI();
	virtual ~Recognition_SAPI();
	//音声認識のためのオブジェクトの構築.
	virtual bool Create(MainWindow* poolMainWindow);

	//呼びかけを設定します。
	//設定したあと、 CommitRule() てしてね。
	virtual bool SetYobikake(const list<string> & yobikakeList);
	//認識結果で不感染なものを捨てる基準値を設定します。
	virtual bool SetRecognitionFilter(double yobikakeRuleConfidenceFilter,double basicRuleConfidenceFilter,bool useDictationFilter);
	//コマンドに反応する音声認識ルールを構築します
	virtual bool AddCommandRegexp(const CallbackDataStruct * callback,const string & str);
	//構築したルールを音声認識エンジンにコミットします。
	virtual bool CommitRule();
	//このコールバックに関連付けられているものをすべて消す
	virtual bool RemoveCallback(const CallbackDataStruct* callback , bool is_unrefCallback) ;
	//メディア情報をアップデートします。
	virtual bool UpdateMedia(const string& name ,const list<string>& list );
private:
	//認識した結果の解析
	bool CallbackReco();
	void Callback(WPARAM wParam, LPARAM lParam);
	//マッチしたphraseから正規表現キャプチャ () による文字列の抽出.
	bool PhraseToRegexpCapture(SPPHRASE *pPhrase,map<string , string>* capture, double * SREngineConfidenceAvg) const;
	//ディクテーションフィルターで呼びかけ文字列が入っているか確認する.
	bool checkDictation(const string & dictationString) const;
	//ルールベースで認識した結果の音声部分をもう一度 ディクテーションにかけて認識した結果を取得します。
	string convertDictation(ISpRecoResult* result,const string& ruleName);
	//音声認識ルールを構築します。 正規表現にも対応しています。
	bool AddRegexp(unsigned int id,const string & str ,SPSTATEHANDLE stateHandle ) ;
	//音声認識ルールを登録する部分の詳細な実行です。正規表現のネストがあるので再起してます。
	bool AddRegexpImpl(const SPPROPERTYINFO* prop,const wstring & str, SPSTATEHANDLE stateHandle);
	//デバッグ用 認識結果をWaveファイルとして保存する
	bool DebugSaveWavFile(const string& directory,ISpStreamFormat* streamFormat) const;
private:
	//ルールベース
	CComPtr<ISpRecognizer>		RuleEngine;
	CComPtr<ISpRecoContext>		RuleRecoCtxt;
	CComPtr<ISpRecoGrammar>		RuleGrammar;

	//Dictation
	CComPtr<ISpRecognizer>		DictationEngine;
	CComPtr<ISpRecoContext>		DictationRecoCtxt;
	CComPtr<ISpRecoGrammar>		DictationGrammar;
	UINT								GlobalRuleNodeCount ;
	UINT								LocalCaptureRuleNodeCount ;
	SPSTATEHANDLE FilterRuleHandleHandle;
	SPSTATEHANDLE FilterRuleHandleHandle2;

	SPSTATEHANDLE YobikakeRuleHandle;
	SPSTATEHANDLE CommandRuleHandle;

	SPSTATEHANDLE MusicRuleHandle;
	SPSTATEHANDLE VideoRuleHandle;
	SPSTATEHANDLE BookRuleHandle;

	bool   UseDictationFilter;
	double YobikakeRuleConfidenceFilter;
	double BasicRuleConfidenceFilter;
	list<string> YobikakeListArray;

	MainWindow* PoolMainWindow;

	vector<const CallbackDataStruct*> CallbackDictionary;
};

#endif // !defined(AFX_Recognition_SAPI_H__1477FE93_D7A8_4F29_A369_60E33C71B2B7__INCLUDED_)
