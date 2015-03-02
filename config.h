/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,      {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,{.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,       {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag, {.ui = 1 << TAG} },

/* appearance */
static const char font[]            = "Input 10";
static const char normbordercolor[] = "#2b303b";
static const char normbgcolor[]     = "#2b303b";
static const char normfgcolor[]     = "#c0c5ce";
static const char selbordercolor[]  = "#a3b38c";
static const char selbgcolor[]      = "#a3b38c";
static const char selfgcolor[]      = "#2b303b";

static const char urgbgcolor[]      = "#bf616a";
static const char urgfgcolor[]      = "#2b303b";
static const char urgbordercolor[]  = "#bf616a";

static const unsigned int borderpx  = 3;
static const unsigned int snap      = 24;
static const unsigned int gappx     = 4;
static const float mfact            = 0.5;
static const int nmaster            = 1;
static const Bool showbar           = True;
static const Bool topbar            = False;
static const Bool resizehints       = False;
static const char clock_fmt[]       = "%m/%d/%y @ %I:%M %p";

#define MAX_TAGLEN 16
#define MONS_TAGGED 3
#define TAGMON(mon) (mon->num < MONS_TAGGED ? mon->num : MONS_TAGGED-1)
static char tags[][MONS_TAGGED][MAX_TAGLEN] = {
	/* monitor 0, monitor 1, monitor 2... */
	{ "comms",     "terms",     "codes"  },
	{ "webs",     "terms++",   "codes++" },
};

static const Layout layouts[] = {
	/* symbol   gaps?  arrange */
	{ "[t]",      True,  tile },
	{ "[b]",      True,  bstack },
	{ "[h]",      True,  bstackhoriz },
	{ "[m]",      False, monocle },
	{ "[ ]",      False, NULL },
};

static const Rule rules[] = {
    /* xprop(1):
     *  WM_CLASS(STRING) = instance, class
     *  WM_NAME(STRING) = title
     */
    /* class     instance title tags mask isfloating attachaside, monitor */
    { "Firefox", NULL,    NULL, 1<<1,        False,     False,       0 },
    { "emacs",   NULL,    NULL, NULL,        False,     False,       1},
    { "Thunderbird", NULL,NULL, (1 << 0),    False,     False, 	     0 },
    { "Pidgin",  NULL,    NULL, (1 << 0),    False,     False,       0 },
    { "urxvtc",  NULL,    NULL, NULL,        False,     False,       2},
};

/* commands */
static char dmenumon[2] = "0";
static const char *dmenu[] = { "dmenu_run", "-fn", font, "-nb", normbgcolor,
    "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };

static const char *term[]    = { "urxvtc", NULL };

static const char *vol_up[]  = { "amixer", "-q", "sset", "Master", "5%+", "unmute", NULL };
static const char *vol_dwn[] = { "amixer", "-q", "sset", "Master", "5%-", "unmute", NULL };
static const char *vol_mut[] = { "amixer", "-q", "sset", "Master", "toggle", NULL };

static const char *killdwm[]	    =	{ "killall", "dwm", NULL };
static const char *fileman[] 	    = 	{ "pcmanfm", NULL };
static const char *slockcmd[]  	    = 	{ "gnome-screensaver-command", "--lock", NULL };

/* Use function keys for tag navigation/manipulation */
#define FNTAGS(KEY,TAG)                                                 \
    { 0,                            KEY,      view,           {.ui = 1 << TAG} }, \
    { ShiftMask,                    KEY,      tag,            {.ui = 1 << TAG} }


static Key keys[] = {
    /* modifier                     key        function        argument */
    { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = term } },
    { MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
    { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    { MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = +1 } },
    { MODKEY|ShiftMask,             XK_d,      incnmaster,     {.i = -1 } },
    { MODKEY|ControlMask,           XK_j,      pushdown,       {0} },
    { MODKEY|ControlMask,           XK_k,      pushup,         {0} },
    { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
    { MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.05} },
    { MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.05} },
    { MODKEY,                       XK_Return, zoom,           {0} },
    { MODKEY,                       XK_Tab,    view,           {0} },
    { MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
    { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
    { MODKEY,                       XK_b,      setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_x,      setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[3]} },
    { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[4]} },
    { MODKEY,                       XK_space,  spawn,           {.v = dmenu} },
    { MODKEY|ShiftMask,             XK_f,  togglefloating, {0} },
    { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
    { MODKEY,                       XK_comma,  focusmon,       {.i = +1 } },
    { MODKEY,                       XK_period, focusmon,       {.i = -1 } },
    { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = +1 } },
    { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = -1 } },
    { MODKEY|ControlMask,           XK_b,      banishpointer,  {0} },
    { MODKEY|ShiftMask,             XK_n,      nametag,        {0} },
    TAGKEYS(                        XK_1,                      0)
    TAGKEYS(                        XK_2,                      1)
    TAGKEYS(                        XK_3,                      2)
    TAGKEYS(                        XK_4,                      3)
    TAGKEYS(                        XK_5,                      4)
    { MODKEY|ShiftMask,             XK_q,      quit,           {0} },
    { 0,            XF86XK_AudioLowerVolume,   spawn,          { .v = vol_dwn } },
    { 0,            XF86XK_AudioRaiseVolume,   spawn,          { .v = vol_up  } },
    { 0,            XF86XK_AudioMute,          spawn,          { .v = vol_mut } },

    /*{ 0,            XF86XK_AudioPlay,          spawn,          { .v = media_tog } },
    { 0,            XF86XK_AudioNext,          spawn,          { .v = media_nxt } },
    { 0,            XF86XK_AudioPrev,          spawn,          { .v = media_prv } },
    { 0,            XF86XK_AudioStop,          spawn,          { .v = ztream } },*/

    { ShiftMask|MODKEY,           XK_space,  spawn,          { .v = slockcmd } },
    FNTAGS(                       XK_F1,                     0),
    FNTAGS(                       XK_F2,                     1),
};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        toggleview,     {0} },
	{ ClkTagBar,            0,              Button3,        view,           {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};
