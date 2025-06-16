#!/bin/sh
export STAGING_DIR=~/proj/openwrt-rtl8198d/staging_dir/toolchain-mips_4kec_gcc-14.3.0_musl
export GCC=${STAGING_DIR}/bin/mips-openwrt-linux-gcc
export LD=${STAGING_DIR}/bin/mips-openwrt-linux-ld
make $*
