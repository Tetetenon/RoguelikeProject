#include "MapData.h"
#include "Graphics.h"
#include "TextureManager.h"
#include "GameScene.h"

#include <stdlib.h>
#include <tchar.h>

#include<fstream>
#include<iostream>
#include<string>
#include<sstream> //文字ストリーム


//静的メンバ実体定義
Map						CMapData::m_TerrainMap[MAP_SIZE][MAP_SIZE];				//地形マップ情報
Map						CMapData::m_UnitMap[MAP_SIZE][MAP_SIZE];				//ユニットマップ
Map						CMapData::m_ItemMap[MAP_SIZE][MAP_SIZE];				//アイテムマップ

LPDIRECT3DVERTEXBUFFER9 CMapData::m_pD3DVtxBuff;								//頂点バッファインタフェースへのポインタ
LPDIRECT3DINDEXBUFFER9	CMapData::m_pD3DIdxBuff;								//インデックスバッファ
D3DXMATRIX				CMapData::m_mtxWorld;									//ワールドマトリックス

int						CMapData::m_NumVertexIndex;								//インデックス数
int						CMapData::m_NumVertex;									//総頂点数
int						CMapData::m_NumPolygon;									//ポリゴン数
RECT					CMapData::m_Section[ROOM_MAX_NUM];						//区画
RECT					CMapData::m_Room[ROOM_MAX_NUM];							//部屋

int						CMapData::m_CountMakeRoom;								//実際に生成した部屋の数
int						CMapData::m_nHierarchyNum;								//階層数


LPD3DXFONT				CMapData::m_pFont;										//描画フォントの設定
RECT					CMapData::m_FontDrawPos;								//フォントの描画位置を設定する
int						CMapData::m_nDividPattern;								//生成するマップパターン

AStar					CMapData::m_AStarData[MAP_SIZE][MAP_SIZE];				//A*アルゴリズムに使用する構造体
AStarList*				CMapData::m_pAstarList;									//A*アルゴリズムで次の探索候補のデータを保存する
//---------------------------------------------------------------------------------------
//　コンストラクタ
//---------------------------------------------------------------------------------------
CMapData::CMapData(void)
{
	int nFloorCounter = 0;

	//マップを生成
	MapGeneration();

	//マップの床数を数える
	for(int i = 0;i < MAP_SIZE;i++)
	{
		for(int j = 0;j < MAP_SIZE;j++)
		{
			//マップ情報が床なら加算
			if(CMapData::Get_TerrainMapSituation(i,j) == FLOOR)
				nFloorCounter ++;
		}
	}

	//ユニットの最大設置可能数を設定
	CEnemyGenerator::SetMaxGenerator((int)nFloorCounter / 5);

	//アイテムの最大生成数を設定
	CItemGenerator::SetMaxItem(10 + rand()%10);

	//アイテムマップ初期化
	for(int i = 0;i < MAP_SIZE;i++)
	{
		for(int j = 0;j < MAP_SIZE;j++)
			m_ItemMap[i][j].m_Map_Situation = 0;
	}

	//ユニットマップ初期化
	for(int i = 0;i < MAP_SIZE;i++)
	{
		for(int j = 0;j < MAP_SIZE;j++)
			m_UnitMap[i][j].m_Map_Situation = 0;
	}

	//デバイス格納
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();

	//-----頂点の作成-----

	//頂点数設定(縮退ポリゴン考慮)
	m_NumVertex = (MAP_SIZE + 1) * MAP_SIZE * 2 + (MAP_SIZE - 1) * 2;

	//インデックス数の設定(縮退ポリゴンを考慮)
	m_NumVertexIndex = (MAP_SIZE + 1) * 2 * MAP_SIZE + (MAP_SIZE - 1) * 2;

	//ポリゴン数(縮退ポリゴン考慮)
	m_NumPolygon = MAP_SIZE * MAP_SIZE * 2 + (MAP_SIZE - 1) * 4;

	// オブジェクトの頂点バッファを生成
	if( FAILED( pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * m_NumVertex,
		// 頂点データ用に確保するバッファサイズ
		D3DUSAGE_WRITEONLY,	// 頂点バッファの使用法
		FVF_VERTEX_3D,	// 使用する頂点フォーマット
		D3DPOOL_MANAGED,
		// リソースのバッファを保持するメモリクラスを指定
		&m_pD3DVtxBuff,
		// 頂点バッファインタフェースへのポインタ
		NULL )))
	{
		LPCTSTR szMsg = _T("動作不良!");
		MessageBox(NULL, szMsg, NULL, MB_OK);
	}

	if( FAILED( pDevice->CreateIndexBuffer( sizeof( WORD ) * m_NumVertexIndex,
	// インデックスデータ用に確保するバッファサイズ（バイト）
		D3DUSAGE_WRITEONLY,		// 使用法
		D3DFMT_INDEX16,			// フォーマット
		D3DPOOL_MANAGED,		// リソースのバッファを保持するメモリクラスを指定
		&m_pD3DIdxBuff,	//
		NULL )))
	{
		LPCTSTR szMsg = _T("失敗!");
		MessageBox(NULL, szMsg, NULL, MB_OK);
	}

	// 1枚の四角形ポリゴンに張り付けるテクスチャのサイズ
	const float fSizeTexX = 1.0f;
	const float fSizeTexZ = 1.0f;

	//頂点バッファの中身を埋める
	VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし
		// 頂点バッファへのポインタを取得
	m_pD3DVtxBuff->Lock( 0, 0,(void**)&pVtx, 0 );

	//頂点情報の設定
	for( int nCntZ = 0; nCntZ < MAP_SIZE + 1; nCntZ ++ )
	{
		for( int nCntX = 0; nCntX < MAP_SIZE + 1; nCntX ++ )
		{
			pVtx[nCntZ * (MAP_SIZE + 1) + nCntX].vtx.x = -MAP_SIZE / 2.0f * MASS_SIZE + nCntX * MASS_SIZE;
			pVtx[nCntZ * (MAP_SIZE + 1) + nCntX].vtx.y = 0.0f;
			pVtx[nCntZ * (MAP_SIZE + 1) + nCntX].vtx.z = MAP_SIZE / 2.0f * MASS_SIZE - nCntZ * MASS_SIZE;
			// 法線
			pVtx[nCntZ * (MAP_SIZE + 1) + nCntX].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
			// 反射光
			pVtx[nCntZ * (MAP_SIZE + 1) + nCntX].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[nCntZ * (MAP_SIZE + 1) + nCntX].diffuse = D3DXCOLOR(0.3f, 0.3f, 0.3f, 1.0f);
			// テクスチャ座標
			pVtx[nCntZ * (MAP_SIZE + 1) + nCntX].tex.x = (float)MASS_SIZE * nCntX / 3;
			pVtx[nCntZ * (MAP_SIZE + 1) + nCntX].tex.y = (float)MASS_SIZE * nCntZ / 3;
		}
	}

	// 頂点データをアンロックする
	m_pD3DVtxBuff->Unlock();

	// インデックスバッファの中身を埋める
	WORD *pIdx;
	
	// インデックスデータの範囲をロックし頂点バッファへのポインタを取得
	m_pD3DIdxBuff->Lock( 0, 0, (void**)&pIdx, 0 );
	
	int nCntIdx = 0;

	for( int nCntZ = 0; nCntZ < MAP_SIZE; nCntZ ++ )
	{
		if( nCntZ > 0 )
		{	
			// 縮退ポリゴンのためのダブりを設定
			pIdx[nCntIdx] = ( nCntZ + 1 ) * ( MAP_SIZE + 1 );
			nCntIdx ++;
		}
		for( int nCntX = 0; nCntX < MAP_SIZE + 1; nCntX ++ )
		{
			pIdx[nCntIdx] = ( nCntZ + 1 ) * ( MAP_SIZE + 1 ) + nCntX;
			nCntIdx ++;
			pIdx[nCntIdx] = nCntZ * ( MAP_SIZE + 1 ) + nCntX;
			nCntIdx ++;
		}
	
		if( nCntZ < MAP_SIZE - 1 )
		{	
			// 縮退ポリゴンのためのダブりを設定
			pIdx[nCntIdx] = nCntZ * ( MAP_SIZE + 1 ) + MAP_SIZE;
			nCntIdx ++;
		}
	}

	// 頂点データをアンロックする
	m_pD3DIdxBuff->Unlock();

	//階層数を初期化
	m_nHierarchyNum = 1;
	
	//フォントへのポインタを取得する
	D3DXCreateFont(pDevice,24,0,1,0,FALSE,SHIFTJIS_CHARSET,OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,NULL,&m_pFont);
	//フォント描画位置を設定
	SetFontPos();
}

