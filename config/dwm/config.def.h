static const unsigned int borderpx  = 1;
static const unsigned int gappx     = 15;
static const unsigned int snap      = 32;
static const int showbar            = 1;
static const unsigned int systraypinning = 0;
static const unsigned int systrayonleft = 0;
static const unsigned int systrayspacing = 2;  
static const int systraypinningfailfirst = 1; 
static const int showsystray        = 1;     
static const int topbar             = 0;    
static const char *fonts[]          = {"Hack Nerd Font:size=8:antialias=true:autohint=true"};
static const char dmenufont[]       = "Hack Nerd Font:size=9:antialias=true:autohint=true";
// static const char col_1[]       = "#101010";
static const char col_1[]       = "#000000";
static const char col_2[]       = "#252525";
static const char col_3[]       = "#ffffff";
static const char col_4[]       = "#b9b9b9";
static const char col_5[]       = "#151515";
static const char *colors[][3]      = {
     [SchemeNorm] = { col_3, col_1, col_5 },
     [SchemeSel]  = { col_4, col_2,  col_4  },
};

static const char *const autostart[] = {
  "setxkbmap","latam", NULL,
  // "dunst", NULL,
  // "sh", "-c", "~/.config/dunst/scripts/low_bat_notifier.sh", NULL,
  //"/usr/lib/mate-polkit/polkit-mate-authentication-agent-1", NULL,
  "feh","--bg-fill","/home/luc/.local/share/wallpapers/MM.png", NULL,
  //"slstatus",NULL,
  NULL /* terminate */
};

// static const char *tags[] = { "term", "www", "nvim", "docs", "fm", "irc", "recs", "foo", "bar" };
static const char *tags[] = { "term", "browser", "virutalm", "offload", "extra" };
/*static char *alttags[] = {"[term]",  "[browser]", "[virutalm]","[offload]", "[extra]"};*/

static const Rule rules[] = {
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

static const float mfact     = 0.50; 
static const int nmaster     = 1;   
static const int resizehints = 1;  
static const int lockfullscreen = 1;

static const Layout layouts[] = {
	{ "[]=",      tile },    
	{ "><>",      NULL },   
	{ "[M]",      monocle },
};

#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

static char dmenumon[2] = "0";
static const char *dmenucmd[] = { "dmenu_run", NULL };
static const char *termcmd[]  = { "alacritty", NULL };
static const char *termcmda[]  = {"kitty", NULL };
static const char *editor[]  = { "code", NULL };
static const char *browser[]  = { "firefox", NULL };
static const char *screenshot[] =   { "flameshot", "gui", NULL };
static const char *files[] =   { "thunar", NULL };
static const char *passwd[] =   { "keepassxc", NULL };
static const char *img[] =   { "gpicview", NULL };
static const char *brupcmd[] = { "brightnessctl", "set", "10%+", NULL };
static const char *brdowncmd[] = { "brightnessctl", "set", "10%-", NULL };
static const char *volupcmd[] = { "amixer", "set", "Master", "10%+", NULL };
static const char *voldowncmd[] = { "amixer", "set", "Master", "10%-", NULL };
static const char *volmutecmd[] = { "amixer", "set", "Master", "toggle", NULL };
static const char *lockcmd[]  = { "betterlockscreen", "-l", "-u", "/home/luc/.local/share/wallpapers/MM2.png", NULL };


static const Key keys[] = {
  { 0,                            XK_F1,     spawn,          {.v = voldowncmd} },  
  { 0,                            XK_F2,     spawn,          {.v = volupcmd} },     
  { 0,                            XK_F3,     spawn,          {.v = volmutecmd} }, 
  { 0,                            XK_F11,    spawn,          {.v = brdowncmd} },
  { 0,                            XK_F12,    spawn,          {.v = brupcmd} },   
	{ MODKEY,             		      XK_Return, spawn,          {.v =  termcmd} },
  { MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmda } },
	{ MODKEY|ShiftMask,             XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask,             XK_b,      spawn,          {.v = browser } },
	{ MODKEY|ShiftMask,             XK_s,      spawn,          {.v = screenshot } },
	{ MODKEY|ShiftMask,             XK_p,      spawn,          {.v = files } },
	{ MODKEY|ShiftMask,             XK_k,      spawn,          {.v = passwd } },
	{ MODKEY|ShiftMask,             XK_g,      spawn,          {.v = img} },
  { MODKEY|ShiftMask,             XK_l,      spawn,          {.v = lockcmd } },
  { MODKEY|ShiftMask,             XK_v,      spawn,          {.v = editor } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ Mod1Mask,                   	XK_Tab,    focusstack,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_f,      togglefullscr,  {0} },

	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,             		      XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,             		      XK_l,      setmfact,       {.f = +0.05} },
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
	{ MODKEY,                       XK_minus,  setgaps,        {.i = -1 } },
	{ MODKEY,                       XK_plus,   setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_plus,   setgaps,        {.i = 0  } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
  {MODKEY|ControlMask|ShiftMask,  XK_q,      quit,          {0}}
};

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

