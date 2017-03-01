#pragma once

#include "2DWindow.h"
#include "Trick.h"
#include "define.h"

class CUnit;
class CMenuWindow;

class CTrickWindow:
	public CTrick,
	public C2DWindow
{
private:
	//シングルトン
	static CTrickWindow* m_pTrickWindow;

	CTrick				m_Trick[TRICK_NUM_MAX];			//技データ(技の持てる数)
	LPD3DXFONT			m_Font;							//描画用フォント
	RECT				m_Pos[TRICK_NUM_MAX];			//ウィンドウ表示位置
	bool				m_bDrawFlg;							//描画フラグ

	CUnit*				m_pPlayer;
	CMenuWindow*		m_pMenuWindow;

	VERTEX_2D				m_aVertex[TRICK_NUM_MAX][NUM_VERTEX];	//ポリゴン頂点情報格納用

	int					m_nInputInterval;		//ボタン入力してからの経過時間

	CTrickWindow(void);							//コンストラクタ
	~CTrickWindow(void);						//デストラクタ
public:
	static void Create();						//実体の作成
	static void Delete();						//実体の削除
	static CTrickWindow* GetPointer();			//実体のポインタを渡す

	void UpDate();								//更新部
	void Draw();								//描画

	void DrawFlgChange();				//描画フラグをON/OFFする

	void SetVertex();							//ポリゴン情報を埋める
	void SetFontPos();							//フォント描画位置設定

	//描画のフラグ状況を取得
	bool GetDrawFlg()	{return m_bDrawFlg;}

	//指定された技データを渡す
	CTrick GetTrick (int Coefficient)	{return m_Trick[Coefficient];}

	//指定されたアイテムの名前を返す
	_TCHAR* GetTrickName(int Coefficient){return m_Trick[Coefficient].GetName();}

	//指定された技の範囲を返す
	int GetRange(int Receipt);

	int GetEffect(int Receipt);					//指定されたアイテムの効果ジャンルを返却

	int GetEffectValue(int Receipt);			//指定されたアイテムの効能を返却する

	void FindName	(int nID,int Receipt);		//IDから名前を検索する

	//メンバ変数のポインタを設定する
	void SetPointer();
};