//---------------------------------------------------------------------------------------
// デストラクタ
//---------------------------------------------------------------------------------------
CMapData::~CMapData(void)
{
	//A*で用いたデータの初期化
	InitAStarData();
	//頂点バッファの開放
	SAFE_RELEASE(m_pD3DVtxBuff);
	//インデックスバッファの開放
	SAFE_RELEASE(m_pD3DIdxBuff);
}

//---------------------------------------------------------------------------------------
// 初期化
//---------------------------------------------------------------------------------------
void CMapData::Init()
{
}
//---------------------------------------------------------------------------------------
//文字描画位置を設定
//---------------------------------------------------------------------------------------
void CMapData::SetFontPos()
{
	m_FontDrawPos.left		= (LONG)125.0f;
	m_FontDrawPos.top		= (LONG)100.0f;
	m_FontDrawPos.right		= (LONG)230.0f;
	m_FontDrawPos.bottom	= (LONG)120.0f;
}
//---------------------------------------------------------------------------------------
// 更新
//---------------------------------------------------------------------------------------
void CMapData::UpDate()
{
	
	VERTEX_3D *pVtx;

	// 頂点エータの範囲をロックし、頂点バッファへのポインタを取得
	m_pD3DVtxBuff->Lock( 0, 0, (void**)&pVtx, 0);

	// 頂点データをアンロックする
	m_pD3DVtxBuff->Unlock();
}
//---------------------------------------------------------------------------------------
// 描画
//---------------------------------------------------------------------------------------
void CMapData:: Draw()
{
	///デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
	
	//ライティングを一時的に切る
	pDevice->SetRenderState(D3DRS_LIGHTING,false);
	// ワールドマトリクスの初期化
	D3DXMatrixIdentity( &m_mtxWorld );
		
	// ワールドマトリクスの設定
	pDevice->SetTransform( D3DTS_WORLD, &m_mtxWorld );

	// この後に描画
	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource( 0,
		m_pD3DVtxBuff, 0,
		sizeof(VERTEX_3D) );

	// インデックスバッファをレンダリングパイプラインに設定
	pDevice->SetIndices( m_pD3DIdxBuff );

	// 頂点フォーマットの設定
	pDevice->SetFVF( FVF_VERTEX_3D );

	//フィールドの位置マスごとに配列状態を確認し、出力内容を変更する
	for(int i = 0;i < MAP_SIZE;i++)
	{
		for(int j = 0;j<MAP_SIZE;j++)
		{
			switch(m_TerrainMap[i][j].m_Map_Situation)
			{
				//床
				case FLOOR:
					pDevice->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_FLOOR));
				break;
				//壁
				case WALL_UP:
				case WALL_DOWN:
				case WALL_RIGH:
				case WALL_LEFT:
					pDevice->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_WALL));
				break;
				//壁中
				case IN_THE_WALL:
					pDevice->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_IN_THE_WALL));
				break;
				//デフォルトは床
				default:
					pDevice->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_IN_THE_WALL));
				break;
			}
			// ポリゴンの描画
			pDevice->DrawIndexedPrimitive(
				D3DPT_TRIANGLESTRIP,
				i * (MAP_SIZE + 1) + j,	// 頂点バッファのベース位置
				0,	// 頂点バッファの使用開始位置
				3,
				0,	// インデックスバッファの開始位置
				2);
		}
	}
	
	//ライティングを戻す
	pDevice->SetRenderState(D3DRS_LIGHTING,true);
}
//---------------------------------------------------------------------------------------
// 終了処理
//---------------------------------------------------------------------------------------
void CMapData:: Fin()
{
}
//---------------------------------------------------------------------------------------
// 指定した地形の状態を返す
//---------------------------------------------------------------------------------------
int CMapData::Get_TerrainMapSituation (int PosX,int PosY)
{
	//範囲外を読み込んだ場合、エラー値を返す
	if(PosX < 0 || PosX > MAP_SIZE || PosY < 0 || PosY > MAP_SIZE)
		return ERROR_NUM;
	return m_TerrainMap[PosY][PosX].m_Map_Situation;
}
//---------------------------------------------------------------------------------------
// 指定した位置のユニット生存状態を返す
//---------------------------------------------------------------------------------------
int CMapData::Get_UnitMapSituation(int PosX,int PosY)
{
	//範囲外を読み込んだ場合、エラー値を返す
	if(PosX < 0 || PosX > MAP_SIZE || PosY < 0 || PosY > MAP_SIZE)
		return ERROR_NUM;
	return m_UnitMap[PosY][PosX].m_Map_Situation;
}
//---------------------------------------------------------------------------------------
// 指定した位置のアイテム状態を返す
//---------------------------------------------------------------------------------------
int CMapData::Get_ItemMapSituation(int PosX,int PosY)
{
	//範囲外を読み込んだ場合、エラー値を返す
	if(PosX < 0 || PosX > MAP_SIZE || PosY < 0 || PosY > MAP_SIZE)
		return ERROR_NUM;
	return m_ItemMap[PosY][PosX].m_Map_Situation;
}


