#include "LevelUp.h"
#include "TextureManager.h"
#include "Camera.h"
#include "Graphics.h"
#include "define.h"

//---------------------------------------------------------------------------------------
//コンストラクタ
//---------------------------------------------------------------------------------------
CLevelUp::CLevelUp(D3DXVECTOR3 Pos)
{
	//テクスチャIDの設定
	m_nTextureID = TEXTURE_LEVELUP;

	//頂点情報の作成
	MakeVertex();
	//位置情報を設定
	m_Pos = Pos;

	//少し上にあげる
	m_Pos.y += 20;

	//頂点情報の設定
	SetVertex();

	//上方向上昇値を初期化
	m_UpPos = 0;

	//スケールの初期化
	m_Scl= D3DXVECTOR3(POLYGON_SIZE_X,POLYGON_SIZE_Y,POLYGON_SIZE_Z);
}

//---------------------------------------------------------------------------------------
//デストラクタ
//---------------------------------------------------------------------------------------
CLevelUp::~CLevelUp(void)
{
	if(m_pD3DVtxBuff != NULL)
	{
		// 頂点バッファの開放
		m_pD3DVtxBuff->Release();
		m_pD3DVtxBuff = NULL;
	}
}
//---------------------------------------------------------------------------------------
//描画処理
//---------------------------------------------------------------------------------------
void CLevelUp::Draw()
{
	D3DXMATRIX mtxView, mtxScale, mtxTranslate,mtxRot,mtxOffset;

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();

	// ライティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// ビューマトリックスを取得
	mtxView = CCamera::GetMtxView();

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity( &m_mtxWorld);
	
	// ポリゴンを正面に向ける
#if 0
	D3DXVECTOR3 TargetPos = D3DXVECTOR3(mtxView._41,mtxView._42,mtxView._43);
	
	D3DXMatrixIdentity( &mtxRot);
	D3DXMatrixIdentity( &mtxOffset);

	D3DXMatrixLookAtLH(&mtxRot,&TargetPos,&m_Pos,&D3DXVECTOR3(0,1,0));

	// 逆行列を求める
	//D3DXMatrixInverse(&m_mtxWorld,NULL,&mtxView);
	D3DXMatrixInverse(&mtxRot,NULL,&mtxRot);
	mtxRot._41 = 0.0f;
	mtxRot._42 = 0.0f;
	mtxRot._43 = 0.0f;
    D3DXMatrixTranslation( &mtxOffset, m_Pos.x, m_Pos.y, m_Pos.z);                        // オフセット行列も作っておいて、

    D3DXMatrixMultiply( &m_mtxWorld, &m_mtxWorld, &mtxRot );                             // まずターゲット方向に軸回転させて
    //D3DXMatrixMultiply( &m_mtxWorld, &m_mtxWorld, &mtxOffset );         
#else
	// 転置行列を求める	
	m_mtxWorld._11 = mtxView._11;	
	m_mtxWorld._12 = mtxView._21;	
	m_mtxWorld._13 = mtxView._31;

	m_mtxWorld._21 = mtxView._12;
	m_mtxWorld._22 = mtxView._22;
	m_mtxWorld._23 = mtxView._32;

	m_mtxWorld._31 = mtxView._13;
	m_mtxWorld._32 = mtxView._23;
	m_mtxWorld._33 = mtxView._33;

#endif
		// スケールを反映
		D3DXMatrixScaling(&mtxScale, m_Scl.x,m_Scl.y,m_Scl.z);
		D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld, &mtxScale);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate,m_Pos.x,m_Pos.y,m_Pos.z);
		D3DXMatrixMultiply(&m_mtxWorld,&m_mtxWorld, &mtxTranslate);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

		// 頂点バッファをレンダリングパイプラインに設定
		pDevice->SetStreamSource(0, m_pD3DVtxBuff, 0, sizeof(VERTEX_3D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//テクスチャのセット
		pDevice ->SetTexture(0,*CTextureManager::GetTexture(m_nTextureID));

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,0, NUM_POLYGON);

		// ライティングを有効にする
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}

//---------------------------------------------------------------------------------------
//更新処理
//---------------------------------------------------------------------------------------
void CLevelUp::Update(D3DXVECTOR3 Pos)
{	
	//上方向上昇値を加算
	m_UpPos += 3;

	if(m_UpPos > 255)
	{
		m_UpPos = 255;
	}
	
	//頂点バッファの中身を埋める
	VERTEX_3D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 上昇していくほど半透明にする
	pVtx[0].diffuse = D3DCOLOR_RGBA(255,255,255,255 - m_UpPos);
	pVtx[1].diffuse = D3DCOLOR_RGBA(255,255,255,255 - m_UpPos);
	pVtx[2].diffuse = D3DCOLOR_RGBA(255,255,255,255 - m_UpPos);
	pVtx[3].diffuse = D3DCOLOR_RGBA(255,255,255,255 - m_UpPos);

	// 頂点データをアンロックする
	m_pD3DVtxBuff->Unlock();
	//ビルボードの移動
	m_Pos.x = Pos.x;
	m_Pos.y = (Pos.y + m_UpPos / 51.0f);
	m_Pos.z = Pos.z;

	//頂点情報の設定
	SetVertex();
}

//---------------------------------------------------------------------------------------
//頂点情報の設定
//---------------------------------------------------------------------------------------
void CLevelUp::SetVertex()
{
	//頂点バッファの中身を埋める
	VERTEX_3D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].vtx = D3DXVECTOR3(-POLYGON_SIZE_X / 2.0f,-POLYGON_SIZE_Y/2.0f,0.0f);
	pVtx[1].vtx = D3DXVECTOR3( POLYGON_SIZE_X / 2.0f,-POLYGON_SIZE_Y/2.0f,0.0f);
	pVtx[2].vtx = D3DXVECTOR3(-POLYGON_SIZE_X / 2.0f, POLYGON_SIZE_Y/2.0f,0.0f);
	pVtx[3].vtx = D3DXVECTOR3( POLYGON_SIZE_X / 2.0f, POLYGON_SIZE_Y/2.0f,0.0f);

	// 頂点データをアンロックする
	m_pD3DVtxBuff->Unlock();
}
//---------------------------------------------------------------------------------------
// 頂点情報の作成
//---------------------------------------------------------------------------------------
HRESULT CLevelUp::MakeVertex()
{
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
	// オブジェクトの頂点バッファを生成
    if(FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
												FVF_VERTEX_3D,				// 使用する頂点フォーマット
												D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
												&m_pD3DVtxBuff,	// 頂点バッファインターフェースへのポインタ
												NULL)))						// NULLに設定
	{
        return E_FAIL;
	}

	{
		//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		m_pD3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-POLYGON_SIZE_X / 2.0f,-POLYGON_SIZE_Y / 2.0f,0.0f);
		pVtx[1].vtx = D3DXVECTOR3( POLYGON_SIZE_X / 2.0f,-POLYGON_SIZE_Y / 2.0f,0.0f);
		pVtx[2].vtx = D3DXVECTOR3(-POLYGON_SIZE_X / 2.0f, POLYGON_SIZE_Y / 2.0f,0.0f);
		pVtx[3].vtx = D3DXVECTOR3( POLYGON_SIZE_X / 2.0f, POLYGON_SIZE_Y / 2.0f,0.0f);

		// 法線の設定
		pVtx[0].nor = D3DXVECTOR3(0.0f,0.0f,-1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f,0.0f,-1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f,0.0f,-1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f,0.0f,-1.0f);

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		
		// 頂点データをアンロックする
		m_pD3DVtxBuff->Unlock();
	}

	return S_OK;
}