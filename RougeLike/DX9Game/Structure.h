#pragma once


#include <d3d9.h>
#include <d3dx9.h>

//テクスチャ描画時に必要な要素をまとめた構造体
typedef struct
{
	D3DXVECTOR3 pos;    //頂点座標
	float       rhw;    //テクスチャのパースペクティブコレクト用
	D3DCOLOR    col;    //頂点カラー
	D3DXVECTOR2 tex;    //テクスチャ座標
}VERTEX_2D;


//頂点フォーマット（頂点座標[2D]/頂点カラー）
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)//(位置情報 | カラー | テクスチャの情報0じゃだめ)

//頂点数
#define NUM_VERTEX  (4)

//ポリゴン数
#define NUM_POLYGON 2