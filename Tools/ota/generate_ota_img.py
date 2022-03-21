#!/usr/bin/env python3

import argparse
import sys
import os
import logging

def parse_command_line_arguments():
    """Parse command-line arguments"""
    parser = argparse.ArgumentParser()

    parser.add_argument("--chip_config_header",
                        help="path to Matter config header file")

    parser.add_argument("--chip_root",
                        help="Path to root Matter directory")

    parser.add_argument("--in_file",
                        help="Path to input file to format to Matter OTA fileformat")

    parser.add_argument("--out_file",
                        help="Path to output file (.ota file)")

    args = parser.parse_args()
    if not args.chip_root:
        logging.error("Supply Matter root directory")
        sys.exit()        

    if not args.in_file:
        logging.error("Supply input file")
        sys.exit()        

    if not args.out_file:
        logging.error("Supply output file")
        sys.exit()        

    return args

def extract_vid_and_pid(chip_config_header):
    vid = None
    pid = None
    with open(chip_config_header, 'r') as config_file:
        lines = config_file.readlines()
        
    for line in lines:
        if 'CHIP_DEVICE_CONFIG_DEVICE_VENDOR_ID' in line and '#define' in line:
            vid = line.split()[2]
        if 'CHIP_DEVICE_CONFIG_DEVICE_PRODUCT_ID' in line and '#define' in line:
            pid = line.split()[2]

    if vid is None or pid is None:
        print("Error retrieving PID and VID from configuration file ({})".format(chip_config_header))
        exit(-1)
    return vid, pid
        
def exec_image_tool(chip_config_header, chip_root, in_file, out_file, vn, vs):

    vid, pid = extract_vid_and_pid(chip_config_header)
    args = "create -v {} -p {} -vn {} -vs {} -da sha256".format(vid, pid, vn, vs)
    cmd = "{}/src/app/ota_image_tool.py {} {} {}".format(chip_root, args, in_file, out_file)
    os.system(cmd)

# Take cmd line parameters <chip_config_header> <chip_root> <in> <out> and call CHIP OTA header generation script
def main():
    
    args = parse_command_line_arguments()

    if args.chip_config_header == None:
        #Find CHIPProjectConfig.h based on chip_root directory - This is done for GN build
        #of the applications. For SDK build, the CHIPProjectConfig.h path is given as argument.
        if 'lighting' in args.in_file:
            project_name = 'lighting-app'
        elif 'lock' in args.in_file:
            project_name = 'lock-app'
        elif 'persistent' in args.in_file:
            project_name = 'persistent-storage'
        elif 'shell' in args.in_file:
            project_name = 'shell'

        chip_config_header = "{}/examples/{}/qpg/include/CHIPProjectConfig.h".format(args.chip_root, project_name)
    else:
        chip_config_header = args.chip_config_header
        
    exec_image_tool(chip_config_header, args.chip_root, args.in_file, args.out_file, 1, "1.0")
        
if __name__ == "__main__":
    main()
