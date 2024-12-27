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

#### X11 - Default X11 system
$il xorg-xdpyinfo xorg-server xorg-xinit xorg-xinput xorg-xkill xorg-xrandr

#### CPU specific microcode update packages Microcode update image for AMD and Intel CPUs
$il intel-ucode

#### GPU - drivers Graphics hardware intel and amd
$il xf86-video-intel vulkan-intel lib32-vulkan-intel vulkan-tools mesa lib32-mesa intel-media-driver libva-utils vdpauinfo clinfo intel-compute-runtime

#### Nvidia Packages
$il nvidia nvidia-settings nvidia-utils lib32-nvidia-utils cuda opencl-nvidia lib32-opencl-nvidia

#### Audio - Audio handling tools apps and libs
$il alsa-firmware alsa-plugins alsa-utils pulseaudio pulseaudio-alsa pamixer pavucontrol

#### Video codecs
$il ffmpeg aom libde265 x265 x264 libmpeg2 xvidcore libtheora libvpx schroedinger sdl gstreamer gst-plugins-bad gst-plugins-base gst-plugins-base-libs gst-plugins-good gst-plugins-ugly xine-lib libdvdcss libdvdread dvd+rw-tools lame

#### Power - Powermanagement support 
$il power-profiles-daemon upower

#### Network - Network apps drivers and tools
$il dhcpcd networkmanager iwd net-tools ifplugd iw wireless_tools wpa_supplicant dialog wireless-regdb

#### Recommended applications selection - General tools and applications
$il git hwinfo inxi rsync wget curl

#Filesystem - Filesystem tools and applications
$il efitools nfs-utils nilfs-utils ntp at-spi2-core base-devel ntfs-3g gvfs tar unrar unzip tar dbus xdotool dosfstools mtools

#### Package - management Packages tools
$il downgrade pacman-contrib pkgfile rebuild-detector reflector yay 

#### Fonts
$il gnu-free-fonts ttf-hack ttf-inconsolata gnome-font-viewer

#### useful packages
#$il ripgrep glow python-virtualenv python-pip

#### user packages
$il alacritty pcmanfm leafpad zathura lxappearance flameshot gpicview mpv neovim nvtop htop feh libnotify dunst lxqt-policykit

echo -e '#autostart
\nexport XDG_SESSION_TYPE=x11
\nexport GDK_BACKEND=x11
\nsetxkbmap latam &
\npipewire &
\nexec dbus-run-session i3'> $HOME/.xinitrc

clear
echo "Instalación de ArtixWorspace Completada"
echo "Pulse cualquiera tecla para continuar..."
read tecla
clear
$s reboot
