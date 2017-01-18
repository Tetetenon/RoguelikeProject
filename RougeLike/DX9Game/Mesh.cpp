//=======================================================================================
//
//	  メッシュ クラス
//
//=======================================================================================
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS
#include <stdio.h>
#include "define.h"

#include "Mesh.h"
#include "Graphics.h"

#define INIT_PIECESPD	3.0f	// 破片初速
#define TIME_EXPLOSION	60		// 破片表示フレーム

//---------------------------------------------------------------------------------------
// コンストラクタ
//---------------------------------------------------------------------------------------
CMesh::CMesh()
{
	m_pD3DMesh = NULL;
	m_dwNumMaterial = 0;
	m_pMaterial = NULL;
	m_ppTexture = NULL;
	m_pAttr = NULL;
	m_dwAttr = 0;
	m_vBBox = D3DXVECTOR3(0, 0, 0);
	m_vCenter = D3DXVECTOR3(0, 0, 0);
	m_fRadius = 0.0f;

	m_pBBox = NULL;
	m_pBSphere = NULL;
	m_cvBColor.r = 0.0f;
	m_cvBColor.g = 1.0f;
	m_cvBColor.b = 0.0f;
	m_cvBColor.a = 0.3f;
}

//---------------------------------------------------------------------------------------
// デストラクタ
//---------------------------------------------------------------------------------------
CMesh::~CMesh()
{
	Finalize();
}

