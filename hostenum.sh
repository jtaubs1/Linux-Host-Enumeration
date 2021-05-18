#!/bin/bash
echo "
  _____             __          __  _ 
 |_   _|            \ \        / / | |
   | |  ___ ___ _____\ \  /\  / /__| |
   | | / __/ _ \______\ \/  \/ /_  / |
  _| || (_|  __/       \  /\  / / /| |
 |_____\___\___|        \/  \/ /___|_|"

#banner function
banner()
{
  echo "+------------------------------------------+"
  printf "|`tput bold` %-40s `tput sgr0`|\n" "$@"
  echo "+------------------------------------------+"
}

#define options
options=("1" "2" "3")

#welcome
echo "++++++++++++++++Welcome++++++++++++++++"
#disclaimer
echo "Please use responsibly, and be good boys and girls."

#display options
echo "[+] Enter "1" to netcat scan the subnet."
echo "[+] Enter "2" to perform host enumeration."
echo "[+] Enter "3" to perform a subnet ping sweep."
echo "[+] Enter "4" to exit."

#menu options
echo "Please choose your option: "
#read user input
read options

#start of case statement
case "$options" in
#start of option 1 code.
    1)
        echo "Enter the network addrerss (first 3 octets)(ex. xxx.xxx.xxx): "
        read net

        echo "Enter the starting ip address (ex. 1): "
        read start

        echo "Enter the ending ip address (ex. 255): "
        read end

        echo "enter the ports you wish to scan (ex. 20-25 80): "
        read port

        for ((i=$start; $i <=$end; i++))
            do
                nc -nvzw1 $net.$i $port 2>&1 | grep open
                echo $net.$i "Scan complete"
        done
        ;;
#end of option 1 code

#start of option 2 code
#check to see if there is an /etc/passwd file
    2)
        banner "Finding basic system information."
        echo "Username...$(whoami)"
        echo "Hostname...$(hostname)"
        echo "Operating system...$(cat /etc/issue)"
        echo "Kernel Version...$(uname -r)"

        banner "Checking to see what users are logged in."
        echo "Users...$(who)"

#check to see if /etc/passwd is readable
        if [ -s /etc/passwd ]
        then
        echo "/etc/passwd file is readable."
        else
        echo "/etc/passwd file is not readable."
        fi
#check to see if /etc/shadow is writable
        if [ -w /etc/passwd ]
        then
        echo "/etc/passwd is writable."
        else
        echo "/etc/passwd is not writable."
        fi
#check to see if shadow is readable
        if [ -s /etc/shadow ]
        then
        echo "/etc/shadow file is readable."
        else
        echo "/etc/shadow file is not readable."
        fi
#check to see if the shadow is writable
        if [ -w /etc/shadow ]
        then
        echo "/etc/shadow is writable."
        else
        echo "/etc/shadow is not writable."
        fi

        banner "Useful pen test tools"
#see if common pen test tools are installed
        whereis netcat
        whereis nmap
        whereis tcpdump
        whereis nikto
        whereis wireshark
        whereis gbd
        whereis g++
        whereis gcc
        python -V
        php -v | awk 'NR==1{print $1, $2}'

        banner "Finding connected hosts"
#find connected hosts
        arp -a

        banner "Finding ip address info"
        ip addr

        banner "Finding active connections"
        netstat -antup

        banner "Finding services running as root"
        ps aux | grep root

        banner "Checking for unmounted file systems"
        cat /etc/fstab

        banner "Finding exploitable binaries use GTFObins"
#find potentially exploitable binaries use GTFObins
        find / -type f -perm /6000 -ls 2>/dev/null

        banner "Looking for files called pass*"
#find / -type f -iname "pass*" 2>/dev/null
#find /usr/share -type f -iname "pass*" 2>/dev/null
        find /home -type f -iname "pass*" 2>/dev/null
        find /tmp -type f -iname "pass*" 2>/dev/null
        find /etc -type f -iname "pass*" 2>/dev/null
        find /root -type f -iname "pass*" 2>/dev/null
        ;;
#start of option 3 ping sweep
    3)
        echo "Enter the first three network octects."
        echo "Example: 192.168.0"
        read address
        for x in `seq 1 254`;
        do
            ping -c 1 -w 1 $address.$x | grep "64 bytes" | cut -d " " -f4 | sed 's/.$//'
        done
        ;;
#start of option 4 quit
    4)
        exit 1
        ;;

esac
exit 0

