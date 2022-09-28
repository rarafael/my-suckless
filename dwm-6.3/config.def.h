/* See LICENSE file for copyright and license details. */
#define TERMINAL  "st"           /* default terminal */
#define TERMCLASS "st-256color"  /* terminal class name */
#define BROWSER   "firefox"      /* default web browser */

/* appearance */
static const unsigned int borderpx       = 1;   /* border pixel of windows */
static const unsigned int snap           = 32;  /* snap pixel */
static const unsigned int gappx          = 4;   /* gap size */
static const int swallowfloating         = 0;   /* swallow floating windows */
static const int lockfullscreen          = 1;   /* 1 will force focus on the fullscreen window */
static const int showbar                 = 1;   /* 0 means no bar */
static const int topbar                  = 1;   /* 0 means bottom bar */
static const char *fonts[]               = { "Iosevka Nerd Font Mono:size=11" };
static const char dmenufont[]            = "Iosevka Nerd Font Mono:size=11";
static const char border_color[]         = "#baa67f";
static const char border_colors[]        = "#f75341";
static const char fg_color1[]            = "#baa67f";
static const char fg_color2[]            = "#fce8c3";
static const char bg_color1[]            = "#1c1b19";
static const char bg_color2[]            = "#918175";
static const char *colors[][3]           = {
	/*               fg         bg         border   */
	[SchemeNorm] = { fg_color1, bg_color1, border_color  },
	[SchemeSel]  = { fg_color2, bg_color2, border_colors },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */

	/* class     instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	{ "Gimp",    NULL,     NULL,           0,         1,          0,           0,        -1 },
	{ "Gimp",    NULL,     "GNU Image Manipulation Program",           0,         0,          0,           0,        -1 },
	{ "Discord", NULL,     NULL,           4,         0,          0,           0,        -1 },
	{ "Steam",   NULL,     NULL,           4,         0,          0,           1,        -1 },
	{ BROWSER,   NULL,     NULL,           0,         0,          0,           0,        -1 },
	{ TERMCLASS, NULL,     NULL,           0,         0,          1,           0,        -1 },
	{ NULL,      NULL,     "Event Tester", 0,         0,          0,           1,        -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
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
static char dmenumon[2]            = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]      = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", bg_color1, "-nf", fg_color1, "-sb", bg_color2, "-sf", fg_color2, "-l", "14", "-c", NULL };
static const char *termcmd[]         = { TERMINAL, NULL };
static const char *browsercmd[]      = { BROWSER, NULL };
static const char *screenshotcmd[]   = { "screenshot", NULL };
static const char *upvolumecmd[]     = { "amixer", "-q", "-D", "pulse", "sset", "Master", "3276+", NULL };
static const char *downvolumecmd[]   = { "amixer", "-q", "-D", "pulse", "sset", "Master", "3276-", NULL };
static const char *mutevolumecmd[]   = { "amixer", "-q", "-D", "pulse", "sset", "Master", "toggle", NULL };
static const char* changeoutputcmd[] = { "change-audio", NULL };
static const char *exitttycmd[]      = { "killall", "xinit", NULL };

#include "movestack.c"
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ControlMask,           XK_t,      spawn,          {.v = termcmd } },
	{ MODKEY|ControlMask,           XK_b,      spawn,          {.v = browsercmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,			XK_f,      togglefullscr,  {0} },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
        { MODKEY,                       XK_F1,     spawn,          {.v = changeoutputcmd } },
	{ MODKEY,                       XK_F2,     spawn,          {.v = downvolumecmd } },
	{ MODKEY,                       XK_F3,     spawn,          {.v = upvolumecmd } },
	{ MODKEY,                       XK_F4,     spawn,          {.v = mutevolumecmd } },
	{ MODKEY,                       XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          {.v = screenshotcmd } },
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
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask|ControlMask, XK_c,      spawn,          {.v = exitttycmd} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
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

