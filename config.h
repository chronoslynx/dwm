/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,      {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,{.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,       {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag, {.ui = 1 << TAG} },

/* appearance */
static const char font[]            = "PragmataPro for Powerline 9"; 
static const char normbordercolor[] = "#3F3F3F";
static const char normbgcolor[]     = "#3F3F3F";
static const char normfgcolor[]     = "#DCDCCC";
static const char selbordercolor[]  = "#506070";
static const char selbgcolor[]      = "#2F2F2F";
static const char selfgcolor[]      = "#DCDCCC";

static const char urgbgcolor[]      = "#1D1F21";
static const char urgfgcolor[]      = "#A54242";

static const unsigned int borderpx  = 3;
static const unsigned int snap      = 24;
static const float mfact            = 0.5;
static const int nmaster            = 1;
static const Bool showbar           = True;
static const Bool topbar            = False;
static const Bool resizehints       = False;
static const char clock_fmt[]       = "%m/%d/%y @ %I:%M %p";

static const char *tags[] = { "web", "term", "code", "media",  "misc" };

static const Layout layouts[] = {
	/* symbol   arrange */
	{ "T",      tile },
	{ "B",      bstack },
	{ "M",      monocle },
	{ "F",      NULL },
};

static const Rule rules[] = {
    /* xprop(1):
     *  WM_CLASS(STRING) = instance, class
     *  WM_NAME(STRING) = title
     */
    /* class     instance title tags mask isfloating attachaside, monitor */
    { "Firefox", NULL,    NULL, 1,        False,     False,       0 },
    { "luakit",  NULL,    NULL, 1,        False,     False,       0 },
    { "URxvt",   NULL,    NULL, 1<<1,     False,     False,       -1 },
    { "Gvim",    NULL,    NULL, 1<<2,     False,     False,       1 },
    { "URxvt",   "mail",  NULL, 1<<3,     False,     False,       0 },
    { "URxvt",   "chat",  NULL, 1<<4,     False,     False,       1 },
};

/* commands */
static char dmenumon[2] = "0";
static const char *dmenu[] = { "dmenu_run", "-fn", font, "-nb", normbgcolor, 
    "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
static const char *term[]    = { "urxvtc", NULL };
//static const char *lock[]    = { "slock", NULL };

static const char *vol_up[]   = { "amixer", "-q", "sset", "Master", "5%+", "unmute", NULL };
static const char *vol_dwn[] = { "amixer", "-q", "sset", "Master", "5%-", "unmute", NULL };
static const char *vol_mut[] = { "amixer", "-q", "sset", "Master", "toggle", NULL };

static const char *media_tog[]  = { "/home/bryan/.bin/mediactl", "toggle", NULL };
static const char *media_stp[]  = { "/home/bryan/.bin/mediactl", "stop", NULL };
static const char *media_prv[]  = { "/home/bryan/.bin/mediactl", "prev", NULL };
static const char *media_nxt[]  = { "/home/bryan/.bin/mediactl", "next", NULL };

static const char *lock_cmd[]   = { "sxlock", NULL };

static Key keys[] = {
    /* modifier                     key        function        argument */
    { MODKEY,                       XK_p,      spawn,          {.v = dmenu } },
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
    { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[3]} },
    /*{ MODKEY,                       XK_x,      setlayout,      {.v = &layouts[4]} },
    { MODKEY,                       XK_d,      setlayout,      {.v = &layouts[5]} },
    { MODKEY,                       XK_g,      setlayout,      {.v = &layouts[6]} },*/
    { MODKEY,                       XK_space,  spawn,           {.v = dmenu} },
    { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
    { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
    { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
    { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    { MODKEY|ControlMask,           XK_b,      banishpointer,  {0} }, 
    TAGKEYS(                        XK_1,                      0)
    TAGKEYS(                        XK_2,                      1)
    TAGKEYS(                        XK_3,                      2)
    TAGKEYS(                        XK_4,                      3)
    TAGKEYS(                        XK_5,                      4)
    { MODKEY|ShiftMask,             XK_q,      quit,           {0} },
    { 0,            XF86XK_AudioLowerVolume,   spawn,          { .v = vol_dwn } },
    { 0,            XF86XK_AudioRaiseVolume,   spawn,          { .v = vol_up  } },
    { 0,            XF86XK_AudioMute,          spawn,          { .v = vol_mut } },

    { 0,            XF86XK_AudioPlay,          spawn,          { .v = media_tog } },
    { 0,            XF86XK_AudioNext,          spawn,          { .v = media_nxt } },
    { 0,            XF86XK_AudioPrev,          spawn,          { .v = media_prv } },
    { 0,            XF86XK_AudioStop,          spawn,          { .v = media_stp } },

    { ControlMask|MODKEY,           XK_space,  spawn,          { .v = lock_cmd } },

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
