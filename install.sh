#!/bin/bash

s="sudo"
is="sudo pacman -S --noconfirm --needed"
clear

echo "|¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯¯|"
echo "|Artix Installer   |"
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

clear
echo "Installing graphics and audio..."
sleep 2s

#### Xorg Packages
$is xorg-server xorg-xinit

#### Intel Packages
$is vulkan-intel lib32-vulkan-intel vulkan-tools mesa lib32-mesa intel-media-driver libva-utils vdpauinfo clinfo intel-compute-runtime 

#### Nvidia Packages
$is nvidia nvidia-settings nvidia-utils lib32-nvidia-utils cuda opencl-nvidia  lib32-opencl-nvidia

#### Audio
$is pulseaudio 

clear
echo "Installing base packages..."
sleep 2s

$is at-spi2-core base-devel ntfs-3g gvfs ntp unzip tar wget curl dbus polkit-gnome feh git libnotify xfce4-notifyd xdo dosfstool mtools cmake ninja

clear
echo "Installing useful packages ..."
sleep 2s

$is ripgrep glow python-virtualenv python-pip 

clear
echo "Installing user packages..."
sleep 2s
$is noto-fonts noto-fonts-cjk noto-fonts-extra noto-fonts-emoji
$is kitty pcmanfm leafpad zathura lxappearance flameshot viewnior neovim

#### Config AutoStart

echo -e '#autostart
\nif [ -d "$HOME/.local/bin" ] ; then
\n    PATH="$HOME/.local/bin:$PATH"
\nfi
\nsetxkbmap latam &
\nexec dbus-run-session i3'> $HOME/.xinitrc 

###
clear
echo "Instalación de VoidBsp-term Completada"
echo "Pulse cualquiera tecla para continuar..."
read tecla
clear
$s reboot

