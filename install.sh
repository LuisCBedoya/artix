#!/bin/bash

######Variables#####
s="sudo"
il="sudo pacman -S --noconfirm --needed"
#####################
clear

echo "|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|"
echo "| Artix Installer  |"
echo "|__________________|"
echo ""
echo ""
sleep 2s
echo "Introduzca contraseña para continuar"
sudo -k
if sudo true; then
	clear
	echo "Iniciando Instalacion..."
	sleep 2s
else
	clear
	echo "Debe introduccir contraseña para continuar"
	exit 1
fi

#### Xorg Packages
$il xorg-server xorg-xinit
#### Intel Packages
$il vulkan-intel lib32-vulkan-intel vulkan-tools mesa lib32-mesa intel-media-driver libva-utils vdpauinfo clinfo intel-compute-runtime
#### Nvidia Packages
$il nvidia nvidia-settings nvidia-utils lib32-nvidia-utils cuda opencl-nvidia lib32-opencl-nvidia
#### Audio
$il pulseaudio
#### base packages
$il at-spi2-core base-devel ntfs-3g gvfs ntp unzip tar wget curl dbus polkit-gnome feh git libnotify dunst xdotool dosfstools mtools cmake 
#### useful packages
#$il ripgrep glow python-virtualenv python-pip 
#### user packages
$il noto-fonts noto-fonts-cjk noto-fonts-extra noto-fonts-emoji
$il alacritty pcmanfm leafpad zathura lxappearance flameshot gpicview mpv vlc neovim nvtop htop

#### Config AutoStart
echo -e '#autostart
\nif [ -d "$HOME/.local/bin" ] ; then
\n    PATH="$HOME/.local/bin:$PATH"
\nfi
\nsetxkbmap latam &
\nexec dbus-run-session i3'> $HOME/.xinitrc 
###
clear
echo "Instalación de ArtixWorspace Completada"
echo "Pulse cualquiera tecla para continuar..."
read tecla
clear
$s reboot
