#line 1 "terrain.fx"
//------------------------------------------------------------------------------
//  ps2.0/default.fx
//
//  The default shader for dx7 cards using fixed function pipeline,
//  running in 1 render pass.
//
//  (C) 2003 RadonLabs GmbH
//------------------------------------------------------------------------------
shared float4x4 Model;
shared float4x4 View;
shared float4x4 Projection;

float4x4 TextureTransform0;
float4x4 TextureTransform1;

float4 MatAmbient;

texture AmbientMap0;                // material weight texture
texture AmbientMap1;                // material detail texture

texture ShadowMap;
texture ShadowModMap;
texture NoiseMap0;                  // a noise map

int CullMode = 2;

float4 FogColor = { 142.0 / 255.0, 140.0 / 255.0, 163.0 / 255.0, 1.0 };
float FogEnd   = 25000.0f;
float DetailEnd = 150.0f;
float TexScale = 0.008f;
float DetailTexScale = 0.1f;

float4 SnowAmplify = { 1.2, 1.2, 1.3, 0.0 };


//------------------------------------------------------------------------------
//  Texture samplers
//------------------------------------------------------------------------------
sampler WeightSampler = sampler_state
{
    Texture = <AmbientMap0>;
    AddressU  = Clamp;
    AddressV  = Clamp;
    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = None;
    MipMapLodBias = -0.75;
};

sampler DetailSampler  = sampler_state
{
    Texture = <AmbientMap1>;
    AddressU  = Wrap;
    AddressV  = Wrap;
    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = Point;
    MipMapLodBias = -0.75;
};


//------------------------------------------------------------------------------
//  The technique.
//------------------------------------------------------------------------------
technique t0
{
    pass p0
    {
        WorldTransform[0]   = <Model>;
        ViewTransform       = <View>;
        ProjectionTransform = <Projection>;

        ZWriteEnable     = true;
        ColorWriteEnable = RED|GREEN|BLUE|ALPHA;       
        ZEnable          = true;
        ZFunc            = LessEqual;
        AlphaBlendEnable = false;
        CullMode         = <CullMode>;       
        AlphaTestEnable  = false;
            
        FVF = XYZ | TEX2;
       
        VertexShader	= 0;
        PixelShader		= 0;       
     
        MaterialAmbient = {1.0, 1.0, 1.0, 1.0};
        Ambient = {1.0, 0.7284, 0.4071, 1.0};

        Lighting = true;
        LightEnable[0] = false;

        SpecularEnable	= false;   
             
        FogEnable = true;
        FogColor = {0.2, 0.2, 0.3, 1.0};
        FogVertexMode = None;
        FogTableMode = Exp2;
        FogDensity = 5.0e-4;

        Sampler[0]		= <WeightSampler>;
        Sampler[1]		= <DetailSampler>;
   
        TexCoordIndex[0]            = CAMERASPACEPOSITION;
        TextureTransformFlags[0]    = Count3;
        TextureTransform[0]         = <TextureTransform0>;

        ColorOp[0] = Modulate;
        ColorArg1[0] = Texture;
        ColorArg2[0] = Diffuse;

        TexCoordIndex[1]            = CAMERASPACEPOSITION;
        TextureTransformFlags[1]    = Count3;
        TextureTransform[1]         = <TextureTransform1>;

        ColorOp[1]   = Modulate;
        ColorArg1[1] = Texture;
        ColorArg2[1] = Current;
        
        ColorOp[2]   = Disable;
        
        AlphaOp[0] = Disable; 
    }
}