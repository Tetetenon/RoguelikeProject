#include "DamageNotation.h"
#include "Graphics.h"
#include "Camera.h"
#include "TextureManager.h"
#include "define.h"
#include <math.h>
#include "DamageBillBoardManager.h"

//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CDamageNotation::CDamageNotation(int Damage,D3DXVECTOR3 Pos)
{
	//使用しない桁を設定
	for (int i = 0; i < DrawDigit; i++)
	{
		int Digit = pow((float)10,(DrawDigit - i) - 1);
		if (Damage - Digit < 0)
			m_NumPolygon[i].m_bDrawFlg = false;

	}
	//テクスチャのIDを設定する
	for (int i = 0; i < DrawDigit; i++)
	{
		//使用しないポリゴンはスル―
		if (!m_NumPolygon[i].m_bDrawFlg)
			continue;
		//描画する数値を設定
		int Digit = pow((float)10, (DrawDigit - i) - 1);
		int nTextureNumber = (Damage / Digit) % 10;

		//描画する数値から、テクスチャを指定
		m_NumPolygon[i].m_nTextureNumber = TEXTURE_0 + nTextureNumber;
	}

	//頂点情報の作成
	MakeVertex();

	//α値を初期化
	m_nAlpha = 0.0f;

	//移動方向を設定
	m_MoveVector.x = MoveVecX;
	m_MoveVector.y = MoveVecY;
	m_MoveVector.z = MoveVecZ;

	//総移動量を初期化
	m_AmountMovement = D3DXVECTOR3(0.0f,0.0f,0.0f);

	//全てのポリゴンを処理
	for (int i = 0; i < DrawDigit; i++)
	{
		//位置情報を設定
		m_NumPolygon[i].m_Pos = Pos;

		m_NumPolygon[i].m_Pos.x += (POLYGON_SIZE_X * (i - 1));

		//少し上にあげる
		m_NumPolygon[i].m_Pos.y += 2.0f;

		//少し手前へ
		m_NumPolygon[i].m_Pos.z -= 1.0f;

		//スケールの初期化
		m_NumPolygon[i].m_Scl = D3DXVECTOR3(1,1,1);
	}

	//マネージャーのポインタの取得
	m_pManager = CDamageBillBoardManager::GetPointer();

	//生存時間の設定
	m_LifeTime = LifeTime;
	//固有IDの取得
	m_nID = m_pManager->GetNextNumber();
	//次の番号を設定する
	m_pManager->SetNextNumber(m_nID + 1);

	//マネージャーに自身の追加する
	m_pManager->Add(m_nID, this);
}


//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CDamageNotation::~CDamageNotation()
{
	//全てのポリゴンデータ分処理
	for (int i = 0; i < DrawDigit; i++)
	{
		if (m_NumPolygon[i].m_pD3DVtxBuff != NULL)
		{
			//頂点バッファの開放
			m_NumPolygon[i].m_pD3DVtxBuff->Release();
			m_NumPolygon[i].m_pD3DVtxBuff = NULL;
		}
	}
}

