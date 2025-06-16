#!/bin/sh
export STAGING_DIR=~/proj/openwrt-rtl8198d/staging_dir/toolchain-mips_4kec_gcc-14.3.0_musl
~/proj/openwrt-rtl8198d/staging_dir/toolchain-mips_4kec_gcc-14.3.0_musl/bin/mips-openwrt-linux-musl-ld $*