//---------------------------------------------------------------------------------------
// 指定した位置情報をもとに戻す
//---------------------------------------------------------------------------------------
void CMapData:: Back_UnitMap(int PosX,int PosY)
{
	m_UnitMap[PosY][PosX].m_Map_Situation = 0;
}
//---------------------------------------------------------------------------------------
// 指定した位置情報を変更する
//---------------------------------------------------------------------------------------
void CMapData:: Set_UnitMap(int PosX,int PosY,int Change)
{
	m_UnitMap[PosY][PosX].m_Map_Situation = Change;
}
//---------------------------------------------------------------------------------------
// 指定した位置情報をもとに戻す
//---------------------------------------------------------------------------------------
void CMapData:: Back_ItemMap(int PosX,int PosY)
{
	m_ItemMap[PosY][PosX].m_Map_Situation = 0;
}
//---------------------------------------------------------------------------------------
// 指定した位置情報を変更する
//---------------------------------------------------------------------------------------
void CMapData:: Set_ItemMap(int PosX,int PosY,int Change)
{
	m_ItemMap[PosY][PosX].m_Map_Situation = Change;
}
//---------------------------------------------------------------------------------------
// マップをすべて初期化する
//---------------------------------------------------------------------------------------
void CMapData::AllInitMapData()
{
	for(int i = 0;i < MAP_SIZE;i++)
	{
		for(int j = 0;j < MAP_SIZE;j++)
		{
			m_TerrainMap[j][i].m_Map_Situation = IN_THE_WALL;
			m_UnitMap[j][i].m_Map_Situation = 0;
			m_ItemMap[j][i].m_Map_Situation = 0;
		}
	}

	for(int i = 0;i < ROOM_MAX_NUM;i++)
	{
		m_Section[i].top    = 0;
		m_Section[i].bottom = 0;
		m_Section[i].right	= 0;
		m_Section[i].left	= 0;
		
		m_Room[i].top		= 0;
		m_Room[i].bottom	= 0;
		m_Room[i].right		= 0;
		m_Room[i].left		= 0;
	}
}

