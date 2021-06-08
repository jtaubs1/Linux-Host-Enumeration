# Bash Host Enumeration
- This script is designed to enumerate a host and identify possible privlage escalation vectors or system misconfiguration.
- It also has options to enumerate through a subnet and find other connected devices.
### Installation
`git clone https://github.com/jtaubs1/bash-host-enum.git`
- Clone the repo.
`cd bash-host-enum`
- CD into the repo.
`chmod +x hostenum.sh`
- Change to allow execution.
`./hostenum.sh`
- Run the script.

#### New Update
- Added in ability to find ssh keys
- Added writeable check on /etc/sudoers
- Added better suid sgid checks
- Check for no_root_squashing
