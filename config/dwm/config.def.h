/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>
/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int systraypinning = 0;   /* 0: sloppy systray follows selected monitor, >0: pin systray to monitor X */
static const unsigned int systrayonleft = 0;    /* 0: systray in the right corner, >0: systray on left of status text */
static const unsigned int systrayspacing = 2;   /* systray spacing */
static const int systraypinningfailfirst = 1;   /* 1: if pinning fails, display systray on the first monitor, False: display systray on the last monitor*/
static const int showsystray        = 1;        /* 0 means no systray */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
/* static const char *fonts[]          = { "HackRegular:size=9:style=Bold" }; */
/* static const char dmenufont[]       = "HackRegular:size=9:style=Bold"; */
static const char *fonts[]          = { "HackBold:size=9:style=Bold" };
static const char dmenufont[]       = "HackBold:size=9:style=Bold";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#eeeeee";
/* static const char col_cyan[]        = "#215B8B"; */
static const char col_cyan[]        = "#306A98";

/* "#005577"; */
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

static const char *const autostart[] = {
  "setxkbmap","latam", NULL,
  "numlockx","on", NULL,
  /* "picom", NULL, */
  "dunst", NULL,
  "nitrogen", "--restore", NULL,
  "pipewire", NULL,
  "pipewire-pulse", NULL,
  "wireplumber", NULL,
  "slstatus", NULL,
  "sh", "-c", "~/.config/dunst/scripts/low_bat_notifier.sh", NULL,
  "/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1", NULL,
  NULL /* terminate */
};


/* tagging */
/* static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" }; */
static const char *tags[] = { "ぜろ", " いち", "に", "さん", "し", "ご", "ろく", "しち", "はち" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class                  instance    title       tags mask     isfloating   monitor */
	{ "Gimp",                 NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",              NULL,       NULL,       0,            0,           -1 },
  { "Lxappearance",         NULL,       NULL,       0,            1,           -1 },
  { "Nitrogen",             NULL,       NULL,       0,            1,           -1 },
  { "Blueman-manager",      NULL,       NULL,       0,            1,           -1 },
  { "Connman-gtk",          NULL,       NULL,       0,            1,           -1 },
  { "Pavucontrol",          NULL,       NULL,       0,            1,           -1 },
  { "KeePassXC",            NULL,       NULL,       0,            1,           -1 },
  { "SimpleScreenRecorder", NULL,       NULL,       0,            1,           -1 },
  { "Pinta",                NULL,       NULL,       0,            1,           -1 },
  { "phototonic",           NULL,       NULL,       0,            1,           -1 },
  { "Pcmanfm",              NULL,       NULL,       0,            1,           -1 },
  { "Leafpad",              NULL,       NULL,       0,            1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

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
/* helper for spawning shell commands in the pre dwm-5.0 fashion */ #define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0";
static const char *dmenucmd[] = { "rofi", "-show","drun", NULL };
static const char *termcmda[]  = { "st", NULL };

static const char *termcmd[]  = { "kitty", NULL }; 
static const char *chromium[]  = { "chromium", NULL };
static const char *flameshot[] =   { "flameshot", "gui", NULL };
static const char *pcmanfm[] =   { "pcmanfm", NULL };
static const char *keepassxc[] =   { "keepassxc", NULL };
static const char *phototonic[] =   { "phototonic", NULL };
static const char *leafpad[] =   { "leafpad", NULL };
static const char *pavucontrol[] =   { "pavucontrol", NULL };
static const char *blueman[]  = { "blueman-manager", NULL }; 
static const char *nitrogen[] =   { "nitrogen", NULL };
static const char *pinta[] =   { "pinta", NULL };
static const char *record[] =   { "simplescreenrecorder", NULL };
static const char *lxappearance[] =   { "lxappearance", NULL };
static const char *connman[] =   { "connman-gtk", NULL };
static const char *mutecmd[] = { "amixer", "-q", "set", "Master", "toggle", NULL };
static const char *volupcmd[] = { "amixer", "-q", "set", "Master", "5%+", "unmute", NULL };
static const char *voldowncmd[] = { "amixer", "-q", "set", "Master", "5%-", "unmute", NULL };

static const Key keys[] = {
	/* modifier                     key        function        argument */

  { MODKEY|ShiftMask,             XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,             		      XK_Return, spawn,          {.v =  termcmd} },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmda } }, 
	{ MODKEY|ShiftMask,             XK_b,      spawn,          {.v = chromium } },
  { MODKEY|ShiftMask,             XK_p,      spawn,          {.v = pcmanfm } },
  { MODKEY|ShiftMask,             XK_t,      spawn,          {.v = leafpad} },
  { MODKEY|ShiftMask,             XK_r,      spawn,          {.v = phototonic } },
  { MODKEY|ShiftMask,             XK_k,      spawn,          {.v = keepassxc } },
	{ MODKEY|ShiftMask,             XK_f,      spawn,          {.v = flameshot } },
	{ MODKEY|ShiftMask,             XK_v,      spawn,          {.v = pavucontrol } },
	{ MODKEY|ShiftMask,             XK_n,      spawn,          {.v = nitrogen } },
	{ MODKEY|ShiftMask,             XK_a,      spawn,          {.v = lxappearance } },
	{ MODKEY|ShiftMask,             XK_c,      spawn,          {.v = blueman } },
	{ MODKEY|ShiftMask,             XK_w,      spawn,          {.v = connman } },
	{ MODKEY|ShiftMask,             XK_g,      spawn,          {.v = record } },
	{ MODKEY|ShiftMask,             XK_y,      spawn,          {.v = pinta } },
  { 0, XF86XK_AudioMute, spawn, {.v = mutecmd } },
  { 0, XF86XK_AudioLowerVolume, spawn, {.v = voldowncmd } },
  { 0, XF86XK_AudioRaiseVolume, spawn, {.v = volupcmd } },



	/* { MODKEY|ShiftMask,             XK_e,      spawn,          SHCMD("sh /opt/idea/bin/idea.sh") }, */
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_c,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY|ShiftMask,             XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ControlMask,           XK_Return, zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
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
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
  {MODKEY|ControlMask|ShiftMask,  XK_q,      quit,           {0} }
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static const Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
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

