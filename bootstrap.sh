#!/usr/bin/env bash
set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
THIRD_PARTY_DIR="${REPO_ROOT}/third_party"

mkdir -p "$THIRD_PARTY_DIR"

IMGUI_VERSION="v1.92.0"

info() { printf "\033[1;36m==>\033[0m %s\n" "$*"; }
success() { printf "\033[1;32m==>\033[0m %s\n" "$*"; }
error() { printf "\033[1;31m==>\033[0m %s\n" "$*" >&2; }

if [[ ! -f /etc/os-release ]]; then
	error "Unsupported Linux distribution."
	exit 1
fi

source /etc/os-release

DISTRO="$ID"

TOOLS_DIR="${REPO_ROOT}/.tools"
VCPKG_DIR="${TOOLS_DIR}/vcpkg"

mkdir -p "$TOOLS_DIR"

if [[ ! -d "$VCPKG_DIR" ]]; then
	git clone https://github.com/microsoft/vcpkg.git "$VCPKG_DIR"
fi

install_packages() {
	case "$DISTRO" in

	arch)

		sudo pacman -Sy --needed \
			base-devel \
			perl \
			git \
			cmake \
			ninja \
			pkgconf \
			curl \
			zip \
			unzip \
			tar \
			python \
			autoconf \
			autoconf-archive \
			automake \
			libtool
		;;

	fedora)

		sudo dnf install -y \
			perl \
			git \
			gcc-c++ \
			cmake \
			ninja-build \
			pkgconf-pkg-config \
			curl \
			zip \
			unzip \
			tar \
			python3 \
			autoconf \
			autoconf-archive \
			automake \
			libtool \
			libX11-devel \
			libXext-devel \
			libXcursor-devel \
			libXi-devel \
			libXtst-devel \
			libXfixes-devel \
			libXrandr-devel \
			libXrender-devel \
			libXft-devel \
			wayland-devel \
			libxkbcommon-devel \
			mesa-libEGL-devel \
			ibus-devel \
			dbus-devel
		;;

	ubuntu | debian)

		sudo apt update

		sudo apt install -y \
			build-essential \
			perl \
			git \
			cmake \
			ninja-build \
			pkg-config \
			curl \
			zip \
			unzip \
			tar \
			python3 \
			autoconf \
			autoconf-archive \
			automake \
			libtool
		;;

	opensuse* | opensuse-leap | opensuse-tumbleweed)

		sudo zypper install -y \
			gcc-c++ \
			git \
			cmake \
			ninja \
			pkgconf-pkg-config \
			curl \
			zip \
			unzip \
			tar \
			python3 \
			autoconf \
			automake \
			libtool
		;;

	void)

		sudo xbps-install -Sy \
			base-devel \
			git \
			cmake \
			ninja \
			pkgconf \
			curl \
			zip \
			unzip \
			tar \
			python3 \
			autoconf \
			automake \
			libtool
		;;

	alpine)

		sudo apk add \
			build-base \
			git \
			cmake \
			ninja \
			pkgconf \
			curl \
			zip \
			unzip \
			tar \
			python3 \
			autoconf \
			automake \
			libtool
		;;

	gentoo)

		sudo emerge --ask \
			sys-devel/gcc \
			dev-vcs/git \
			dev-build/cmake \
			dev-build/ninja \
			dev-util/pkgconf \
			net-misc/curl \
			app-arch/zip \
			app-arch/unzip \
			app-alternatives/tar \
			dev-lang/python \
			sys-devel/autoconf \
			sys-devel/automake \
			sys-devel/libtool
		;;

	*)

		error "Unsupported distribution: ${DISTRO}"
		exit 1
		;;

	esac
}
clone_imgui() {

	if [[ ! -d "${THIRD_PARTY_DIR}/imgui/.git" ]]; then

		git clone \
			--depth 1 \
			--branch "${IMGUI_VERSION}" \
			https://github.com/ocornut/imgui.git \
			"${THIRD_PARTY_DIR}/imgui"

	else

		git -C "${THIRD_PARTY_DIR}/imgui" fetch origin "${IMGUI_VERSION}" --depth 1
		git -C "${THIRD_PARTY_DIR}/imgui" checkout "${IMGUI_VERSION}"
		git -C "${THIRD_PARTY_DIR}/imgui" reset --hard FETCH_HEAD

	fi
}

info "Detected ${PRETTY_NAME}"

info "Installing development packages..."
install_packages
"$VCPKG_DIR/bootstrap-vcpkg.sh"
.tools/vcpkg/vcpkg install \
	--triplet=x64-linux \
	--x-manifest-root="$REPO_ROOT"
info "Updating Dear ImGui..."
clone_imgui

echo
echo "============================================================"
echo "Bootstrap Complete"
echo "============================================================"
echo
echo "Distribution : ${PRETTY_NAME}"
echo "ImGui        : ${IMGUI_VERSION}"
echo
echo "Next:"
echo
echo "    ./build.sh"