//---------------------------------------------------------------------------------------
// メッシュ初期化
//---------------------------------------------------------------------------------------
bool CMesh::Initialize(LPCTSTR pszFName, bool bReverse)
{
	TCHAR			szMsg[MAX_PATH + 32];
	TCHAR			szDir[_MAX_DIR];
	TCHAR			szCurrentDir[_MAX_PATH];

	LPD3DXBUFFER	pD3DXMtrlBuffer = NULL;

	// フォルダ名を抽出
	_tsplitpath(pszFName, NULL, szDir, NULL, NULL);

	// Ｘファイルからメッシュデータを読み込む
	if (FAILED(D3DXLoadMeshFromX(pszFName, D3DXMESH_SYSTEMMEM, CGraphics::GetDevice(),
		NULL, &pD3DXMtrlBuffer, NULL, &m_dwNumMaterial, &m_pD3DMesh))) 
	{
		_stprintf(szMsg, _T("Xファイル(%s)の読み込みに失敗しました。"), pszFName);
		MessageBox(NULL, szMsg, NULL, MB_OK);
		return false;
	}
	// カレントディレクトリを変更
	if (szDir[0]) {
		GetCurrentDirectory(_MAX_PATH, szCurrentDir);
		SetCurrentDirectory(szDir);
	}

	// マテリアル読み込み
	D3DXMATERIAL* pD3DMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	m_pMaterial = new D3DMATERIAL9[m_dwNumMaterial];
	m_ppTexture = new LPDIRECT3DTEXTURE9[m_dwNumMaterial];
	for (DWORD i = 0; i < m_dwNumMaterial; i++)
	{ 
		m_pMaterial[i] = pD3DMaterials[i].MatD3D;
		m_pMaterial[i].Ambient = m_pMaterial[i].Diffuse;
		m_ppTexture[i] = NULL;
		if (pD3DMaterials[i].pTextureFilename && pD3DMaterials[i].pTextureFilename[0])
		{
			// テクスチャファイルを読み込む
			if (FAILED(D3DXCreateTextureFromFileA(CGraphics::GetDevice(),
				pD3DMaterials[i].pTextureFilename, &m_ppTexture[i]))) {
				_stprintf(szMsg, _T("テクスチャ(%hs)の読み込みに失敗しました。"),
					pD3DMaterials[i].pTextureFilename);
				MessageBox(NULL, szMsg, NULL, MB_OK);
			}
		}
	}

	// 属性テーブルを生成するための最適化
	LPD3DXMESH pMeshWk;
	HRESULT hr = m_pD3DMesh->Optimize(D3DXMESHOPT_ATTRSORT,
		NULL, NULL, NULL, NULL, &pMeshWk);
	if (SUCCEEDED(hr))
	{
		m_pD3DMesh->Release();
		m_pD3DMesh = pMeshWk;
	} 
	else
	{
		SAFE_RELEASE(pD3DXMtrlBuffer);
		return false;
	}

	// 属性テーブル取得
	m_dwAttr = 0;
	m_pD3DMesh->GetAttributeTable(NULL, &m_dwAttr);
	m_pAttr = new D3DXATTRIBUTERANGE[m_dwAttr];
	m_pD3DMesh->GetAttributeTable(m_pAttr, &m_dwAttr);

	// 頂点がMVERTEXと異なる場合、矯正
	DWORD dwFVF = m_pD3DMesh->GetFVF();
	if (dwFVF != FVF_MVERTEX) 
	{
		LPD3DXMESH pMeshTmp = m_pD3DMesh;
		pMeshTmp->CloneMeshFVF(pMeshTmp->GetOptions(),
			FVF_MVERTEX, CGraphics::GetDevice(), &m_pD3DMesh);
		SAFE_RELEASE(pMeshTmp);
		if (!(dwFVF & D3DFVF_NORMAL)) 
		{
			D3DXComputeNormals(m_pD3DMesh, NULL);
		}	// 法線が無ければ追加
	}

	// 頂点バッファから頂点情報を取得
	DWORD dwVtx = m_pD3DMesh->GetNumVertices();
	MVERTEX* pVtx = new MVERTEX[dwVtx];
	LPVOID pSrc = NULL;
	m_pD3DMesh->LockVertexBuffer(0, &pSrc);

	if (bReverse)
	{
		D3DXMATRIX rev;
		D3DXMatrixRotationY(&rev, D3DXToRadian(180));
		D3DXVECTOR3 v;
		MVERTEX* p = (MVERTEX*)pSrc;
		for (DWORD i = 0; i < dwVtx; ++i, ++p) 
		{
			v = p->pos;
			D3DXVec3TransformCoord(&v, &v, &rev);
			p->pos = v;
			v = p->normal;
			D3DXVec3TransformNormal(&v, &v, &rev);
			p->normal = v;
		}
	}

	CopyMemory(pVtx, pSrc, sizeof(MVERTEX) * dwVtx);
	m_pD3DMesh->UnlockVertexBuffer();

	// 境界ボックス取得
	D3DXVECTOR3 vMin, vMax;
	vMin = vMax = pVtx[0].pos;
	for (DWORD i = 1; i < dwVtx; ++i) 
	{
		if (vMin.x > pVtx[i].pos.x)
			vMin.x = pVtx[i].pos.x;
		if (vMin.y > pVtx[i].pos.y)
			vMin.y = pVtx[i].pos.y;
		if (vMin.z > pVtx[i].pos.z)
			vMin.z = pVtx[i].pos.z;
		if (vMax.x < pVtx[i].pos.x)
			vMax.x = pVtx[i].pos.x;
		if (vMax.y < pVtx[i].pos.y)
			vMax.y = pVtx[i].pos.y;
		if (vMax.z < pVtx[i].pos.z)
			vMax.z = pVtx[i].pos.z;
	}
	m_vCenter = (vMax + vMin) / 2.0f;
	m_vBBox = (vMax - vMin) / 2.0f;
	// 境界球取得
	m_fRadius = 0.0f;
	for (DWORD i = 0; i < dwVtx; ++i) 
	{
		float dx = pVtx[i].pos.x - m_vCenter.x;
		float dy = pVtx[i].pos.y - m_vCenter.y;
		float dz = pVtx[i].pos.z - m_vCenter.z;
		float fLen = sqrtf(dx * dx + dy * dy + dz * dz);
		if (m_fRadius < fLen) {
			m_fRadius = fLen;
		}
	}
	// 境界表示用メッシュ生成
	D3DXCreateBox(CGraphics::GetDevice(),
		m_vBBox.x * 2.0f, m_vBBox.y * 2.0f, m_vBBox.z * 2.0f,
		&m_pBBox, NULL);
	D3DXCreateSphere(CGraphics::GetDevice(),
		m_fRadius, 16, 8, &m_pBSphere, NULL);

	// インデックスバッファからインデックス情報を取得

	// 頂点配列、インデックス配列を解放
	delete[] pVtx;

	// カレントディレクトリを元に戻す
	if (szDir[0])
		SetCurrentDirectory(szCurrentDir);

	pD3DXMtrlBuffer->Release();

	return true;
}

