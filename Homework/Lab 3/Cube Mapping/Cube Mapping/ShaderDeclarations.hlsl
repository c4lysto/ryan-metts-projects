#ifndef SHADERDECLARATIONS_HLSL
#define SHADERDECLARATIONS_HLSL

#pragma pack_matrix(row_major)

cbuffer CAMERA : register(b0)
{
	float4x4 ViewProjectionMatrix;
	float4x4 InvViewProjMatrix;
	float3 CameraPos;
}

cbuffer OBJECT : register(b1)
{
	float4x4 MVPMatrix;
	float4x4 WorldMatrix;
}

texture2D DiffuseTexture1 : register(t0);
texture2D DiffuseTexture2 : register(t1);
textureCUBE CubeMapDiffuse : register(t2);

SamplerState WrapSampler : register(s0);
SamplerState ClampSampler : register(s1);

struct VERTCLR_IN
{
	float3 position : POSITION0;
	float4 color : COLOR0;
};

struct VERTCLR_OUT
{
	float4 color : COLOR0;
	float4 position : SV_POSITION;
};

struct VERTNORMUV_IN
{
	float3 position : POSITION0;
	float3 normal : NORMAL0;
	float2 texCoord : TEXCOORD0;
};

struct VERTNORMUV_OUT
{
	float2 texCoord : TEXCOORD0;
	float3 normal : NORMAL0;
	float4 position : SV_POSITION;
};

struct CUBEMAP_OUT
{
	float3 texCoord : TEXCOORD;
	float4 position : SV_POSITION;
};

#endif