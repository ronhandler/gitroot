#!/usr/bin/perl

# Check that the script is run as root.
my $id = `id -u`;
if ($id != 0) {
	print("The script must be run as root. Exiting.\n");
	exit 1;
}

# Shutting down some services.
print("Trying to remount /dev/sda1 as read-only...\n");
system("service rsyslog stop");
system("service network-manager stop");
system("killall dhclient");

# Trying to remount the partition.
system("mount -n -o remount,ro -t ext3 /dev/sda1 /");
if ($? eq '0') {
	print("Success.\n");
} else {
	print("Failed to remount. Exiting.\n");
	exit 2;
}

# Executing the shrinking command, zerfree.
print("Running zerofree...\n");
system("zerofree -v /dev/sda1");

# Printing some instructions on how to shrink the vdi.
print("To shrink the vdi, execute the following in Command Prompt:\n");
print('C:\Program Files\Oracle VM VirtualBox>VBoxManage.exe modifyhd "c:\data\Virtual M achines\deb\deb.vdi" --compact');
print("\n");

