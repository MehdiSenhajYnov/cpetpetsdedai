SCENEID: 56043528
--- !t!GameObject!i!7613371
id: 7613371
name: mainCameraObject
position: x: -143 y: -96
scale: x: 1 y: 1
positionType: 0
isActive: 1
parent: nullptr
_tags: [  ]
components: [ 30510471 !&! 33102371 ]
--- !t!GameObject!i!18776239
id: 18776239
name: EditorOnly
position: x: 0 y: 0
scale: x: 1 y: 1
positionType: 0
isActive: 1
parent: nullptr
_tags: [  ]
components: [ 14047131 ]
--- !t!GameObject!i!14027068
id: 14027068
name: CreatedObject14027068
position: x: 430.477 y: 488.545
scale: x: 1 y: 1
positionType: 0
isActive: 1
parent: nullptr
_tags: [  ]
components: [ 60151349 !&! 42746711 !&! 70596474 !&! 70624439 ]
--- !t!GameObject!i!90831574
id: 90831574
name: CreatedObject90831574
position: x: 229 y: 214
scale: x: 2 y: 1
positionType: 0
isActive: 1
parent: nullptr
_tags: [  ]
components: [ 83287472 ]
--- !t!GameObject!i!51048533
id: 51048533
name: CreatedObject51048533
position: x: 836 y: 530
scale: x: 1 y: 1
positionType: 0
isActive: 1
parent: nullptr
_tags: [  ]
components: [ 27780490 ]
--- !t!Camera!i!30510471
id: 30510471
componentWorkType: 2
gameObject: 7613371
CameraView: x: 1920 y: 1080
CameraRect: left: -143 top: -96 width: 1920 height: 1080
--- !t!EditorCameraUserMove!i!33102371
id: 33102371
componentWorkType: 2
gameObject: 7613371
--- !t!EditorComponent!i!14047131
id: 14047131
componentWorkType: 2
gameObject: 18776239
--- !t!SpriteRenderer!i!60151349
id: 60151349
componentWorkType: 2
gameObject: 14027068
alreadyInit: 1
Scale: x: 1 y: 1
OffsetPosition: x: 0 y: 0
ZIndex: 0
spriteName: PLAYERIDLE001
color: a: 255 r: 255 g: 255 b: 255
--- !t!Animator!i!42746711
id: 42746711
componentWorkType: 2
gameObject: 14027068
spriteRenderer: nullptr
--- !t!PlayerMove!i!70596474
id: 70596474
componentWorkType: 2
gameObject: 14027068
speed: 200
--- !t!BoxCollider!i!70624439
id: 70624439
componentWorkType: 2
gameObject: 14027068
Gravity: 0
IsStatic: 0
Visible: 1
allPoints: [ x: 0 y: 0 !&! x: 0 y: 10 ]
Center: x: 0 y: 0
--- !t!SpriteRenderer!i!83287472
id: 83287472
componentWorkType: 2
gameObject: 90831574
alreadyInit: 1
Scale: x: 1 y: 1
OffsetPosition: x: 0 y: 0
ZIndex: 0
spriteName: Square
color: a: 255 r: 120 g: 0 b: 255
--- !t!SpriteRenderer!i!27780490
id: 27780490
componentWorkType: 2
gameObject: 51048533
alreadyInit: 1
Scale: x: 1 y: 1
OffsetPosition: x: 0 y: 0
ZIndex: 0
spriteName: Square
color: a: 255 r: 0 g: 0 b: 255
