#!/bin/sh
set -e
. ./iso.sh

qemu-system-$(./target-triplet-to-arch.sh $HOST) -d int,in_asm -cdrom llama.iso #-monitor stdio
