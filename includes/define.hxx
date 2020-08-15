#include "funcs.hxx"

#define malloc(size, alignment) __nwa__FUl(size, alignment)
#define free(pointer) __dla__FPv(pointer)

#define dcbst(_val) asm volatile("dcbst 0, %0" \
                                 :             \
                                 : "r"(_val))
#define dcbf(_val) asm volatile("dcbf 0, %0" \
                                :            \
                                : "r"(_val))
#define icbi(_val) asm volatile("icbi 0, %0" \
                                :            \
                                : "r"(_val))

#define     SME_DEBUG   true

#define 	DEVICE_TYPE_GAMECUBE_DVD   (('G'<<24)|('D'<<16)|('V'<<8)|'D')
#define 	DVD_ERROR_CANCELED   -3
#define 	DVD_ERROR_COVER_CLOSED   -4
#define 	DVD_ERROR_FATAL   -1
#define 	DVD_ERROR_IGNORED   -2
#define 	DVD_ERROR_OK   0
#define 	DVD_RESETHARD   0
#define 	DVD_RESETNONE   2
#define 	DVD_RESETSOFT   1
#define 	DVD_SetUserData(block, data)   ((block)->usrdata = (data))
#define 	DVD_SPINMOTOR_ACCEPT   0x00004000
#define 	DVD_SPINMOTOR_CHECKDISK   0x00008000
#define 	DVD_SPINMOTOR_DOWN   0x00000000
#define 	DVD_SPINMOTOR_UP   0x00000100
#define 	DVD_STATE_BUSY   1
#define 	DVD_STATE_CANCELED   10
#define 	DVD_STATE_COVER_CLOSED   3
#define 	DVD_STATE_COVER_OPEN   5
#define 	DVD_STATE_END   0
#define 	DVD_STATE_FATAL_ERROR   -1
#define 	DVD_STATE_IGNORED   8
#define 	DVD_STATE_MOTOR_STOPPED   7
#define 	DVD_STATE_NO_DISK   4
#define 	DVD_STATE_RETRY   11
#define 	DVD_STATE_WAITING   2
#define 	DVD_STATE_WRONG_DISK   6

#define MAX_SHINES 300
#define NULL 0
#define MEM1_LO (u32*)0x80000000
#define MEM1_HI (u32*)0x81800000

#define PRESS_START	0x1000
#define PRESS_B		0x0200
#define PRESS_A		0x0100
#define PRESS_Z		0x0010
#define PRESS_X		0x0400
#define PRESS_Y		0x0800
#define PRESS_DU	0x0008
#define PRESS_DD	0x0004
#define PRESS_DL	0x0001
#define PRESS_DR	0x0002
#define PRESS_L		0x0040
#define PRESS_R		0x0020

#define MARIOFLAG_ALIVE						0x00000001
#define MARIOFLAG_INVISIBLE					0x00000004
#define MARIOFLAG_ALLDEAD					0x00000F00
#define MARIOFLAG_GAMEOVER					0x00000400
#define MARIOFLAG_SLIP						0x00000080
#define MARIOFLAG_HASHELMET_FOLLOWCAMERA	0x00001000
#define MARIOFLAG_HASHELMET					0x00002000
#define MARIOFLAG_HASFLUDD					0x00008000
#define MARIOFLAG_SPLASH					0x00010000
#define MARIOFLAG_PUDDLE					0x00020000
#define MARIOFLAG_SHIRT						0x00100000
#define MARIOFLAG_GONE						0x00200000

#define STATE_NUMBER	0x0000000F
#define STATE_DOJUMP	0x00000080
#define STATE_AIRBORN	0x00000800
#define STATE_CUTSCENE	0x00001000
#define STATE_WATERBORN	0x00002000

