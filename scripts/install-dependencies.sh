#!/usr/bin/env sh

if [[ $EUID != 0 ]]; then
    echo "Warning: you may need to run this script as admistrator!"
fi

which lsb_release 1>/dev/null 2>&1

if [ $? = 0 ]; then
    OS=$(lsb_release -si)
elif [ -f /etc/os-release ]; then
    source /etc/os-release
    OS=${NAME}
else
    echo "Unknown OS"
fi

ARCH=$(uname -m | sed 's/x86_//;s/i[3-6]86/32/')
# VER=$(lsb_release -sr)
PACKAGES=""

case $OS in
    "Ubuntu")
	PACKAGES="cmake \
               	libwayland-dev \
		libxkbcommon-dev \
		libegl1-mesa-dev \
		libgl1-mesa-dev \
		libgles2-mesa-dev \
		libvulkan-dev \
		libjpeg-dev \
		libgif-dev \
		libfreetype6-dev \
		libfontconfig1-dev \
		libexpat1-dev \
		zlib1g-dev \
		libwebp-dev \
		liblua5.3-dev \
		libinput-dev \
		libavcodec-dev \
		libavformat-dev \
		libavdevice-dev \
		libavutil-dev \
		libavfilter-dev \
		libswscale-dev \
		libpostproc-dev \
		libswresample-dev \
		doxygen \
		graphviz"
	apt install ${PACKAGES}
	;;
    "Fedora")
        echo "Please make sure that rpmfusion repos were loaded."
	PACKAGES="gcc-c++ \
		cmake \
		wayland-devel \
		libxkbcommon-devel \
		mesa-libwayland-egl-devel \
		mesa-libGLES-devel \
		mesa-libGL-devel \
		mesa-libEGL-devel \
		vulkan-devel \
		libwebp-devel \
		libjpeg-turbo-devel \
		giflib-devel \
		expat-devel \
		zlib-devel \
		lua-devel \
		libinput-devel \
		freetype-devel \
		fontconfig-devel \
		ffmpeg-devel \
		OpenImageIO-devel \
		libicu-devel \
		OpenEXR-devel \
		libv4l-devel \
		doxygen \
		graphviz"
	# sudo dnf install https://download1.rpmfusion.org/free/fedora/rpmfusion-free-release-$(rpm -E %fedora).noarch.rpm https://download1.rpmfusion.org/nonfree/fedora/rpmfusion-nonfree-release-$(rpm -E %fedora).noarch.rpm
	dnf install ${PACKAGES}
	;;
    "Arch Linux")
	PACKAGES="cmake \
                vulkan-headers \
                openimageio"
	pacman -Syu ${PACKAGES}
        echo "You may need to install one of vulkan drivers for your graphic card: vulkan-intel vulkan-nvidia vulkan-radeon."
	;;
    *)
	echo "Unsupported Linux distribution!"
	exit 2
	;;
esac

# Recommended to install ccache.
