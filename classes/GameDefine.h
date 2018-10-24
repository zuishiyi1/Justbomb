#ifndef _GAMEDEFINE_H_
#define _GAMEDEFINE_H_


#define ROW 8
#define COL 7


static const char *elementnormal[5] =
{
	"star.png",
	"blueball.png",
	"ziball.png",
	"eye.png",
	"fire.png"
};

static const char* elementdamage = "kulou.png";

static const char* elementwind = "windball.png";

static const char* elementfire = "fireball.png";

static const char* elementdark = "darkball.png";

static const char* elementland = "landball.png";


enum DisplayMode
{
	normal=0,
	damage,
	wind,
	fire,
	dark,
	land,
};

enum State
{
	openpk=0,
	closepk,
	state_usekulouitem,
	state_useaddwinditem,
	state_useclearallitem,
};

static const char* itemclearkulou = "kulouitem.png";

static const char* itemaddwind = "addwind.png";

static const char* itemclearall = "clearall.png";


enum conditonforwin
{
	scoredayuerbai=5,
	wanchengliangcicixuanfeng,
	scoredayuyibaibingbunengyicikulou,
};

#endif