//---------------------------------------------------------------------------------------
// マップを生成する
//---------------------------------------------------------------------------------------
void CMapData::MapGeneration()
{
	//マップデータの初期化
	AllInitMapData();

	//マップの区画分け
	DivideMap();

	//区画内に部屋を作る
	MakeRoom();

	//部屋から部屋への通路を作成する
	MakeRoot();

	//階段をどこかの部屋の中に設定する
	StairsSet();

	//階層数加算
	m_nHierarchyNum ++;

	
	//10階層移動したら、シーンをゲームクリアに遷移させる
	if(m_nHierarchyNum > 10)
	{
		//ゲームのクリア状況をクリアに変更する
		CGameScene::GameClearFlgChange(true);

		//ゲームメインを終了
		CGameScene::FadeOutStart();

		//エネミーの生成数のリセット
		CEnemyGenerator::ResetMakeEnemyNum();
		//フィールドアイテム生成数のリセット
		CItemGenerator::ResetMakeItemNum();
	}

}
//---------------------------------------------------------------------------------------
// マップの区画分け
//---------------------------------------------------------------------------------------
void CMapData::DivideMap()
{
	//残った区画
	int RemainingZone_X = MAP_SIZE;
	int RemainingZone_Z = MAP_SIZE;


	//境界線を決定するときに使用
	int BorderLineX = 0;
	int BorderLineZ = 0;

	//人区画当たりのサイズ
	int OneRoomX = 0;
	int OneRoomZ = 0;

	//３パターンの中から、ランダムに選択し、区画を分ける
	m_nDividPattern = rand()%4;
	//m_nDividPattern = 3;

	switch(m_nDividPattern)
	{
		//一区画ずつ分ける
	case 0:
		//-----境界線を引く& 区画を作る-----
		for(m_CountMakeRoom = 0;m_CountMakeRoom < ROOM_MAX_NUM;m_CountMakeRoom ++)
		{
			//まだ区画を作れるだけの領域があるか確認
			if(RemainingZone_X < SECTION_MAX_SIZE || RemainingZone_Z < SECTION_MAX_SIZE)
				break;

			//奇数個の区画の横幅を設定する
			BorderLineX = rand()%SECTION_MAX_SIZE;

			//横幅が最低限の幅を取れなければ取れるまでする
			while(BorderLineX < SECTION_MIN_SIZE)
			{
				//最初の区画の横幅を設定する
				BorderLineX = rand()%SECTION_MAX_SIZE;
			}

			//区画サイズを決定
			m_Section[m_CountMakeRoom].top	= 0;
			m_Section[m_CountMakeRoom].bottom = RemainingZone_Z;

			m_Section[m_CountMakeRoom].right	= RemainingZone_X;
			m_Section[m_CountMakeRoom].left	= RemainingZone_X - BorderLineX;

			//残りの幅を減らす
			RemainingZone_X -= BorderLineX;
			
			//次の区画を策定しに行く!
			m_CountMakeRoom ++;
			
			//まだ区画を作れるだけの領域があるか確認
			if(RemainingZone_X < SECTION_MAX_SIZE || RemainingZone_Z < SECTION_MAX_SIZE)
				break;

			//偶数個の区画の縦幅を設定
			BorderLineZ = rand()%SECTION_MAX_SIZE;

			//縦幅が最低限の幅を取れていなければ、取れるまでループ
			while(BorderLineZ < SECTION_MIN_SIZE)
			{
				BorderLineZ = rand()%SECTION_MAX_SIZE;
			}

			//区画サイズを決定
			m_Section[m_CountMakeRoom].top	= RemainingZone_Z - BorderLineZ;
			m_Section[m_CountMakeRoom].bottom = RemainingZone_Z;

			m_Section[m_CountMakeRoom].right	= RemainingZone_X;
			m_Section[m_CountMakeRoom].left	= 0;

			//残りの高さを減らす
			RemainingZone_Z -= BorderLineZ;
		}
		break;

		//全区画均等に当分
	case 1:
		{
			int RoomNumX = (RemainingZone_X / SECTION_MIN_SIZE);
			int RoomNumZ = (RemainingZone_Z / SECTION_MIN_SIZE);

			//マップ上に作れる数を計算
			OneRoomX = RemainingZone_X / RoomNumX;
			OneRoomZ = RemainingZone_Z / RoomNumZ;

			//区画位置を設定
			for(m_CountMakeRoom= 0;m_CountMakeRoom < RoomNumX * RoomNumZ;m_CountMakeRoom++)
			{
				m_Section[m_CountMakeRoom].left = (m_CountMakeRoom % RoomNumX) * OneRoomX;
				m_Section[m_CountMakeRoom].right = (m_CountMakeRoom % RoomNumX) * OneRoomX + OneRoomX;

				m_Section[m_CountMakeRoom].top = (m_CountMakeRoom / RoomNumZ) * OneRoomZ;
				m_Section[m_CountMakeRoom].bottom = (m_CountMakeRoom / RoomNumZ) * OneRoomX + OneRoomZ;
			}
		}
		break;

		//4分割
	case 2:
		{
			int RoomNumX = (RemainingZone_X / SECTION_MAX_SIZE);
			int RoomNumZ = (RemainingZone_Z / SECTION_MAX_SIZE);

			//マップ上に作れる数を計算
			OneRoomX = RemainingZone_X / RoomNumX;
			OneRoomZ = RemainingZone_Z / RoomNumZ;

			//区画位置を設定
			for(m_CountMakeRoom= 0;m_CountMakeRoom < RoomNumX * RoomNumZ;m_CountMakeRoom++)
			{
				m_Section[m_CountMakeRoom].left = (m_CountMakeRoom % RoomNumX) * OneRoomX;
				m_Section[m_CountMakeRoom].right = (m_CountMakeRoom % RoomNumX) * OneRoomX + OneRoomX;

				m_Section[m_CountMakeRoom].top = (m_CountMakeRoom / RoomNumZ) * OneRoomZ;
				m_Section[m_CountMakeRoom].bottom = (m_CountMakeRoom / RoomNumZ) * OneRoomX + OneRoomZ;
			}
		}
		break;
	case 3:
		{
			m_Section[0].left		= 0;
			m_Section[0].right	= MAP_SIZE;

			m_Section[0].top		= 0;
			m_Section[0].bottom	= MAP_SIZE;
		}
		break;
	}
}
//---------------------------------------------------------------------------------------
// 部屋の作成
//---------------------------------------------------------------------------------------
void CMapData::MakeRoom()
{
	//作る部屋のサイズ
	int nRoomSize_X;
	int nRoomSize_Y;

	//区画のサイズ
	int nSectionSize_X;
	int nSectionSize_Y;

	//部屋を作る場所の中心位置
	int nMakeRoomPos_X;
	int nMakeRoomPos_Y;

	//作った部屋のかずだけ設定処理を行う
	for(int i = 0;i <= m_CountMakeRoom;i++)
	{
		//区画のサイズを計算する
		nSectionSize_X = m_Section[i].right - m_Section[i].left;	//区画の横幅
		nSectionSize_Y = m_Section[i].bottom - m_Section[i].top;	//区画の縦幅

		//区画のサイズが一定以下ならば、ループから抜ける
		if(nSectionSize_X < SECTION_MIN_SIZE || nSectionSize_Y < SECTION_MIN_SIZE )
			break;
		//---部屋のサイズを設定----

		//部屋の幅
		nRoomSize_X = rand()%(nSectionSize_X - 3);

		//一定サイズ以下にならないよう調整
		while(nRoomSize_X < (nSectionSize_X / 2))
			nRoomSize_X = rand()%(nSectionSize_X - 3);

		//部屋の奥行
		nRoomSize_Y = rand()%(nSectionSize_Y - 3);

		//一定サイズ以下にならない様に調整
		while(nRoomSize_Y < (nSectionSize_Y / 2))
			nRoomSize_Y = rand()%(nSectionSize_Y - 3);

		//-----部屋の位置を設定する-----
		//横
		nMakeRoomPos_X = rand()%(m_Section[i].right - nRoomSize_X / 2);

		//一定値以下にならない様に調整
		//while(nMakeRoomPos_X <= m_Section[i].left + 2)
		//	nMakeRoomPos_X = rand()%(m_Section[i].right - nRoomSize_X / 2 - 2);
		while(m_Section[i].left >= nMakeRoomPos_X - nRoomSize_X / 2 || m_Section[i].right <= nMakeRoomPos_X + nRoomSize_X / 2 || nMakeRoomPos_X <= m_Section[i].left)
			nMakeRoomPos_X = rand()%(m_Section[i].right - nRoomSize_X / 2 - 1);


		//縦
		nMakeRoomPos_Y = rand()%(m_Section[i].bottom - nRoomSize_Y / 2);

		//一定値以下にならない様に調整
		//while(nMakeRoomPos_Y <= m_Section[i].top + 2)
		//	nMakeRoomPos_Y = rand()%(m_Section[i].bottom - nRoomSize_Y / 2 - 2);
		
		while(m_Section[i].top >= nMakeRoomPos_Y - nRoomSize_Y / 2 || m_Section[i].bottom <= nMakeRoomPos_Y + nRoomSize_Y / 2 || nMakeRoomPos_Y <= m_Section[i].top)
			nMakeRoomPos_Y = rand()%(m_Section[i].bottom - nRoomSize_Y / 2);

		//部屋の設定
		m_Room[i].top		= nMakeRoomPos_Y - (nRoomSize_Y / 2);
		m_Room[i].bottom	= nMakeRoomPos_Y + (nRoomSize_Y / 2);
		m_Room[i].left		= nMakeRoomPos_X - (nRoomSize_X / 2);
		m_Room[i].right		= nMakeRoomPos_X + (nRoomSize_X / 2);

		//部屋を実際にマップ上に作成する
		for(int j = m_Room[i].top;j < m_Room[i].bottom;j++)
		{
			for(int k = m_Room[i].left;k < m_Room[i].right;k++)
			{
				m_TerrainMap[j][k].m_Map_Situation = FLOOR;
			}
		}
	}

}
//---------------------------------------------------------------------------------------
// 通路の作成
//---------------------------------------------------------------------------------------
void CMapData::MakeRoot()
{
	
	bool bNeighbor_LeftAndRight;		//部屋が隣接している(左右で)
	bool bNeighbor_UpAndDown;			//部屋が隣接している(上下で)
	
	int nBorderLine;					//境界線
	
	//隣接している区画を探す
	for(int i = 0;i <= m_CountMakeRoom;i++)
	{	
		if(m_Room[i].bottom - m_Room[i].top <= 0)
			break;

		if(m_Room[i].right - m_Room[i].left <= 0)
			break;
		for(int j = 0;j < m_CountMakeRoom;j++)
		{
			//フラグを初期化する
			bNeighbor_LeftAndRight = false;
			bNeighbor_UpAndDown = false;
			
			if(m_Room[j].bottom - m_Room[j].top <= 0)
				break;

			if(m_Room[j].right - m_Room[j].left <= 0)
				break;
	
			//自身の右端と検索している部屋の左端が等しければ、隣接している
			if(m_Section[i].right == m_Section[j].left)
			{
				bNeighbor_LeftAndRight = true;
			}
	
			//自身の上端と検索している部屋の下端が等しければ、隣接している
			if(m_Section[i].top == m_Section[j].bottom)
			{
				bNeighbor_UpAndDown = true;
			}
	
			//隣接フラグが立っていれば、通路を作成する
	
			//左右で隣接(i:右の部屋	j:左の部屋)
			if(bNeighbor_LeftAndRight)
			{
				//右の部屋の通路のスタート位置
				int RightRootStertPoint;

				//左の部屋の通路のスタート位置
				int LeftRootStertPoint;
	
				//境界線位置を設定
				nBorderLine = m_Section[i].right;
	
				//通路のスタート位置を右の部屋の右端から設定
				RightRootStertPoint = rand()%(m_Room[i].top - m_Room[i].bottom) + m_Room[i].top;
	
				//通路のスタート位置を左の部屋の左側から設定
				LeftRootStertPoint = rand()%(m_Room[j].top - m_Room[j].bottom) + m_Room[j].top;

				//右の部屋から境界線まで通路を作成
				for(int k = m_Room[i].right;k <= nBorderLine;k++)
				{
					m_TerrainMap[RightRootStertPoint][k].m_Map_Situation = FLOOR;
				}
				
				//左の部屋から境界線まで通路を作成
				for(int k = m_Room[j].left;k >= nBorderLine;k--)
				{
					m_TerrainMap[LeftRootStertPoint][k].m_Map_Situation = FLOOR;
				}
				
	
				//境界線を埋めて通路作成
				for(int k = RightRootStertPoint;k != LeftRootStertPoint;)
				{
					m_TerrainMap[k][nBorderLine].m_Map_Situation = FLOOR;
				
					//左の通路位置より作業位置が高ければ下げていく
					if(k > LeftRootStertPoint)
						k--;
				
					//左の通路位置より作業位置が低ければあげていく
					if(k < LeftRootStertPoint)
						k++;	
				}
			}
		}
	}

}
//---------------------------------------------------------------------------------------
// 階段の作成
//---------------------------------------------------------------------------------------
void CMapData::StairsSet()
{
	int StairsPos_X;		//階段建設予定地
	int StairsPos_Y;		//階段建設予定地


	//階段の位置をランダムに設定
	StairsPos_X = rand()%MAP_SIZE;
	StairsPos_Y = rand()%MAP_SIZE;

	//仮に設定した位置が部屋の中ならば、設置
	while(!CheckInTheRoom(StairsPos_X,StairsPos_Y))
	{
		//部屋の中でなければ再設定を行う
		StairsPos_X = rand()%MAP_SIZE;
		StairsPos_Y = rand()%MAP_SIZE;
	}

	//階段を設置する!
	m_TerrainMap[StairsPos_Y][StairsPos_X].m_Map_Situation = STAIRS;
}

