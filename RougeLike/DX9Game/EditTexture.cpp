#include <cassert>
#include "EditTexture.h"

/**
* テクスチャの作成
*/
static const bool CreateTexture(int width, int height, LPDIRECT3DDEVICE9 pDevice, LPDIRECT3DTEXTURE9* ppTexture)
	{
	HRESULT hr = pDevice->CreateTexture(
		width,				// 横幅
		height,				// 高さ
		1,					// ミップマップ
		0,					// 使用目的
		D3DFMT_A8R8G8B8,	// フォーマットカラー
		D3DPOOL_MANAGED,	// メモリ管理方法
		ppTexture,			// 生成先
		NULL);				// 未使用引数
	return FAILED(hr) ? false : true;
	}

/**
* ドットの書き込み
*/
static void WriteBit(DWORD* pBits, int line, int x, int y, DWORD col)
	{
	pBits[y*line + x] = col;
	}

/**
* ドットの取得
*/
static DWORD LoadBit(DWORD* pBits, int line, int x, int y)
	{
	return pBits[y*line + x];
	}

	
/**
* コンストラクタ
*/
CEditTexture::CEditTexture(int width, int height, LPDIRECT3DDEVICE9 pDevice)
	: m_pD3DTexture(nullptr)
	, m_nWidth(width)
	, m_nHeight(height)
	{
	CreateTexture(width, height, pDevice, &m_pD3DTexture);
	}

/**
* デストラクタ
*/
CEditTexture::~CEditTexture()
	{
	if (m_pD3DTexture)
		{
		m_pD3DTexture->Release();
		m_pD3DTexture = nullptr;
		}
	}

/**
* 色のセット
*/
void CEditTexture::SetColor(int x, int y, DWORD col)
	{
	// テクスチャがなければ
	if(!m_pD3DTexture) return;
	// 範囲チェック
	assert(x >= 0 && x < m_nWidth);
	assert(y >= 0 && y < m_nHeight);
	// テクスチャのロック
	D3DLOCKED_RECT lockRect;
	HRESULT hr = m_pD3DTexture->LockRect(0, &lockRect, nullptr, 0);
	if (FAILED(hr)) return;
	// 横幅をバイト単位からデータ単位へ
	const int line = lockRect.Pitch >> 2;
	DWORD* pBits = (DWORD*)lockRect.pBits;
	// 書き込み
	WriteBit(pBits,line,x,y,col);
	// アンロック
	m_pD3DTexture->UnlockRect(0);
	}

/**
* 色の取得
*/
const DWORD CEditTexture::GetColor(int x, int y) const
	{
	// テクスチャがなければ
	if(!m_pD3DTexture) return NULL;
	// 範囲チェック
	assert(x >= 0 && x < m_nWidth);
	assert(y >= 0 && y < m_nHeight);
	// テクスチャのロック
	D3DLOCKED_RECT lockRect;
	HRESULT hr = m_pD3DTexture->LockRect(0, &lockRect, nullptr, 0);
	if (FAILED(hr)) return NULL;
	// 横幅をバイト単位からデータ単位へ
	const int line = lockRect.Pitch >> 2;
	DWORD* pBits = (DWORD*)lockRect.pBits;
	// 書き込み
	DWORD col = LoadBit(pBits,line,x,y);
	// アンロック
	m_pD3DTexture->UnlockRect(0);
	return col;
	}

void CEditTexture::FillColor(DWORD col)
	{
	// テクスチャがなければ
	if(!m_pD3DTexture) return;
	// テクスチャのロック
	D3DLOCKED_RECT lockRect;
	HRESULT hr = m_pD3DTexture->LockRect(0, &lockRect, nullptr, 0);
	// 横幅をバイト単位からデータ単位へ
	const int line = lockRect.Pitch >> 2;
	DWORD* pBits = (DWORD*)lockRect.pBits;
	for (int x = 0; x < m_nWidth; ++x)
		{
		for (int y = 0; y < m_nHeight; ++y)
			{
				WriteBit(pBits,line,x,y,col);
			}
		}
	// アンロック
	m_pD3DTexture->UnlockRect(0);
	}

void CEditTexture::FillColor( int _x, int _y, int w, int h, DWORD col)
{
	// テクスチャがなければ
	if(!m_pD3DTexture) return;
	// 範囲チェック
	const int right = _x + w;
	const int bottom = _y + h;
	assert(_x >= 0 && _x < m_nWidth);
	assert(_y >= 0 && _y < m_nHeight);
	assert(right - 1 < m_nWidth);
	assert(bottom - 1 < m_nHeight);
	// テクスチャのロック
	D3DLOCKED_RECT lockRect;
	HRESULT hr = m_pD3DTexture->LockRect(0, &lockRect, nullptr, 0);
	// 横幅をバイト単位からデータ単位へ
	const int line = lockRect.Pitch >> 2;
	DWORD* pBits = (DWORD*)lockRect.pBits;
	for (int x = _x; x < right; ++x)
	{
		for (int y = _y; y < bottom; ++y)
		{
			WriteBit(pBits,line,x,y,col);
		}
	}
	// アンロック
	m_pD3DTexture->UnlockRect(0);
}

