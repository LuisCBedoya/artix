/* See LICENSE file for copyright and license details. */

/* interval between updates (in ms) */
const unsigned int interval = 1000;

/* text to show if no value can be retrieved */
static const char unknown_str[] = "n/a";

/* maximum output string length */
#define MAXLEN 2048

static const struct arg args[] = {
	/* function format          argument */
  { cpu_perc,      "    [cpu %s%%] ", NULL },
	{ ram_perc,      "    [ram %s%%] ", NULL },
	{ disk_perc,     "    [disk %s%%] ", "/" },
  { run_command,   "    [vol %s] ", "pactl list sinks | tr ' ' '\n' | grep -m1 '%'"},
	// { ipv4,          "    [ eth0  %s ]",     "eth0"},
  { run_command,   "    [eth %s] ", "ip link show eth0 | grep -q 'state UP' && echo 'on' || echo 'n/a'" },
	{ wifi_essid,    "    [ wlan0  %s ]",     "wlan0"},
	{ datetime,      "    [ %s ]",     "%Y %b %e (%a) %R" },
};

