cmd_/home/pi/project/Module.symvers :=  sed 's/ko$$/o/'  /home/pi/project/modules.order | scripts/mod/modpost -m -a    -o /home/pi/project/Module.symvers -e -i Module.symvers -T - 
