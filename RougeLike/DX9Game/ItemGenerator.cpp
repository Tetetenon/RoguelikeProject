#include "ItemGenerator.h"
#include "FieldItem.h"
#include "Input.h"

//静的メンバ実体定義
int CItemGenerator::m_MaxFieldItem;		//フィールド上の最大アイテム再生数を設定
int CItemGenerator::m_FieldItemCounter;	//フィールド上のアイテム生成数をカウント

//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CItemGenerator::CItemGenerator(CGameScene *pScene):
CMeshObj(pScene)
{
}


//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CItemGenerator::~CItemGenerator(void)
{
}

//---------------------------------------------------------------------------------------
//初期化
//---------------------------------------------------------------------------------------
void CItemGenerator::Init()
{
	//親クラス初期化呼び出し
	CMeshObj::Init();
}

//---------------------------------------------------------------------------------------
//終了処理
//---------------------------------------------------------------------------------------
void CItemGenerator::Fin()
{
	//親クラスの終了処理呼び出し
	CMeshObj::Fin();
}

//---------------------------------------------------------------------------------------
//更新
//---------------------------------------------------------------------------------------
void CItemGenerator::Update()
{
	//デバッグコマンド(宝箱の生成)
	if(CInput::GetKeyTrigger(DIK_X) && m_FieldItemCounter < m_MaxFieldItem)
	{
		//生成
		CFieldItem::Generation(this);

		//生成数加算
		m_FieldItemCounter++;
	}
}
//---------------------------------------------------------------------------------------
//アイテム最大生成数を設定
//---------------------------------------------------------------------------------------
void CItemGenerator::SetMaxItem(int MaxItemNum)
{
	m_MaxFieldItem = MaxItemNum;
}
//---------------------------------------------------------------------------------------
//アイテム最大生成数を再設定
//---------------------------------------------------------------------------------------
void CItemGenerator::ResetMakeItemNum()
{
	m_FieldItemCounter = 0;
}
//---------------------------------------------------------------------------------------
//アイテムを生成
//---------------------------------------------------------------------------------------
void CItemGenerator::MakeItem()
{
	//生成数を設定
	int nMakeNum = rand()%8 + 7;

	//生成
	for(int i = 0;i < nMakeNum;i++)
	{
		//生成
		CFieldItem::Generation(this);

		//生成数加算
		m_FieldItemCounter++;
	}
}