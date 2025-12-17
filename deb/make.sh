#!/usr/bin/env bash
set -e

PKG_NAME="libmodernc-dev"
VERSION="${1:-0.1}"
ARCH="amd64"
MAINTAINER="nekogakure <info@mail.nekogakure.jp>"
DESC_SHORT="modern C utility library"
DESC_LONG=" library for modern and easy use of the C language"
LIB_NAME="libmodernC.a"

ROOT="${PKG_NAME}_${VERSION}_${ARCH}"
DEBIAN_DIR="$ROOT/DEBIAN"
INCLUDE_DIR="$ROOT/usr/include/modernc"
LIB_DIR="$ROOT/usr/lib"
PKGCONFIG_DIR="$ROOT/usr/lib/pkgconfig"

rm -rf "$ROOT"
mkdir -p "$DEBIAN_DIR" "$INCLUDE_DIR" "$LIB_DIR" "$PKGCONFIG_DIR"

cat > "$DEBIAN_DIR/control" <<EOF
Package: $PKG_NAME
Version: $VERSION
Section: libdevel
Priority: optional
Architecture: $ARCH
Maintainer: $MAINTAINER
Description: $DESC_SHORT
 $DESC_LONG
EOF

# Find the built static library in common locations relative to this script.
# This makes running the script from deb/ convenient: it will search ../cmake-build-debug, ../, etc.
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
# Candidate paths to check (relative to script dir)
CANDIDATES=(
    "$SCRIPT_DIR/../$LIB_NAME"
    "$SCRIPT_DIR/../cmake-build-debug/$LIB_NAME"
    "$SCRIPT_DIR/../build/$LIB_NAME"
    "$SCRIPT_DIR/../cmake-build-debug/Debug/$LIB_NAME"
    "$SCRIPT_DIR/../lib/$LIB_NAME"
    "$SCRIPT_DIR/$LIB_NAME"
    # also check lowercase variant (common)
    "$SCRIPT_DIR/../libmodernc.a"
    "$SCRIPT_DIR/../cmake-build-debug/libmodernc.a"
)
LIB_PATH=""
for p in "${CANDIDATES[@]}"; do
    if [ -f "$p" ]; then
        LIB_PATH="$p"
        break
    fi
done

# Fallback: try a wider search one level up if not found yet
if [ -z "$LIB_PATH" ]; then
    found=$(find "$SCRIPT_DIR/.." -maxdepth 4 -type f -name "libmodern*.a" 2>/dev/null | head -n1 || true)
    if [ -n "$found" ]; then
        LIB_PATH="$found"
    fi
fi

if [ -z "$LIB_PATH" ]; then
    echo "Error: cannot find $LIB_NAME. Tried common locations."
    echo "Please build the library first (e.g. run cmake/make in project root)," \
         "or provide the library next to this script. Searched locations:" >&2
    for p in "${CANDIDATES[@]}"; do
        echo "  - $p" >&2
    done
    echo "  - and recursive search under: $SCRIPT_DIR/.. (depth 4)" >&2
    exit 1
fi

cp "$SCRIPT_DIR/../include"/*.h "$INCLUDE_DIR/"
cp "$LIB_PATH" "$LIB_DIR/"
LIB_FILE_NAME="$(basename "$LIB_PATH")"
PC_LIB_NAME=""
if [[ "$LIB_FILE_NAME" =~ ^lib(.+)\.a$ ]]; then
    PC_LIB_NAME="${BASH_REMATCH[1]}"
else
    PC_LIB_NAME="${LIB_FILE_NAME#lib}"
    PC_LIB_NAME="${PC_LIB_NAME%.a}"
fi

cat > "$PKGCONFIG_DIR/modernc.pc" <<EOF
prefix=/usr
libdir=\${prefix}/lib
includedir=\${prefix}/include

Name: modernc
Description: modern C library
Version: $VERSION
Libs: -L\${libdir} -l$PC_LIB_NAME
Cflags: -I\${includedir}/modernc
EOF

chmod 755 "$DEBIAN_DIR"

dpkg-deb --build "$ROOT"

echo "DONE: ${ROOT}.deb"