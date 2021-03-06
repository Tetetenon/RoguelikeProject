#include "MapData.h"
#include "Graphics.h"
#include "TextureManager.h"
#include "GameScene.h"
#include "Fade.h"
#include"UnitManager.h"
#include <stdlib.h>
#include <tchar.h>
#include<fstream>
#include<iostream>
#include<string>
#include<sstream> //文字ストリーム


//静的メンバ実体定義
CMapData* CMapData::m_pMapData = NULL;
//---------------------------------------------------------------------------------------
//　コンストラクタ
//---------------------------------------------------------------------------------------
CMapData::CMapData(void)
{
	//メンバ変数の初期化
	m_nHierarchyNum = 0;
	m_pAstarList = NULL;

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
	m_nHierarchyNum = 0;
	
	//フォントへのポインタを取得する
	D3DXCreateFont(pDevice,24,0,1,0,FALSE,SHIFTJIS_CHARSET,OUT_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,NULL,&m_pFont);
	//フォント描画位置を設定
	SetFontPos();

	//前回生成したマップパターンの初期化
	m_nBackDividPattern = -99;
}

//---------------------------------------------------------------------------------------
// デストラクタ
//---------------------------------------------------------------------------------------
CMapData::~CMapData(void)
{
	m_nHierarchyNum = 0;
	//A*で用いたデータの初期化
	InitAStarData();
	//頂点バッファの開放
	SAFE_RELEASE(m_pD3DVtxBuff);
	//インデックスバッファの開放
	SAFE_RELEASE(m_pD3DIdxBuff);
}
//---------------------------------------------------------------------------------------
// 実体の作成
//---------------------------------------------------------------------------------------
void CMapData::Create()
{
	//中身がなければ作成
	if (!m_pMapData)
	{
		m_pMapData = new CMapData;
	}
}
//---------------------------------------------------------------------------------------
// 実体の削除
//---------------------------------------------------------------------------------------
void CMapData::Delete()
{
	//実体があれば削除
	if (m_pMapData)
	{
		delete m_pMapData;
		m_pMapData = NULL;
	}
}

//---------------------------------------------------------------------------------------
// 実体のポインタを渡す
//---------------------------------------------------------------------------------------
CMapData* CMapData::GetPointer()
{
	//念のため作成関数を呼ぶ
	Create();
	return m_pMapData;
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
	m_FontDrawPos.left		= (LONG) 90.0f;
	m_FontDrawPos.top		= (LONG) 15.0f;
	m_FontDrawPos.right		= (LONG)140.0f;
	m_FontDrawPos.bottom	= (LONG) 45.0f;
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
			switch(m_MapData[i][j].m_terrain)
			{
				//床
				case FLOOR:
				case ROOT:
					pDevice->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_FLOOR));
				break;
				//壁
				case WALL:
					pDevice->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_WALL));
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
	return m_MapData[PosY][PosX].m_terrain;
}
//---------------------------------------------------------------------------------------
// 指定した位置のユニット生存状態を返す
//---------------------------------------------------------------------------------------
int CMapData::Get_UnitMapSituation(int PosX,int PosY)
{
	//範囲外を読み込んだ場合、エラー値を返す
	if(PosX < 0 || PosX > MAP_SIZE || PosY < 0 || PosY > MAP_SIZE)
		return ERROR_NUM;
	return m_MapData[PosY][PosX].m_unit;
}
//---------------------------------------------------------------------------------------
// 指定した位置のアイテム状態を返す
//---------------------------------------------------------------------------------------
int CMapData::Get_ItemMapSituation(int PosX,int PosY)
{
	//範囲外を読み込んだ場合、エラー値を返す
	if(PosX < 0 || PosX > MAP_SIZE || PosY < 0 || PosY > MAP_SIZE)
		return ERROR_NUM;
	return m_MapData[PosY][PosX].m_item;
}

//---------------------------------------------------------------------------------------
// マップデータを手に入れる
//---------------------------------------------------------------------------------------
const Map& CMapData::Get_MapData(int x,int y)
{
	return m_MapData[y][x];
}


//---------------------------------------------------------------------------------------
// 指定した位置情報をもとに戻す
//---------------------------------------------------------------------------------------
void CMapData:: Back_UnitMap(int PosX,int PosY)
{
	m_MapData[PosY][PosX].m_unit = (ObjectNumber)0;
}

//---------------------------------------------------------------------------------------
// 可視化
//---------------------------------------------------------------------------------------
void CMapData::SetDark(int PosX,int PosY, BOOL isDark)
{
	if (PosX < 0 ) return;
	if (PosX >= MAP_SIZE) return;
	if (PosY < 0 ) return;
	if (PosY >= MAP_SIZE) return;
	m_MapData[PosY][PosX].m_isVisible = isDark;
}

void CMapData::SetRoomVisible(int room)
{
	for (int x = 0; x < MAP_SIZE; ++x)
	{
		for (int y = 0; y < MAP_SIZE; ++y)
		{
			const Map& node = CMapData::Get_MapData(x,y);
			if (node.m_roomnumber == room)
			{
				CMapData::SetDark(x,y, TRUE);
			}
		}
	}
}

