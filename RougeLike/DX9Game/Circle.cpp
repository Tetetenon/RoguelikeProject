#include "Circle.h"
#include "Graphics.h"
#include "define.h"
#include "TextureManager.h"
#include <tchar.h>

#define MAP_SIZE 1

//---------------------------------------------------------------------------------------
//　コンストラクタ
//---------------------------------------------------------------------------------------
CCircle::CCircle(void)
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();

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
			pVtx[nCntZ * (MAP_SIZE + 1) + nCntX].vtx.y = 0.1f;
			pVtx[nCntZ * (MAP_SIZE + 1) + nCntX].vtx.z = MAP_SIZE / 2.0f * MASS_SIZE - nCntZ * MASS_SIZE;
			// 法線
			pVtx[nCntZ * (MAP_SIZE + 1) + nCntX].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
			// 反射光
			pVtx[nCntZ * (MAP_SIZE + 1) + nCntX].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
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
}


//---------------------------------------------------------------------------------------
//　デストラクタ
//---------------------------------------------------------------------------------------
CCircle::~CCircle(void)
{
	//頂点バッファの開放
	SAFE_RELEASE(m_pD3DVtxBuff);
	//インデックスバッファの開放
	SAFE_RELEASE(m_pD3DIdxBuff);
}


//---------------------------------------------------------------------------------------
// 初期化
//---------------------------------------------------------------------------------------
void CCircle::Init()
{
}
//---------------------------------------------------------------------------------------
// 更新
//---------------------------------------------------------------------------------------
void CCircle::Update()
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
void CCircle:: Draw(int UnitNumber)
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

			//ユニットの識別番号により、使用するテクスチャを設定

			//プレイヤーの場合
			if(UnitNumber == OBJ_NUM_PLAYER)
				pDevice->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_CIRCLE_P));
			
			//パーティーメンバーの場合
			if(UnitNumber >= OBJ_NUM_PARTY)
				pDevice->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_CIRCLE_F));

			//エネミーの場合
			if(UnitNumber >= OBJ_NUM_ENEMY)
				pDevice->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_CIRCLE_E));

			//アイテムの場合
			if(UnitNumber == OBJ_NUM_ITEM)
				pDevice->SetTexture(0,*CTextureManager::GetTexture(TEXTURE_CIRCLE_I));

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
void CCircle:: Fin()
{
}

//---------------------------------------------------------------------------------------
//　位置情報の設定
//---------------------------------------------------------------------------------------
void CCircle::SetPos(D3DXVECTOR3 Pos)
{
	
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
			pVtx[nCntZ * (MAP_SIZE + 1) + nCntX].vtx.x = Pos.x + (-MAP_SIZE / 2.0f * MASS_SIZE + nCntX * MASS_SIZE);
			pVtx[nCntZ * (MAP_SIZE + 1) + nCntX].vtx.y = 0.1f;
			pVtx[nCntZ * (MAP_SIZE + 1) + nCntX].vtx.z = Pos.z + (MAP_SIZE / 2.0f * MASS_SIZE - nCntZ * MASS_SIZE);

			// 法線
			pVtx[nCntZ * (MAP_SIZE + 1) + nCntX].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);

			// 反射光
			pVtx[nCntZ * (MAP_SIZE + 1) + nCntX].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標
			pVtx[nCntZ * (MAP_SIZE + 1) + nCntX].tex.x = (float)MASS_SIZE * nCntX / 3;
			pVtx[nCntZ * (MAP_SIZE + 1) + nCntX].tex.y = (float)MASS_SIZE * nCntZ / 3;
		}
	}

	// 頂点データをアンロックする
	m_pD3DVtxBuff->Unlock();
}