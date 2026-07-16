#!/usr/bin/env bash
set -euo pipefail

REPO_ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
THIRD_PARTY_DIR="${REPO_ROOT}/third_party"

mkdir -p "$THIRD_PARTY_DIR"

IMGUI_VERSION="v1.92.0"


info()    { printf "\033[1;36m==>\033[0m %s\n" "$*"; }
success() { printf "\033[1;32m==>\033[0m %s\n" "$*"; }
error()   { printf "\033[1;31m==>\033[0m %s\n" "$*" >&2; }


if [[ ! -f /etc/os-release ]]; then
    error "Unsupported Linux distribution."
    exit 1
fi

source /etc/os-release

DISTRO="$ID"


install_packages() {

    case "$DISTRO" in

        arch)

            sudo pacman -Sy --needed \
                base-devel \
                git \
                cmake \
                ninja \
                sdl3 \
                sdl3_image \
                sdl3_ttf
            ;;

        fedora)

            sudo dnf install -y \
                gcc-c++ \
                git \
                cmake \
                ninja-build \
                SDL3-devel \
                SDL3_image-devel \
                SDL3_ttf-devel
            ;;

        ubuntu|debian)

            sudo apt update

            sudo apt install -y \
                build-essential \
                git \
                cmake \
                ninja-build \
                libsdl3-dev \
                libsdl3-image-dev \
                libsdl3-ttf-dev
            ;;

        opensuse*)

            sudo zypper install -y \
                gcc-c++ \
                git \
                cmake \
                ninja \
                SDL3-devel \
                SDL3_image-devel \
                SDL3_ttf-devel
            ;;

        void)

            sudo xbps-install -Sy \
                git \
                cmake \
                ninja \
                SDL3-devel \
                SDL3_image-devel \
                SDL3_ttf-devel
            ;;

        alpine)

            sudo apk add \
                build-base \
                git \
                cmake \
                ninja \
                sdl3-dev \
                sdl3-image-dev \
                sdl3-ttf-dev
            ;;

        gentoo)

            sudo emerge \
                dev-build/cmake \
                dev-vcs/git \
                dev-build/ninja \
                media-libs/libsdl3 \
                media-libs/sdl3-image \
                media-libs/sdl3-ttf
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
