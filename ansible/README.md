# Description
This document describes the manual steps that must be applied to a Raspberry Pi in preparation for Ansible execution.  At the end of this procedure, the Pi will be: 
* Authenticated onto your home wifi.
* Accessible via Secure Shell (SSH), so no monitor or keyboard will be necessary after initial configuration.
* Updated and upgraded.
* Ready for Ansible configuration.

## Install Operating System
This section describes how to install the operating system (OS) onto a 32 GB SD card.  In this case, the OS that I installed onto my Raspberry Pi 3 and 4 fleet is Ubuntu Server 22.04 LTS, available [here](https://ubuntu.com/download/raspberry-pi).  There are good general instructions to do [here](https://ubuntu.com/tutorials/how-to-install-ubuntu-on-your-raspberry-pi#1-overview); the instructions that follow are my specific steps.

1.  On a Mac, install Balena Etcher.
2.  Download the OS image from the above link.
3.  Follow the Balena Etcher UI to flash the OS onto an SD card.
4.  Once the flash process is complete, eject the SD card.
    
## Configure Wifi
This section describes how to edit the network configuration using your Mac.  It involves simply removing some comments from a YAML file, and addition of your wifi network name and password.

1.  Insert the SD card into the adapter used for the flash process.  A drive named `system-boot` appears on the desktop.
2.  Open the Finder app on the Mac.
3.  In the Finder left column, in the Locations section, click on the `system-boot` icon.
4.  Scroll to find the `network-config` file, and open it using the Mac TextEdit app.
5.  Find the commented-out lines that start with `wifis:`. Starting with that line, remove the comments down to but not including the `myworkwifi:` line.
6.  Under the `access-points:` section, define the name of your home wifi network, and beneath it, the password.  This is YAML, so put quotes around your network name if it contains anything but string characters.
7.  Check alignment with the `ethernets` section to make YAML correct.
8.  On the `system-boot` icon, click on the up arrow to eject the drive.
9.  Insert the SD card into the slot on your Pi.
10. Connect a monitor to the Pi.
11. Connect a keyboard to the Pi.
12. Connect power to the Pi.  We're going in!


## Logon to Your Pi
At the `ubuntu login` enter the default Unbuntu login and password, both of which are: ubuntu

You will be forced to change the user ubuntu password, so have a decent password ready.  For extra credit, find a way to remember it a year from now.

# Get the Device Internet Protocol (IP) and Media Access Control (MAC) addresses
In this section, we install net-tools.  This installs the `ifconfig` utility, which is used to get the IP and MAC addresses.

1.  Execute:    sudo apt install net-tools
2.  Execute:    ifconfig

In the wlan0 output: 
* Record the IP address.  It is adjacent to the `inet` field and looks like this:  192.168.1.122
* Record the MAC address.  It is adjacent to the `ether` field and looks like this:  dc:a6:32:e5:64:2d


## Create Alternate User
In this section, we create another user to use for SSH access.  This user should be setup on your SSH client ("ssh client" is your Mac, Chromebook, whatever) with an SSH key.  We also add this user to the `sudo` group

1.  At the Pi prompt, create the user (in this case, rod):  sudo adduser rod
2.  Enter the new user's password.  For extra credit, record it somewhere. 
3.  Add the new user to the sudo group: usermod -aG sudo rod

## Make Alternate User Sudo (With No Password Required)
This step enables the new user to use `sudo` with specification of a password.

1.  Execute:  sudo visudo /etc/sudoers
    1.  This opens a nano editor session.
2.  At the bottom of this file, add this line:  rod ALL=(ALL) NOPASSWD:ALL
3.  Follow instructions to write out the file.
4.  Follow instructions to exit the editor.

## Copy an SSH Public Key to the Pi  
This step assumes that you have established an ssh key pair.  In this step, the public key is copied to the device to enable SSH login.  You will need the IP address of the Pi recorded above.

1.  On you laptop, execute:    ssh-copy-id -i ~/.ssh/id_rsa rod@192.168.1.122
2.  Respond `yes` to confirm that you want to connect.
3.  Respond with the user's password (not the password for user `ubuntu`)
4.  Follow the instruction given to login to the machine.

## Verify that the SSH Service Starts Upon Reboot
This command shows indicates the status of the ssh service on the Pi.

1.  Execute:  sudo systemctl status ssh
2.  In the Loaded line, verify that the `ssh.service` is `enabled`.


## Update and Upgrade
These steps pull the latest versions of installed software:
1.  Execute: sud apt update
    1.  This step identifies packages that can be upgraded.
2.  Execute: sudo apt upgrade -y
    * This can take a while, so go get lunch.
   
## Add Pi to Ansible hosts
This step adds information that you collected to your Ansible hosts file.  This allows it to be configured by Ansible, and allows ad-hoc fleet-wide commands to be executed.  

1.  Decide on a host name for this Pi.  For this example, it will be `server03`.
2.  In file ansible/host/dev/hosts, add a row that specifies the IP, host name, and MAC address under the raspi group:
    192.168.1.122 hostname=server03 mac=dc:a6:32:e5:64:2d

## Enable easy SSH Connection by Host Name  
This step will enable ssh connection by only specification of the host name, i.e., `ssh server03`.

In file ~/.ssh/config, add a section for the Pi:

```
Host server03
HostName 192.168.1.122
User rod
IdentityFile ~/.ssh/id_rsa
```

Upon completion, test:  ssh server03

To close the SSH session:  exit

Useful hint:  You can run a command on a host simply by including it as a quoted string in an ssh command line.  Example:

```
$ ssh server03 'df -h'
Filesystem      Size  Used Avail Use% Mounted on
tmpfs           781M  3.1M  778M   1% /run
/dev/mmcblk0p2  117G  2.9G  110G   3% /
tmpfs           3.9G     0  3.9G   0% /dev/shm
tmpfs           5.0M     0  5.0M   0% /run/lock
/dev/mmcblk0p1  253M  149M  104M  60% /boot/firmware
tmpfs           781M  4.0K  781M   1% /run/user/1001
```

## Add Raspberry Pi to DHCP Reservations
DHCP is Dynamic Host Configuration Protocol, and it is the service on your network that assigns IP addresses.  IP addresses are assigned by DHCP leases, meaning that an IP address is assigned with a termination time, on the order of 24 hours.  Typically, DHCP leases are automatically renewed, so your device will retain the same IP address over time.  However, if there is an extended power failure, or if you power down the fleet while you go on an extended vacation, you could come back to alphabet soup, in which you cannot access your devices because all the IP addresses have changed.

Some routers allow DHCP Reservations. These reservations enable perpetual IP addresses. 

To configure a reserved address on DHCP (on my router, these are the steps, your may be different):
* Logon to the router at 192.168.1.1.
* Select Connectivity > Local Network > DHCP Reservations
* Find the device MAC address in the list of assigned addresses.
* Click Select
* Click `Add DHCP Reservation` (it's at the bottom of the page)
* Specify the host name as the Device Name. Consider adding a `-wifi` or `-lan` suffix as appropriate.
* Click Save.
* Click OK (at the bottom).  The configuration will take maybe a minute.
* Verify that the device has a Reserved Address.
