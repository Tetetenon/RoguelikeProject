#pragma once

#include "2DWindow.h"
#include "Trick.h"
#include "define.h"

class CTrickWindowCursor;

class CTrickWindow:
	public CTrick,
	public C2DWindow
{
private:
	CTrick				m_Trick[TRICK_NUM_MAX];	//技データ(技の持てる数)
	LPD3DXFONT			m_Font;					//描画用フォント
	RECT				m_Pos[TRICK_NUM_MAX];	//ウィンドウ表示位置
	static bool			m_bDrawFlg;				//描画フラグ

	VERTEX_2D	m_aVertex[TRICK_NUM_MAX][NUM_VERTEX];	//ポリゴン頂点情報格納用
	static CTrickWindowCursor	m_TrickCursor;			//選択しているアイテムウインドウの取得
public:
	CTrickWindow(void);							//コンストラクタ
	~CTrickWindow(void);						//デストラクタ

	void Init();								//初期化
	void Fin();									//終了処理

	void UpDate();								//更新部
	void Draw();								//描画

	static void DrawFlgChange();				//描画フラグをON/OFFする

	void SetVertex();							//ポリゴン情報を埋める
	void SetFontPos();							//フォント描画位置設定

	//描画のフラグ状況を取得
	static bool GetDrawFlg()	{return m_bDrawFlg;}

	//指定された技データを渡す
	CTrick GetTrick (int Coefficient)	{return m_Trick[Coefficient];}

	//指定されたアイテムの名前を返す
	_TCHAR* GetTrickName(int Coefficient){return m_Trick[Coefficient].GetName();}

	//指定された技の範囲を返す
	int GetRange(int Receipt);

	int GetEffect(int Receipt);					//指定されたアイテムの効果ジャンルを返却

	int GetEffectValue(int Receipt);			//指定されたアイテムの効能を返却する

	void FindName	(int nID,int Receipt);		//IDから名前を検索する

};

