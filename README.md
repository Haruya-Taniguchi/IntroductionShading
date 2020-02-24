# IntroductionShading
 
GLSLでのシェーディング入門のために書いたコード
![preview](https://i.gyazo.com/ade125a91627e5b218e68769565306da.png)

# Dependency
## framework
openframeworks 0.11.0
## addon
 - ofxGui 
 - ofxAssimpModelLoader

# Usage
キーボードとマウスで操作
## Mouse
- ドラッグでモデル回転
- 'lightDirスライダー'で平行光源のベクトルを操作
## Keyboard
- 数字キーで表示する図形の変更
  - '0' ウサギの3dモデル
  - '1' ofSpherePrimitive
  - '2' ofIcoSpherePrimitive
  - '3' ofCylinderPrimitive
  - '4' ofBoxPrimitive
- アルファベットのキーでシェーディングの変更
  - 'a' グーローシェーディング
  - 'b' フォンシェーディング
  - 'c' フラットシェーディング
  - 'd' オリジナルのシェーディング1
  - 'e' オリジナルのシェーディング2