//---------------------------------------------------------------------------------------
//描画
//---------------------------------------------------------------------------------------
void CDamageNotation::Draw()
{
	D3DXMATRIX mtxView, mtxScale, mtxTranslate, mtxRot, mtxOffset;

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();

	// ライティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ビューマトリックスを取得
	mtxView = CCamera::GetMtxView();

	//全てのポリゴン分描画処理を行う
	for (int i = 0; i < DrawDigit; i++)
	{
		//描画フラグが立っていない場合、処理をスキップ
		if (!m_NumPolygon[i].m_bDrawFlg)
			continue;
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&m_NumPolygon[i].m_mtxWorld);

		// 転置行列を求める	
		m_NumPolygon[i].m_mtxWorld._11 = mtxView._11;
		m_NumPolygon[i].m_mtxWorld._12 = mtxView._21;
		m_NumPolygon[i].m_mtxWorld._13 = mtxView._31;

		m_NumPolygon[i].m_mtxWorld._21 = mtxView._12;
		m_NumPolygon[i].m_mtxWorld._22 = mtxView._22;
		m_NumPolygon[i].m_mtxWorld._23 = mtxView._32;

		m_NumPolygon[i].m_mtxWorld._31 = mtxView._13;
		m_NumPolygon[i].m_mtxWorld._32 = mtxView._23;
		m_NumPolygon[i].m_mtxWorld._33 = mtxView._33;

		// スケールを反映
		D3DXMatrixScaling(&mtxScale, m_NumPolygon[i].m_Scl.x, m_NumPolygon[i].m_Scl.y, m_NumPolygon[i].m_Scl.z);
		D3DXMatrixMultiply(&m_NumPolygon[i].m_mtxWorld, &m_NumPolygon[i].m_mtxWorld, &mtxScale);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, m_NumPolygon[i].m_Pos.x, m_NumPolygon[i].m_Pos.y, m_NumPolygon[i].m_Pos.z);
		D3DXMatrixMultiply(&m_NumPolygon[i].m_mtxWorld, &m_NumPolygon[i].m_mtxWorld, &mtxTranslate);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &m_NumPolygon[i].m_mtxWorld);

		// 頂点バッファをレンダリングパイプラインに設定
		pDevice->SetStreamSource(0, m_NumPolygon[i].m_pD3DVtxBuff, 0, sizeof(VERTEX_3D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//テクスチャのセット
		pDevice->SetTexture(0, *CTextureManager::GetTexture(m_NumPolygon[i].m_nTextureNumber));

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
	}

	// ライティングを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}
//---------------------------------------------------------------------------------------
//更新
//---------------------------------------------------------------------------------------
void CDamageNotation::Update()
{
	//移動
	m_AmountMovement += m_MoveVector;

	//生存時間を減らす
	m_LifeTime--;

	//透明度を変更する
	m_nAlpha = (m_LifeTime / LifeTime) * 255;

	//全てのポリゴン分更新
	for (int i = 0; i < DrawDigit; i++)
	{

		//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		m_NumPolygon[i].m_pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 上昇していくほど半透明にする
		pVtx[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255 - m_nAlpha);
		pVtx[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255 - m_nAlpha);
		pVtx[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255 - m_nAlpha);
		pVtx[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255 - m_nAlpha);

		// 頂点データをアンロックする
		m_NumPolygon[i].m_pD3DVtxBuff->Unlock();
		//ビルボードの移動
		m_NumPolygon[i].m_Pos += m_MoveVector;
	}
}
//---------------------------------------------------------------------------------------
// 頂点情報の作成
//---------------------------------------------------------------------------------------
HRESULT CDamageNotation::MakeVertex()
{
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();

	//全てのポリゴンを処理
	for (int i = 0; i < DrawDigit; i++)
	{
		// オブジェクトの頂点バッファを生成
		if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
			D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
			FVF_VERTEX_3D,				// 使用する頂点フォーマット
			D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
			&m_NumPolygon[i].m_pD3DVtxBuff,	// 頂点バッファインターフェースへのポインタ
			NULL)))						// NULLに設定
		{
			return E_FAIL;
		}

		{
			//頂点バッファの中身を埋める
			VERTEX_3D *pVtx;

			// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
			m_NumPolygon[i].m_pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

			// 頂点座標の設定
			pVtx[0].vtx = D3DXVECTOR3((-POLYGON_SIZE_X / 2.0f),-POLYGON_SIZE_Y / 2.0f, 0.0f);
			pVtx[1].vtx = D3DXVECTOR3((-POLYGON_SIZE_X / 2.0f), POLYGON_SIZE_Y / 2.0f, 0.0f);
			pVtx[2].vtx = D3DXVECTOR3(( POLYGON_SIZE_X / 2.0f),-POLYGON_SIZE_Y / 2.0f, 0.0f);
			pVtx[3].vtx = D3DXVECTOR3(( POLYGON_SIZE_X / 2.0f), POLYGON_SIZE_Y / 2.0f, 0.0f);


			// 法線の設定
			pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
			pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

			// 反射光の設定
			pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

			// 頂点データをアンロックする
			m_NumPolygon[i].m_pD3DVtxBuff->Unlock();
		}
	}

	return S_OK;
}