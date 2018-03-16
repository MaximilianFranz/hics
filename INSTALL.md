# Installation manual for HICS

## Prerequisites

To successfully build the HICS software, the following libraries and frameworks are needed.
Some of the dependencies have been bundled and don't need to be installed explicitly.

* [CMake](https://cmake.org/)
* [Qt 5](https://www.qt.io/)
* [HDF5](https://support.hdfgroup.org/HDF5/)
* [JSON for Modern C++](https://github.com/nlohmann/json) (bundled)
* [spdlog](https://github.com/gabime/spdlog) (bundled)
* [protobuf 3](https://github.com/google/protobuf)
* [GRPC](https://grpc.io/)
* OpenCL / Altera SDK
* C++11 (requires GCC >= 4.9)
* [Catch2](https://github.com/catchorg/Catch2) (bundled)
* [QTest](http://doc.qt.io/qt-5/qtest-overview.html) (part of Qt 5)

## Getting the sources

You can download a release tarball from the [GitHub release page](https://github.com/hics-project/hics/releases). The tarballs named
hics-$(ver).tar.gz include the AlexNet weights file which is needed for the
software to function properly.

The alternative is to use git and clone the repository:

    # git clone https://github.com/hics-project/hics.git

As the weights file is rather large, GitHubs bandwith limitations forced us to
exclude the file from the repository, so it was moved into a git submodule
which is hosted on a different server.
To get the weights file via the git submodule, run:

    # cd hics
    # git submodule init
    # git submodule update

This will pull the file `resources/weights/alexnet_weights.h5`.

## PC / Ubuntu 16.04 LTS

Our main target on the PC is Ubuntu 16.04 LTS. It provides all required libraries
with two notable exceptions: protobuf and grpc. Both versions as provided by
Ubuntu 16.04 are too old, in addition the grpc package is affected by two major bugs,
which made it unusable:
- https://bugs.launchpad.net/ubuntu/+source/grpc/+bug/1748586
- https://bugs.launchpad.net/ubuntu/+source/grpc/+bug/1727528

We thus provide fixed backports in a separate repository. To enable that repository run the following command:

    # apt-add-repository ppa:mbiebl/hics

Hopefully, in future versions of Ubuntu, those packages are fixed, so this separate repository is no longer needed.

### Installing the build dependencies

After those preparatory steps, the build dependencies can be installed via:

    # apt-get update
    # apt-get install cmake qtbase5-dev libprotobuf-dev protobuf-compiler libgrpc-dev libgrpc++-dev protobuf-compiler-grpc libhdf5-dev ocl-icd-opencl-dev build-essential --no-install-recommends

### Compiling and installing hics

Now, we go on compiling and installing the software. Assuming you already have the sources, we create a build directory inside the source directory, then run the configure, make and make install steps like this:

    # mkdir build
    # cd build
    # cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_INSTALL_SYSCONFDIR=/etc -DINSTALL=ON
    # make
    # sudo make install

This will make an optimized release build which is suitable for being installed system-wide. It will install the binaries to `/usr/bin` and the resource files to `/etc/hics`. In addition, it provides a desktop menu entry, so hics can be started directly from your desktop launcher. Alternatively it can be started from the command line via the `hics` command.

If you want to run hics directly from the build directory, remove the `-DINSTALL=ON` cmake flag.

### Configuration

Please keep in mind that hics needs be configured first, before it can be run system-wide. You will need to setup `/etc/hics/platforms.json` and `/etc/hics/computationHosts.json` describing the details of your hardware setup. Please see [CONFIGURE](CONFIGURE.md) for more details.
We also ship example files which you can use as a template for your own configuration.


## FPGA / Altera de1soc board

Getting the software to run on the Atera de1soc FPGA board, requires a few more steps. To build the host program, we will use an armhf chroot and qemu emulation on the Ubuntu PC.
We will also have to compile the OpenCL kernel. For that we use `aoc` from the Intel FPGA SDK.
Finally, we will setup another chroot on the board to run the `hics-server` binary.
To make it clearer where a command is executed, we will introduce the following prefixes:

    ubuntu# <command is executed on the Ubuntu PC>
    chroot# <command is executed in the armhf chroot>
    board# <command is executed the remote FPGA board>

For the purpose of this document we assume that the remote FPGA board is accessible via SSH under the name `board`.


### Preparing the armhf chroot

In our first step, we will create a barebones Debian buster armhf chroot on the Ubuntu PC. We chose Debian buster, as it provides solid support for armhf and provides all the necessary libraries which we need to compile the software.
We will create the chroot under `/srv/chroot/buster-armhf` with the following commands:

    ubuntu# sudo apt-get install qemu binfmt-support qemu-user-static debootstrap
    ubuntu# sudo debootstrap --arch=armhf --foreign buster /srv/chroot/buster-armhf
    ubuntu# sudo cp /usr/bin/qemu-arm-static /srv/chroot/buster-armhf/usr/bin/
    ubuntu# sudo chroot /srv/chroot/buster-armhf /bin/bash /debootstrap/debootstrap --second-stage

We will reuse this minimal chroot on the FPGA board, so let's make a copy at this point. For that we create a tarball:

    ubuntu# cd /srv/chroot
    ubuntu# sudo tar czf buster-armhf.tar.gz buster-armhf

### Setting up the build chroot

We will need the OpenCL library provided by the Intel FPGA SDK inside the build chroot. For the purpose of this document, we assume that the FPGA SDK is installed at `/home/user/intelFPGA/16.1`. We won't go into detail here how to setup the SDK but refer to existing documentation.

The easiest way to make the FPGA SDK available in the chroot is via a bind mount:

    ubuntu# sudo mount -o bind /home/ /srv/chroot/buster-armhf/home/

We now switch into the chroot

    ubuntu# sudo chroot -i /srv/chroot/buster-armhf
    chroot# source /home/user/setup.sh

We assume here, that there is a setup.sh script which set's up the user environment variables, so `aocl` is functional at this point.
In our next step we install the build dependencies:

    chroot# apt-get install cmake qtbase5-dev libprotobuf-dev protobuf-compiler libgrpc-dev libgrpc++-dev protobuf-compiler-grpc libhdf5-dev ocl-icd-opencl-dev build-essential --no-install-recommends


### Compiling and installing hics-server

We are now ready to build build `hics-server`. Assuming you already have the source inside the build chroot (if not, see [how to get the sources](#getting-the-sources))
The build dependencies are the same as for [hics](#installing-the-build-dependencies)

    chroot# apt-get install cmake qtbase5-dev libprotobuf-dev libgrpc-dev libgrpc++-dev protobuf-compiler-grpc libhdf5-dev ocl-icd-opencl-dev build-essential --no-install-recommends

Building the armhf binaries is also very similar to building [hics](#compiling-and-installing-hics), the only difference is that we pass `-DPLATFORM_ALTERA=ON` to cmake:

    chroot# cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_INSTALL_SYSCONFDIR=/etc -DINSTALL=ON -DPLATFORM_ALTERA=ON
    chroot# make
    chroot# make install

We are done in the build chroot, so we `exit` at this point. Our next step is to compile the OpenCL kernel.

### Compiling the OpenCL kernel

We are back as regular user and now proceed with compiling the OpenCL kernel for the FPGA board. Switch to the `resources/kernels` directory inside the hics source, then run the following command:

    ubuntu# aoc gemm4_fpga.cl --board de1soc_sharedonly

This command will take a while and produce `gemm4_fpga.aocx` if successful.

We now have everything compiled and ready. In our next step, we will prepare the runtime environment on the FPGA board.

### Setting up the runtime environment on the de1soc FPGA board

The officially supported distribution on the de1soc board is Ångström Linux 2014, which is rather old and doesn't provide all the necessary libraries we need. We thus use a Debian buster chroot instead.
The Debian buster armhf tarball which we created [earlier](#preparing-the-armhf-chroot) is now transferred to the board via ssh to the /tmp directory and we will unpack it as `/srv/chroot/buster-armhf`:

    chroot# mkdir /srv/chroot
    chroot# cd /srv/chroot
    chroot# tar xf /tmp/buster-armhf.tar.gz

We then make the OpenCL libraries available in the chroot:

    board# cp -a /home/root/opencl_arm32_rte /srv/chroot/buster-armhf/opt/

To make sure the dynamic loader finds those libraries, create a file
`/srv/chroot/buster-armhf/etc/ld.so.conf.d/altera.conf`
containing

     /opt/opencl_arm32_rte/host/arm32/lib

Before we can install the necessary dependencies in the chroot environment we need to setup `/etc/resolv.conf`. We simply copy the one from the host system for that:

     board# cp /etc/resolv.conf /srv/chroot/buster-armhf/etc

We then can finally install the runtime dependencies in the chroot:

    board# chroot /srv/chroot/buster-armhf apt-get install libprotobuf10 libgrpc3 libgrpc++1 libhdf5-100

We return to to Ubuntu system and copy the hics-server binary, the resource files including the gemm4_fpga.aocx kernel to the board

    ubuntu# scp -r /srv/chroot/buster-armhf/etc/hics board:/srv/chroot/buster-armhf/etc
    ubuntu# scp gemm4_fpga.aocx board:/srv/chroot/buster-armhf/etc/hics/kernels/
    ubuntu# scp /srv/chroot/buster-armhf/usr/bin/hics-server board:/srv/chroot/buster-armhf/usr/bin/

### Configuring and running hics-server

At this point we are almost ready to run `hics-server` on the board.
The remaining part is to setup platforms.json and computationHosts.json in `/srv/chroot/buster-armhf/etc/hics`. Once that is done, we can finally start the server:

    board# /usr/bin/systemd-nspawn --register=no --bind=/sys --bind=/dev -D /srv/chroot/buster-armhf /usr/bin/hics-server

To simplify the handling of the hics-server daemon, we will utilize systemd and create a .service file `/etc/systemd/system/hics-server.service`

```
[Unit]
Description=Run HICS server in buster chroot

[Service]
Restart=on-failure
ExecStart=/usr/bin/systemd-nspawn --register=no --bind=/sys --bind=/dev -D /srv/chroot/buster-armhf /usr/bin/hics-s
erver

[Install]
WantedBy=multi-user.target
```

After a `systemctl daemon-reload` we can now easily start the service via `systemctl start hics-server`. Log messages will end up in the journal which you can inspect via `journalctl`. To make sure hics-server is started if the board is rebooted, run `systemctl enable hics-server`.
You can check the current status of the service with

```
board# systemctl status hics-server
● hics-server.service - Run HICS server in buster chroot
   Loaded: loaded (/etc/systemd/system/hics-server.service; enabled; vendor preset: enabled)
   Active: active (running) since Tue 2018-03-13 17:01:56 UTC; 1h 45min ago
 Main PID: 2399 (systemd-nspawn)
   CGroup: /system.slice/hics-server.service
           ├─2399 /usr/bin/systemd-nspawn --register=no --bind=/sys --bind=/dev -D /srv/chroot/buster-armhf /usr/bin/hics-server
           └─2401 /usr/bin/hics-server

Mar 13 17:01:56 socfpga systemd[1]: Started Run HICS server in buster chroot.
Mar 13 17:01:56 socfpga systemd-nspawn[2399]: Spawning container buster-armhf on /srv/chroot/buster-armhf.
Mar 13 17:01:56 socfpga systemd-nspawn[2399]: Press ^] three times within 1s to kill container.
Mar 13 17:01:56 socfpga systemd-nspawn[2399]: I0313 17:01:56.350113845       1 server_builder.cc:247]      Synchronous server. Num CQs: 1, Min pollers: 1, Max Pollers: 2147483647, CQ timeout (msec): 1000
Mar 13 17:01:56 socfpga systemd-nspawn[2399]: Server listening on 0.0.0.0:50051
```
