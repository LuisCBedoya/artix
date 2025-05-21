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

#### Intel CPUs
$il intel-ucode

#### Intel Packages
$il mesa vulkan-intel vulkan-tools vulkan-icd-loader intel-media-driver libva-utils intel-compute-runtime lib32-mesa lib32-vulkan-intel vdpauinfo clinfo
#$il mesa vulkan-intel vulkan-tools vulkan-icd-loader intel-media-driver libva-utils linux-firmware lib32-mesa lib32-vulkan-intel vdpauinfo clinfo

#### Nvidia Packages
$il nvidia nvidia-settings nvidia-utils cuda cudnn opencl-nvidia lib32-nvidia-utils lib32-opencl-nvidia

#### Audio
$il alsa-firmware alsa-plugins alsa-utils pulseaudio pulseaudio-alsa pavucontrol

#### Power - Powermanagement support 
#$il power-profiles-daemon upower

#### base packages
$il at-spi2-core base-devel ntfs-3g gvfs ntp unzip tar unrar wget curl dbus git ffmpegthumbnailer ffmpegthumbs gst-libav gst-plugins-bad gst-plugins-good gst-plugins-ugly gvfs-mtp iwd-openrc

### video codecs
$il ffmpeg aom libde265 x265 x264 libmpeg2 xvidcore libtheora libvpx schroedinger sdl gstreamer gst-plugins-bad gst-plugins-base gst-plugins-base-libs gst-plugins-good gst-plugins-ugly libdvdcss libdvdread dvd+rw-tools lame

#### python tools
#$il python-virtualenv pyenv

### tools
#$i fzf ripgrep brightnessctl fd

#### System fonts
$il noto-fonts noto-fonts-cjk noto-fonts-extra noto-fonts-emoji gnu-free-fonts 

#### User Packages
$il alacritty thunar thunar-archive-plugin thunar-media-tags-plugin thunar-volman lxappearance-gtk3 flameshot gpicview neovim nvtop htop libnotify dunst xdg-user-dirs feh lynx mupdf-tools ranger ffmpegthumbnailer mediainfo syncthing keepassxc xclip
#zathura-pdf-mupdf

#### in yay
#betterlockscreen ueberzugpp-new-git lsd rate-mirrors


#### Config AutoStart
xdg-user-dirs-update
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
