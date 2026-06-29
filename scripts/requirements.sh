#!/bin/bash

set -e  # Stoppe le script si une commande échoue

echo "Mise à jour des paquets..."
apt update
apt upgrade -y

echo "Installation des outils de développement..."
apt install -y \
    gcc \
    g++ \
    build-essential \
    nasm \
    make \
    git \
    vim \
    gdb \
    hexedit

echo "Installation des outils GRUB..."
apt install -y \
    grub2-common \
    grub-pc-bin \
    grub-common \
    grub-efi-amd64-bin \
    xorriso \
    mtools

echo "Installation de l'émulateur..."
apt install -y \
    qemu-system-x86 \
    qemu-system-data

echo "Vérification des installations..."
gcc --version | head -1
nasm --version
qemu-system-i386 --version | head -1
grub-mkrescue --version | head -1

echo "✅ Tout est installé !"