//---------------------------------------------------------------------------------------
// メッシュ解放
//---------------------------------------------------------------------------------------
void CMesh::Finalize()
{
	SAFE_DELETE_ARRAY(m_pAttr);

	SAFE_RELEASE(m_pBSphere);
	SAFE_RELEASE(m_pBBox);

	// テクスチャ オブジェクトを解放
	if (m_ppTexture) {
		for (DWORD i = 0; i < m_dwNumMaterial; i++) {
			SAFE_RELEASE(m_ppTexture[i]);
		}
		SAFE_DELETE_ARRAY(m_ppTexture);
	}
	SAFE_DELETE_ARRAY(m_pMaterial);

	SAFE_RELEASE(m_pD3DMesh);	// メッシュ オブジェクトを解放
}

//---------------------------------------------------------------------------------------
// メッシュ描画
//---------------------------------------------------------------------------------------
void CMesh::Draw(D3DXMATRIX& world)
{

	DrawNoAlpha(world);
	LPDIRECT3DDEVICE9 pD = CGraphics::GetDevice();
	pD->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pD->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pD->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	DrawAlpha(world);
	pD->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

// 不透明部分描画
void CMesh::DrawNoAlpha(D3DXMATRIX& world)
{
	// ワールド マトリックス設定
	CGraphics::GetDevice()->SetTransform(D3DTS_WORLD, &world);

	for (DWORD i = 0; i < m_dwAttr; i++) {
		DWORD dwID = m_pAttr[i].AttribId;
		if (m_pMaterial[dwID].Diffuse.a < 1.0f) {
			continue;
		}
		CGraphics::GetDevice()->SetMaterial(&m_pMaterial[dwID]);
		CGraphics::GetDevice()->SetTexture(0, m_ppTexture[dwID]);	// テクスチャを設定
		m_pD3DMesh->DrawSubset(dwID);								// 描画を実行
	}
}

// 半透明部分描画
void CMesh::DrawAlpha(D3DXMATRIX& world)
{
	// ワールド マトリックス設定
	CGraphics::GetDevice()->SetTransform(D3DTS_WORLD, &world);

	for (DWORD i = 0; i < m_dwAttr; i++) {
		DWORD dwID = m_pAttr[i].AttribId;
		if (m_pMaterial[dwID].Diffuse.a >= 1.0f) {
			continue;
		}
		CGraphics::GetDevice()->SetMaterial(&m_pMaterial[dwID]);
		CGraphics::GetDevice()->SetTexture(0, m_ppTexture[dwID]);	// テクスチャを設定
		m_pD3DMesh->DrawSubset(dwID);								// 描画を実行
	}
}
// 境界ボックス描画
void CMesh::DrawAABB(D3DXMATRIX& world)
{
	// 中心座標を移動
	D3DXVECTOR3 vPos;
	D3DXVec3TransformCoord(&vPos, &GetCenter(), &world);

	// ワールドマトリックス設定
	D3DXMATRIX mtx;
	D3DXMatrixTranslation(&mtx, vPos.x, vPos.y, vPos.z);
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
	pDevice->SetTransform(D3DTS_WORLD, &mtx);

	// マテリアル設定
	pDevice->SetTexture(0, NULL);
	D3DMATERIAL9 mtrl = {{0.0f}};
	mtrl.Diffuse = m_cvBColor;
	pDevice->SetMaterial(&mtrl);

	// 描画
	m_pBBox->DrawSubset(0);
}

// 境界球描画
void CMesh::DrawBSphere(D3DXMATRIX& world)
{
	// 中心座標を移動
	D3DXVECTOR3 vPos;
	D3DXVec3TransformCoord(&vPos, &GetCenter(), &world);

	// ワールドマトリックス設定
	D3DXMATRIX mtx;
	D3DXMatrixTranslation(&mtx, vPos.x, vPos.y, vPos.z);
	LPDIRECT3DDEVICE9 pDevice = CGraphics::GetDevice();
	pDevice->SetTransform(D3DTS_WORLD, &mtx);

	// マテリアル設定
	pDevice->SetTexture(0, NULL);
	D3DMATERIAL9 mtrl = {{0.0f}};
	mtrl.Diffuse = m_cvBColor;
	pDevice->SetMaterial(&mtrl);

	// 描画
	m_pBSphere->DrawSubset(0);
}

//=======================================================================================
//	End of File
//=======================================================================================