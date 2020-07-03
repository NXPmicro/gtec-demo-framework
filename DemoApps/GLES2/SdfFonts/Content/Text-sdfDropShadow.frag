precision mediump float;

uniform sampler2D Texture;

// 0.25f / (spread * scale)
uniform float g_smoothing;
// Between 0 and spread / textureSize
uniform vec2 g_shadowOffset;
// Between 0 and 0.5
uniform float g_shadowSmoothing;

varying vec2 v_fragTextureCoord;

const vec4 FontColor = vec4(1.0);
const vec4 ShadowColor = vec4(0.0, 0.0, 0.0, 1.0);

void main()
{
  float distance = texture2D(Texture, v_fragTextureCoord).a;
  float alpha = smoothstep(0.5 - g_smoothing, 0.5 + g_smoothing, distance);
  vec4 text = vec4(FontColor.rgb, FontColor.a * alpha);

  float shadowDistance = texture2D(Texture, v_fragTextureCoord - g_shadowOffset).a;
  float shadowAlpha = smoothstep(0.5 - g_shadowSmoothing, 0.5 + g_shadowSmoothing, shadowDistance);
  vec4 shadow = vec4(ShadowColor.rgb, ShadowColor.a * shadowAlpha);

  gl_FragColor = mix(shadow, text, text.a);
}
