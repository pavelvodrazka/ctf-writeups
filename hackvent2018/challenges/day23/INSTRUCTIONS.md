# MuffinCTF

Welcome pjslf! :)

I am really happy that you decided to play muffinCTF.  
First off read the rules, these are fundamental to ensure the best gameplay experience.

This is an attack defense CTF.  
You have to do the following things:

1. Ensure the availability of all your vuln box services.
2. Defend your vuln box.
3. Attack other players vuln boxes.

### VULN_BOX Installation

Download the .ova file @ https://mega.nz/#F!gEVyESDC!JddG3WPFMZEQX7y9dN74rw

The share contains the following files:
- The vuln_box ova virtual machine
- The attack_library to assist you with exploitation

The virtual machine is a debian 9 (stretch) linux box.

Import the .ova file into virtualbox and start the machine.  
You can use vmware workstation, but it isn't supported officially and you are expected to troubleshoot for yourself.  
(!) Attention: Do not change any network settings for security reasons!

You can login to your machine by using the following users:
1. user (password = user)
2. root (password = root)

Now replace your access token under /home/tunnel/auth_token with your personal one from the Flags/Stats site.

If you want to remotely access your machine you can set up a secure ssh tunnel.

Finally, reboot your vuln_box with: sudo reboot now


### General Instructions

The muffinCTF challenge requires you to do your own research and troubleshooting.  
Availability of your vulnerable machine is your responsibility, make sure to take frequent snapshots.  
You will get the hackvent flag if your service remains unexploited over a certain period of time.  
Hackvent flags are not released before (01:00 CEST) of each day.

Any further information about the challenge is provided over the following Twitter accounts:

News: @_muffinx  
Support: @_muffinx, @xorkiwi

Please note that support is only provided for fundamental infrastructure or challenge problems, not to help you setup your vuln box.

### Ensure Availability

To score availability points you have to make sure that your services are up and are functioning properly.
The services are being monitored in regular intervals (ticks) to ensure that they are reachable and the application logic isn't broken.

At day one (00:01 CEST) you are provided with the virtual machine and two preinstalled services.

- You have to defend the services, if other players exploit it and mess with them, you loose availability points.
- If you patch the services badly and cause unusual application behaviour, you will loose availability points.
- If you have to restart/reinstall your services and they aren't reachable, you will loose availability points.

Additionally, on day two and three (00:01 CEST), you will be provided with additional services as zip files.

- You are responsible for setting the services up, if they don't run, you will loose availability points.
- The availability checking persists at any time, so be as quick as possible.

### Defend Services

To make sure your services don't get exploited and stay available you have to fix intenional coding errors, making them safe to use.  
There might be some backdoors involved, which you have to clear from your services ;)

Here's a quick overview on how to patch a vulnerable service:

Lets have a look at the bakery service.  

At /etc/systemd/system/ we can see there is a bakery.service file which starts the bakery service.

The service code is stored at /home/servicename/. For example bakery whould be in the /home/bakery/ directory.

The next step is to look at the sourcecode and checking which vulnerabilities are present.

Now you can fix the code so the vulnerability doesn't persist anymore.

Afterwards the service requires a reload: sudo systemctl restart bakery.service

It is recommended to patch the services on your local machine and publish the changes as few as possible to ensure a high availability.

(!) Attention: When fixing services you should keep in mind to not cause any issues with the application logic.  
Only fix the vulnerabilities, else the checker service, which tests if your service works will not give you points for availability.  
You get defense points if your service remains available and unexploited.

### Attack services

Exploiting other services is weighted heighest in the ranking.  
First you have to identify the vulnerable part of the application and write an exploit.  
In post exploitation you have to identify the flag location and exfiltrate it.  
You can also use your exploit to mess with other players services, making them loose availability.

The flag format is muffinCTF{...}.

Now you can make use of the attack_library to automate your exploit and steal flags from as many other players as possible.  
Finally you can submit them using the attack_library to get points.

### Rules

The rules are:

- Do not attack whale.hacking-lab.com
- Do not Denial of Service whale.hacking-lab.com
- Do not use Hypervisor Exploits to break out of player virtual machines
- Do not create Kernel Panic in players virtual machines
- Do not deploy malware on player virtual machines
- Do not deploy randsomware on player virtual machines
- Do not activate network (lan) functionalities for the virtual machine
- Do not steal/use other players authentication keys
- Do not reverse engineer the tunneling mechanism

What is allowed:

- Attack players virtual machines over whale.hacking-lab.com
- Create small patches for own services
- Deploy small backdoors in player virtual machines
- Destroy / corrupt player services in player virtual machines
- Shutdown player virtual machines
