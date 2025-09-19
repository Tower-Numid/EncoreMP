#!/bin/sh -ex
echo -n | openssl s_client -connect scan.coverity.com:443 | sed -ne '/-BEGIN CERTIFICATE-/,/-END CERTIFICATE-/p' | sudo tee -a /etc/ssl/certs/ca-

# Set up compilers
if [ ! -z "${MATRIX_CC}" ]; then
    eval "${MATRIX_CC}"
fi

cd ~/
git clone https://github.com/TES3MP/CrabNet
cd CrabNet
cmake . -DCRABNET_ENABLE_DLL=OFF -DCRABNET_ENABLE_SAMPLES=OFF -DCMAKE_BUILD_TYPE=Release
make -j3
