#!/bin/bash

mkdir build && cd build

../configure --with-pkgversion="Debian 1:6.2+dfsg-2ubuntu6.6" --extra-cflags="-g -O2 -ffile-prefix-map=/home/me/virtio-gl/qemu=. -flto=auto -ffat-lto-objects -flto=auto -ffat-lto-objects -fstack-protector-strong -Wformat -Werror=format-security -Wdate-time -D_FORTIFY_SOURCE=2" --extra-ldflags="-Wl,-Bsymbolic-functions -flto=auto -ffat-lto-objects -flto=auto -Wl,-z,relro -Wl,--as-needed" --prefix=/usr --sysconfdir=/etc --libdir=/usr/lib/x86_64-linux-gnu --libexecdir=/usr/lib/qemu --firmwarepath=/usr/share/qemu:/usr/share/seabios:/usr/lib/ipxe/qemu --localstatedir=/var --disable-install-blobs --disable-strip --interp-prefix=/etc/qemu-binfmt/%M --localstatedir=/var --with-git-submodules=ignore \
	--disable-user \
        --enable-system \
        --disable-linux-user \
        --disable-xen \
        --enable-modules \
        --enable-module-upgrades \
        --disable-tcg   \
        --enable-linux-aio --audio-drv-list=pa,alsa,jack,oss,sdl --enable-attr --enable-brlapi --enable-virtfs --enable-cap-ng --enable-curl --enable-fuse --enable-gnutls --enable-gtk --enable-vte --enable-libiscsi --enable-curses --enable-virglrenderer --enable-opengl --enable-smartcard --enable-vnc-sasl --enable-sdl --enable-slirp=system --enable-spice --enable-rdma --enable-linux-io-uring --enable-libusb --enable-usb-redir --enable-libssh --enable-zstd --enable-nettle --enable-xfsctl --enable-libudev --enable-vnc --enable-vnc-jpeg --enable-vnc-png --enable-libpmem --enable-kvm --enable-vhost-net
