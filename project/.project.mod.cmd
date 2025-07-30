cmd_/home/pi/project/project.mod := printf '%s\n'   project.o | awk '!x[$$0]++ { print("/home/pi/project/"$$0) }' > /home/pi/project/project.mod
