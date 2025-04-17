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

#### CPU specific microcode update packages Microcode update image for AMD and Intel CPUs
$il intel-ucode

#### Intel Packages 32libs
#$il lib32-mesa lib32-vulkan-intel vdpauinfo clinfo 

#### Intel Packages
$il mesa vulkan-intel vulkan-tools vulkan-icd-loader intel-media-driver libva-utils intel-compute-runtime
#$il mesa vulkan-intel vulkan-tools vulkan-icd-loader intel-media-driver libva-utils linux-firmware lib32-vulkan-intel

#### Nvidia Packages 32libs
#$il lib32-nvidia-utils lib32-opencl-nvidia

#### Nvidia Packages
$il nvidia nvidia-settings nvidia-utils cuda cudnn opencl-nvidia 

#### Audio
$il alsa-firmware alsa-plugins alsa-utils pulseaudio pulseaudio-alsa pavucontrol

#### Power - Powermanagement support 
#$il power-profiles-daemon upower

#### base packages
$il at-spi2-core base-devel ntfs-3g gvfs ntp unzip tar wget curl dbus git xdotool dosfstools mtools ffmpegthumbnailer ffmpegthumbs gst-libav gst-plugins-bad gst-plugins-good gst-plugins-ugly gvfs-mtp

#### python tools
$il python-virtualenv pyenv

### video codecs
#$il ffmpeg aom libde265 x265 x264 libmpeg2 xvidcore libtheora libvpx schroedinger sdl gstreamer gst-plugins-bad gst-plugins-base gst-plugins-base-libs gst-plugins-good gst-plugins-ugly libdvdcss libdvdread dvd+rw-tools lame

#### System fonts
$il noto-fonts noto-fonts-cjk noto-fonts-extra noto-fonts-emoji gnu-free-fonts 

#### User Packages
$il alacritty thunar leafpad zathura lxappearance flameshot gpicview vlc neovim nvtop htop libnotify dunst ripgrep

#### Config AutoStart
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
