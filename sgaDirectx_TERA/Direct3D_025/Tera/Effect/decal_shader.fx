float4x4	matWorld : World;
float4x4	matView : View;
float4x4	matProjection : Projection;

float4		vPos[2];
float		fRange;

struct VS_INPUT 
{
   float4 Position : POSITION0;   
   float2 TexCoord : TEXCOORD0;   
};

struct VS_OUTPUT 
{
   float4 Position		: POSITION0;
   float2 TexCoord		: TEXCOORD0;
   float4 WorldPosition	: TEXCOORD1;   
};

VS_OUTPUT Default_DirectX_Effect_Pass_0_Vertex_Shader_vs_main( VS_INPUT Input )
{
   VS_OUTPUT Output;

   Output.Position = mul( Input.Position, matWorld );

   Output.WorldPosition = Output.Position;

   Output.Position = mul( Output.Position, matView );
   Output.Position = mul( Output.Position, matProjection );
   Output.TexCoord = Input.TexCoord;
   
   return( Output );
   
}

struct PS_INPUT
{
	float2 TexCoord			: TEXCOORD0; 
	float4 WorldPosition	: TEXCOORD1;    
};

texture Diffuse_Tex;
sampler2D DiffuseSampler = sampler_state
{
	Texture = Diffuse_Tex;
	MinFilter = Linear;
	MagFilter = Linear;
	MipFilter = Point;
};

float4 Default_DirectX_Effect_Pass_0_Pixel_Shader_ps_main(PS_INPUT Input) : COLOR0
{   
	float4 albedo = tex2D(DiffuseSampler, Input.TexCoord);
	float l = length(vPos[0].xz - Input.WorldPosition.xz);
	if ( l < fRange )
	{
		float fAlpha = ((fRange - l) * (fRange - l)) / (fRange * fRange);
		float4 black = float4(0, 0, 0, 0);
		albedo = albedo * (1.0 - fAlpha) + fAlpha * black;
	}

	l = length (vPos[1].xz - Input.WorldPosition.xz);
	if( l < fRange)
	{
		float fAlpha = ((fRange - l) * (fRange - l)) / (fRange * fRange);
		float4 black = float4(0, 0, 0, 0);
		albedo = albedo * (1.0 - fAlpha) + fAlpha * black;
	}
	return( albedo );
}

//--------------------------------------------------------------//
// Technique Section for Default_DirectX_Effect
//--------------------------------------------------------------//
technique Default_DirectX_Effect
{
   pass Pass_0
   {
      VertexShader = compile vs_2_0 Default_DirectX_Effect_Pass_0_Vertex_Shader_vs_main();
      PixelShader = compile ps_2_0 Default_DirectX_Effect_Pass_0_Pixel_Shader_ps_main();
   }

}

