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

# paquetes xorg 
$is xorg xorg-xinit xorg-server-xdmx xorg-xsetroot xdo xorg-xbacklight
# Compilacion, windows, red y demas
$is ncurses openssl dkms lz4 bc rsync linux-zen-headers ninja fuse cmake git python-pip libglvnd at-spi2-core base-devel p7zip ntp ntfs-3g exfat-utils pciutils lshw network-manager-applet mtools dosfstools gvfs wget curl unzip tar dbus ripgrep python-virtualenv
# intel 
$is xf86-video-intel vulkan-intel lib32-vulkan-intel vulkan-tools mesa lib32-mesa
$is libva-intel-driver libva-utils vdpauinfo clinfo
$is intel-compute-runtime
#nvidia
$is nvidia-dkms nvidia-settings cuda nvidia-utils lib32-nvidia-utils opencl-nvidia  lib32-opencl-nvidia vdpauinfo clinfo
#audio
$is pulsemixer pipewire pipewire-pulse wireplumber alsa-utils
#navegador and fonts
$is chromium noto-fonts noto-fonts-cjk noto-fonts-extra noto-fonts-emoji
#wallpapers
$is nitrogen
#notificaciones
$is dunst libnotify
# numkeys
$is numlockx
# explorador de archivos
$is pcmanfm
# lector de pdf 
$is zathura
#imagenes
$is phototonic
# capturas de pantalla
$is flameshot
#editor de texto
$is leafpad
# reproductor de audio y video
$is mpv
# administrador de pantalla
$is arandr
#terminal
$is kitty
#screen record
$is simplescreenrecorder
#info terminal
$is neofetch
# temas
$is lxappearance
#bluetooth
#$is bluez bluez-libs bluez-utils bluez-openrc blueman
# paint
$is pinta
#Android Debug Bridge
$is android-tools
#pass
$is keepassxc
#vol
$is pavucontrol

