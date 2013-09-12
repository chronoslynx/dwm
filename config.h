/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const char font[]            = "Source Code Pro Light 9";
static const char normbordercolor[] = "#262626";
static const char normbgcolor[]     = "#262626";
static const char normfgcolor[]     = "#e4e4e4";
static const char selbordercolor[]  = "#e9afcc";
static const char selbgcolor[]      = "#e9afcc";
static const char selfgcolor[]      = "#262626";
static const unsigned int minwsz    = 50;       /* Minimum size of client's window wrt smfact*/
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const Bool showbar           = True;     /* False means no bar */
static const Bool topbar            = True;     /* False means bottom bar */
static const unsigned int gappx     = 10;        /* Gap applied around windows */

/* tagging */
static const char *tags[] = { "web", "code", "term", "mail", "chat", "misc", };

static const Rule rules[] = {
    /* xprop(1):
     *  WM_CLASS(STRING) = instance, class
     *  WM_NAME(STRING) = title
     */
    /* class      instance    title       tags mask     isfloating   monitor */
    { "Gimp",     NULL,       NULL,       0,            True,        -1 },
};

/* layout(s) */
static const float mfact      = 0.5; /* factor of master area size [0.05..0.95] */
static const float smfact     = 0.0; /* factor of bottom slave (0.0 == "Normally tiled")*/
static const int nmaster      = 1;    /* number of clients in master area */
static const Bool resizehints = False; /* True means respect size hints in tiled resizals */

static const Layout layouts[] = {
    /* symbol     arrange function */
    { "[T]",      tile },    /* first entry is default */
    { "[F]",      NULL },    /* no layout function means floating behavior */
    { "[M]",      monocle },
    { "[B]",      bstack },
    { "[H]",      bstackhoriz },
    { "[D]",      deck },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
    { MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
    { MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
    { MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static const char *dmenucmd[] = { "dmenu_run", "-fn", font, "-nb", normbgcolor, "-nf", normfgcolor, "-sb", selbgcolor, "-sf", selfgcolor, NULL };
//static const char *termcmd[]  = { "st", NULL };
static const char *termcmd[]  = { "urxvt", NULL };
static const char *mpd_tog[]  = { "ncmpcpp", "toggle", NULL };
static const char *mpd_stp[]  = { "ncmpcpp", "stop", NULL };
static const char *mpd_prv[]  = { "ncmpcpp", "prev", NULL };
static const char *mpd_nxt[]  = { "ncmpcpp", "next", NULL }; 

static const char *vol_mut[]  = { "amixer", "set", "Master", "toggle", NULL };
static const char *vol_dwn[]  = { "amixer", "set", "Master", "5%-", NULL };
static const char *vol_up[]   = { "amixer", "set", "Master", "5%+", NULL };

static const char *lock_cmd[]   = { "sxlock", NULL };

static Key keys[] = {
    /* modifier                     key        function        argument */
    { MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
    { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },
    { MODKEY|ShiftMask,             XK_b,      togglebar,      {0} },
    { MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
    { MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
    { MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = +1 } },
    { MODKEY|ShiftMask,             XK_d,      incnmaster,     {.i = -1 } },
    { MODKEY|ControlMask,           XK_j,      pushdown,       {0} },
    { MODKEY|ControlMask,           XK_k,      pushup,         {0} },
    { MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
    { MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
    { MODKEY|ShiftMask,             XK_h,      setsmfact,      {.f = +0.05} },
    { MODKEY|ShiftMask,             XK_l,      setsmfact,      {.f = -0.05} },
    { MODKEY,                       XK_Return, zoom,           {0} },
    { MODKEY,                       XK_Tab,    view,           {0} },
    { MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
    { MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
    { MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
    { MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
    { MODKEY,                       XK_b,      setlayout,      {.v = &layouts[3]} },
    { MODKEY,                       XK_x,      setlayout,      {.v = &layouts[4]} },
    { MODKEY,                       XK_d,      setlayout,      {.v = &layouts[5]} },
    { MODKEY,                       XK_space,  setlayout,      {0} },
    { MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
    { MODKEY,                       XK_0,      view,           {.ui = ~0 } },
    { MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
    { MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
    { MODKEY,                       XK_period, focusmon,       {.i = +1 } },
    { MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
    { MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
    TAGKEYS(                        XK_1,                      0)
    TAGKEYS(                        XK_2,                      1)
    TAGKEYS(                        XK_3,                      2)
    TAGKEYS(                        XK_4,                      3)
    TAGKEYS(                        XK_5,                      4)
    TAGKEYS(                        XK_6,                      5)
    TAGKEYS(                        XK_7,                      6)
    { MODKEY|ShiftMask,             XK_q,      quit,           {0} },
    { 0,            XF86XK_AudioLowerVolume,   spawn,          { .v = vol_dwn } },
    { 0,            XF86XK_AudioRaiseVolume,   spawn,          { .v = vol_up  } },
    { 0,            XF86XK_AudioMute,          spawn,          { .v = vol_mut } },

    { 0,            XF86XK_AudioPlay,          spawn,          { .v = mpd_tog } },
    { 0,            XF86XK_AudioNext,          spawn,          { .v = mpd_nxt } },
    { 0,            XF86XK_AudioPrev,          spawn,          { .v = mpd_prv } },
    { 0,            XF86XK_AudioStop,          spawn,          { .v = mpd_stp } },

    { ControlMask|MODKEY,           XK_space,  spawn,          { .v = lock_cmd } }, 

};

/* button definitions */
/* click can be ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
    /* click                event mask      button          function        argument */
    { ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
    { ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
    { ClkWinTitle,          0,              Button2,        zoom,           {0} },
    { ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
    { ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
    { ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
    { ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
    { ClkTagBar,            0,              Button1,        view,           {0} },
    { ClkTagBar,            0,              Button3,        toggleview,     {0} },
    { ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
    { ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