//---------------------------------------------------------------------------------------
// 指定された位置が部屋の中か確認する
//---------------------------------------------------------------------------------------
bool CMapData::CheckInTheRoom(int PosX,int PosY)
{
	bool InFlg = false;	//部屋の中に居る

	//部屋のデータ一つ一つ確認し、中に居るか確認する
	for(int i = 0;i <= m_CountMakeRoom;i ++)
	{
		//部屋の高さから確認する
		if(m_Room[i].top < (PosY) && m_Room[i].bottom > (PosY))
		{
			//部屋の横を確認
			if(m_Room[i].right > (PosX) && m_Room[i].left < (PosX))
			{
				//両方の条件を満たせば部屋にいることになる。
				InFlg = true;
				break;
			}
		}
	}

	return InFlg;
}

//---------------------------------------------------------------------------------------
//指定された位置に階段があるか判断する
//---------------------------------------------------------------------------------------
bool CMapData::CheckStairs(int PosX,int PosY)
{
	//指定位置に階段があれば正
	if(m_TerrainMap[PosY][PosX].m_Map_Situation == STAIRS)
	{
		return true;
	}

	//無ければ負
	return false;
}
//---------------------------------------------------------------------------------------
//指定された位置が、どの部屋か、判別し、部屋番号を返す(部屋にいなければ、最大部屋番号を渡す)
//---------------------------------------------------------------------------------------
int CMapData::GetRoomNumber(int nPosX,int nPosZ)
{
	//全ての部屋分チェック
	for(int i = 0;i <= m_CountMakeRoom;i++)
	{
		//部屋の横幅内に存在するか確認
		if(nPosX >= m_Room[i].left && nPosX <= m_Room[i].right)
		{
			//部屋の縦幅内に存在するか確認
			if(nPosZ >= m_Room[i].top && nPosZ <= m_Room[i].bottom)
			{
				return i;
			}
		}
	}

	return ROOM_MAX_NUM;
}
//---------------------------------------------------------------------------------------
//指定された部屋番号の間取りを返す(部屋番号が作成した部屋数より大きければ、0,0,0,0の値を返す)
//---------------------------------------------------------------------------------------
RECT CMapData::GetRoomFloorPlan(int nRoomNumber)
{
	//指定された引数が、作った部屋の数いないか確認する
	if(m_CountMakeRoom >= nRoomNumber)
	{
		return m_Room[nRoomNumber];
	}

	//範囲外の数値が渡された
	RECT ReturnNum;
	ReturnNum.top		= 0.0f;
	ReturnNum.bottom	= 0.0f;
	ReturnNum.right		= 0.0f;
	ReturnNum.left		= 0.0f;

	return ReturnNum;
}
//---------------------------------------------------------------------------------------
//階層数の描画
//---------------------------------------------------------------------------------------
void CMapData::DrawHierarchyNum()
{
	char Hierarchy[256];
	_stprintf(Hierarchy, _T("%d階"), m_nHierarchyNum);
	//数値(文字)描画
	m_pFont ->DrawText(NULL,Hierarchy,-1,&m_FontDrawPos,DT_LEFT,D3DCOLOR_ARGB(0xff, 0x00, 0x00, 0x00));
}



