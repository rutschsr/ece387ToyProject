import sys
import os
import subprocess
import random
import operator
import csv
import logging
import tempfile

def run_command(command):
    print('----------------------------------------')
    print('Executing: '+command)
    pipe = subprocess.Popen(command, shell=True, bufsize=1, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, universal_newlines=True)
    #pipe.stdout.close()
    out, err = pipe.communicate()
    print (out)
    

# 0_script 1_list_of_student_usernames 2_directory_to_store_files
# SAMPLE: python compile_script.py level_of_compilation comport
print ("Number of arguments: %d" %  len(sys.argv))
print ("Argument List: %s" % str(sys.argv))

files_to_compile = ['stop_light_fixed']
directories = ['']
file_to_compile = 'stop_light_fixed'
#Com port on my linux virtual machine
if len(sys.argv) == 2:
    com_port = '/dev/ttyACM0'
else:
	com_port = sys.argv[2]

level_of_compilation = int(sys.argv[1])

#path_win_avr = '/users/sam/Desktop/test_size_egb267'
path_win_avr = ''

if level_of_compilation == 0: 
    for dir in directories:
        cmd = 'rm '+dir+'/*.o'
        run_command(cmd)
        cmd = 'rm '+dir+'/*~*'
        run_command(cmd)

    cmd = 'rm *.o'
    run_command(cmd)
    cmd = 'rm '+file_to_compile
    run_command(cmd)
    cmd = 'rm *.hex'
    run_command(cmd)
    cmd = 'rm  *~*'
    run_command(cmd)
    cmd = 'rm -f .*un'
    run_command(cmd)

if level_of_compilation >= 1: 
    cmd = 'rm '+file_to_compile
    run_command(cmd)
    cmd = 'rm *.o'
    run_command(cmd)
    cmd = 'rm *.hex'
    run_command(cmd)
    for fs in files_to_compile:
        cmd = path_win_avr + 'avr-gcc -Wall -Os -DF_CPU=16000000UL -mmcu=atmega32u4 -c -o '+fs+'.o '+fs+'.c'
        run_command(cmd)
    


    
if level_of_compilation >= 2:
    cmd = path_win_avr + 'avr-gcc -mmcu=atmega32u4 '
    for fs in files_to_compile:
        cmd = cmd+fs+'.o ' 
    cmd = cmd +'-o '+file_to_compile
    run_command(cmd)

if level_of_compilation >= 3:
    cmd = path_win_avr + 'avr-objcopy -O ihex -R .eeprom '+file_to_compile+' '+file_to_compile+'.hex'
    run_command(cmd)

if level_of_compilation >= 4:
    cmd = path_win_avr + 'avrdude -p m32u4 -P'+com_port+' -carduino -D -U flash:w:'+file_to_compile+'.hex:i'
    run_command(cmd)