#define STATE_RUNNING	0x04000440
#define STATE_IDLE		0x0C400201
#define STATE_STOP		0x0C00023D
#define STATE_SPIN		0x00000441
#define STATE_JUMPSPIN	0x00000890
#define STATE_JUMPSPIN1	0x00000895
#define STATE_JUMPSPIN2	0x00000896
#define STATE_JUMP		0x02000880
#define STATE_D_JUMP	0x02000881
#define STATE_TRIPLE_J	0x00000882
#define STATE_JMP_LAND  0x04000470
#define STATE_HVY_LAND	0x04000473
#define STATE_D_LAND	0x04000472
#define STATE_T_LAND	0x0800023A
#define STATE_JUMPSIDE	0x00000880
#define STATE_BOUNCE    0x00000884
#define STATE_SIDESTEP	0x0C008220
#define STATE_SIDE_FLIP 0x00000887
#define STATE_FALL      0x0000088C
#define STATE_SWIM		0x000024D7
#define STATE_DIVE		0x0080088A
#define STATE_DIVEJUMP	0x02000889
#define STATE_DIVESLIDE	0x00800456
#define STATE_CLIMB		0x18100340
#define STATE_CLIMBUP	0x10100343
#define STATE_WALLJUMP	0x02000886
#define STATE_WALLSLIDE 0x000008A7
#define STATE_HANG		0x3800034B
#define STATE_HANGCLIMB	0x3000054F
#define STATE_SLAMSTART	0x008008A9
#define STATE_SLAM		0x0080023C
#define STATE_SPRAY		0x0C008220
#define STATE_THROWN	0x000208B8
#define STATE_HOVER		0x0000088B
#define STATE_STUCK		0x0002033C
#define STATE_TALKING	0x10001308
#define STATE_TURNING	0x00000444
#define STATE_YOSHI_ESC 0x0000089C
//add new
#define STATE_SHINE_C	0x00001302 // Collected Shine Sprite
#define STATE_DEATH		0x00020467
#define STATE_DOOR_F_O	0x00001321 // Door open fail
#define STATE_WALL_S_L	0x04000471
#define STATE_F_KNCK_H	0x000208B0 // hard knockback from front (bumping into a wall from dive)
#define STATE_KNCK_LND	0x00020462 // Landing from front knockback
#define STATE_KNCK_GND  0x00020466 // Front knockback while grounded
#define STATE_FIRE_HIT	0x000208B7
#define STATE_FIRE_RVR	0x08000239 // Recover from fire on ground
#define STATE_HOVER_F	0x0000088D // Falling from hover
#define STATE_SLIDE_R1	0x000008A6 // Recover from slide by flipping
#define STATE_SLIDE_R2 	0x00000386 // Recover from slide by getting up
#define STATE_R_SPRAY	0x0C008220 // Recover from spray
#define STATE_G_POUND	0x008008A9 // Ground pounding

//gpMarDirector States
#define WARP_OUT        0x00000002

//gpMarDirector Statuses
#define INTRO_INIT      0
#define INTRO_PLAYING   1
#define NORMAL          4
#define PAUSE_MENU      5
#define SAVE_CARD       11
//#define

#define BGM_DOLPIC          0x80010001
#define BGM_BIANCO          0x80010002
#define BGM_MAMMA           0x80010003
#define BGM_PINNAPACO_SEA   0x80010004
#define BGM_PINNAPACO       0x80010005
#define BGM_MARE_SEA        0x80010006
#define BGM_MONTEVILLAGE    0x80010007
#define BGM_SHILENA         0x80010008
#define BGM_RICCO           0x80010009
#define BGM_GET_SHINE       0x8001000A
#define BGM_CHUBOSS         0x8001000B
#define BGM_MISS            0x8001000C
#define BGM_BOSS            0x8001000D
#define BGM_MAP_SELECT      0x8001000E
#define BGM_BOSSPAKU_DEMO   0x8001000F
#define BGM_MAIN_TITLE      0x80010010
#define BGM_CHUBOSS2        0x80010011
#define BGM_EXTRA           0x80010012
#define BGM_DELFINO         0x80010013
#define BGM_MAREVILLAGE     0x80010014
#define BGM_CORONA          0x80010015
#define BGM_KAGEMARIO       0x80010016
#define BGM_CAMERA          0x80010017
#define BGM_MONTE_ONSEN     0x80010018
#define BGM_MECHAKUPPA      0x80010019
#define BGM_AIRPORT         0x8001001A
#define BGM_UNDERGROUND     0x8001001B
#define BGM_TITLEBACK       0x8001001C
#define BGM_MONTE_NIGHT     0x8001001D
#define BGM_CASINO          0x8001001E
#define BGM_EVENT           0x8001001F
#define BGM_TIME_IVENT      0x80010020
#define BGM_SKY_AND_SEA     0x80010021
#define BGM_MONTE_RESCUE    0x80010022
#define BGM_MERRY_GO_ROUND  0x80010023
#define BGM_SCENARIO_SELECT 0x80010024
#define BGM_FANFARE_CASINO  0x80010025
#define BGM_FANFARE_RACE    0x80010026
#define BGM_CAMERA_KAGE     0x80010027
#define BGM_GAMEOVER        0x80010028
#define BGM_BOSSHANA_2ND3RD 0x80010029
#define BGM_BOSSGESO_2ND3RD 0x8001002A
#define BGM_CHUBOSS_MANTA   0x8001002B
#define BGM_MONTE_LAST      0x8001002C
#define BGM_SHINE_APPEAR    0x8001002D
#define BGM_KUPPA           0x8001002E
#define BGM_SPACEWORLD		0x80011030

#define SND_PIPE			9598

//#define GFX_OFF				0x09A4 - E3
#define GFX_OFF				0x07F4

