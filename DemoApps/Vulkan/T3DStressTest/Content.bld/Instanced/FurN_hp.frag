#version 310 es
precision highp float;
#define MAX_LIGHTS 10

layout(location = 0) in mediump vec3 v_normal;
layout(location = 1) in mediump vec2 v_texcoord;
layout(location = 2) in mediump float v_layerDepth;

layout(std140, binding = 0) uniform UBO
{
  mat4 World;
  mat4 View;
  mat4 Projection;
  vec4 Displacement;
  vec4 AmbientColor;
  float MaxHairLength;
  float InstanceMul;
  float LightCount;
  float Reserved0;
  vec4 LightDirection[MAX_LIGHTS];
  vec4 LightColor[MAX_LIGHTS];
}
g_ubo;

layout(binding = 1) uniform sampler2D Texture0;
layout(binding = 2) uniform sampler2D Texture1;

layout(location = 0) out vec4 o_fragColor;

void main()
{
  vec4 furColor = texture(Texture0, v_texcoord);
  vec4 furData = texture(Texture1, v_texcoord);
  // based on layer depth, choose the amount of shading.
  // we lerp between two values to avoid having the base of the fur pure black.

  float dist = mix(1.0, 0.2, v_layerDepth);
  float shadow = mix(0.4, 1.0, v_layerDepth);
  furColor *= shadow;
  float furVisibility = (v_layerDepth > furData.r) ? 0.0 : furData.a * dist;
  furColor.a = (v_layerDepth == 0.0) ? 1.0 : furVisibility;
  vec3 N = normalize(v_normal);

  vec3 lighting = g_ubo.AmbientColor.xyz;
  for (int i = 0; i < int(g_ubo.LightCount); ++i)
  {
    vec3 L = normalize(-g_ubo.LightDirection[i].xyz);
    float lightAmount = max(dot(N, L), 0.0);
    lighting += lightAmount * g_ubo.LightColor[i].xyz;
  }

  furColor.xyz *= lighting;
  o_fragColor = furColor;
}
