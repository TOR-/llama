#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/llama.kernel isodir/boot/llama.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "llama" {
	multiboot /boot/llama.kernel
}
EOF
grub-mkrescue -o llama.iso isodir