//---------------------------------------------------------------------------------------
//A*アルゴリズムの情報を設定する
//---------------------------------------------------------------------------------------
void CMapData::ASarSetData(int NowPosX,int NowPosZ,int EnemyPosX,int EnemyPosZ,int PlayerPosX,int PlayerPosZ)
{
	//自身の位置を構造体配列の中に格納する

	//位置情報を保存
	m_AStarData[NowPosZ][NowPosX].m_nPosX = NowPosX;
	m_AStarData[NowPosZ][NowPosX].m_nPosZ = NowPosZ;
	//コストを入力する
	m_AStarData[NowPosZ][NowPosX].m_nCost = AStarCalculator(NowPosX,NowPosZ,EnemyPosX,EnemyPosZ);
	//ヒューリステック値を入力する
	m_AStarData[NowPosZ][NowPosX].m_nHeuristic = AStarCalculator(NowPosX,NowPosZ,PlayerPosX,PlayerPosX);
	//スコアを入力する(コスト+ヒューリスティック値)
	m_AStarData[NowPosZ][NowPosX].m_nScore = m_AStarData[NowPosZ][NowPosX].m_nCost + m_AStarData[NowPosZ][NowPosX].m_nHeuristic;
}

//---------------------------------------------------------------------------------------
//A*アルゴリズム用構造体の初期化を行う
//---------------------------------------------------------------------------------------
void CMapData::InitAStarData()
{
	//データの初期化を行う
	for(int i = 0;i < MAP_SIZE;i++)
	{
		for(int k = 0;k < MAP_SIZE;k++)
		{
			//マップのオープンクローズフラグ初期化
			m_AStarData[i][k].m_nMapStatus = 0;

			//コスト、ヒューリスティック値、スコア初期化
			m_AStarData[i][k].m_nCost = 0;
			m_AStarData[i][k].m_nHeuristic = 0;
			m_AStarData[i][k].m_nScore = 0;

			//自身の親のポインタを初期化する
			m_AStarData[i][k].m_ParentPos = D3DXVECTOR2(0,0);
		}
	}
	
	//これから削除するデータ
	AStarList* DeleteAstarData = m_pAstarList;


	//リストの最後まで移動する
	while(DeleteAstarData!= NULL)
	{
		//これから削除するデータの次のデータ
		AStarList* NextDeleteData = DeleteAstarData->NextData;

		//データの削除
		delete DeleteAstarData;
		DeleteAstarData = NULL;

		//次のデータの削除に移る
		DeleteAstarData = NextDeleteData;
	}

	m_pAstarList = NULL;
}