#define AIRPORT		0
#define DOLPIC0		1
#define	BIANCO0		2
#define RICCO0		3
#define MAMMA0		4
#define PINNABEACH0	5
#define SIRENA0		6
#define DELFINO0	7
#define	MONTE0		8
#define MARE0		9
#define NONE0		10
#define SCALE0		11
#define TEST10		12
#define PINNAPARCO0	13
#define CASINO0		14
#define	MONTE0		8
#define MARE0		9
#define NONE0		10
#define SCALE0		11
#define TEST10		12
#define PINNAPARCO0	13
#define CASINO0		14
#define OPTION0     15

//#define Yoshi states
#define EGG          0
#define DROWNING     3
#define DYING        4
#define UNMOUNTED    6
#define MOUNTED      8

//#define Yoshi types
#define GREEN_YOSHI  0
#define ORANGE_YOSHI 1
#define PURPLE_YOSHI 2
#define PINK_YOSHI   3

//#define Mario Voices
#define VOICE_CANNON_WAIL           30911
#define VOICE_TJUMP                 30902
#define VOICE_JUMP                  30891
#define VOICE_DIVE_OUT              30897

//#define Mario Animations
#define ANIM_IDLE                   0xC3
#define ANIM_FALL                   0x4C
#define ANIM_BOUNCE                 0x50
#define ANIM_SPINJUMP               0xF4
#define ANIM_SHINEGET               0xCD

//#define Mario Effcts
#define EFFECT_SMOKE_CLOUD              0x1
#define EFFECT_ROCKET_SPRAY_MIST        0x2
#define EFFECT_ROCKET_SPRAY_DROPS       0x3
#define EFFECT_BURNING_SMOKE            0x6
#define EFFECT_GROUND_SHARP_SHOCK       0x7
#define EFFECT_STARS                    0xC
#define EFFECT_SPARKLE                  0xE
#define EFFECT_WATER_RECHARGE           0xF
#define EFFECT_GROUND_SHOCK             0x10
#define EFFECT_GROUND_SMOKE_PLUME       0x11
#define EFFECT_WARP_IN_BODY_PIECES      0x24
#define EFFECT_WARP_IN_BELT_PIECES      0x25
#define EFFECT_WARP_IN_HAT_PIECES       0x26
#define EFFECT_WARP_IN_RED_PIECES       0x27
#define EFFECT_WARP_IN_BLUE_PIECES      0x29
#define EFFECT_WARP_IN_BROWN_PIECES     0x2A
#define EFFECT_WARP_IN_FLUDD_PIECES     0x2D
#define EFFECT_WATER_RIPPLE             0x30

//#define Fludd Types
#define SPRAY_NOZZLE        0
#define ROCKET_NOZZLE       1
#define UNDERWATER_NOZZLE   2
#define YOSHI_NOZZLE        3
#define HOVER_NOZZLE        4
#define TURBO_NOZZLE        5
#define SNIPER_NOZZLE       6

//#define Fruit IDs
#define FRUIT_COCONUT       0x40000390
#define FRUIT_PAPAYA        0x40000391
#define FRUIT_PINEAPPLE     0x40000392
#define FRUIT_DURIAN        0x40000393
#define FRUIT_BANANA        0x40000394

//define global addresses
#define WaterAddr 0x803DD898
#define CustomInfoInstance 0x80003BD0
#define YoshiColor 0x8039F934
#define ShineShadowCoordinates 0x803A1C94
#define YoshiJuiceColor 0x803DD89C
#define TApplicationInstance 0x803E9700
#define SVolumeList 0x804042B4
#define StreamVolume 0x8040C1C0
#define CPolarSubCameraInstance 0x8040D0A8
#define TCameraShakeInstance 0x8040D0B8
#define TCardLoadInstance 0x8040DDE0
#define TMapInstance 0x8040DE98
#define TMapCollisionDataInstance 0x8040DEA0
#define TPollutionManagerInstance 0x8040DED0
#define GamePad1Instance 0x8040E0D0
#define GamePad2Instance 0x8040E0D4
#define GamePad3Instance 0x8040E0D8
#define GamePad4Instance 0x8040E0DC
#define TMarioInstance 0x8040E108
#define TMarioCoordinates 0x8040E10C
#define TWaterManagerInstance 0x8040E138
#define TFlagManagerInstance 0x8040E160
#define TMarDirectorInstance 0x8040E178
#define MSoundInstance 0x8040E17C
#define TCardManagerInstance 0x8040E184
#define ARCBufferMario 0x8040E198
#define GameHeapBlock 0x8040E1A4
#define StreamID 0x8040E1F0
#define JKRSystemHeap 0x8040E290
#define JKRCurrentHeap 0x8040E294
#define JKRRootHeap 0x8040E298
#define StreamPitch 0x80417248
#define StreamSpeed 0x8041731C
