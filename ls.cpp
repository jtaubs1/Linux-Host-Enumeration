#include <unistd.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <pwd.h>
#include <filesystem>

using namespace std;


//Function for Title color
void title_color(){
    std::system("Color 7C");

}
    //Function for output text
void output_color(){
    std::system("Color 7");

}

int main()
{


    // Basic Checks Situational Awareness
    //title_color();
    std::cout << "Current Date Time:" << std::endl;
    //output_color();
    std::system("date\n");
    std::cout << "Current User Context:" << std::endl;
    std::system("whoami\n");
    std::cout << "User id:" << std::endl;
    std::system("id\n");
    std::cout << "Enum Groups" << std::endl;
    std::system("groups\n");
    std::cout << "Present Working Directory Listing:" << std::endl;
    std::system("ls -la\n"); 
    std::cout << "Currently Logged In Users:" << std::endl;
    std::system("w\n");
    std::cout << "Operating System Detection:" << std::endl;
    std::system("cat /etc/issue\n");
    std::cout << "Kernel Version:" << std::endl;
    std::system("uname -r");
    std::cout << "Checking for unmounted filesystems:" << std::endl;
    std::system("cat /etc/fstab | grep '^[^#]'\n");
    std::cout << "Checking for Removed or Deleted executables running in Memory" << std::endl;
    std::system("cat /proc/[0-9]*/exe 2>/dev/null | grep 'deleted|removed|dev|tmp|run'\n");
    std::cout << "Checking for named pipes" << std::endl;
    std::system("find / -type p 2>/dev/null");
    std::cout << "Checking for Docker:" << std::endl;
    std::system("docker version --format '{{.Server.Version}}'\n");
    std::cout << "Ensure you are not in a chroot jail:" << std::endl;
    std::system("ps -elf | head -n2\n");
    std::cout << "Key Users:" << std::endl;
    std::system("cat /etc/passwd | grep -v '/nologin' | grep -v '/false' | grep -v '/sync'\n");
    std::cout << "Checking status of SELinux:" << std::endl;
    std::system("cat /etc/sysconfig/selinux | grep 'SELINUX='\n");
    std::cout << "Process List:" << std::endl;
    std::system("ps -elf\n");
    std::cout << "Connections:" << std::endl;
    std::system("ss -n -t -a -u -a\n");
    std::cout << "ARP:" << std::endl;
    std::system("arp -a\n");
   
    // Check for root permissions, should be obvious by now, but users are dumb
    std::cout << "Root Check:" << std::endl; 
    
    int check_root = getuid();
    int check_eid = geteuid();    
    
    if (check_root == 0){
        std::cout << "Your uid is root" << std::endl;
        ///////////////////////////////////////////////////////////////////////
        //Make our directory 
        std::cout << "Creating directory /dev/shm/containerd" << std::endl;
        std::system("mkdir /dev/shm/containerd");
        //run mkfinds here
        std::cout << "Finding files modified in the last 5 minutes" << std::endl;
        std::system("find / -type f -mmin 5 2>/dev/null\n");

        //start of logging copy 
        std::cout << "Copy auth.log, syslog, wtmp, btmp, kern.log to new directory" << std::endl;
        std::filesystem::copy("/var/log/auth.log", "/dev/shm/containerd/auth.log");
        std::filesystem::copy("/var/log/syslog", "/dev/shm/containerd/syslog");
        std::filesystem::copy("/var/log/wtmp", "/dev/shm/containerd/wtmp");
        std::filesystem::copy("/var/log/btmp", "/dev/shm/containerd/btmp");
        //Depends on the distro 
        //std::filesystem::copy("/var/log/utmp", "/dev/shm/containerd/utmp");
        std::filesystem::copy("/var/log/kern.log", "/dev/shm/containerd/kern.log"); 
        std::cout << "tar'ed all logs for exfil" << std::endl;
        std::system("cd /dev/shm/containerd\n");
        std::system("tar -cvzpf logs.tar /dev/shm/containerd");
        
    } else { 
	    std::cout << "You are not the root user\n" << std::endl;

    }	
    
    if (check_eid == 0){
	std::cout << "Your euid is root\n" << std::endl;
    } else {
	    std::cout << "Your euid is not root\n" << std::endl;
    }
    
    /////////////////////////////////////////////////////////////////////////
    //Permission Check on Passwd Shadow
    std::cout << "Permissions for passwd and shadow file:" << std::endl;;
    std::system("ls -la /etc/passwd\n");
    std::system("ls -la /etc/shadow\n");
    /////////////////////////////////////////////////////////////////////////
    
   
    //////////////////////////////////////////////////////////////////////
    //Userful Software find
    std::cout << "Finding useful software:" << std::endl;
    std::system("which nc\n");
    std::system("which netcat\n");
    std::system("which nmap\n");
    std::system("which tcpdump\n");
    std::system("which gdb\n");
    std::system("which g++\n");
    std::system("which gcc\n");
    std::system("which python\n");
    std::system("which python3\n");
    
    //suid binaries 
    std::cout << "Finding SUID binaries" << std::endl;
    std::system("find / -type f -perm -u=s 2>/dev/null\n");
    
    //Capabilities check 
    std::cout << "Checking files with capabilities:" << std::endl;
    std::system("getcap -r / 2>/dev/null\n");

    //root squash
    std::cout << "Checking for root squashing:" << std::endl;
    std::system("cat /etc/exports\n");

    //////////////////////////////////////////////////////////////////////
    //Start of makedirs
    std::cout << "Dir of /:" << std::endl;
    std::cout << "Dir of Web Root:" << std::endl;
    std::system("ls -la /var/www/html\n");
    std::cout << "Dir of /tmp:" << std::endl;
    std::system("ls -la /tmp\n");
    std::cout << "Dir of /dev/shm:" << std::endl;
    std::system("ls -la /dev/shm\n");
    std::cout << "Dir of /root:" << std::endl;
    std::system("ls -la /root\n");
    std::cout << "Dir of /home" << std::endl;
    std::system("ls -la /home\n");

    ////////////////////////////////////////////////////////////////////
    //Start of Key File Hunting 
    std::cout << "Searching for password files regex" << std::endl;
    std::system("find / -type f -iname 'password.*' 2>/dev/null | grep -v /usr/share | grep -v python\n");
    std::system("find / -type f -name 'passwords.*' 2>/dev/null | grep -v /usr/share | grep -v python\n");
    
    //.ssh key searching 
    std::cout << "Searching for ssh key files/ssh directories:" << std::endl;
    std::system("find / -type f -iname 'id_rsa' 2>/dev/null\n");
    std::system("find / -type d -name '.ssh' 2>/dev/null\n");

    //.pem file searching 
    std::cout << "Searching for pem files:" << std::endl;
    std::system("find / -type f -iname '*.pem' 2>/dev/null | grep -v gems | grep -v python | grep -v python3 | grep -v '/usr/share' | grep -v '/var/lib/docker'\n");
    
    ///////////////////////////////////////////////////////////////////
    //Start of backup hunting 
    std::cout << "Searching for backup files" << std::endl;
    std::system("find / -type f -iname '*.bak' 2>/dev/null | grep -v README | grep -v '/var/lib/docker'\n");



    //history files viminfo tar for exfil 
    std::cout << "Finding key history files:" << std::endl;
    std::system("find / -type f -iname '*_history' 2>/dev/null | grep -v '/usr/share'\n");
    std::system("find / -type f -name '.viminfo' 2>/dev/null\n");
    std::system("find / -type f -name 'search_history' 2>/dev/null\n");






/*
    // Pause 
    std::cout<< "Execution Pausing, Press ENTER to Continue...\n" << std::endl;
    cin.get();
*/  
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    return 0; 
}