//---------------------------------------------------------------------------------------
//指定された位置周囲の移動可能な場所を検索しリストに追加
//---------------------------------------------------------------------------------------
void CMapData::SearchPosition(int SearchPosX,int SearchPosZ,int EnemyPosX,int EnemyPosZ,int PlayerPosX,int PlayerPosZ)
{
	//方向の補正値
	D3DXVECTOR2 CorrectionPos[MOVEVEC] = 
	{
		//			 X, Z
		D3DXVECTOR2(-1,-1),	//左上
		D3DXVECTOR2( 0,-1),	//上
		D3DXVECTOR2( 1,-1),	//右上
		D3DXVECTOR2( 1, 0),	//右
		D3DXVECTOR2( 1, 1),	//右下
		D3DXVECTOR2(0 , 1),	//下
		D3DXVECTOR2(-1, 1),	//左下
		D3DXVECTOR2(-1, 0)	//左
	};

	//周囲を確認する
	for(int i = 0;i < MOVEVEC;i++)
	{
		//子供の位置を保存
		int ChildPosX = (int)(SearchPosX + CorrectionPos[i].x);
		int ChildPosZ = (int)(SearchPosZ + CorrectionPos[i].y);

		int StatusFlg = m_AStarData[ChildPosZ][ChildPosX].m_nMapStatus;

		//確認した場所の状態が計算を行っていない状態ならば処理を続ける
		if(StatusFlg != 0)
			continue;

		//確認した位置が床(移動可能)かつ、誰もいなければ移動可能リストに加える
		int MapSituNum = Get_TerrainMapSituation(ChildPosX,ChildPosZ);
		int UnitSituNum = Get_UnitMapSituation(ChildPosX,ChildPosZ);

		if(UnitSituNum > 1)
			continue;

		if(MapSituNum != FLOOR && MapSituNum != STAIRS)
			continue;

		//子供の親の位置を自身に設定する
		m_AStarData[ChildPosZ][ChildPosX].m_ParentPos.x = SearchPosX;
		m_AStarData[ChildPosZ][ChildPosX].m_ParentPos.y = SearchPosZ;

		//スコアの計算を行う
		ASarSetData(ChildPosX,ChildPosZ,EnemyPosX,EnemyPosZ,PlayerPosX,PlayerPosZ);

		//計算を行った状態に遷移する
		CMapData::CompleteCellCal(ChildPosX,ChildPosZ,1);

		//リストに追加
		//これから格納するデータ
		AStarList* NextAStarData = new AStarList;
		//位置情報の格納
		NextAStarData->AstarData = m_AStarData[ChildPosZ][ChildPosX];
		//次のデータ
		NextAStarData->NextData = NULL;
		//初めてリストに登録する
		if(m_pAstarList == NULL)
		{
			m_pAstarList = NextAStarData;
		}
		else
		{
			//これから格納するデータの前のデータ
			AStarList* BackAstarData = m_pAstarList;

			//リストの最後まで移動する
			while(BackAstarData->NextData != NULL)
			{
				BackAstarData = BackAstarData ->NextData;
			}

			//最後まで到達したら、その後ろにデータを追加し、接合させる
			BackAstarData ->NextData = NextAStarData;
		}

	}
}
//---------------------------------------------------------------------------------------
//A*アルゴリズムにおける、距離を計算する
//---------------------------------------------------------------------------------------
int CMapData::AStarCalculator(int NowPosX,int NowPosZ,int GoalPosX,int GoalPosZ)
{
	//現在の位置と、目標地点の位置の距離を計算する
	int DistanceX = abs(NowPosX - GoalPosX);
	int DistanceZ = abs(NowPosZ - GoalPosZ);

	//値を暫定的に計算する
	int HeuristicScoreNum = DistanceX + DistanceZ;

	//斜め移動も可能なため、縦、横の数値の低い分、スコア値から減算する
	//引く数値
	int SubNum = DistanceX;

	if(DistanceX > DistanceZ)
		SubNum = DistanceZ;

	HeuristicScoreNum -= SubNum;

	//計算が完了した数値をヒューリスティック値として返す
	return HeuristicScoreNum;
}
//---------------------------------------------------------------------------------------
//リスト内の、最もスコアの小さい位置を検索し、渡す
//---------------------------------------------------------------------------------------
void CMapData::SearchMinScoreData(int *PosX,int *PosZ)
{
	//もし、リストに何も登録されていなければ処理を中断
	if(m_pAstarList == NULL)
	{
		//非常値を入れて、検索失敗を返す
		*PosX = -99;
		*PosZ = -99;

		return;
	}

	//現在探索中のデータ
	AStarList * NowListData = m_pAstarList;

	//最少スコアのデータ
	AStarList* MinScoreData = m_pAstarList;

	//全てのデータの探索が終了するまで続ける
	while(NowListData)
	{

		//もし現在の最少スコアよりも探索中のデータのスコアのほうが小さければ、入れ替える
		if(MinScoreData->AstarData.m_nScore > NowListData->AstarData.m_nScore)
		{
			MinScoreData = NowListData;
		}

		//次のデータの探索に移る
		NowListData = NowListData->NextData;
	}

	//全てのデータの探索を行った

	//位置情報の値を渡せるように格納しておく
	*PosX = MinScoreData->AstarData.m_nPosX;
	*PosZ = MinScoreData->AstarData.m_nPosZ;

	//リスト上から最小値のデータを削除する

	//削除するデータが最前の場合、先頭ポインタを移動させる
	if(MinScoreData == m_pAstarList)
	{
		m_pAstarList = m_pAstarList ->NextData;
	}

	//削除するデータの前にデータが存在している場合、つなぎなおす
	else
	{
		//削除するデータの前のデータ
		AStarList* BackAstarData = m_pAstarList;

		//次のポインタが削除するデータになるまで移動する
		while(BackAstarData->NextData != MinScoreData)
		{
			BackAstarData = BackAstarData ->NextData;
		}

		//ポインタの先を変更
		BackAstarData ->NextData = MinScoreData->NextData;
	}

	//状態を遷移させる
	CompleteCellCal(MinScoreData ->AstarData.m_nPosX,MinScoreData ->AstarData.m_nPosZ,2);

	//データの削除
	delete MinScoreData;
	MinScoreData = NULL;
}
//---------------------------------------------------------------------------------------
//指定したセルの状態をクローズ化(探索完了)にする
//---------------------------------------------------------------------------------------
void CMapData::CompleteCellCal(int PosX,int PosZ,int State)
{
	m_AStarData[PosZ][PosX].m_nMapStatus = State;
}
//---------------------------------------------------------------------------------------
//指定したセルの親の位置を返す
//---------------------------------------------------------------------------------------
void CMapData::GetParentPos(int ChildPosX,int ChildPosZ,int *ParentPosX,int *ParentPosZ)
{
	*ParentPosX = (int)m_AStarData[ChildPosZ][ChildPosX].m_ParentPos.x;
	*ParentPosZ = (int)m_AStarData[ChildPosZ][ChildPosX].m_ParentPos.y;
}