void CMapData::SetVisibleProcess(int PosX, int PosY)
{
	// 部屋かどうか
	const Map& node = CMapData::Get_MapData(PosX,PosY);
	if (node.m_roomnumber == 0)
	{ 
		// 通路
		//現在位置と周囲8マスを可視化
		for (int i = -1; i <= 1; i++)
		{
			for (int j = -1; j <= 1; j++)
			{
				CMapData::SetDark(PosX + i, PosY + j, TRUE);
			}
		}
	}
	else
	{ // 部屋
		// 暗ければ全部照らす
		if (node.m_isVisible) return;
		// 部屋全てを照らす
		CMapData::SetRoomVisible(node.m_roomnumber);
	}
}

//---------------------------------------------------------------------------------------
// 指定した位置情報を変更する
//---------------------------------------------------------------------------------------
void CMapData:: Set_UnitMap(int PosX,int PosY,int Change)
{
	m_MapData[PosY][PosX].m_unit = (ObjectNumber)Change;
}
//---------------------------------------------------------------------------------------
// 指定した位置情報をもとに戻す
//---------------------------------------------------------------------------------------
void CMapData:: Back_ItemMap(int PosX,int PosY)
{
	m_MapData[PosY][PosX].m_item = 0;
}
//---------------------------------------------------------------------------------------
// 指定した位置情報を変更する
//---------------------------------------------------------------------------------------
void CMapData:: Set_ItemMap(int PosX,int PosY,int Change)
{
	m_MapData[PosY][PosX].m_item = Change;
}
//---------------------------------------------------------------------------------------
// マップをすべて初期化する
//---------------------------------------------------------------------------------------
void CMapData::AllInitMapData()
{
	//部屋を作った数を初期化
	m_CountMakeRoom = 0;
	for(int i = 0;i < MAP_SIZE;i++)
	{
		for(int j = 0;j < MAP_SIZE;j++)
		{
			//地形情報をすべて壁に初期化する
			m_MapData[j][i].m_terrain = WALL;
			//アイテム情報を初期化
			m_MapData[j][i].m_item = 0;
			//ユニット情報を初期化
			m_MapData[j][i].m_unit = (ObjectNumber)0;
			//到達情報を初期化
			m_MapData[j][i].m_isVisible = FALSE;
			//部屋の番号を初期化
			m_MapData[j][i].m_roomnumber = 0;
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
	//階層数加算
	m_nHierarchyNum++;

	//マップデータの初期化
	AllInitMapData();

	//マップの作り方を決定する
	//m_nMapMakePattern = rand() % MAP_GENERATION_PATTERN_MAX;
	m_nMapMakePattern = ROOT_FIRST;
	//m_nMapMakePattern = rand() % OUT_DATA_ROAD;

	//最終階層ならば、マップの作り方固定
	if (m_nHierarchyNum == GameClearNum)
	{
		m_nMapMakePattern = ROOM_FIRST;
	}

	//パターンで生成方法を分岐
	switch (m_nMapMakePattern)
	{
		//区画を作ってから通路を作成する
	case ROOM_FIRST:
		//マップの区画分け
		DivideMap();
		//区画内に部屋を作る
		MakeRoom();
		//部屋から部屋への通路を作成する
		MakeRoot();
		break;
		//通路を作成してから部屋を配置する
	case ROOT_FIRST:
		//必要な変数を初期化する
		RootFirstMakeInit();
		//通路の作成
		RootFirstMake();
		//部屋の作成
		RootUpRoom();
		break;
		//外部からデータを読み込む
	case OUT_DATA_ROAD:
		break;
	}


	//最終階層以外ならば階段を作成
	if (m_nHierarchyNum != GameClearNum)
	{
		//階段をどこかの部屋の中に設定する
		StairsSet();
	}
	//フィールド上にオブジェクトを設置する
	SetFieldObj();

	//フェードの状態をフェードインに設定
	m_pFade->ChangeState(FADEMODE_IN);
	//ユニットを一時行動不能状態に設定
	m_pUnitManager->ChangeMoveCanFlg(false);

	// 一部分可視化

	//床の数
	int nFloorCounter = 0;
	
	//マップの床数を数える
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			//マップ情報が床なら加算
			if (CMapData::Get_TerrainMapSituation(i, j) == FLOOR)
				nFloorCounter++;
		}
	}

	//ユニットの最大設置可能数を設定
	m_pEnemyGerenator->SetMaxGenerator((int)(nFloorCounter / 20));

	//アイテムの最大生成数を設定
	CItemGenerator::SetMaxItem((int)(nFloorCounter / 30));

	//アイテムマップ初期化
	for (int i = 0; i < MAP_SIZE; i++)
	{
		for (int j = 0; j < MAP_SIZE; j++)
		{
			m_MapData[i][j].m_item = 0;
			m_MapData[i][j].m_unit = (ObjectNumber)0;
			m_MapData[i][j].m_isVisible = FALSE;
		}

	}
	
	//10階層移動したら、シーンをゲームクリアに遷移させる
	if(m_nHierarchyNum > GameClearNum && !DebugMode)
	{
		//ゲームのクリア状況をクリアに変更する
		CGameScene::GameClearStateChange(GAME_CLEAR);
	
		//ゲームメインを終了
		m_pFade->ChangeState(FADEMODE_OUT);
	
		//エネミーの生成数のリセット
		m_pEnemyGerenator->ResetMakeEnemyNum();
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

	//作成した区画の数を初期化する
	m_CountMakeRoom = 0;

	//３パターンの中から、ランダムに選択し、区画を分ける
	m_nDividPattern = rand()% PATTERN_MAX;

	//もし前の階で作成したパターンと同じ場合、選択しなおす
	while (m_nDividPattern == m_nBackDividPattern)
	{
		m_nDividPattern = rand() % PATTERN_MAX;
	}

	if (m_nHierarchyNum == GameClearNum)
	{
		m_nDividPattern = 3;
	}

	//パターン情報を記録しておく
	m_nBackDividPattern = m_nDividPattern;

	switch(m_nDividPattern)
	{
		//一区画ずつ分ける
	case HEIGHT_NEXT_WIDTH:
		//-----境界線を引く& 区画を作る-----
		for(;m_CountMakeRoom < ROOM_MAX_NUM;m_CountMakeRoom ++)
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

		//全区画均等に等分
	case EQUALLY_DIVID:
		{
			int RoomNumX = (RemainingZone_X / SECTION_MIN_SIZE);
			int RoomNumZ = (RemainingZone_Z / SECTION_MIN_SIZE);

			//マップ上に作れる数を計算
			OneRoomX = RemainingZone_X / RoomNumX;
			OneRoomZ = RemainingZone_Z / RoomNumZ;

			//区画位置を設定
			for(;m_CountMakeRoom < RoomNumX * RoomNumZ;m_CountMakeRoom++)
			{
				m_Section[m_CountMakeRoom].left = (m_CountMakeRoom % RoomNumX) * OneRoomX;
				m_Section[m_CountMakeRoom].right = (m_CountMakeRoom % RoomNumX) * OneRoomX + OneRoomX;

				m_Section[m_CountMakeRoom].top = (m_CountMakeRoom / RoomNumZ) * OneRoomZ;
				m_Section[m_CountMakeRoom].bottom = (m_CountMakeRoom / RoomNumZ) * OneRoomX + OneRoomZ;
			}
		}
		break;

		//4分割
	case FOUR_DIVID:
		{
			int RoomNumX = (RemainingZone_X / SECTION_MAX_SIZE);
			int RoomNumZ = (RemainingZone_Z / SECTION_MAX_SIZE);

			//マップ上に作れる数を計算
			OneRoomX = RemainingZone_X / RoomNumX;
			OneRoomZ = RemainingZone_Z / RoomNumZ;

			//区画位置を設定
			for(;m_CountMakeRoom < RoomNumX * RoomNumZ;m_CountMakeRoom++)
			{
				m_Section[m_CountMakeRoom].left = (m_CountMakeRoom % RoomNumX) * OneRoomX;
				m_Section[m_CountMakeRoom].right = (m_CountMakeRoom % RoomNumX) * OneRoomX + OneRoomX;

				m_Section[m_CountMakeRoom].top = (m_CountMakeRoom / RoomNumZ) * OneRoomZ;
				m_Section[m_CountMakeRoom].bottom = (m_CountMakeRoom / RoomNumZ) * OneRoomX + OneRoomZ;
			}
		}
		break;
		//大部屋
	case LARGE_ROOM:
		{
			m_Section[0].left		= 0;
			m_Section[0].right	= MAP_SIZE;

			m_Section[0].top		= 0;
			m_Section[0].bottom	= MAP_SIZE;

			//生成した数を加算
			m_CountMakeRoom++;
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
	int i = 0;
	do
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
		while(m_Section[i].left + 1 >= (nMakeRoomPos_X - nRoomSize_X / 2) || m_Section[i].right - 1 <= (nMakeRoomPos_X + nRoomSize_X / 2) || nMakeRoomPos_X < m_Section[i].left)
			nMakeRoomPos_X = rand()%(m_Section[i].right - nRoomSize_X / 2);

		//縦
		nMakeRoomPos_Y = rand()%(m_Section[i].bottom - nRoomSize_Y / 2);

		//一定値以下にならない様に調整
		while(m_Section[i].top + 1 >= (nMakeRoomPos_Y - nRoomSize_Y / 2) || m_Section[i].bottom - 1 <= (nMakeRoomPos_Y + nRoomSize_Y / 2) || nMakeRoomPos_Y < m_Section[i].top)
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
				m_MapData[j][k].m_terrain = FLOOR;
				m_MapData[j][k].m_roomnumber = i + 1;
			}
		}
		//部屋を作った回数を保存する。
		i++;
	} while (i < m_CountMakeRoom);

}
//---------------------------------------------------------------------------------------
// 通路の作成
//---------------------------------------------------------------------------------------
void CMapData::MakeRoot()
{
	bool bNeighbor_LeftAndRight;		//部屋が隣接している(左右で)
	bool bNeighbor_UpAndDown;			//部屋が隣接している(上下で)
	
	//隣接している区画を探す
	for(int i = 0;i <= m_CountMakeRoom;i++)
	{	
		//使用していない区画まで処理を行ったらスキップ
		if(m_Room[i].bottom - m_Room[i].top <= 0)
			break;
		if(m_Room[i].right - m_Room[i].left <= 0)
			break;

		//現在の区画の隣にいる区画を検索する
		for(int j = 0;j < m_CountMakeRoom;j++)
		{
			//フラグを初期化する
			bNeighbor_LeftAndRight = false;
			bNeighbor_UpAndDown = false;
			
			//使用していない区画をスキップ
			if(m_Room[j].bottom - m_Room[j].top <= 0)
				break;
			if(m_Room[j].right - m_Room[j].left <= 0)
				break;

			//自身の右端と検索している部屋の左端が等しいかチェックを行う
			if((m_Section[i].right == m_Section[j].left) && CheckSectionOverRide(i,j,VectorFlg::Vectical))
			{
				//部屋の一部でも接触していれば、隣り合っている
				bNeighbor_LeftAndRight = true;
			}
	
			//自身の上端と検索している部屋の下端が等しければ、隣接している
			if((m_Section[i].top == m_Section[j].bottom) && CheckSectionOverRide(i, j, VectorFlg::Horizon))
			{
				bNeighbor_UpAndDown = true;
			}
	
			//隣接フラグが立っていれば、通路を作成する
	
			//左右で隣接(i:右の部屋	j:左の部屋)
			if(bNeighbor_LeftAndRight)
			{
				MekeRoomRoot(i,j,Horizon);
			}
			//上下で隣接(i:下の部屋j:上の部屋)
			if (bNeighbor_UpAndDown)
			{
				MekeRoomRoot(i, j, Vectical);
			}
		}
	}

}
//---------------------------------------------------------------------------------------
// 指定された部屋をつなぐ通路を作成する(引数:部屋１、部屋２、方向、境界線)
//---------------------------------------------------------------------------------------
void CMapData::MekeRoomRoot(int i, int j, VectorFlg Vector)
{
	int nBorderLine;					//境界線
	switch (Vector)
	{
	case CMapData::Vectical:
	{
		//通路の作成位置を区画の小さいほうに合わせる
		int MiniSectionNumber_Verctical = i;

		if ((m_Room[i].right - m_Room[i].left) > (m_Room[j].right - m_Room[j].left))
			MiniSectionNumber_Verctical = j;

		//下の部屋の通路のスタート位置
		int BottomRootStertPoint;

		//上の部屋の通路のスタート位置
		int TopRootStertPoint;

		//境界線位置を設定
		nBorderLine = m_Section[i].top;

		//通路のスタート位置を右の部屋の右端から設定
		bool bMakeFlgBottom = false;
		//既に通路入口が作られていないかチェックを行う
		for (int k = m_Room[i].left; k <= m_Room[i].right; k++)
		{
			if (m_MapData[m_Room[i].top - 1][k].m_terrain == ROOT)
			{
				//既に通路入口が作られていた場合、その位置を利用する
				TopRootStertPoint = k;
				bMakeFlgBottom = true;
			}
		}
		//もしどこにも入口が作成されていない場合、新しく作る
		if (!bMakeFlgBottom)
			TopRootStertPoint = rand() % (m_Room[i].right - m_Room[i].left) + m_Room[i].left;

		//通路のスタート位置を左の部屋の左側から設定
		bool bMakeFlgTop = false;

		//既に通路入口が作られていないかチェックを行う
		for (int k = m_Room[j].left; k <= m_Room[j].right; k++)
		{
			if (m_MapData[m_Room[j].bottom + 1][k].m_terrain == ROOT)
			{
				//既に通路入口が作られていた場合、その位置を利用する
				BottomRootStertPoint = k;
				bMakeFlgTop = true;
			}
		}
		//もしどこにも入口が作成されていない場合、新しく作る
		if (!bMakeFlgTop)
			BottomRootStertPoint = rand() % (m_Room[j].right - m_Room[j].left) + m_Room[j].left;

		//上の部屋から境界線まで通路を作成
		for (int k = m_Room[j].bottom; k <= nBorderLine; k++)
		{
			m_MapData[k][BottomRootStertPoint].m_terrain = ROOT;
		}

		//下の部屋から境界線まで通路を作成
		for (int k = m_Room[i].top; k >= nBorderLine; k--)
		{
			m_MapData[k][TopRootStertPoint].m_terrain = ROOT;
		}


		//境界線を埋めて通路作成
		for (int k = BottomRootStertPoint; k != TopRootStertPoint;)
		{
			m_MapData[nBorderLine][k].m_terrain = ROOT;
		
			//左の通路位置より作業位置が高ければ下げていく
			if (k > TopRootStertPoint)
				k--;
		
			//左の通路位置より作業位置が低ければあげていく
			if (k < TopRootStertPoint)
				k++;
		}
	}
		break;
	case CMapData::Horizon:
	{
		//通路の作成位置を区画の小さいほうに合わせる
		int MiniSectionNumber_Horizon = i;

		if ((m_Room[i].bottom - m_Room[i].top) >(m_Room[j].bottom - m_Room[j].top))
			MiniSectionNumber_Horizon = j;

		//右の部屋の通路のスタート位置
		int RightRootStertPoint;

		//左の部屋の通路のスタート位置
		int LeftRootStertPoint;

		//境界線位置を設定
		nBorderLine = m_Section[i].right;

		//通路のスタート位置を右の部屋の右端から設定
		bool bMakeFlgRight = false;
		//既に通路入口が作られていないかチェックを行う
		for (int k = m_Room[i].top; k <= m_Room[i].bottom; k++)
		{
			if (m_MapData[k][m_Room[i].right + 1].m_terrain == ROOT)
			{
				//既に通路入口が作られていた場合、その位置を利用する
				RightRootStertPoint = k;
				bMakeFlgRight = true;
			}
		}
		//もしどこにも入口が作成されていない場合、新しく作る
		if (!bMakeFlgRight)
			RightRootStertPoint = rand() % (m_Room[i].bottom - m_Room[i].top) + m_Room[i].top;

		//通路のスタート位置を左の部屋の左側から設定
		bool bMakeFlgLeft = false;
		//既に通路入口が作られていないかチェックを行う
		for (int k = m_Room[j].top; k <= m_Room[j].bottom; k++)
		{
			if (m_MapData[k][m_Room[j].left - 1].m_terrain == ROOT)
			{
				//既に通路入口が作られていた場合、その位置を利用する
				LeftRootStertPoint = k;
				bMakeFlgLeft = true;
			}
		}
		//もしどこにも入口が作成されていない場合、新しく作る
		if (!bMakeFlgLeft)
			LeftRootStertPoint = rand() % (m_Room[j].bottom - m_Room[j].top) + m_Room[j].top;

		//右の部屋から境界線まで通路を作成
		for (int k = m_Room[i].right; k <= nBorderLine; k++)
		{
			m_MapData[RightRootStertPoint][k].m_terrain = ROOT;
		}

		//左の部屋から境界線まで通路を作成
		for (int k = m_Room[j].left; k >= nBorderLine; k--)
		{
			m_MapData[LeftRootStertPoint][k].m_terrain = ROOT;
		}


		//境界線を埋めて通路作成
		for (int k = RightRootStertPoint; k != LeftRootStertPoint;)
		{
			m_MapData[k][nBorderLine].m_terrain = ROOT;

			//左の通路位置より作業位置が高ければ下げていく
			if (k > LeftRootStertPoint)
				k--;

			//左の通路位置より作業位置が低ければあげていく
			if (k < LeftRootStertPoint)
				k++;
		}
	}
		break;
	case CMapData::Max:
		break;
	default:
		break;
	}



}
//---------------------------------------------------------------------------------------
// 階段の作成
//---------------------------------------------------------------------------------------
void CMapData::StairsSet()
{
	int StairsPos_X;		//階段建設予定地
	int StairsPos_Y;		//階段建設予定地

	//作成する部屋の番号を設定
	int nRoomNumber = rand() % m_CountMakeRoom;
	//作成する部屋の情報を取得
	RECT RoomData = m_Room[nRoomNumber];

	//階段の位置をランダムに設定
	StairsPos_X = rand()%(RoomData.right - RoomData.left) + RoomData.left;
	StairsPos_Y = rand()%(RoomData.bottom - RoomData.top) + RoomData.top;

	//階段を設置する!
	m_MapData[StairsPos_Y][StairsPos_X].m_terrain = STAIRS;
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
	if(m_MapData[PosY][PosX].m_terrain == STAIRS)
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
	ReturnNum.top		= (LONG)0.0f;
	ReturnNum.bottom	= (LONG)0.0f;
	ReturnNum.right		= (LONG)0.0f;
	ReturnNum.left		= (LONG)0.0f;

	return ReturnNum;
}
//---------------------------------------------------------------------------------------
//階層数の描画
//---------------------------------------------------------------------------------------
void CMapData::DrawHierarchyNum()
{
	char Hierarchy[256];
	sprintf_s(Hierarchy, _T("%d階"), m_nHierarchyNum);
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
		D3DXVECTOR2( 0,-1),	//上
		D3DXVECTOR2( 1, 0),	//右
		D3DXVECTOR2(-1, 0),	//左
		D3DXVECTOR2( 0, 1),	//下
		D3DXVECTOR2( 1,-1),	//右上
		D3DXVECTOR2( 1, 1),	//右下
		D3DXVECTOR2(-1, 1),	//左下
		D3DXVECTOR2(-1,-1)	//左上
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


		if(MapSituNum != FLOOR && MapSituNum != STAIRS && MapSituNum != ROOT && MapSituNum != ROOT_ENTRANCE)
			continue;

		//親の位置を自身に設定する
		m_AStarData[ChildPosZ][ChildPosX].m_ParentPos.x = (float)SearchPosX;
		m_AStarData[ChildPosZ][ChildPosX].m_ParentPos.y = (float)SearchPosZ;

		//スコアの計算を行う
		ASarSetData(ChildPosX,ChildPosZ,EnemyPosX,EnemyPosZ,PlayerPosX,PlayerPosZ);

		if(UnitSituNum >= OBJ_NUM_ENEMY)
			m_AStarData[ChildPosZ][ChildPosX].m_nCost *= 10;

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
float CMapData::AStarCalculator(int NowPosX,int NowPosZ,int GoalPosX,int GoalPosZ)
{
	//現在の位置と、目標地点の位置の距離を計算する
	int DistanceX = abs(NowPosX - GoalPosX);
	int DistanceZ = abs(NowPosZ - GoalPosZ);

	//値を暫定的に計算する
	float HeuristicScoreNum = DistanceX + DistanceZ;

	//斜め移動も可能なため、縦、横の数値の低い分、スコア値から減算する
	//引く数値
	int SubNum = DistanceX;

	if(DistanceX > DistanceZ)
		SubNum = DistanceZ;

	//もし、斜め移動の場合、スコア、コストを加算する
	if (DistanceX > 0 && DistanceZ > 0)
		HeuristicScoreNum+= 0.5f;

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
//---------------------------------------------------------------------------------------
//指定された部屋同士が一部でも重なっているか返す
//---------------------------------------------------------------------------------------
bool CMapData::CheckSectionOverRide(int Section1, int Section2, VectorFlg VectorFlg)
{
	switch (VectorFlg)
	{
		//横の隣接関係を確認する
	case VectorFlg::Vectical:
		//Section1の位置がSection2と一致しているか確認を行う
		if ((m_Section[Section1].top == m_Section[Section2].top) && (m_Section[Section1].bottom == m_Section[Section2].bottom))
			//重なっている
			return true;
		//Section1の区画の一部がSection2の中に入っているか確認を行う
		if ((m_Section[Section1].top < m_Section[Section2].top) && (m_Section[Section1].bottom > m_Section[Section2].top))
			//重なっている
			return true;
		//Section2の区画の一部がSection1の中に入っているか確認を行う
		if ((m_Section[Section2].top < m_Section[Section1].top) && (m_Section[Section2].bottom > m_Section[Section1].top))
			//重なっている
			return true;

		//重なっていなかった
		return false;
		//縦の隣接関係を確認する
	case VectorFlg::Horizon:
		//Section1の位置がSection2と一致しているか確認を行う
		if ((m_Section[Section1].left == m_Section[Section2].left) && (m_Section[Section1].right == m_Section[Section2].right))
			//重なっている
			return true;
		//Section1の区画の一部がSection2の中に入っているか確認を行う
		if ((m_Section[Section1].left < m_Section[Section2].left) && (m_Section[Section1].right > m_Section[Section2].left))
			//重なっている
			return true;
		//Section2の区画の一部がSection1の中に入っているか確認を行う
		if ((m_Section[Section2].left < m_Section[Section1].left) && (m_Section[Section2].right > m_Section[Section1].left))
			//重なっている
			return true;
		//重なっていなかった
		return false;
	default:
		return false;
	}
}

//---------------------------------------------------------------------------------------
//フィールド上にオブジェクトを配置する
//---------------------------------------------------------------------------------------
void CMapData::SetFieldObj()
{
	//部屋の状態を確認し、一定以上の空間が存在する場合、家を設置する

	//全ての部屋を確認
	for (int i = 0; i < m_CountMakeRoom; i++)
	{
		//家を建てられる数
		int MakeHomePositionNum = 0;

		//部屋のサイズが、一定値以上ならば、家を建てる
		//家を設置できる場所があるか確認
		for (int j = m_Room[i].top; j < m_Room[i].bottom; j++)
		{
			for (int k = m_Room[i].left; k < m_Room[i].right; k++)
			{
				//場所情報が床の物のみカウント
				if(m_MapData[j][k].m_terrain == FLOOR)
					MakeHomePositionNum++;
			}
		}

		//床の数が一定以上存在する場合、家を建てる
		if (MakeHomePositionNum > MakeHomeSize)
		{
			int MakePosZ = rand() % (m_Room[i].bottom - m_Room[i].top) + m_Room[i].top;
			int MakePosX = rand() % (m_Room[i].right - m_Room[i].left) + m_Room[i].left;

			//指定した位置が床になるまで回す
			while (m_MapData[MakePosZ][MakePosX].m_terrain != FLOOR)
			{
				MakePosZ = rand() % (m_Room[i].bottom - m_Room[i].top) + m_Room[i].top;
				MakePosX = rand() % (m_Room[i].right - m_Room[i].left) + m_Room[i].left;
			}

			//空いている空間に家を設定
			m_MapData[MakePosZ][MakePosX].m_terrain = HOME;

			//家は一個のみ作成する
			break;
		}
	}
}

//---------------------------------------------------------------------------------------
//メンバ変数のポインタを設定する
//---------------------------------------------------------------------------------------
void CMapData::SetPointer()
{
	//フェードのポインタを取得
	m_pFade = CFade::GetPointer();
	//ユニットマネージャーのポインタを取得
	m_pUnitManager = CUnitManager::GetPointer();
	//エネミージェネレーターのポインタを取得
	m_pEnemyGerenator = CEnemyGenerator::GetPointer();
}
//---------------------------------------------------------------------------------------
//マップ上に通路を作成する
//---------------------------------------------------------------------------------------
void CMapData::RootFirstMake()
{
	//通路を作成する回数を設定する
	int nRootMakeNum = rand() % 4 + 8;

	for (int i = 0; i < nRootMakeNum; i++)
	{
		//通路を作る位置を決定する
		int RootMapStartPostionX = 0;
		int RootMapStartPostionZ = 0;

		RootMapStartPostionX = (rand() % ((MAP_SIZE - 2) / 2)) * 2 + 1;
		RootMapStartPostionZ = (rand() % ((MAP_SIZE - 2) / 2)) * 2 + 1;

		//通路を作成する長さ
		int nRootMakeLength = 0;

		//1本の通路の曲がる回数
		int nRootCurveNum = 0;

		//マップ上左上から通路を作成する
		while ((nRootCurveNum <= MAX_CURVE_NUM))
		{
			//-----横に通路を作成する-----
			//長さを決定する
			nRootMakeLength = (rand() % (ROOT_MAX_SIZE / 2) - (rand() % (ROOT_MAX_SIZE / 2))) * 2;

			//長さが最小サイズ以上か確認
			while (abs(nRootMakeLength) < ROOT_MIN_SIZE)
			{
				nRootMakeLength = (rand() % (ROOT_MAX_SIZE / 2) - (rand() % (ROOT_MAX_SIZE / 2))) * 2;
			}

			//マップの範囲外に出ない様に調整する
			if ((RootMapStartPostionX + nRootMakeLength) >(MAP_SIZE - 3))
			{
				nRootMakeLength = (MAP_SIZE - 3) - RootMapStartPostionX;
			}
			if ((RootMapStartPostionX + nRootMakeLength) < 1)
			{
				nRootMakeLength = -(RootMapStartPostionX - 1);
			}

			//通路を作成する
			SetPositionMakeRoot(RootMapStartPostionX, RootMapStartPostionZ, nRootMakeLength, Horizon);
			//次の通路作成位置を設定
			RootMapStartPostionX += nRootMakeLength;

			//曲がった回数を加算
			nRootCurveNum++;

			//-----縦に通路を作成する-----
			nRootMakeLength = (rand() % (ROOT_MAX_SIZE / 2) - (rand() % (ROOT_MAX_SIZE / 2))) * 2;

			//長さが最小サイズ以上か確認
			while (abs(nRootMakeLength) < ROOT_MIN_SIZE)
			{
				nRootMakeLength = (rand() % (ROOT_MAX_SIZE / 2) - (rand() % (ROOT_MAX_SIZE / 2))) * 2;
			}
			//マップの範囲外に出ない様に調整する
			if ((RootMapStartPostionZ + nRootMakeLength) >(MAP_SIZE - 3))
			{
				nRootMakeLength = (MAP_SIZE - 3) - RootMapStartPostionZ;
			}
			if ((RootMapStartPostionZ + nRootMakeLength) < 1)
			{
				nRootMakeLength = -(RootMapStartPostionZ - 1);
			}

			//通路を作成する
			SetPositionMakeRoot(RootMapStartPostionX, RootMapStartPostionZ, nRootMakeLength, Vectical);
			//次の通路作成位置を設定
			RootMapStartPostionZ += nRootMakeLength;

			//曲がった回数を加算
			nRootCurveNum++;
		}
	}
}

//---------------------------------------------------------------------------------------
//指定された位置から指定した長さまで通路を作成する
//---------------------------------------------------------------------------------------
void CMapData::SetPositionMakeRoot(int StartPosX, int StartPosZ, int Length, VectorFlg Vector)
{
	//作成する方向で分岐させる
	switch (Vector)
	{
		//縦方向に通路を作成する
	case Vectical:
		if (Length > 0)
		{
			for (int i = 0; i < Length; i++)
			{
				m_MapData[StartPosZ + i][StartPosX].m_terrain = ROOT;
			}
			int a = ROOM_MAX_NUM;
			//部屋の作成数がいっぱいになっていない場合、部屋を確立で作成する
			if (m_CountMakeRoom < ROOM_MAX_NUM)
			{
				//作成予定位置がほかの部屋とかぶっていないか確認
				if (CheckMakeRoomPoint(StartPosX, StartPosZ + Length))
				{
					//かぶっていなければ部屋作成位置に設定
					m_MakeRoomPoint[m_CountMakeRoom].x = StartPosX;
					m_MakeRoomPoint[m_CountMakeRoom].y = StartPosZ + Length;

					//部屋作成数を加算
					m_CountMakeRoom++;
				}
			}
		}
		else
		{
			for (int i = Length; i <= 0; i++)
			{
				m_MapData[StartPosZ + i][StartPosX].m_terrain = ROOT;
			}

			//部屋の作成数がいっぱいになっていない場合、部屋を確立で作成する
			if (m_CountMakeRoom < ROOM_MAX_NUM)
			{
				//作成予定位置がほかの部屋とかぶっていないか確認
				if (CheckMakeRoomPoint(StartPosX, StartPosZ + Length))
				{
					//かぶっていなければ部屋作成位置に設定
					m_MakeRoomPoint[m_CountMakeRoom].x = StartPosX;
					m_MakeRoomPoint[m_CountMakeRoom].y = StartPosZ + Length;

					//部屋作成数を加算
					m_CountMakeRoom++;
				}
			}
		}
		break;
		//横方向に通路を作成する
	case Horizon:
		if (Length > 0)
		{
			for (int i = 0; i < Length; i++)
			{
				m_MapData[StartPosZ][StartPosX + i].m_terrain = ROOT;
			}

			//部屋の作成数がいっぱいになっていない場合、部屋を確立で作成する
			if (m_CountMakeRoom < ROOM_MAX_NUM)
			{
				//作成予定位置がほかの部屋とかぶっていないか確認
				if (CheckMakeRoomPoint(StartPosX + Length, StartPosZ))
				{
					//かぶっていなければ部屋作成位置に設定
					m_MakeRoomPoint[m_CountMakeRoom].x = StartPosX + Length;
					m_MakeRoomPoint[m_CountMakeRoom].y = StartPosZ;

					//部屋作成数を加算
					m_CountMakeRoom++;
				}
			}
		}
		else
		{
			for (int i = Length; i <= 0; i++)
			{
				m_MapData[StartPosZ][StartPosX + i].m_terrain = ROOT;
			}

			//部屋の作成数がいっぱいになっていない場合、部屋を確立で作成する
			if (m_CountMakeRoom < ROOM_MAX_NUM)
			{
				//作成予定位置がほかの部屋とかぶっていないか確認
				if (CheckMakeRoomPoint(StartPosX + Length, StartPosZ))
				{
					//かぶっていなければ部屋作成位置に設定
					m_MakeRoomPoint[m_CountMakeRoom].x = StartPosX + Length;
					m_MakeRoomPoint[m_CountMakeRoom].y = StartPosZ;

					//部屋作成数を加算
					m_CountMakeRoom++;
				}
			}
		}
		break;
	}
}

//---------------------------------------------------------------------------------------
//通路上に部屋を作成する
//---------------------------------------------------------------------------------------
void CMapData::RootUpRoom()
{
	//作成予定の場所に部屋を立てる
	for (int i = 0; i < m_CountMakeRoom; i++)
	{
		//間取りの設定
		m_Room[i].top		= m_MakeRoomPoint[i].y - ((rand()% (RoomMaxSize - RoomMinSize)) + RoomMinSize) / 2;
		m_Room[i].bottom	= m_MakeRoomPoint[i].y + ((rand()% (RoomMaxSize - RoomMinSize)) + RoomMinSize) / 2;
		m_Room[i].left		= m_MakeRoomPoint[i].x - ((rand()% (RoomMaxSize - RoomMinSize)) + RoomMinSize) / 2;
		m_Room[i].right		= m_MakeRoomPoint[i].x + ((rand()% (RoomMaxSize - RoomMinSize)) + RoomMinSize) / 2;

		//部屋を実際にマップ上に作成する
		for (int j = m_Room[i].top; j < m_Room[i].bottom; j++)
		{
			for (int k = m_Room[i].left; k < m_Room[i].right; k++)
			{
				m_MapData[j][k].m_terrain = FLOOR;
				m_MapData[j][k].m_roomnumber = i + 1;
			}
		}
	}
}
//---------------------------------------------------------------------------------------
//部屋の作成予定地周辺に別の作成予定地がないかチェックを行う
//---------------------------------------------------------------------------------------
bool CMapData::CheckMakeRoomPoint(int X,int Z)
{
	//境界判定
	if (X > (MAP_SIZE - RoomMaxSize)
		|| Z > (MAP_SIZE - RoomMaxSize) 
		|| X < RoomMaxSize || Z < RoomMaxSize)
		return false;

	for (int i = 0; i < m_CountMakeRoom; i++)
	{
		//作成予定地とほかの作成予定地が近すぎないかチェック
		int DistanceX = abs(m_MakeRoomPoint[i].x - X);
		int DistanceZ = abs(m_MakeRoomPoint[i].y - Z);

		//部屋の位置がかぶりそうになった場合、偽を返す
		if (DistanceX < RoomMaxSize && DistanceZ < RoomMaxSize)
			return false;
	}
	//どの位置ともかぶらなければ正を返す
	return true;
}
//---------------------------------------------------------------------------------------
//通路を先に作る場合のデータの初期化
//---------------------------------------------------------------------------------------
void CMapData::RootFirstMakeInit()
{

	//部屋を作成する位置の初期化
	for (int i = 0; i < ROOM_MAX_NUM; i++)
	{
		m_MakeRoomPoint[i].x = 0.0f;
		m_MakeRoomPoint[i].y = 0.0f;
	}

	//必ず部屋を１つ作成する
	m_MakeRoomPoint[0].x = MAP_SIZE / 2;
	m_MakeRoomPoint[0].y = MAP_SIZE / 2;
	//部屋作成数を初期化
	m_CountMakeRoom = 1;
}