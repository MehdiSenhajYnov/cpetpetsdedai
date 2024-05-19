SCENEID: 77161918
--- !t!GameObject!i!13681869
id: 13681869
name: mainCameraObject
position: x: 0 y: 0
scale: x: 1 y: 1
positionType: 0
isActive: 1
parent: nullptr
_tags: [  ]
components: [ 16008663 !&! 37682226 ]
--- !t!GameObject!i!75920345
id: 75920345
name: playButton
position: x: 950 y: 550
scale: x: 1 y: 1
positionType: 0
isActive: 1
parent: nullptr
_tags: [  ]
components: [ 50954194 !&! 16641037 !&! 68381509 ]
--- !t!GameObject!i!52044986
id: 52044986
name: exitButton
position: x: 950 y: 650
scale: x: 1 y: 1
positionType: 0
isActive: 1
parent: nullptr
_tags: [  ]
components: [ 37602609 !&! 96818112 !&! 39273205 ]
--- !t!Camera!i!16008663
id: 16008663
componentWorkType: 2
gameObject: 13681869
CameraView: x: 1920 y: 1080
CameraRect: left: 0 top: 0 width: 1920 height: 1080
--- !t!EditorCameraUserMove!i!37682226
id: 37682226
componentWorkType: 2
gameObject: 13681869
--- !t!Button!i!50954194
id: 50954194
componentWorkType: 2
gameObject: 75920345
baseColor: a: 255 r: 0 g: 0 b: 0
hoverColor: a: 255 r: 110 g: 110 b: 110
pressedColor: a: 255 r: 80 g: 80 b: 80
textColor: a: 255 r: 0 g: 0 b: 0
wantHoverColor: 1
wantPressedColor: 1
spriteRenderer: 16641037
textComponent: 68381509
buttonInitialized: 1
OnButtonClicked: [ OnPlayButtonClicked77161918 ]
--- !t!SpriteRenderer!i!16641037
id: 16641037
componentWorkType: 2
gameObject: 75920345
alreadyInit: 1
Scale: x: 1 y: 1
OffsetPosition: x: 0 y: 0
ZIndex: 20
spriteName: RoundedRectangle
color: a: 255 r: 110 g: 110 b: 110
--- !t!TextComponent!i!68381509
id: 68381509
componentWorkType: 2
gameObject: 75920345
alreadyInit: 1
Scale: x: 1 y: 1
OffsetPosition: x: 0 y: 0
ZIndex: 0
currentText: PLAY
--- !t!Button!i!37602609
id: 37602609
componentWorkType: 2
gameObject: 52044986
baseColor: a: 255 r: 0 g: 0 b: 0
hoverColor: a: 255 r: 110 g: 110 b: 110
pressedColor: a: 255 r: 80 g: 80 b: 80
textColor: a: 255 r: 255 g: 255 b: 255
wantHoverColor: 1
wantPressedColor: 1
spriteRenderer: 96818112
textComponent: 39273205
buttonInitialized: 1
OnButtonClicked: [ OnExitButtonClicked77161918 ]
--- !t!SpriteRenderer!i!96818112
id: 96818112
componentWorkType: 2
gameObject: 52044986
alreadyInit: 1
Scale: x: 1 y: 1
OffsetPosition: x: 0 y: 0
ZIndex: 20
spriteName: RoundedRectangle
color: a: 255 r: 0 g: 0 b: 0
--- !t!TextComponent!i!39273205
id: 39273205
componentWorkType: 2
gameObject: 52044986
alreadyInit: 1
Scale: x: 1 y: 1
OffsetPosition: x: 0 y: 0
ZIndex: 0
currentText: EXIT
