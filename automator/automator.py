#!/usr/bin/env python
"""
automator.py

A tool that communciate the phone to start transmitting log messages.

Author: Jiayao Li, Samson Richard Wong
"""

import binascii
import os
import optparse
import serial
import sys

from trace_collector import *

# Define some constants
IN_EXE = hasattr(sys, "frozen") # true if the code is being run in an exe
if IN_EXE:
    PROGRAM_PATH   = sys.executable
    COMMAND_FILES_PATH = "./command_files"
else:
    PROGRAM_PATH   = sys.argv[0]
    COMMAND_FILES_PATH = "../command_files"
PROGRAM_DIR_PATH = os.path.dirname(os.path.abspath(PROGRAM_PATH))
WS_DISSECT_EXECUTABLE_PATH = os.path.join(PROGRAM_DIR_PATH, "../ws_dissector/dissect")
LIBWIRESHARK_PATH = "/home/likayo/wireshark-local-1.12.3/lib"


def init_opt():
    """
    Initialize and return the option parser.
    """
    opt = optparse.OptionParser(prog="automator",
                                usage="usage: %prog [options] -p PHY_PORT_NAME ...",
                                description="Automatic mobile trace collector.")
    opt.add_option("-p", "--phy-serial-name",
                    metavar="STR",
                    action="store", type="string", dest="phy_serial_name", 
                    help="Manually set the name of physical serial name.")
    # TODO: temporarily removed
    # opt.add_option("-l", "--log-output",
    #                 metavar="STR",
    #                 action="store", type="string", dest="log_output", 
    #                 help="Specify a log file to save packets in")
    # TODO: temporarily removed or permanantly???
    # opt.add_option("-c", "--commands-file",
    #                 metavar="STR",
    #                 action="store", type="string", dest="cmd_file_name", 
    #                 help="Specify the file which contains the commands to send to the phone.")
    opt.add_option("--phy-baudrate",
                    metavar="N",
                    action="store", type="int", dest="phy_baudrate", 
                    help="Set the physical baud rate [default: %default].")
    opt.set_defaults(phy_baudrate=9600)
    return opt


if __name__ == "__main__":
    opt = init_opt()
    options, args = opt.parse_args(sys.argv[1:])

    if not options.phy_serial_name:
        opt.error("please use -p option to specify physical port name.")
        sys.exit(1)

    src = DMCollector(prefs={
                        "command_files_path": os.path.join(PROGRAM_DIR_PATH, COMMAND_FILES_PATH),
                        "ws_dissect_executable_path": WS_DISSECT_EXECUTABLE_PATH,
                        "libwireshark_path": LIBWIRESHARK_PATH,
                        })
    src.set_serial_port(options.phy_serial_name)
    src.set_baudrate(options.phy_baudrate)

    src.run()
    
    # log = None
    # if options.log_output is not None:
    #     log = open(options.log_output, "w")
