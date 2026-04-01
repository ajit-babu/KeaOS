#!/bin/bash
# Run this script once. It installs the cross-compiler to ~/opt/cross
export PREFIX="$HOME/opt/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"

# Download sources
mkdir -p ~/src && cd ~/src
wget https://ftp.gnu.org/gnu/binutils/binutils-2.40.tar.gz
wget https://ftp.gnu.org/gnu/gcc/gcc-13.2.0/gcc-13.2.0.tar.gz
tar xf binutils-2.40.tar.gz
tar xf gcc-13.2.0.tar.gz

# Build binutils (linker + assembler for target)
mkdir build-binutils && cd build-binutils
../binutils-2.40/configure --target=$TARGET --prefix="$PREFIX" \
  --with-sysroot --disable-nls --disable-werror
make && make install && cd ..

# Build GCC (C compiler for target)
mkdir build-gcc && cd build-gcc
../gcc-13.2.0/configure --target=$TARGET --prefix="$PREFIX" \
  --disable-nls --enable-languages=c --without-headers
make all-gcc && make all-target-libgcc
make install-gcc && make install-target-libgcc

echo "Done! Add to PATH:"
echo 'export PATH="$HOME/opt/cross/bin:$PATH"'
