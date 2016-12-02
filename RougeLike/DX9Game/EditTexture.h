#pragma once
#include <d3dx9.h>


//作成:高橋陸
class CEditTexture
	{
	public:
		/**
		* コンストラクタ
		* width テクスチャの横幅
		* height テクスチャの縦幅
		* pDevice DirectXのデバイス
		*/
		CEditTexture(int width, int height, LPDIRECT3DDEVICE9 pDevice);

		/**
		* デストラクタ
		*/
		~CEditTexture();

		/**
		* 色のセット
		* x X座標
		* y Y座標
		*/
		void SetColor(int x, int y, DWORD col);

		/**
		* 色の取得
		* x X座標
		* y Y座標
		*/
		const DWORD GetColor(int x, int y) const;

		/**
		* 塗りつぶし
		* ロックが一回ですみます
		*/
		void FillColor(DWORD col);

		/**
		* 塗りつぶし
		*/
		void FillColor( int x, int y, int w, int h, DWORD col);

		/**
		* 色のプロパティ
		*/
		_declspec(property(get = getter, put = SetColor)) DWORD color[][];

		/**
		* テクスチャへのキャスト
		*/
		operator IDirect3DBaseTexture9*() { return this ? m_pD3DTexture : nullptr; }
	private:
		LPDIRECT3DTEXTURE9 m_pD3DTexture;
		int m_nWidth;
		int m_nHeight;
	};